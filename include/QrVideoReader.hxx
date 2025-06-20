#pragma once

#include <QrComponent.hxx>
#include <QrFrame.hxx>
#include <QrVideo.hxx>

namespace QrSDK
{
	/// \brief Class for reading video files and capturing frames into QrFrame or QrImage objects.
	/// \details QrVideoReader provides:
	///   - Opening and closing video sources via Open(file) and Close()
	///   - Capturing individual frames into QrFrame* or QrImage* via Read(...)
	///   - Querying whether the reader is open via IsOpen()
	///   - Getting and setting the playback state via State()
	class DLL_EXPORTS QrVideoReader
	{
	public:
		QrVideoReader();
		virtual ~QrVideoReader();

		bool Open(std::string file);
		bool Close();
		bool Read(QrFrame* qrFrame);
		bool Read(QrImage* qrImage);
		bool IsOpen();
		QrVideoState State();
		QrVideoState State(QrVideoState state);

	public:
		double FPS;
		int Width;
		int Height;
		int FourCC;
		int Format;
		int Frames;
		//int Channels;

	private:
		int videoCodec = -1;
		void* videoReader = nullptr;
		QrVideoState state = QrVideoState::STOP;
	};
}
