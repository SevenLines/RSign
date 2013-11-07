//---------------------------------------------------------------------------
#ifndef ObjFormH
#define ObjFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "DataSour.h"

#pragma link "CSPIN"

//---------------------------------------------------------------------------
class TObjFrm : public TForm
{
__published:	// IDE-managed Components
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TGroupBox *CGroup;
    TGroupBox *ChrGroup;
    TGroupBox *PlaceGroup;
    TButton *Button1;
    TButton *Button2;
    TPanel *Panel2;
    TSpeedButton *AutoClose;
    TButton *Button3;
    TButton *Button4;
    TListBox *DocListBox;
    void __fastcall FormDeactivate(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall ElemChange(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
   void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
    bool FChanged;
    TList* CompList;
    TGroupBox* __fastcall SelectGroup(int n);
    void __fastcall ClearGroup(TWinControl *wnd);
    void __fastcall ClearGroups(void);
    void __fastcall AddRef(TControl* ctrl,int id);
    String __fastcall GetAsString(int n);
    void __fastcall SetAsString(int n,String val);
    int __fastcall GetAsInt(int n);
    void __fastcall SetAsInt(int n,int val);
    void __fastcall WndProc(TMessage&);
    void __fastcall SetChanged(bool);
public:		// User declarations
    // Добавляет новый MaskEdit к группе gr
    void __fastcall AddMask(int gr,int id,String Title,String Mask,String Val);
    void __fastcall AddCombo(int gr,int id,String Title,int vid,bool enable);
    void __fastcall AddText(int gr,int id,String Title,String Val,bool enable);
    void __fastcall AddCheckBox(int gr,int id,String Title,int Val,bool enable);
    void __fastcall AlignGroup(int);
TDtaSource *Data;
TDictSource *Dict;
TRoadObject *Obj;
int *ModalRes; // Переменная для возвращения значения в случае
               // вызова по ShowModal  
    __fastcall TObjFrm(TComponent* Owner);
void __fastcall BuildForm(TDictSource *dict,TDtaSource* data, TRoadObject *obj);
__property String SValue[int]={read=GetAsString,write=SetAsString};
__property __int32 NValue[int]={read=GetAsInt,write=SetAsInt};
__property bool Changed={read=FChanged,write=SetChanged};
};
//---------------------------------------------------------------------------
extern PACKAGE TObjFrm *ObjFrm;
//---------------------------------------------------------------------------
#endif
