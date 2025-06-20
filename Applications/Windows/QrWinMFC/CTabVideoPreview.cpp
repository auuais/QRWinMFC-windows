// CTabVideoPreview.cpp : implementation file
//

#include "pch.h"
#include "QrWinMFC.h"
#include "CTabVideoPreview.h"
#include "afxdialogex.h"


// CTabVideoPreview dialog

IMPLEMENT_DYNAMIC(CTabVideoPreview, CDialogEx)

CTabVideoPreview::CTabVideoPreview(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_VIDEO_PREVIEW, pParent)
{

}

CTabVideoPreview::~CTabVideoPreview()
{
}

void CTabVideoPreview::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTUREBOX_VIDEO, m_PictureBoxVideoPreview);
	DDX_Control(pDX, IDC_STATIC_FILE_VIDEO, m_StaticFileVideo);
	DDX_Control(pDX, IDC_STATIC_VIDEO_INFO, m_StaticVideoInfo);
	DDX_Control(pDX, IDC_BUTTON_VIDEO_PLAY, m_BtnVideoPlay);
	DDX_Control(pDX, IDC_PROGRESS_VIDEO_READ, m_ProgressVideoRead);
	DDX_Control(pDX, IDC_STATIC_VIDEO_FRAME_POS, m_StaticVideoFramePos);
	DDX_Control(pDX, IDC_STATIC_VIDEO_TOTAL_FRAMES, m_StaticVideoTotalFrame);
}


BEGIN_MESSAGE_MAP(CTabVideoPreview, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO_FILE_OPEN, &CTabVideoPreview::OnBnClickedButtonVideoFileOpen)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO_PLAY, &CTabVideoPreview::OnBnClickedButtonVideoPlay)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_FRAME, &CTabVideoPreview::OnBnClickedButtonLoadFrame)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_IMAGE, &CTabVideoPreview::OnBnClickedButtonLoadImage)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_BITMAP, &CTabVideoPreview::OnBnClickedButtonLoadBitmap)
END_MESSAGE_MAP()


// CTabVideoPreview message handlers


/**
* @brief Open video file
*
* @return
*/
void CTabVideoPreview::OnBnClickedButtonVideoFileOpen()
{
	if (theApp.pMainDlg->pQrCamera == NULL || !theApp.pMainDlg->pQrCamera->IsConnect) return;
	CFileDialog dlg(TRUE, _T(".mp4"), nullptr, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("mp4 files(*.mp4)|*.mp4|avi files(*.avi)|*.avi||"), this);
	double fps;

	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();
		CT2CA str(filePath);
		bool ret = theApp.pMainDlg->qrVideoReader.Open(std::string(str));
		int pos = 0;
		CString Token = filePath.Tokenize(_T("\\"), pos);
		CString fileName;
		while (!Token.IsEmpty()) {
			Token = filePath.Tokenize(_T("\\"), pos);
			if (!Token.IsEmpty())
				fileName = Token;
		}
		
		if (ret == FALSE) {
			std::cout << "Video file open failed!" << endl;
		}
		else {
			std::cout << "Video file open " << endl;
			theApp.pMainDlg->m_TabVideoPreview.m_StaticFileVideo.SetWindowTextW(fileName);
			CString videoInfo;
			int fps = theApp.pMainDlg->qrVideoReader.FPS;
			videoInfo.Format(_T("%dx%d@%d"), theApp.pMainDlg->qrVideoReader.Width, theApp.pMainDlg->qrVideoReader.Height, fps);
			theApp.pMainDlg->m_TabVideoPreview.m_StaticVideoInfo.SetWindowTextW(videoInfo);
		}
	}
}

/**
* @brief Play video
*
* @return
*/
void CTabVideoPreview::OnBnClickedButtonVideoPlay()
{
	CString text;
	switch (theApp.pMainDlg->qrVideoReader.State())
	{
	case QrSDK::QrVideoState::STOP:
		break;
	case QrSDK::QrVideoState::READY:
		m_BtnVideoPlay.GetWindowTextW(text);

		if (text.Compare(_T("Play")) == 0)
		{
			theApp.pMainDlg->qrVideoReader.State(QrSDK::QrVideoState::PLAYING);
			theApp.pMainDlg->m_hVideoThread = AfxBeginThread(CQrWinMFCDlg::ReadVideoWorker, theApp.pMainDlg);
			m_BtnVideoPlay.SetWindowTextW(_T("Stop"));
		}
		break;
	case QrSDK::QrVideoState::PLAYING:
		m_BtnVideoPlay.GetWindowTextW(text);
		if (text.Compare(_T("Stop")) == 0)
		{
			theApp.pMainDlg->qrVideoReader.State(QrSDK::QrVideoState::STOP);
			theApp.pMainDlg->qrVideoReader.Close();
			m_BtnVideoPlay.SetWindowTextW(_T("Play"));
		}
		break;
	}
}

/**
* @brief Load frame
*
* @return
*/
void CTabVideoPreview::OnBnClickedButtonLoadFrame()
{
	CFileDialog dlg(TRUE, _T(".tiff"), nullptr, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("TIFF files(*.tiff)|*.tiff||"), this);
	if (dlg.DoModal() == IDOK)
	{
		CStatic* picBox = &theApp.pMainDlg->m_TabVideoPreview.m_PictureBoxVideoPreview;
		QrSDK::QrSnapshot qrSnapshot;
		CString filePath = dlg.GetPathName();
		CT2CA str(filePath);
		QrSDK::QrFrame frame;
		QrSDK::QrImage image;
		if (qrSnapshot.Load(std::string(str), &frame) == TRUE) {
			frame.QueryImage(image);

			CRect rect;
			CImage ci;
			picBox->GetClientRect(rect);
			CDC* dc = picBox->GetDC();
			ci.Create(image.Width, image.Height, 24);

			// Draw bitmap
			SetBitmapBits(ci, image.Width * image.Height * 3, image.ToBitmapData());

			//ci.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
			ci.StretchBlt(dc->m_hDC, 0, 0, image.Width, image.Height, SRCCOPY);
		}
		else {
			std::cout << "Load Frame Failed!" << endl;
		}

	}
}

/**
* @brief Load image
*
* @return
*/
void CTabVideoPreview::OnBnClickedButtonLoadImage()
{
	CFileDialog dlg(TRUE, _T(".tiff"), nullptr, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("PNG files(*.png)|*.png||"), this);
	if (dlg.DoModal() == IDOK)
	{
		CStatic* picBox = &theApp.pMainDlg->m_TabVideoPreview.m_PictureBoxVideoPreview;
		QrSDK::QrSnapshot qrSnapshot;
		CString filePath = dlg.GetPathName();
		CT2CA str(filePath);
		QrSDK::QrImage image;
		if (qrSnapshot.Load(std::string(str), &image) == TRUE) {
			CRect rect;
			CImage ci;
			picBox->GetClientRect(rect);
			CDC* dc = picBox->GetDC();
			ci.Create(image.Width, image.Height, 24);

			// Draw bitmap
			SetBitmapBits(ci, image.Width * image.Height * 3, image.ToBitmapData());

			//ci.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
			ci.StretchBlt(dc->m_hDC, 0, 0, image.Width, image.Height, SRCCOPY);
		}
		else {
			std::cout << "Load Image Failed!" << endl;
		}

	}
}


void CTabVideoPreview::OnBnClickedButtonLoadBitmap()
{
	CFileDialog dlg(TRUE, _T(".bmp"), nullptr, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("BMP files(*.bmp)|*.bmp||"), this);
	if (dlg.DoModal() == IDOK)
	{
		CStatic* picBox = &theApp.pMainDlg->m_TabVideoPreview.m_PictureBoxVideoPreview;
		QrSDK::QrSnapshot qrSnapshot;
		CString filePath = dlg.GetPathName();
		CT2CA str(filePath);
		QrSDK::QrImage image;
		if (qrSnapshot.Load(std::string(str), &image) == TRUE) {
			CRect rect;
			CImage ci;
			picBox->GetClientRect(rect);
			CDC* dc = picBox->GetDC();
			ci.Create(image.Width, image.Height, 24);

			// Draw bitmap
			SetBitmapBits(ci, image.Width * image.Height * 3, image.ToBitmapData());

			//ci.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
			ci.StretchBlt(dc->m_hDC, 0, 0, image.Width, image.Height, SRCCOPY);
		}
		else {
			std::cout << "Load Image Failed!" << endl;
		}

	}
}
