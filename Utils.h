//---------------------------------------------------------------------------

#ifndef UtilsH
#define UtilsH

#include <vector>
#include <vcl.h>

using namespace std;

class Utils
{
  public:
        static void split(AnsiString str, AnsiString separators, vector<AnsiString>& words_out, int max_splits = -1);
        static void optimize(vector<TPoint> &points, int step /*in cm*/);
        static float r(TPoint p1, TPoint p2);
};


#endif
