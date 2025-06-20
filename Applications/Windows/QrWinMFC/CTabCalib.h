#pragma once


// CTabCalib dialog

class CTabCalib : public CDialogEx
{
	DECLARE_DYNAMIC(CTabCalib)

public:
	CTabCalib(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabCalib();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_CALIB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpenCalib();
	afx_msg void OnBnClickedButtonUpdateParams();
	CEdit m_EditObjEmissivity;
	CEdit m_EditReflTemp;
	CEdit m_EditDistance;
	CEdit m_EditAtmTemp;
	CEdit m_EditHumidity;
	CEdit m_EditAtmTrans;
	CEdit m_EditLensTemp;
	CEdit m_EditLensTrans;
	CButton m_radioHighGain;
	CButton m_radioLowGain;
};
