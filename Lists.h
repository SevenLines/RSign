//---------------------------------------------------------------------------
#ifndef ListsH
#define ListsH
#include "graphics.hpp"
//---------------------------------------------------------------------------
//     Файл содержит описания списочных структур
//     Wrote By Kirichenko K.D.
//
//---------------------------------------------------------------------------
//Шаблон списка пользовательских объектов.
//Переопределяеет TList::Clear, так чтобы при
//очистке списка освобождались и элементы списка.
template <class Type_T>
class TObjList : public TList
{
private:
    void __fastcall PutP(int n,Type_T *p)
        {if ((n>=0)&&(n<Count)) (List)[n]=p; else throw new EListError(n);}
    Type_T* __fastcall GetP(int n)
        {if ((n>=0)&&(n<Count)) return (Type_T*)((List)[n]);else throw new EListError(n);}
public:
    int __fastcall FirstFree(int start)
        {
        int i;
        for (i=start;i<Count;i++)
                if ((List)[i]==NULL)
                        break;
        return i;
        }
    virtual void __fastcall ClearList(void)
        {
        TList::Clear();
        }
    virtual void __fastcall Clear(void)
        {for (int i=0;i<Count;i++)
            delete (Type_T*)(List)[i];
        TList::Clear();
        }
    __property Type_T* Items[int n]={read=GetP,write=PutP};
};

// Список объектов GDI Windows. Переопределяет функцию
// очистки списка, удаляя объекты GDI
class TGDIList : public TList
{
public:
    __fastcall TGDIList(void) : TList() {}
    virtual void __fastcall Clear(void)
        {for (int i=0;i<Count;i++)
            DeleteObject((List)[i]);
        TList::Clear();
        }
    int __fastcall FirstFree(int start)
        {
        int i;
        for (i=start;i<Count;i++)
                if (Items[i]==NULL)
                        break;
        return i;
        }
};

// Список метафайлов. Изначально должен задаваться
// как список строк. При обращении к метафайлу
// через свойство Metas происходит его открытие.
// Открытый метафайл остается в памяти до освобождения
// списка
class TMetafileList : public TStringList
{
private:

public:
TMetafile* __fastcall GetMetafile(int n,int dir);
void __fastcall SetCount(int n);
__fastcall TMetafileList(void): TStringList() {}
__fastcall ~TMetafileList(void) {Clear();}
virtual void __fastcall Clear(void);
TMetafile* __fastcall GetMetafile(int n);
__property TMetafile* Metas[int n]={read=GetMetafile};
};

#endif
