#pragma once

#if defined(_MSC_VER)
#include <Windows.h>
#include <dshow.h>
#include <setupapi.h>
#include <winioctl.h>
#include <iostream>
#include <vector>
#include <string>
#pragma comment(lib, "strmiids")
#elif defined(__GNUC__)
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <iostream>
#endif

#include <map>
#include <string>

namespace QrSDK
{
	struct Device {
		int id; // This can be used to open the device in OpenCV
		std::string devicePath;
		std::string deviceName; // This can be used to show the devices to the user
		std::string deviceID;
		std::string deviceVID;
		std::string devicePID;
		std::string deviceInst;
	};

	struct DeviceNumber {
		DWORD deviceType;
		DWORD deviceNumber;
		DWORD partitionNumber;

		DeviceNumber(DWORD t, DWORD n, DWORD p)
			: deviceType(t), deviceNumber(n), partitionNumber(p) {
		}
	};

	struct UsbDiskInfo {
		std::string devicePath;
		DeviceNumber devNum;
		
		UsbDiskInfo(const std::string& path, const DeviceNumber& num)
			: devicePath(path), devNum(num) {
		}
	};

	class DeviceEnum {

	public:
		DeviceEnum() = default;
#if defined(_MSC_VER)
		std::map<int, Device> getDevicesMap(const GUID deviceClass);
#elif defined(__GNUC__)
		std::map<int, Device> getDevicesMap(const char* deviceClass);
#endif
		std::map<int, Device> getVideoDevicesMap();
		std::map<int, Device> getAudioDevicesMap();

		std::vector<UsbDiskInfo> EnumerateUsbDisks();
		std::vector<std::pair<char, std::string>> MapUsbDisksToLetters();

	private:

#if defined(_MSC_VER)
		std::string ConvertBSTRToMBS(BSTR bstr);
#elif defined(__GNUC__)
		std::string ConvertBSTRToMBS(char* bstr);
#endif
		std::string ConvertWCSToMBS(const wchar_t* pstr, long wslen);

	};
}
