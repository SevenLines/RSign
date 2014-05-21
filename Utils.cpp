//---------------------------------------------------------------------------


#pragma hdrstop

#include "Utils.h"

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
