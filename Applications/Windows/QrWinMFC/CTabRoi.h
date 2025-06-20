#pragma once
#include <libQrCore.hpp>
#include <libQrComponent.hpp>

// CTabRoi dialog

class CTabRoi : public CDialogEx
{
	DECLARE_DYNAMIC(CTabRoi)

public:
	CTabRoi(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabRoi();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_ROI };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonClearRoi();
	afx_msg void OnBnClickedButtonAddRoi();
	afx_msg void OnBnClickedButtonRemoveRoi();
	afx_msg void OnBnClickedButtonSaveRoiFrame();
	afx_msg void OnBnClickedButtonSaveRoiImage();
	afx_msg void OnBnClickedButtonOpenLogFile();
	afx_msg void OnBnClickedButtonLogItem();
	CEdit m_EditStrRoiX;
	CEdit m_EditStrRoiY;
	CEdit m_EditStrRoiW;
	CEdit m_EditStrRoiH;
	CComboBox m_ComboRoiList;
};
