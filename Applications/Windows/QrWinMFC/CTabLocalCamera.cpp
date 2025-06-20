// CTabLocalCamera.cpp : implementation file
//

#include "pch.h"
#include "QrWinMFC.h"
#include "QrWinMFCDlg.h"
#include "CTabLocalCamera.h"
#include "afxdialogex.h"
#include <functional>

// CTabLocalCamera dialog

IMPLEMENT_DYNAMIC(CTabLocalCamera, CDialogEx)

CTabLocalCamera::CTabLocalCamera(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_LOCALCAMERA, pParent)
{

}

CTabLocalCamera::~CTabLocalCamera()
{
}

void CTabLocalCamera::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_LOCAL_CONNECT, m_BtnLocalConnect);
	DDX_Control(pDX, IDC_COMBO_LOCAL_CAMERALIST, m_CbLocalCamList);
	DDX_Control(pDX, IDC_EDIT_ACQUISITION_COUNT, m_EditAcquisitionCount);
	DDX_Control(pDX, IDC_BUTTON_BEGIN_ACQUISITION, m_BtnBeginAcquisition);
	DDX_Control(pDX, IDC_BUTTON_END_ACQUISITION, m_BtnEndAcquisition);
	DDX_Control(pDX, IDC_BUTTON_SW_TRIGGER, m_BtnSwTrigger);
	DDX_Control(pDX, IDC_RADIO_TRIGGERMODE_ON, m_RadioTriggerModeOn);
	DDX_Control(pDX, IDC_RADIO_TRIGGERMODE_OFF, m_RadioTriggerModeOff);
	DDX_Control(pDX, IDC_BUTTON_GET_CAMERA_POSITION, m_BtnGetCameraPosition);
	DDX_Control(pDX, IDC_BUTTON_SET_CAMERA_POSITION, m_BtnSetCameraPosition);
	DDX_Control(pDX, IDC_RADIO_CAMERA_POSITION_LEFT, m_RadioCameraPositionLeft);
	DDX_Control(pDX, IDC_RADIO_CAMERA_POSITION_RIGHT, m_RadioCameraPositionRight);
	DDX_Control(pDX, IDC_RADIO_CAMERA_POSITION_UNKNOWN, m_RadioCameraPositionUnknown);
}


BEGIN_MESSAGE_MAP(CTabLocalCamera, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOCAL_CONNECT, &CTabLocalCamera::OnBnClickedButtonLocalConnect)
	ON_MESSAGE(WM_QRFRAME_EVENT, &CTabLocalCamera::OnMessageEventHandler)
	ON_BN_CLICKED(IDC_BUTTON_BEGIN_ACQUISITION, &CTabLocalCamera::OnBnClickedButtonBeginAcquisition)
	ON_BN_CLICKED(IDC_BUTTON_END_ACQUISITION, &CTabLocalCamera::OnBnClickedButtonEndAcquisition)
	ON_BN_CLICKED(IDC_RADIO_TRIGGERMODE_ON, &CTabLocalCamera::OnBnClickedRadioTriggermodeOn)
	ON_BN_CLICKED(IDC_BUTTON_SW_TRIGGER, &CTabLocalCamera::OnBnClickedButtonSwTrigger)
	ON_BN_CLICKED(IDC_RADIO_TRIGGERMODE_OFF, &CTabLocalCamera::OnBnClickedRadioTriggermodeOff)
	ON_BN_CLICKED(IDC_BUTTON_GET_CAMERA_POSITION, &CTabLocalCamera::OnBnClickedButtonGetCameraPosition)
	ON_BN_CLICKED(IDC_BUTTON_SET_CAMERA_POSITION, &CTabLocalCamera::OnBnClickedButtonSetCameraPosition)
END_MESSAGE_MAP()

double minVal = 0.0;
double maxVal = 0.0;
double avgVal = 0.0;

UINT CTabLocalCamera::FrameProcessingThread(LPVOID pParam)
{
	auto* tp = static_cast<ThreadParam*>(pParam);
	auto  pFrame = std::move(tp->frame);
	auto  pThis = tp->pThis;
	delete tp;

	QrSDK::QrPoint minLoc, maxLoc;
	//double minVal = 0.0;
	//double maxVal = 0.0;

	QrSDK::QrRect qrRect;
	qrRect.x = -1;
	qrRect.y = -1;
	qrRect.width = -1;
	qrRect.height = -1;
	pFrame->MinMaxLoc(qrRect, &minVal, &maxVal, &minLoc, &maxLoc);
	pFrame->MeasureROI(theApp.pMainDlg->pQrCamera->qrROI);

	avgVal = (minVal + maxVal) / 2;

	return 0;
}

LRESULT CTabLocalCamera::OnMessageEventHandler(WPARAM wParam, LPARAM)
{
	CRect rect;
	CStatic* picBox = &theApp.pMainDlg->m_TabCameraPreview.m_PictureBoxCameraPreview;
	picBox->GetClientRect(rect);
	CDC* dc = picBox->GetDC();
	bool ret = false;

	if (theApp.pMainDlg->pQrCamera == nullptr)
	{
		return 0;
	}

	theApp.pMainDlg->pQrCamera->Resize(rect.Width(), rect.Height());


	auto sp = std::unique_ptr<QrSDK::QrFramePtr>(reinterpret_cast<QrSDK::QrFramePtr*>(wParam));
	QrSDK::QrFramePtr pFrame = std::move(*sp);


	//QrSDK::QrImage qrImage;
	if (pFrame->QueryImage(theApp.pMainDlg->qrImage))
	{
		if (theApp.pMainDlg->isWriting == TRUE) {
			if (theApp.pMainDlg->qrVideoWriter.IsOpen() == TRUE) {
				if (theApp.pMainDlg->m_TabCameraPreview.m_RadioRecordFrame.GetCheck() == BST_CHECKED) {
					ret = theApp.pMainDlg->qrVideoWriter.Write(*pFrame);
				}
				else {
					ret = theApp.pMainDlg->qrVideoWriter.Write(theApp.pMainDlg->qrImage);
				}
				if (ret == FALSE) {
					std::cout << "Write Image Failed!" << endl;
				}
			}
		}

		switch (theApp.pMainDlg->cem) {
		case QrSDK::QrCEM::CEM_NONE:
			theApp.pMainDlg->qrImage.SetCEM(QrSDK::QrCEM::CEM_NONE);
			break;
		case QrSDK::QrCEM::CEM_LINEAR:
			theApp.pMainDlg->qrImage.SetCEM(QrSDK::QrCEM::CEM_LINEAR, theApp.pMainDlg->cem_linear_gain, theApp.pMainDlg->cem_linear_offset);
			break;
		case QrSDK::QrCEM::CEM_HISTEQ:
			theApp.pMainDlg->qrImage.SetCEM(QrSDK::QrCEM::CEM_HISTEQ);
			break;
		}

		theApp.pMainDlg->qrImage.SetColorMap(theApp.pMainDlg->colormap);

		//QrSDK::QrPoint minLoc, maxLoc;
		//double minVal = 0.0;
		//double maxVal = 0.0;

		//QrSDK::QrRect qrRect;
		//qrRect.x = -1;
		//qrRect.y = -1;
		//qrRect.width = -1;
		//qrRect.height = -1;
		//pFrame->MinMaxLoc(qrRect, &minVal, &maxVal, &minLoc, &maxLoc);
		//pFrame->MeasureROI();
		//double avgVal = (minVal + maxVal) / 2;

		auto* param = new ThreadParam{ pFrame, this };

		CString s;
		m_EditAcquisitionCount.GetWindowTextW(s);
		auto frameCnt = _wtoi(s);
		if (frameCnt == 0)
		{
			::AfxBeginThread(FrameProcessingThread, param);
		}
		else
		{
			CWinThread* pThread = ::AfxBeginThread(FrameProcessingThread, param);
			pThread->m_bAutoDelete = FALSE;
			::WaitForSingleObject(pThread->m_hThread, INFINITE);
			delete pThread;
		}

		double minTemp = 0.0;
		double maxTemp = 0.0;
		double avgTemp = 0.0;
		CString str;
		
		int tempUnitIndex = theApp.pMainDlg->m_ComboBox_TempUnit.GetCurSel();

		switch (tempUnitIndex)
		{
		case 0: // RAW/Kelvin
			minTemp = minVal;
			avgTemp = avgVal;
			maxTemp = maxVal;
			str.Format(_T("%ld K"), static_cast<int>(minTemp));
			theApp.pMainDlg->m_Static_TempMin.SetWindowTextW(str);
			str.Format(_T("%ld K"), static_cast<int>(avgTemp));
			theApp.pMainDlg->m_Static_TempAvg.SetWindowTextW(str);
			str.Format(_T("%ld K"), static_cast<int>(maxTemp));
			theApp.pMainDlg->m_Static_TempMax.SetWindowTextW(str);
			break;
		case 1: // Celsius
			// 온도 변환된 데이터인 경우 직접 사용, 아닌 경우 변환
			if (theApp.pMainDlg->pQrCamera->GetTempUnit() == QrSDK::tTempUnit::CELSIUS) {
				// 이미 Celsius로 변환된 데이터
				minTemp = minVal;
				avgTemp = avgVal;
				maxTemp = maxVal;
			} else {
				// Raw 데이터를 Celsius로 변환
				minTemp = pFrame->GetTempAsCelsius((unsigned short)minVal);
				avgTemp = pFrame->GetTempAsCelsius((unsigned short)avgVal);
				maxTemp = pFrame->GetTempAsCelsius((unsigned short)maxVal);
			}
			str.Format(_T("%.1lf \u2103"), minTemp);
			theApp.pMainDlg->m_Static_TempMin.SetWindowTextW(str);
			str.Format(_T("%.1lf \u2103"), avgTemp);
			theApp.pMainDlg->m_Static_TempAvg.SetWindowTextW(str);
			str.Format(_T("%.1lf \u2103"), maxTemp);
			theApp.pMainDlg->m_Static_TempMax.SetWindowTextW(str);
			break;
		case 2: // Fahrenheit
			// 온도 변환된 데이터인 경우 직접 사용, 아닌 경우 변환
			if (theApp.pMainDlg->pQrCamera->GetTempUnit() == QrSDK::tTempUnit::FAHRENHEIT) {
				// 이미 Fahrenheit로 변환된 데이터
				minTemp = minVal;
				avgTemp = avgVal;
				maxTemp = maxVal;
			} else {
				// Raw 데이터를 Fahrenheit로 변환
				minTemp = pFrame->GetTempAsFahrenheit((unsigned short)minVal);
				avgTemp = pFrame->GetTempAsFahrenheit((unsigned short)avgVal);
				maxTemp = pFrame->GetTempAsFahrenheit((unsigned short)maxVal);
			}
			str.Format(_T("%.1lf \u2109"), minTemp);
			theApp.pMainDlg->m_Static_TempMin.SetWindowTextW(str);
			str.Format(_T("%.1lf \u2109"), avgTemp);
			theApp.pMainDlg->m_Static_TempAvg.SetWindowTextW(str);
			str.Format(_T("%.1lf \u2109"), maxTemp);
			theApp.pMainDlg->m_Static_TempMax.SetWindowTextW(str);
			break;
		case 3: // Kelvin
			// 온도 변환된 데이터인 경우 직접 사용, 아닌 경우 변환
			if (theApp.pMainDlg->pQrCamera->GetTempUnit() == QrSDK::tTempUnit::KELVIN) {
				// 이미 Kelvin으로 변환된 데이터
				minTemp = minVal;
				avgTemp = avgVal;
				maxTemp = maxVal;
			} else {
				// Raw 데이터를 Kelvin으로 변환
				minTemp = pFrame->GetTempAsKelvin((unsigned short)minVal);
				avgTemp = pFrame->GetTempAsKelvin((unsigned short)avgVal);
				maxTemp = pFrame->GetTempAsKelvin((unsigned short)maxVal);
			}
			str.Format(_T("%.1lf K"), minTemp);
			theApp.pMainDlg->m_Static_TempMin.SetWindowTextW(str);
			str.Format(_T("%.1lf K"), avgTemp);
			theApp.pMainDlg->m_Static_TempAvg.SetWindowTextW(str);
			str.Format(_T("%.1lf K"), maxTemp);
			theApp.pMainDlg->m_Static_TempMax.SetWindowTextW(str);
			break;
		}


		switch (tempUnitIndex)
		{
		case 0:
			str.Format(_T("%.0lf"), minVal);
			theApp.pMainDlg->m_Static_RawMin.SetWindowTextW(str);
			str.Format(_T("%.0lf"), avgVal);
			theApp.pMainDlg->m_Static_RawAvg.SetWindowTextW(str);
			str.Format(_T("%.0lf"), maxVal);
			theApp.pMainDlg->m_Static_RawMax.SetWindowTextW(str);
			break;
		default:
			str.Format(_T("--"));
			theApp.pMainDlg->m_Static_RawMin.SetWindowTextW(str);
			str.Format(_T("--"));
			theApp.pMainDlg->m_Static_RawAvg.SetWindowTextW(str);
			str.Format(_T("--"));
			theApp.pMainDlg->m_Static_RawMax.SetWindowTextW(str);
			break;
		}


		CImage image;
		image.Create(theApp.pMainDlg->qrImage.Width, theApp.pMainDlg->qrImage.Height, 24);

		// Draw bitmap
		SetBitmapBits(image, theApp.pMainDlg->qrImage.Width * theApp.pMainDlg->qrImage.Height * 3, theApp.pMainDlg->qrImage.ToBitmapData());

		image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);

		std::vector<QrSDK::QrRoiItem> item = theApp.pMainDlg->pQrCamera->qrROI.Items;
		for (int i = 0; i < theApp.pMainDlg->pQrCamera->qrROI.Length(); i++) {
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
			switch (tempUnitIndex)
			{
			case 0: // RAW/Kelvin
				strMaxROI.Format(_T("%.0lf K"), item[i].MaxTempLoc.value);
				break;
			case 1: // Celsius
				if (theApp.pMainDlg->pQrCamera->GetTempUnit() == QrSDK::tTempUnit::CELSIUS) {
					strMaxROI.Format(_T("%.0lf \u2103"), item[i].MaxTempLoc.value);
				} else {
					strMaxROI.Format(_T("%.0lf \u2103"), pFrame->GetTempAsCelsius((unsigned short)item[i].MaxTempLoc.value));
				}
				break;
			case 2: // Fahrenheit
				if (theApp.pMainDlg->pQrCamera->GetTempUnit() == QrSDK::tTempUnit::FAHRENHEIT) {
					strMaxROI.Format(_T("%.0lf \u2109"), item[i].MaxTempLoc.value);
				} else {
					strMaxROI.Format(_T("%.0lf \u2109"), pFrame->GetTempAsFahrenheit((unsigned short)item[i].MaxTempLoc.value));
				}
				break;
			case 3: // Kelvin
				if (theApp.pMainDlg->pQrCamera->GetTempUnit() == QrSDK::tTempUnit::KELVIN) {
					strMaxROI.Format(_T("%.0lf K"), item[i].MaxTempLoc.value);
				} else {
					strMaxROI.Format(_T("%.0lf K"), pFrame->GetTempAsKelvin((unsigned short)item[i].MaxTempLoc.value));
				}
				break;
			}
			dc->SetTextColor(RGB(255, 0, 0));
			CRect tempRect(item[i].MaxTempLoc.x, item[i].MaxTempLoc.y, item[i].MaxTempLoc.x + 10, item[i].MaxTempLoc.y + 10);
			dc->DrawText(strMaxROI, tempRect, DT_SINGLELINE | DT_NOCLIP);

			SelectObject(dc->m_hDC, hOldBrush);
			SelectObject(dc->m_hDC, hOldPen);
			DeleteObject(hPen);
		}

		image.Destroy();
	}

	if (dc) {
		picBox->ReleaseDC(dc);
	}

	//theApp.pMainDlg->qrFrame = std::move(*pFrame);
	theApp.pMainDlg->qrFrame = *pFrame;

	return 0;
}

unsigned int NumOfFrames = 0;
unsigned int FrameCount = 0;

/// <summary>
/// Callback function
/// </summary>
/// <param name="frame"></param>
void OnFrameEventHandler(QrSDK::QrFramePtr frame)
{
	HWND hWnd = theApp.pMainDlg->m_TabLocalCamera.GetSafeHwnd();
	
	//auto pSp = new QrSDK::QrFramePtr(std::make_shared<QrSDK::QrFrame>(*frame));
	auto pSp = new QrSDK::QrFramePtr(frame);

	::PostMessage(
		hWnd,
		WM_QRFRAME_EVENT,
		reinterpret_cast<WPARAM>(pSp),
		0
	);

	if (NumOfFrames > 0)
	{
		if (++FrameCount >= NumOfFrames)
		{
			theApp.pMainDlg->m_TabLocalCamera.OnBnClickedButtonEndAcquisition();
		}
	}
}

class TestClass
{
public:
	void print()
	{
		cout << "Callback Context Test!!" << endl;
	}
};

void OnFrameEventHandlerWithContext(QrSDK::QrFramePtr frame, void* context)
{
	HWND hWnd = theApp.pMainDlg->m_TabLocalCamera.GetSafeHwnd();

	//TestClass* pContext = (TestClass*)context;
	//pContext->print();

	auto pSp = new QrSDK::QrFramePtr(frame);

	::PostMessage(
		hWnd,
		WM_QRFRAME_EVENT,
		reinterpret_cast<WPARAM>(pSp),
		0
	);

	if (NumOfFrames > 0)
	{
		if (++FrameCount >= NumOfFrames)
		{
			theApp.pMainDlg->m_TabLocalCamera.OnBnClickedButtonEndAcquisition();
		}
	}
}

void CTabLocalCamera::OnFrameEventHandler(QrSDK::QrFramePtr frame)
{
	HWND hWnd = theApp.pMainDlg->m_TabLocalCamera.GetSafeHwnd();
	
	//auto pSp = new QrSDK::QrFramePtr(std::make_shared<QrSDK::QrFrame>(*frame));
	auto pSp = new QrSDK::QrFramePtr(frame);

	::PostMessage(
		hWnd,
		WM_QRFRAME_EVENT,
		reinterpret_cast<WPARAM>(pSp),
		0
	);

	if (NumOfFrames > 0)
	{
		if (++FrameCount >= NumOfFrames)
		{
			theApp.pMainDlg->m_TabLocalCamera.OnBnClickedButtonEndAcquisition();
		}
	}
}


void CTabLocalCamera::OnBnClickedButtonLocalConnect()
{
	CString strCaption;
	m_BtnLocalConnect.GetWindowTextW(strCaption);
	
	if (strCaption == _T("CONNECT"))
	{
		int index = m_CbLocalCamList.GetCurSel();
		if (index >= 0)
		{
			//int serial = m_CbLocalSerialPorts.GetCurSel();
			
			//if (serial >= 0)
			{
				try
				{
					//CString name;
					//m_CbLocalSerialPorts.GetLBText(serial, name);

					theApp.pMainDlg->pQrCamera = new QrSDK::QrLocalCamera();
					if (theApp.pMainDlg->pQrCamera->Connect(index) && theApp.pMainDlg->pQrCamera->IsConnect)
					{

						if (theApp.pMainDlg->pQrCamera->Open(theApp.pMainDlg->camList[index].portName))
						{
							//	1. Read directly from the camera
							//theApp.pMainDlg->m_hThread = AfxBeginThread(CQrWinMFCDlg::FrameWorker, theApp.pMainDlg);


							//	2. Using a Callback Function
							// theApp.pMainDlg->pQrCamera->RegisterEventHandler(OnFrameEventHandler);

							//	3. Using a Callback Function - 람다 방식으로 멤버 함수 등록
							//theApp.pMainDlg->pQrCamera->RegisterEventHandler(
							//	[this](QrSDK::QrFramePtr frame) {
							//		this->OnFrameEventHandler(frame);
							//	}
							//);

							//	4. Using a Callback Function - with context pointer
							TestClass* tClass = new TestClass();
							theApp.pMainDlg->pQrCamera->RegisterEventHandler(OnFrameEventHandlerWithContext, tClass);
							


							theApp.pMainDlg->pQrCamera->BeginAcquisition();

							m_EditAcquisitionCount.EnableWindow(FALSE);
							m_BtnBeginAcquisition.EnableWindow(FALSE);
							m_BtnEndAcquisition.EnableWindow(TRUE);

							m_RadioTriggerModeOff.EnableWindow(TRUE);
							m_RadioTriggerModeOn.EnableWindow(TRUE);

							m_BtnLocalConnect.SetWindowTextW(_T("DISCONNECT"));

							///if (theApp.pMainDlg->m_TabControlProduct.m_ComboProtocol.GetCurSel() == 0) {
							///	theApp.pMainDlg->pQrCamera->qrControl.pQrCtrl->protocolMode = QrSDK::QrProtocol::MODE_NORMAL;
							///}
							///else if (theApp.pMainDlg->m_TabControlProduct.m_ComboProtocol.GetCurSel() == 1) {
							///	theApp.pMainDlg->pQrCamera->qrControl.pQrCtrl->protocolMode = QrSDK::QrProtocol::MODE_PACKET;
							///}
							///theApp.pMainDlg->m_TabControlProduct.RefreshButton();
							


							theApp.pMainDlg->pQrCamera->qrControl.GetAllInform();

							m_pTabProduct->SetDlgItemText(IDC_EDIT_PRODUCT_VERSION, CString(theApp.pMainDlg->pQrCamera->qrControl.ProductVersion().c_str()));
							m_pTabProduct->SetDlgItemText(IDC_EDIT_HW_VERSION, CString(theApp.pMainDlg->pQrCamera->qrControl.HardwareVersion().c_str()));
							m_pTabProduct->SetDlgItemText(IDC_EDIT_SW_VERSION, CString(theApp.pMainDlg->pQrCamera->qrControl.SoftwareVersion().c_str()));
							m_pTabProduct->SetDlgItemText(IDC_EDIT_PRODUCT_SERIAL, CString(theApp.pMainDlg->pQrCamera->qrControl.ProductSerial().c_str()));
							m_pTabProduct->SetDlgItemText(IDC_EDIT_SENSOR_SERIAL, CString(theApp.pMainDlg->pQrCamera->qrControl.SensorSerial().c_str()));

							// Read a sensor serial number
							std::string serialNumber = theApp.pMainDlg->pQrCamera->qrControl.SensorSerial();

							// 1. LoadCalibParams()
							//CString filePath = _T("..\\..\\..\\CalibrationFiles\\") + CString(serialNumber.c_str()) + ".xml";
							//CT2CA str(filePath);
							//bool ret = false;
							//if (m_pTabCalib->m_radioLowGain.GetCheck() != 0) {
							//	ret = theApp.pMainDlg->pQrCamera->LoadCalibParams(std::string(str), 1, serialNumber);
							//}
							//else {
							//	ret = theApp.pMainDlg->pQrCamera->LoadCalibParams(std::string(str), 0, serialNumber);
							//}

							// 2. LoadCalibFile()
							//std::string filePath = "C:\\388415273.xml";
							//bool ret = false;
							//if (m_pTabCalib->m_radioLowGain.GetCheck() != 0) {
							//	ret = theApp.pMainDlg->pQrCamera->LoadCalibFile(filePath, 1);
							//}
							//else {
							//	ret = theApp.pMainDlg->pQrCamera->LoadCalibFile(filePath, 0);
							//}

							// 3. LoadCalib()
							//serialNumber = "388415273";
							bool ret = false;
							if (m_pTabCalib->m_radioLowGain.GetCheck() != 0) {
								ret = theApp.pMainDlg->pQrCamera->LoadCalib(serialNumber, 1);
							}
							else {
								ret = theApp.pMainDlg->pQrCamera->LoadCalib(serialNumber, 0);
							}
							
							// GetCameraPosition()
							std::string cameraPosition = theApp.pMainDlg->pQrCamera->GetCameraPosition(serialNumber);
							if (cameraPosition == "L")
							{
								m_RadioCameraPositionLeft.SetCheck(true);
								m_RadioCameraPositionRight.SetCheck(false);
								m_RadioCameraPositionUnknown.SetCheck(false);
							}
							else if (cameraPosition == "R")
							{
								m_RadioCameraPositionLeft.SetCheck(false);
								m_RadioCameraPositionRight.SetCheck(true);
								m_RadioCameraPositionUnknown.SetCheck(false);
							}
							else
							{
								m_RadioCameraPositionLeft.SetCheck(false);
								m_RadioCameraPositionRight.SetCheck(false);
								m_RadioCameraPositionUnknown.SetCheck(true);
							}
							
							if (ret) {
								AfxMessageBox(CA2T("Successfully loaded calibration file."));
							}
							else {
								AfxMessageBox(CA2T("Failed to load the calibration file.\n(check the serial number in the file.)"));
							}
						}
					}
				}
				catch (QrSDK::QrException ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}

		}
	}
	else
	{
		if (theApp.pMainDlg->pQrCamera->IsConnect)
		{
			m_EditAcquisitionCount.EnableWindow(FALSE);
			m_BtnBeginAcquisition.EnableWindow(FALSE);
			m_BtnEndAcquisition.EnableWindow(FALSE);
			m_EditAcquisitionCount.SetWindowTextW(_T("0"));
			FrameCount = 0;
			NumOfFrames = 0;

			theApp.pMainDlg->pQrCamera->EndAcquisition();
			theApp.pMainDlg->pQrCamera->UnregisterEventHandler();
			theApp.pMainDlg->pQrCamera->Disconnect();
			m_BtnLocalConnect.SetWindowTextW(_T("CONNECT"));
			theApp.pMainDlg->m_TabRoi.OnBnClickedButtonClearRoi();
			delete theApp.pMainDlg->pQrCamera;
			theApp.pMainDlg->pQrCamera = nullptr;
		}
	}
}

void CTabLocalCamera::SetTabProductPtr(CTabControlProduct* pTab)
{
	m_pTabProduct = pTab;
}

void CTabLocalCamera::SetTabCalibPtr(CTabCalib* pTab)
{
	m_pTabCalib = pTab;
}
void CTabLocalCamera::OnBnClickedButtonBeginAcquisition()
{
	CString s;
	m_EditAcquisitionCount.GetWindowTextW(s);
	NumOfFrames = _wtoi(s);
	FrameCount = 0;

	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	m_BtnBeginAcquisition.EnableWindow(FALSE);
	m_BtnEndAcquisition.EnableWindow(TRUE);
	m_EditAcquisitionCount.EnableWindow(FALSE);

	theApp.pMainDlg->pQrCamera->BeginAcquisition();

	m_RadioTriggerModeOff.EnableWindow(TRUE);
	m_RadioTriggerModeOn.EnableWindow(TRUE);
	if (m_RadioTriggerModeOn.GetCheck() == TRUE)
		m_BtnSwTrigger.EnableWindow(TRUE);
}

void CTabLocalCamera::OnBnClickedButtonEndAcquisition()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	m_BtnBeginAcquisition.EnableWindow(TRUE);
	m_BtnEndAcquisition.EnableWindow(FALSE);
	m_EditAcquisitionCount.EnableWindow(TRUE);

	theApp.pMainDlg->pQrCamera->EndAcquisition();

	m_RadioTriggerModeOff.EnableWindow(FALSE);
	m_RadioTriggerModeOn.EnableWindow(FALSE);
	m_BtnSwTrigger.EnableWindow(FALSE);
}

void CTabLocalCamera::OnBnClickedRadioTriggermodeOn()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	theApp.pMainDlg->pQrCamera->SetTriggerMode(true);
	m_RadioTriggerModeOff.SetCheck(FALSE);
	m_BtnSwTrigger.EnableWindow(TRUE);
}

void CTabLocalCamera::OnBnClickedRadioTriggermodeOff()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	theApp.pMainDlg->pQrCamera->SetTriggerMode(false);
	m_RadioTriggerModeOn.SetCheck(FALSE);
	m_BtnSwTrigger.EnableWindow(FALSE);
}

void CTabLocalCamera::OnBnClickedButtonSwTrigger()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	theApp.pMainDlg->pQrCamera->ExecuteSoftwareTrigger();
}

void CTabLocalCamera::OnBnClickedButtonGetCameraPosition()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	std::string serialNumber = theApp.pMainDlg->pQrCamera->qrControl.SensorSerial();
	std::string position = theApp.pMainDlg->pQrCamera->GetCameraPosition(serialNumber);
	if (position == "L")
	{
		m_RadioCameraPositionLeft.SetCheck(true);
		m_RadioCameraPositionRight.SetCheck(false);
		m_RadioCameraPositionUnknown.SetCheck(false);
	}
	else if (position == "R")
	{
		m_RadioCameraPositionLeft.SetCheck(false);
		m_RadioCameraPositionRight.SetCheck(true);
		m_RadioCameraPositionUnknown.SetCheck(false);
	}
	else
	{
		m_RadioCameraPositionLeft.SetCheck(false);
		m_RadioCameraPositionRight.SetCheck(false);
		m_RadioCameraPositionUnknown.SetCheck(true);
	}
}

void CTabLocalCamera::OnBnClickedButtonSetCameraPosition()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	std::string serialNumber = theApp.pMainDlg->pQrCamera->qrControl.SensorSerial();
	if (m_RadioCameraPositionLeft.GetCheck() == true)
	{
		theApp.pMainDlg->pQrCamera->SetCameraPosition(serialNumber, "L");
	}
	else if (m_RadioCameraPositionRight.GetCheck() == true)
	{
		theApp.pMainDlg->pQrCamera->SetCameraPosition(serialNumber, "R");
	}
}
