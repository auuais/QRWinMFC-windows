// CTabCalib.cpp : implementation file
//

#include "pch.h"
#include "QrWinMFC.h"
#include "CTabCalib.h"
#include "afxdialogex.h"


// CTabCalib dialog

IMPLEMENT_DYNAMIC(CTabCalib, CDialogEx)

CTabCalib::CTabCalib(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_CALIB, pParent)
{

}

CTabCalib::~CTabCalib()
{
}

void CTabCalib::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_OBJ_EMISSIVITY, m_EditObjEmissivity);
	DDX_Control(pDX, IDC_EDIT_REFL_TEMP, m_EditReflTemp);
	DDX_Control(pDX, IDC_EDIT_DISTANCE, m_EditDistance);
	DDX_Control(pDX, IDC_EDIT_ATM_TEMP, m_EditAtmTemp);
	DDX_Control(pDX, IDC_EDIT_HUMIDITY, m_EditHumidity);
	DDX_Control(pDX, IDC_EDIT_ATM_TRANS, m_EditAtmTrans);
	DDX_Control(pDX, IDC_EDIT_LENS_TEMP, m_EditLensTemp);
	DDX_Control(pDX, IDC_EDIT_LENS_TRANS, m_EditLensTrans);
	DDX_Control(pDX, IDC_RADIO_HIGH_GAIN, m_radioHighGain);
	DDX_Control(pDX, IDC_RADIO_LOW_GAIN, m_radioLowGain);
}


BEGIN_MESSAGE_MAP(CTabCalib, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_CALIB, &CTabCalib::OnBnClickedButtonOpenCalib)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_PARAMS, &CTabCalib::OnBnClickedButtonUpdateParams)
END_MESSAGE_MAP()


// CTabCalib message handlers

/** 
* @brief Open calibration file
*
* @return
*/
void CTabCalib::OnBnClickedButtonOpenCalib()
{
	CFileDialog dlg(TRUE, _T(".xml"), nullptr, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("XAML File(*.xml, *.xaml) |*.xml;*.xaml| All Files(*.*)|*.*||"), this);
	if (dlg.DoModal() == IDOK)
	{
		QrSDK::QrSnapshot qrSnapshot;
		CString filePath = dlg.GetPathName();
		CT2CA str(filePath);
		std::string serialNumber = theApp.pMainDlg->pQrCamera->qrControl.SensorSerial();
		bool ret = false;
		if (IsDlgButtonChecked(IDC_RADIO_LOW_GAIN) != 0) {
			//ret = theApp.pMainDlg->pQrCamera->LoadCalibParams(std::string(str), 1, serialNumber);
			ret = theApp.pMainDlg->pQrCamera->LoadCalibFile(std::string(str), 1);
		}
		else {
			//ret = theApp.pMainDlg->pQrCamera->LoadCalibParams(std::string(str), 0, serialNumber);
			ret = theApp.pMainDlg->pQrCamera->LoadCalibFile(std::string(str), 0);
		}

		if (ret) {
			AfxMessageBox(CA2T("Successfully loaded calibration file."));
		}
		else {
			AfxMessageBox(CA2T("Failed to load the calibration file.\n(check the serial number in the file.)"));
		}
	}
}

/**
* @brief Update parameters
*
* @return
*/
void CTabCalib::OnBnClickedButtonUpdateParams()
{
	if (theApp.pMainDlg->pQrCamera != NULL && theApp.pMainDlg->pQrCamera->IsConnect) {

		CString str;
		m_EditObjEmissivity.GetWindowTextW(str);
		double objEmissivity = _tcstod(str, NULL);
		m_EditReflTemp.GetWindowTextW(str);
		double reflTemp = _tcstod(str, NULL);
		m_EditDistance.GetWindowTextW(str);
		double distance = _tcstod(str, NULL);
		m_EditAtmTemp.GetWindowTextW(str);
		double atmTemp = _tcstod(str, NULL);
		m_EditHumidity.GetWindowTextW(str);
		double humidity = _tcstod(str, NULL);
		m_EditAtmTrans.GetWindowTextW(str);
		double atmTrans = _tcstod(str, NULL);
		m_EditLensTemp.GetWindowTextW(str);
		double lensTemp = _tcstod(str, NULL);
		m_EditLensTrans.GetWindowTextW(str);
		double lensTrans = _tcstod(str, NULL);

		bool ret = theApp.pMainDlg->pQrCamera->SetFluxParams(objEmissivity, reflTemp, distance, atmTemp, humidity, atmTrans, lensTemp, lensTrans);
		if (ret == FALSE) {
			std::cout << "Set parameter Failed!" << endl;
		}
	}
}
