//---------------------------------------------------------------------------

#ifndef UtilsH
#define UtilsH

#include <vector>
#include <system.hpp>

using namespace std;

class Utils
{
  public:
        static void split(AnsiString str, AnsiString separators, vector<AnsiString>& words_out, int max_splits = -1);
};


#endif
