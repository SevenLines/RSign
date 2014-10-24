//---------------------------------------------------------------------------
#ifndef GdiEFormH
#define GdiEFormH
#define GDIEDIT

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include "DataSour.h"
#include "DrawMan.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <CheckLst.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TGroupBox *GroupBox1;
        TSplitter *Splitter1;
        TGroupBox *GroupBox2;
        TSplitter *Splitter2;
        TGroupBox *GroupBox3;
        TListBox *PropList;
        TComboBox *ClassList;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *ObjName;
        TLabel *Label3;
    TEdit *ObjFlags;
        TComboBox *MainChar;
        TLabel *Label4;
        TLabel *Label5;
        TCheckListBox *CharList;
        TButton *Button1;
        TTabSheet *TabSheet2;
        TGroupBox *GroupBox4;
        TGroupBox *GroupBox5;
        TSplitter *Splitter3;
        TListBox *GDIPens;
        TGroupBox *GroupBox6;
        TListBox *GDIBrushs;
        TTabSheet *TabSheet3;
        TGroupBox *GroupBox7;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *PropName;
        TEdit *PropShort;
        TLabel *Label8;
        TEdit *PropClass;
        TLabel *Label9;
        TComboBox *PropType;
        TButton *Button2;
        TGroupBox *GroupBox8;
        TListBox *ProperList;
    TEdit *PropField;
    TLabel *Label10;
    TListBox *ValList;
        TGroupBox *GroupBox9;
        TListBox *VisList;
        TSplitter *Splitter4;
        TSplitter *Splitter5;
        TGroupBox *GroupBox10;
        TGroupBox *GroupBox11;
        TSplitter *Splitter6;
        TRadioButton *Radio1;
        TRadioButton *Radio2;
        TRadioButton *Radio3;
        TRadioButton *Radio4;
        TCheckBox *Check1;
        TCheckBox *Check2;
        TCheckBox *Check3;
        TCheckBox *Check4;
    TPaintBox *VisBox;
    TADOConnection *Connection;
    TMenuItem *N4;
    TMenuItem *N5;
        TPopupMenu *Popup1;
        TMenuItem *P1;
        TMenuItem *P2;
        TMenuItem *P3;
        TMenuItem *P4;
        TMenuItem *P5;
        TMenuItem *P6;
        TButton *Button3;
    TButton *Button4;
    TEdit *Edit1;
    TUpDown *UpDown1;
    TLabel *Label11;
    TEdit *MainTable;
    TTreeView *ObjTree;
    TMenuItem *N6;
    TMenuItem *N7;
    TCheckBox *ShowGrid;
    TMenuItem *N8;
    TMenuItem *N9;
    TPanel *Panel1;
    TCheckListBox *PagesList;
    TSplitter *Splitter7;
    TListBox *VisPropList;
    TPanel *Panel2;
    TTreeView *VisObjTree;
    TGroupBox *GroupBox12;
    TComboBox *CurPage;
    TButton *Button5;
        void __fastcall N2Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall PropListDblClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall N3Click(TObject *Sender);
        void __fastcall GDIPensDrawItem(TWinControl *Control, int Index,
          TRect &Rect, TOwnerDrawState State);
        void __fastcall GDIBrushsDrawItem(TWinControl *Control, int Index,
          TRect &Rect, TOwnerDrawState State);
        void __fastcall ProperListClick(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
    void __fastcall ClassListChange(TObject *Sender);
    void __fastcall ProperListMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall ProperListMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall ProperListMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall VisListDrawItem(TWinControl *Control, int Index,
          TRect &Rect, TOwnerDrawState State);
        void __fastcall VisPropListClick(TObject *Sender);
        void __fastcall VisBoxPaint(TObject *Sender);
        void __fastcall Radio1Click(TObject *Sender);
        void __fastcall VisListDblClick(TObject *Sender);
    void __fastcall N4Click(TObject *Sender);
    void __fastcall N5Click(TObject *Sender);
        void __fastcall P4Click(TObject *Sender);
        void __fastcall P1Click(TObject *Sender);
        void __fastcall P5Click(TObject *Sender);
        void __fastcall P2Click(TObject *Sender);
        void __fastcall GDIPensDblClick(TObject *Sender);
        void __fastcall GDIBrushsDblClick(TObject *Sender);
        void __fastcall VisListClick(TObject *Sender);
        void __fastcall P6Click(TObject *Sender);
        void __fastcall Check1Click(TObject *Sender);
        void __fastcall Check2Click(TObject *Sender);
        void __fastcall Check3Click(TObject *Sender);
        void __fastcall Check4Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall P3Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall Edit1Change(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall ObjTreeChange(TObject *Sender, TTreeNode *Node);
    void __fastcall VisObjTreeChange(TObject *Sender, TTreeNode *Node);
    void __fastcall VisBoxDblClick(TObject *Sender);
    void __fastcall N7Click(TObject *Sender);
    void __fastcall ShowGridClick(TObject *Sender);
    void __fastcall ValListMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall ValListMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall ValListMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall N8Click(TObject *Sender);
    void __fastcall N9Click(TObject *Sender);
    void __fastcall Button5Click(TObject *Sender);
private:	// User declarations
        int MovedIndex;
        int MovedTextIndex;
        TDictSource *Dict;
        TResManager *Manager;
        TSharedObjSource *Shared;
        TRoadObjFactory *Factory;
        TDrawManager *FDrawMan;
        TRoad *FRoad;
        TDrwClassesRec *CurrentDrw;
        void __fastcall ShowObjTree(TTreeView* List,TDictSource *Dict);
        void __fastcall BuildPagesList(TDictSource *Dict);
        int __fastcall PageIndex(void);
        int __fastcall PageFlags(void);        
        void __fastcall ShowPagesFlag(TDrwClassesRec *Rec);
        void __fastcall ShowPropList(TDictSource *Dict);
        void __fastcall ShowGdiList(void);
        void __fastcall ShowVisList(TObjMetaClass*);
        void __fastcall DeleteFromCharList(int n);
        void __fastcall AddToCharList(TPropClassesRec* r);
        void __fastcall CopyDrwParam(TObjMetaClass*,TTextPropRec*);
        void __fastcall CopyDrwParam(TDrwClassesRec *NewRec);
        void __fastcall ShowObject(void);
        void __fastcall ShowProc(void);
        int __fastcall  GetClassNameIndex(String s);
        void __fastcall SortTextByViewOrder(int id);
        void __fastcall SortByViewOrder(void);
        void __fastcall MoveStringList(TStrings *Lst,int newindex,int &oldindex);
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        void __fastcall SendBroadCastMessage(int,int,int) {}        
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
