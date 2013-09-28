//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "..\\SaveCursor\\ppSaveCursor.h"
#include "EditGeomParams.h"
#include "ShowVideo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "DBGridEh"
#pragma resource "*.dfm"
TfrmEditGeomData *frmEditGeomData;
//---------------------------------------------------------------------------
__fastcall TfrmEditGeomData::TfrmEditGeomData(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditGeomData::FormShow(TObject *Sender)
{
    TADODataSet* DS = new TADODataSet(NULL);
    DS->Connection = FConnection;
    DS->CommandText = "select * from Classifier where class_id = 79 order by id_";
    DS->Open();
    cbType->Items->Clear();
    while(!DS->Eof)
    {
        cbType->AddItem(DS->FieldByName("FullTitle")->AsString.Trim(), (TObject*)DS->FieldByName("id_")->AsInteger);
        DS->Next();
    }

    DataSource->DataSet = frmShowVideo->DSGeomConers;
    TColumnEh* NewColumn = DBGGeomParams->Columns->Add();
    NewColumn->WordWrap = true;
    NewColumn->Title->Caption = "Начало участка";
    NewColumn->FieldName = "StartPos";
    NewColumn = DBGGeomParams->Columns->Add();
    NewColumn->WordWrap = true;
    NewColumn->Title->Caption = "Конец участка";
    NewColumn->FieldName = "EndPos";
    NewColumn = DBGGeomParams->Columns->Add();
    NewColumn->WordWrap = true;
    NewColumn->Title->Caption = "Тип кривой";
    NewColumn->FieldName = "FullTitle";
    NewColumn = DBGGeomParams->Columns->Add();
    NewColumn->WordWrap = true;
    NewColumn->Title->Caption = "Радиус поворота";
    NewColumn->FieldName = "Value2";

    UpdateTXTControls(NULL);

}
//---------------------------------------------------------------------------
void __fastcall TfrmEditGeomData::UpdateTXTControls(TObject *Sender)
{
    this->txtStartPos->Text = frmShowVideo->DSGeomConers->FieldByName("StartPos")->AsString;
    this->txtEndPos->Text = frmShowVideo->DSGeomConers->FieldByName("EndPos")->AsString;
    this->txtRadius->Text = frmShowVideo->DSGeomConers->FieldByName("Value2")->AsString;
    for(int i = 0; i < cbType->Items->Count; i++)
    {
        if((int)cbType->Items->Objects[i] == frmShowVideo->DSGeomConers->FieldByName("Reference")->AsInteger)
        {
            cbType->ItemIndex = i;
            break;
        }
    }
}
void __fastcall TfrmEditGeomData::cmdChangeClick(TObject *Sender)
{
    if(txtStartPos->Text.IsEmpty())
    {
        Application->MessageBoxA("Вы не заполнили поле\nНАЧАЛО УЧАСТКА!", "Ошибка", 0);
        txtStartPos->SetFocus();
        return;
    }
    if(txtEndPos->Text.IsEmpty())
    {
        Application->MessageBoxA("Вы не заполнили поле\nКОНЕЦ УЧАСТКА!", "Ошибка", 0);
        txtEndPos->SetFocus();
        return;
    }
    if((int)cbType->Items->Objects[cbType->ItemIndex] == 2385045 && txtRadius->Text.IsEmpty()) //Круговая кривая
    {
        Application->MessageBoxA("Вы не заполнили поле\nРАДИУС!", "Ошибка", 0);
        txtRadius->SetFocus();
        return;
    }
    if(txtStartPos->Text.ToInt() >= txtEndPos->Text.ToInt())
    {
        Application->MessageBoxA("Значение поля НАЧАЛО УЧАСТКА больше или равно поля КОНЕЦ УЧАСТКА", "Ошибка", 0);
        txtRadius->SetFocus();
        return;
    }
    TADODataSet* DS = frmShowVideo->DSGeomConers;
    AnsiString lcStartPos = txtStartPos->Text;
    AnsiString lcEndPos = txtEndPos->Text;
    AnsiString lcRadius = txtRadius->Text;
    AnsiString lcFullTitle = cbType->Items->Strings[cbType->ItemIndex];
    int lcTypeID = (int)cbType->Items->Objects[cbType->ItemIndex];
//сначала удаляем все отрезки которые входят в введеный отрезок
    DS->Filtered = false;
    DS->Filter = "StartPos >= "+ txtStartPos->Text +" and EndPos <= "+ txtEndPos->Text;
    DS->Filtered = true;
    while(!DS->Eof)
    {
        DS->Edit();
        DS->Delete();
    }
    DS->Filtered = false;
//введенный отрезок пересекает справа
    DS->Filter = "EndPos > "+ lcStartPos + " and EndPos <= " + lcEndPos;
    if(DS->FindFirst())
    {
        DS->Edit();
        DS->FieldValues["EndPos"] = lcStartPos;
        DS->Post();
    }
    DS->Filtered = false;
//введенный отрезок пересекает слева
    DS->Filter = "StartPos < "+ lcEndPos + " and StartPos >= " + lcStartPos;
    if(DS->FindLast())
    {
        DS->Edit();
        DS->FieldValues["StartPos"] = lcEndPos;
        DS->Post();
    }
    DS->Filtered = false;
//введенный отрезок входит в другой отрезок
    DS->Filter = "StartPos < "+ lcStartPos + " and EndPos > "+ lcEndPos;
    if(DS->FindFirst())
    {
        int LStartPos = DS->FieldByName("StartPos")->AsInteger;
        int LEndPos = DS->FieldByName("EndPos")->AsInteger;
        AnsiString LRadius = DS->FieldByName("Radius")->AsString;
        int LType = DS->FieldByName("Type")->AsInteger;
        AnsiString LFullTitle = DS->FieldByName("FullTitle")->AsString; 
        DS->Edit();
        DS->FieldValues["EndPos"] = lcStartPos;
        DS->Post();
        DS->Append();
        DS->FieldValues["NumRoad"] = frmShowVideo->ID_Road;
        DS->FieldValues["NumDataSource"] = frmShowVideo->DataSource;
        DS->FieldValues["StartPos"] = lcEndPos;
        DS->FieldValues["EndPos"] = LEndPos;
        DS->FieldValues["Reference"] = LType;
        DS->FieldValues["NumPartType"] = 34;
        DS->FieldValues["Value2"] = LRadius;
        DS->FieldValues["FullTitle"] = LFullTitle;
        DS->Post();
    }
    DS->Edit();
    DS->Append();
    DS->FieldValues["NumRoad"] = frmShowVideo->ID_Road;
    DS->FieldValues["NumDataSource"] = frmShowVideo->DataSource;
    DS->FieldValues["StartPos"] = lcStartPos;
    DS->FieldValues["EndPos"] = lcEndPos;
    DS->FieldValues["Value2"] = lcRadius;
    DS->FieldValues["FullTitle"] = lcFullTitle;
    DS->FieldValues["Reference"] = lcTypeID;
    DS->FieldValues["NumPartType"] = 34;
    DS->Post();
    DS->Sort = "StartPos ASC";
//1 вариант введенный отрезок пересекает слева
//2 вариант введенный отрезок пересекает справа
//3 вариант введенный отрезок входит в другой отрезок
//4 вариант введенный отрезок поглащает другой отрезок
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditGeomData::Button3Click(TObject *Sender)
{
    this->DBGGeomParams->DataSource = NULL;
    SaveDataSet(frmShowVideo->DSGeomConers, "ListRoadParts", "id_", "id_", "NumPartType,NumRoad,Reference,StartPos,EndPos,Value2,NumDataSource", "NumPartType,NumRoad,Reference,StartPos,EndPos,Value2,NumDataSource");
    this->DBGGeomParams->DataSource = this->DataSource;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditGeomData::DBGGeomParamsDblClick(TObject *Sender)
{
//пытаемся установить видео в нужное место
    if(frmShowVideo->MPlayer->Mode != mpPlaying)
    {
        frmShowVideo->txtDistRoad->Text = frmShowVideo->DSGeomConers->FieldByName("StartPos")->AsString;
        frmShowVideo->cmdPlayClick(NULL);
    }
}
//---------------------------------------------------------------------------

