
// QrWinMFCDlg.h : header file
//

#pragma once

#include <libQrCore.hpp>
#include <libQrComponent.hpp>

#include "CTabLocalCamera.h"
#include "CTabRemoteCamera.h"

#include "CTabControlProduct.h"
#include "CTabControlSystem.h"

#include "CTabFeatureCalib.h"
#include "CTabRoi.h"
#include "CTabImage.h"
#include "CTabCalib.h"
#include "CTabCameraPreview.h"
#include "CTabVideoPreview.h"

#include <QrVideoWriter.hxx>
#include <QrVideoReader.hxx>
#include <QrLogger.hxx>
// CQrWinMFCDlg dialog
class CQrWinMFCDlg : public CDialogEx
{
// Construction
public:
	CQrWinMFCDlg(CWnd* pParent = nullptr);	// standard constructor
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD_PTR dwData);
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QrWinMFC_DIALOG };
#endif

	QrSDK::QrCamera* pQrCamera = nullptr;
	QrSDK::QrFrame qrFrame;
	QrSDK::QrImage qrImage;
	QrSDK::QrLogger qrLogger;
	QrSDK::QrVideoWriter qrVideoWriter;
	QrSDK::QrVideoReader qrVideoReader;
	QrSDK::QrColorMap colormap = QrSDK::QrColorMap::COLORMAP_NONE;
	QrSDK::QrCEM cem = QrSDK::QrCEM::CEM_NONE;
	double cem_linear_gain = 1.0;
	double cem_linear_offset = 0.0;

	HANDLE m_hThread = NULL;
	HANDLE m_hVideoThread = NULL;
	static UINT FrameWorker(LPVOID param);
	static UINT ReadVideoWorker(LPVOID param);

	bool isWriting = FALSE;
	std::vector<QrSDK::tCamDev> camList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	HDEVNOTIFY m_hDevNotify = nullptr;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabCamera;
	CTabLocalCamera m_TabLocalCamera;
	CTabRemoteCamera m_TabRemoteCamera;
	afx_msg void OnTcnSelchangeTabCamera(NMHDR* pNMHDR, LRESULT* pResult);
	CTabCtrl m_TabControl;
	CTabControlProduct m_TabControlProduct;
	CTabControlSystem m_TabControlSystem;
	CTabCtrl m_TabFeature;
	CTabRoi m_TabRoi;
	CTabImage m_TabImage;
	CTabCalib m_TabCalib;
	CTabFeatureCalib m_TabFeatureCalib;
	afx_msg void OnTcnSelchangeTabFeature(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTcnSelchangeTabControl(NMHDR* pNMHDR, LRESULT* pResult);
	CStatic m_PictureBox_Preview;

	CTabCtrl m_TabPreview;
	afx_msg void OnSelchangeTabPreview(NMHDR* pNMHDR, LRESULT* pResult);
	CTabVideoPreview m_TabVideoPreview;
	CTabCameraPreview m_TabCameraPreview;
	CStatic m_Static_RawMax;
	CStatic m_Static_TempMax;
	CStatic m_Static_RawAvg;
	CStatic m_Static_TempAvg;
	CStatic m_Static_RawMin;
	CStatic m_Static_TempMin;
	CComboBox m_ComboBox_TempUnit;
	afx_msg void OnCbnSelchangeComboTempunit();
};
