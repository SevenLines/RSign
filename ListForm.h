//---------------------------------------------------------------------------
#ifndef ListFormH
#define ListFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "DataSour.h"
#include <ImgList.hpp>
#include <CheckLst.hpp>
#include <Buttons.hpp>
class TDtaSource;
class TDictSource;
class TListFrm : public TForm
{
__published:	// IDE-managed Components
    TTreeView *ClTree;
    TSplitter *Splitter1;
    TCheckListBox *ObjList;
    TPanel *Panel1;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton3;
    TSpeedButton *SpeedButton4;
    TSpeedButton *SpeedButton5;
    TSpeedButton *SpeedButton6;
    TSpeedButton *SpeedButton7;
    void __fastcall ClTreeClick(TObject *Sender);
    void __fastcall ObjListDblClick(TObject *Sender);
    void __fastcall WndProc(TMessage &Mes);
    void __fastcall ObjListClickCheck(TObject *Sender);
    void __fastcall SpeedButton5Click(TObject *Sender);
    void __fastcall ObjListClick(TObject *Sender);
    void __fastcall SpeedButton7Click(TObject *Sender);
    void __fastcall SpeedButton3Click(TObject *Sender);
    void __fastcall SpeedButton6Click(TObject *Sender);
    void __fastcall SpeedButton4Click(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
    void __fastcall ClTreeKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
    TDtaSource* Data;
    TDictSource* Dict;
    bool NeedRebuild; // Флаг Если список невидимый и список изменился
                      // то устанавливается в true и дерево перестраивается
                      // при показе формы
void __fastcall BuildObjectList(TTreeNode *StartNode);
void __fastcall GoFromNode(TTreeNode *Node,bool *Vis);
void __fastcall PostAction(void);
public:		// User declarations
void __fastcall BuildClassesTree(TDtaSource*,TDictSource*);
    __fastcall TListFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TListFrm *ListFrm;
//---------------------------------------------------------------------------
#endif
