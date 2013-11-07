//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProcForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProcEdit *ProcEdit;
//---------------------------------------------------------------------------
__fastcall TProcEdit::TProcEdit(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TProcEdit::RadioGroup1Click(TObject *Sender)
{
GroupBox1->Visible=RadioGroup1->ItemIndex==0;
GroupBox2->Visible=RadioGroup1->ItemIndex==1;
GroupBox3->Visible=RadioGroup1->ItemIndex==2;
GroupBox4->Visible=RadioGroup1->ItemIndex==3;
GroupBox5->Visible=RadioGroup1->ItemIndex==4;
GroupBox6->Visible=RadioGroup1->ItemIndex==5;
GroupBox7->Visible=RadioGroup1->ItemIndex==6;
GroupBox8->Visible=RadioGroup1->ItemIndex==7;
}
//---------------------------------------------------------------------------
void __fastcall TProcEdit::SetParams(TDrwParamRec *Rec)
{
FId=Rec->Id;
TDrwParamRec1 *Rec1=dynamic_cast<TDrwParamRec1*>(Rec);
if (Rec1)
        {
        PenNum1->Text=Rec1->PenId;
        BrushNum1->Text=Rec1->BrushId;
        RadioGroup1->ItemIndex=0;
        return;
        }
TDrwParamRec2 *Rec2=dynamic_cast<TDrwParamRec2*>(Rec);
if (Rec2)
        {
        PenNum2->Text=Rec2->PenId;
        PenWidth2->Text=Rec2->Width;
        PenScale2->ItemIndex=int(Rec2->ScaleKind);
        PenStyle2->Text=Rec2->Style;
        PenOffset2->Text=Rec2->Offset;
        RadioGroup1->ItemIndex=1;
        return;
        }
TDrwParamRec3 *Rec3=dynamic_cast<TDrwParamRec3*>(Rec);
if (Rec3)
        {
        MetaMeasure3->ItemIndex=Rec3->Measure;
        MetaNum3->Text=Rec3->MetaId;
        Width3->Text=Rec3->Width;
        Height3->Text=Rec3->Height;
        DX3->Text=Rec3->DX;
        DY3->Text=Rec3->DY;
        Left3->Text=Rec3->DataRect.left;
        Top3->Text=Rec3->DataRect.top;
        Right3->Text=Rec3->DataRect.right;
        Bottom3->Text=Rec3->DataRect.bottom;
        RadioGroup1->ItemIndex=2;
        return;
        }
TDrwParamRec4 *Rec4=dynamic_cast<TDrwParamRec4*>(Rec);
if (Rec4)
        {
        PenNum4->Text=Rec4->PenId;
        Length4->Text=Rec4->TaleLength;
        PenWidth4->Text=Rec4->Width;
        PenScale4->ItemIndex=(int)Rec4->ScaleKind;
        RadioGroup1->ItemIndex=3;
        return;
        }
TDrwParamRec5 *Rec5=dynamic_cast<TDrwParamRec5*>(Rec);
if (Rec5)
        {
        PenNum5->Text=Rec5->PenId;
        BrushNum5->Text=Rec5->BrushId;
        Shift5->Text=Rec5->Shift;
        Width5->Text=Rec5->Width;
        Dash5->Text=Rec5->Dash;
        Space5->Text=Rec5->Space;
        Offset5->Text=Rec5->Offset;
        RadioGroup1->ItemIndex=4;
        return;
        }
TDrwParamRec6 *Rec6=dynamic_cast<TDrwParamRec6*>(Rec);
if (Rec6)
        {
        PenNum6->Text=Rec6->PenId;
        BrushNum6->Text=Rec6->BrushId;
        Shift6->Text=Rec6->Shift;
        Space6->Text=Rec6->Space;
        Offset6->Text=Rec6->Offset;
        Kind6->ItemIndex=Rec6->Kind;
        PenScale6->ItemIndex=int(Rec6->ScaleKind);
        Size6->Text=Rec6->Size;
        OrSize6->Text=Rec6->OrSize;
        RadioGroup1->ItemIndex=5;
        return;
        }
TDrwParamRec7 *Rec7=dynamic_cast<TDrwParamRec7*>(Rec);
if (Rec7)
    {
    PenNum7->Text=Rec7->PenId;
    Shift7->Text=Rec7->Shift;
    RadioGroup1->ItemIndex=6;
    return;
    }
TDrwParamRec8 *Rec8=dynamic_cast<TDrwParamRec8*>(Rec);
if (Rec8)
    {
    PenNum8->Text=Rec8->PenId;
    Length8->Text=Rec8->Length;
    Kind8->ItemIndex=Rec8->Kind;
    RadioGroup1->ItemIndex=7;
    return;
    }
}

TDrwParamRec* __fastcall TProcEdit::GetParams(void)
{
switch (RadioGroup1->ItemIndex)
        {
        case 0: return new TDrwParamRec1(PenNum1->Text.ToInt(),BrushNum1->Text.ToInt(),FId,1);
        case 1:
            {
            TDrwParamRec2 *Rec=new TDrwParamRec2(FId,2);
            Rec->SetPen(PenNum2->Text.ToInt(),PenWidth2->Text.ToInt(),TScaleKind(PenScale2->ItemIndex));
            Rec->SetStyle(PenStyle2->Text);
            Rec->SetOffset(PenOffset2->Text.ToInt());
            return Rec;
            }
        case 2:
            {
            TDrwParamRec3 *Rec=new TDrwParamRec3(MetaMeasure3->ItemIndex,MetaNum3->Text.ToInt(),Width3->Text.ToInt(),Height3->Text.ToInt(),DX3->Text.ToInt(),DY3->Text.ToInt(),FId,3);
            Rec->DataRect=TRect(Left3->Text.ToInt(),Top3->Text.ToInt(),Right3->Text.ToInt(),Bottom3->Text.ToInt());
            return Rec;
            }
        case 3:
            {
            TDrwParamRec4 *Rec=new TDrwParamRec4(FId,4,Length4->Text.ToInt());
            Rec->SetPen(PenNum4->Text.ToInt(),PenWidth4->Text.ToInt(),TScaleKind(PenScale4->ItemIndex));
            return Rec;
            }
        case 4: {
                TDrwParamRec5 *Rec=new TDrwParamRec5(FId,5);
                Rec->SetDrawParam(PenNum5->Text.ToInt(),BrushNum5->Text.ToInt());
                Rec->SetLineParam(Width5->Text.ToInt(),Shift5->Text.ToInt());
                Rec->SetDashParam(Dash5->Text.ToInt(),Space5->Text.ToInt(),Offset5->Text.ToInt(),true);
                return Rec;
                }
        case 5: {
                TDrwParamRec6 *Rec=new TDrwParamRec6(FId,6);
                Rec->SetDrawParam(PenNum6->Text.ToInt(),BrushNum6->Text.ToInt());
                Rec->SetPen(PenNum6->Text.ToInt(),0,TScaleKind(PenScale6->ItemIndex));
                Rec->SetLineParam(Space6->Text.ToInt(),Offset6->Text.ToInt(),Shift6->Text.ToInt(),true);
                Rec->SetFigureParam(Kind6->ItemIndex,Size6->Text.ToInt(),OrSize6->Text.ToInt());
                return Rec;
                }
        case 6: return new TDrwParamRec7(PenNum7->Text.ToInt(),Shift7->Text.ToInt(),FId,7);
        case 7: return new TDrwParamRec8(PenNum8->Text.ToInt(),Length8->Text.ToInt(),Kind8->ItemIndex,FId,8);
        }
return NULL;
}


