#pragma once

#include <QrComponent.hxx>
#if defined(_MSC_VER)
#include <QrROI.hxx>
#elif defined(__GNUC__)
#include <QrROI.hxx>
#endif
#include "QrCSV.hxx"

namespace QrSDK
{
	/// \brief Logs ROI measurements to CSV files.
	/// \details QrLogger provides:
	///   - Opening and initializing a CSV file with headers via Open(file)
	///   - Writing individual ROI entries (timestamp, coordinates, temperature values) via Write(item)
	///   - Appending ROI entries to an existing CSV file via Append(file, item)
	///   - Closing the CSV file and releasing resources via Close()
	///   - Checking if the CSV file is currently open via IsOpen()
	class DLL_EXPORTS QrLogger
	{
	public:
		/// <summary>
		/// Constructor of QrLogger
		/// </summary>
		QrLogger() {};
		/// <summary>
		/// Destructor of QrLogger
		/// </summary>
		virtual ~QrLogger() {}

		bool Open(std::string file);
		bool Write(QrRoiItem item);
		bool Append(std::string file, QrRoiItem item);
		bool Close();

	public:
		bool IsOpen();

	private:
		QrCSV::ofstream csvfile;
	};
}
