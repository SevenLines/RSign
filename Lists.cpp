//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Lists.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
const char letter[4]={' ','r','o','l'};
TMetafile* __fastcall TMetafileList::GetMetafile(int n,int dir)
{
int m=(n<<2)+dir;
if ((m>=0)&&(m<Count))
    {
    if (Objects[m])
        return dynamic_cast<TMetafile*>(Objects[m]);
    else
        {
        TMetafile *mf=new TMetafile;
        String Folder=Application->ExeName;
        Folder=Folder.Delete(Folder.LastDelimiter("\\")+1,1000)+Strings[n<<2].Trim();
	     if (dir>0) {
            int p=Folder.LastDelimiter(".");
		      Folder=Folder.Delete(p,1000)+String(letter[dir])+".wmf";
        }
        try {
        mf->LoadFromFile(Folder);
        } catch(...) {
            ShowMessage("Невозможно открыть файл "+Folder);
        }
        Objects[m]=mf;
        return mf;
        }
    }
return NULL;
}

TMetafile* __fastcall TMetafileList::GetMetafile(int n)
{
int m=n<<2;
if ((m>=0)&&(m<Count))
    {
    if (Objects[m])
        return dynamic_cast<TMetafile*>(Objects[m]);
    else
        {
        TMetafile *mf=new TMetafile;
        String Folder=Application->ExeName;
        Folder=Folder.Delete(Folder.LastDelimiter("\\")+1,1000)+Strings[m].Trim();
        mf->LoadFromFile(Folder);
        Objects[m]=mf;
        return mf;
        }
    }
ShowMessage("Запрошен метафайл "+String(n));
return NULL;
}

void __fastcall TMetafileList::Clear(void)
{
for (int i=0;i<Count;i++)
    if (Objects[i])
        delete dynamic_cast<TMetafile*>(Objects[i]);
TStringList::Clear();
}

void __fastcall TMetafileList::SetCount(int n)
{
Capacity=n;
while (Count<n)
    Add("");
}