#pragma once
#include <QrShared.hxx>

namespace QrSDK
{
	/// @brief Data structure representing a region-of-interest (ROI) measurement item.
	/// @details QrRoiItem contains:
	///   - Name: a user-defined identifier for the ROI
	///   - Rect: the rectangular coordinates defining the ROI area
	///   - MinTempLoc: location and value of the minimum temperature within the ROI
	///   - AvgTempLoc: location and value of the average temperature within the ROI
	///   - MaxTempLoc: location and value of the maximum temperature within the ROI
	#pragma pack(push, 1)
	typedef struct _QrRoiItem
	{
		char Name[64];			/**< Name of item */
		QrRect Rect;			/**< Rectangle area of item */
		QrLocItem MinTempLoc;	/**< location in area for minium temperature */
		QrLocItem AvgTempLoc;	/**< average temperature for area, no location */
		QrLocItem MaxTempLoc;	/**< location in area for maximum temperature */

	}QrRoiItem;
	#pragma pack(pop)
	
	/// @brief Manages a collection of region-of-interest (ROI) items for measurement and analysis.
	/// @details QrROI provides:
	///   - Checking if the collection is empty via IsEmpty()
	///   - Clearing all ROI items via Clear()
	///   - Retrieving the first or last ROI item via First() and Last()
	///   - Adding and removing items with Add(item), RemoveLast(item), and RemoveAt(index)
	///   - Accessing or updating an item at a specific index via Get(index) and Set(index, item)
	///   - Querying the number of stored items via Length()
	///   - Direct access to the underlying std::vector<QrRoiItem> Items
	class DLL_EXPORTS QrROI
	{
	public:
		QrROI() {};
		virtual ~QrROI() { Items.clear(); };
	
		bool IsEmpty();
		bool Clear();
		QrRoiItem First();
		QrRoiItem Last();
		bool Add(QrRoiItem item);
		bool RemoveLast(QrRoiItem item);
		bool RemoveAt(int index);
		QrRoiItem Get(int index);
		bool Set(int index, QrRoiItem item);
		int Length();
		std::vector<QrRoiItem> Items;

	private:
	};
}


