
// QrWinMFCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "QrWinMFC.h"
#include "QrWinMFCDlg.h"
#include "afxdialogex.h"
#include <Dbt.h>
#include <initguid.h>
#include <Usbiodef.h>   // GUID_DEVINTERFACE_USB_DEVICE
#include <fstream>

namespace
{
	std::ofstream g_log;

	void WriteLog(const char* event)
	{
		if (!g_log.is_open()) return;

		SYSTEMTIME st;
		GetLocalTime(&st);

		char timebuf[32];
		sprintf_s(timebuf, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
			st.wYear, st.wMonth, st.wDay,
			st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

		g_log << "[" << timebuf << "] " << event << std::endl;
	}
}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CQrWinMFCDlg dialog
CQrWinMFCDlg::CQrWinMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_QrWinMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQrWinMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_CAMERA, m_TabCamera);
	DDX_Control(pDX, IDC_TAB_CONTROL, m_TabControl);
	DDX_Control(pDX, IDC_TAB_FEATURE, m_TabFeature);
	DDX_Control(pDX, IDC_TAB_PREVIEW, m_TabPreview);
	DDX_Control(pDX, IDC_STATIC_RAW_MAX, m_Static_RawMax);
	DDX_Control(pDX, IDC_STATIC_TEMP_MAX, m_Static_TempMax);
	DDX_Control(pDX, IDC_STATIC_RAW_AVG, m_Static_RawAvg);
	DDX_Control(pDX, IDC_STATIC_TEMP_AVG, m_Static_TempAvg);
	DDX_Control(pDX, IDC_STATIC_RAW_MIN, m_Static_RawMin);
	DDX_Control(pDX, IDC_STATIC_TEMP_MIN, m_Static_TempMin);
	DDX_Control(pDX, IDC_COMBO_TEMPUNIT, m_ComboBox_TempUnit);
}

BEGIN_MESSAGE_MAP(CQrWinMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CAMERA, &CQrWinMFCDlg::OnTcnSelchangeTabCamera)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_FEATURE, &CQrWinMFCDlg::OnTcnSelchangeTabFeature)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTROL, &CQrWinMFCDlg::OnTcnSelchangeTabControl)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PREVIEW, &CQrWinMFCDlg::OnSelchangeTabPreview)
	ON_CBN_SELCHANGE(IDC_COMBO_TEMPUNIT, &CQrWinMFCDlg::OnCbnSelchangeComboTempunit)
	ON_WM_DEVICECHANGE()
END_MESSAGE_MAP()


BOOL CQrWinMFCDlg::OnDeviceChange(UINT nEventType, DWORD_PTR dwData)
{
	PDEV_BROADCAST_HDR pHdr = reinterpret_cast<PDEV_BROADCAST_HDR>(dwData);

	switch (nEventType)
	{
	case DBT_DEVICEARRIVAL:
		if (pHdr && pHdr->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
		{
			DEV_BROADCAST_DEVICEINTERFACE* pDevIf = reinterpret_cast<DEV_BROADCAST_DEVICEINTERFACE*>(pHdr);
			CString devicePath(pDevIf->dbcc_name);

			int vidPos = devicePath.Find(L"VID_");
			int pidPos = devicePath.Find(L"PID_");
			if (vidPos >= 0 && pidPos >= 0)
			{
				CString vid = devicePath.Mid(vidPos + 4, 4);
				CString pid = devicePath.Mid(pidPos + 4, 4);

				if (vid.CompareNoCase(L"04B4") == 0 && pid.CompareNoCase(L"00F8") == 0)
				{
					char buf[128] = {};
					sprintf_s(buf, "Quantum RED is attached (VID=%ls, PID=%ls)", vid.GetString(), pid.GetString());
					WriteLog(buf);
				}
			}
		}
		break;

	case DBT_DEVICEREMOVECOMPLETE:
		if (pHdr && pHdr->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
		{
			DEV_BROADCAST_DEVICEINTERFACE* pDevIf = reinterpret_cast<DEV_BROADCAST_DEVICEINTERFACE*>(pHdr);
			CString devicePath(pDevIf->dbcc_name);

			int vidPos = devicePath.Find(L"VID_");
			int pidPos = devicePath.Find(L"PID_");
			if (vidPos >= 0 && pidPos >= 0)
			{
				CString vid = devicePath.Mid(vidPos + 4, 4);
				CString pid = devicePath.Mid(pidPos + 4, 4);

				if (vid.CompareNoCase(L"04B4") == 0 && pid.CompareNoCase(L"00F8") == 0)
				{
					char buf[128] = {};
					sprintf_s(buf, "Quantum RED is detached (VID=%ls, PID=%ls)", vid.GetString(), pid.GetString());
					WriteLog(buf);
				}
			}
		}
		break;

	default:
		break;
	}

	return TRUE;
}

// CQrWinMFCDlg message handlers

BOOL CQrWinMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(_T("QrWinMFC"));

	// 로그 파일 생성: YYYYMMDD_HHMMSS.txt
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		char filename[64];
		sprintf_s(filename, "Log_QrWinMFC_%04d%02d%02d_%02d%02d%02d.txt",
			st.wYear, st.wMonth, st.wDay,
			st.wHour, st.wMinute, st.wSecond);
		g_log.open(filename, std::ios::out | std::ios::app);
		WriteLog("Program started");
	}

	// Register for USB device interface notifications (e.g., USB cameras)
	DEV_BROADCAST_DEVICEINTERFACE NotificationFilter = {};
	NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	NotificationFilter.dbcc_classguid = GUID_DEVINTERFACE_USB_DEVICE;

	m_hDevNotify = RegisterDeviceNotification(
		this->GetSafeHwnd(),
		&NotificationFilter,
		DEVICE_NOTIFY_WINDOW_HANDLE
	);

	//// Add "About..." menu item to system menu.

	//// IDM_ABOUTBOX must be in the system command range.
	//ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	//ASSERT(IDM_ABOUTBOX < 0xF000);

	//CMenu* pSysMenu = GetSystemMenu(FALSE);
	//if (pSysMenu != nullptr)
	//{
	//	BOOL bNameValid;
	//	CString strAboutMenu;
	//	bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
	//	ASSERT(bNameValid);
	//	if (!strAboutMenu.IsEmpty())
	//	{
	//		pSysMenu->AppendMenu(MF_SEPARATOR);
	//		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	//	}
	//}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CRect rect;
	// Init Tab Camera
	m_TabCamera.GetWindowRect(rect);

	m_ComboBox_TempUnit.AddString(_T("Raw"));
	m_ComboBox_TempUnit.AddString(_T("Celsius [��]"));
	m_ComboBox_TempUnit.AddString(_T("Fehrenheit [��]"));
	m_ComboBox_TempUnit.AddString(_T("Kelvin [K]"));
	m_ComboBox_TempUnit.SetCurSel(0);

	m_TabCamera.InsertItem(0, _T("Local Camera"));
	m_TabCamera.InsertItem(1, _T("Remote Camera"));
	m_TabCamera.SetCurSel(0);

	m_TabLocalCamera.Create(IDD_TAB_LOCALCAMERA, &m_TabCamera);
	m_TabLocalCamera.MoveWindow(0, 20, rect.Width(), rect.Height());
	m_TabLocalCamera.ShowWindow(SW_SHOW);
	m_TabLocalCamera.SetTabProductPtr(&m_TabControlProduct);
	m_TabLocalCamera.SetTabCalibPtr(&m_TabCalib);
	m_TabLocalCamera.m_EditAcquisitionCount.SetActiveWindow();
	m_TabLocalCamera.m_EditAcquisitionCount.SetWindowTextW(_T("0"));
	m_TabLocalCamera.m_EditAcquisitionCount.EnableWindow(FALSE);
	m_TabLocalCamera.m_BtnBeginAcquisition.EnableWindow(FALSE);
	m_TabLocalCamera.m_BtnEndAcquisition.EnableWindow(FALSE);
	m_TabLocalCamera.m_RadioTriggerModeOff.SetCheck(TRUE);
	m_TabLocalCamera.m_RadioTriggerModeOn.SetCheck(FALSE);
	m_TabLocalCamera.m_RadioTriggerModeOff.EnableWindow(FALSE);
	m_TabLocalCamera.m_RadioTriggerModeOn.EnableWindow(FALSE);
	m_TabLocalCamera.m_BtnSwTrigger.EnableWindow(FALSE);

	m_TabRemoteCamera.Create(IDD_TAB_REMOTECAMERA, &m_TabCamera);
	m_TabRemoteCamera.MoveWindow(0, 20, rect.Width(), rect.Height());
	m_TabRemoteCamera.ShowWindow(SW_HIDE);
	m_TabRemoteCamera.m_RemoteAddress.SetAddress(192, 168, 0, 151);

	// Init Tab Control
	m_TabControl.GetWindowRect(rect);
	m_TabControl.InsertItem(0, _T("PRODUCT"));
	m_TabControl.InsertItem(1, _T("SYSTEM"));
	m_TabControl.SetCurSel(0);

	m_TabControlProduct.Create(IDD_TAB_CONTROL_PRODUCT, &m_TabControl);
	m_TabControlProduct.MoveWindow(0, 20, rect.Width(), rect.Height());
	m_TabControlProduct.ShowWindow(SW_SHOW);
	//m_TabControlProduct.m_ComboProtocol.AddString(_T("Normal Mode"));
	//m_TabControlProduct.m_ComboProtocol.AddString(_T("Packet Mode"));
	m_TabControlProduct.m_ComboViewMode.AddString(_T("NUC"));
	m_TabControlProduct.m_ComboViewMode.AddString(_T("RAW"));
	m_TabControlProduct.m_ComboViewMode.AddString(_T("PATTERN"));

	m_TabControlSystem.Create(IDD_TAB_CONTROL_SYSTEM, &m_TabControl);
	m_TabControlSystem.MoveWindow(0, 20, rect.Width(), rect.Height());
	m_TabControlSystem.ShowWindow(SW_HIDE);

	// init local camera list
	//m_TabLocalCamera.m_CbLocalCamList.ResetContent();
	//std::vector<QrSDK::tCamDev> camList = QrSDK::QrCamera::GetCameraNames();
	//for (auto name : camList)
	//{
	//	m_TabLocalCamera.m_CbLocalCamList.AddString(CString(name.name.c_str()));
	//}

	//m_TabLocalCamera.m_CbLocalSerialPorts.ResetContent();
	//std::vector<std::string> serialList = QrSDK::QrCamera::GetSerialPorts();
	//for (auto name : serialList)
	//{
	//	m_TabLocalCamera.m_CbLocalSerialPorts.AddString(CString(name.c_str()));
	//}

	camList = QrSDK::QrCamera::GetCameraList();
	for (auto cam : camList)
	{
		std::string name = cam.name + " - " + cam.portName;
		m_TabLocalCamera.m_CbLocalCamList.AddString(CString(name.c_str()));
	}

	// init picture box
//	GetDlgItem(IDC_PICTUREBOX)->MoveWindow(186, 10, 480, 360);

	// init local camera list
	m_TabControlSystem.m_CbIpMode.ResetContent();
	m_TabControlSystem.m_CbIpMode.AddString(_T("0. Static"));
	m_TabControlSystem.m_CbIpMode.AddString(_T("1. DHCP"));

	m_TabControlSystem.m_CbTrsmGuideTo.ResetContent();
	m_TabControlSystem.m_CbTrsmGuideTo.AddString(_T("0. LEFT"));
	m_TabControlSystem.m_CbTrsmGuideTo.AddString(_T("1. RIGHT"));
	m_TabControlSystem.m_CbTrsmGuideTo.AddString(_T("2. UP"));
	m_TabControlSystem.m_CbTrsmGuideTo.AddString(_T("3. DOWN"));

	m_TabPreview.GetWindowRect(rect);
	m_TabPreview.InsertItem(0, _T("Camera"));
	m_TabPreview.InsertItem(1, _T("Video"));
	m_TabPreview.SetCurSel(0);

	m_TabCameraPreview.Create(IDD_TAB_CAMERA_PREVIEW, &m_TabPreview);
	m_TabCameraPreview.MoveWindow(0, 20, rect.Width(), rect.Height());
	m_TabCameraPreview.ShowWindow(SW_SHOW);
	m_TabCameraPreview.m_RadioRecordFrame.EnableWindow(FALSE);
	m_TabCameraPreview.m_RadioRecordImage.EnableWindow(FALSE);
	m_TabCameraPreview.m_BtnCapture.EnableWindow(FALSE);

	m_TabVideoPreview.Create(IDD_TAB_VIDEO_PREVIEW, &m_TabPreview);
	m_TabVideoPreview.MoveWindow(0, 20, rect.Width(), rect.Height());
	m_TabVideoPreview.ShowWindow(SW_HIDE);

	// init picture box
	m_TabCameraPreview.GetDlgItem(IDC_PICTUREBOX)->MoveWindow(0, 0, 480, 360);
	m_TabVideoPreview.GetDlgItem(IDC_PICTUREBOX_VIDEO)->MoveWindow(0, 0, 480, 360);

	// init Feature
	m_TabFeature.GetWindowRect(rect);
	m_TabFeature.InsertItem(0, _T("ROI"));
	m_TabFeature.InsertItem(1, _T("Image"));
	m_TabFeature.InsertItem(2, _T("Calib"));
	m_TabFeature.SetCurSel(0);

	m_TabRoi.Create(IDD_TAB_ROI, &m_TabFeature);
	m_TabRoi.MoveWindow(0, 20, rect.Width(), rect.Height());
	m_TabRoi.ShowWindow(SW_SHOW);

	m_TabImage.Create(IDD_TAB_IMAGE, &m_TabFeature);
	m_TabImage.MoveWindow(0, 20, rect.Width(), rect.Height());
	m_TabImage.ShowWindow(SW_HIDE);

	m_TabCalib.Create(IDD_TAB_CALIB, &m_TabFeature);
	m_TabCalib.MoveWindow(0, 20, rect.Width(), rect.Height());
	m_TabCalib.ShowWindow(SW_HIDE);
	m_TabCalib.m_radioLowGain.SetCheck(BST_CHECKED);

	m_TabImage.m_ComboColorMap.AddString(_T("None"));
	m_TabImage.m_ComboColorMap.AddString(_T("Autumn"));
	m_TabImage.m_ComboColorMap.AddString(_T("Bone"));
	m_TabImage.m_ComboColorMap.AddString(_T("Jet"));
	m_TabImage.m_ComboColorMap.AddString(_T("Winter"));
	m_TabImage.m_ComboColorMap.AddString(_T("Rainbow"));
	m_TabImage.m_ComboColorMap.AddString(_T("Ocean"));
	m_TabImage.m_ComboColorMap.AddString(_T("Summer"));
	m_TabImage.m_ComboColorMap.AddString(_T("Spring"));
	m_TabImage.m_ComboColorMap.AddString(_T("Cool"));
	m_TabImage.m_ComboColorMap.AddString(_T("Hsv"));
	m_TabImage.m_ComboColorMap.AddString(_T("Pink"));
	m_TabImage.m_ComboColorMap.AddString(_T("Hot"));
	m_TabImage.m_ComboColorMap.AddString(_T("Parula"));
	m_TabImage.m_ComboColorMap.AddString(_T("Magma"));
	m_TabImage.m_ComboColorMap.AddString(_T("Inferno"));
	m_TabImage.m_ComboColorMap.AddString(_T("Plasma"));
	m_TabImage.m_ComboColorMap.AddString(_T("Viridis"));
	m_TabImage.m_ComboColorMap.AddString(_T("Cividis"));
	m_TabImage.m_ComboColorMap.AddString(_T("Twiight"));
	m_TabImage.m_ComboColorMap.AddString(_T("Twilight Shifted"));
	m_TabImage.m_ComboColorMap.AddString(_T("Turbo"));
	m_TabImage.m_ComboColorMap.AddString(_T("DeepGreen"));
	m_TabImage.m_ComboCem.AddString(_T("None"));
	m_TabImage.m_ComboCem.AddString(_T("Linear"));
	m_TabImage.m_ComboCem.AddString(_T("Histogram EQ"));
	m_TabImage.m_ComboColorMap.SetCurSel(0);
	m_TabImage.m_ComboCem.SetCurSel(0);

	m_TabImage.m_EditLinearGain.SetWindowText(_T("1.0"));
	m_TabImage.m_EditLinearOffset.SetWindowText(_T("0.0"));

	m_TabImage.m_EditLinearGain.EnableWindow(FALSE);
	m_TabImage.m_EditLinearOffset.EnableWindow(FALSE);
	m_TabImage.m_BtnSetLinear.EnableWindow(FALSE);

	m_TabCalib.m_EditObjEmissivity.SetWindowTextW(_T("1.0"));
	m_TabCalib.m_EditReflTemp.SetWindowTextW(_T("21.9"));
	m_TabCalib.m_EditDistance.SetWindowTextW(_T("1.0"));
	m_TabCalib.m_EditAtmTemp.SetWindowTextW(_T("21.9"));
	m_TabCalib.m_EditHumidity.SetWindowTextW(_T("0.5"));
	m_TabCalib.m_EditAtmTrans.SetWindowTextW(_T("1.0"));
	m_TabCalib.m_EditLensTemp.SetWindowTextW(_T("21.9"));
	m_TabCalib.m_EditLensTrans.SetWindowTextW(_T("1.0"));

	//EDDY // Redirect std::cout
	///FILE* stream;
	///AllocConsole();
	///freopen_s(&stream, "CONOUT$", "w", stdout);
	///freopen_s(&stream, "CONOUT$", "w", stderr);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CQrWinMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CQrWinMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CQrWinMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT CQrWinMFCDlg::FrameWorker(LPVOID param)
{
	CQrWinMFCDlg* pDlg = (CQrWinMFCDlg*)param;

	CRect rect;
	CStatic* picBox = &pDlg->m_TabCameraPreview.m_PictureBoxCameraPreview;
	picBox->GetClientRect(rect);
	CDC* dc = picBox->GetDC();

	pDlg->pQrCamera->Resize(rect.Width(), rect.Height());
	bool ret = FALSE;

	while (pDlg->pQrCamera->IsConnect)
	{
		//QrSDK::QrFrame qrFrame;
		if (pDlg->m_TabCameraPreview.m_CheckCaptureEnable.GetCheck() == BST_CHECKED)
		{
			continue;
		}
		try
		{
			if (pDlg->pQrCamera->Read(pDlg->qrFrame, (QrSDK::tTempUnit)pDlg->m_ComboBox_TempUnit.GetCurSel()) && !pDlg->qrFrame.IsEmpty())
			{
				if (pDlg->qrFrame.QueryImage(pDlg->qrImage))
				{
					if (pDlg->isWriting == TRUE) {
						if (pDlg->qrVideoWriter.IsOpen() == TRUE) {
							if (pDlg->m_TabCameraPreview.m_RadioRecordFrame.GetCheck() == BST_CHECKED) {
								ret = pDlg->qrVideoWriter.Write(pDlg->qrFrame);
							}
							else {
								ret = pDlg->qrVideoWriter.Write(pDlg->qrImage);
							}
							if (ret == FALSE) {
								std::cout << "Write Image Failed!" << endl;
							}
						}
					}

					switch (pDlg->cem) {
					case QrSDK::QrCEM::CEM_NONE:
						pDlg->qrImage.SetCEM(QrSDK::QrCEM::CEM_NONE);
						break;
					case QrSDK::QrCEM::CEM_LINEAR:
						pDlg->qrImage.SetCEM(QrSDK::QrCEM::CEM_LINEAR, pDlg->cem_linear_gain, pDlg->cem_linear_offset);
						break;
					case QrSDK::QrCEM::CEM_HISTEQ:
						pDlg->qrImage.SetCEM(QrSDK::QrCEM::CEM_HISTEQ);
						break;
					}

					pDlg->qrImage.SetColorMap(pDlg->colormap);

					QrSDK::QrPoint minLoc, maxLoc;
					double minVal, maxVal;

					QrSDK::QrRect qrRect;
					qrRect.x = -1;
					qrRect.y = -1;
					qrRect.width = -1;
					qrRect.height = -1;
					pDlg->qrFrame.MinMaxLoc(qrRect, &minVal, &maxVal, &minLoc, &maxLoc);
					double avgVal = (minVal + maxVal) / 2;

					double minTemp = 0.0;
					double maxTemp = 0.0;
					double avgTemp = 0.0;
					CString str;
					switch (pDlg->m_ComboBox_TempUnit.GetCurSel())
					{
						case 0:
							minTemp = minVal;
							avgTemp = avgVal;
							maxTemp = maxVal;
							str.Format(_T("%ld K"), static_cast<int>(minTemp));
							pDlg->m_Static_TempMin.SetWindowTextW(str);
							str.Format(_T("%ld K"), static_cast<int>(avgTemp));
							pDlg->m_Static_TempAvg.SetWindowTextW(str);
							str.Format(_T("%ld K"), static_cast<int>(maxTemp));
							pDlg->m_Static_TempMax.SetWindowTextW(str);
							break;
						case 1:
							//minTemp = pDlg->qrFrame.GetTempAsCelsius((unsigned short)minVal);
							//avgTemp = pDlg->qrFrame.GetTempAsCelsius((unsigned short)avgVal);
							//maxTemp = pDlg->qrFrame.GetTempAsCelsius((unsigned short)maxVal);
							minTemp = minVal;
							avgTemp = avgVal;
							maxTemp = maxVal;
							str.Format(_T("%.1lf ��"), minTemp);
							pDlg->m_Static_TempMin.SetWindowTextW(str);
							str.Format(_T("%.1lf ��"), avgTemp);
							pDlg->m_Static_TempAvg.SetWindowTextW(str);
							str.Format(_T("%.1lf ��"), maxTemp);
							pDlg->m_Static_TempMax.SetWindowTextW(str);
							break;
						case 2:
							//minTemp = pDlg->qrFrame.GetTempAsFahrenheit((unsigned short)minVal);
							//avgTemp = pDlg->qrFrame.GetTempAsFahrenheit((unsigned short)avgVal);
							//maxTemp = pDlg->qrFrame.GetTempAsFahrenheit((unsigned short)maxVal);
							minTemp = minVal;
							avgTemp = avgVal;
							maxTemp = maxVal;
							str.Format(_T("%.1lf ��"), minTemp);
							pDlg->m_Static_TempMin.SetWindowTextW(str);
							str.Format(_T("%.1lf ��"), avgTemp);
							pDlg->m_Static_TempAvg.SetWindowTextW(str);
							str.Format(_T("%.1lf ��"), maxTemp);
							pDlg->m_Static_TempMax.SetWindowTextW(str);
							break;
						case 3:
							//minTemp = pDlg->qrFrame.GetTempAsKelvin((unsigned short)minVal);
							//avgTemp = pDlg->qrFrame.GetTempAsKelvin((unsigned short)avgVal);
							//maxTemp = pDlg->qrFrame.GetTempAsKelvin((unsigned short)maxVal);
							minTemp = minVal;
							avgTemp = avgVal;
							maxTemp = maxVal;
							str.Format(_T("%.1lf K"), minTemp);
							pDlg->m_Static_TempMin.SetWindowTextW(str);
							str.Format(_T("%.1lf K"), avgTemp);
							pDlg->m_Static_TempAvg.SetWindowTextW(str);
							str.Format(_T("%.1lf K"), maxTemp);
							pDlg->m_Static_TempMax.SetWindowTextW(str);
							break;
					}					

					pDlg->qrFrame.MeasureROI(pDlg->pQrCamera->qrROI);
					
					switch (pDlg->m_ComboBox_TempUnit.GetCurSel())
					{
					case 0:
						str.Format(_T("%.0lf"), minVal);
						pDlg->m_Static_RawMin.SetWindowTextW(str);
						str.Format(_T("%.0lf"), avgVal);
						pDlg->m_Static_RawAvg.SetWindowTextW(str);
						str.Format(_T("%.0lf"), maxVal);
						pDlg->m_Static_RawMax.SetWindowTextW(str);
						break;
					default:
						str.Format(_T("--"));
						pDlg->m_Static_RawMin.SetWindowTextW(str);
						str.Format(_T("--"));
						pDlg->m_Static_RawAvg.SetWindowTextW(str);
						str.Format(_T("--"));
						pDlg->m_Static_RawMax.SetWindowTextW(str);
						break;
					//case 1:
					//	str.Format(_T("%.0lf ��"), minVal);
					//	pDlg->m_Static_RawMin.SetWindowTextW(str);
					//	str.Format(_T("%.0lf ��"), avgVal);
					//	pDlg->m_Static_RawAvg.SetWindowTextW(str);
					//	str.Format(_T("%.0lf ��"), maxVal);
					//	pDlg->m_Static_RawMax.SetWindowTextW(str);
					//	break;
					//case 2:
					//	str.Format(_T("%.0lf ��"), minVal);
					//	pDlg->m_Static_RawMin.SetWindowTextW(str);
					//	str.Format(_T("%.0lf ��"), avgVal);
					//	pDlg->m_Static_RawAvg.SetWindowTextW(str);
					//	str.Format(_T("%.0lf ��"), maxVal);
					//	pDlg->m_Static_RawMax.SetWindowTextW(str);
					//	break;
					//case 3:
					//	str.Format(_T("%.0lf K"), minVal);
					//	pDlg->m_Static_RawMin.SetWindowTextW(str);
					//	str.Format(_T("%.0lf K"), avgVal);
					//	pDlg->m_Static_RawAvg.SetWindowTextW(str);
					//	str.Format(_T("%.0lf K"), maxVal);
					//	pDlg->m_Static_RawMax.SetWindowTextW(str);
					//	break;
					}






					CImage image;
					image.Create(pDlg->qrImage.Width, pDlg->qrImage.Height, 24);

					// Draw bitmap
					SetBitmapBits(image, pDlg->qrImage.Width * pDlg->qrImage.Height * 3, pDlg->qrImage.ToBitmapData());

					image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);

					std::vector<QrSDK::QrRoiItem> item = pDlg->pQrCamera->qrROI.Items;
					for (int i = 0; i < pDlg->pQrCamera->qrROI.Length(); i++) {
						HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
						HBRUSH hOldBrush = (HBRUSH)SelectObject(dc->m_hDC, GetStockObject(NULL_BRUSH));
						HPEN hOldPen = (HPEN)SelectObject(dc->m_hDC, hPen);

						Rectangle(dc->m_hDC, item[i].Rect.x, item[i].Rect.y, item[i].Rect.x + item[i].Rect.width, item[i].Rect.y + item[i].Rect.height);
						CString roiStr(item[i].Name);
						CRect rect(item[i].Rect.x, item[i].Rect.y, item[i].Rect.x + item[i].Rect.width, item[i].Rect.y + item[i].Rect.height);
						dc->SetBkMode(TRANSPARENT);
						dc->SetTextColor(RGB(0, 255, 255));
						dc->DrawText(roiStr, rect, DT_SINGLELINE | DT_NOCLIP);

						CString strMaxROI;
						str.Format(_T("%.0lf K"), maxVal);
						switch (pDlg->m_ComboBox_TempUnit.GetCurSel())
						{
						case 0:
							strMaxROI.Format(_T("%.0lf K"), item[i].MaxTempLoc.value);
							break;
						case 1:
							strMaxROI.Format(_T("%.0lf ��"), pDlg->qrFrame.GetTempAsCelsius((unsigned short)item[i].MaxTempLoc.value));
							break;
						case 2:
							strMaxROI.Format(_T("%.0lf ��"), pDlg->qrFrame.GetTempAsFahrenheit((unsigned short)item[i].MaxTempLoc.value));
							break;
						case 3:
							strMaxROI.Format(_T("%.0lf K"), pDlg->qrFrame.GetTempAsKelvin((unsigned short)item[i].MaxTempLoc.value));
							break;
						}
						dc->SetTextColor(RGB(255, 0, 0));
						CRect tempRect(item[i].MaxTempLoc.x, item[i].MaxTempLoc.y, item[i].MaxTempLoc.x + 10, item[i].MaxTempLoc.y + 10);
						dc->DrawText(strMaxROI, tempRect, DT_SINGLELINE | DT_NOCLIP);

						SelectObject(dc->m_hDC, hOldBrush);
						SelectObject(dc->m_hDC, hOldPen);
						DeleteObject(hPen);
					}
				}
			}
		}
		catch (QrSDK::QrException e)
		{
			std::cout << e.what() << std::endl;
		}

	}

	return 0;
}


void CQrWinMFCDlg::OnTcnSelchangeTabCamera(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (IDC_TAB_CAMERA == pNMHDR->idFrom)
	{
		switch (m_TabCamera.GetCurSel())
		{
			case 0:
				m_TabLocalCamera.ShowWindow(SW_SHOW);
				m_TabRemoteCamera.ShowWindow(SW_HIDE);
				break;
			case 1:
				m_TabLocalCamera.ShowWindow(SW_HIDE);
				m_TabRemoteCamera.ShowWindow(SW_SHOW);
				break;
		}
	}
	*pResult = 0;
}

void CQrWinMFCDlg::OnTcnSelchangeTabControl(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (IDC_TAB_CONTROL == pNMHDR->idFrom)
	{
		switch (m_TabControl.GetCurSel())
		{
		case 0:
			m_TabControlProduct.ShowWindow(SW_SHOW);
			m_TabControlSystem.ShowWindow(SW_HIDE);
			break;
		case 1:
			m_TabControlProduct.ShowWindow(SW_HIDE);
			m_TabControlSystem.ShowWindow(SW_SHOW);;
			break;
		}
	}
	*pResult = 0;
}

void CQrWinMFCDlg::OnTcnSelchangeTabFeature(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (IDC_TAB_FEATURE == pNMHDR->idFrom)
	{
		switch (m_TabFeature.GetCurSel())
		{
		case 0:
			m_TabRoi.ShowWindow(SW_SHOW);
			m_TabImage.ShowWindow(SW_HIDE);
			m_TabCalib.ShowWindow(SW_HIDE);
			break;
		case 1:
			m_TabRoi.ShowWindow(SW_HIDE);
			m_TabImage.ShowWindow(SW_SHOW);
			m_TabCalib.ShowWindow(SW_HIDE);
			break;
		case 2:
			m_TabRoi.ShowWindow(SW_HIDE);
			m_TabImage.ShowWindow(SW_HIDE);
			m_TabCalib.ShowWindow(SW_SHOW);
			break;
		}
	}
	*pResult = 0;
}

void CQrWinMFCDlg::OnSelchangeTabPreview(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (IDC_TAB_PREVIEW == pNMHDR->idFrom)
	{
		switch (m_TabPreview.GetCurSel())
		{
		case 0:
			m_TabCameraPreview.ShowWindow(SW_SHOW);
			m_TabVideoPreview.ShowWindow(SW_HIDE);
			break;
		case 1:
			m_TabCameraPreview.ShowWindow(SW_HIDE);
			m_TabVideoPreview.ShowWindow(SW_SHOW);
			break;
		}
	}
	*pResult = 0;
}

void CQrWinMFCDlg::OnClose()
{
	WriteLog("Program exiting");
	if (g_log.is_open())
	{
		g_log.close();
	}

	if (theApp.pMainDlg->pQrCamera)
	{
		theApp.pMainDlg->pQrCamera->Disconnect();
	}

	CDialogEx::OnClose();
}

void CQrWinMFCDlg::OnCbnSelchangeComboTempunit()
{
	if (theApp.pMainDlg->pQrCamera)
	{
		theApp.pMainDlg->pQrCamera->SetTempUnit((QrSDK::tTempUnit)m_ComboBox_TempUnit.GetCurSel());
	}
}
