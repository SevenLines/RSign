//---------------------------------------------------------------------------

#ifndef VisSetFormH
#define VisSetFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "List.h"
#include "DataSour.h"
//#include "ShowRoad.h"
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TVisSetFrm : public TForm
{
__published:	// IDE-managed Components
    TImageList *ImageList1;
    TTreeView *ClTree;
    TPanel *Panel1;
    TLabel *Label1;
    TComboBox *MainSrcList;
    TLabel *Label2;
    TComboBox *VideoSrcList;
  TLabel *Label3;
  TComboBox *EditedSrcList;
  TComboBox *ProfilSrcList;
  TLabel *Label4;
  TLabel *Label5;
  TComboBox *CurveSrcList;
    void __fastcall ClTreeMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall MainSrcListChange(TObject *Sender);
    void __fastcall VideoSrcListChange(TObject *Sender);
  void __fastcall EditedSrcListChange(TObject *Sender);
  void __fastcall ProfilSrcListChange(TObject *Sender);
  void __fastcall CurveSrcListChange(TObject *Sender);
    void __fastcall ClTreeKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
__int32 FRoadId;
TObjList<TDtaSource> *FDataList;
TRoadFrm *FRoadFrm;
TDictSource *FDict;
TDtaSource *FMainSource,*FVideoSource, *FEditedSource, *FProfilSource, *FCurveSource;
void __fastcall SetImageIndex(TTreeNode *snode,int ind);
void __fastcall GetVisByNode(int max,bool *mask,TTreeNode *node);
void __fastcall SetVisByNode(int max,bool *mask,TTreeNode *node);
int __fastcall TestImageByNode(TTreeNode *node);
void __fastcall TestImages(void);
void __fastcall SetComboListItem(TComboBox *CBox,TDtaSource *Dta);
void __fastcall SetMetricSource(TDtaSource *Dta)
    {SetComboListItem(MainSrcList,Dta);}
void __fastcall SetVideoSource(TDtaSource *Dta)
    {SetComboListItem(VideoSrcList,Dta);}
void __fastcall SetProfilSource(TDtaSource *Dta)
    {SetComboListItem(ProfilSrcList,Dta);}
void __fastcall SetCurveSource(TDtaSource *Dta)
    {SetComboListItem(CurveSrcList,Dta);}
void __fastcall SetEditedSource(TDtaSource *Dta)
    {SetComboListItem(EditedSrcList,Dta);}
public:		// User declarations
    __fastcall TVisSetFrm(TComponent* Owner);
    __fastcall ~TVisSetFrm(void);
    void __fastcall SetRoadId(__int32 roadid,TDictSource *dict);
    void __fastcall SetMainSource(TDtaSource *data);
    bool __fastcall GetVisible(int max,bool *mask,TDtaSource *data);
    bool __fastcall SetVisible(int max,bool *mask,TDtaSource *data);
    bool __fastcall SourceVisible(TDtaSource *data);
    bool __fastcall SourceVisible(__int32 dataclass);
    void __fastcall SetSourceVisible(TDtaSource *data);
    void __fastcall SetSourceVisible(TDtaSource *data, bool vis);    
    void __fastcall ReleaseData(void);
    __property TDtaSource* MetricSource={read=FMainSource,write=SetMetricSource};
    __property TDtaSource* EditedSource={read=FEditedSource,write=SetEditedSource};
    __property TDtaSource* ProfilSource={read=FProfilSource,write=SetProfilSource};
    __property TDtaSource* VideoSource={read=FVideoSource,write=SetVideoSource};
    __property TDtaSource* CurveSource={read=FCurveSource,write=SetCurveSource};
    __property TObjList<TDtaSource> *DataList={read=FDataList};
    __property TRoadFrm* RoadFrm={read=FRoadFrm,write=FRoadFrm};
};
//---------------------------------------------------------------------------
extern PACKAGE TVisSetFrm *VisSetFrm;
//---------------------------------------------------------------------------
#endif
