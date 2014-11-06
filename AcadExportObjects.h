//---------------------------------------------------------------------------

#ifndef AcadExportObjectsH
#define AcadExportObjectsH

#include "RoadObj.h"
#include <vector>

using namespace std;

struct KromkaObject{
    TSquareRoadSideObject_Kromka* obj;
    bool exist;
};

class KromkaObjectGroup {
private:
	int mMin, mMax;
	TRoad *mRoad;
public:	
	KromkaObjectGroup(TRoad *road) : mMin(-1), mMax(-1), mRoad(road) {
	}
	
	vector<KromkaObject> objects;
	void addObject(KromkaObject &obj) {
		if (obj.obj->LMin < mMin || objects.size() == 0) mMin = obj.obj->LMin;
		if (obj.obj->LMax > mMax || objects.size() == 0) mMax = obj.obj->LMax;
		objects.push_back(obj);
	}
	
	bool isOverlap(KromkaObject &obj) {
		return ((mMin < obj.obj->LMin && obj.obj->LMin < mMax) 
				|| (mMin < obj.obj->LMax && obj.obj->LMax < mMax)
				|| (obj.obj->LMin < mMax && mMax < obj.obj->LMax )
				|| (obj.obj->LMin < mMin && mMin < obj.obj->LMax )) &&
				objects.size() > 0 && obj.obj->Placement == objects[0].obj->Placement;
	}
	
	int min() {
		return mMin;
	}
	
	int max() {
		return mMax;
	}
	
	TRoad *road() {
		return mRoad;
	}
};

//---------------------------------------------------------------------------
#endif
