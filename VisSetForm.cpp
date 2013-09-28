//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VisSetForm.h"
#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TVisSetFrm *VisSetFrm;
//---------------------------------------------------------------------------
__fastcall TVisSetFrm::TVisSetFrm(TComponent* Owner)
    : TForm(Owner)
{
FDataList=new TObjList<TDtaSource>;
FRoadFrm=NULL;
FMainSource=FEditedSource=FVideoSource=FProfilSource=FCurveSource=NULL;
}
//---------------------------------------------------------------------------

__fastcall TVisSetFrm::~TVisSetFrm(void)
{
ReleaseData();
}

void __fastcall TVisSetFrm::ReleaseData(void)
{
if (FDataList)
    {
    for (int i=0;i<FDataList->Count;i++)
      MainForm->ResManager->ReleaseDataSource(FDataList->Items[i]);
    FDataList->TList::Clear();
    delete FDataList;
    FDataList=NULL;
    if (FRoadFrm)
        {
        FRoadFrm->VisSet=NULL;
        FRoadFrm=NULL;
        }
    }
}

void __fastcall TVisSetFrm::SetComboListItem(TComboBox *CBox,TDtaSource *Dta)
{
if (CBox->Items->Count>=0)
    {
    int index=0;
    for (int i=0;i<CBox->Items->Count;i++)
        if (Dta==CBox->Items->Objects[i])
            {index=i;break;}
    CBox->ItemIndex=index;
    if (CBox->OnChange)
        CBox->OnChange(CBox);
    }
}

void __fastcall TVisSetFrm::SetRoadId(__int32 roadid,TDictSource *dict)
{
FDict=dict;
FRoadId=roadid;
int OldCount=FDataList->Count;
bool *OldVis=new bool [MAXCODEID*FDataList->Count];
TDtaSource **OldSrc=new TDtaSource* [FDataList->Count];
bool *OldSrcUse=new bool [FDataList->Count];
TDtaSource *MainSrc=FMainSource;
TDtaSource *VideoSrc=FVideoSource;
TDtaSource *EditedSrc=FEditedSource;
TDtaSource *ProfilSrc=FProfilSource;
TDtaSource *CurveSrc=FCurveSource;
FMainSource=NULL;
FVideoSource=NULL;
FEditedSource=NULL;
FProfilSource=NULL;
FCurveSource=NULL;

for (int i=0;i<FDataList->Count;i++)
    {
    OldSrcUse[i]=false;
    OldSrc[i]=FDataList->Items[i];
    GetVisible(MAXCODEID,OldVis+sizeof(bool)*MAXCODEID*i,OldSrc[i]);
    }
FDataList->TList::Clear();
MainSrcList->Items->BeginUpdate();
MainSrcList->Items->Clear();
VideoSrcList->Items->BeginUpdate();
VideoSrcList->Items->Clear();
EditedSrcList->Items->BeginUpdate();
EditedSrcList->Clear();
ProfilSrcList->Items->BeginUpdate();
ProfilSrcList->Clear();
CurveSrcList->Items->BeginUpdate();
CurveSrcList->Clear();
ClTree->Items->BeginUpdate();
ClTree->Items->Clear();
for (int i=0;i<MainForm->ResManager->DataCount;i++)
    {
    TDtaSource *Dta=MainForm->ResManager->Data[i];
    if (Dta)
        if (Dta->Id==roadid)
            {
            if (!FMainSource)
                FMainSource=Dta;
            MainSrcList->Items->AddObject(Dta->SourceName,Dta);
            if ((Dta->HaveDirVideo)||(Dta->HaveUnDirVideo))
                VideoSrcList->Items->AddObject(Dta->SourceName,Dta);
            if (!Dta->ReadOnly)
                EditedSrcList->Items->AddObject(Dta->SourceName,Dta);
            ProfilSrcList->Items->AddObject(Dta->SourceName,Dta);
            CurveSrcList->Items->AddObject(Dta->SourceName,Dta);
            FDataList->Add(Dta);
            TTreeNode *Head=ClTree->Items->Add(NULL,Dta->SourceName);
            Head->Data=Dta;
            FDict->BuildClassesTree(ClTree,Head);
            int j;
            for (j=0;j<OldCount;j++)
                if (Dta==OldSrc[j])
                    {
                    OldSrcUse[j]=true;
                    SetVisByNode(MAXCODEID,OldVis+sizeof(bool)*MAXCODEID*j,Head);
                    break;
                    }
            if (j==OldCount)
              MainForm->ResManager->UseDataSource(Dta);
            }
    }
MainSrcList->Items->EndUpdate();
VideoSrcList->Items->EndUpdate();
EditedSrcList->Items->EndUpdate();
ProfilSrcList->Items->EndUpdate();
CurveSrcList->Items->EndUpdate();
ClTree->Items->EndUpdate();
//TRoadFrm *Frm=FRoadFrm;
//FRoadFrm=NULL;
SetComboListItem(MainSrcList,MainSrc);
SetComboListItem(VideoSrcList,VideoSrc);
SetComboListItem(ProfilSrcList,ProfilSrc);
SetComboListItem(EditedSrcList,EditedSrc);
SetComboListItem(CurveSrcList,CurveSrc);
for (int i=0;i<OldCount;i++)
  if (!OldSrcUse[i])
    MainForm->ResManager->ReleaseDataSource(OldSrc[i]);
delete[] OldVis;
delete[] OldSrc;
delete[] OldSrcUse;
TestImages();
ClTree->Invalidate();
//FRoadFrm=Frm;
FRoadFrm->FindSources();
}

int __fastcall TVisSetFrm::TestImageByNode(TTreeNode *node)
{
int indexes[3]={0,0,0};
if (node->HasChildren)
    {
    for (int i=0;i<node->Count;i++)
        indexes[TestImageByNode(node->Item[i])]++;
    int ii;
    if (indexes[0]==node->Count)
        ii=0;
    else if (indexes[1]==node->Count)
        ii=1;
    else
        ii=2;
    node->ImageIndex=ii;
    node->SelectedIndex=ii;
    }
return node->ImageIndex;
}

void __fastcall TVisSetFrm::TestImages(void)
{
TTreeNode *Node=ClTree->Items->GetFirstNode();
while (Node)
    {
    TestImageByNode(Node);
    Node=Node->getNextSibling();
    }
}

void __fastcall TVisSetFrm::SetImageIndex(TTreeNode *snode,int ind)
{
snode->ImageIndex=ind;
snode->SelectedIndex=ind;
for (int i=0;i<snode->Count;i++)
    SetImageIndex(snode->Item[i],ind);
}

void __fastcall TVisSetFrm::GetVisByNode(int max,bool *mask,TTreeNode *node)
{
TObjMetaClass* rec=dynamic_cast<TObjMetaClass*>((TObject*)node->Data);
if (rec)
    if (rec->Id<max)
        mask[rec->Id]=node->ImageIndex==1;
for (int i=0;i<node->Count;i++)
    GetVisByNode(max,mask,node->Item[i]);
}

void __fastcall TVisSetFrm::SetVisByNode(int max,bool *mask,TTreeNode *node)
{
TObjMetaClass* rec=dynamic_cast<TObjMetaClass*>((TObject*)node->Data);
if (rec)
    if (rec->Id<max)
        node->ImageIndex=mask[rec->Id] ? 1 : 0;
for (int i=0;i<node->Count;i++)
    SetVisByNode(max,mask,node->Item[i]);
}

bool __fastcall TVisSetFrm::GetVisible(int max,bool *mask,TDtaSource *data)
{
bool Res=false;
for (int i=0;i<max;i++)
    mask[i]=false;
TTreeNode *Node=ClTree->Items->GetFirstNode();
while (Node)
    {
    if (Node->Data==data)
        {
        GetVisByNode(max,mask,Node);
        Res=true;
        break;
        }
    Node=Node->getNextSibling();
    }
return Res;
}

bool __fastcall TVisSetFrm::SetVisible(int max,bool *mask,TDtaSource *data)
{
bool Res=false;
TTreeNode *Node=ClTree->Items->GetFirstNode();
while (Node)
    {
    if (Node->Data==data)
        {
        SetVisByNode(max,mask,Node);
        TestImageByNode(Node);
        Res=true;
        break;
        }
    Node=Node->getNextSibling();
    }
return Res;
}

void __fastcall TVisSetFrm::SetMainSource(TDtaSource *data)
{
for (int i=0;i<MainSrcList->Items->Count;i++)
    {
    if (MainSrcList->Items->Objects[i]==data)
        {
        MainSrcList->ItemIndex=i;
        MainSrcListChange(MainSrcList);
        break;
        }
    }
}
bool __fastcall TVisSetFrm::SourceVisible(TDtaSource *data)
{
TTreeNode *Node=ClTree->Items->GetFirstNode();
while (Node)
    {
    if (Node->Data==data)
        return Node->ImageIndex;
    Node=Node->getNextSibling();
    }
return false;
}

bool __fastcall TVisSetFrm::SourceVisible(__int32 dataclass)
{
TTreeNode *Node=ClTree->Items->GetFirstNode();
while (Node)
    {
    TDtaSource* Dta=dynamic_cast<TDtaSource*>((TObject*)Node->Data);
    if (Dta)
        if (Dta->DataClass==dataclass)
            return Node->ImageIndex;
    Node=Node->getNextSibling();
    }
return false;
}

void __fastcall TVisSetFrm::SetSourceVisible(TDtaSource *data, bool vis)
{
TTreeNode *Node=ClTree->Items->GetFirstNode();
while (Node)
    {
    int imindex;
    if (Node->Data==data)
        {
        imindex=vis?1:0;
        SetImageIndex(Node,imindex);
        }
    Node=Node->getNextSibling();
    }
SetMainSource(data);
}

void __fastcall TVisSetFrm::SetSourceVisible(TDtaSource *data)
{
TTreeNode *Node=ClTree->Items->GetFirstNode();
while (Node)
    {
    int imindex;
    if (Node->Data==data)
        imindex=1;
    else
        imindex=0;
    SetImageIndex(Node,imindex);
    Node=Node->getNextSibling();
    }
SetMainSource(data);
}

void __fastcall TVisSetFrm::ClTreeMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
TV_HITTESTINFO htest;
htest.pt.x=X;
htest.pt.y=Y;
void *item=TreeView_HitTest(ClTree->Handle,&htest);
if (item&&(htest.flags&TVHT_ONITEMICON))
    {
    TTreeNode *nod=ClTree->GetNodeAt(X,Y);
    if (nod)
        {
        SetImageIndex(nod,(nod->ImageIndex+1)&1);
        TestImages();
//        MainForm->SendBroadCastMessage(CM_CHANGEVIS,0,(int)Data);
        ClTree->Invalidate();
        FRoadFrm->RefreshPlan();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TVisSetFrm::MainSrcListChange(TObject *Sender)
{
if (MainSrcList->ItemIndex>=0)
    FMainSource=dynamic_cast<TDtaSource*>(MainSrcList->Items->Objects[MainSrcList->ItemIndex]);
else
    FMainSource=NULL;
if (FRoadFrm)
    {
    FRoadFrm->FindSources();
    FRoadFrm->RefreshPlan();
    }
}
//---------------------------------------------------------------------------


void __fastcall TVisSetFrm::VideoSrcListChange(TObject *Sender)
{
if (VideoSrcList->ItemIndex>=0)
    FVideoSource=dynamic_cast<TDtaSource*>(VideoSrcList->Items->Objects[VideoSrcList->ItemIndex]);
else
    FVideoSource=NULL;
if (FRoadFrm)
    if (FVideoSource!=FRoadFrm->VideoData)
        {
        FRoadFrm->FindSources();
        FRoadFrm->HideVideo();
        }
}
//---------------------------------------------------------------------------

void __fastcall TVisSetFrm::EditedSrcListChange(TObject *Sender)
{
if (EditedSrcList->ItemIndex>=0)
    FEditedSource=dynamic_cast<TDtaSource*>(EditedSrcList->Items->Objects[EditedSrcList->ItemIndex]);
else
    FEditedSource=NULL;
if (FRoadFrm)
        {
        FRoadFrm->FindSources();
        }
}
//---------------------------------------------------------------------------

void __fastcall TVisSetFrm::ProfilSrcListChange(TObject *Sender)
{
if (ProfilSrcList->ItemIndex>=0)
    FProfilSource=dynamic_cast<TDtaSource*>(ProfilSrcList->Items->Objects[ProfilSrcList->ItemIndex]);
else
    FProfilSource=NULL;
if (FRoadFrm)
    {
    FRoadFrm->FindSources();
    FRoadFrm->RefreshPlan();
    }

}
//---------------------------------------------------------------------------

void __fastcall TVisSetFrm::CurveSrcListChange(TObject *Sender)
{
if (CurveSrcList->ItemIndex>=0)
    FCurveSource=dynamic_cast<TDtaSource*>(CurveSrcList->Items->Objects[CurveSrcList->ItemIndex]);
else
    FCurveSource=NULL;
if (FRoadFrm)
    {
    FRoadFrm->FindSources();
    FRoadFrm->RefreshPlan();
    }
}
//---------------------------------------------------------------------------

void __fastcall TVisSetFrm::ClTreeKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Shift.Contains(ssShift)&&Shift.Contains(ssAlt)&&(Key==46))
    SetRoadId(FRoadId,FDict);    
}
//---------------------------------------------------------------------------

