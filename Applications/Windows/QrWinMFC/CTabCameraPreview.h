#pragma once


// CTabCameraPreview dialog

class CTabCameraPreview : public CDialogEx
{
	DECLARE_DYNAMIC(CTabCameraPreview)

public:
	CTabCameraPreview(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabCameraPreview();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_CAMERA_PREVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_PictureBoxCameraPreview;
	CStatic m_StaticFileRecord;
	afx_msg void OnBnClickedButtonVideoFileRecord();
	afx_msg void OnBnClickedButtonVideoRecord();
	afx_msg void OnBnClickedButtonSaveFrame();
	afx_msg void OnBnClickedButtonSaveImage();
	afx_msg void OnBnClickedButtonSaveBitmap();
	CButton m_BtnVideoRecord;
	CButton m_RadioRecordFrame;
	CButton m_RadioRecordImage;
	CButton m_BtnCapture;
	afx_msg void OnBnClickedCheckCaptureEnable();
	afx_msg void OnBnClickedButtonCapture();
	CButton m_CheckCaptureEnable;
};
