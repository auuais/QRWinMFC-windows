#pragma once
#include <QrShared.hxx>
//#include <QrCore.hxx>
#include <QrCtrl.hxx>
#include <QrProtocol.hxx>
#include <string>
#if defined(_MSC_VER)
#elif defined(__GNUC__)
#include <math.h>
#endif

namespace QrSDK
{
	using namespace std;

    /// @brief QrControl is an interface for configuring and querying camera control settings.
    ///
    /// @details QrControl provides methods to:
    ///  - Retrieve device information: model, hardware/software versions, serial numbers
	///  - Configure imaging parameters: auto shutter, shutter control, DPC, TEC, view mode
	///  - Manage temperature conversion & calibration: sensor FPA/body temps, gain/offset, NUC
	///  - Control system functions: reboot, network settings (IP, gateway, DNS, MAC), display settings
	///  - Query and set video output parameters: resolution, frame rate, and format
 
	class DLL_EXPORTS QrControl
	{
	public:
		QrControl() {};
		virtual ~QrControl() {};

	public:
		QrCtrl* pQrCtrl = nullptr;

	public:
		#pragma region MEMBER METHODS

		///////  View Control
		// Config Setting
		bool GetAllInform();
		bool GetModel();
		bool GetProductVersion();
		bool GetHardwareVersion();
		bool GetSoftwareVersion();
		bool GetProductSerial();
		bool GetSensorSerial();

		bool SetAutoShutter(tAutoShutter arg);
		bool GetAutoShutter();
		bool SetShutterControl(tCtrlShutter arg);
		bool SetSystemReboot();
		bool GetSystemSetting();

		bool GetTempFPA();
		bool GetTempBody();
		bool GetRefGain();
		bool GetRefOffset();
		bool GetTempCoeff1();
		bool GetTempCoeff2();

		// App Setting
		bool Set1pNUC();
		bool SetViewMode(tViewMode arg);
		bool SetTEC(tCtrlTEC arg);
		bool SetDPC(tCtrlDPC arg);
		bool Set2ndComp(tCtrlComp arg);
		bool SetShutterComp(tShutterComp arg);
		bool SetTempConvert(tTempConvert arg);
		bool SetImageOut(tImageOut arg);
		bool SetHotMode(tHotMode arg);
		bool GetHotMode();
		bool SetGainMode(tGainMode arg);
		bool GetGainMode();

		// TRSM Control
		bool SetTrsmRefTemp(uint16_t arg);
		bool SetTrsmComp(tTrsmComp arg);
		bool SetTrsmGuide(tTrsmGuide arg);
		bool SetTrsmGuideSave();
		bool SetTrsmGuideTo(tTrsmGuideTo arg);
		
		bool SetNetworkReboot();
		bool GetMacAddress();
		bool GetIpMode();
		bool SetIpMode(tIpMode arg);
		bool GetIpAddress();
		bool SetIpAddress(std::vector<uint8_t> arg);
		bool GetGatewayAddress();
		bool SetGatewayAddress(std::vector<uint8_t> arg);
		bool GetSubnetMask();
		bool SetSubnetMask(std::vector<uint8_t> arg);
		bool GetDnsAddress();
		bool SetDnsAddress(std::vector<uint8_t> arg);
		
		bool GetVideoResolution();
		bool GetVideoFPS();
		bool GetVideoFormat();
		#pragma region

		#pragma region MEMBER DATA

		std::string Model();
		std::string ProductVersion();
		std::string HardwareVersion();
		std::string SoftwareVersion();
		std::string ProductSerial();
		std::string SensorSerial();
		std::string UseCase();
		tAutoShutter AutoShutter();
		tHotMode HotMode();
		float RefGain();
		float RefOffset();
		float EstTempCoeff1();
		float EstTempCoeff2();
		std::string DisplaySetting();
		tAutoShutter AutoShutterMode();
		std::string HotModeStr();
		tGainMode GainMode();
		float TempFPA();
		float TempBody();
		tIpMode IpMode();
		uint8_t* IpAddress();
		uint8_t* MacAddress();
		uint8_t* GatewayAddress();
		uint8_t* SubnetMask();
		uint8_t* DnsAddress();
		int VideoWidth();
		int VideoHeight();
		int VideoFPS();
		std::string VideoFormat();

		#pragma region
	};
}
