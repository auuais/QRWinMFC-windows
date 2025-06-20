#pragma once

#include <QrShared.hxx>
#include <QrROI.hxx>

namespace QrSDK
{
	/** Contrast Enhanced Mammography */
	typedef enum
	{
		CEM_NONE,		/**< None of CEM */
		CEM_LINEAR,		/**< Linear algorithm of CEM */
		CEM_HISTEQ		/**< Histogram Equalizaton algorithm of CEM */
	}QrCEM;

	/** Image output format */
	typedef enum
	{
		COLOR_BGR = 0,	/**< output to BRG format */
		COLOR_RGB = 1	/**< output to RGB format */
	}QrColor;

	typedef enum //_ColorMap
	{
		COLORMAP_NONE = -1,
		COLORMAP_AUTUMN = 0, //!< ![autumn](pics/colormaps/colorscale_autumn.jpg)
		COLORMAP_BONE = 1, //!< ![bone](pics/colormaps/colorscale_bone.jpg)
		COLORMAP_JET = 2, //!< ![jet](pics/colormaps/colorscale_jet.jpg)
		COLORMAP_WINTER = 3, //!< ![winter](pics/colormaps/colorscale_winter.jpg)
		COLORMAP_RAINBOW = 4, //!< ![rainbow](pics/colormaps/colorscale_rainbow.jpg)
		COLORMAP_OCEAN = 5, //!< ![ocean](pics/colormaps/colorscale_ocean.jpg)
		COLORMAP_SUMMER = 6, //!< ![summer](pics/colormaps/colorscale_summer.jpg)
		COLORMAP_SPRING = 7, //!< ![spring](pics/colormaps/colorscale_spring.jpg)
		COLORMAP_COOL = 8, //!< ![cool](pics/colormaps/colorscale_cool.jpg)
		COLORMAP_HSV = 9, //!< ![HSV](pics/colormaps/colorscale_hsv.jpg)
		COLORMAP_PINK = 10, //!< ![pink](pics/colormaps/colorscale_pink.jpg)
		COLORMAP_HOT = 11, //!< ![hot](pics/colormaps/colorscale_hot.jpg)
		COLORMAP_PARULA = 12, //!< ![parula](pics/colormaps/colorscale_parula.jpg)
		COLORMAP_MAGMA = 13, //!< ![magma](pics/colormaps/colorscale_magma.jpg)
		COLORMAP_INFERNO = 14, //!< ![inferno](pics/colormaps/colorscale_inferno.jpg)
		COLORMAP_PLASMA = 15, //!< ![plasma](pics/colormaps/colorscale_plasma.jpg)
		COLORMAP_VIRIDIS = 16, //!< ![viridis](pics/colormaps/colorscale_viridis.jpg)
		COLORMAP_CIVIDIS = 17, //!< ![cividis](pics/colormaps/colorscale_cividis.jpg)
		COLORMAP_TWILIGHT = 18, //!< ![twilight](pics/colormaps/colorscale_twilight.jpg)
		COLORMAP_TWILIGHT_SHIFTED = 19, //!< ![twilight shifted](pics/colormaps/colorscale_twilight_shifted.jpg)
		COLORMAP_TURBO = 20, //!< ![turbo](pics/colormaps/colorscale_turbo.jpg)
		COLORMAP_DEEPGREEN = 21  //!< ![deepgreen](pics/colormaps/colorscale_deepgreen.jpg)
	}QrColorMap;

	/// @brief QrImage stores and processes image buffers with color and contrast utilities.
	/// @details QrImage provides:
	///   - Raw data access via DataPtr()
	///   - Conversion to 3-channel bitmap with optional color map and channel order via ToBitmapData()
	///   - Emptiness check through IsEmpty()
	///   - Contrast enhancement methods (histogram equalization, linear scaling) via SetCEM()
	///   - Color mapping selection through SetColorMap()
	///   - Histogram computation over a specified intensity range via HistogramBins()
	class DLL_EXPORTS QrImage
	{
	public:
		QrImage();
		QrImage(void* src);
		virtual ~QrImage();
		unsigned char* DataPtr();
		unsigned char* ToBitmapData(QrColor color = QrColor::COLOR_BGR);
		/// <summary>
		/// Determines whether the image contains any valid image data.
		/// </summary>
		/// <returns>
		/// `true` if the internal Image8U pointer is null (indicating no data available);
		/// `false` otherwise.
		/// </returns>
		bool IsEmpty() { return Image8U == nullptr ? true : false; }
		bool SetCEM(QrCEM cem, double gain = 1.0, double offset = 0.0);
		bool SetColorMap(QrColorMap palette);
		std::vector<float> HistogramBins(int range_min, int range_max);

	public:
		int Width;
		int Height;
		int Channels;
		QrColorMap colormap = QrColorMap::COLORMAP_NONE;

	public:
		void* Image8U = nullptr;
		void* Image32U = nullptr;

	private:
	};
}



