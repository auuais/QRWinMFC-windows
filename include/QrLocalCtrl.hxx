#pragma once

#include <QrCtrl.hxx>

#if defined(_MSC_VER)
#include <windows.h>
#include "SerialThread.h"
#elif defined(__GNUC__)
#include <QrCore.hxx>
#include <termios.h>
#include <unistd.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>

#endif

namespace QrSDK
{
	class QrLocalCtrl : public QrCtrl
	{
	public:
		QrLocalCtrl();
		virtual ~QrLocalCtrl();

		bool Open(std::string port) override;
		bool Close() override;
		bool IsConnected();
		int GetQueueSize();
		uint8_t GetQueue();
	private:
#if defined(_MSC_VER)
		//HANDLE	hComm = NULL;
		SerialThread m_ComPort;
		HANDLE m_hThreadMessageHandler;
#elif defined(__GNUC__)
		int comfd = -1;
#endif
		int SendPacket(std::vector<uint8_t> packet);
		std::vector<std::string> ReceiveLocalString();
		std::vector<uint8_t> ReceiveLocalData();

		/// \cond HIDDEN_BLOCK
		// Config Setting
		bool GetAllInform() override;
		bool GetModel() override;
		bool GetProductVersion() override;
		bool GetHardwareVersion() override;
		bool GetSoftwareVersion() override;
		bool GetProductSerial() override;
		bool GetSensorSerial() override;

		bool SetAutoShutter(tAutoShutter arg) override;
		bool GetAutoShutter() override;
		bool SetShutterControl(tCtrlShutter arg) override;
		bool SetSystemReboot() override;
		bool GetSystemSetting() override;

		bool GetTempFPA() override;
		bool GetTempBody() override;
		bool GetRefGain() override;
		bool GetRefOffset() override;
		bool GetTempCoeff1() override;
		bool GetTempCoeff2() override;

		// App Setting
		bool Set1pNUC();
		bool SetViewMode(tViewMode arg) override;
		bool SetTEC(tCtrlTEC arg) override;
		bool SetDPC(tCtrlDPC arg) override;
		bool Set2ndComp(tCtrlComp arg) override;
		bool SetTempConvert(tTempConvert arg) override;
		bool SetShutterComp(tShutterComp arg) override;
		bool SetImageOut(tImageOut arg) override;
		bool SetHotMode(tHotMode arg) override;
		bool GetHotMode() override;
		bool SetGainMode(tGainMode arg) override;
		bool GetGainMode() override;

		// TRSM Control
		bool SetTrsmRefTemp(uint16_t arg) override;
		bool SetTrsmComp(tTrsmComp arg) override;
		bool SetTrsmGuide(tTrsmGuide arg) override;
		bool SetTrsmGuideSave() override;
		bool SetTrsmGuideTo(tTrsmGuideTo arg) override;

		bool SetNetworkReboot() override;
		bool GetIpMode() override;
		bool GetIpAddress() override;
		bool GetMacAddress() override;
		bool GetGatewayAddress() override;
		bool GetSubnetMask() override;
		bool GetDnsAddress() override;
		bool SetIpMode(const tIpMode val) override;
		bool SetIpAddress(const std::vector<uint8_t> addr) override;
		bool SetGatewayAddress(const std::vector<uint8_t> addr) override;
		bool SetSubnetMask(const std::vector<uint8_t> mask) override;
		bool SetDnsAddress(const std::vector<uint8_t> addr) override;

		bool GetVideoResolution() override;
		bool GetVideoFPS() override;
		bool GetVideoFormat() override;
	};
	DWORD ThreadMessageHandler(QrLocalCtrl* pQrCtrl);
	/// \endcond HIDDEN_BLOCK
}
