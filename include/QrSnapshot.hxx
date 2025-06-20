#pragma once

//#include <QrTypes.hxx>
#include <QrFrame.hxx>
#include <QrImage.hxx>

namespace QrSDK
{
	/// \brief Provides utilities for saving and loading snapshots of frames and images.
	/// \details QrSnapshot supports:
	///   - Saving a region of a QrFrame to an image file via Save(path, frame, rect)
	///   - Saving a region of a QrImage to an image file via Save(path, image, rect)
	///   - Saving a raw 3-channel bitmap buffer to an image file via Save(path, bitmap, size)
	///   - Loading an image file into a QrFrame (16-bit data) via Load(path, frame)
	///   - Loading an image file into a QrImage (1- or 3-channel data) via Load(path, image)
	class DLL_EXPORTS QrSnapshot
	{
	public:
		QrSnapshot() {};
		virtual ~QrSnapshot() {};

		bool Save(std::string path, QrFrame& frame, QrRect rect = QrRect());
		bool Save(std::string path, QrImage& image, QrRect rect = QrRect());
		bool Save(std::string path, uint8_t* bitmap, QrSize size);
		bool Load(std::string path, QrFrame* frame);
		bool Load(std::string path, QrImage* image);
	};
}
