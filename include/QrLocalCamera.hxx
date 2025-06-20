#pragma once

#include <QrShared.hxx>
#include "QrCore.hxx"
#include "QrCamera.hxx"

#include <memory>

namespace QrSDK
{
	extern std::vector<tCamDev> listCam;

	/// @brief Local camera implementation using platform-specific backends (UVC/DirectShow/V4L2).
	/// @details QrLocalCamera extends QrCamera to provide:
	///   - Connecting to and disconnecting from a local camera by index
	///   - Reading and capturing frames with optional temperature-unit conversion
	///   - Override of the base class's Connect, Disconnect, Read, and Capture methods
	class DLL_EXPORTS QrLocalCamera : public QrCamera
	{
	public:
		QrLocalCamera();
		virtual ~QrLocalCamera();

		bool Connect(int index) override;
		bool Disconnect() override;
		bool Read(QrFrame& qrFrame, tTempUnit unit = tTempUnit::RAW) override;
		bool Capture(QrFrame& qrFrame, tTempUnit unit = tTempUnit::RAW) override;

	private:
		void* pCamera = nullptr;
	};
}

