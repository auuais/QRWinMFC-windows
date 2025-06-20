#pragma once
//#include <QrCore.hxx>
//#include <QrCamera.hxx>
#include <QrFrame.hxx>

#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

namespace QrSDK
{
	class QrCamera;

	class QrFrameThread
	{
	public:
		QrFrameThread(QrCamera* pCamera);
		~QrFrameThread();
		void Start();
		void Stop();
		void Join();
		bool IsRunning() const;
		void SetTriggerMode(bool mode);
		bool GetTriggerMode();
		void ExecuteSoftwareTrigger();
		void ResetTrigger();

	private:
		void Run();

	private:
		std::atomic<bool> Running{ false };
		std::thread Thread;
		QrCamera* pQrCamera = nullptr;
		std::atomic<bool> TriggerMode{ false };
		std::atomic<bool> ExeTrigger{ false };
	};
}