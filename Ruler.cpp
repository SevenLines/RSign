//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Ruler.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

void __fastcall TRuler::SetFont(TFont *font)
{
FFont->Assign(font);
Invalidate();
}

void __fastcall TRuler::SetMinMax(bool d,double min,double max,int dr,int dl)
    {
    if ((d!=FDir)||(FMin!=min)||(FMax!=max)||(FDrwStart!=dr)||(FDrwLen!=dl))
        {FDir=d;FMin=min;FMax=max;FDrwStart=dr,FDrwLen=dl;Paint();}
    }

void __fastcall TRuler::SetMarker(double Pos)
{
HideMarker();
FMarker=Pos;
DrawMarker();
}

void __fastcall TRuler::SetKind(TRulerKind k)
{
if (FKind!=k)
    {
    FKind=k;
    Invalidate();
    }
}

void __fastcall TRuler::HideMarker(void)
{
if (FMarkerVisible)
    DrawMarker();
}

void __fastcall TRuler::DrawMarker(void)
{
double dl=FMax-FMin;
if (dl>1)
    {
    FMarkerVisible=!FMarkerVisible;
    Canvas->Pen->Style=psDash;
    Canvas->Pen->Mode=pmXor;
    Canvas->Pen->Color=TColor(RGB(255,255,0));
    if (Kind==rkGorisontal)
        {
        __int32 x=(FMarker-FMin)*FDrwLen/dl+FDrwStart;
        if (!FDir)
            x=Width-x;
        Canvas->MoveTo(x,0);
        Canvas->LineTo(x,Height);
        }
    else
        {
        __int32 x=(FMarker-FMin)*FDrwLen/dl+FDrwStart;
        if (!FDir)
            x=Height-x;
        Canvas->MoveTo(0,x);
        Canvas->LineTo(Width,x);
        }
    }
}

void __fastcall TRuler::Paint(void)
{
Canvas->Font->Assign(Font);
int h=Font->Height;
if (h<0)
    h=-h;
Canvas->Brush->Color=clWhite;
Canvas->Brush->Style=bsSolid;
Canvas->Pen->Style=psSolid;
Canvas->Pen->Mode=pmCopy;
Canvas->Pen->Color=clWhite;
Canvas->Rectangle(0,0,Width,Height);
double d=FMax-FMin;
double dl=d;
int k=FDrwLen/40; // Максимальное число больших делений
if (k<=0)
    return;
double s=1; // Шаг между большими делениями
while (d>k)
    d/=10,s*=10;
double minval=floor(FMin/s)*s;
double maxval=ceil(FMax/s)*s;
double s1; //Шаг маленьких делений
if (dl>1)
    {
    double pixs=FDrwLen*s/dl;
    if (pixs>80)
        s1=s/10;
    else if (pixs>40)
        s1=s/5;
    else if (pixs>15)
        s1=s/2;
    if (!s)
        s=1;
    if (!s1)
        s1=1;
    if (minval!=maxval)
    for (double i=minval;i<=maxval;i+=s)
    {
    int x=(i-FMin)*FDrwLen/dl+FDrwStart;
    Canvas->Pen->Width=3;
    Canvas->Pen->Color=clBlack;
    if (Kind==rkGorisontal)
        {
        if (!FDir)
            x=Width-x;
        Canvas->MoveTo(x,h);
        Canvas->LineTo(x,Height);
        Canvas->TextOut(x-Canvas->TextWidth(String(i))/2,0,String(i));
        }
    else
        {
        if (!FDir)
            x=Height-x;
        Canvas->MoveTo(h,x);
        Canvas->LineTo(Width,x);
        Canvas->TextOut(0,x-Canvas->TextWidth(String(i))/2,String(i));
        }
    Canvas->Pen->Width=1;


    for (double j=s1;j<s;j+=s1)
        {
        __int32 y=(i-FMin+j)*FDrwLen/dl+FDrwStart;
        if (Kind==rkGorisontal)
            {
            if (!FDir)
                y=Width-y;
            Canvas->MoveTo(y,h);
            Canvas->LineTo(y,Height);
            }
        else
            {
            if (!FDir)
                y=Height-y;
            Canvas->MoveTo(h,y);
            Canvas->LineTo(Width,y);
            }
        }
    }
    }
FMarkerVisible=false;
DrawMarker();
}