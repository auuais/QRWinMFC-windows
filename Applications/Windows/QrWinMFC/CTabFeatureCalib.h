#pragma once


// CTabFeatureCalib dialog

class CTabFeatureCalib : public CDialogEx
{
	DECLARE_DYNAMIC(CTabFeatureCalib)

public:
	CTabFeatureCalib(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabFeatureCalib();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_FEATURE_CALIB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
