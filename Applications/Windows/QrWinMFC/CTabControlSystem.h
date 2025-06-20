#pragma once


// CTabControlSystem dialog

class CTabControlSystem : public CDialogEx
{
	DECLARE_DYNAMIC(CTabControlSystem)

public:
	CTabControlSystem(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabControlSystem();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_CONTROL_SYSTEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonGetVideoResolution();
	afx_msg void OnBnClickedButtonGetVideoFps();
	afx_msg void OnBnClickedButtonGetVideoFormat();
	afx_msg void OnBnClickedButtonGetMacAddress();
	afx_msg void OnBnClickedButtonGetIpMode();
	afx_msg void OnBnClickedButtonSetIpMode();
	CComboBox m_CbIpMode;
	afx_msg void OnBnClickedButtonGetIpAddress();
	afx_msg void OnBnClickedButtonSetIpAddress();
	CIPAddressCtrl m_IpAddress;
	CIPAddressCtrl m_GatewayAddress;
	CIPAddressCtrl m_SubnetMask;
	CIPAddressCtrl m_DnsAddress;
	afx_msg void OnBnClickedButtonGetGatewayAddress();
	afx_msg void OnBnClickedButtonSetGatewayAddress();
	afx_msg void OnBnClickedButtonGetSubnetmask();
	afx_msg void OnBnClickedButtonSetSubnetmask();
	afx_msg void OnBnClickedButtonGetSubnetmask2();
	afx_msg void OnBnClickedButtonSetSubnetmask2();
	afx_msg void OnBnClickedButtonGetDnsAddress();
	afx_msg void OnBnClickedButtonSetDnsAddress();
	afx_msg void OnBnClickedButtonSetTempPrint();
	afx_msg void OnBnClickedButtonSetTrsmGuideTo();
	CComboBox m_CbTrsmGuideTo;
	afx_msg void OnBnClickedButtonSetTrsmSave();
	afx_msg void OnBnClickedButtonSetTrsmValue();
	afx_msg void OnBnClickedButtonSetTrsmGuide();
	afx_msg void OnBnClickedButtonSetTrsmComp();
	afx_msg void OnBnClickedButtonSetTempConvert();
	afx_msg void OnBnClickedButtonSet1pNuc();
	afx_msg void OnBnClickedButtonSetAlarmNuc();
	afx_msg void OnBnClickedButtonSetShutterTime();
	afx_msg void OnBnClickedButtonSetAutoshutter();
	afx_msg void OnBnClickedButtonGetAutoshutter();
	CButton m_BtnGetAutoShtter;
	afx_msg void OnBnClickedButtonSetTrsmRefTemp();
	afx_msg void OnBnClickedButtonSetNetworkReboot();
};
