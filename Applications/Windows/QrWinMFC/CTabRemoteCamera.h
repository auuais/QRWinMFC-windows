#pragma once

#include <libQrCore.hpp>

class CTabRemoteCamera : public CDialogEx
{
	DECLARE_DYNAMIC(CTabRemoteCamera)

public:
	CTabRemoteCamera(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabRemoteCamera();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_REMOTECAMERA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRemoteConnect();
	CButton m_BtnRemoteConnect;
	CIPAddressCtrl m_RemoteAddress;
	afx_msg void OnIpnFieldchangedIpaddress(NMHDR* pNMHDR, LRESULT* pResult);
};
