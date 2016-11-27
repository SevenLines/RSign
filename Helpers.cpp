//---------------------------------------------------------------------------


#pragma hdrstop

#include "Helpers.h"
#include <vector>

//---------------------------------------------------------------------------

#pragma package(smart_init)


float Helpers::GetAngle(TPoint vec1, TPoint vec2)
{
    /* Возвращает угол между векторами*/
    float temp = (float)(vec1.x * vec2.x + vec1.y * vec2.y) /
          (sqrt(vec1.x * vec1.x + vec1.y * vec1.y) * sqrt(vec2.x * vec2.x + vec2.y * vec2.y));
    if (temp < -1)
        return M_PI;
    else if (temp > 1)
        return 0;
    else
        return acos(temp);
}

float Helpers::GetAngle2(TPoint &p1, TPoint &p2, float ScaleY, float *length) {
    /* Возвращает угол между вектором образованым точками p1 и p2 и осью X
     * Если указан параметр length в него попадет длина вектора
    */
    float yoffset = -ScaleY * (p2.y - p1.y);
    float xoffset = p2.x - p1.x;
    float angle = xoffset != 0 ? atan(yoffset / xoffset) : yoffset < 0 ? -M_PI_2 : M_PI_2;
    if (xoffset < 0)angle += M_PI;
    if (length) 
        *length = Helpers::GetLength(p1, p2, ScaleY);
    return angle;
}


float  Helpers::GetLength(TPoint p1, TPoint p2, float ScaleY)
{
    float yoffset = -ScaleY * (p2.y - p1.y);
    float xoffset = p2.x - p1.x;
    return sqrt(yoffset * yoffset + xoffset * xoffset);
}

// функция для сортировки знаков
bool  Helpers::compareSigns(const TRoadSign* s1, const TRoadSign* s2)
{
    /*    return s1->OldTitle < s2->OldTitle;*/
    int order[] = {
        2, 1, 5, 3, 4, 6, 7, 8
    };

    int signNum1;
    int signNum2;
    if (TryStrToInt(s1->OldTitle.SubString(0, 1), signNum1)
            && TryStrToInt(s2->OldTitle.SubString(0, 1), signNum2)) {
        if (s1->OldTitle.Pos("8.13") && signNum2 != 2) {
            return true;
        }
        if (signNum1 != 2 && s2->OldTitle.Pos("8.13")) {
            return false;
        }
        if (order[signNum1 - 1] == order[signNum2 - 1]) {
            return s1->OldTitle < s2->OldTitle;
        }
        return order[signNum1 - 1] < order[signNum2 - 1];
    }
    return false;
}

AnsiString Helpers::SignLabelParser(AnsiString signName, AnsiString label)
{
    AnsiString temp = label;
    if (signName == "8.2.2" ||
            signName == "3.13") {
        if (label.UpperCase()[label.Length()] == 'М') {
            label = Trim(label.SubString(1, label.Length() - 1));
        }
    }
    return label;
}

int Helpers::GetAngle(TPoint p0, TPoint p1, TPoint p2)
{
    float vec1[2], vec2[2];
    vec1[0] = p1.x - p0.x;
    vec1[1] = p1.y - p0.y;
    vec2[0] = p2.x - p0.x;
    vec2[1] = p2.y - p0.y;

    double anorm = sqrt(vec1[0] * vec1[0] + vec1[1] * vec1[1]);
    double bnorm = sqrt(vec2[0] * vec2[0] + vec2[1] * vec2[1]);

    if (anorm == 0 || bnorm == 0) return 0;

    double cosangle = (vec2[0] * vec1[0] + vec2[1] * vec1[1]) / (anorm * bnorm);
    if (cosangle < -1) cosangle = -1;
    if (cosangle > 1) cosangle = 1;
    double angle = acos(cosangle);
    float dirSign = vec1[0] * vec2[1] - vec1[1] * vec2[0];
    if (dirSign < 0 && angle != 0)
        angle = -angle;

    if (angle == M_PI) return 180;
    if (angle == -M_PI) return -180;
    return angle * 180 / M_PI;
}

AnsiString Helpers::StringConvertSignals(float f1, float f2, void* data)
{
    int counter = 0;
    AnsiString temp;
    int t = int(f2) % 100000 / 100;
    int i;
    std::vector<int>* signalsPositions = (vector<int>*)data;

    for (i = 0; i < signalsPositions->size(); ++i) {
        if (signalsPositions->at(i) >= f1 - 1 && signalsPositions->at(i) <= f2 + 1) {
            counter++;
        }
    }
    if (fabs(f2 - f1) >= lessForVerticalLabels * 100) {
        temp.printf(" [%i; %i]", int(f1) % 100000 / 100, t == 0 ? 1000 : t);
        return IntToStr(counter) + "шт." + temp;
    }
    return IntToStr(counter) + "шт.";
}


AnsiString Helpers::StringConvert(float f1, float f2, void* data)
{
    int t = int(f2) % 100000 / 100;
    int t1, t2;
    t1 =  int(f1) % 100000 / 100;
    t2 =  t == 0 ? 1000 : t;
    //if(t2-t1<50) return "";
    if (t2 - t1 >= lessForVerticalLabels) {
        AnsiString temp;
        temp.printf(" [%i; %i]", t1, t2);
        return temp;
    } else {
        return "";
    }
}

void Helpers::swap(int &x, int &y)
{
    int t = x;
    x = y;
    y = t;
}