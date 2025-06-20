// CTabRemoteCamera.cpp : implementation file
//

#include "pch.h"
#include "QrWinMFC.h"
#include "CTabRemoteCamera.h"
#include "afxdialogex.h"


// CTabRemoteCamera dialog

IMPLEMENT_DYNAMIC(CTabRemoteCamera, CDialogEx)

CTabRemoteCamera::CTabRemoteCamera(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_REMOTECAMERA, pParent)
{

}

CTabRemoteCamera::~CTabRemoteCamera()
{
}

void CTabRemoteCamera::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_REMOTE_CONNECT, m_BtnRemoteConnect);
	DDX_Control(pDX, IDC_IPADDRESS, m_RemoteAddress);
}


BEGIN_MESSAGE_MAP(CTabRemoteCamera, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REMOTE_CONNECT, &CTabRemoteCamera::OnBnClickedButtonRemoteConnect)
END_MESSAGE_MAP()


// CTabRemoteCamera message handlers

/**
* @brief Connect remote camera
*
* @return
*/
void CTabRemoteCamera::OnBnClickedButtonRemoteConnect()
{
	CString strCaption;
	m_BtnRemoteConnect.GetWindowTextW(strCaption);

	if (strCaption == _T("CONNECT"))
	{
		BYTE addr0, addr1, addr2, addr3;
		m_RemoteAddress.GetAddress(addr0, addr1, addr2, addr3);

		try
		{
			//CString name;
			//m_CbLocalSerialPorts.GetLBText(serial, name);

			CString strIpAddress;
			strIpAddress.Format(_T("%d.%d.%d.%d"), addr0, addr1, addr2, addr3);
			theApp.pMainDlg->pQrCamera = new QrSDK::QrRemoteCamera();
			if (theApp.pMainDlg->pQrCamera->Connect(std::string(CT2CA(strIpAddress)), 10603) && theApp.pMainDlg->pQrCamera->IsConnect)
			{
			
				if (theApp.pMainDlg->pQrCamera->Open(std::string(CT2CA(strIpAddress)), 10604))
				{
					theApp.pMainDlg->m_hThread = AfxBeginThread(CQrWinMFCDlg::FrameWorker, theApp.pMainDlg);
					m_BtnRemoteConnect.SetWindowTextW(_T("DISCONNECT"));

					///if (theApp.pMainDlg->m_TabControlProduct.m_ComboProtocol.GetCurSel() == 0) {
					///	theApp.pMainDlg->pQrCamera->qrControl.pQrCtrl->protocolMode = QrSDK::QrProtocol::MODE_NORMAL;
					///}
					///else if (theApp.pMainDlg->m_TabControlProduct.m_ComboProtocol.GetCurSel() == 1) {
					///	theApp.pMainDlg->pQrCamera->qrControl.pQrCtrl->protocolMode = QrSDK::QrProtocol::MODE_PACKET;
					///}
					///theApp.pMainDlg->m_TabControlProduct.RefreshButton();
				}
			}
		}
		catch (QrSDK::QrException ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}
	else
	{
		if (theApp.pMainDlg->pQrCamera->IsConnect)
		{
			theApp.pMainDlg->pQrCamera->Disconnect();
			m_BtnRemoteConnect.SetWindowTextW(_T("CONNECT"));
		}
	}
}
