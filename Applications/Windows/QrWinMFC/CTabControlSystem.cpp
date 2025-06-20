// CTabControlSystem.cpp : implementation file
//

#include "pch.h"
#include "QrWinMFC.h"
#include "CTabControlSystem.h"
#include "afxdialogex.h"


// CTabControlSystem dialog

IMPLEMENT_DYNAMIC(CTabControlSystem, CDialogEx)

CTabControlSystem::CTabControlSystem(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_CONTROL_SYSTEM, pParent)
{

}

CTabControlSystem::~CTabControlSystem()
{
}

void CTabControlSystem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_IP_MODE, m_CbIpMode);
	DDX_Control(pDX, IDC_IP_ADDRESS, m_IpAddress);
	DDX_Control(pDX, IDC_GATEWAY_ADDRESS, m_GatewayAddress);
	DDX_Control(pDX, IDC_SUBNETMASK, m_SubnetMask);
	DDX_Control(pDX, IDC_DNS_ADDRESS, m_DnsAddress);
	DDX_Control(pDX, IDC_COMBO_TRSM_GUIDE_TO, m_CbTrsmGuideTo);
}


BEGIN_MESSAGE_MAP(CTabControlSystem, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SET_NETWORK_REBOOT, &CTabControlSystem::OnBnClickedButtonSetNetworkReboot)
	ON_BN_CLICKED(IDC_BUTTON_GET_VIDEO_RESOLUTION, &CTabControlSystem::OnBnClickedButtonGetVideoResolution)
	ON_BN_CLICKED(IDC_BUTTON_GET_VIDEO_FPS, &CTabControlSystem::OnBnClickedButtonGetVideoFps)
	ON_BN_CLICKED(IDC_BUTTON_GET_VIDEO_FORMAT, &CTabControlSystem::OnBnClickedButtonGetVideoFormat)
	ON_BN_CLICKED(IDC_BUTTON_GET_MAC_ADDRESS, &CTabControlSystem::OnBnClickedButtonGetMacAddress)
	ON_BN_CLICKED(IDC_BUTTON_GET_IP_MODE, &CTabControlSystem::OnBnClickedButtonGetIpMode)
	ON_BN_CLICKED(IDC_BUTTON_SET_IP_MODE, &CTabControlSystem::OnBnClickedButtonSetIpMode)
	ON_BN_CLICKED(IDC_BUTTON_GET_IP_ADDRESS, &CTabControlSystem::OnBnClickedButtonGetIpAddress)
	ON_BN_CLICKED(IDC_BUTTON_SET_IP_ADDRESS, &CTabControlSystem::OnBnClickedButtonSetIpAddress)
	ON_BN_CLICKED(IDC_BUTTON_GET_GATEWAY_ADDRESS, &CTabControlSystem::OnBnClickedButtonGetGatewayAddress)
	ON_BN_CLICKED(IDC_BUTTON_SET_GATEWAY_ADDRESS, &CTabControlSystem::OnBnClickedButtonSetGatewayAddress)
	ON_BN_CLICKED(IDC_BUTTON_GET_SUBNETMASK, &CTabControlSystem::OnBnClickedButtonGetSubnetmask)
	ON_BN_CLICKED(IDC_BUTTON_SET_SUBNETMASK, &CTabControlSystem::OnBnClickedButtonSetSubnetmask)
	ON_BN_CLICKED(IDC_BUTTON_GET_DNS_ADDRESS, &CTabControlSystem::OnBnClickedButtonGetDnsAddress)
	ON_BN_CLICKED(IDC_BUTTON_SET_DNS_ADDRESS, &CTabControlSystem::OnBnClickedButtonSetDnsAddress)
	ON_BN_CLICKED(IDC_BUTTON_SET_TRSM_GUIDE_TO, &CTabControlSystem::OnBnClickedButtonSetTrsmGuideTo)
	ON_BN_CLICKED(IDC_BUTTON_SET_TRSM_SAVE, &CTabControlSystem::OnBnClickedButtonSetTrsmSave)
	ON_BN_CLICKED(IDC_BUTTON_SET_TRSM_GUIDE, &CTabControlSystem::OnBnClickedButtonSetTrsmGuide)
	ON_BN_CLICKED(IDC_BUTTON_SET_TRSM_COMP, &CTabControlSystem::OnBnClickedButtonSetTrsmComp)
	ON_BN_CLICKED(IDC_BUTTON_SET_TRSM_REF_TEMP, &CTabControlSystem::OnBnClickedButtonSetTrsmRefTemp)
END_MESSAGE_MAP()


// CTabControlSystem message handlers

/**
* @brief Get video resolution
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonGetVideoResolution()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (theApp.pMainDlg->pQrCamera->qrControl.GetVideoResolution())
	{
		CString str;
		str.Format(_T("%d x %d"), theApp.pMainDlg->pQrCamera->qrControl.VideoWidth(), theApp.pMainDlg->pQrCamera->qrControl.VideoHeight());
		SetDlgItemText(IDC_EDIT_VIDEO_RESOLUTION, str);
	}
}

/**
* @brief Get video FPS
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonGetVideoFps()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (theApp.pMainDlg->pQrCamera->qrControl.GetVideoFPS())
	{
		SetDlgItemInt(IDC_EDIT_VIDEO_FPS, theApp.pMainDlg->pQrCamera->qrControl.VideoFPS());
	}
}

/**
* @brief Get video format
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonGetVideoFormat()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (theApp.pMainDlg->pQrCamera->qrControl.GetVideoFormat())
	{
		SetDlgItemText(IDC_EDIT_VIDEO_FORMAT, CString(theApp.pMainDlg->pQrCamera->qrControl.VideoFormat().c_str()));
	}
}

/**
* @brief Get MAC address
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonGetMacAddress()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (theApp.pMainDlg->pQrCamera->qrControl.GetMacAddress())
	{
		CString str;
		uint8_t* mac = theApp.pMainDlg->pQrCamera->qrControl.MacAddress();
		str.Format(_T("%02X:%02X:%02X:%02X:%02X:%02X"), mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
		SetDlgItemText(IDC_MAC_ADDRESS, str);
	}
}

/**
* @brief Get IP mode
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonGetIpMode()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	if (theApp.pMainDlg->pQrCamera->qrControl.GetIpMode())
	{
		QrSDK::QrProtocol::tIpMode mode = theApp.pMainDlg->pQrCamera->qrControl.IpMode();
		if (mode == QrSDK::QrProtocol::IP_MODE::IP_STATIC)
		{
			m_CbIpMode.SetCurSel(0);
		}
		else
		{
			m_CbIpMode.SetCurSel(1);
		}
	}
}

/**
* @brief Set IP mode
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonSetIpMode()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	int sel = m_CbIpMode.GetCurSel();
	if (sel < 0 || sel > 1) return;

	QrSDK::QrProtocol::tIpMode mode = sel == 0 ? QrSDK::QrProtocol::IP_MODE::IP_STATIC : QrSDK::QrProtocol::IP_MODE::IP_DHCP;

	if (theApp.pMainDlg->pQrCamera->qrControl.SetIpMode(mode))
	{
	}
}

/**
* @brief Get IP address
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonGetIpAddress()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (theApp.pMainDlg->pQrCamera->qrControl.GetIpAddress())
	{
		CString str;
		uint8_t* addr = theApp.pMainDlg->pQrCamera->qrControl.IpAddress();
		str.Format(_T("%d.%d.%d.%d"), addr[0], addr[1], addr[2], addr[3]);
		SetDlgItemText(IDC_IP_ADDRESS, str);
	}
}

/**
* @brief Set IP address
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonSetIpAddress()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	BYTE addr0, addr1, addr2, addr3;
	m_IpAddress.GetAddress(addr0, addr1, addr2, addr3);

	if (theApp.pMainDlg->pQrCamera->qrControl.SetIpAddress(std::vector<uint8_t> {addr0, addr1, addr2, addr3}))
	{
	}
}

/**
* @brief Get gateway address
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonGetGatewayAddress()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (theApp.pMainDlg->pQrCamera->qrControl.GetGatewayAddress())
	{
		CString str;
		uint8_t* addr = theApp.pMainDlg->pQrCamera->qrControl.GatewayAddress();
		str.Format(_T("%d.%d.%d.%d"), addr[0], addr[1], addr[2], addr[3]);
		SetDlgItemText(IDC_GATEWAY_ADDRESS, str);
	}
}

/**
* @brief Set gateway address
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonSetGatewayAddress()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	BYTE addr0, addr1, addr2, addr3;
	m_GatewayAddress.GetAddress(addr0, addr1, addr2, addr3);

	if (theApp.pMainDlg->pQrCamera->qrControl.SetGatewayAddress(std::vector<uint8_t> {addr0, addr1, addr2, addr3}))
	{
	}
}

/**
* @brief Get subnetmask
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonGetSubnetmask()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (theApp.pMainDlg->pQrCamera->qrControl.GetSubnetMask())
	{
		CString str;
		uint8_t* mask = theApp.pMainDlg->pQrCamera->qrControl.SubnetMask();
		str.Format(_T("%d.%d.%d.%d"), mask[0], mask[1], mask[2], mask[3]);
		SetDlgItemText(IDC_SUBNETMASK, str);
	}
}

/**
* @brief Set subnetmask
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonSetSubnetmask()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	BYTE addr0, addr1, addr2, addr3;
	m_SubnetMask.GetAddress(addr0, addr1, addr2, addr3);

	if (theApp.pMainDlg->pQrCamera->qrControl.SetSubnetMask(std::vector<uint8_t> {addr0, addr1, addr2, addr3}))
	{
	}
}

/**
* @brief Assert reboot to network
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonSetNetworkReboot()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (theApp.pMainDlg->pQrCamera->qrControl.SetNetworkReboot())
	{
	}
}

/**
* @brief Get DNS address
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonGetDnsAddress()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (theApp.pMainDlg->pQrCamera->qrControl.GetDnsAddress())
	{
		CString str;
		uint8_t* addr = theApp.pMainDlg->pQrCamera->qrControl.DnsAddress();
		str.Format(_T("%d.%d.%d.%d"), addr[0], addr[1], addr[2], addr[3]);
		SetDlgItemText(IDC_DNS_ADDRESS, str);
	}
}

/**
* @brief Set DNS address
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonSetDnsAddress()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	BYTE addr0, addr1, addr2, addr3;
	m_DnsAddress.GetAddress(addr0, addr1, addr2, addr3);

	if (theApp.pMainDlg->pQrCamera->qrControl.SetDnsAddress(std::vector<uint8_t> {addr0, addr1, addr2, addr3}))
	{
	}
}

/**
* @brief Set TRSM guide
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonSetTrsmGuideTo()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	int sel = m_CbTrsmGuideTo.GetCurSel();
	if (sel < 0 || sel > 3) return;

	QrSDK::QrProtocol::tTrsmGuideTo val = (QrSDK::QrProtocol::tTrsmGuideTo)sel;

	if (theApp.pMainDlg->pQrCamera->qrControl.SetTrsmGuideTo(val))
	{
	}
}

/**
* @brief Set TRSM guide save
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonSetTrsmSave()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (theApp.pMainDlg->pQrCamera->qrControl.SetTrsmGuideSave())
	{
	}
}

/**
* @brief Set TRSM value
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonSetTrsmValue()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	CString str;
	GetDlgItemText(IDC_EDIT_TRSM_VALUE, str);
	if (theApp.pMainDlg->pQrCamera->qrControl.SetTrsmRefTemp(_wtoi(str)))
	{

	}
}

/**
* @brief Set TRSM guide
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonSetTrsmGuide()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (IsDlgButtonChecked(IDC_RADIO_TRSM_GUIDE_ON) != 0 || IsDlgButtonChecked(IDC_RADIO_TRSM_GUIDE_OFF) != 0)
	{
		QrSDK::QrProtocol::tTrsmGuide val = IsDlgButtonChecked(IDC_RADIO_TRSM_GUIDE_ON) != 0 ? QrSDK::QrProtocol::TRSM_GUIDE::TRSM_GUIDE_ON : QrSDK::QrProtocol::TRSM_GUIDE::TRSM_GUIDE_OFF;
		if (theApp.pMainDlg->pQrCamera->qrControl.SetTrsmGuide(val))
		{

		}
	}
}

/**
* @brief Set TRSM compensation
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonSetTrsmComp()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;

	if (IsDlgButtonChecked(IDC_RADIO_TRSM_COMP_ON) != 0 || IsDlgButtonChecked(IDC_RADIO_TRSM_COMP_OFF) != 0)
	{
		QrSDK::QrProtocol::tTrsmComp val = IsDlgButtonChecked(IDC_RADIO_TRSM_COMP_ON) != 0 ? QrSDK::QrProtocol::TRSM_COMP::TRSM_COMP_ON : QrSDK::QrProtocol::TRSM_COMP::TRSM_COMP_OFF;
		if (theApp.pMainDlg->pQrCamera->qrControl.SetTrsmComp(val))
		{

		}
	}
}

/**
* @brief Set TRSM ref temperature
*
* @return
*/
void CTabControlSystem::OnBnClickedButtonSetTrsmRefTemp()
{
	if (theApp.pMainDlg->pQrCamera == nullptr) return;
	CString str;
	GetDlgItemText(IDC_EDIT_TRSM_REF_TEMP, str);
	if (theApp.pMainDlg->pQrCamera->qrControl.SetTrsmRefTemp(_wtof(str)))
	{

	}
}
