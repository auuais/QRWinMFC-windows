// CTabCameraPreview.cpp : implementation file
//

#include "pch.h"
#include "QrWinMFC.h"
#include "CTabCameraPreview.h"
#include "afxdialogex.h"


// CTabCameraPreview dialog

IMPLEMENT_DYNAMIC(CTabCameraPreview, CDialogEx)

CTabCameraPreview::CTabCameraPreview(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_CAMERA_PREVIEW, pParent)
{

}

CTabCameraPreview::~CTabCameraPreview()
{
}

void CTabCameraPreview::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTUREBOX, m_PictureBoxCameraPreview);
	//  DDX_Control(pDX, IDC_STATIC_FILE_RECORD, m_StaticFileFecord);
	DDX_Control(pDX, IDC_STATIC_FILE_RECORD, m_StaticFileRecord);
	DDX_Control(pDX, IDC_BUTTON_VIDEO_RECORD, m_BtnVideoRecord);
	DDX_Control(pDX, IDC_RADIO_RECORD_FRAME, m_RadioRecordFrame);
	DDX_Control(pDX, IDC_RADIO_RECORD_IMAGE, m_RadioRecordImage);
	DDX_Control(pDX, IDC_BUTTON_CAPTURE, m_BtnCapture);
	DDX_Control(pDX, IDC_CHECK_CAPTURE_ENABLE, m_CheckCaptureEnable);
}


BEGIN_MESSAGE_MAP(CTabCameraPreview, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO_FILE_RECORD, &CTabCameraPreview::OnBnClickedButtonVideoFileRecord)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO_RECORD, &CTabCameraPreview::OnBnClickedButtonVideoRecord)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_FRAME, &CTabCameraPreview::OnBnClickedButtonSaveFrame)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_IMAGE, &CTabCameraPreview::OnBnClickedButtonSaveImage)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_BITMAP, &CTabCameraPreview::OnBnClickedButtonSaveBitmap)
	ON_BN_CLICKED(IDC_CHECK_CAPTURE_ENABLE, &CTabCameraPreview::OnBnClickedCheckCaptureEnable)
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE, &CTabCameraPreview::OnBnClickedButtonCapture)
END_MESSAGE_MAP()


// CTabCameraPreview message handlers

/**
* @brief Open video file
*
* @return
*/
void CTabCameraPreview::OnBnClickedButtonVideoFileRecord()
{
	if (theApp.pMainDlg->pQrCamera == NULL || !theApp.pMainDlg->pQrCamera->IsConnect) return;
	CFileDialog dlg(FALSE, _T(".mp4"), nullptr, OFN_OVERWRITEPROMPT, _T("mp4 files(*.mp4)|*.mp4|avi files(*.avi)|*.avi||"), this);
	double fps = 0.0;
	if (theApp.pMainDlg->m_TabCamera.GetCurSel() == 0) {
		fps = theApp.pMainDlg->pQrCamera->FPS;
	}
	else {
		if (theApp.pMainDlg->pQrCamera->qrControl.GetVideoFPS() == TRUE) {
			fps = theApp.pMainDlg->pQrCamera->qrControl.VideoFPS();
		}
	}
	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();
		CT2CA str(filePath);
		CRect rect;
		int pos = 0;
		CString Token = filePath.Tokenize(_T("\\"), pos);
		CString fileName;
		CString ext;
		while (!Token.IsEmpty()) {
			Token = filePath.Tokenize(_T("\\"), pos);
			if (!Token.IsEmpty()) {
				fileName = Token;
			}
		}
		pos = 0;
		Token = fileName.Tokenize(_T("."), pos);
		while (!Token.IsEmpty()) {
			Token = fileName.Tokenize(_T("."), pos);
			if (!Token.IsEmpty()) {
				ext = Token;
			}
		}
		if (ext == _T("mp4")) {
			m_RadioRecordFrame.SetCheck(BST_UNCHECKED);
			m_RadioRecordImage.SetCheck(BST_CHECKED);
		}
		else {
			m_RadioRecordFrame.SetCheck(BST_CHECKED);
			m_RadioRecordImage.SetCheck(BST_UNCHECKED);
		}
		theApp.pMainDlg->m_TabCameraPreview.m_StaticFileRecord.SetWindowTextW(fileName);
		theApp.pMainDlg->m_TabCameraPreview.m_PictureBoxCameraPreview.GetClientRect(rect);
		bool ret = theApp.pMainDlg->qrVideoWriter.Create(std::string(str), fps, rect.Width(), rect.Height());
		if (ret == FALSE) {
			std::cout << "Video file create failed!" << endl;
		}
	}
}

/**
* @brief Recode video
*
* @return
*/
void CTabCameraPreview::OnBnClickedButtonVideoRecord()
{
	if (theApp.pMainDlg->pQrCamera == NULL || !theApp.pMainDlg->pQrCamera->IsConnect) return;
	if (theApp.pMainDlg->qrVideoWriter.IsOpen())
	{
		CString text;
		switch (theApp.pMainDlg->qrVideoWriter.State())
		{
		case QrSDK::QrVideoState::STOP:
			break;
		case QrSDK::QrVideoState::READY:
			m_BtnVideoRecord.GetWindowTextW(text);
			if (text.Compare(_T("Record")) == 0)
			{
				theApp.pMainDlg->qrVideoWriter.State(QrSDK::QrVideoState::RECORDING);
				m_BtnVideoRecord.SetWindowTextW(_T("Stop"));
				theApp.pMainDlg->isWriting = TRUE;
			}
			break;
		case QrSDK::QrVideoState::RECORDING:
			m_BtnVideoRecord.GetWindowTextW(text);
			if (text.Compare(_T("Stop")) == 0)
			{
				theApp.pMainDlg->isWriting = FALSE;
				theApp.pMainDlg->qrVideoWriter.Close();
				m_BtnVideoRecord.SetWindowTextW(_T("Record"));
			}
			break;
		}
	}
}

/**
* @brief Save frame
*
* @return
*/
void CTabCameraPreview::OnBnClickedButtonSaveFrame()
{
	CFileDialog dlg(FALSE, _T(".tiff"), nullptr, OFN_OVERWRITEPROMPT, _T("TIFF files(*.tiff)|*.tiff||"), this);
	if (dlg.DoModal() == IDOK)
	{
		QrSDK::QrSnapshot qrSnapshot;
		QrSDK::QrRect rect;
		rect.x = 0;
		rect.y = 0;
		rect.width = 0;
		rect.height = 0;
		CString filePath = dlg.GetPathName();
		CT2CA str(filePath);
		qrSnapshot.Save(std::string(str), theApp.pMainDlg->qrFrame, rect);
	}
}

/**
* @brief Save image
*
* @return
*/
void CTabCameraPreview::OnBnClickedButtonSaveImage()
{
	CFileDialog dlg(FALSE, _T(".png"), nullptr, OFN_OVERWRITEPROMPT, _T("PNG files(*.png)|*.png||"), this);
	if (dlg.DoModal() == IDOK)
	{
		QrSDK::QrSnapshot qrSnapshot;
		QrSDK::QrRect rect;
		rect.x = 0;
		rect.y = 0;
		rect.width = 0;
		rect.height = 0;
		CString filePath = dlg.GetPathName();
		CT2CA str(filePath);
		qrSnapshot.Save(std::string(str), theApp.pMainDlg->qrImage, rect);
	}
}

/**
* @brief Save bitmap
*
* @return
*/
void CTabCameraPreview::OnBnClickedButtonSaveBitmap()
{
	CFileDialog dlg(FALSE, _T(".bmp"), nullptr, OFN_OVERWRITEPROMPT, _T("BMP files(*.bmp)|*.bmp||"), this);
	if (dlg.DoModal() == IDOK)
	{
		QrSDK::QrSnapshot qrSnapshot;
		CString filePath = dlg.GetPathName();
		CT2CA str(filePath);

		CStatic* picBox = &theApp.pMainDlg->m_TabCameraPreview.m_PictureBoxCameraPreview;

		//DC
		//CDC* pDC = theApp.pMainDlg->m_PictureBox_Preview.GetDC();
		CDC* pDC = picBox->GetDC();
		HDC hDC = pDC->m_hDC;

		//picture control 크기
		CRect rect;
		picBox->GetClientRect(rect);

		//비트맵생성
		HDC hMemDC = CreateCompatibleDC(hDC);
		HBITMAP hBitmap = CreateCompatibleBitmap(hDC, rect.right, rect.bottom);
		HBITMAP hBmpOld = (HBITMAP)SelectObject(hMemDC, hBitmap);
		BitBlt(hMemDC, 0, 0, rect.right, rect.bottom, hDC, 0, 0, SRCCOPY);
		SelectObject(hMemDC, hBmpOld);
		DeleteDC(hMemDC);

		//비트맵사양설정
		BITMAPINFOHEADER bmih;
		ZeroMemory(&bmih, sizeof(BITMAPINFOHEADER));
		bmih.biSize = sizeof(BITMAPINFOHEADER);
		bmih.biWidth = rect.Width();
		bmih.biHeight = rect.Height();
		bmih.biPlanes = 1;
		bmih.biBitCount = 24;
		bmih.biCompression = BI_RGB;

		// 비트맵(DIB) 데이터 추출
		GetDIBits(hDC, hBitmap, 0, rect.bottom, NULL, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
		LPBYTE lpBits = new BYTE[bmih.biSizeImage];
		GetDIBits(hDC, hBitmap, 0, rect.bottom, lpBits, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
		ReleaseDC(pDC);
		DeleteObject(hBitmap);

		// 비트맵 파일 헤더 설정
		BITMAPFILEHEADER bmfh;
		bmfh.bfType = 'MB';
		bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmih.biSizeImage;
		bmfh.bfReserved1 = 0;
		bmfh.bfReserved2 = 0;
		bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

		_bstr_t gg(filePath);
		BSTR lpszFileName = gg.copy();

		// 비트맵 파일 생성 및 데이터 저장
		DWORD dwWritten;
		HANDLE hFile = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(hFile, &bmfh, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
		WriteFile(hFile, &bmih, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
		WriteFile(hFile, lpBits, bmih.biSizeImage, &dwWritten, NULL);
		CloseHandle(hFile);

		//QrSDK::QrSize size;
		//size.width = rect.Width();
		//size.height = rect.Height();
		//qrSnapshot.Save(std::string(str), (uint8_t * )(lpBits), size);

		delete[] lpBits;
	}
}

/**
* @brief Check capture mode
*
* @return
*/
void CTabCameraPreview::OnBnClickedCheckCaptureEnable()
{
	if (IsDlgButtonChecked(IDC_CHECK_CAPTURE_ENABLE) == 1)
	{
		m_BtnCapture.EnableWindow(TRUE);
	}
	else
	{
		m_BtnCapture.EnableWindow(FALSE);
	}
}

/**
* @brief Capture a frame
*
* @return
*/
void CTabCameraPreview::OnBnClickedButtonCapture()
{
	CRect rect;
	CStatic* picBox = &theApp.pMainDlg->m_TabCameraPreview.m_PictureBoxCameraPreview;
	picBox->GetClientRect(rect);
	CDC* dc = picBox->GetDC();
	theApp.pMainDlg->pQrCamera->Resize(rect.Width(), rect.Height());

	if (theApp.pMainDlg->pQrCamera->IsConnect)
	{
		if (theApp.pMainDlg->pQrCamera->Capture(theApp.pMainDlg->qrFrame) && !theApp.pMainDlg->qrFrame.IsEmpty())
		{
			if (theApp.pMainDlg->qrFrame.QueryImage(theApp.pMainDlg->qrImage))
			{
				CImage image;
				image.Create(theApp.pMainDlg->qrImage.Width, theApp.pMainDlg->qrImage.Height, 24);

				// Draw bitmap
				SetBitmapBits(image, theApp.pMainDlg->qrImage.Width * theApp.pMainDlg->qrImage.Height * 3, theApp.pMainDlg->qrImage.ToBitmapData());
				image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
			}
		}
	}
}
