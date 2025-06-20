#pragma once


// CTabImage dialog

class CTabImage : public CDialogEx
{
	DECLARE_DYNAMIC(CTabImage)

public:
	CTabImage(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabImage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_IMAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditLinearOffset();
	afx_msg void OnEnChangeEditLinearGain();
	afx_msg void OnCbnSelchangeComboColorMap();
	afx_msg void OnCbnSelchangeComboCem();
	afx_msg void OnBnClickedButtonSetLinear();
	afx_msg void OnBnClickedButtonVideoFileRecord();
	afx_msg void OnBnClickedButtonVideoFileOpen();
	afx_msg void OnBnClickedButtonVideoRecord();
	afx_msg void OnBnClickedButtonVideoPlay();
	void CTabImage::InitializeComboBox();
	CComboBox m_ComboColorMap;
	CComboBox m_ComboCem;
	CEdit m_EditLinearGain;
	CEdit m_EditLinearOffset;
	CButton m_BtnVideoRecord;
	CButton m_BtnBideoPlay;
	CButton m_BtnSetLinear;
};
