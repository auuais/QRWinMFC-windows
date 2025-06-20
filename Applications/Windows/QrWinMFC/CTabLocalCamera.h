#pragma once
#include "CTabControlProduct.h"
#include "CTabCameraPreview.h"
#include "CTabCalib.h"

#define WM_QRFRAME_EVENT  (WM_APP + 200)

// CTabLocalCamera dialog
class CTabLocalCamera : public CDialogEx
{
	DECLARE_DYNAMIC(CTabLocalCamera)

public:
	CTabLocalCamera(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabLocalCamera();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_LOCALCAMERA };
#endif
	static UINT WINAPI FrameProcessingThread(LPVOID pParam);

	struct ThreadParam {
		QrSDK::QrFramePtr frame;
		CTabLocalCamera* pThis;
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg LRESULT OnMessageEventHandler(WPARAM wParam, LPARAM lParam);
	
	void OnFrameEventHandler(QrSDK::QrFramePtr frame);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLocalConnect();
	CButton m_BtnLocalConnect;
	CComboBox m_CbLocalCamList;
	afx_msg void OnIddTabLocalcamera();
	afx_msg void OnUpdateIddTabLocalcamera(CCmdUI* pCmdUI);
	//CComboBox m_CbLocalSerialPorts;

	CTabControlProduct* m_pTabProduct;
	CTabCalib* m_pTabCalib;

	void SetTabProductPtr(CTabControlProduct* pTab);
	void SetTabCalibPtr(CTabCalib* pTab);

	CTabCameraPreview m_TabCameraPreview;
	CEdit m_EditAcquisitionCount;
	CButton m_BtnBeginAcquisition;
	CButton m_BtnEndAcquisition;
	afx_msg void OnBnClickedButtonBeginAcquisition();
	afx_msg void OnBnClickedButtonEndAcquisition();
	afx_msg void OnBnClickedRadioTriggermodeOn();
	afx_msg void OnBnClickedButtonSwTrigger();
	afx_msg void OnBnClickedRadioTriggermodeOff();
	CButton m_BtnSwTrigger;
	CButton m_RadioTriggerModeOn;
	CButton m_RadioTriggerModeOff;
	CEdit m_EditCameraPosition;
	CButton m_BtnGetCameraPosition;
	CButton m_BtnSetCameraPosition;
	CButton m_RadioCameraPositionLeft;
	CButton m_RadioCameraPositionRight;
	afx_msg void OnBnClickedButtonGetCameraPosition();
	afx_msg void OnBnClickedButtonSetCameraPosition();
	CButton m_RadioCameraPositionUnknown;
};
