//---------------------------------------------------------------------------

#ifndef DocumentH
#define DocumentH
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TDocument : public TObject
{
private:
String FName;
String FPath;
int FDocId;
int FObjId;
int FDictId;
public:
void __fastcall Show(void);
__fastcall TDocument(int ADocId,int AObjId,int ADictId,String AName,String APath)
    {FDocId=ADocId;FObjId=AObjId;FDictId=ADictId;FName=AName;FPath=APath;}
__property String Name={read=FName};
__property String Path={read=FPath};
__property int DocId={read=FDocId};
__property int ObjId={read=FObjId};
__property int DictId={read=FDictId};
};
#endif
