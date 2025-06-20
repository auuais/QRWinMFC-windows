// CTabRoi.cpp : implementation file
//

#include "pch.h"
#include "QrWinMFC.h"
#include "CTabRoi.h"
#include "afxdialogex.h"


// CTabRoi dialog

IMPLEMENT_DYNAMIC(CTabRoi, CDialogEx)

CTabRoi::CTabRoi(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_ROI, pParent)
{
	
}

CTabRoi::~CTabRoi()
{
}

void CTabRoi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_STR_ROI_X, strRoiX);
	DDX_Control(pDX, IDC_STR_ROI_X, m_EditStrRoiX);
	DDX_Control(pDX, IDC_STR_ROI_Y, m_EditStrRoiY);
	DDX_Control(pDX, IDC_STR_ROI_W, m_EditStrRoiW);
	DDX_Control(pDX, IDC_STR_ROI_H, m_EditStrRoiH);
	DDX_Control(pDX, IDC_COMBO_ROI_LIST, m_ComboRoiList);
}


BEGIN_MESSAGE_MAP(CTabRoi, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_ROI, &CTabRoi::OnBnClickedButtonClearRoi)
	ON_BN_CLICKED(IDC_BUTTON_ADD_ROI, &CTabRoi::OnBnClickedButtonAddRoi)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_ROI, &CTabRoi::OnBnClickedButtonRemoveRoi)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_LOG_FILE, &CTabRoi::OnBnClickedButtonOpenLogFile)
	ON_BN_CLICKED(IDC_BUTTON_LOG_ITEM, &CTabRoi::OnBnClickedButtonLogItem)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_ROI_FRAME, &CTabRoi::OnBnClickedButtonSaveRoiFrame)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_ROI_IMAGE, &CTabRoi::OnBnClickedButtonSaveRoiImage)
END_MESSAGE_MAP()


// CTabRoi message handlers

/**
* @brief Clear ROI
*
* @return
*/
void CTabRoi::OnBnClickedButtonClearRoi()
{
	theApp.pMainDlg->pQrCamera->qrROI.Clear();
	m_ComboRoiList.ResetContent();
}

/**
* @brief Add ROI
*
* @return
*/
void CTabRoi::OnBnClickedButtonAddRoi()
{
	CString strX, strY, strW, strH;
	m_EditStrRoiX.GetWindowTextW(strX);
	m_EditStrRoiY.GetWindowTextW(strY);
	m_EditStrRoiW.GetWindowTextW(strW);
	m_EditStrRoiH.GetWindowTextW(strH);
	if (strX == "" || strY == "" || strW == "" || strH == "")
	{
		return;
	}
	int x = _ttoi(strX);
	int y = _ttoi(strY);
	int w = _ttoi(strW);
	int h = _ttoi(strH);

	QrSDK::QrRoiItem qrRoiItem;
	sprintf_s(qrRoiItem.Name, "ROI%d", m_ComboRoiList.GetCount());
	qrRoiItem.Rect.x = x;
	qrRoiItem.Rect.y = y;
	qrRoiItem.Rect.width = w;
	qrRoiItem.Rect.height = h;
	qrRoiItem.AvgTempLoc.value = 0.0;
	qrRoiItem.MaxTempLoc.value = 0.0;
	qrRoiItem.MinTempLoc.value = 0.0;
	
	CString strCombined;
	strCombined.Format(_T("ROI%d"), m_ComboRoiList.GetCount());
	theApp.pMainDlg->pQrCamera->qrROI.Add(qrRoiItem);
	m_ComboRoiList.AddString(strCombined);
	m_ComboRoiList.SetCurSel(0);
}

/**
* @brief Remove ROI
*
* @return
*/
void CTabRoi::OnBnClickedButtonRemoveRoi()
{
	theApp.pMainDlg->pQrCamera->qrROI.RemoveAt(m_ComboRoiList.GetCurSel());
	m_ComboRoiList.DeleteString(m_ComboRoiList.GetCurSel());
	m_ComboRoiList.SetCurSel(0);
}

/**
* @brief Save ROI frame
*
* @return
*/
void CTabRoi::OnBnClickedButtonSaveRoiFrame()
{
	if (m_ComboRoiList.GetCurSel() >= 0) {
		QrSDK::QrRoiItem item = theApp.pMainDlg->pQrCamera->qrROI.Get(m_ComboRoiList.GetCurSel());
		CFileDialog dlg(FALSE, _T(".tiff"), nullptr, OFN_OVERWRITEPROMPT, _T("TIFF files(*.tiff)|*.tiff||"), this);
		if (dlg.DoModal() == IDOK)
		{
			QrSDK::QrSnapshot qrSnapshot;
			CString filePath = dlg.GetPathName();
			CT2CA str(filePath);
			qrSnapshot.Save(std::string(str), theApp.pMainDlg->qrFrame, item.Rect);
		}
	}
}

/**
* @brief Save ROI image
*
* @return
*/
void CTabRoi::OnBnClickedButtonSaveRoiImage()
{
	if (m_ComboRoiList.GetCurSel() >= 0) {
		QrSDK::QrRoiItem item = theApp.pMainDlg->pQrCamera->qrROI.Get(m_ComboRoiList.GetCurSel());
		CFileDialog dlg(FALSE, _T(".png"), nullptr, OFN_OVERWRITEPROMPT, _T("PNG files(*.png)|*.png||"), this);
		if (dlg.DoModal() == IDOK)
		{
			QrSDK::QrSnapshot qrSnapshot;
			CString filePath = dlg.GetPathName();
			CT2CA str(filePath);
			qrSnapshot.Save(std::string(str), theApp.pMainDlg->qrImage, item.Rect);
		}
	}
}

/**
* @brief Open log file
*
* @return
*/
void CTabRoi::OnBnClickedButtonOpenLogFile()
{
	CFileDialog dlg(FALSE, _T(".csv"), nullptr, OFN_OVERWRITEPROMPT, _T("CSV files(*.csv)|*.csv|Text Files (*.txt)|*.txt||"), this);
	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();
		CT2CA str(filePath);
		theApp.pMainDlg->qrLogger.Open(std::string(str));
	}
}

/**
* @brief Write log
*
* @return
*/
void CTabRoi::OnBnClickedButtonLogItem()
{
	if (m_ComboRoiList.GetCurSel() >= 0) {
		QrSDK::QrRoiItem item = theApp.pMainDlg->pQrCamera->qrROI.Get(m_ComboRoiList.GetCurSel());
		theApp.pMainDlg->qrLogger.Write(item);
	}
}

