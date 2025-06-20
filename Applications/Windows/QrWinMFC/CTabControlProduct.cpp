// CTabControlProduct.cpp : implementation file
//

#include "pch.h"
#include "QrWinMFC.h"
#include "CTabControlProduct.h"
#include "afxdialogex.h"


// CTabControlProduct dialogm_BtnGetProductVersion

IMPLEMENT_DYNAMIC(CTabControlProduct, CDialogEx)

CTabControlProduct::CTabControlProduct(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_CONTROL_PRODUCT, pParent)
{

}

CTabControlProduct::~CTabControlProduct()
{
}

void CTabControlProduct::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_GET_PRODUCT_VERSION, m_BtnGetProductVersion);
	DDX_Control(pDX, IDC_BUTTON_GET_HW_VERSION, m_BtnGetHwVersion);
	DDX_Control(pDX, IDC_BUTTON_GET_SW_VERSION, m_BtnGetSwVersion);
	DDX_Control(pDX, IDC_BUTTON_GET_REF_GAIN, m_BtnGetRefGain);
	DDX_Control(pDX, IDC_BUTTON_GET_REF_OFFSET, m_BtnGetRefOffset);
	DDX_Control(pDX, IDC_BUTTON_GET_TEMP_COEFF1, m_GetTempCoeff1);
	DDX_Control(pDX, IDC_BUTTON_GET_TEMP_COEFF2, m_GetTempCoeff2);
	DDX_Control(pDX, IDC_EDIT_MODEL, m_EditModel);
	DDX_Control(pDX, IDC_BUTTON_GET_GAIN_MODE, m_BtnGetGainMode);
	DDX_Control(pDX, IDC_BUTTON_GET_WHITE_BLACK_HOT, m_BtnGetWhiteBlackHot);
	DDX_Control(pDX, IDC_BUTTON_GET_SYSTEM_SETTING, m_BtnGetSystemSetting);
	DDX_Control(pDX, IDC_BUTTON_GET_FPA_TEMP, m_BtnGetFpaTemp);
	DDX_Control(pDX, IDC_BUTTON_GET_BODY_TEMP, m_BtnGetBodyTemp);
	DDX_Control(pDX, IDC_COMBO_VIEW_MODE, m_ComboViewMode);
}


BEGIN_MESSAGE_MAP(CTabControlProduct, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GET_PRODUCT_SERIAL, &CTabControlProduct::OnBnClickedButtonGetProductSerial)
	ON_BN_CLICKED(IDC_BUTTON_GET_SENSOR_SERIAL, &CTabControlProduct::OnBnClickedButtonGetSensorSerial)
	ON_BN_CLICKED(IDC_BUTTON_GET_GAIN_MODE, &CTabControlProduct::OnBnClickedButtonGetGainMode)
	ON_BN_CLICKED(IDC_BUTTON_SET_GAIN_MODE, &CTabControlProduct::OnBnClickedButtonSetGainMode)
	ON_BN_CLICKED(IDC_BUTTON_SET_REF_GAIN, &CTabControlProduct::OnBnClickedButtonSetRefGain)
	ON_BN_CLICKED(IDC_BUTTON_SET_REF_OFFSET, &CTabControlProduct::OnBnClickedButtonSetRefOffset)
	ON_BN_CLICKED(IDC_BUTTON_SET_TEMP_COEFF1, &CTabControlProduct::OnBnClickedButtonSetTempCoeff1)
	ON_BN_CLICKED(IDC_BUTTON_SET_TEMP_COEFF2, &CTabControlProduct::OnBnClickedButtonSetTempCoeff2)
	ON_BN_CLICKED(IDC_BUTTON_GET_TEMP_INFO, &CTabControlProduct::OnBnClickedButtonGetTempInfo)
	ON_BN_CLICKED(IDC_BUTTON_GET_MODEL, &CTabControlProduct::OnBnClickedButtonGetModel)
	ON_BN_CLICKED(IDC_BUTTON_GET_HW_VERSION, &CTabControlProduct::OnBnClickedButtonGetHwVersion)
	ON_BN_CLICKED(IDC_BUTTON_GET_SW_VERSION, &CTabControlProduct::OnBnClickedButtonGetSwVersion)
	ON_BN_CLICKED(IDC_BUTTON_GET_REF_GAIN, &CTabControlProduct::OnBnClickedButtonGetRefGain)
	ON_BN_CLICKED(IDC_BUTTON_GET_REF_OFFSET, &CTabControlProduct::OnBnClickedButtonGetRefOffset)
	ON_BN_CLICKED(IDC_BUTTON_GET_TEMP_COEFF1, &CTabControlProduct::OnBnClickedButtonGetTempCoeff1)
	ON_BN_CLICKED(IDC_BUTTON_GET_TEMP_COEFF2, &CTabControlProduct::OnBnClickedButtonGetTempCoeff2)
	ON_BN_CLICKED(IDC_BUTTON_GET_BODY_TEMP, &CTabControlProduct::OnBnClickedButtonGetBodyTemp)
	ON_BN_CLICKED(IDC_BUTTON_GET_FPA_TEMP, &CTabControlProduct::OnBnClickedButtonGetFpaTemp)
	ON_BN_CLICKED(IDC_BUTTON_GET_WHITE_BLACK_HOT, &CTabControlProduct::OnBnClickedButtonGetWhiteBlackHot)
	ON_BN_CLICKED(IDC_BUTTON_SET_HOT_WHITE_BLACK, &CTabControlProduct::OnBnClickedButtonSetHotWhiteBlack)
	ON_BN_CLICKED(IDC_BUTTON_GET_SYSTEM_SETTING, &CTabControlProduct::OnBnClickedButtonGetSystemSetting)
	ON_BN_CLICKED(IDC_BUTTON_SET_TEMP_CONVERT, &CTabControlProduct::OnBnClickedButtonSetTempConvert)
	ON_BN_CLICKED(IDC_BUTTON_GET_PRODUCT_VERSION, &CTabControlProduct::OnBnClickedButtonGetProductVersion)
	ON_BN_CLICKED(IDC_BUTTON_GET_AUTOSHUTTER, &CTabControlProduct::OnBnClickedButtonGetAutoshutter)
	ON_BN_CLICKED(IDC_BUTTON_SET_AUTOSHUTTER, &CTabControlProduct::OnBnClickedButtonSetAutoshutter)
	ON_BN_CLICKED(IDC_BUTTON_SET_SHUTTER_CONTROL, &CTabControlProduct::OnBnClickedButtonSetShutterControl)
	ON_BN_CLICKED(IDC_BUTTON_SET_SYSTEM_REBOOT, &CTabControlProduct::OnBnClickedButtonSetSystemReboot)
	ON_BN_CLICKED(IDC_BUTTON_SET_1P_NUC, &CTabControlProduct::OnBnClickedButtonSet1pNuc)
	ON_BN_CLICKED(IDC_BUTTON_SET_VIEW_MODE, &CTabControlProduct::OnBnClickedButtonSetViewMode)
	ON_BN_CLICKED(IDC_BUTTON_SET_TEC, &CTabControlProduct::OnBnClickedButtonSetTec)
	ON_BN_CLICKED(IDC_BUTTON_SET_DPC, &CTabControlProduct::OnBnClickedButtonSetDpc)
	ON_BN_CLICKED(IDC_BUTTON_SET_2ND_COMP, &CTabControlProduct::OnBnClickedButtonSet2ndComp)
	ON_BN_CLICKED(IDC_BUTTON_SET_SHUTTER_COMP, &CTabControlProduct::OnBnClickedButtonSetShutterComp)
	ON_BN_CLICKED(IDC_BUTTON_SET_IMAGE_OUT, &CTabControlProduct::OnBnClickedButtonSetImageOut)
END_MESSAGE_MAP()


// CTabControlProduct message handlers

/**
* @brief Get product serial number
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonGetProductSerial()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (theApp.pMainDlg->pQrCamera->qrControl.GetProductSerial())
	{
		SetDlgItemText(IDC_EDIT_PRODUCT_SERIAL, CString(theApp.pMainDlg->pQrCamera->qrControl.ProductSerial().c_str()));
	}
}

/**
* @brief Get sensor serial number
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonGetSensorSerial()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (theApp.pMainDlg->pQrCamera->qrControl.GetSensorSerial())
	{
		SetDlgItemText(IDC_EDIT_SENSOR_SERIAL, CString(theApp.pMainDlg->pQrCamera->qrControl.SensorSerial().c_str()));
	}
}

/**
* @brief Get gain mode
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonGetGainMode()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (theApp.pMainDlg->pQrCamera->qrControl.GetGainMode())
	{
		if (theApp.pMainDlg->pQrCamera->qrControl.GainMode() == QrSDK::QrProtocol::GAIN_MODE::GAIN_HIGH)
		{
			((CButton*)GetDlgItem(IDC_RADIO_GAIN_HIGH))->SetCheck(true);
			((CButton*)GetDlgItem(IDC_RADIO_GAIN_LOW))->SetCheck(false);
		}
		else
		{
			((CButton*)GetDlgItem(IDC_RADIO_GAIN_HIGH))->SetCheck(false);
			((CButton*)GetDlgItem(IDC_RADIO_GAIN_LOW))->SetCheck(true);
		}

		CString str;
	}
}

/**
* @brief Set gain mode
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonSetGainMode()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (IsDlgButtonChecked(IDC_RADIO_GAIN_HIGH) != 0 || IsDlgButtonChecked(IDC_RADIO_GAIN_LOW) != 0)
	{
		QrSDK::QrProtocol::tGainMode gain = IsDlgButtonChecked(IDC_RADIO_GAIN_HIGH) != 0 ? QrSDK::QrProtocol::GAIN_MODE::GAIN_HIGH : QrSDK::QrProtocol::GAIN_MODE::GAIN_LOW;
		if (theApp.pMainDlg->pQrCamera->qrControl.SetGainMode(gain))
		{

		}
	}
}

/**
* @brief Set ref gain
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonSetRefGain()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	CString str;
	GetDlgItemText(IDC_EDIT_REF_GAIN, str);
	//if (theApp.pMainDlg->pQrCamera->qrControl.SetRefGain(_wtof(str)))
	//{

	//}

}

/**
* @brief Set ref offset
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonSetRefOffset()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	CString str;
	GetDlgItemText(IDC_EDIT_REF_OFFSET, str);
	//if (theApp.pMainDlg->pQrCamera->qrControl.SetRefOffset(_wtof(str)))
	//{

	//}
}

/**
* @brief Set temperature coeff1
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonSetTempCoeff1()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	CString str;
	GetDlgItemText(IDC_EDIT_TEMP_COEFF1, str);
	//if (theApp.pMainDlg->pQrCamera->qrControl.SetTempCoeff1(_wtof(str)))
	//{

	//}
}

/**
* @brief Set temperature coeff2
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonSetTempCoeff2()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	CString str;
	GetDlgItemText(IDC_EDIT_TEMP_COEFF2, str);
	//if (theApp.pMainDlg->pQrCamera->qrControl.SetTempCoeff2(_wtof(str)))
	//{

	//}
}

/**
* @brief Get temperature information
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonGetTempInfo()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	//if (theApp.pMainDlg->pQrCamera->qrControl.GetTempInfo())
	//{
	//	CString str;

	//	str.Format(_T("%f"), theApp.pMainDlg->pQrCamera->qrControl.TempFPA());
	//	SetDlgItemText(IDC_EDIT_TEMP_FPA, str);
	//	str.Format(_T("%f"), theApp.pMainDlg->pQrCamera->qrControl.TempBody());
	//	SetDlgItemText(IDC_EDIT_TEMP_BODY, str);
	//}	
}

/**
* @brief Get FPA temperature
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonGetFpaTemp()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	if (theApp.pMainDlg->pQrCamera->qrControl.GetTempFPA())
	{
		CString str;

		str.Format(_T("%f"), theApp.pMainDlg->pQrCamera->qrControl.TempFPA());
		SetDlgItemText(IDC_EDIT_TEMP_FPA, str);
	}
}

/**
* @brief Get body temperature
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonGetBodyTemp()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	if (theApp.pMainDlg->pQrCamera->qrControl.GetTempBody())
	{
		CString str;

		str.Format(_T("%f"), theApp.pMainDlg->pQrCamera->qrControl.TempBody());
		SetDlgItemText(IDC_EDIT_TEMP_BODY, str);
	}
}

/**
* @brief Get model
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonGetModel()
{
	if (theApp.pMainDlg->pQrCamera == nullptr)
		return;
	theApp.pMainDlg->pQrCamera->qrControl.GetModel();
	SetDlgItemText(IDC_EDIT_MODEL, CString(theApp.pMainDlg->pQrCamera->qrControl.Model().c_str()));
}

/**
* @brief Get product version
*
* @return
*/
//void CTabControlProduct::OnBnClickedButtonGetVersion()
//{
//	if (theApp.pMainDlg->pQrCamera == nullptr)
//		return;
//	theApp.pMainDlg->pQrCamera->qrControl.GetProductVersion();
//	SetDlgItemText(IDC_EDIT_PRODUCT_VERSION, CString(theApp.pMainDlg->pQrCamera->qrControl.ProductVersion().c_str()));
//}

/**
* @brief Get hardware version
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonGetHwVersion()
{
	if (theApp.pMainDlg->pQrCamera == nullptr)
		return;
	theApp.pMainDlg->pQrCamera->qrControl.GetHardwareVersion();
	SetDlgItemText(IDC_EDIT_HW_VERSION, CString(theApp.pMainDlg->pQrCamera->qrControl.HardwareVersion().c_str()));
}

/**
* @brief Get software version
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonGetSwVersion()
{
	if (theApp.pMainDlg->pQrCamera == nullptr)
		return;
	theApp.pMainDlg->pQrCamera->qrControl.GetSoftwareVersion();
	SetDlgItemText(IDC_EDIT_SW_VERSION, CString(theApp.pMainDlg->pQrCamera->qrControl.SoftwareVersion().c_str()));
}

/**
* @brief Get ref gain
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonGetRefGain()
{
	if (theApp.pMainDlg->pQrCamera == nullptr)
		return;
	theApp.pMainDlg->pQrCamera->qrControl.GetRefGain();
	CString str;
	str.Format(_T("%f"), theApp.pMainDlg->pQrCamera->qrControl.RefGain());
	SetDlgItemText(IDC_EDIT_REF_GAIN, str);
}

/**
* @brief Get ref offset
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonGetRefOffset()
{
	if (theApp.pMainDlg->pQrCamera == nullptr)
		return;
	theApp.pMainDlg->pQrCamera->qrControl.GetRefOffset();
	CString str;
	str.Format(_T("%f"), theApp.pMainDlg->pQrCamera->qrControl.RefOffset());
	SetDlgItemText(IDC_EDIT_REF_OFFSET, str);
}

/**
* @brief Get temperature coeff1
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonGetTempCoeff1()
{
	if (theApp.pMainDlg->pQrCamera == nullptr)
		return;
	theApp.pMainDlg->pQrCamera->qrControl.GetTempCoeff1();
	CString str;
	str.Format(_T("%f"), theApp.pMainDlg->pQrCamera->qrControl.EstTempCoeff1());
	SetDlgItemText(IDC_EDIT_TEMP_COEFF1, str);
}

/**
* @brief Get temperature coeff2
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonGetTempCoeff2()
{
	if (theApp.pMainDlg->pQrCamera == nullptr)
		return;
	theApp.pMainDlg->pQrCamera->qrControl.GetTempCoeff2();
	CString str;
	str.Format(_T("%f"), theApp.pMainDlg->pQrCamera->qrControl.EstTempCoeff2());
	SetDlgItemText(IDC_EDIT_TEMP_COEFF2, str);
}

/**
* @brief Get hot mode
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonGetWhiteBlackHot()
{
	if (theApp.pMainDlg->pQrCamera == nullptr)
		return;
	theApp.pMainDlg->pQrCamera->qrControl.GetHotMode();
	if (theApp.pMainDlg->pQrCamera->qrControl.HotMode() == 0) {
		((CButton*)GetDlgItem(IDC_RADIO_HOT_WHITE))->SetCheck(true);
		((CButton*)GetDlgItem(IDC_RADIO_HOT_BLACK))->SetCheck(false);
	} 
	else {
		((CButton*)GetDlgItem(IDC_RADIO_HOT_WHITE))->SetCheck(false);
		((CButton*)GetDlgItem(IDC_RADIO_HOT_BLACK))->SetCheck(true);
	}
}

/**
* @brief Set hot mode
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonSetHotWhiteBlack()
{
	if (theApp.pMainDlg->pQrCamera == nullptr)
		return;

	if (IsDlgButtonChecked(IDC_RADIO_HOT_WHITE) != 0 || IsDlgButtonChecked(IDC_RADIO_HOT_BLACK) != 0)
	{
		QrSDK::QrProtocol::tHotMode hot = IsDlgButtonChecked(IDC_RADIO_HOT_WHITE) != 0 ? QrSDK::QrProtocol::HOT_MODE::HOT_WHITE : QrSDK::QrProtocol::HOT_MODE::HOT_BLACK;
		if (theApp.pMainDlg->pQrCamera->qrControl.SetHotMode(hot))
		{

		}
	}
}

/**
* @brief Get system setting
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonGetSystemSetting()
{
	if (theApp.pMainDlg->pQrCamera == nullptr)
		return;
	if (theApp.pMainDlg->pQrCamera->qrControl.GetSystemSetting()) {
		SetDlgItemText(IDC_EDIT_USECASE, CString(theApp.pMainDlg->pQrCamera->qrControl.UseCase().c_str()));
		SetDlgItemText(IDC_EDIT_DISPLAY, CString(theApp.pMainDlg->pQrCamera->qrControl.DisplaySetting().c_str()));
	}
}

/**
* @brief Set temperature convert
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonSetTempConvert()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (IsDlgButtonChecked(IDC_RADIO_TEMP_CONVERT_ON) != 0 || IsDlgButtonChecked(IDC_RADIO_TEMP_CONVERT_OFF) != 0)
	{
		QrSDK::QrProtocol::tTempConvert val = IsDlgButtonChecked(IDC_RADIO_TEMP_CONVERT_ON) != 0 ? QrSDK::QrProtocol::TEMP_CVRT::TEMP_CVRT_ON : QrSDK::QrProtocol::TEMP_CVRT::TEMP_CVRT_OFF;
		if (theApp.pMainDlg->pQrCamera->qrControl.SetTempConvert(val))
		{
		}
	}
}

/**
* @brief Get product version
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonGetProductVersion()
{
	if (theApp.pMainDlg->pQrCamera == nullptr)
		return;
	theApp.pMainDlg->pQrCamera->qrControl.GetProductVersion();
	SetDlgItemText(IDC_EDIT_PRODUCT_VERSION, CString(theApp.pMainDlg->pQrCamera->qrControl.ProductVersion().c_str()));
}

/**
* @brief Get auto shutter
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonGetAutoshutter()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	if (theApp.pMainDlg->pQrCamera->qrControl.GetAutoShutter()) {
		if (theApp.pMainDlg->pQrCamera->qrControl.AutoShutterMode() == QrSDK::QrProtocol::AUTO_SHUTTER::SHUTTER_ON) {
			((CButton*)GetDlgItem(IDC_RADIO_AUTOSHUTTER_ON))->SetCheck(true);
			((CButton*)GetDlgItem(IDC_RADIO_AUTOSHUTTER_OFF))->SetCheck(false);
		}
		else {
			((CButton*)GetDlgItem(IDC_RADIO_AUTOSHUTTER_ON))->SetCheck(false);
			((CButton*)GetDlgItem(IDC_RADIO_AUTOSHUTTER_OFF))->SetCheck(true);
		}
	}
}

/**
* @brief Set auto shutter
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonSetAutoshutter()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (IsDlgButtonChecked(IDC_RADIO_AUTOSHUTTER_ON) != 0 || IsDlgButtonChecked(IDC_RADIO_AUTOSHUTTER_OFF) != 0)
	{
		QrSDK::QrProtocol::tAutoShutter val = IsDlgButtonChecked(IDC_RADIO_AUTOSHUTTER_ON) != 0 ? QrSDK::QrProtocol::AUTO_SHUTTER::SHUTTER_ON : QrSDK::QrProtocol::AUTO_SHUTTER::SHUTTER_OFF;
		if (theApp.pMainDlg->pQrCamera->qrControl.SetAutoShutter(val))
		{

		}
	}
}

/**
* @brief Set shutter control
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonSetShutterControl()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	if (IsDlgButtonChecked(IDC_RADIO_SHUTTER_CTRL_OPEN) != 0 || IsDlgButtonChecked(IDC_RADIO_SHUTTER_CTRL_CLOSE) != 0)
	{
		QrSDK::QrProtocol::tCtrlShutter val = IsDlgButtonChecked(IDC_RADIO_SHUTTER_CTRL_OPEN) != 0 ? QrSDK::QrProtocol::SHUTTER_CTRL::SHUTTER_OPEN : QrSDK::QrProtocol::SHUTTER_CTRL::SHUTTER_CLOSE;
		if (theApp.pMainDlg->pQrCamera->qrControl.SetShutterControl(val))
		{

		}
	}
}

/**
* @brief Set system reboot
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonSetSystemReboot()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	if (theApp.pMainDlg->pQrCamera->qrControl.SetSystemReboot())
	{

	}
}

/**
* @brief Set 1p NUC
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonSet1pNuc()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (theApp.pMainDlg->pQrCamera->qrControl.Set1pNUC())
	{

	}
}

/**
* @brief Set view mode
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonSetViewMode()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (m_ComboViewMode.GetCurSel() >= 0)
	{
		QrSDK::QrProtocol::VIEW_MODE mode = QrSDK::QrProtocol::VIEW_MODE::VIEW_RAW;
		switch (m_ComboViewMode.GetCurSel())
		{
		case 0: mode = QrSDK::QrProtocol::VIEW_MODE::VIEW_NUC; break;
		case 1: mode = QrSDK::QrProtocol::VIEW_MODE::VIEW_RAW; break;
		case 2: mode = QrSDK::QrProtocol::VIEW_MODE::VIEW_PATTERN; break;
		}
		if (theApp.pMainDlg->pQrCamera->qrControl.SetViewMode(mode))
		{

		}
	}
	
}

/**
* @brief Set TEC
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonSetTec()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	if (IsDlgButtonChecked(IDC_RADIO_TEC_ON) != 0 || IsDlgButtonChecked(IDC_RADIO_TEC_OFF) != 0)
	{
		if (theApp.pMainDlg->pQrCamera->qrControl.SetTEC(IsDlgButtonChecked(IDC_RADIO_TEC_ON) != 0 
			? QrSDK::QrProtocol::TEC_CTRL::TEC_ON : QrSDK::QrProtocol::TEC_CTRL::TEC_OFF))
		{

		}
	}
}

/**
* @brief Set DPC
* 
* @return
*/
void CTabControlProduct::OnBnClickedButtonSetDpc()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	if (IsDlgButtonChecked(IDC_RADIO_DPC_ON) != 0 || IsDlgButtonChecked(IDC_RADIO_DPC_OFF) != 0)
	{
		if (theApp.pMainDlg->pQrCamera->qrControl.SetDPC(IsDlgButtonChecked(IDC_RADIO_DPC_ON) != 0
			? QrSDK::QrProtocol::DPC_CTRL::DPC_ON : QrSDK::QrProtocol::DPC_CTRL::DPC_OFF))
		{

		}
	}
}

/**
* @brief Set 2nd compensation
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonSet2ndComp()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	if (IsDlgButtonChecked(IDC_RADIO_2ND_COMP_ON) != 0 || IsDlgButtonChecked(IDC_RADIO_2ND_COMP_OFF) != 0)
	{
		if (theApp.pMainDlg->pQrCamera->qrControl.Set2ndComp(IsDlgButtonChecked(IDC_RADIO_2ND_COMP_ON) != 0
			? QrSDK::QrProtocol::COMP_CTRL::COMP_ON : QrSDK::QrProtocol::COMP_CTRL::COMP_ON))
		{

		}
	}
}

/**
* @brief Set shutter compensation
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonSetShutterComp()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	if (IsDlgButtonChecked(IDC_RADIO_SHUTTER_COMP_ON) != 0 || IsDlgButtonChecked(IDC_RADIO_SHUTTER_COMP_OFF) != 0)
	{
		if (theApp.pMainDlg->pQrCamera->qrControl.SetShutterComp(IsDlgButtonChecked(IDC_RADIO_SHUTTER_COMP_ON) != 0
			? QrSDK::QrProtocol::SHUTTER_COMP::SHUTTER_COMP_ON : QrSDK::QrProtocol::SHUTTER_COMP::SHUTTER_COMP_OFF))
		{

		}
	}
}

/**
* @brief Set image out
*
* @return
*/
void CTabControlProduct::OnBnClickedButtonSetImageOut()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	if (IsDlgButtonChecked(IDC_RADIO_IMAGE_OUT_FIRST) != 0 || IsDlgButtonChecked(IDC_RADIO_IMAGE_OUT_LAST) != 0)
	{
		if (theApp.pMainDlg->pQrCamera->qrControl.SetImageOut(IsDlgButtonChecked(IDC_RADIO_IMAGE_OUT_FIRST) != 0
			? QrSDK::QrProtocol::IMG_OUT::IMG_FIRST : QrSDK::QrProtocol::IMG_OUT::IMG_LAST))
		{

		}
	}
}

