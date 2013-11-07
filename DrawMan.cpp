//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DrawMan.h"
#include "common.h"
#include "SettingFrm.h"
#include <math.h>

// Размер радиуса кружка в точке установки знака в 0.1 мм
#define ELRAD 10

//---------------------------------------------------------------------------
#pragma package(smart_init)

/*
void __fastcall TDrawContents::ConvertPoint(__int32 L,__int32 X,__int32 &PX,__int32 &PY)
{
double KL=(double)FWidth/(L2-L1);
double KX=(double)FHeight/(X2-X1);
PX=(L-L1)*KL;
PY=(X-X1)*KX;
}
void __fastcall TDrawContents::ConvertPoly(__int32 n, TRoadPoint *in, POINT *out)
{
double KL=(double)FWidth/(L2-L1);
double KX=(double)FHeight/(X2-X1);
for (int i=0;i<n;i++)
    {
    out[i].x=(in[i].L-L1)*KL;
    out[i].y=(in[i].X-X1)*KX;
    }

}
*/

void __fastcall TDrawBitmap::DrawTo(TCanvas *canvas,int X,int Y)
{
HDC bdc1=CreateCompatibleDC(NULL);
::SelectObject(bdc1,FBitmap);
BitBlt(canvas->Handle,X,Y,FWidth-1,FHeight-1,bdc1,0,0,SRCCOPY);
DeleteDC(bdc1);
}

bool __fastcall TDrawBitmap::PrepareUpdating(void)
{
TDrawContents::PrepareUpdating();
FreeBitmap();
HDC dc=GetDC(0);
FBitmap=CreateCompatibleBitmap(dc,FWidth,FHeight);
ReleaseDC(0,dc);
if (FBitmap)
    {
    Fdc=CreateCompatibleDC(NULL);
    SelectObject(Fdc,FBitmap);
    }
return
    FBitmap!=NULL;
}

void __fastcall TDrawBitmap::FinishUpdating(void)
{
TDrawContents::FinishUpdating();
DeleteDC(Fdc);
}

void __fastcall TDrawBitmap::FreeBitmap(void)
{
if (FBitmap)
   DeleteObject(FBitmap);
}

bool __fastcall TPrintContents::PrepareUpdating(void)
{
TDrawContents::PrepareUpdating();
Printer()->Orientation=poLandscape;
Printer()->BeginDoc();
FWidth=Printer()->PageWidth;
FHeight=Printer()->PageHeight;
return true;
}

void __fastcall TPrintContents::FinishUpdating(void)
{
TDrawContents::FinishUpdating();
Printer()->EndDoc();
}

void __fastcall TMetaContents::FreeMetaFile(void)
{
if (FMetaFile)
    DeleteEnhMetaFile(FMetaFile);
}

bool __fastcall TMetaContents::PrepareUpdating(void)
{
TDrawContents::PrepareUpdating();
HDC dc=GetDC(0);
int dpi=GetDeviceCaps(dc,LOGPIXELSX);
Fdc=CreateEnhMetaFile(dc,FFileName.c_str(),&TRect(0,0,(FWidth*2540)/dpi,(FHeight*2540)/dpi),"File from RSign");
ReleaseDC(0,dc);
return Fdc!=NULL;
}

void __fastcall TMetaContents::FinishUpdating(void)
{
TDrawContents::FinishUpdating();
FMetaFile=CloseEnhMetaFile(Fdc);
}

__fastcall TRectsManager::TRectsManager(void)
{
FCount=0;
FMemCount=0;
Rects=NULL;
SortedRects=NULL;
}

__fastcall TRectsManager::~TRectsManager(void)
{Clear();}

void __fastcall TRectsManager::Clear(void)
{
delete[] Rects;
Rects=NULL;
delete[] SortedRects;
SortedRects=NULL;
FMemCount=FCount=0;
}

void __fastcall TRectsManager::NewSession(int n,int dir)
{
Clear();
FMemCount=n;
FDirection=dir;
Rects=new TExtRect[FMemCount];
SortedRects=new TExtRect* [FMemCount];
}

void __fastcall TRectsManager::PutRect(int index,RECT &r)
{
if (Rects[index].SelfIndex==-1) // Прямоугольник добавляется
    {
    Rects[index]=TExtRect(index,r);
    int i;
    int val=Rects[index].Dimention(FDirection);
    for (i=FCount-1;i>=0;i--)
        {
        if (val>=SortedRects[i]->Dimention(FDirection))
            break;
        else
            (SortedRects[i+1]=SortedRects[i])->SortedIndex++;
        }
    SortedRects[i+1]=Rects+index;
    Rects[index].SortedIndex=i+1;
    FCount++;
    }
else  // Прямоугольник замещается
    {
    int oldval=Rects[index].Dimention(FDirection);
    int oldsrtindex=Rects[index].SortedIndex;
    Rects[index]=TExtRect(index,r);
    int val=Rects[index].Dimention(FDirection);
    if (val>oldval) // Новый прямоугольник дальше старого
        {  // Надо сдвинуть все прямоугольники от старого до нового назад
        int i;
        for (i=oldsrtindex+1;i<FCount;i++)
            if (val<SortedRects[i]->Dimention(FDirection))
                break;
            else
                (SortedRects[i-1]=SortedRects[i])->SortedIndex--;
        SortedRects[i-1]=Rects+index;
        Rects[index].SortedIndex=i-1;
        }
    else    //Новый прямоугольник ближе старого
        {  //Надо сдвинуть прямоугольники от старого до нового вперед
        int i;
        for (i=oldsrtindex-1;i>=0;i--)
            if (val>=SortedRects[i]->Dimention(FDirection))
                break;
            else
                (SortedRects[i+1]=SortedRects[i])->SortedIndex++;
        SortedRects[i+1]=Rects+index;
        Rects[index].SortedIndex=i+1;
        }
    }
}

bool inline Cross(int h1,int e1,int h2,int e2)
{
return (h2<e1)&&(e2>h1);
}

void __fastcall MySortInt(int * ar,int n)  // Как я думаю, должен быстро сортировать почти упорядоченные массивы
{
if (n>0)
    {
    int *ar1=new int [n];
    int *ar2=new int [n];
    int k1=0;
    ar1[0]=ar[0];
    int k2=-1;                // Выделяет упорядоченный подмассив ar1
    for (int i=1;i<n;i++)
        if (ar[i]>=ar1[k1])
            ar1[++k1]=ar[i];
        else
            ar2[++k2]=ar[i];
    if (k2>=0)
        {
        MySortInt(ar2,k2+1);     // Сортируем остаток
        int i=0;
        int j=0;
        int k=0;
        while (j<=k2)           //Слияние
            {
            if (ar1[i]<ar2[j])
                ar[k++]=ar1[i++];
            else
                ar[k++]=ar2[j++];
            }
        while (i<=k1)
            ar[k++]=ar1[i++];
        }
    delete[] ar1;
    delete[] ar2;
    }

}

bool __fastcall TRectsManager::TestRect(RECT &r)
{
bool Result=true;
for (int i=0;i<FCount;i++)
    {
    if (SortedRects[i]->SortedIndex!=-1)
        {
        RECT *prect=&(SortedRects[i]->Rect);
        if (Cross(prect->left,prect->right,r.left,r.right)&&Cross(prect->top,prect->bottom,r.top,r.bottom))
            {
            Result=false;
            break;
            }
        }
    }
return Result;
}

// param=0 если упорядочивать надо сверху вниз, иначе param=1
void __fastcall TRectsManager::FindSignPlacement(int param,RECT &r)
{
int n=0;
int memsize=16;
int *starts=new int [memsize];
int *ends=new int [memsize];
int findpos=param==0 ? r.top:-r.bottom; // Начинаем искать подходящее расположение с этой точки
int findsize=r.bottom-r.top;
for (int i=0;i<FCount;i++)
    if (SortedRects[i]->SortedIndex!=-1)
        {
        RECT *prect=&(SortedRects[i]->Rect);
        if (Cross(prect->left,prect->right,r.left,r.right))
            {
            if (n>=memsize)
                {
                int *oldst=starts;
                int *olden=ends;
                memsize*=2;
                starts=new int [memsize];
                ends=new int [memsize];
                memcpy(starts,oldst,n*sizeof(int));
                memcpy(ends,olden,n*sizeof(int));
                delete oldst;
                delete olden;
                }
            if (param)
                {
                starts[n]=-prect->bottom;
                ends[n]=-prect->top;
                }
            else
                {
                starts[n]=prect->top;
                ends[n]=prect->bottom;
                }
            n++;
            }
        }
if (n)
    {
    MySortInt(starts,n);
    MySortInt(ends,n);
    int i=0;
    int j=0;
    int k=0;
    while (i<n)
        {
        if (starts[i]<ends[j])
            {
            if (k==0)  //Текущий отрезок не занят
                {
                if (starts[i]-findpos>findsize)
                    break;
                }
            k++,i++;
            }
        else
            {
            k--;
            if (k==0)
                if (findpos<ends[j])
                    findpos=ends[j];
            j++;
            }
        }
    if (param)
        {
        int newpos=-(i<n?findpos:ends[n-1]);
        if (newpos<r.bottom)
            r.bottom=newpos;
        r.top=r.bottom-findsize;
        }
    else
        {
        int newpos=i<n?findpos:ends[n-1];
        if (newpos>r.top)
            r.top=newpos;
        r.bottom=r.top+findsize;
        }

    }
    delete[] starts;
    delete[] ends;    
}

void __fastcall TRectsManager::FindPlacement(int version,int param,int index,RECT &r)
{
if (version==1)
    {
    FindSignPlacement(param,r);
    PutRect(index,r);
    }
}

__fastcall TDrawManager::TDrawManager(void)
{
Road=NULL;
ObjCount=0;
Objs=NULL;
Sources=NULL;
Polys=NULL;
FVisSet=NULL;
FDict=NULL;
FSensetive=6;
FBaseScaleL=4000;
FBaseScaleX=500;
FBaseScaleP=500;
FDelVis=true;
FProVis=true;
FVisModeLength=5000;
FVisModeVisLength=300;
FVisModeMinStep=10;
FVisModeBorder=6;
}

__fastcall TDrawManager::TDrawManager(TVisSetFrm *NSetFrm,TDictSource* NDict,TSharedObjSource *NShared)
{
Road=NULL;
ObjCount=0;
Objs=NULL;
Sources=NULL;
Polys=NULL;
FVisSet=NSetFrm;
FDict=NDict;
FShared=Shared;
FSensetive=6;
FBaseScaleL=5000;
FBaseScaleX=2000;
FVisModeLength=5000;
FVisModeVisLength=300;
FVisModeMinStep=10;
FVisModeBorder=6;
}

__fastcall TDrawManager::~TDrawManager(void)
{
FreeHash();
}

void __fastcall TDrawManager::SetDefaults(TDrawManager *SourMan)
{
FVisSet=SourMan->VisSet;
FDict=SourMan->Dict;
FShared=SourMan->Shared;
FBaseScaleL=SourMan->BaseScaleL;
FBaseScaleX=SourMan->BaseScaleX;
FBaseScaleP=SourMan->BaseScaleP;
FFontSize=SourMan->FontSize;
FDelVis=SourMan->DelVis;
FProVis=SourMan->ProVis;
}

/*
int __fastcall TDrawManager::CutBy(__int32 n,TRoadPoint *Sour,POINT *Dest,TDrawContents *Cont)
{
__int32 L1=Cont->L1;
__int32 L2=Cont->L2;
int j,i=0;
int s=0;
// Здесь можно написать двоичный поиск.
while ((Sour[i].L<L1)&&(i<n))
    i++;
j=i;
while (Sour[j].L<L2)
    j++;
if ((i==n)||(j==0))
    return 0;         // Точки начинаются за областью вывода
if (i>0)
    {
    int DL=Sour[i].L-Sour[i-1].L;
    int X=Sour[i-1].X+(double)(Sour[i].X-Sour[i-1].X)*(Sour[i].L-L1)/(DL);
    int NX,NY;
    Cont->ConvertPoint(L1,X,NX,NY);
    Dest[s].x=NX;
    Dest[s].y=NY;
    s++;
    }
Cont->ConvertPoly(j-i,Sour+i,Dest+s);
s+=j-i;
if (j<n)
    {
    int DL=Sour[j].L-Sour[j-1].L;
    int X=Sour[j-1].X+(double)(Sour[j].X-Sour[j-1].X)*(L2-Sour[j].L)/(DL);
    int NX,NY;
    Cont->ConvertPoint(L2,X,NX,NY);
    Dest[s].x=NX;
    Dest[s].y=NY;
    s++;
    }
return s;
}
*/

void __fastcall TDrawManager::FreeHash(void)
{
for (int i=0;i<ObjCount;i++)
    delete Polys[i];
delete[] Polys;
delete[] Objs;
delete[] Sources;
RectsMan.Clear();
delete Road;
}

void __fastcall TDrawManager::SelectObjects(int codes,bool *Mask,__int32 L1,__int32 L2)
{
#ifndef GDIEDIT
ObjCount=0;
bool LMask[MAXCODEID];
if (FVisSet)
    {
    int Count=0;
    for (int j=0;j<FVisSet->DataList->Count;j++)
        {
        TDtaSource *Dta=FVisSet->DataList->Items[j];
        if (Dta)
            Count+=Dta->Objects->Count;
        }
    Objs=new TRoadObject* [Count];
    Sources=new TDtaSource* [Count];
    for (int j=0;j<FVisSet->DataList->Count;j++)
        {
        TDtaSource *Dta=FVisSet->DataList->Items[j];
        if (Dta)
            {
            TObjList<TRoadObject> *Src=Dta->Objects;
            FVisSet->GetVisible(MAXCODEID,LMask,Dta);
            for (int i=0;i<Src->Count;i++)
                {
                TRoadObject *obj=dynamic_cast<TRoadObject*>(Src->Items[i]);
                if (obj)
                 if (obj->DictId<codes)
                  if (Mask[obj->DictId]&&LMask[obj->DictId])
                   if (obj->DrwClassId>0)
                    if ((FDelVis)||(obj->Test!=stBad))
                      {
                      TDescreetRoadObject *dobj=dynamic_cast<TDescreetRoadObject*>(Src->Items[i]);
                      if (dobj)
                        {
                        if ((dobj->L<=L2)&&(dobj->L>=L1))
                            {
                            Objs[ObjCount]=dobj;
                            Sources[ObjCount]=Dta;
                            ObjCount++;
                            }
                        else if (dobj->Poly)
                            {
                            if (dobj->Poly->Count)
                                {
                                int minl,maxl;
                                dobj->Poly->GetMinMax(minl,maxl);
                                if ((minl<=L2)&&(maxl>=L1))
                                    {
                                    Objs[ObjCount]=dobj;
                                    Sources[ObjCount]=Dta;
                                    ObjCount++;
                                    }
                                }
                            }
                        }
                      else
                        {
                        TContRoadObject *cobj=dynamic_cast<TContRoadObject*>(Src->Items[i]);
                        if (cobj)
                            {
                            if ((cobj->LMin<L2)&&(cobj->LMax>L1))
                                {
                                Objs[ObjCount]=cobj;
                                Sources[ObjCount]=Dta;
                                ObjCount++;
                                }
                            }
                        }
                      }
                }
            }
        }
    }
#endif
}

void __fastcall TDrawManager::SortObjects(void)
{
// Сортировка по приоритетам. Предполагается, что
// приоритетов несколько (не очень много)
__int32 i,maxpri=0;
// Массив приоритетов
__int32 *Prior=new __int32 [ObjCount];
// Массив массивов ссылок на объекты и источники
TRoadObject ***SrtObj;
TDtaSource ***SrtDta;
for (i=0;i<ObjCount;i++)  //Заполняем массив приоритетов и находим максимальный
    {
    Prior[i]=Dict->DrwClasses->Items[Objs[i]->DrwClassId]->Priority;
    if (maxpri<Prior[i])
        maxpri=Prior[i];
    }
maxpri++;
// массив количества объектов каждого приоритета
__int32 *PriCount=new __int32 [maxpri];
for (i=0;i<maxpri;i++)
    PriCount[i]=0;
for (i=0;i<ObjCount;i++)
    PriCount[Prior[i]]++;
// создаем массив для массивов указателей
SrtObj=new TRoadObject** [maxpri];
SrtDta=new TDtaSource** [maxpri];
for (i=0;i<maxpri;i++)
    {
    SrtObj[i]=new TRoadObject* [PriCount[i]];
    SrtDta[i]=new TDtaSource* [PriCount[i]];
    }
// Готовимся к заполнению массива объектов
for (i=0;i<maxpri;i++)
    PriCount[i]=0;
// Заполняем
for (i=0;i<ObjCount;i++)
    {
    int p=Prior[i];
    SrtObj[p][PriCount[p]]=Objs[i];
    SrtDta[p][PriCount[p]]=Sources[i];
    PriCount[p]++;
    }
// Переписываем объекты обратно в массив по возрастанию приоритета
int n=0;
for (i=0;i<maxpri;i++)
    {
    int m=PriCount[i];
    for (int j=0;j<m;j++)
        {
        Objs[n]=SrtObj[i][j];
        Sources[n]=SrtDta[i][j];
        n++;
        }
    }
// Освобождаем память.
for (i=0;i<maxpri;i++)
    {
    delete[] SrtObj[i];
    delete[] SrtDta[i];
    }
delete[] SrtObj;
delete[] SrtDta;
delete[] PriCount;
delete[] Prior;
}

void __fastcall TDrawManager::PrepareMetric(TDrawContents *Cont,RECT *OutRect)
{
Road=new TRoad(FVisSet->MetricSource->Road,Cont->L1,Cont->L2);
if (FVisSet->MetricSource->ProfilKind&1)
    Road->CalcMinMaxZ();
Road->SetFrame(Cont->L1,Cont->L2,Cont->X1,Cont->X2,FPlanKind,FPlanDirect);
Road->SetOutBound(OutRect->left,OutRect->right,OutRect->top,OutRect->bottom);
Polys=new TExtPolyline*[ObjCount];
int dir=FPlanKind==pkGorizontal ? 0 :2;
dir+=FPlanDirect==pdDirect? 0 : 1;
RectsMan.NewSession(ObjCount,dir);
int n=0;
for (int i=0;i<ObjCount;i++)
    {
    Objs[n]=Objs[i];
    Sources[n]=Sources[i];
    Polys[n]=Objs[i]->PrepareMetric(Road);
    if (Polys[n])
        n++;
    }
ObjCount=n;
}

void __fastcall TDrawManager::FindSignsPlacement(TDrawContents *Cont)
{
TObjList<TDrwParamRec> *DrPar=Dict->DrwParams;
TObjList<TDrwClassesRec> *DrCl=Dict->DrwClasses;
TRoad *SRoad=new TRoad(FVisSet->MetricSource->Road,Cont->L1,Cont->L2);
// Устанавливаем параметры так, чтобы точка соответствоовала 0.1 мм в масштабе вывода
SRoad->SetFrame(Cont->L1,Cont->L2,SRoad->XMin,SRoad->XMax,pkGorizontal,pdDirect);
SRoad->SetOutBound(0,(Cont->L2-Cont->L1)*100/FBaseScaleL,(SRoad->XMin*100)/FBaseScaleP,(SRoad->XMax*100)/FBaseScaleP);
SignsMan.NewSession(ObjCount,0);
int GostLabelSize=FFontSize*254*FBaseScaleX/(72*FBaseScaleP);
for (int i=0;i<ObjCount;i++)
    {
    TRoadSign *sign=dynamic_cast<TRoadSign*>(Objs[i]);
    if (sign)
        {
        TExtPolyline *pl=sign->PrepareMetric(SRoad);
        int x=pl->Points[0].x;
        int y=pl->Points[0].y;
        delete pl;
        int dir=GetSignDirection(sign,pkGorizontal,pdDirect);
        int plc=sign->Placement!=spRight? 1 : 0;
          if (sign->Direction!=roDirect)
              plc=1-plc;
        TDrwClassesRec *ClRec=DrCl->Items[sign->DrwClassId];
        TDrwParamRec3 *DrwRec=dynamic_cast<TDrwParamRec3*>(DrPar->Items[ClRec->DrwParamId[0]]);
        if (DrwRec)
            {
            int DrwWidth=(DrwRec->Width*FBaseScaleX)/FBaseScaleP;
            int DrwHeight=(DrwRec->Height*FBaseScaleX)/FBaseScaleP;
            int DrwDX=(DrwRec->DX*FBaseScaleX)/FBaseScaleP;
            int DrwDY=(DrwRec->DY*FBaseScaleX)/FBaseScaleP;
            RECT r;
            int signheight=dir&1? DrwWidth : DrwHeight;
            if (plc)
                r.top=y-3*ELRAD-signheight;
            else
                r.top=y+3*ELRAD;
            switch (dir)
                {
                case 0: {r.bottom=r.top+DrwHeight;
                    r.left=x-DrwDX;r.right=r.left+DrwWidth;} break;
                case 1: {r.bottom=r.top+DrwWidth;
                    r.left=x-DrwDY;r.right=r.left+DrwHeight;} break;
                case 2: {r.bottom=r.top+DrwHeight;
                    r.right=x+DrwDX;r.left=r.right-DrwWidth;} break;
                case 3: {r.bottom=r.top+DrwWidth;
                    r.right=x+DrwDY;r.left=r.right-DrwHeight;} break;
                }
            if (plc)   // Учитываем подпись для кода Gibdd
                r.right+=GostLabelSize;
            else
                r.left-=GostLabelSize;
            SignsMan.FindPlacement(1,plc,i,r);
            if (plc)   // Восстанавливаем размер прямоугольника
                r.right-=GostLabelSize;
            else
                r.left+=GostLabelSize;
            int px,py;
            switch (dir)
                {
                case 0:{py=r.top+DrwDY;px=r.left+DrwDX;}break;
                case 1:{py=r.bottom-DrwDX;px=r.left+DrwDY;}break;
                case 2:{py=r.bottom-DrwDY;px=r.right-DrwDX;}break;
                case 3:{py=r.top+DrwDX;px=r.right-DrwDY;}break;
                }
            int RL,RX;
            SRoad->RConvertPoint(px,py,RL,RX);
            SignsMan.Rects[i].RoadL=RL;
            SignsMan.Rects[i].RoadX=RX;
            }
        }
    }
delete SRoad;
}

void __fastcall TDrawManager::DrawSignLabel(TDrawContents *Cont,int dir,RECT *r,String Caption)
{
HDC dc=Cont->GetContentDC();
if (dc)
    {
    // Разбиваем подпись на строки
    char *str=Caption.c_str();
    char *s=str;
    int n=Caption.Length();
    int lcount=1;
    int hline[64];
    SIZE wline[64];
    hline[0]=0;
    for (int i=0;i<n;i++)
        {
        if ((*s=='\n')||(*s=='\\'))
            hline[lcount++]=i+1;
        s++;
        }
    hline[lcount]=n+1;
    // Считаем размер шрифта от количества строк и рамки
    int size;
    if (dir&1)   // Предполагается полуторный интервал между строками
        size=2*(r->right-r->left)/(3*lcount-1);
    else
        size=2*(r->bottom-r->top)/(3*lcount-1);
    if (size>3)
        {
        // Определяем шрифт
        LOGFONT fn;
        GetObject(GetStockObject(SYSTEM_FONT),sizeof(LOGFONT),&fn);
        fn.lfHeight=-size;
        fn.lfWidth=0;
        switch (dir)
            {
            case 0:fn.lfEscapement=0;break;
            case 1:fn.lfEscapement=900;break;
            case 2:fn.lfEscapement=1800;break;
            case 3:fn.lfEscapement=2700;break;
            }
        strcpy(fn.lfFaceName,"Arial");
        SelectObject(dc,CreateFontIndirect(&fn));
        // Ищем размер надписи с использованием шрифта
        for (int i=0;i<lcount;i++)
            GetTextExtentPoint(dc,str+hline[i],hline[i+1]-hline[i]-1,wline+i);
        int width=wline[0].cx;
        for (int i=1;i<lcount;i++)
            if (width<wline[i].cx)
                width=wline[i].cx;
        int height=wline[0].cy*lcount;
        int textx,texty;
        textx=((r->right+r->left)>>1);
        texty=((r->top+r->bottom)>>1);
        switch (dir)
            {
            case 0:{textx-=width>>1;texty-=height>>1;}break;
            case 1:{textx-=height>>1;texty+=width>>1;}break;
            case 2:{textx+=width>>1;texty+=height>>1;}break;
            case 3:{textx+=height>>1;texty-=width>>1;}break;
            }
        size=(size*3)>>1;  // Учитаваем полуторный интервал
        for (int i=0;i<lcount;i++)
            {
            TextOut(dc,textx,texty,str+hline[i],hline[i+1]-hline[i]-1);
            switch (dir)
                {
                case 0:texty+=size;break;
                case 1:textx+=size;break;
                case 2:texty-=size;break;
                case 3:textx-=size;break;
                }
            }
        DeleteObject(SelectObject(dc,GetStockObject(SYSTEM_FONT)));
        }
    }
}

void __fastcall TDrawManager::DrawLabel(TDrawContents *Cont,TPlanLabel *l)
{
HDC dc=Cont->GetContentDC();
if (dc)
        {
        double scale;
        if (l->ScaleKind==skByL)
                scale=(double)FBaseScaleL/FSclL*FDpsm*(2.54/72);
        else
                scale=(double)FBaseScaleX/FSclX*FDpsm*(2.54/72);
        int size=l->Size*scale;
        if (size>3)
           {
           LOGFONT fn;
           GetObject(GetStockObject(SYSTEM_FONT),sizeof(LOGFONT),&fn);
           fn.lfHeight=-size;
           fn.lfWidth=0;
           strcpy(fn.lfFaceName,"Arial");
           bool vert=l->Orientation==oOrto;
           if (FPlanKind==pkVertical)
                vert=!vert;
           if (vert)
                fn.lfEscapement=2700;
           SelectObject(dc,CreateFontIndirect(&fn));
           char *str=l->Caption.c_str();
           char *s=str;
           int n=l->Caption.Length();
           int lcount=1;
           int hline[64];
           SIZE wline[64];
           hline[0]=0;
           for (int i=0;i<n;i++)
                if (*(s++)=='\n')
                        hline[lcount++]=i;
           hline[lcount]=n;
           for (int i=0;i<lcount;i++)
                GetTextExtentPoint32(dc,str+hline[i],hline[i+1]-hline[i],wline+i);
           int width=wline[0].cx;
           for (int i=1;i<lcount;i++)
                if (width<wline[i].cx)
                        width=wline[i].cx;
           int height=wline[0].cy*lcount;
           int textx,texty;
           textx=l->Pos.x;
           texty=l->Pos.y;
           if (vert)
                {
                switch (l->VertAlign)
                        {
                        case aBaseline:textx+=height>>1;break;
                        case aBottom:textx+=height;break;
                        }
                switch (l->HorzAlign)
                        {
                        case aCenter:texty-=width>>1;break;
                        case aRight:texty-=width;break;
                        }
                }
           else
                {
                switch (l->VertAlign)
                        {
                        case aBaseline:texty-=height>>1;break;
                        case aBottom:texty-=height;
                        }
                switch (l->HorzAlign)
                        {
                        case aCenter:textx-=width>>1;break;
                        case aRight:textx-=width;break;
                        }
                }
           int oldcolor=SetTextColor(dc,l->Color);
           TextOut(dc,textx,texty,l->Caption.c_str(),l->Caption.Length());
           SetTextColor(dc,oldcolor);
           DeleteObject(SelectObject(dc,GetStockObject(SYSTEM_FONT)));
           }
        }
}

#define MAXSIGN 16

void __fastcall TDrawManager::DrawObjects(TDrawContents *Cont,int flag)
{
HDC dc=Cont->GetContentDC();
if (dc)
  SetBkMode(dc,TRANSPARENT);

TObjList<TDrwParamRec> *DrPar=Dict->DrwParams;
TObjList<TDrwClassesRec> *DrCl=Dict->DrwClasses;
for (int i=0;i<ObjCount;i++)
    Objs[i]->Tag=1;
for (int i=0;i<ObjCount;i++)
  if (Objs[i]->Tag)
    {
    TRoadSign *sign=dynamic_cast<TRoadSign*>(Objs[i]);
    Objs[i]->Tag=0;
    if (sign)  // Как только встретили первый знак рисуем все знаки
        {
        for (int j=i;j<ObjCount;j++)
            {
            TRoadSign *sg=dynamic_cast<TRoadSign*>(Objs[j]);
            if (sg)
                DrawSignLines(Cont,j);
            }
        for (int j=i;j<ObjCount;j++)
            {
            TRoadSign *sg=dynamic_cast<TRoadSign*>(Objs[j]);
            if (sg)
                {
                sg->Tag=0;
                DrawSignImage(Cont,j);
                }
            }
        for (int j=i;j<ObjCount;j++)
            {
            TRoadSign *sg=dynamic_cast<TRoadSign*>(Objs[j]);
            if (sg)
                {
                DrawSignLabels(Cont,j);
                }
            }
/*      int Signs[MAXSIGN];
        int countc=0;
        int j=i;
        int signplc=sign->Placement==spRight ? 1 : sign->Placement==spLeft ? -1 : 0;
        if (sign->Direction==roUnDirect)
            signplc*=-1;
        while (j<ObjCount)
            {
            if ((sign->L+SignSpace<Objs[j]->L)||(Sources[i]!=Sources[j])||(countc>=MAXSIGN))
                break;
            TRoadSign *sg=dynamic_cast<TRoadSign*>(Objs[j]);
            if (sg)
                {
                int sgplc=sg->Placement==spRight ? 1 : sg->Placement==spLeft ? -1 : 0;
                if (sg->Direction==roUnDirect)
                    sgplc*=-1;
                if (sgplc==signplc)
                    {
                    Signs[countc]=j;
                    sg->Tag=0;
                    countc++;
                    }
                }
            j++;
            }
        DrawSign(Cont,countc,Signs,flag);
*/
        }
    else
        {
        if ((Objs[i]->Test==stBad)&&(!(flag&2)))
            continue;
        if ((Objs[i]->Test!=stBad)&&(!(flag&1)))
            continue;
        int drclass=Objs[i]->DrwClassId;
        TDrwClassesRec *ClRec=DrCl->Items[drclass];
        for (int k=0;k<MAXDRWPARAM;k++)
            {
            TDrwParamRec *Rec;
            try
                {Rec=DrPar->Items[ClRec->DrwParamId[k]];}
            catch (...) {}
            if (!Rec)
                continue;
            if (Rec->ProcId!=3)
                {
                RECT r;
                CalcRect(Polys[i],&r);
                RectsMan.PutRect(i,r);
                }
            else
                {
                RECT r;
                DrawMetafile(Cont,Polys[i],dynamic_cast<TDrwParamRec3*>(Rec),&r);
                RectsMan.PutRect(i,r);
                }
            switch (Rec->ProcId)
                {
                case 1: DrawArea(Cont,Polys[i],dynamic_cast<TDrwParamRec1*>(Rec)); break;
                case 2: DrawLine(Cont,Polys[i],dynamic_cast<TDrwParamRec2*>(Rec)); break;
                case 4: DrawBridge(Cont,Polys[i],dynamic_cast<TDrwParamRec4*>(Rec)); break;
//            case 5: DrawDash(Cont,PCount[i],Points[i],dynamic_cast<TDrwParamRec5*>(Rec)); break;
                case 6: DrawFigureLine(Cont,Objs[i]->ComponentCount(),Polys[i],dynamic_cast<TDrwParamRec6*>(Rec)); break;
//            case 7: DrawCurvesLine(Cont,PCount[i],Points[i],dynamic_cast<TDrwParamRec7*>(Rec)); break;
                case 8: DrawBordersLine(Cont,Polys[i],dynamic_cast<TDrwParamRec8*>(Rec)); break;
                }
            }
        }
    }
// Рисуем подписи
for (int i=0;i<ObjCount;i++)
    {
    int count=Objs[i]->GetTextsCount();
    for (int j=0;j<count;j++)
        {
        TPlanLabel *l=Objs[i]->GetText(j,Road,FDict);
        if (l)
                {
                DrawLabel(Cont,l);
                delete l;
                }
        }
    }
}

void __fastcall TDrawManager::CallDrawFunc(TDrawContents *Cont,TExtPolyline *Poly,TDrwParamRec *Rec,TRect *r,bool clear)
{
double dpsm=(double)GetDeviceCaps(Cont->DC,LOGPIXELSX)/2.54;
CallDrawFunc(Cont,Poly,Rec,r,FBaseScaleL,FBaseScaleX,pkGorizontal,pdDirect,dpsm,clear);
}

void __fastcall TDrawManager::CallDrawFunc(TDrawContents *Cont,TExtPolyline *Poly,TDrwParamRec *Rec,TRect* r,__int32 fl,__int32 fx,TPlanKind pk,TPlanDirect pd,double dpsm,bool clear)
{
HDC dc=Cont->DC;
SetBkMode(dc,TRANSPARENT);
FDpsm=dpsm;
FSclL=fl;
FSclX=fx;
FPlanKind=pk;
FPlanDirect=pd;
if (clear)
        {
        void *oldbr=SelectObject(dc,GetStockObject(WHITE_BRUSH));
        void *oldpn=SelectObject(dc,GetStockObject(NULL_PEN));
        Rectangle(dc,0,0,Cont->Width,Cont->Height);
        SelectObject(dc,oldbr);
        SelectObject(dc,oldpn);
        }
switch (Rec->ProcId)
        {
        case 1: DrawArea(Cont,Poly,dynamic_cast<TDrwParamRec1*>(Rec)); break;
        case 2: DrawLine(Cont,Poly,dynamic_cast<TDrwParamRec2*>(Rec)); break;
        case 3: DrawMetafile(Cont,Poly,dynamic_cast<TDrwParamRec3*>(Rec),r); break;
        case 4: DrawBridge(Cont,Poly,dynamic_cast<TDrwParamRec4*>(Rec)); break;
//        case 5: DrawDash(Cont,n,p,dynamic_cast<TDrwParamRec5*>(Rec)); break;
        case 6: DrawFigureLine(Cont,0,Poly,dynamic_cast<TDrwParamRec6*>(Rec)); break;
//        case 7: DrawCurvesLine(Cont,n,p,dynamic_cast<TDrwParamRec7*>(Rec)); break;
        case 8: DrawBordersLine(Cont,Poly,dynamic_cast<TDrwParamRec8*>(Rec)); break;
        }
}


void __fastcall TDrawManager::CalcRect(TExtPolyline* Poly,RECT *r)
{
POINT *p=Poly->Points;
int n=Poly->Count;
if (n)
    {
    r->right=r->left=p[0].x;
    r->top=r->bottom=p[0].y;
    for (int i=0;i<n;i++)
        {
        if (r->left>p[i].x)
            r->left=p[i].x;
        if (r->right<p[i].x)
            r->right=p[i].x;
        if (r->top>p[i].y)
            r->top=p[i].y;
        if (r->bottom<p[i].y)
            r->bottom=p[i].y;
        }
    }
}

void __fastcall TDrawManager::DrawPolygon(TDrawContents *Cont,TExtPolyline *Poly,int PenId,int BrushId)
{
HDC dc=Cont->GetContentDC();
if (dc)
    if (Poly)
        {
        void *br=GetGdiObj(BrushId);
        void *pen=GetGdiObj(PenId);
        Poly->DrawTo(dc,pen,br);
        }
}

void __fastcall TDrawManager::DrawArea(TDrawContents *Cont,TExtPolyline *Poly,TDrwParamRec1 *par)
{
if (par)
    DrawPolygon(Cont,Poly,par->PenId,par->BrushId);
}


void* __fastcall TDrawManager::GetGdiObj(int ObjId)
{
void* obj;
if (ObjId>0)
    {
    if (FPlanKind==pkGorizontal)
        obj=Shared->GorzGDIObjects->Items[ObjId];
    else
        obj=Shared->VertGDIObjects->Items[ObjId];
    }
else
    obj=GetStockObject(-ObjId);
return obj;
}

void* __fastcall TDrawManager::GetPen(TDrwParamRec *par,bool &needdel)
{
needdel=false;
void *pen=NULL;
if (par->PenId>0)
    {
    pen=GetGdiObj(par->PenId);
    if (par->Width>0)
        {
        double scale;
        if (par->ScaleKind==skByL)
            scale=(double)FBaseScaleL/FSclL*FDpsm/100;
        else
            scale=(double)FBaseScaleX/FSclX*FDpsm/100;
        int width=(double)par->Width*scale+0.5;
        unsigned long Styles[32];
        for (int i=0;i<par->StyleCount;i++)
            Styles[i]=par->Styles[i]*scale+0.5;
        EXTLOGPEN pn;
        GetObject(pen,sizeof(EXTLOGPEN),&pn);
        LOGBRUSH lb;
        lb.lbStyle=BS_SOLID;
        lb.lbColor=pn.elpColor;
        if (par->StyleCount)
            pen=ExtCreatePen(PS_GEOMETRIC|PS_USERSTYLE|pn.elpPenStyle,width,&lb,par->StyleCount,Styles);
        else
            pen=ExtCreatePen(PS_GEOMETRIC|pn.elpPenStyle,width,&lb,0,NULL);
        needdel=true;
        }
    else
        pen=GetStockObject(-par->PenId);
    }
return pen;
}

void __fastcall TDrawManager::DrawLine(TDrawContents *Cont,TExtPolyline *Poly,TDrwParamRec2 *par)
{
if (par)
    {
    HDC dc=Cont->GetContentDC();
    if (dc)
        {
        bool needdel;
        void *pen=GetPen(par,needdel);
        int ofs=(double)par->Offset*Poly->DirectionVal*FBaseScaleX/FSclX*FDpsm/100;
        if (FPlanDirect==pdUndirect)
            ofs*=-1;
        TExtPolyline *NPoly;
        if (FPlanKind==pkGorizontal)
            NPoly=new TExtPolyline(Poly,0,ofs);
        else
            NPoly=new TExtPolyline(Poly,ofs,0);
//        Poly->DrawPoly(dc,pen,GetStockObject(NULL_PEN));
        NPoly->PolyDraw(dc,pen,TRect(0,0,Cont->Width,Cont->Height));
        if (needdel)
            DeleteObject(pen);
        delete NPoly;
        }
    }

}

RECT* __fastcall TDrawManager::GetRect(int n)
{
if (n<ObjCount)
    {
    return &(RectsMan.Rects[n].Rect);
    }
return NULL;
}


int __fastcall TDrawManager::GetSignDirection(TRoadSign *sign,TPlanKind pk,TPlanDirect pd)
{
int Result=0;
bool dr=sign->Placement==spRight;
if (sign->Direction==roUnDirect)
    dr=!dr;
bool b=sign->Direction==roDirect;
if (pd==pdUndirect)
    b=!b,dr=!dr;
if (sign->OnAttach==saIn) // Виден при въезде на дорогу
    {
    if (pk!=pkGorizontal)
        Result=1;
    if (!dr) Result+=2;
    }
else if (sign->OnAttach==saOut)  //Виден при выезде с дороги
    {
    if (pk!=pkGorizontal)
        Result=1;
    if (dr) Result+=2;
    }
else
    {
    if (pk==pkGorizontal)
        {
        Result=1;
        if (b)
            Result+=2;
        }
    else if (!b)
        Result=2;
    }
return Result;
}

void __fastcall TDrawManager::CalcMetaRect(POINT *p,TDrwParamRec3 *par,RECT* rct,int dir,bool data)
{
if (par)
    {
    double scalex,scalel;
    if (par->Measure==1)
        {
        scalex=(double)FDpsm/FSclX;;
        scalel=(double)FDpsm/FSclL;
        }
    else
        {
        scalex=(double)FBaseScaleX/FSclX*FDpsm/100;
        scalel=(double)FBaseScaleX/FSclX*FDpsm/100;
        }
    __int32 w,h,dx,dy;
    if (data)
        {
        w=(par->DataRect.right-par->DataRect.left)*scalel;
        h=(par->DataRect.bottom-par->DataRect.top)*scalex;
        dx=(par->DX-par->DataRect.left)*scalel;
        dy=(par->DY-par->DataRect.top)*scalex;
        }
    else
        {
        w=par->Width*scalel;
        h=par->Height*scalex;
        dx=par->DX*scalel;
        dy=par->DY*scalex;
        }
    switch (dir)
        {
        case 0: // знак в нормальном положении
            {
            rct->left=p[0].x-dx;
            rct->top=p[0].y-dy;
            rct->right=rct->left+w;
            rct->bottom=rct->top+h;
            } break;
        case 1: // Поворот на 90 против часовой
            {
            rct->left=p[0].x-dy;
            rct->top=p[0].y+dx-w;
            rct->right=rct->left+h;
            rct->bottom=rct->top+w;
            } break;
        case 2: // знак повернут на 180
            {
            rct->left=p[0].x+dx-w;
            rct->top=p[0].y+dy-h;
            rct->right=rct->left+w;
            rct->bottom=rct->top+h;
            } break;
        case 3: // поворот на 90 против часовой
            {
            rct->left=p[0].x+dy-h;
            rct->top=p[0].y-dx;
            rct->right=rct->left+h;
            rct->bottom=rct->top+w;
            } break;
        }
    }
}

void __fastcall TDrawManager::DrawMetafile(TDrawContents *Cont,TExtPolyline *Poly,TDrwParamRec3 *par,RECT *rct)
{
if (par)
    {
    HDC dc=Cont->GetContentDC();
    if (dc)
        {
        int dir=0;
        if (FPlanKind==pkVertical)
            dir=1;
        if (FPlanDirect==pdUndirect)
            dir+=2;
//      Найдем угол для ориентированных метафайлов
//      углы только кратные 90
        if (Poly->Count>1)
            {
            int dx=Poly->Points[1].x-Poly->Points[0].x;
            int dy=Poly->Points[1].y-Poly->Points[0].y;
            int adx=abs(dx);
            int ady=abs(dy);
            dir=0;
            if ((dy<0)&&(ady>=adx)) // Угол вверх
                dir=1;
            else if ((dx<0)&&(adx>=ady)) // угол влево
                dir=2;
            else if ((dy>0)&&(ady>=adx)) // Угол вНиз
                dir=3;
//            dir=dir&3;
            }

//        TMetafile *mtf=Shared->Metas->Metas[par->MetaId];
        TMetafile *mtf=Shared->Metas->GetMetafile(par->MetaId,dir);
        CalcMetaRect(Poly->Points,par,rct,dir,false);
        PlayEnhMetaFile(dc,(void*)mtf->Handle,rct);
        }
    }
}

void __fastcall TDrawManager::DrawSignLines(TDrawContents *Cont,int ObjNum)
{
HDC dc=Cont->GetContentDC();
TRoadSign *sign=dynamic_cast<TRoadSign*>(Objs[ObjNum]);
if ((dc)&&(sign))
    {
    int ElRad=(FDpsm*ELRAD)/100+0.5;  // Радиус кружка
    int ArLen=(double)FBaseScaleX/FSclX*FDpsm/2;  // длина стрелки
    TExtRect *erect=SignsMan.Rects+ObjNum;
    int SignX,SignY; // Точка отображения метафайла
    Road->ConvertPoint(erect->RoadL,erect->RoadX,SignX,SignY);
    int direction=GetSignDirection(sign,FPlanKind,FPlanDirect);

    SelectObject(dc,CreatePen(PS_SOLID,FDpsm/100+0.5,0));
    SelectObject(dc,GetStockObject(WHITE_BRUSH));
    // Рисуем линию от кружка до картинки и кружок
    POINT *p=Polys[ObjNum]->Points;
    MoveToEx(dc,p[0].x,p[0].y,NULL);
    LineTo(dc,SignX,SignY);
    Ellipse(dc,p[0].x-ElRad,p[0].y-ElRad,p[0].x+ElRad,p[0].y+ElRad);
    MoveToEx(dc,p[0].x,p[0].y,NULL);
    // Рисуем стрелочку в зависимости от направления знака
    switch (direction)
        {
        case 0:
            {LineTo(dc,p[0].x,p[0].y-ArLen);
             LineTo(dc,p[0].x+ArLen/3,p[0].y-(ArLen>>1));
             MoveToEx(dc,p[0].x,p[0].y-ArLen,NULL);
             LineTo(dc,p[0].x-ArLen/3,p[0].y-(ArLen>>1));
            } break;
        case 1:
            {LineTo(dc,p[0].x-ArLen,p[0].y);
             LineTo(dc,p[0].x-(ArLen>>1),p[0].y+ArLen/3);
             MoveToEx(dc,p[0].x-ArLen,p[0].y,NULL);
             LineTo(dc,p[0].x-(ArLen>>1),p[0].y-ArLen/3);
            }break;
        case 2:
            {LineTo(dc,p[0].x,p[0].y+ArLen);
             LineTo(dc,p[0].x+ArLen/3,p[0].y+(ArLen>>1));
             MoveToEx(dc,p[0].x,p[0].y+ArLen,NULL);
             LineTo(dc,p[0].x-ArLen/3,p[0].y+(ArLen>>1));
            }break;
        case 3:
            {LineTo(dc,p[0].x+ArLen,p[0].y);
             LineTo(dc,p[0].x+(ArLen>>1),p[0].y+ArLen/3);
             MoveToEx(dc,p[0].x+ArLen,p[0].y,NULL);
             LineTo(dc,p[0].x+(ArLen>>1),p[0].y-ArLen/3);
            }break;
        }
    DeleteObject(SelectObject(dc,GetStockObject(BLACK_PEN)));
    }
}

void __fastcall TDrawManager::DrawSignImage(TDrawContents *Cont,int ObjNum)
{
HDC dc=Cont->GetContentDC();
TRoadSign *sign=dynamic_cast<TRoadSign*>(Objs[ObjNum]);
if ((dc)&&(sign))
    {
    int drclass=Objs[ObjNum]->DrwClassId;
    TDrwClassesRec *ClRec=Dict->DrwClasses->Items[drclass];
    TDrwParamRec3 *DrwRec=dynamic_cast<TDrwParamRec3*>(Dict->DrwParams->Items[ClRec->DrwParamId[0]]);
    if (DrwRec)
        {
        int direction=GetSignDirection(sign,FPlanKind,FPlanDirect);
        TExtRect *erect=SignsMan.Rects+ObjNum;
        int SignX,SignY;
        Road->ConvertPoint(erect->RoadL,erect->RoadX,SignX,SignY);
        POINT p;
        p.x=SignX;
        p.y=SignY;
        RECT signrect;
        CalcMetaRect(&p,DrwRec,&signrect,direction,false);
        RectsMan.PutRect(ObjNum,signrect);
        TMetafile *mtf=Shared->Metas->GetMetafile(DrwRec->MetaId,direction);
        PlayEnhMetaFile(dc,(void*)mtf->Handle,&signrect);
        RectsMan.PutRect(ObjNum,signrect);
        // Рисуем надпись на знаке
        if (sign->Label!="")
            {
            RECT R;
            CalcMetaRect(&p,DrwRec,&R,direction,true);
            DrawSignLabel(Cont,direction,&R,sign->Label);
            }
        }
    }
}

void __fastcall TDrawManager::DrawSignLabels(TDrawContents *Cont,int ObjNum)
{
HDC dc=Cont->GetContentDC();
TRoadSign *sign=dynamic_cast<TRoadSign*>(Objs[ObjNum]);
if ((dc)&&(sign))
    {
    int fsize=(double)FBaseScaleX/FSclX*FFontSize*FDpsm*(2.54/72); // Размер надписи при выводе
    int GostLabelSize=FFontSize*254*FBaseScaleX/(72*FBaseScaleP); // Размер надписи в 0.1 мм при печати
    RECT *signrect=GetRect(ObjNum);
    String Gibdd=Dict->GetShortTitle(sign->NumRoadSign);
    TExtRect *erect=SignsMan.Rects+ObjNum;    
    int gibdddir; // Ориентация надписи на знаке
    gibdddir=erect->RoadX>0? 0:2;
    if (FPlanDirect==pdUndirect)
        gibdddir=2-gibdddir;
    if (FPlanKind==pkGorizontal)
        gibdddir=3-gibdddir;
    RECT R;
    switch (gibdddir)
        {
        case 0:{R.left=signrect->left;R.right=signrect->right;
            R.top=signrect->bottom;R.bottom=R.top+fsize;} break;
        case 1:{R.top=signrect->top;R.bottom=signrect->bottom;
            R.left=signrect->right;R.right=R.left+fsize;} break;
        case 2:{R.left=signrect->left;R.right=signrect->right;
            R.bottom=signrect->top;R.top=R.bottom-fsize;} break;
        case 3:{R.top=signrect->top;R.bottom=signrect->bottom;
            R.right=signrect->left;R.left=R.right-fsize;} break;
        }
    DrawSignLabel(Cont,gibdddir,&R,Gibdd);
    RECT PosRect;
    int CX=(erect->Rect.left+erect->Rect.right)>>1;
    PosRect.left=CX-(GostLabelSize>>1);
    PosRect.right=CX+(GostLabelSize>>1);
    PosRect.top=erect->RoadX>0?erect->Rect.bottom:erect->Rect.top-3*GostLabelSize;
    PosRect.bottom=PosRect.top+3*GostLabelSize;
    if (SignsMan.TestRect(PosRect))
        {
        int CX=(signrect->left+signrect->right)>>1;
        int CY=(signrect->top+signrect->bottom)>>1;
        switch (gibdddir)
            {
            case 0: {R.left=signrect->right;R.right=R.left+fsize*2;
                R.top=CY-(fsize>>1);R.bottom=CY+(fsize>>1);} break;
            case 1: {R.left=CX-(fsize>>1);R.right=CX+(fsize>>1);
                R.bottom=signrect->top;R.top=R.bottom-fsize*2;} break;
            case 2: {R.right=signrect->left;R.left=R.right-fsize*2;
                R.top=CY-(fsize>>1);R.bottom=CY+(fsize>>1);} break;
            case 3: {R.left=CX-(fsize>>1);R.right=CX+(fsize>>1);
                R.top=signrect->bottom;R.bottom=R.top+fsize*2;} break;
            }
        String S=String((int)((sign->L%100000)/100));
        while (S.Length()<3)
            S="0"+S;
        DrawSignLabel(Cont,gibdddir,&R,S);
        }
    }
}

void __fastcall TDrawManager::DrawSign(TDrawContents *Cont,int count,int *ObjNum,int flag)
{
HDC dc=Cont->GetContentDC();
if (dc)
    {
    int ElRad=(FDpsm*ELRAD)/100+0.5;
    int dir[32]; // Массивы для хранения направлений поворотов
    int plc[32]; // 0 - без поворота 3 - 90 гр по часовой стрелке
                 // 2 - 180 гр. 1 - 90 гр против часовой стрелки

    RECT *prct=NULL; // Прямоугольник i-1 нарисованного знака
    for (int i=0;i<count;i++)
        {
        int num=ObjNum[i];
        int drclass=Objs[num]->DrwClassId;
        TDrwClassesRec *ClRec=Dict->DrwClasses->Items[drclass];
        TDrwParamRec3 *DrwRec=dynamic_cast<TDrwParamRec3*>(Dict->DrwParams->Items[ClRec->DrwParamId[0]]);
        if (DrwRec)
            {
            POINT *pt=Polys[num]->Points;
            RECT rct;
            TRoadSign *sign=dynamic_cast<TRoadSign*>(Objs[num]);
            bool dr=sign->Placement==spRight;
            if (sign->Direction==roUnDirect)
                dr=!dr;
            bool b=sign->Direction==roDirect;
            if (FPlanDirect==pdUndirect)
                b=!b,dr=!dr;
            dir[i]=GetSignDirection(sign,FPlanKind,FPlanDirect);
            plc[i]=0;
            if (FPlanKind==pkGorizontal)
                {
                plc[i]=1;
                if (b) plc[i]+=2;
                }
            else if (!b)
                plc[i]=2;
            CalcMetaRect(pt,DrwRec,&rct,dir[i],false);
            int dw=0;
            int dh=0;
            int rctw=(rct.right-rct.left)>>1;
            int rcth=(rct.bottom-rct.top)>>1;
            // Делаем смещение изображений знаков
            if (FPlanKind==pkGorizontal)
                {
                if (dr)  // Выстраиваем знаки сверху вниз
                    {
                    dh=rcth+3*ElRad; // Смещение по умолчанию
                    if (prct)
                        {
                        if (prct->bottom+ElRad>rct.top+dh)
                            dh=prct->bottom+ElRad-rct.top;
                        }
                    }
                else
                    {  // Выстраиваем знаки снизу вверх
                    dh=-rcth-3*ElRad;
                    if (prct)
                        {
                        if (prct->top-ElRad<rct.bottom+dh)
                            dh=prct->top-ElRad-rct.bottom;
                        }
                    }
                }
            else
                {
                if (dr) //Выстраиваем знаки слева направо
                    {
                    dw=rctw+3*ElRad;
                    if (prct)
                        {
                        if (prct->right+ElRad>rct.left+dw)
                            dw=prct->right+ElRad-rct.left;
                        }
                    }
                else   //Выстраиваем знаки справа налево
                    {
                    dw=-rctw-3*ElRad;
                    if (prct)
                        if (prct->left-ElRad<rct.right+dw)
                            dw=prct->left-ElRad-rct.right;
                    }
                }
            rct.left+=dw;
            rct.right+=dw;
            rct.top+=dh;
            rct.bottom+=dh;
            RectsMan.PutRect(num,rct);
            prct=&(RectsMan.Rects[num].Rect);
            }
        }
    int scale=(double)FBaseScaleX/FSclX*FDpsm/2;
    int fsize=(double)FBaseScaleX/FSclX*FFontSize*FDpsm*(2.54/72);
    SelectObject(dc,CreatePen(PS_SOLID,FDpsm/100+0.5,0));
    SelectObject(dc,GetStockObject(WHITE_BRUSH));
    for (int i=0;i<count;i++)
        {
        int num=ObjNum[i];
        RECT *prect=&(RectsMan.Rects[num].Rect);
        TRoadSign *sign=dynamic_cast<TRoadSign*>(Objs[num]);
        if ((sign->Test==stBad)&&(!(flag&2)))
            continue;
        if ((sign->Test!=stBad)&&(!(flag&1)))
            continue;
        POINT *p=Polys[ObjNum[i]]->Points;
        MoveToEx(dc,p[0].x,p[0].y,NULL);
        LineTo(dc,(prect->left+prect->right)>>1,(prect->top+prect->bottom)>>1);
        Ellipse(dc,p[0].x-ElRad,p[0].y-ElRad,p[0].x+ElRad,p[0].y+ElRad);
        MoveToEx(dc,p[0].x,p[0].y,NULL);
        switch (dir[i])
            {
            case 0:
                {LineTo(dc,p[0].x,p[0].y-scale);
                LineTo(dc,p[0].x+scale/3,p[0].y-(scale>>1));
                MoveToEx(dc,p[0].x,p[0].y-scale,NULL);
                LineTo(dc,p[0].x-scale/3,p[0].y-(scale>>1));
                } break;
            case 1:
                {LineTo(dc,p[0].x-scale,p[0].y);
                LineTo(dc,p[0].x-(scale>>1),p[0].y+scale/3);
                MoveToEx(dc,p[0].x-scale,p[0].y,NULL);
                LineTo(dc,p[0].x-(scale>>1),p[0].y-scale/3);
                }break;
            case 2:
                {LineTo(dc,p[0].x,p[0].y+scale);
                LineTo(dc,p[0].x+scale/3,p[0].y+(scale>>1));
                MoveToEx(dc,p[0].x,p[0].y+scale,NULL);
                LineTo(dc,p[0].x-scale/3,p[0].y+(scale>>1));
                }break;
            case 3:
                {LineTo(dc,p[0].x+scale,p[0].y);
                LineTo(dc,p[0].x+(scale>>1),p[0].y+scale/3);
                MoveToEx(dc,p[0].x+scale,p[0].y,NULL);
                LineTo(dc,p[0].x+(scale>>1),p[0].y-scale/3);
                }break;
            }
        }
    DeleteObject(SelectObject(dc,GetStockObject(BLACK_PEN)));
    for (int i=0;i<count;i++)
        {
//        TMetafile *mtf=Shared->Metas->Metas[par[i]->MetaId];
        int num=ObjNum[i];
        int drclass=Objs[num]->DrwClassId;
        TDrwClassesRec *ClRec=Dict->DrwClasses->Items[drclass];
        TDrwParamRec3 *DrwRec=dynamic_cast<TDrwParamRec3*>(Dict->DrwParams->Items[ClRec->DrwParamId[0]]);
        if (DrwRec)
            {
            TRoadSign *sign=dynamic_cast<TRoadSign*>(Objs[num]);
            if ((sign->Test==stBad)&&(!(flag&2)))
                continue;
            if ((sign->Test!=stBad)&&(!(flag&1)))
                continue;

            TMetafile *mtf=Shared->Metas->GetMetafile(DrwRec->MetaId,dir[i]);
            RECT *prect=&(RectsMan.Rects[num].Rect);
            TExtRect *erect=SignsMan.Rects+num;
            RECT qrect;
            POINT p;
            int PX,PY;
            Road->ConvertPoint(erect->RoadL,erect->RoadX,PX,PY);
            p.x=PX;
            p.y=PY;
            CalcMetaRect(&p,DrwRec,&qrect,dir[i],false);
//            PlayEnhMetaFile(dc,(void*)mtf->Handle,prect);
            PlayEnhMetaFile(dc,(void*)mtf->Handle,&qrect);
            SelectObject(dc,GetStockObject(NULL_BRUSH));
// Изначально предполагалось хранить проект дислокации вместе с данными по дороге
// И эти условия должны были использоваться для отделения реальных знаков от проектируемых
/*        if (Sources[i]->NotExist)
            {
            SelectObject(dc,CreatePen(PS_DOT,1,clRed));
            Rectangle(dc,Rects[num].left-3,Rects[num].top-3,Rects[num].right+3,Rects[num].bottom+3);
            DeleteObject(SelectObject(dc,GetStockObject(BLACK_PEN)));
            }
        else if (sign->Test==stBad)
            {
            SelectObject(dc,CreatePen(PS_DOT,1,clBlack));
            Rectangle(dc,Rects[num].left-3,Rects[num].top-3,Rects[num].right+3,Rects[num].bottom+3);
            DeleteObject(SelectObject(dc,GetStockObject(BLACK_PEN)));
            }
*/
            if (sign->Label!="")
                {
                TRect R;
                POINT p;
                p.x=(prect->left+prect->right)>>1;
                p.y=(prect->top+prect->bottom)>>1;
                CalcMetaRect(&p,DrwRec,&R,dir[i],true);
                DrawSignLabel(Cont,dir[i],&R,sign->Label);
                }
            String Gibdd=Dict->GetShortTitle(sign->NumRoadSign);
            RECT r;
            switch (plc[i])
                {
                case 0:{r.left=prect->left;r.right=prect->right;
                    r.top=prect->bottom;r.bottom=r.top+fsize;} break;
                case 1:{r.top=prect->top;r.bottom=prect->bottom;
                    r.left=prect->right;r.right=r.left+fsize;} break;
                case 2:{r.left=prect->left;r.right=prect->right;
                    r.bottom=prect->top;r.top=r.bottom-fsize;} break;
                case 3:{r.top=prect->top;r.bottom=prect->bottom;
                    r.right=prect->left;r.left=r.right-fsize;} break;
                }
            DrawSignLabel(Cont,plc[i],&r,Gibdd);
            }
        }
    int num=ObjNum[count-1];
    RECT *prect=&(RectsMan.Rects[num].Rect);
    TRoadSign *sign=dynamic_cast<TRoadSign*>(Objs[num]);
    TRect R;
    int CX=(prect->left+prect->right)>>1;
    int CY=(prect->top+prect->bottom)>>1;
    switch (plc[count-1])
        {
        case 0: {R.left=prect->right;R.right=R.left+fsize*2;
            R.top=CY-(fsize>>1);R.bottom=CY+(fsize>>1);} break;
        case 1: {R.left=CX-(fsize>>1);R.right=CX+(fsize>>1);
            R.bottom=prect->top;R.top=R.bottom-fsize*2;} break;
        case 2: {R.right=prect->left;R.left=R.right-fsize*2;
            R.top=CY-(fsize>>1);R.bottom=CY+(fsize>>1);} break;
        case 3: {R.left=CX-(fsize>>1);R.right=CX+(fsize>>1);
            R.top=prect->bottom;R.bottom=R.top+fsize*2;} break;
        }
    String S=String((int)((sign->L%100000)/100));
    while (S.Length()<3)
        S="0"+S;
    DrawSignLabel(Cont,plc[count-1],&R,S);
    }
}

void __fastcall TDrawManager::DrawBridge(TDrawContents *Cont,TExtPolyline *Poly,TDrwParamRec4 *par)
{
if (par)
    {
    HDC dc=Cont->GetContentDC();
    if (dc)
        {
        double scalex=(double)FBaseScaleX/FSclX*FDpsm/100;
        double scalel=(double)FBaseScaleL/FSclL*FDpsm/100;
        int LTaleY,LTaleX;
        int LTaleTube;
        if (FPlanKind==pkGorizontal)
            {
            LTaleY=(double)par->TaleLength*scalex/sqrt(2);
            LTaleX=(double)par->TaleLength*scalel/sqrt(2);
            LTaleTube=LTaleY;
            }
        else
            {
            LTaleX=(double)par->TaleLength*scalex/sqrt(2);
            LTaleY=(double)par->TaleLength*scalel/sqrt(2);
            LTaleTube=LTaleX;
            }
        int dir=1;
        if (FPlanDirect==pdUndirect)
            dir=-1;
        bool needdel;
        void *pen=GetPen(par,needdel);
        SelectObject(dc,pen);
        int n=Poly->Count;
        POINT *p=Poly->Points;
        if (n==2)  //Рисуем трубу
            {
            if (abs(p[1].x-p[0].x)<abs(p[1].y-p[0].y))
                {
                if (p[1].y>p[0].y)
                    dir=1;
                else
                    dir=-1;
                MoveToEx(dc,p[0].x-LTaleTube,p[0].y-dir*LTaleTube,NULL);
                LineTo(dc,p[0].x,p[0].y);
                LineTo(dc,p[0].x+LTaleTube,p[0].y-dir*LTaleTube);
                MoveToEx(dc,p[1].x-LTaleTube,p[1].y+dir*LTaleTube,NULL);
                LineTo(dc,p[1].x,p[1].y);
                LineTo(dc,p[1].x+LTaleTube,p[1].y+dir*LTaleTube);
                }
            else
                {
                if (p[1].x>p[0].x)
                    dir=1;
                else
                    dir=-1;
                MoveToEx(dc,p[0].x-dir*LTaleTube,p[0].y-LTaleTube,NULL);
                LineTo(dc,p[0].x,p[0].y);
                LineTo(dc,p[0].x-dir*LTaleTube,p[0].y+LTaleTube);
                MoveToEx(dc,p[1].x+dir*LTaleTube,p[1].y-LTaleTube,NULL);
                LineTo(dc,p[1].x,p[1].y);
                LineTo(dc,p[1].x+dir*LTaleTube,p[1].y+LTaleTube);
                }
            }
        else
            {
            int m=0;
            if (FPlanKind==pkGorizontal)
              MoveToEx(dc,p[m].x-dir*LTaleX,p[m].y+dir*LTaleY,NULL);
            else
              MoveToEx(dc,p[m].x+dir*LTaleX,p[m].y+dir*LTaleY,NULL);
            LineTo(dc,p[m].x,p[m].y);
            m=n/2-1;
            if (FPlanKind==pkGorizontal)
                MoveToEx(dc,p[m].x+dir*LTaleX,p[m].y+dir*LTaleY,NULL);
            else
                MoveToEx(dc,p[m].x+dir*LTaleX,p[m].y-dir*LTaleY,NULL);
            LineTo(dc,p[m].x,p[m].y);
            m=n/2;
            if (FPlanKind==pkGorizontal)
              MoveToEx(dc,p[m].x+dir*LTaleX,p[m].y-dir*LTaleY,NULL);
            else
              MoveToEx(dc,p[m].x-dir*LTaleX,p[m].y-dir*LTaleY,NULL);
            LineTo(dc,p[m].x,p[m].y);
            m=n-1;
            if (FPlanKind==pkGorizontal)
              MoveToEx(dc,p[m].x-dir*LTaleX,p[m].y-dir*LTaleY,NULL);
            else
              MoveToEx(dc,p[m].x-dir*LTaleX,p[m].y+dir*LTaleY,NULL);
            LineTo(dc,p[m].x,p[m].y);
            Polyline(dc,p,n/2);

            Polyline(dc,p+n/2,n/2);
            }
        if (needdel)
            {
            SelectObject(dc,GetStockObject(BLACK_PEN));
            DeleteObject(pen);
            }

        }
    }
}

int __fastcall round(double l)
{
if (l>0)
        return l+0.5;
else
        return l-0.5;
}

/*
POINT * __fastcall TDrawManager::BuildEqvi(POINT *Sour,int count,double shift,double Ex,int &n)
{
// Временный массив точек. Удаляем все точки лежащие на одной прямой и совпадающие точки
POINT *p=new POINT [count];
int i,j,k;// номера точек которые не совпадают
i=0;
j=1;
p[0].x=Sour[0].x;
p[0].y=Sour[0].y;
int c=1;
while ((Sour[j].x==Sour[i].x)&&(Sour[j].y==Sour[i].y)&&(j<count))
        j++;
if (j<count)
   {
   for (k=j+1;k<count;k++)
        {
        if ((Sour[k].x==Sour[j].x)&&(Sour[k].y==Sour[j].y))
                continue;
        int s=(Sour[k].x-Sour[j].x)*(Sour[i].y-Sour[j].y)-(Sour[i].x-Sour[j].x)*(Sour[k].y-Sour[j].y);
        if (s!=0)
                {
                p[c].x=Sour[j].x;
                p[c].y=Sour[j].y;
                c++;
                i=j;
                }
        j=k;
        }
   if ((p[c-1].x!=Sour[count-1].x)||(p[c-1].y!=Sour[count-1].y))
       {
       p[c].x=Sour[count-1].x;
       p[c].y=Sour[count-1].y;
       c++;
       }
   }

double minang;
// Считаем количество точек
int c1=c-1;
int sgn;
if (shift>0) sgn=1;
else  if (shift<0) sgn=-1;
else sgn=0;
n=c;
if (sgn)
    {
    minang=2*acos((fabs(shift)-Ex)/fabs(shift));
    for (i=1;i<c1;i++)
        {
        int dx1=p[i+1].x-p[i].x;
        int dy1=p[i+1].y-p[i].y;
        int dx2=p[i-1].x-p[i].x;
        int dy2=p[i-1].y-p[i].y;
        int s=dx1*dy2-dx2*dy1;
        if (s*sgn<0) // Поворот в сторону противоположную смещению
                {
                double len1=sqrt(dx1*dx1+dy1*dy1);
                double len2=sqrt(dx2*dx2+dy2*dy2);
                double vx1=dy2*shift/len2;
                double vy1=-dx2*shift/len2;
                double vx2=-dy1*shift/len1;
                double vy2=dx1*shift/len1;
                double cosa=(vx1*vx2+vy1*vy2)/(sqrt(vx1*vx1+vy1*vy1)*sqrt(vx2*vx2+vy2*vy2));
                double ang=acos(cosa);
                n+=ceil(ang/minang);
                }
        }
    }
POINT *res=new POINT[n+1];
if (sgn==0)
        {
        for (int i=0;i<n;i++)
                res[i].x=p[i].x,res[i].y=p[i].y;
        k=n;
        }
else
        {
        if (n==1) // Все точки совпадают
                {
                res[0].x=p[0].x;
                res[0].y=p[0].y;
                k=1;
                }
        else
                {
                k=1;
                int dx=p[1].x-p[0].x;
                int dy=p[1].y-p[0].y;
                double len=sqrt(dx*dx+dy*dy);
                res[0].x=round(p[0].x-dy*shift/len);
                res[0].y=round(p[0].y+dx*shift/len);
                for (i=1;i<c1;i++)
                        {
                        int dx1=p[i+1].x-p[i].x;
                        int dy1=p[i+1].y-p[i].y;
                        double len1=sqrt(dx1*dx1+dy1*dy1);
                        int dx2=p[i-1].x-p[i].x;
                        int dy2=p[i-1].y-p[i].y;
                        double len2=sqrt(dx2*dx2+dy2*dy2);
                        int s=dx1*dy2-dx2*dy1;
                        if (s!=0)
                                {
                                if (s*sgn>0)  // поворот в сторону смещения
                                        {
                                        double cos2a=(dx1*dx2+dy1*dy2)/(len1*len2);
                                        if (cos2a>1.0)
                                                cos2a=1.0;
                                        else if (cos2a<-1.0)
                                                cos2a=-1.0;
                                        double tana=sqrt((1.0+cos2a)/(1.0-cos2a));
                                        double l=fabs(shift*tana);
                                        res[k].x=round(p[i].x+dy2*shift/len2+dx2*l/len2);//
                                        res[k].y=round(p[i].y-dx2*shift/len2+dy2*l/len2);//
                                        k++;
                                        }
                                else          // поворот в другую строну
                                        {
                                        double vx1=dy2*shift/len2;
                                        double vy1=-dx2*shift/len2;
                                        double vx2=-dy1*shift/len1;
                                        double vy2=dx1*shift/len1;
                                        double cosa=(vx1*vx2+vy1*vy2)/(sqrt(vx1*vx1+vy1*vy1)*sqrt(vx2*vx2+vy2*vy2));

                                        double ang=acos(cosa);
                                        int t=ceil(ang/minang);
                                        ang/=t;
                                        double an;
                                        for (j=0,an=0;j<=t;j++,an+=ang)
                                                {
                                                double cs=cos(an);
                                                double sn=sin(an);
                                                res[k].x=round(p[i].x+vx1*cs+sgn*vy1*sn);
                                                res[k].y=round(p[i].y-sgn*vx1*sn+vy1*cs);
                                                k++;
                                                }
                                        }
                                }
//                        else
//                            n=k;
                        }
                dx=p[c1].x-p[c1-1].x;
                dy=p[c1].y-p[c1-1].y;
                len=sqrt(dx*dx+dy*dy);
                res[k].x=round(p[c1].x-dy*shift/len);
                res[k].y=round(p[c1].y+dx*shift/len);
                k++;
                }
        }
n=k;
delete[] p;
return res;
}

*/

void __fastcall TDrawManager::DrawFigure(TDrawContents *Cont,POINT pt,double dirx,double diry,int kind,int size,int orsize,__int32 penid,__int32 brushid)
{
HDC dc=Cont->GetContentDC();
if (dc)
        {
        SelectObject(dc,GetGdiObj(brushid));
        SelectObject(dc,GetGdiObj(penid));
        switch (kind)
                {
                case 0: Ellipse(dc,pt.x-size,pt.y-size,pt.x+size,pt.y+size); break;
                case 1: Rectangle(dc,pt.x-size,pt.y-size,pt.x+size,pt.y+size); break;
                case 2: {
                    POINT p[3];

                    double dxs=dirx*orsize;
                    double dys=diry*orsize;
                    p[1].x=pt.x+dxs;
                    p[1].y=pt.y+dys;
                    dxs=dirx*size/2;
                    dys=diry*size/2;
                    p[0].x=pt.x+dys;
                    p[0].y=pt.y-dxs;
                    p[2].x=pt.x-dys;
                    p[2].y=pt.y+dxs;
                    Polygon(dc,p,3);
                    } break;
                case 3:
                    {
                    POINT p[4];
                    int dxs=dirx*size/2;
                    int dys=diry*size/2;
                    p[0].x=pt.x+dys;
                    p[0].y=pt.y-dxs;
                    p[3].x=pt.x-dys;
                    p[3].y=pt.y+dxs;
                    dxs=dirx*orsize;
                    dys=diry*orsize;
                    p[1].x=p[0].x+dxs;
                    p[1].y=p[0].y+dys;
                    p[2].x=p[3].x+dxs;
                    p[2].y=p[3].y+dys;
                    Polygon(dc,p,4);
                    }
                }
        SelectObject(dc,GetStockObject(BLACK_PEN));
        SelectObject(dc,GetStockObject(NULL_BRUSH));
        }
}


void __fastcall TDrawManager::DrawBordersLine(TDrawContents *Cont,TExtPolyline *Poly,TDrwParamRec8 *par)
{
double scale;
HDC dc=Cont->GetContentDC();
if (dc)
    {
    POINT *p=Poly->Points;
    scale=(double)FBaseScaleX/FSclX*FDpsm/100;
    int size=(double)par->Length*scale+0.5;
    SelectObject(dc,GetGdiObj(par->PenId));
    if (par->Kind&1)
        {
        if (FPlanKind==pkGorizontal)
            {
            MoveToEx(dc,p[0].x,p[0].y-size/2,NULL);
            LineTo(dc,p[0].x,p[0].y+size/2);
            }
        else
            {
            MoveToEx(dc,p[0].x-size/2,p[0].y,NULL);
            LineTo(dc,p[0].x+size/2,p[0].y);
            }
        }
    if (par->Kind&2)
        {
        int n=Poly->Count-1;
        if (FPlanKind==pkGorizontal)
            {
            MoveToEx(dc,p[n].x,p[n].y-size/2,NULL);
            LineTo(dc,p[n].x,p[n].y+size/2);
            }
        else
            {
            MoveToEx(dc,p[n].x-size/2,p[n].y,NULL);
            LineTo(dc,p[n].x+size/2,p[n].y);
            }
        }
    SelectObject(dc,GetStockObject(BLACK_PEN));
    }
}

#define BEZIERSTEPCOUNT 100
void __fastcall TDrawManager::DrawFigureLine(TDrawContents *Cont,int count,TExtPolyline *Poly,TDrwParamRec6 *par)
{
int n=Poly->Count;
if (n>0)
    {
    POINT *p=Poly->Points;
    int *Codes=(int*)Poly->Codes;
    double scale;
    if (par->ScaleKind==skByX)
        scale=(double)FBaseScaleX/FSclX*FDpsm/100;
    else
        scale=(double)FBaseScaleL/FSclL*FDpsm/100;
    int size=(double)par->Size*scale+0.5;
    int orsize=(double)par->OrSize*scale+0.5;
    if ((size>1)||(orsize>1))
        {
        double shift=par->Shift*scale*Poly->DirectionVal;
        double offset=par->Offset*scale;
        double space=par->Space*scale;
        if (count>0)
            {
            double s=0; // Ищем длину полилинии
            for (int i=1;i<n;i++)
                {
                int inext=(i+1)%n;
                if ((Codes[inext]&7)==5) // к следующей точке идет кривая Безье
                    {
                    int inn=(inext+1)%n; // Ищем длину участка кривой безье численныым интегрированием
                    int steps=BEZIERSTEPCOUNT;
                    double st=1.0/steps;

                    double x0=p[i-1].x;
                    double x1=p[i].x;
                    double x2=p[inext].x;
                    double x3=p[inn].x;
                    double y0=p[i-1].y;
                    double y1=p[i].y;
                    double y2=p[inext].y;
                    double y3=p[inn].y;

                    double oldx=x0;
                    double oldy=y0;
                    double t=0.0;
                    for (int  j=0;j<steps;j++)
                        {
                        t+=st;
                        double t2=t*t;
                        double t3=t2*t;
                        double to=1-t;
                        double to2=to*to;
                        double to3=to2*to;
                        double t_to2_3=t*to2*3;
                        double t2_to_3=t2*to*3;

                        double newx=to3*x0+t_to2_3*x1+t2_to_3*x2+t3*x3;
                        double newy=to3*y0+t_to2_3*y1+t2_to_3*y2+t3*y3;
                        double dx=newx-oldx;
                        double dy=newy-oldy;
                        s+=sqrt(dx*dx+dy*dy);
                        oldx=newx;
                        oldy=newy;
                        }
                    i+=2;
                    }
                else if (Codes[i]>0)
                    {
                    int dx=p[i].x-p[i-1].x;
                    int dy=p[i].y-p[i-1].y;
                    s+=sqrt(dx*dx+dy*dy);
                    }
                }
            if (count==1)
                {
                offset=s/2;
                space=s;
                }
            else
                space=(s-2*offset-2)/(count-1);
            }
        if (space<2)
            space=2;
        double PrevPtx,PrevPty;
        PrevPtx=p[0].x;
        PrevPty=p[0].y;
        double SpaceLen=offset; // начинаем со смещения
        int i=1;
        if (n==1)
            DrawFigure(Cont,p[0],0,1,par->Kind,size,orsize,par->PenId,par->BrushId);
        else
        while (i<n)
                {
                int inext=(i+1)%n;
                if ((Codes[inext]&7)==5) // к следующей точке идет Безье
                    {
                    int inn=(inext+1)%n; //
                    int steps=BEZIERSTEPCOUNT;
                    double st=1.0/steps;

                    double x0=p[i-1].x;
                    double x1=p[i].x;
                    double x2=p[inext].x;
                    double x3=p[inn].x;
                    double y0=p[i-1].y;
                    double y1=p[i].y;
                    double y2=p[inext].y;
                    double y3=p[inn].y;
                    double oldx=x0;
                    double oldy=y0;
                    double t=0.0;
                    for (int j=0;j<steps;j++)
                        {
                        t+=st;
                        double t2=t*t;
                        double t3=t2*t;
                        double to=1-t;
                        double to2=to*to;
                        double to3=to2*to;
                        double t_to2_3=t*to2*3;
                        double t2_to_3=t2*to*3;

                        double newx=to3*x0+t_to2_3*x1+t2_to_3*x2+t3*x3;
                        double newy=to3*y0+t_to2_3*y1+t2_to_3*y2+t3*y3;
                        double dx=newx-oldx;
                        double dy=newy-oldy;
                        double len=sqrt(dx*dx+dy*dy);
                        if (len<SpaceLen)
                            SpaceLen-=len;
                        else
                            {
                            POINT DrwPt;
                            dx/=len;
                            dy/=len;

                            PrevPtx=oldx+dx*SpaceLen;
                            PrevPty=oldy+dy*SpaceLen;
                            DrwPt.x=PrevPtx-dy*shift/len+0.5;
                            DrwPt.y=PrevPty+dx*shift/len+0.5;
                            DrawFigure(Cont,DrwPt,-dy,dx,par->Kind,size,orsize,par->PenId,par->BrushId);
                            SpaceLen=SpaceLen+space-len;
                            }
                        oldx=newx;
                        oldy=newy;
                        }
                    i+=2;
                    if (i<n)
                        {
                        PrevPtx=p[i].x;
                        PrevPty=p[i].y;
                        }
                    i++;
                    }
                else if (Codes[i]>0)  // линия по которой мы движемся является прямой
                    {
                    double dx=p[i].x-PrevPtx;
                    double dy=p[i].y-PrevPty;
                    double len=sqrt(dx*dx+dy*dy);
                    if (len<SpaceLen)  // точку надо ставить вне этого отрезка
                        {
                        PrevPtx=p[i].x;
                        PrevPty=p[i].y;
                        SpaceLen-=len;
                        i++;
                        }
                    else   // Точку надо ставить на отрезке
                        {
                        POINT DrwPt;
                        if (len>0.000001)
                            {
                            dx/=len;
                            dy/=len;
                            PrevPtx+=dx*SpaceLen;
                            PrevPty+=dy*SpaceLen;
                            DrwPt.x=PrevPtx-dy*shift+0.5;
                            DrwPt.y=PrevPty+dx*shift+0.5;
                            }
                        else
                            {
                            dx=1;
                            dy=0;
                            DrwPt.x=PrevPtx;
                            DrwPt.y=PrevPty;
                            }
                        DrawFigure(Cont,DrwPt,-dy,dx,par->Kind,size,orsize,par->PenId,par->BrushId);
                        SpaceLen=space;
                        }
                    }
                else
                    i++;
                }
        }
    }
}

/*
void __fastcall TDrawManager::DrawOneDash(TDrawContents *Cont,__int32 n,POINT *p,int shift,int width,__int32 penid,__int32 brushid)
{
if (n>1)
   {
   int lcount,rcount;
   POINT *l=BuildEqvi(p,n,shift+width,1,lcount);
   POINT *r=BuildEqvi(p,n,shift-width,1,rcount);
   int sumcount=lcount+rcount;
   POINT *res=new POINT[sumcount];
   for (int i1=0;i1<lcount;i1++)
        {
        res[i1].x=l[i1].x;
        res[i1].y=l[i1].y;
        }
   for (int i1=0;i1<rcount;i1++)
        {
        res[i1+lcount].x=r[rcount-1-i1].x;
        res[i1+lcount].y=r[rcount-1-i1].y;
        }
   DrawPolygon(Cont,sumcount,res,penid,brushid);
   delete[] l;
   delete[] r;
   delete[] res;
   }
}

void __fastcall TDrawManager::DrawDash(TDrawContents *Cont,__int32 n,POINT *p,TDrwParamRec5 *par)
{
double scale=(double)FBaseScaleX/FSclX*FDpsm/100;   // Пикселей в 0.1 мм
double DashLen=par->Dash*scale;
if (DashLen<2)
    DashLen=2;
double SpaceLen=par->Space*scale;
if (SpaceLen<2)
    SpaceLen=2;
double Width=par->Width*scale/2;
if (Width<1)
    Width=1;
double Shift=par->Shift*scale;
POINT * Dash;
Dash=new POINT [n];
double DashPartLen;  // Оставшаяся длина штриха от пройденной точки.
double PrevPtx,PrevPty;        // Точка, добавленная в штрих последней
int i=1;
PrevPtx=Dash[0].x=p[0].x;    // Штрих начинается с нулевой точки
PrevPty=Dash[0].y=p[0].y;
int k=1;
DashPartLen=par->Offset*scale;  // Начинаем со смещения
bool onoff=false;
while (i<n)
        {
        double dx=p[i].x-PrevPtx;
        double dy=p[i].y-PrevPty;
        double len=sqrt(dx*dx+dy*dy);
        if (len<DashPartLen)   //Точка лежит внутри штриха
                {
                PrevPtx=Dash[k].x=p[i].x;
                PrevPty=Dash[k].y=p[i].y;
                k++;
                DashPartLen-=len;
                i++;
                }
        else                   // Штрих завершается на отрезке
                {
                if (len>0.000001)
                        {
                        PrevPtx+=dx*DashPartLen/len;
                        PrevPty+=dy*DashPartLen/len;
                        }
                Dash[k].x=PrevPtx;
                Dash[k].y=PrevPty;
                k++;
                if (onoff)
                        {
                        DrawOneDash(Cont,k,Dash,Shift,Width,par->PenId,par->BrushId);
                        // Нарисовать штрих
                        DashPartLen=SpaceLen;
                        }
                else if (SpaceLen>0)
                        DashPartLen=DashLen;
                else
                        DashPartLen=10000000; // Не пунктир, а сплошная линия
                onoff=!onoff;
                Dash[0].x=PrevPtx;
                Dash[0].y=PrevPty;
                k=1;
                }
        }
if (onoff)
        DrawOneDash(Cont,k,Dash,Shift,Width,par->PenId,par->BrushId);
delete[] Dash;
}

void __fastcall TDrawManager::DrawCurvesLine(TDrawContents *Cont,__int32 n,POINT *p,TDrwParamRec7 *par)
{
if (par)
    {
    HDC dc=Cont->GetContentDC();
    if (dc)
        {
        if (par->PenId>0)
            SelectObject(dc,Shared->GDIObjects->Items[par->PenId]);
        else
            SelectObject(dc,GetStockObject(-par->PenId));
        double scale=(double)FBaseScaleX/FSclX*FDpsm/100;   // Пикселей в 0.1 мм
        double Shift=par->Shift*scale;
        n--; // Для каждого сегмента используется две точки
        for (int i=0;i<n;i+=2)
            {
            POINT pt[7];
            int dx=p[i+1].x-p[i].x;
            int dy=p[i+1].y-p[i].y;
            if (dx||dy)
                {
                double len=sqrt(dx*dx+dy*dy);
                int sy=(double)dy*Shift/len;
                int sx=(double)dx*Shift/len;
                pt[0].x=p[i].x;
                pt[0].y=p[i].y;
                pt[1].x=p[i].x+dx/6-sy;
                pt[1].y=p[i].y+dy/6+sx;
                pt[2].x=p[i].x+dx/3+sy;
                pt[2].y=p[i].y+dy/3-sx;
                pt[3].x=(p[i].x+p[i+1].x)>>1;
                pt[3].y=(p[i].y+p[i+1].y)>>1;
                pt[4].x=p[i].x+dx*2/3-sy;
                pt[4].y=p[i].y+dy*2/3+sx;
                pt[5].x=p[i].x+dx*5/6+sy;
                pt[5].y=p[i].y+dy*5/6-sx;
                pt[6].x=p[i+1].x;
                pt[6].y=p[i+1].y;
                PolyBezier(dc,pt,7);
                }
            }
        SelectObject(dc,GetStockObject(BLACK_PEN));
        }
    }
}
*/

void __fastcall TDrawManager::DrawRazrez(TDrawContents *Cont,TRect *OutRect,TPlanKind pk,TPlanDirect pd,__int32 L)
{
FPlanKind=pk;
FPlanDirect=pd;
TGeometryVal GVal;
Road->Geometry.GetMesValue(L,GVal);
int LeftWid=-Road->LeftLine.FindX(L);
int RightWid=Road->RightLine.FindX(L);

int RoadSR=(RightWid*GVal.RightSlope)/1000;
int RoadSL=(LeftWid*GVal.LeftSlope)/1000;

TObjList<TRoadObject> *Src=FVisSet->MetricSource->Objects;
int Count=Src->Count;
TRoadDress *Dress[32];
TRect Rects[32];
int rdcount=0;
for (int i=0;(i<Count)&&(rdcount<32);i++)
    {
    TRoadObject *Obj=Src->Items[i];
    if (Obj)
        if (Obj->DictId==ROADDRESSCODE)
            {
            TRoadDress *rd=dynamic_cast<TRoadDress*>(Obj);
            if (rd)
                if ((rd->L<=L) && (rd->LMax>=L))
                    {
                    int i;
                    for (i=rdcount-1;i>=0;i--)
                        if ((Dress[i]->LayerKind < rd->LayerKind)||((Dress[i]->LayerKind==rd->LayerKind)&&(Dress[i]->LayerNum>rd->LayerNum)))
                            Dress[i+1]=Dress[i];
                        else
                            break;
                    Dress[i+1]=rd;
                    rdcount++;
                    }
            }
    }
TObjList<TDrwParamRec> *DrPar=Dict->DrwParams;
TObjList<TDrwClassesRec> *DrCl=Dict->DrwClasses;
TExtPolyline Poly(6,1);
int comheight;
if (RoadSL*RoadSR<0)
    comheight=abs(RoadSL)+abs(RoadSR);
else
    comheight=max(abs(RoadSL),abs(RoadSR));
for (int i=0;i<rdcount;i++)
    comheight+=Dress[i]->Height;
int curheight=max(RoadSL,RoadSR);  // Высота слоя по оси
if (curheight<0)
    curheight=0;
int leftheight=curheight-RoadSL;  // Высота слоя по левой бровке
int rightheight=curheight-RoadSR; // Высота слоя по правой бровке
int dh=OutRect->bottom-OutRect->top-2;
int dl=OutRect->right-OutRect->left-2;
TRect RefRect;

int cx=LeftWid*(OutRect->right-OutRect->left)/(LeftWid+RightWid);
int cy=LeftWid*(OutRect->bottom-OutRect->top)/(LeftWid+RightWid);
for (int i=0;i<rdcount;i++)
    {
    if (FPlanKind==pkGorizontal)
        {
        Poly[0].y=OutRect->bottom-(leftheight*dh)/comheight-1;
        Poly[0].x=OutRect->left;
        Poly[1].y=OutRect->bottom-(curheight*dh)/comheight-1;
        Poly[1].x=cx;
        Poly[2].y=OutRect->bottom-(rightheight*dh)/comheight-1;
        Poly[2].x=OutRect->right;
        curheight+=Dress[i]->Height;
        leftheight+=Dress[i]->Height;
        rightheight+=Dress[i]->Height;
        Poly[3].y=OutRect->bottom-(rightheight*dh)/comheight-1;
        Poly[3].x=OutRect->right;
        Poly[4].y=OutRect->bottom-(curheight*dh)/comheight-1;
        Poly[4].x=cx;
        Poly[5].y=OutRect->bottom-(leftheight*dh)/comheight-1;
        Poly[5].x=OutRect->left;
        Rects[i].left=OutRect->left;
        Rects[i].right=OutRect->right;
        Rects[i].top=Poly[4].y;
        Rects[i].bottom=Poly[1].y;
        }
    else
        {
        Poly[0].x=OutRect->right-(leftheight*dl)/comheight-1;
        Poly[0].y=OutRect->bottom;
        Poly[1].x=OutRect->right-(curheight*dl)/comheight-1;
        Poly[1].y=cy;
        Poly[2].x=OutRect->right-(leftheight*dl)/comheight-1;
        Poly[2].y=OutRect->top;
        curheight+=Dress[i]->Height;
        leftheight+=Dress[i]->Height;
        rightheight+=Dress[i]->Height;
        Poly[3].x=OutRect->right-(leftheight*dl)/comheight-1;
        Poly[3].y=OutRect->top;
        Poly[4].x=OutRect->right-(curheight*dl)/comheight-1;
        Poly[4].y=cy;
        Poly[5].x=OutRect->right-(leftheight*dl)/comheight-1;
        Poly[5].y=OutRect->bottom;
        Rects[i].left=Poly[4].x;
        Rects[i].right=Poly[1].x;
        Rects[i].top=OutRect->top;
        Rects[i].bottom=OutRect->bottom;
        }
    int drclass=Dress[i]->DrwClassId;
    TDrwClassesRec *ClRec=DrCl->Items[drclass];
    for (int k=0;k<MAXDRWPARAM;k++)
        {
        TDrwParamRec *Rec;
        try
            {Rec=DrPar->Items[ClRec->DrwParamId[k]];}
        catch (...) {}
        if (!Rec)
            continue;
        CallDrawFunc(Cont,&Poly,Rec,&RefRect,false);
        }
    }
for (int i=0;i<rdcount;i++)
    {
    String DrwStr=Dict->GetTitle(Dress[i]->Material)+"("+String(Dress[i]->Height)+")";
    if (DrwStr!="")
        DrawText(Cont->DC,DrwStr.c_str(),DrwStr.Length(),&Rects[i],37|DT_NOCLIP);
    }
if (FPlanKind==pkGorizontal)
    {
    String S=String(GVal.LeftSlope);
    DrawText(Cont->DC,S.c_str(),S.Length(),OutRect,DT_NOCLIP);
    S=String(GVal.RightSlope);
    DrawText(Cont->DC,S.c_str(),S.Length(),OutRect,2|DT_NOCLIP);
    }
else
    {
    String S=String(GVal.LeftSlope);
    DrawText(Cont->DC,S.c_str(),S.Length(),OutRect,DT_NOCLIP);
    S=String(GVal.RightSlope);
    DrawText(Cont->DC,S.c_str(),S.Length(),OutRect,40|DT_NOCLIP);
    }
}


void __fastcall TDrawManager::DrawProfilLine(TDrawContents *Cont,TRect *ProfRect,__int32 L1,__int32 L2,int dir)
{
int X1,X2,Y;
Road->ConvertPoint(L1,0,X1,Y);
Road->ConvertPoint(L2,0,X2,Y);
POINT P[3];
if (dir>0)
    {
    P[0].x=X1;
    P[1].x=P[2].x=X2;
    P[0].y=P[2].y=ProfRect->bottom;
    P[1].y=ProfRect->top;
    }
else
    {
    P[0].x=P[2].x=X1;
    P[1].x=X2;
    P[0].y=ProfRect->top;
    P[1].y=P[2].y=ProfRect->bottom;
    }
void *dc=Cont->DC;
SelectObject(dc,GetStockObject(BLACK_BRUSH));
SelectObject(dc,GetStockObject(BLACK_PEN));
Polygon(dc,P,3);
}

void __fastcall TDrawManager::DrawCurvesPlan(TDrawContents *Cont,TRect *OutRect,TPlanKind pk,TPlanDirect pd)
{
void *dc=Cont->DC;
int dpi=GetDeviceCaps(dc,LOGPIXELSY);
FPlanKind=pk;
FPlanDirect=pd;
int LineWid=dpi/254;
TObjList<TRoadObject> *Src=FVisSet->CurveSource->Objects;
int Count=Src->Count;
int CenY=(OutRect->Top+OutRect->Bottom)>>1;
int CenX=(OutRect->Right+OutRect->Left)>>1;
int RH;
if (FPlanKind==pkGorizontal)
    RH=OutRect->Bottom-OutRect->Top;
else
    RH=OutRect->Right-OutRect->Left;
TExtPolyline *Poly1=new TExtPolyline(4,0);
Poly1->Codes[2]=5;
TExtPolyline *Poly2=new TExtPolyline(2,0);
Poly2->Codes[1]=1;
POINT *P1=Poly1->Points;
POINT *P2=Poly2->Points;
TRect R;
TObjList<TDrwParamRec> *DrPar=Dict->DrwParams;
TObjList<TDrwClassesRec> *DrCl=Dict->DrwClasses;

void *pen=CreatePen(psSolid,LineWid,clBlack);
void *oldpen=SelectObject(dc,pen);
void *labfont=CreateLabelFont(dpi);
void *oldfont=SelectObject(dc,labfont);
bool prevln=true; // Истина если до этого была линия
for (int i=0;i<Count;i++)
    {
    TDangerCurve *Crv=dynamic_cast<TDangerCurve*>(Src->Items[i]);
    if (Crv)
        if ((Crv->LMin<Cont->L2)&&(Crv->LMax>Cont->L1))
        {
        int X1,X2,Y1,Y2;
        int L1=max(Crv->LMin,Cont->L1);
        int L2=min(Crv->LMax,Cont->L2);
        Road->ConvertPoint(L1,0,X1,Y1);
        Road->ConvertPoint(L2,0,X2,Y2);
        switch (Crv->Kind)
            {
            case ckLine:
                {
                if (FPlanKind==pkGorizontal)
                    {
                    P2[0].x=X1;
                    P2[1].x=X2;
                    P2[0].y=P2[1].y=CenY;
                    }
                else
                    {
                    P2[0].y=Y1;
                    P2[1].y=Y2;
                    P2[0].x=P2[1].x=CenX;
                    }
                } break;
            case ckCircle:
                {
                if (FPlanKind==pkGorizontal)
                    {
                    P1[0].x=P1[1].x=X1;
                    P1[2].x=P1[3].x=X2;
                    P1[0].y=P1[3].y=CenY;
                    if (Crv->Radius>0)
                        P1[1].y=P1[2].y=OutRect->Bottom;
                    else
                        P1[1].y=P1[2].y=OutRect->Top;
                    }
                else
                    {
                    P1[0].y=P1[1].y=Y1;
                    P1[2].y=P1[3].y=Y2;
                    P1[0].x=P1[3].x=CenX;
                    if (Crv->Radius>0)
                        P1[1].x=P1[2].x=OutRect->Right;
                    else
                        P1[1].x=P1[2].x=OutRect->Left;
                    }
                } break;
            case ckLeftCurve:
                {
                if (FPlanKind==pkGorizontal)
                    {
                    P1[0].x=X1;
                    P1[3].x=X2;
                    if (prevln)
                        {
                        P1[1].x=(X1+X2)>>1;
                        P1[2].x=X2;
                        P1[0].y=P1[1].y=CenY;
                        P1[2].y=OutRect->Top+(RH>>1);
                        P1[3].y=OutRect->top+LineWid;
                        }
                    else
                        {
                        P1[1].x=X1;
                        P1[2].x=(X1+X2)>>1;
                        P1[0].y=OutRect->top+LineWid;
                        P1[1].y=OutRect->Top+(RH>>1);
                        P1[2].y=P1[3].y=CenY;
                        }
                    }
                else
                    {
                    P1[0].y=Y1;
                    P1[3].y=Y2;
                    if (prevln)
                        {
                        P1[1].y=(Y1+Y2)>>1;
                        P1[2].y=Y2;
                        P1[0].x=P1[1].x=CenX;
                        P1[2].x=OutRect->Left+(RH>>1);
                        P1[3].x=OutRect->Left+LineWid;
                        }
                    else
                        {
                        P1[1].y=Y1;
                        P1[2].y=(Y1+Y2)>>1;
                        P1[0].x=OutRect->Left+LineWid;
                        P1[1].x=OutRect->Left+(RH>>1);
                        P1[2].x=P1[3].x=CenX;
                        }
                    }
                }break;
            case ckRightCurve:
                {
                if (FPlanKind==pkGorizontal)
                    {
                    P1[0].x=X1;
                    P1[3].x=X2;
                    if (prevln)
                        {
                        P1[1].x=(X1+X2)>>1;
                        P1[2].x=X2;
                        P1[0].y=P1[1].y=CenY;
                        P1[2].y=OutRect->Bottom-(RH>>1);
                        P1[3].y=OutRect->Bottom-LineWid;
                        }
                    else
                        {
                        P1[1].x=X1;
                        P1[2].x=(X1+X2)>>1;
                        P1[0].y=OutRect->Bottom-LineWid;
                        P1[1].y=OutRect->Bottom-(RH>>1);
                        P1[2].y=CenY;
                        P1[3].y=CenY;
                        }
                    }
                else
                    {
                    P1[0].y=Y1;
                    P1[3].y=Y2;
                    if (prevln)
                        {
                        P1[1].y=(Y1+Y2)>>1;
                        P1[2].y=Y2;
                        P1[0].x=P1[1].x=CenX;
                        P1[2].x=OutRect->Right-(RH>>1);
                        P1[3].x=OutRect->Right-LineWid;
                        }
                    else
                        {
                        P1[1].y=Y1;
                        P1[2].y=(Y1+Y2)>>1;
                        P1[0].x=OutRect->Right-LineWid;
                        P1[1].x=OutRect->Right-(RH>>1);
                        P1[2].x=P1[3].x=CenX;
                        }
                    }
                }break;
            }
        int drclass=Crv->DrwClassId;
        TDrwClassesRec *ClRec=DrCl->Items[drclass];
        if (ClRec)
            for (int k=0;k<MAXDRWPARAM;k++)
                {
                TDrwParamRec *Rec=NULL;
                try
                    {Rec=DrPar->Items[ClRec->DrwParamId[k]];}
                catch (...) {}
                if (!Rec)
                    continue;
                if (Crv->Kind==ckLine)
                    CallDrawFunc(Cont,Poly2,Rec,&R,false);
                else
                    CallDrawFunc(Cont,Poly1,Rec,&R,false);
                }
        if (Crv->Kind==ckCircle)
            {
            String Str=abs(Crv->Radius);
            if (FPlanKind==pkGorizontal)
                DrawText(dc,Str.c_str(),Str.Length(),&TRect(X1,OutRect->top,X2,OutRect->bottom),37|DT_NOCLIP);
            else
                DrawText(dc,Str.c_str(),Str.Length(),&TRect(OutRect->Left,Y1,OutRect->Right,Y2),37|DT_NOCLIP);
            }
        if ((Crv->Kind==ckLeftCurve)||(Crv->Kind==ckRightCurve))
            {
            SelectObject(dc,pen);
            if (FPlanKind==pkGorizontal)
                {
                int x;
                if (prevln)
                    x=X1;
                else
                    x=X2;
                MoveToEx(dc,x,OutRect->Top+(RH>>2),NULL);
                LineTo(dc,x,OutRect->Bottom-(RH>>2));
                }
            else
                {
                int y;
                if (prevln)
                    y=Y1;
                else
                    y=Y2;
                MoveToEx(dc,OutRect->Left+(RH>>2),y,NULL);
                LineTo(dc,OutRect->Right-(RH>>2),y);
                }
            }
        prevln=Crv->Kind==ckLine;
        }
    }
SelectObject(dc,oldpen);
DeleteObject(pen);
SelectObject(dc,oldfont);
DeleteObject(labfont);
}

void* __fastcall TDrawManager::CreateLabelFont(int dpi)
{
LOGFONT Fon;
GetObject(GetStockObject(SYSTEM_FONT),sizeof(Fon),&Fon);
strcpy(Fon.lfFaceName,"Arial");
Fon.lfHeight=(dpi*10)/72;
Fon.lfWidth=0;
return CreateFontIndirect(&Fon);
}


void __fastcall TDrawManager::GetVisModeParam(TRect *OutRect,TPlanKind pk,TPlanDirect pd,int X,int Y,int &dir,int &len) {
int dh,dz,dl;
   if (FPlanKind==pkGorizontal)
      dh=OutRect->bottom-OutRect->top,dl=OutRect->bottom-Y;
   else
      dh=OutRect->right-OutRect->left,dl=OutRect->right-X;;
   dz=(dh-2*FVisModeBorder)/2;
   if (dl>=dz+FVisModeBorder)
      dl-=dz+FVisModeBorder,dir=roUnDirect;
   else
      dir=roDirect;
   if (dl>=dz)
      len=0;
   else {
      len=(dl*FVisModeVisLength)/dz;
      len=((len+FVisModeMinStep-1)/FVisModeMinStep)*FVisModeMinStep;
      if (len>=FVisModeVisLength)
         len=0;
   }
}


void __fastcall TDrawManager::DrawVisibleMode(TDrawContents *Cont,TRect *OutRect,TPlanKind pk,TPlanDirect pd) {
   int border=FVisModeBorder;
   int maxlen=FVisModeVisLength;
   int step=20;
   int tstep=100;
   int dh,dz,ch;
   if (FPlanKind==pkGorizontal)
      dh=OutRect->bottom-OutRect->top;
   else
      dh=OutRect->right-OutRect->left;
   dz=(dh-2*border)/2;
   if (FVisSet->MetricSource) {
      TObjList<TRoadObject> *Src=FVisSet->MetricSource->Objects;
      int Count=Src->Count;
      TExtPolyline *Poly=new TExtPolyline(4,1);
      POINT *P=Poly->Points;
      TRect R;
      TObjList<TDrwParamRec> *DrPar=Dict->DrwParams;
      TObjList<TDrwClassesRec> *DrCl=Dict->DrwClasses;
      for (int i=0;i<Count;i++) {
         TDangerVisMode *Dvm=dynamic_cast<TDangerVisMode*>(Src->Items[i]);
         if (Dvm && Dvm->LMax>Cont->L1 && Dvm->LMin<Cont->L2) {
            int X1,X2,Y1,Y2,H,B;
            int L1=max(Dvm->LMin,Cont->L1);
            int L2=min(Dvm->LMax,Cont->L2);
            Road->ConvertPoint(L1,0,X1,Y1);
            Road->ConvertPoint(L2,0,X2,Y2);
            H=(Dvm->Length*dz)/maxlen;
            B=Dvm->Direction==roUnDirect? dz+border :0;

            if (FPlanKind==pkGorizontal) {
               P[0].x=X1;
               P[0].y=OutRect->bottom-B;
               P[1].x=X1;
               P[1].y=OutRect->bottom-B-H;
               P[2].x=X2;
               P[2].y=OutRect->bottom-B-H;
               P[3].x=X2;
               P[3].y=OutRect->bottom-B;
            } else  {
               P[0].x=OutRect->right-B;
               P[0].y=Y1;
               P[1].x=OutRect->right-B-H;
               P[1].y=Y1;
               P[2].x=OutRect->right-B-H;
               P[2].y=Y2;
               P[3].x=OutRect->right-B;
               P[3].y=Y2;
            }
            int drclass=Dvm->DrwClassId;
            TDrwClassesRec *ClRec=DrCl->Items[drclass];
            if (ClRec!=0) {
               for (int k=0;k<MAXDRWPARAM;k++) {
                  TDrwParamRec *Rec=NULL;
                  try{Rec=DrPar->Items[ClRec->DrwParamId[k]];}
                  catch (...) {}
                  if (!Rec)  continue;
                  CallDrawFunc(Cont,Poly,Rec,&R,false);
               }
            }
         }
      }
      delete Poly;
   }
   void *dc=Cont->DC;
   void *thinpen=CreatePen(PS_SOLID,0,0);
   void *thickpen=CreatePen(PS_SOLID,3,0);
   SelectObject(dc,GetStockObject(BLACK_PEN));
   SelectObject(dc,GetStockObject(BLACK_BRUSH));
   if (FPlanKind==pkGorizontal) {
      Rectangle(dc,OutRect->left,OutRect->top+dz+border,OutRect->right,OutRect->top+dz+2*border);
      Rectangle(dc,OutRect->left,OutRect->top,OutRect->right,OutRect->top+border);
      for (int i=0;i<2;i++) {
         for (int j=0;j<maxlen;j+=step) {
            if (j%tstep)
               SelectObject(dc,thinpen);
            else
               SelectObject(dc,thickpen);
            ch=i*(dz+border)+(j*dz)/maxlen;
            MoveToEx(dc,OutRect->left,OutRect->bottom-ch,0);
            LineTo(dc,OutRect->right,OutRect->bottom-ch);
         }
      }
   } else {
      Rectangle(dc,OutRect->left+dz+border,OutRect->top,OutRect->left+dz+2*border,OutRect->bottom);
      Rectangle(dc,OutRect->left,OutRect->top,OutRect->left+border,OutRect->bottom);
      for (int i=0;i<2;i++) {
         for (int j=0;j<maxlen;j+=step) {
            if (j%tstep)
               SelectObject(dc,thinpen);
            else
               SelectObject(dc,thickpen);
            ch=i*(dz+border)+(j*dz)/maxlen;
            MoveToEx(dc,OutRect->right-ch,OutRect->top,0);
            LineTo(dc,OutRect->right-ch,OutRect->bottom);
         }
      }
   }
   SelectObject(dc,GetStockObject(BLACK_PEN));
   DeleteObject(thinpen);
   DeleteObject(thickpen);
}

void __fastcall TDrawManager::DrawProfil(TDrawContents *Cont,TRect *OutRect,TPlanKind pk,TPlanDirect pd)
{
if (FVisSet)
    if (FVisSet->ProfilSource)
        {
        FPlanKind=pk;
        FPlanDirect=pd;
        TRect ProfilRect;
        int dh;
        if (FPlanKind==pkGorizontal)
            {
            ProfilRect.left=OutRect->left;
            ProfilRect.right=OutRect->right;
            ProfilRect.top=OutRect->top+2;
            ProfilRect.bottom=OutRect->bottom-2;
            dh=ProfilRect.Bottom-ProfilRect.top;
            }
        else
            {
            ProfilRect.left=OutRect->left+2;
            ProfilRect.right=OutRect->right-2;
            ProfilRect.top=OutRect->top;
            ProfilRect.bottom=OutRect->bottom;
            dh=ProfilRect.right-ProfilRect.left;
            }
        void *dc=Cont->DC;
        void *labfont=CreateLabelFont(GetDeviceCaps(dc,LOGPIXELSY));
        void *oldfont=SelectObject(dc,labfont);
        if (FVisSet->ProfilSource->ProfilKind>>1)
            {
            int DZ=Road->ZMax-Road->ZMin;
            if (DZ)
                {
                TObjList<TRoadObject> *Src=FVisSet->ProfilSource->Objects;
                int Count=Src->Count;
  //    TSlopesPart* Parts=Road->Geometry.BuildSlopesPart(Source->ProfilMinLen*100,Source->ProfilMaxDev,n);
                TExtPolyline *Poly=new TExtPolyline(4,1);
                POINT *P=Poly->Points;
                TRect R;
                TObjList<TDrwParamRec> *DrPar=Dict->DrwParams;
                TObjList<TDrwClassesRec> *DrCl=Dict->DrwClasses;
                for (int i=0;i<Count;i++)
                    {
                    TDangerSlope *Slp=dynamic_cast<TDangerSlope*>(Src->Items[i]);
                    if (Slp)
                        if ((Slp->LMax>Cont->L1)&&(Slp->LMin<Cont->L2))
                        {
                        int X1,X2,Y1,Y2,H1,H2;
                        int L1=max(Slp->LMin,Cont->L1);
                        int L2=min(Slp->LMax,Cont->L2);
                        Road->ConvertPoint(L1,0,X1,Y1);
                        Road->ConvertPoint(L2,0,X2,Y2);
                        TGeometryVal Geom;
                        Road->Geometry.GetMesValue(L1,Geom);
                        H1=((Geom.Z-Road->ZMin)*dh)/DZ;
                        Road->Geometry.GetMesValue(L2,Geom);
                        H2=((Geom.Z-Road->ZMin)*dh)/DZ;
                        if (FPlanKind==pkGorizontal)
                            {
                            H1=ProfilRect.bottom-H1;
                            H2=ProfilRect.bottom-H2;
                            P[0].x=X1;
                            P[0].y=ProfilRect.bottom;
                            P[1].x=X1;
                            P[1].y=H1;
                            P[2].x=X2;
                            P[2].y=H2;
                            P[3].x=X2;
                            P[3].y=ProfilRect.bottom;
                            }
                        else
                            {
                            H1=ProfilRect.right-H1;
                            H2=ProfilRect.right-H2;
                            P[0].x=ProfilRect.right;
                            P[0].y=Y1;
                            P[1].x=H1;
                            P[1].y=Y1;
                            P[2].x=H2;
                            P[2].y=Y2;
                            P[3].x=ProfilRect.right;
                            P[3].y=Y2;
                            }
                        int drclass=Slp->DrwClassId;
                        TDrwClassesRec *ClRec=DrCl->Items[drclass];
                        for (int k=0;k<MAXDRWPARAM;k++)
                            {
                            TDrwParamRec *Rec=NULL;
                            try
                                {Rec=DrPar->Items[ClRec->DrwParamId[k]];}
                            catch (...) {}
                            if (!Rec)
                                continue;
                            CallDrawFunc(Cont,Poly,Rec,&R,false);
                            }
                        SelectObject(dc,GetStockObject(BLACK_PEN));
                        String Str=String(Slp->Promille);
                        if (Slp->Radius>0)
                           Str=Str+" "+String(Slp->Radius);
                        if (FPlanKind==pkGorizontal)
                            {
                            MoveToEx(dc,X1,ProfilRect.bottom,NULL);
                            LineTo(dc,X1,ProfilRect.top);
                            MoveToEx(dc,X2,ProfilRect.bottom,NULL);
                            LineTo(dc,X2,ProfilRect.top);
                            DrawText(dc,Str.c_str(),Str.Length(),&TRect(X1,ProfilRect.top,X2,ProfilRect.bottom),41|DT_NOCLIP);
                            }
                        else
                            {
                            MoveToEx(dc,ProfilRect.left,Y1,NULL);
                            LineTo(dc,ProfilRect.right,Y1);
                            MoveToEx(dc,ProfilRect.left,Y2,NULL);
                            LineTo(dc,ProfilRect.right,Y2);
                            DrawText(dc,Str.c_str(),Str.Length(),&TRect(ProfilRect.left,Y2,ProfilRect.right,Y1),41|DT_NOCLIP);
                            }
                        }
                    }
                delete Poly;
                }
            }
        else
            {
            TExtPolyline *Poly=Road->GetProfilMetric(ProfilRect);
            if (Poly)
                {
                Poly->DrawTo(dc,GetStockObject(BLACK_PEN),GetStockObject(BLACK_BRUSH));
                int n=Road->Geometry.Count;
                int napr=1;
                int PrevOutPos;
                if (FPlanKind==pkGorizontal)
                    {if (FPlanDirect==pdDirect)
                        PrevOutPos=0;
                    else
                        PrevOutPos=OutRect->right;
                    }
                else
                    {
                    if (FPlanDirect==pdDirect)
                        PrevOutPos=OutRect->bottom;
                    else
                        PrevOutPos=0;
                    }
                int PrevI=0;
                TGeometryVal *Geom=Road->Geometry.Values;
                for (int i=1;i<n;i++)
                    {
                    int newnapr;
                    if (Geom[i].Z>Geom[i-1].Z)
                        newnapr=1;
                    else if (Geom[i].Z<Geom[i-1].Z)
                        newnapr=-1;
                    else
                        newnapr=0;
                    if (napr*newnapr<0)
                        {  // возможно вывести значение
                        SIZE strsize;
                        String Z=String(((double)Geom[i-1].Z-Road->ZMin)/100);
                        GetTextExtentPoint32(dc,Z.c_str(),Z.Length(),&strsize);
                        if (FPlanKind==pkGorizontal)
                            {
                            int outx=(Poly->Points[i+1].x+Poly->Points[PrevI+2].x-strsize.cx)>>1;
                            bool dodraw=false;
                            if (FPlanDirect==pdDirect)
                                {if (outx>PrevOutPos)
                                PrevOutPos=outx+strsize.cx+2,dodraw=true;
                                }
                            else
                                {if (outx+strsize.cx<PrevOutPos)
                                    PrevOutPos=outx-2,dodraw=true;
                                }
                            if (dodraw)
                                {
                                int outy=Poly->Points[i+1].y;
                                if (newnapr>0)
                                    outy-=5+strsize.cy;
                                else
                                    outy+=5;
                                if (outy<0)
                                    outy=0;
                                if (outy>OutRect->bottom-strsize.cy)
                                    outy=OutRect->bottom-strsize.cy;
                                TextOut(dc,outx,outy,Z.c_str(),Z.Length());
                                }
                            }
                        else
                            {
                            int outy=(Poly->Points[i+1].y+Poly->Points[PrevI+2].y-strsize.cy)>>1;
                            bool dodraw=false;
                            if (FPlanDirect==pdUndirect)
                                {if (outy>PrevOutPos)
                                    PrevOutPos=outy+strsize.cy+2,dodraw=true;
                                }
                            else
                                {if (outy+strsize.cy<PrevOutPos)
                                    PrevOutPos=outy-2,dodraw=true;
                                }
                            if (dodraw)
                                {
                                int outx=Poly->Points[i+1].x;
                                if (newnapr>0)
                                    outx-=5+strsize.cx;
                                else
                                    outx+=5;
                                TextOut(dc,outx,outy,Z.c_str(),Z.Length());
                                }
                            }
                        napr=newnapr;
                        }
                    if (newnapr!=0)
                        PrevI=i;
                    }
                delete Poly;
                }
            }
        SelectObject(dc,oldfont);
        DeleteObject(labfont);
        }
}

void __fastcall TDrawManager::DrawRoad(int codes,bool *Mask,TDrawContents *Cont,RECT *OutRect)
{
FreeHash();
if (FVisSet)
    if (FVisSet->MetricSource)
        {
        SelectObjects(codes,Mask,Cont->L1,Cont->L2);
        SortObjects();
        PrepareMetric(Cont,OutRect);
        FindSignsPlacement(Cont);
        DrawObjects(Cont,2);
        if (SetROP2(Cont->DC,R2_MERGEPEN))
            {
            if (GetROP2(Cont->DC)==R2_MERGEPEN)
                if (FrmSetting->RopEnabled)
                    {
                    SelectObject(Cont->DC,CreateSolidBrush(0x808080));
                    Rectangle(Cont->DC,0,0,Cont->Width,Cont->Height);
                    DeleteObject(SelectObject(Cont->DC,GetStockObject(NULL_BRUSH)));
                    }
            }
        SetROP2(Cont->DC,R2_COPYPEN);
        void *Reg=CreateRectRgnIndirect(OutRect);
        SelectClipRgn(Cont->DC,Reg);
        DrawObjects(Cont,1);
        SelectClipRgn(Cont->DC,NULL);
        DeleteObject(Reg);
        }
}

void __fastcall TDrawManager::FillCont(TDrawContents *Cont)
{
HDC dc=Cont->GetContentDC();
SelectObject(dc,GetStockObject(WHITE_BRUSH));
SelectObject(dc,GetStockObject(WHITE_PEN));
Rectangle(dc,0,0,Cont->Width,Cont->Height);
}

void __fastcall TDrawManager::DrawByCodes(int max,bool *vis,TDrawContents* Cont,__int32 fl,__int32 fx,double dpsm,RECT *OutRect,TPlanKind pk,TPlanDirect pd)
{
FDpsm=dpsm;
FSclL=fl;
FSclX=fx;
FPlanKind=pk;
FPlanDirect=pd;
DrawRoad(max,vis,Cont,OutRect);
}

void __fastcall TDrawManager::DrawAll(TDrawContents *Cont,__int32 fl,__int32 fx,double dpsm,RECT *OutRect,TPlanKind pk,TPlanDirect pd)
{
bool Mask[MAXCODEID];
for (int i=0;i<MAXCODEID;i++)
  Mask[i]=true;
Mask[DANGERSLOPECODE]=false;
Mask[DANGERCURVECODE]=false;
Mask[ROADDRESSCODE]=false;
DrawByCodes(MAXCODEID,Mask,Cont,fl,fx,dpsm,OutRect,pk,pd);
}

void __fastcall TDrawManager::DrawByCode(__int32 Code,TDrawContents *Cont,__int32 fl,__int32 fx,double dpsm,RECT *OutRect,TPlanKind pk,TPlanDirect pd)
{
bool Mask[MAXCODEID];
for (int i=0;i<MAXCODEID;i++)
  Mask[i]=false;
Mask[Code]=true;
DrawByCodes(MAXCODEID,Mask,Cont,fl,fx,dpsm,OutRect,pk,pd);
}

void __fastcall TDrawManager::DrawObjectMetric(HDC dc,int index)
{
void *pen=CreatePen(PS_SOLID,2,clBlue);
int oldrop=SetROP2(dc,R2_XORPEN);
if (index<ObjCount)
    Polys[index]->DrawPoly(dc,pen,GetStockObject(NULL_PEN));
DeleteObject(pen);
SetROP2(dc,oldrop);
}

void __fastcall TDrawManager::DrawSelected(HDC dc)
{
void *oldpen=SelectObject(dc,CreatePen(PS_SOLID,2,clBlue));
for (int i=0;i<ObjCount;i++)
    if (Objs[i]->Selected)
        {
        RECT *prect=&(RectsMan.Rects[i].Rect);
        MoveToEx(dc,prect->left-5,prect->top-5,NULL);
        LineTo(dc,prect->right+5,prect->top-5);
        LineTo(dc,prect->right+5,prect->bottom+5);
        LineTo(dc,prect->left-5,prect->bottom+5);
        LineTo(dc,prect->left-5,prect->top-5);
        }
DeleteObject(SelectObject(dc,oldpen));
}

void __fastcall TDrawManager::StopDrawing(void)
{
}

TRoadObject* __fastcall TDrawManager::FindNearestL(__int32 &L,TRoadObject *obj,__int32 DL)
{
TRoadObject *res=NULL;
__int32 NewL;
for (int i=0;i<ObjCount;i++)
    {
    TRoadObject *robj=Objs[i];
    if (robj!=obj)
        {
        TContRoadObject *cobj=dynamic_cast<TContRoadObject*>(robj);
        if (cobj)
            {
            int d=abs(L-cobj->LMax);
            if (d<DL)
                DL=d,NewL=cobj->LMax,res=cobj;
            }
        int d=abs(L-robj->L);
        if (d<DL)
            DL=d,NewL=robj->L,res=robj;
        TPolyline *Poly=robj->Poly;
        if (Poly)
            {
            int n=Poly->Count;
            for (int i=0;i<n;i++)
                {
                int d=abs(L-(*Poly)[i].L);
                if (d<DL)
                    DL=d,NewL=(*Poly)[i].L,res=robj;
                }
            }
        }
    }
if (res)
    L=NewL;
return res;
}

void __fastcall TDrawManager::LeepPoint(int& PX,int &PY,TRoadObject *obj,__int32 DL)
{
int L,X;
Road->RConvertPoint(PX,PY,L,X);
if (FindNearestL(L,obj,DL))
    Road->ConvertPoint(L,X,PX,PY);
}

int __fastcall TDrawManager::SelectByXY(__int32 X,__int32 Y,TRoadObject** Array,TDtaSource **Src,int *Indexes,int max)
{
int selcount=0;
int *LenToObj=new int [ObjCount];
POINT p1,p2;
p1.x=X;
p1.y=Y;
int index;
for (int i=0;i<ObjCount;i++)
    {
    double d=Polys[i]->LenTo(p1,p2,index);
    if (d>0x100000)
        LenToObj[i]=0x100000;
    else
        LenToObj[i]=d;
    if (dynamic_cast<TRoadSign*>(Objs[i]))
        {
        RECT *r=GetRect(i);
        if ((X<=r->right)&&(X>=r->left)&&(Y>=r->top)&&(Y<=r->bottom))
            LenToObj[i]=0;
        }
    }
if (ObjCount>0)
    {
    int *Lens=new __int32 [max+1];
    Lens[0]=FSensetive;
    for (int i=0;i<ObjCount;i++)
        if (LenToObj[i]<FSensetive)
                {
                int j;
                for (j=0;Lens[j]<LenToObj[i];j++)
                        {}
                if (j<max)
                        {
                        if (selcount<max)
                                {
                                selcount++;
                                Lens[selcount]=FSensetive;
                                }
                        for (int k=selcount-1;k>j;k--)
                                {
                                Lens[k]=Lens[k-1];
                                Array[k]=Array[k-1];
                                Src[k]=Src[k-1];
                                Indexes[k]=Indexes[k-1];
                                }
                        Lens[j]=LenToObj[i];
                        Array[j]=Objs[i];
                        Src[j]=Sources[i];
                        Indexes[j]=i;
                        }
                }
    delete[] Lens;
    }
delete[] LenToObj;
return selcount;
}
