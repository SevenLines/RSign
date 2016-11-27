//---------------------------------------------------------------------------

#ifndef HelpersH
#define HelpersH

#include <Types.hpp>
#include "RoadObj.h"
//---------------------------------------------------------------------------

class Helpers {
public:
    static float GetAngle(TPoint vec1, TPoint vec2);
    static float GetAngle2(TPoint &p1, TPoint &p2, float ScaleY, float *length=NULL);
    static float GetLength(TPoint p1, TPoint p2, float ScaleY);
    static bool compareSigns(const TRoadSign* s1, const TRoadSign* s2);
    static int GetAngle(TPoint p0, TPoint p1, TPoint p2);
    static AnsiString SignLabelParser(AnsiString signName, AnsiString label);
    static AnsiString StringConvertSignals(float f1, float f2, void* data);
    static AnsiString StringConvert(float f1, float f2, void* data);

    static void swap(int &x, int &y);
};

TPoint operator -(TPoint pt1, TPoint pt2)
{
    return TPoint(pt1.x - pt2.x, pt1.y - pt2.y);
}

bool operator==(TPoint p1, TPoint p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

int lessForVerticalLabels;

#endif
