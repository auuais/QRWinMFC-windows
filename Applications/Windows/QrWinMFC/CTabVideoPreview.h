#pragma once


// CTabVideoPreview dialog

class CTabVideoPreview : public CDialogEx
{
	DECLARE_DYNAMIC(CTabVideoPreview)

public:
	CTabVideoPreview(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabVideoPreview();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_VIDEO_PREVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_PictureBoxVideoPreview;
	afx_msg void OnStnClickedStaticFileVideo();
	CStatic m_StaticFileVideo;
	CStatic m_StaticVideoInfo;
	afx_msg void OnBnClickedButtonVideoFileOpen();
	afx_msg void OnBnClickedButtonVideoPlay();
	afx_msg void OnBnClickedButtonLoadFrame();
	afx_msg void OnBnClickedButtonLoadImage();
	CButton m_BtnVideoPlay;
	CProgressCtrl m_ProgressVideoRead;
	CStatic m_StaticVideoFramePos;
	CStatic m_StaticVideoTotalFrame;
	afx_msg void OnBnClickedButtonLoadBitmap();
};
