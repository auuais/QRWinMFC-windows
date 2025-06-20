#pragma once
#include <QrCore.hxx>
#include <QrCamera.hxx>
#include <QrCtrl.hxx>

#if defined(_MSC_VER)
#elif defined(__GNUC__)
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#endif

#define CTRL_SOCKET_BUFF_SIZE	64

namespace QrSDK
{
	class QrRemoteCtrl : public QrCtrl
	{
	private:
#if defined(_MSC_VER)
		SOCKET ctrlSocket = INVALID_SOCKET;
#elif defined(__GNUC__)
		unsigned int ctrlSocket = -1;
#endif
	public:
		QrRemoteCtrl();
		virtual ~QrRemoteCtrl();

		bool Open(std::string addr, int port) override;
		bool Close() override;

	private:
		int SendPacket(std::vector<uint8_t> packet);
		std::vector<std::string> ReceiveRemoteString();
		std::vector<uint8_t> ReceiveRemoteData();
		std::vector<uint8_t> ReceiveRemoteNetwork();


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
		/// \endcond HIDDEN_BLOCK
	};
}
