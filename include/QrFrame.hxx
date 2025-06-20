#pragma once

#include <QrShared.hxx>
#include <QrROI.hxx>
#include <QrImage.hxx>

namespace QrSDK
{
	/// @brief QrFrame represents a captured camera frame and provides image/temperature utilities.
	/// @details QrFrame offers:
	///   - Raw data access via DataPtr()
	///   - Image conversion and normalization with QueryImage(QrImage& qrImage)
	///   - Pixel value statistics using MinMaxLoc() and HistogramBins()
	///   - Temperature conversion methods: GetTempAsKelvin(), GetTempAsCelsius(), GetTempAsFahrenheit()
	///   - ROI measurement support through MeasureROI()
	///   - Frame emptiness check via IsEmpty()
	class DLL_EXPORTS QrFrame
	{

	public:
		QrFrame();
		QrFrame(const QrFrame& other);
		QrFrame& operator=(const QrFrame& other);
		QrFrame& operator=(QrFrame&& other) noexcept;
		virtual ~QrFrame();

		unsigned char* DataPtr();	// get raw data
		bool QueryImage(QrImage& qrImage);
		
		bool MinMaxLoc(const QrRect rect, double* minVal, double* maxVal, QrPoint* minLoc, QrPoint* maxLoc);
		bool HistogramBins(int min, int max);

		float GetTempAsKelvin(unsigned short raw);
		float GetTempAsCelsius(unsigned short raw);
		float GetTempAsFahrenheit(unsigned short raw);
		/// <summary>
		/// Determines whether the frame contains any valid image data.
		/// </summary>
		/// <returns>
		/// `true` if the internal rawFrame pointer is null (indicating no data available);
		/// `false` otherwise.
		/// </returns>
		bool IsEmpty() { return rawFrame == nullptr ? true : false; }

		bool MeasureROI(QrROI& qrROI);

		//bool AssertException();

		//QrROI qrROI;

	public:
		int Width = -1, Height = -1;
		int ActualWidth = -1, ActualHeight = -1;
		int Length = -1;

		void* rawFrame = nullptr;
	};
}

