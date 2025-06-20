#pragma once
#include <QrShared.hxx>
#include <QrProtocol.hxx>
#include <string>
#include <cstring>
#include <algorithm>
#include <map>
#include <regex>
#include <chrono>
#include <thread>

namespace QrSDK
{
	using namespace QrProtocol;

	class QrCtrl //: public QrProtocol
	{
		typedef struct QRPROPERTY
		{
			float TempFPA = 0.0f;
			float TempBody = 32.0f;
			float RefGain;
			float RefOffset;
			float EstTempCoeff1;
			float EstTempCoeff2;

			tGainMode GainMode = tGainMode::GAIN_HIGH;
			tHotMode HotMode = tHotMode::HOT_NONE;
			tAutoShutter AutoShutterMode;
			tTempConvert TempConvert;

			std::string strModel;
			std::string strProductVer;
			std::string strHardwareVer;
			std::string strSoftwareVer;
			std::string strProductSerial;
			std::string strSensorSerial;
			std::string strUseCase;
			std::string strDisplaySetting;
			std::string strHotMode;

			tIpMode netIpMode;
			uint8_t netIpAddress[4];
			uint8_t netMacAddress[6];
			uint8_t netGatewayAddress[4];
			uint8_t netSubnetMask[4];
			uint8_t netDnsAddress[4];

			int videoWidth = 0;
			int videoHeight = 0;
			int videoFPS = 0;
			std::string strVideoFormat;
		} QrProperty;

	public:
		tCmdDst cmdDest = CMD_DST::DST_EOST;	// DST_EOST;
		QrProperty qrProperty;

	public:
		QrCtrl();
		virtual ~QrCtrl();

		virtual bool Open(std::string port) { return false; }
		virtual bool Open(std::string addr, int port) { return false; }
		virtual bool Close() { return false; };

	public:
		bool IsOpen = false;

	public:
		std::vector<uint8_t> BuildPacket(tCmdSrc src, tCmdDst dst, uint8_t hdr, std::vector<uint8_t> payload);

#pragma region ICD SYSTEM COMMANDS
		/// <summary>
		/// Get All Information
		/// </summary>
		/// <returns></returns>
		virtual bool GetAllInform() = 0;
		virtual std::vector<uint8_t> txGetAllInform()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				CMD_DST::DST_EOST,
				0xF1,
				std::vector<uint8_t> {0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxGetAllInform(std::vector<std::string> list)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			if (list.empty()) return false;
			
			std::map<std::string, std::string> infoMap;

			std::regex regexPattern(R"(\[IPU1-0\]\s+(.*?)\s*:\s*(?:\[(.*?)\]|([^\[\]\r\n]+)))");
			std::smatch match;

			for (const auto& line : list)
			{
				if (std::regex_search(line, match, regexPattern))
				{
					if (match.size() >= 4)
					{
						std::string key = match[1];
						std::string value = match[2].matched ? match[2].str() : match[3].str();
						infoMap[key] = value;

						if (key == "QuantumRED Version")
						{
							qrProperty.strProductVer = value;
						}
						else if (key == "QuantumRED HW Version")
						{
							qrProperty.strHardwareVer = value;
						}
						else if (key == "QuantumRED SW Version")
						{
							qrProperty.strSoftwareVer = value;
						}
						else if (key == "QuantumRED BUILD Date")
						{
						}
						else if (key == "QuantumRED BUILD Time")
						{
						}
						else if (key == "QuantumRED Bootload Version")
						{
						}
						else if (key == "Product Serial Number")
						{
							qrProperty.strProductSerial = value;
						}
						else if (key == "Sensor Serial Number")
						{
							qrProperty.strSensorSerial = value;
						}
					}
				}
			}

			return true;
		}
		/// <summary>
		/// GetModel
		/// </summary>
		/// <returns></returns>
		virtual bool GetModel() = 0;
		virtual std::vector<uint8_t> txGetModel()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				CMD_DST::DST_BOTH,
				0xF4,
				std::vector<uint8_t> {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxGetModel(std::vector<std::uint8_t> list)
		{
			if (list.empty()) return false;
			if (list[1] == 0x03) {
				qrProperty.strModel = "EOST";
			}
			else if (list[1] == 0x06) {
				qrProperty.strModel = "SURV";
			}
			else
			{
				qrProperty.strModel = "UNKNOWN";
			}

			return true;
		}
		/// <summary>
		/// GetProductionSerial
		/// </summary>
		/// <returns></returns>
		virtual bool GetProductVersion() = 0;
		virtual std::vector<uint8_t> txGetProductVersion()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xF1,
				std::vector<uint8_t> {0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxGetProductVersion(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			std::stringstream ss;
			for (auto it = list.begin() + 1; it != list.begin() + 4; ++it) {
				if (it != list.begin() + 1) {
					ss << ".";
				}
				ss << static_cast<char>(*it);
			}
			qrProperty.strProductVer = ss.str();
			return true;
		}
		/// <summary>
		/// GetHardwareVersion
		/// </summary>
		/// <returns></returns>
		virtual bool GetHardwareVersion() = 0;
		virtual std::vector<uint8_t> txGetHardwareVersion()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xF1,
				std::vector<uint8_t> {0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxGetHardwareVersion(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			std::stringstream ss;
			for (auto it = list.begin() + 1; it != list.begin() + 3; ++it) {
				if (it != list.begin() + 1) {
					ss << ".";
				}
				ss << static_cast<char>(*it);
			}
			qrProperty.strHardwareVer = ss.str();
			return true;
		}
		/// <summary>
		/// GetSoftwareVersion
		/// </summary>
		/// <returns></returns>
		virtual bool GetSoftwareVersion() = 0;
		virtual std::vector<uint8_t> txGetSoftwareVersion()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xF1,
				std::vector<uint8_t> {0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxGetSoftwareVersion(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			std::stringstream ss;
			for (auto it = list.begin() + 1; it != list.begin() + 4; ++it) {
				if (it != list.begin() + 1) {
					ss << ".";
				}
				ss << static_cast<char>(*it);
			}
			qrProperty.strSoftwareVer = ss.str();
			return true;
		}
		/// <summary>
		/// GetSensorSerial
		/// </summary>
		/// <returns></returns>
		virtual bool GetSensorSerial() = 0;
		virtual std::vector<uint8_t> txGetSensorSerial()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xF1,
				std::vector<uint8_t>{ 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxGetSensorSerial(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;

			uint32_t intBits;
			std::memcpy(&intBits, list.data() + 1, sizeof(uint32_t));
			qrProperty.strSensorSerial = std::to_string(intBits);
			return true;
		}
		/// <summary>
		/// GetProductSerial
		/// </summary>
		/// <returns></returns>
		virtual bool GetProductSerial() = 0;
		virtual std::vector<uint8_t> txGetProductSerialChar()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xF1,
				std::vector<uint8_t>{ 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxGetProductSerialChar(std::vector<std::uint8_t> list)
		{
			if (list.empty()) return false;


			std::string str(list.begin() + 1, list.begin() + 5);
			qrProperty.strProductSerial = str;
	
			return true;
		}
		virtual std::vector<uint8_t> txGetProductSerialNum()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xF1,
				std::vector<uint8_t>{ 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxGetProductSerialNum(std::vector<std::uint8_t> list)
		{
			if (list.empty()) return false;


			std::string str(list.begin() + 1, list.begin() + 5);
			uint32_t intBits;
			std::memcpy(&intBits, list.data() + 1, sizeof(uint32_t));
			qrProperty.strProductSerial = qrProperty.strProductSerial  + std::to_string(intBits);

			return true;
		}
		/// <summary>
		/// SetAutoShutter
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		virtual bool SetAutoShutter(const tAutoShutter val) = 0;
		virtual std::vector<uint8_t> txSetAutoShutter(const tAutoShutter val)
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xA6,
				std::vector<uint8_t>{ val, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxSetAutoShutter(std::vector<std::uint8_t> list)
		{
			if (list.empty()) return false;

			return true;
		}
		/// <summary>
		/// GetAutoShutter
		/// </summary>
		/// <returns></returns>
		virtual bool GetAutoShutter() = 0;
		virtual std::vector<uint8_t> txGetAutoShutter()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xA7,
				std::vector<uint8_t>{ 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxGetAutoShutter(std::vector<std::uint8_t> list)
		{
			if (list.empty()) return false;

			if (list[1] == 0x00) {
				qrProperty.AutoShutterMode = AUTO_SHUTTER::SHUTTER_OFF;
			}
			else {
				qrProperty.AutoShutterMode = AUTO_SHUTTER::SHUTTER_ON;
			}
			return true;
		}
		/// <summary>
		/// SetShutterControl
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		virtual bool SetShutterControl(const tCtrlShutter arg) = 0;
		virtual std::vector<uint8_t> txSetAutoShutter(const tCtrlShutter arg)
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xA8,
				std::vector<uint8_t>{ arg, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxSetShutterControl(std::vector<std::uint8_t> list)
		{
			if (list.empty()) return false;

			bool ret = false;
			return ret;
		}
		/// <summary>
		/// SetSystemReboot
		/// </summary>
		/// <returns></returns>
		virtual bool SetSystemReboot() = 0;
		virtual std::vector<uint8_t> txSetSystemReboot()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xF3,
				std::vector<uint8_t>{ 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxSetSystemReboot(std::vector<std::string> list)
		{
			if (list.empty()) return false;

			bool ret = false;
			return ret;
		}
		virtual bool rxSetSystemReboot(std::vector<std::uint8_t> list)
		{
			if (list.empty()) return false;

			bool ret = true;
			return ret;
		}
		/// <summary>
		/// GetSystemSetting
		/// </summary>
		/// <returns></returns>
		virtual bool GetSystemSetting() = 0;
		virtual std::vector<uint8_t> txGetSystemSetting()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xF5,
				std::vector<uint8_t> {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxGetSystemSetting(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;

			switch (list[0]) {
			case 1:
				qrProperty.strUseCase = "Estimated [Skin] Temperature";
				break;
			case 3:
				qrProperty.strUseCase = "Estimated [Object] Temperature";
				break;
			case 5:
				qrProperty.strUseCase = "Estimated [Factory Mode] with [CameraLink Board]";
				break;
			case 6:
				qrProperty.strUseCase = "[Factory Mode] with [USB Board]";
				break;
			}
			switch (list[1]) {
			case 0x13:
				qrProperty.strDisplaySetting = "QVGA 30fps";
				break;
			case 0x14:
				qrProperty.strDisplaySetting = "VGA 30fps";
				break;
			case 0x01:
				qrProperty.strDisplaySetting = "Analog NTSC";
				break;
			case 0x02:
				qrProperty.strDisplaySetting = "Analog PAL";
				break;
			case 0x1A:
				qrProperty.strDisplaySetting = "QVGA BT656";
				break;
			case 0x1B:
				qrProperty.strDisplaySetting = "VGA BT656";
				break;
			case 0x1C:
				qrProperty.strDisplaySetting = "QVGA BT1120";
				break;
			case 0x1D:
				qrProperty.strDisplaySetting = "VGA BT1120";
				break;
			}
			return true;
		}
		/// <summary>
		/// GetTempFPA
		/// </summary>
		/// <returns></returns>
		virtual bool GetTempFPA() = 0;
		virtual std::vector<uint8_t> txGetTempFPA()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xF4,
				std::vector<uint8_t> {0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxGetTempFPA(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			uint32_t fpa;
			std::memcpy(&fpa, list.data() + 1, sizeof(uint32_t));
			qrProperty.TempFPA = (float)fpa;

			return true;
		}
		/// <summary>
		/// GetTempBody
		/// </summary>
		/// <returns></returns>
		virtual bool GetTempBody() = 0;
		virtual std::vector<uint8_t> txGetTempBody()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xF4,
				std::vector<uint8_t> {0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxGetTempBody(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			uint32_t body;
			std::memcpy(&body, list.data() + 1, sizeof(uint32_t));
			qrProperty.TempBody = (float)((body * 165.0f) / 65535 - 40);
			return true;
		}
		/// <summary>
		/// GetRefGain
		/// </summary>
		/// <returns></returns>
		virtual bool GetRefGain() = 0;
		virtual std::vector<uint8_t> txGetRefGain()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xB8,
				std::vector<uint8_t> {	(uint8_t)(qrProperty.GainMode == GAIN_MODE::GAIN_HIGH ? 0x01 : 0x05),
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxGetRefGain(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			uint32_t floatBits;
			std::memcpy(&floatBits, list.data() + 1, sizeof(uint32_t));
			std::memcpy(&qrProperty.RefGain, &floatBits, sizeof(float));

			return true;
		}
		/// <summary>
		/// GetRefOffset
		/// </summary>
		/// <returns></returns>
		virtual bool GetRefOffset() = 0;
		virtual std::vector<uint8_t> txGetRefOffset()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xB8,
				std::vector<uint8_t> {	(uint8_t)(qrProperty.GainMode == GAIN_MODE::GAIN_HIGH ? 0x02 : 0x06),
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxGetRefOffset(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			uint32_t floatBits;
			std::memcpy(&floatBits, list.data() + 1, sizeof(uint32_t));
			std::memcpy(&qrProperty.RefOffset, &floatBits, sizeof(float));

			return true;
		}
		/// <summary>
		/// GetTepCoeff1
		/// </summary>
		/// <returns></returns>
		virtual bool GetTempCoeff1() = 0;
		virtual std::vector<uint8_t> txGetTempCoeff1()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xB8,
				std::vector<uint8_t> {	(uint8_t)(qrProperty.GainMode == GAIN_MODE::GAIN_HIGH ? 0x03 : 0x07),
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxGetTempCoeff1(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			uint32_t floatBits;
			std::memcpy(&floatBits, list.data() + 1, sizeof(uint32_t));
			std::memcpy(&qrProperty.EstTempCoeff1, &floatBits, sizeof(float));

			return true;
		}
		/// <summary>
		/// GetTempCoeff2
		/// </summary>
		/// <returns></returns>
		virtual bool GetTempCoeff2() = 0;
		virtual std::vector<uint8_t> txGetTempCoeff2()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xB8,
				std::vector<uint8_t> {	(uint8_t)(qrProperty.GainMode == GAIN_MODE::GAIN_HIGH ? 0x04 : 0x08),
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxGetTempCoeff2(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			uint32_t floatBits;
			std::memcpy(&floatBits, list.data() + 1, sizeof(uint32_t));
			std::memcpy(&qrProperty.EstTempCoeff2, &floatBits, sizeof(float));

			return true;
		}

		/// <summary>
		/// Set 1P NUC
		/// </summary>
		/// <returns></returns>
		virtual bool Set1pNUC() = 0;
		virtual std::vector<uint8_t> txSet1pNUC()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xD0,
				std::vector<uint8_t>{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxSet1pNUC(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;

			bool ret = false;
			return ret;
		}
		/// <summary>
		/// Set ViewMode
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		virtual bool SetViewMode(tViewMode arg) = 0;
		virtual std::vector<uint8_t> txSetViewMode(tViewMode arg)
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xD1,
				std::vector<uint8_t> {0x00, arg, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxSetViewMode(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;

			bool ret = true;
			return ret;
		}
		/// <summary>
		/// Set TEC
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		virtual bool SetTEC(tCtrlTEC arg) = 0;
		virtual std::vector<uint8_t> txSetTEC(tCtrlTEC arg)
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xD1,
				std::vector<uint8_t> {0x00, arg, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxSetTEC(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;

			bool ret = true;
			return ret;
		}
		/// <summary>
		/// Set DPC
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		virtual bool SetDPC(tCtrlDPC arg) = 0;
		virtual std::vector<uint8_t> txSetDPC(tCtrlDPC arg)
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xD0,
				std::vector<uint8_t> {0x01, arg, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxSetDPC(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;

			bool ret = true;
			return ret;
		}
		/// <summary>
		/// Set 2nd Compensation
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		virtual bool Set2ndComp(tCtrlComp arg) = 0;
		virtual std::vector<uint8_t> txSet2ndComp(tCtrlComp arg)
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xD0,
				std::vector<uint8_t> {arg, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxSet2ndComp(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;

			bool ret = true;
			return ret;
		}
		/// <summary>
		/// Set Temp Converter
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		virtual bool SetTempConvert(tTempConvert arg) = 0;
		virtual std::vector<uint8_t> txSetTempConvert(tTempConvert arg)
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xDA,
				std::vector<uint8_t> {0x01, arg, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxSetTempConvert(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;

			bool ret = true;
			return ret;
		}
		/// <summary>
		/// Set Shutter Compensation
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		virtual bool SetShutterComp(tShutterComp arg) = 0;
		virtual std::vector<uint8_t> txSetShutterComp(tShutterComp arg)
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xDA,
				std::vector<uint8_t> {0x00, arg, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxSetShutterComp(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;

			bool ret = true;
			return ret;
		}
		/// <summary>
		/// Set Image Out
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		virtual bool SetImageOut(tImageOut arg) = 0;
		virtual std::vector<uint8_t> txSetImageOut(tImageOut arg)
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xD4,
				std::vector<uint8_t> {arg, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxSetImageOut(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;

			bool ret = true;
			return ret;
		}
		/// <summary>
		/// Set Hot Mode
		/// </summary>
		/// <param name="arg"></param>
		/// <returns></returns>
		virtual bool SetHotMode(tHotMode arg) = 0;
		virtual std::vector<uint8_t> txSetHotMode(tHotMode arg)
		{
			uint8_t val = arg + 1;
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xD4,
				std::vector<uint8_t> {val, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxSetHotMode(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			//qrProperty.HotMode = list[1];
			return true;
		}
		/// <summary>
		/// Get Hot Mode
		/// </summary>
		/// <returns></returns>
		virtual bool GetHotMode() = 0;
		virtual std::vector<uint8_t> txGetHotMode()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xD4,
				std::vector<uint8_t> {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
		}
		virtual bool rxGetHotMode(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			qrProperty.HotMode = (tHotMode)list[1];
			return true;
		}
		/// <summary>
		/// Get Gain Mode
		/// </summary>
		/// <returns></returns>
		virtual bool GetGainMode() = 0;
		virtual std::vector<uint8_t> txGetGainMode()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xB2,
				std::vector<uint8_t>{ 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxGetGainMode(std::vector<std::uint8_t> list)
		{
			if (list.empty()) return false;
			if (list[1] == 0) {
				qrProperty.GainMode = GAIN_MODE::GAIN_HIGH;
			}
			else {
				qrProperty.GainMode = GAIN_MODE::GAIN_LOW;
			}
			return true;
		}
		/// <summary>
		/// Set Gain Mode
		/// </summary>
		/// <param name="gain"></param>
		/// <returns></returns>
		virtual bool SetGainMode(const tGainMode gain) = 0;
		virtual std::vector<uint8_t> txSetGainMode(const tGainMode gain)
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xB2,
				std::vector<uint8_t> { 0x01, gain, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxSetGainMode(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;

			bool ret = true;
			return ret;
		}
		/// <summary>
		/// Set TRSM Reference Temperature
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		virtual bool SetTrsmRefTemp(const uint16_t val) = 0;
		virtual std::vector<uint8_t> txSetTrsmRefTemp(const uint16_t val)
		{
			unsigned char* p = (unsigned char*)&val;
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xD6,
				std::vector<uint8_t>{ 0x11, 0x01, p[0], p[1], 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxSetTrsmRefTemp(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;

			bool ret = true;
			return ret;
		}
		/// <summary>
		/// Set TRSM Compensation
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		virtual bool SetTrsmComp(const tTrsmComp val) = 0;
		virtual std::vector<uint8_t> txSetTrsmComp(const tTrsmComp val)
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xD6,
				std::vector<uint8_t>{ val, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxSetTrsmComp(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;

			bool ret = true;
			return ret;
		}
		/// <summary>
		/// Set TRSM Guide
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		virtual bool SetTrsmGuide(const tTrsmGuide val) = 0;
		virtual std::vector<uint8_t> txSetTrsmGuide(const tTrsmGuide val)
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xD6,
				std::vector<uint8_t>{ 0x00, val, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxSetTrsmGuide(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;

			bool ret = true;
			return ret;
		}
		/// <summary>
		/// Set TRSM Guide Save
		/// </summary>
		/// <returns></returns>
		virtual bool SetTrsmGuideSave() = 0;
		virtual std::vector<uint8_t> txSetTrsmGuideSave()
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xD6,
				std::vector<uint8_t>{ 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxSetTrsmGuideSave(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;

			bool ret = true;
			return ret;
		}
		/// <summary>
		/// Set TRSM GuideTo
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		virtual bool SetTrsmGuideTo(const tTrsmGuideTo val) = 0;
		virtual std::vector<uint8_t> txSetTrsmGuideDir(const tTrsmGuideTo val)
		{
			return BuildPacket(CMD_SRC::SRC_PACKET,
				cmdDest,
				0xD6,
				std::vector<uint8_t>{ 0x01, val, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxSetTrsmGuideTo(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;

			bool ret = true;
			return ret;
		}
#pragma endregion

#pragma region ICD NETWORK COMMANDS
		/// <summary>
		/// Assert Reboot to network
		/// </summary>
		/// <returns></returns>
		virtual bool SetNetworkReboot() = 0;
		virtual std::vector<uint8_t> txSetNetworkReboot()
		{
			return BuildPacket(CMD_SRC::SRC_OTHER,
				CMD_DST::DST_NETWORK,
				0x01,
				std::vector<uint8_t>{ 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxSetNetworkReboot(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			return true;
		}
		/// <summary>
		/// Get Ip Mdoe
		/// </summary>
		/// <returns></returns>
		virtual bool GetIpMode() = 0;
		virtual std::vector<uint8_t> txGetIpMode()
		{
			return BuildPacket(CMD_SRC::SRC_OTHER,
				CMD_DST::DST_NETWORK,
				0x00,
				std::vector<uint8_t>{ 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxGetIpMode(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			qrProperty.netIpMode = (tIpMode)list[0];
			return true;
		}
		/// <summary>
		///  Set Ip Mdoe
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		virtual bool SetIpMode(const tIpMode val) = 0;
		virtual std::vector<uint8_t> txSetIpMode(const tIpMode val)
		{
			return BuildPacket(CMD_SRC::SRC_OTHER,
				CMD_DST::DST_NETWORK,
				0x01,
				std::vector<uint8_t>{ val, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxSetIpMode(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			return true;
		}
		/// <summary>
		/// Get IP Address
		/// </summary>
		/// <returns></returns>
		virtual bool GetIpAddress() = 0;
		virtual std::vector<uint8_t> txGetIpAddress()
		{
			return BuildPacket(CMD_SRC::SRC_OTHER,
				CMD_DST::DST_NETWORK,
				0x00,
				std::vector<uint8_t>{ 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxGetIpAddress(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			std::copy_n(list.begin(), sizeof(qrProperty.netIpAddress), qrProperty.netIpAddress);
			return true;
		}
		/// <summary>
		/// Get MAC address
		/// </summary>
		/// <returns></returns>
		virtual bool GetMacAddress() = 0;
		virtual std::vector<uint8_t> txGetMacAddress()
		{
			return BuildPacket(CMD_SRC::SRC_OTHER,
				CMD_DST::DST_NETWORK,
				0x00,
				std::vector<uint8_t>{ 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxGetMacAddress(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			std::copy_n(list.begin(), sizeof(qrProperty.netMacAddress), qrProperty.netMacAddress);
			return true;
		}
		/// <summary>
		/// Get Gateway Address
		/// </summary>
		/// <returns></returns>
		virtual bool GetGatewayAddress() = 0;
		virtual std::vector<uint8_t> txGetGatewayAddress()
		{
			return BuildPacket(CMD_SRC::SRC_OTHER,
				CMD_DST::DST_NETWORK,
				0x00,
				std::vector<uint8_t>{ 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxGetGatewayAddress(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			std::copy_n(list.begin(), sizeof(qrProperty.netGatewayAddress), qrProperty.netGatewayAddress);
			return true;
		}
		/// <summary>
		/// Get Subnet Mask
		/// </summary>
		/// <returns></returns>
		virtual bool GetSubnetMask() = 0;
		virtual std::vector<uint8_t> txGetSubnetMask()
		{
			return BuildPacket(CMD_SRC::SRC_OTHER,
				CMD_DST::DST_NETWORK,
				0x00,
				std::vector<uint8_t>{ 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxGetSubnetMask(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			std::copy_n(list.begin(), sizeof(qrProperty.netSubnetMask), qrProperty.netSubnetMask);
			return true;
		}
		/// <summary>
		/// Get DNS Address
		/// </summary>
		/// <returns></returns>
		virtual bool GetDnsAddress() = 0;
		virtual std::vector<uint8_t> txGetDnsAddress()
		{
			return BuildPacket(CMD_SRC::SRC_OTHER,
				CMD_DST::DST_NETWORK,
				0x00,
				std::vector<uint8_t>{ 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxGetDnsAddress(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			std::copy_n(list.begin(), sizeof(qrProperty.netDnsAddress), qrProperty.netDnsAddress);
			return true;
		}
		/// <summary>
		/// Set IP Address
		/// </summary>
		/// <param name="addr"></param>
		/// <returns></returns>
		virtual bool SetIpAddress(const std::vector<uint8_t> addr) = 0;
		virtual std::vector<uint8_t> txSetIpAddress(const std::vector<uint8_t> addr)
		{
			return BuildPacket(CMD_SRC::SRC_OTHER,
				CMD_DST::DST_NETWORK,
				0x01,
				std::vector<uint8_t>{ 0x02, addr[0], addr[1], addr[2], addr[3], 0x00, 0x00, 0x00 });
		}
		virtual bool rxSetIpAddress(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			return true;
		}
		/// <summary>
		/// Set Gateway Address
		/// </summary>
		/// <param name="addr"></param>
		/// <returns></returns>
		virtual bool SetGatewayAddress(const std::vector<uint8_t> addr) = 0;
		virtual std::vector<uint8_t> txSetGatewayAddress(const std::vector<uint8_t> addr)
		{
			return BuildPacket(CMD_SRC::SRC_OTHER,
				CMD_DST::DST_NETWORK,
				0x01,
				std::vector<uint8_t>{ 0x03, addr[0], addr[1], addr[2], addr[3], 0x00, 0x00, 0x00 });
		}
		virtual bool rxSetGatewayAddress(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			return true;
		}
		/// <summary>
		/// Set Subnet Mask
		/// </summary>
		/// <param name="mask"></param>
		/// <returns></returns>
		virtual bool SetSubnetMask(const std::vector<uint8_t> mask) = 0;
		virtual std::vector<uint8_t> txSetSubnetMask(const std::vector<uint8_t> mask)
		{
			return BuildPacket(CMD_SRC::SRC_OTHER,
				CMD_DST::DST_NETWORK,
				0x01,
				std::vector<uint8_t>{ 0x04, mask[0], mask[1], mask[2], mask[3], 0x00, 0x00, 0x00 });
		}
		virtual bool rxSetSubnetMask(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			return true;
		}
		/// <summary>
		/// Set DNS Address
		/// </summary>
		/// <param name="addr"></param>
		/// <returns></returns>
		virtual bool SetDnsAddress(const std::vector<uint8_t> addr) = 0;
		virtual std::vector<uint8_t> txSetDnsAddress(const std::vector<uint8_t> addr)
		{
			return BuildPacket(CMD_SRC::SRC_OTHER,
				CMD_DST::DST_NETWORK,
				0x01,
				std::vector<uint8_t>{ 0x05, addr[0], addr[1], addr[2], addr[3], 0x00, 0x00, 0x00 });
		}
		virtual bool rxSetDnsAddress(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;
			return true;
		}
#pragma endregion

#pragma region ICD VIDEO COMMANDS
		/// <summary>
		/// Get Video Resolution
		/// </summary>
		/// <returns></returns>
		virtual bool GetVideoResolution() = 0;
		virtual std::vector<uint8_t> txGetVideoResolution()
		{
			return BuildPacket(CMD_SRC::SRC_OTHER,
				CMD_DST::DST_VIDEO,
				0x00,
				std::vector<uint8_t>{ 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxGetVideoResolution(std::vector<uint8_t> list)
		{
			if (list.empty()) return false;

			qrProperty.videoWidth = (int)(((int)list[0] & 0xFF) << 8) + ((int)list[1] & 0xFF);
			qrProperty.videoHeight = (int)(((int)list[2] & 0xFF) << 8) + ((int)list[3] & 0xFF);
			return true;
		}
		/// <summary>
		/// Get Video FPS
		/// </summary>
		/// <returns></returns>
		virtual bool GetVideoFPS() = 0;
		virtual std::vector<uint8_t> txGetVideoFPS()
		{
			return BuildPacket(CMD_SRC::SRC_OTHER,
				CMD_DST::DST_VIDEO,
				0x00,
				std::vector<uint8_t>{ 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxGetVideoFPS(std::vector<uint8_t> list)
		{
			if (list.empty())	return false;
			qrProperty.videoFPS = list[0];
			return true;
		}
		/// <summary>
		/// Get Video Format
		/// </summary>
		/// <returns></returns>
		virtual bool GetVideoFormat() = 0;
		virtual std::vector<uint8_t> txGetVideoFormat()
		{
			return BuildPacket(CMD_SRC::SRC_OTHER,
				CMD_DST::DST_VIDEO,
				0x00,
				std::vector<uint8_t> { 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
		}
		virtual bool rxGetVideoFormat(std::vector<uint8_t> list)
		{
			if (list.empty())	return false;
			qrProperty.strVideoFormat = list[0] == 0 ? "Y16" : "YUV";
			return true;
		}
#pragma endregion
	};
}
