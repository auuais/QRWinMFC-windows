#pragma once

#include <QrComponent.hxx>
#include <QrFrame.hxx>
#include <QrVideo.hxx>

#define QRVIDEO_ASYNC_WRITE

namespace QrSDK
{
	/// \brief Class for writing video files by encoding frames from QrFrame, QrImage, or raw buffers.
	/// \details QrVideoWriter provides:
	///   - Creating a video file with specified codec, frame rate, and resolution via Create(file, fps, width, height)
	///   - Writing frames from QrFrame or QrImage objects via Write(frame) and Write(image)
	///   - Writing raw 3-channel bitmap buffers via Write(bitmap, size)
	///   - Closing the video file and releasing resources via Close()
	///   - Querying whether the writer is open via IsOpen()
	///   - Getting and setting the writer state via State()
	class DLL_EXPORTS QrVideoWriter
	{
	public:
		QrVideoWriter();
		virtual ~QrVideoWriter();

		bool Create(std::string file, double fps, int width, int height);
		bool Close();
		bool Write(QrFrame& frame);
		bool Write(QrImage& image);
		bool Write(uint8_t* bitmap, QrSize size);
		bool IsOpen();
		QrVideoState State();
		QrVideoState State(QrVideoState state);

	public:
		double FPS;
		int Width;
		int Height;
		int FourCC;
		int Format;

	private:
		void* videoWriter = nullptr;
		int videoCodec = -1;
		QrVideoState state = QrVideoState::STOP;
	};
}
