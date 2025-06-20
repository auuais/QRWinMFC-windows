#pragma once

#include <QrShared.hxx>
#include <QrFrame.hxx>

#include <QrROI.hxx>
#include <QrCameraEx.hpp>

#include <QrControl.hxx>
#include <QrFrameThread.hxx>


#if defined(_MSC_VER)
#elif defined(__GNUC__)
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#endif
namespace QrSDK
{
	/// @brief Represents a camera device with its display name and index.
	/// @details Used for enumerating and identifying available camera devices.
	///   - name: Camera device name.
	///   - num:  Zero-based index or identifier for opening the device.
	typedef struct _cam_dev
	{
		std::string name;
		std::string portName;
		int num;
		std::string instId;

	}tCamDev;

	typedef enum TEMP_UNIT : uint8_t
	{
		RAW = 0,
		CELSIUS = 1, 
		FAHRENHEIT = 2,
		KELVIN = 3
	} tTempUnit;

	using QrFramePtr = std::shared_ptr<QrFrame>;
    using ImageCallback = std::function<void(QrFramePtr)>;
    using ImageCallbackCtx = std::function<void(QrFramePtr, void*)>;

	/// @brief QrCamera is abstraction layer for connecting to and streaming from thermal cameras.
	///
	/// @details
	/// QrCamera offers a unified interface for both local and remote camera connections. 
	/// It supports:
	///  - Enumerating available video and serial ports
	///  - Opening, closing, and disconnecting camera streams
	///  - Reading and capturing frames with optional temperature-unit conversion
	///  - Resizing output frames
	///  - Loading calibration parameters by file and serial number
	///  - Configuring detailed flux parameters (emissivity, reflected temperature, distance,
	///    atmospheric conditions, lens temperature/transmittance)
	///  - Continuous acquisition via a background thread and event-driven callbacks
	///  - Registering and unregistering frame callbacks for asynchronous frame delivery
	///  - Starting and stopping acquisition mode at runtime
	///  - Loading calibration parameters from specified file paths or by serial number with USB drive auto-discovery
	/// Raw sensor data is converted into meaningful temperature values and delivered
	/// via QrFrame objects for further processing or display.
	class DLL_EXPORTS QrCamera
	{
	public:
		QrCamera();
		virtual ~QrCamera();

		static std::vector<tCamDev> GetCameraNames();
		static std::vector<std::string> GetSerialPorts();
		static std::vector<tCamDev> GetCameraList();
		/// <summary>
		/// Connect to the remote camera
		/// </summary>
		/// <param name="addr">Ip Address of the remote camera to connect.</param>
		/// <param name="port">Port number of the remote camera to connect
		/// Port number : 10603.</param>
		/// <returns>
		/// `true` if the underlying QrControl pointer is valid and the connection was successfully opened;  
		/// `false` otherwise (e.g., if the controller pointer is null or the connection attempt failed).
		/// </returns>
		virtual bool Connect(std::string url, int port) { return false; }
		/// <summary>
		/// Connect to the local camera
		/// </summary>
		/// <param name="index">Index of the local camera to connect.</param>
		/// <returns>
		/// `true` if the camera was successfully opened, configured, and validated;  
		/// `false` if the raw capture pointer is null or the camera fails to open,  
		/// </returns>
		virtual bool Connect(int index) { return false; }
		/// <summary>
		/// Disconnect the camera
		/// </summary>
		/// <returns>
		/// <c>true</c> if the camera was successfully released and disconnected;  
		/// <c>false</c> if an error occurred.
		/// </returns>
		virtual bool Disconnect() { return false; }
		virtual bool Open(std::string port);
		virtual bool Open(std::string addr, int port);
		virtual bool Close();
		/// <summary>
		/// Read frame data from the camera.
		/// </summary>
		/// <param name="qrFrame">Reference to a QrFrame object that will be filled with the captured frame data.</param>
		/// <param name="unit">Temperature unit to use when converting pixel values 
		/// (e.g., tTempUnit::RAW, tTempUnit::CELSIUS, tTempUnit::FAHRENHEIT, tTempUnit::KELVIN).</param>
		/// <returns>
		/// `true` if a non-empty frame was successfully read, processed, and stored in qrFrame;  
		/// `false` if the camera pointer is null, or no frame could be read.
		/// </returns>
		virtual bool Read(QrFrame& qrFrame, tTempUnit unit = tTempUnit::RAW) { return false; }
		/// <summary>
		/// Capture frame data from the camera.
		/// </summary>
		/// <param name="qrFrame">Reference to a QrFrame object that will be filled with the captured frame data.</param>
		/// <param name="unit">Temperature unit to use when converting pixel values 
		/// (e.g., tTempUnit::RAW, tTempUnit::CELSIUS, tTempUnit::FAHRENHEIT, tTempUnit::KELVIN).</param>
		/// <returns>
		/// `true` if a non-empty frame was successfully read, processed, and stored in qrFrame;  
		/// `false` if the camera pointer is null, or no frame could be read.
		/// </returns>
		virtual bool Capture(QrFrame& qrFrame, tTempUnit unit = tTempUnit::RAW) { return false; }
		virtual bool Resize(int width, int height);
		bool LoadCalibParams(std::string path, int gain = 0, std::string serialNumber = "");
		bool LoadCalibFile(std::string path, int gain = 0);
		bool LoadCalib(std::string serialNumber, int gain = 0);
		bool SetFluxParams(double objEmissivity,
			double reflectedTemp,
			double distance,
			double atmTemp,
			double relHumidity,
			double atmTransmittance,
			double opticTemp,
			double opticTransmittance);
		tTempUnit GetTempUnit();
		void SetTempUnit(tTempUnit unit);
        void RegisterEventHandler(ImageCallback handler);
        void RegisterEventHandler(ImageCallbackCtx handler, void* pContext);
		void UnregisterEventHandler();
		void BeginAcquisition();
		void EndAcquisition();
		void SetTriggerMode(bool mode);
		bool GetTriggerMode();
		void ExecuteSoftwareTrigger();
		void ResetTrigger();
		std::string GetCameraPosition(std::string serialNumber);
		std::string GetCameraPositionFile(std::string filePath);
		void SetCameraPosition(std::string serialNumber, std::string position);
		void SetCameraPositionFile(std::string filePath, std::string position);

	
	protected:
		bool GetTempFrame(QrFrame* qrFrame, tTempUnit unit = tTempUnit::RAW);

	public:
		bool IsConnect = false;
		int Width, Height;
		int Format;		// Codec Format
		int FourCC;
		int PixFmt;		// Pixel Format
		double FPS;

		QrControl qrControl;
		QrROI qrROI;

		bool Acquisition = false;
        ImageCallback Icb;
        ImageCallbackCtx IcbCtx;
		void* pContext = nullptr;
		tTempUnit TempUnit = tTempUnit::RAW;
		QrFrameThread* pQrFrameThread = nullptr;

	protected:
		int ActualWidth = 0, ActualHeight = 0;
	};
}

#include "QrLocalCamera.hxx"
#include "QrRemoteCamera.hxx"


