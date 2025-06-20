// CTabImage.cpp : implementation file
//

#include "pch.h"
#include "QrWinMFC.h"
#include "CTabImage.h"
#include "afxdialogex.h"

// CTabImage dialog

IMPLEMENT_DYNAMIC(CTabImage, CDialogEx)

CTabImage::CTabImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_IMAGE, pParent)
{
}


CTabImage::~CTabImage()
{
}


void CTabImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COLOR_MAP, m_ComboColorMap);
	DDX_Control(pDX, IDC_COMBO_CEM, m_ComboCem);
	DDX_Control(pDX, IDC_EDIT_LINEAR_GAIN, m_EditLinearGain);
	DDX_Control(pDX, IDC_EDIT_LINEAR_OFFSET, m_EditLinearOffset);
	DDX_Control(pDX, IDC_BUTTON_SET_LINEAR, m_BtnSetLinear);
}


BEGIN_MESSAGE_MAP(CTabImage, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_COLOR_MAP, &CTabImage::OnCbnSelchangeComboColorMap)
	ON_CBN_SELCHANGE(IDC_COMBO_CEM, &CTabImage::OnCbnSelchangeComboCem)
	ON_BN_CLICKED(IDC_BUTTON_SET_LINEAR, &CTabImage::OnBnClickedButtonSetLinear)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO_FILE_RECORD, &CTabImage::OnBnClickedButtonVideoFileRecord)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO_FILE_OPEN, &CTabImage::OnBnClickedButtonVideoFileOpen)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO_RECORD, &CTabImage::OnBnClickedButtonVideoRecord)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO_PLAY, &CTabImage::OnBnClickedButtonVideoPlay)
END_MESSAGE_MAP()


/**
* @brief Select color map
*
* @return
*/
void CTabImage::OnCbnSelchangeComboColorMap()
{
	if (m_ComboColorMap.GetCurSel() >= 0)
	{
		theApp.pMainDlg->colormap = (QrSDK::QrColorMap)(m_ComboColorMap.GetCurSel() - 1);
	}
}

/**
* @brief Select CEM
*
* @return
*/
void CTabImage::OnCbnSelchangeComboCem()
{
	if (m_ComboCem.GetCurSel() >= 0)
	{
		theApp.pMainDlg->cem = (QrSDK::QrCEM)(m_ComboCem.GetCurSel());
	}

	if (m_ComboCem.GetCurSel() == (QrSDK::QrCEM::CEM_LINEAR)) {
		m_EditLinearGain.EnableWindow(TRUE);
		m_EditLinearOffset.EnableWindow(TRUE);
		m_BtnSetLinear.EnableWindow(TRUE);
	}
	else {
		m_EditLinearGain.EnableWindow(FALSE);
		m_EditLinearOffset.EnableWindow(FALSE);
		m_BtnSetLinear.EnableWindow(FALSE);
	}
}

/**
* @brief Set linear
*
* @return
*/
void CTabImage::OnBnClickedButtonSetLinear()
{
	theApp.pMainDlg->cem = QrSDK::QrCEM::CEM_LINEAR;
	CString strGain, strOffset;
	m_EditLinearGain.GetWindowTextW(strGain);
	m_EditLinearOffset.GetWindowTextW(strOffset);

	theApp.pMainDlg->cem_linear_gain = _tcstod(strGain, NULL);
	theApp.pMainDlg->cem_linear_offset = _tcstod(strOffset, NULL);
}

/**
* @brief Create video file
*
* @return
*/
void CTabImage::OnBnClickedButtonVideoFileRecord()
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
		CStringArray arrToken;
		int index;
		CString Token = filePath.Tokenize(_T("/"), index);
		std::cout << "index = " << index << endl;
		while (!Token.IsEmpty()) {
			Token = filePath.Tokenize(_T("/"), index);
			std::cout << "index = " << index << " - "<<Token << endl;
		}
		theApp.pMainDlg->m_TabCameraPreview.m_StaticFileRecord.SetWindowTextW(_T("--"));
		theApp.pMainDlg->m_TabCameraPreview.m_PictureBoxCameraPreview.GetClientRect(rect);
		bool ret = theApp.pMainDlg->qrVideoWriter.Create(std::string(str), fps, rect.Width(), rect.Height());
		if (ret == FALSE) {
			std::cout << "Video file create failed!" << endl;
		}
	}
}

/**
* @brief Open video file
*
* @return
*/
void CTabImage::OnBnClickedButtonVideoFileOpen()
{
	if (theApp.pMainDlg->pQrCamera == NULL || !theApp.pMainDlg->pQrCamera->IsConnect) return;
	CFileDialog dlg(TRUE, _T(".mp4"), nullptr, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("mp4 files(*.mp4)|*.mp4|avi files(*.avi)|*.avi||"), this);
	double fps;

	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();
		CT2CA str(filePath);
		bool ret = theApp.pMainDlg->qrVideoReader.Open(std::string(str));
		if (ret == FALSE) {
			std::cout << "Video file open failed!" << endl;
		}
		else {
			std::cout << "Video file open " << endl;
		}
	}
}

/**
* @brief Record video
*
* @return
*/
void CTabImage::OnBnClickedButtonVideoRecord()
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
* @brief Play video
*
* @return
*/
void CTabImage::OnBnClickedButtonVideoPlay()
{
	CString text;
	std::cout << theApp.pMainDlg->qrVideoReader.State() << endl;
	switch (theApp.pMainDlg->qrVideoReader.State())
	{
	case QrSDK::QrVideoState::STOP:
		break;
	case QrSDK::QrVideoState::READY:
		m_BtnBideoPlay.GetWindowTextW(text);
			
		if (text.Compare(_T("Play")) == 0)
		{
			theApp.pMainDlg->qrVideoReader.State(QrSDK::QrVideoState::PLAYING);
			theApp.pMainDlg->m_hVideoThread = AfxBeginThread(CQrWinMFCDlg::ReadVideoWorker, theApp.pMainDlg);
			m_BtnBideoPlay.SetWindowTextW(_T("Stop"));
		}
		break;
	case QrSDK::QrVideoState::PLAYING:
		m_BtnBideoPlay.GetWindowTextW(text);
		if (text.Compare(_T("Stop")) == 0)
		{
			theApp.pMainDlg->qrVideoReader.State(QrSDK::QrVideoState::STOP);
			theApp.pMainDlg->qrVideoReader.Close();
			m_BtnBideoPlay.SetWindowTextW(_T("Play"));
		}
		break;
	}
}

/**
* @brief Play video thread
*
* @return
*/
UINT CQrWinMFCDlg::ReadVideoWorker(LPVOID param)
{
	CQrWinMFCDlg* pDlg = (CQrWinMFCDlg*)param;
	CStatic* picBox = &pDlg->m_TabVideoPreview.m_PictureBoxVideoPreview;

	int fps = pDlg->qrVideoReader.FPS;
	int nFrames = pDlg->qrVideoReader.Frames;
	int nFramePos = 1;
	
	CString totFrames;
	totFrames.Format(_T("%d"), pDlg->qrVideoReader.Frames);
	pDlg->m_TabVideoPreview.m_StaticVideoTotalFrame.SetWindowTextW(totFrames);

	while (theApp.pMainDlg->qrVideoReader.State() == QrSDK::QrVideoState::PLAYING)
	{
		QrSDK::QrFrame qrFrame;
		QrSDK::QrImage qrImage;
		{
			try
			{
				if (pDlg->qrVideoReader.Read(&qrFrame))
				{
					if (qrFrame.QueryImage(qrImage))
					{
						CImage image;
						CRect rect;
						CDC* dc = picBox->GetDC();
						picBox->GetClientRect(rect);
						image.Create(qrImage.Width, qrImage.Height, 24);

						// Draw bitmap
						SetBitmapBits(image, qrImage.Width * qrImage.Height * 3, qrImage.ToBitmapData());

						image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);


						CString framePos;
						framePos.Format(_T("%d"), nFramePos);
						pDlg->m_TabVideoPreview.m_StaticVideoFramePos.SetWindowTextW(framePos);
						pDlg->m_TabVideoPreview.m_ProgressVideoRead.SetPos((int)(((double)nFramePos / (double)nFrames) * 100));
						
					}
					Sleep((int)(1000 / fps * 0.5));
					nFramePos++;

				}
				else
				{
					pDlg->qrVideoReader.State(QrSDK::QrVideoState::STOP);
					pDlg->qrVideoReader.Close();
					pDlg->m_TabVideoPreview.m_BtnVideoPlay.SetWindowTextW(_T("Play"));
				}
			}
			catch (QrSDK::QrException e)
			{
				std::cout << e.what() << endl;
			}

		}
	}
	//pictureBox_Preview.Image = null;

	return 0;
}
