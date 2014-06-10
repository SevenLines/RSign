//---------------------------------------------------------------------------


#pragma hdrstop

#include "Utils.h"
#include <math.h>

#pragma package(smart_init)

using namespace std;

void Utils::split(AnsiString str, AnsiString separators, vector<AnsiString>& words_out, int max_splits)
{
     bool wordStart = False;
     int startPos = 0;
     int splits_counter = 0;

     max_splits -= 1;

     for (int i=1;i<=str.Length();++i) {
        bool is_sep = false;
        // check separator
        for (int j=1;j<=separators.Length();++j) {
           if (str[i] == separators[j]) {
               is_sep = true;
               break;
           }
        }
        if(!is_sep ) {
           if (!wordStart) {
             startPos = i;
             wordStart = True;
           }
        }else if (wordStart) {
           words_out.push_back(str.SubString(startPos, i - startPos));
           splits_counter++;
           wordStart = False;
        }
        if (splits_counter >= max_splits) {
           break;
        }
     }
     words_out.push_back(str.SubString(startPos + words_out.back().Length(), str.Length() - startPos - words_out.back().Length() + 1));
}

float Utils::r(TPoint p1, TPoint p2)
{
   int vx = p2.x - p1.x;
   int vy = p2.y - p1.y;
   int r = vx*vx + vy*vy;
   if (r<=0)
      return 0;
   return sqrt(r);
}

void Utils::optimize(vector<TPoint>& points, int step /*in cm*/)
{
    bool ffind;
    vector<TPoint> new_points;
//    new_points = points;
    new_points.push_back(points[0]);
    for (int i=1; i<points.size()-1;++i) {
       TPoint &p1 = new_points.back();
       TPoint &p2 = points[i];
       if (Utils::r(p1,p2) > step) {
          new_points.push_back(p2);
       }
    }
    TPoint &p2 = points[points.size()-1];
    if (Utils::r(new_points.back(),p2) > step || new_points.size() ==1) {
        new_points.push_back(p2);
    } else {
        new_points.back() = p2;
    }

    points = new_points;
}
