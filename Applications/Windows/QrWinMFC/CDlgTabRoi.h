#pragma once


// CDlgTabRoi dialog

class CDlgTabRoi : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTabRoi)

public:
	CDlgTabRoi(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgTabRoi();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_ROI };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
