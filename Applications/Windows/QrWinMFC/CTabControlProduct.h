#pragma once


// CTabControlProduct dialog

class CTabControlProduct : public CDialogEx
{
	DECLARE_DYNAMIC(CTabControlProduct)

public:
	CTabControlProduct(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabControlProduct();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_CONTROL_PRODUCT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonGetProductInfo();
	afx_msg void OnBnClickedButtonGetVersionInfo();
	afx_msg void OnBnClickedButtonGetSystemInfo();
	afx_msg void OnBnClickedButtonGetProductSerial();
	afx_msg void OnBnClickedButtonGetSensorSerial();
	afx_msg void OnBnClickedButtonGetGainMode();
	afx_msg void OnBnClickedButtonSetGainMode();
	afx_msg void OnBnClickedButtonSetRefGain();
	afx_msg void OnBnClickedButtonSetRefOffset();
	afx_msg void OnBnClickedButtonSetTempCoeff1();
	afx_msg void OnBnClickedButtonSetTempCoeff2();
	afx_msg void OnBnClickedButtonGetTempInfo();
	CComboBox m_ComboProtocol;
	CButton m_BtnGetProductVersion;
	CButton m_BtnGetHwVersion;
	CButton m_BtnGetSwVersion;
	CButton m_BtnGetBuildDate;
	CButton m_BtnGetBuildTime;
	CButton m_BtnGetRefGain;
	CButton m_BtnGetRefOffset;
	CButton m_GetTempCoeff1;
	CButton m_GetTempCoeff2;
	afx_msg void OnBnClickedButtonGetModel();
	afx_msg void OnBnClickedButtonGetVersion();
	afx_msg void OnBnClickedButtonGetHwVersion();
	afx_msg void OnBnClickedButtonGetSwVersion();
	afx_msg void OnBnClickedButtonGetBuildDate();
	afx_msg void OnBnClickedButtonGetBuildTime();
	afx_msg void OnBnClickedButtonGetRefGain();
	afx_msg void OnBnClickedButtonGetRefOffset();
	afx_msg void OnBnClickedButtonGetTempCoeff1();
	afx_msg void OnBnClickedButtonGetTempCoeff2();
	afx_msg void OnEnChangeEditModel();
	CEdit m_EditModel;
	afx_msg void OnBnClickedButtonGetFpaTemp();
	afx_msg void OnBnClickedButtonGetBodyTemp();
	CButton m_BtnGetProductInfo;
	CButton m_BtnGetGainMode;
	CButton m_BtnGetVersionInfo;
	CButton m_BtnGetTempInfo;
	afx_msg void OnBnClickedButtonGetWhiteBlackHot();
	afx_msg void OnBnClickedButtonGetAutoShutter();
	afx_msg void OnBnClickedButtonGetUsecase();
	afx_msg void OnBnClickedButtonGetDisplay();
	afx_msg void OnBnClickedButtonSetHotWhiteBlack();
	afx_msg void OnBnClickedButtonSetAutoShutter();
	CButton m_RadioHotWhite;
	CButton m_RadioHotBlack;
	CButton m_RadioAutoShutterEnable;
	CButton m_RadioAutoShutterDisable;
	afx_msg void OnBnClickedButtonGetPrintstatics();
	CButton m_BtnGetWhiteBlackHot;
	afx_msg void OnBnClickedButtonGetSystemSetting();
	CButton m_BtnGetSystemSetting;
	CButton m_BtnGetFpaTemp;
	CButton m_BtnGetBodyTemp;
	CButton m_BtnSetWhiteBlackHot;
	CButton m_BtnSetGainMode;
	afx_msg void OnBnClickedButtonSetTempConvert();
	afx_msg void OnBnClickedButtonGetProductVersion();
	afx_msg void OnBnClickedButtonGetAutoshutter();
	afx_msg void OnBnClickedButtonSetAutoshutter();
	afx_msg void OnBnClickedButtonSetShutterControl();
	afx_msg void OnBnClickedButtonSetSystemReboot();
	afx_msg void OnBnClickedButtonSet1pNuc();
	afx_msg void OnBnClickedButtonSetViewMode();
	afx_msg void OnBnClickedButtonSetTec();
	afx_msg void OnBnClickedButtonSetDpc();
	afx_msg void OnBnClickedButtonSet2ndComp();
	afx_msg void OnBnClickedButtonSetShutterComp();
	afx_msg void OnBnClickedButtonSetImageOut();
	CComboBox m_ComboViewMode;
};
