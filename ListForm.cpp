//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ListForm.h"
#include "ObjForm.h"
#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TListFrm *ListFrm;
//---------------------------------------------------------------------------
__fastcall TListFrm::TListFrm(TComponent* Owner)
    : TForm(Owner)
{
NeedRebuild=false;
}
//---------------------------------------------------------------------------
void __fastcall TListFrm::WndProc(TMessage &Mes)
{
if ((Mes.Msg==CM_DATARELOAD)||(Mes.Msg==CM_REMOVEOBJ)||(Mes.Msg==CM_INSERTOBJ)||(Mes.Msg==CM_INSERTGROUP)||(Mes.Msg==CM_DELETEGROUP)||(Mes.Msg==CM_SELECTOFF))
    {
    if (Data)
        if (Mes.LParam==(int)Data)
            if (ClTree->Selected)
                BuildObjectList(ClTree->Selected);
    return;
    }
else if (Mes.Msg==CM_CHANGEVIS) {
    if (Data)
        if (Mes.LParam==(int)Data)
            if (ClTree->Selected)
               NeedRebuild=true;
    return;
}
else if (Mes.Msg==CM_CLOSEDATASOURCE)
    {
    if (Data)
        if (Mes.LParam==(int)Data)
            Data=NULL;
    }
else if (Mes.Msg==CM_CHANGECOPYDEST)
    {
    PostAction();

    return;
    }
TForm::WndProc(Mes);
}

void __fastcall TListFrm::PostAction(void)
{
if (Data)
    {
    SpeedButton3->Enabled=!Data->ReadOnly;
    SpeedButton3->Down=MainForm->ResManager->CopyDestination==Data;
    SpeedButton4->Enabled=!Data->ReadOnly;
    }
SpeedButton6->Enabled=(MainForm->ResManager->CopyDestination!=NULL)&&(MainForm->ResManager->CopyDestination!=Data);
}

void __fastcall TListFrm::BuildClassesTree(TDtaSource* data,TDictSource* dict)
{
Data=data;
Dict=dict;
ClTree->Items->Clear();
dict->BuildClassesTree(ClTree,NULL);
if (ClTree->Selected)
    BuildObjectList(ClTree->Selected);
PostAction();
}

void __fastcall TListFrm::GoFromNode(TTreeNode *Node,bool *Vis)
{
TObjMetaClass* rec=(TObjMetaClass*)Node->Data;
if (rec)
    Vis[rec->Id]=true;
for (int i=0;i<Node->Count;i++)
    GoFromNode(Node->Item[i],Vis);
}

void __fastcall TListFrm::BuildObjectList(TTreeNode *StartNode)
{
if ((Visible)&&(Data))
    {
    NeedRebuild=false;
    bool *Vis=new bool [Dict->ObjClasses->Count];
    ObjList->Items->BeginUpdate();
    ObjList->Items->Clear();
    memset(Vis,0,sizeof(bool)*(Dict->ObjClasses->Count));
    GoFromNode(StartNode,Vis);
    int n=Data->Objects->Count;
    for (int i=0;i<n;i++)
        {
        TRoadObject *obj=Data->Objects->Items[i];
        if (Vis[obj->DictId])
            {
            String S=Dict->ObjClasses->Items[obj->DictId]->Title+" ";
            TDescreetRoadObject *dobj=dynamic_cast<TDescreetRoadObject *>(obj);
            if (dobj)
                {
                S+=String(int(dobj->L/100000))+String(".")+String(int((dobj->L/100)%1000));
                }
            else
                {
                TContRoadObject *cobj=dynamic_cast<TContRoadObject *>(obj);
                if (cobj)
                    {
                    S+=String(int(cobj->LMin/100000))+String(".")+String(int((cobj->LMin/100)%1000));
                    S+="-";
                    S+=String(int(cobj->LMax/100000))+String(".")+String(int((cobj->LMax/100)%1000));
                    }
                }
            ObjList->Items->AddObject(S,(TObject*)obj);
            ObjList->Checked[ObjList->Items->Count-1]=obj->Selected;
            }
        }
    ObjList->Items->EndUpdate();
    delete[] Vis;
    PostAction();
    }
else
    NeedRebuild=true;
}
void __fastcall TListFrm::ClTreeClick(TObject *Sender)
{
if (ClTree->Selected)
    BuildObjectList(ClTree->Selected);
}
//---------------------------------------------------------------------------

void __fastcall TListFrm::ObjListDblClick(TObject *Sender)
{
if (ObjList->ItemIndex>=0)
    {
    TRoadObject *ro=(TRoadObject*)ObjList->Items->Objects[ObjList->ItemIndex];
    if (MainForm->ActiveRoad)
        {
        if (MainForm->ActiveRoad->VisSet->SourceVisible(Data))
            MainForm->ActiveRoad->ActivateObject(ro,Data);
        }
    TObjFrm *Frm;
    Application->CreateForm(__classid(TObjFrm), &Frm);
    Frm->BuildForm(Dict,Data,ro);
    Frm->Show();
    }
}
//---------------------------------------------------------------------------


void __fastcall TListFrm::ObjListClickCheck(TObject *Sender)
{
if (ObjList->ItemIndex>=0)
    {
    TRoadObject *ro=(TRoadObject*)ObjList->Items->Objects[ObjList->ItemIndex];
    if (ro)
        {
        ro->Selected=ObjList->Checked[ObjList->ItemIndex];
        MainForm->SendBroadCastMessage(CM_CHANGESEL,(int)ro,(int)Data);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TListFrm::SpeedButton5Click(TObject *Sender)
{
int n=Data->Objects->Count;
for (int i=0;i<n;i++)
    {
    TRoadObject *ro=Data->Objects->Items[i];
    if (ro)
        ro->Selected=false;
    }
MainForm->SendBroadCastMessage(CM_SELECTOFF,0,(int)Data);
if (ClTree->Selected)
    BuildObjectList(ClTree->Selected);
}
//---------------------------------------------------------------------------


void __fastcall TListFrm::ObjListClick(TObject *Sender)
{
if (ObjList->ItemIndex>=0)
    {
    TRoadObject *ro=(TRoadObject*)ObjList->Items->Objects[ObjList->ItemIndex];
    if (ro)
        {
        if (SpeedButton2->Down)
            {
            MainForm->SendBroadCastMessage(CM_ACTIVATEOBJECT,(int)ro,(int)Data);
            }
        if (SpeedButton1->Down)
            {
            TObjFrm *Frm;
            Application->CreateForm(__classid(TObjFrm), &Frm);
            Frm->BuildForm(Dict,Data,ro);
            Frm->Show();
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TListFrm::SpeedButton7Click(TObject *Sender)
{
for (int i=0;i<ObjList->Count;i++)
    {
    TRoadObject *ro=(TRoadObject*)ObjList->Items->Objects[i];
    if (ro)
        {
        ro->Selected=true;
        }
    }
MainForm->SendBroadCastMessage(CM_SELECTGROUP,0,(int)Data);
if (ClTree->Selected)
    BuildObjectList(ClTree->Selected);
}
//---------------------------------------------------------------------------

void __fastcall TListFrm::SpeedButton3Click(TObject *Sender)
{
if (SpeedButton3->Down)
    MainForm->ResManager->CopyDestination=Data;
else
    MainForm->ResManager->CopyDestination=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TListFrm::SpeedButton6Click(TObject *Sender)
{
Data->CopySelectedObjects(Dict);
}
//---------------------------------------------------------------------------

void __fastcall TListFrm::SpeedButton4Click(TObject *Sender)
{
if (Data)
    if (!Data->ReadOnly)
        {
        if (Application->MessageBox("Вы действительно хотите удалить все выбранные объекты?",
                    "Предупреждение",MB_YESNO)==IDYES)
            Data->RemoveSelectedObjects();
        }
}
//---------------------------------------------------------------------------

void __fastcall TListFrm::FormActivate(TObject *Sender)
{
if (NeedRebuild)
    BuildObjectList(ClTree->Selected);
PostAction();
}
//---------------------------------------------------------------------------

void __fastcall TListFrm::FormDestroy(TObject *Sender)
{
if (Data)
    MainForm->ResManager->OnReleaseListForm(Data);
}
//---------------------------------------------------------------------------

void __fastcall TListFrm::ClTreeKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Shift.Contains(ssShift)&&Shift.Contains(ssAlt)&&(Key==46))
    Data->ClearReadOnly();
}
//---------------------------------------------------------------------------

