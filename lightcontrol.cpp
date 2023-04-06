#include "lightcontrol.h"
#include <windows.h>
#include <highlevelmonitorconfigurationapi.h>
#include <physicalmonitorenumerationapi.h>
#include <QDebug>


LightControl::LightControl()
{

    int bright = getGamma();
    setMaximum(bright + 200);
    setMinimum(0);
    qDebug() << bright;
    setValue(bright);
//    setValue(value());
}

void LightControl::setValue(int value)
{
    RangeControl::setValue(value);
    setBright(value);
}


void LightControl::setBright(int bright)
{
    setGamma(bright);
}

/*
调整亮度 参数0-100
设置成功返回0
设置失败返回负数
*/
int LightControl::setGamma(int bright)
{
    void * lpGamma = NULL;
    int iArrayValue;
    WORD gMap[3][256] = {{0}};
    lpGamma = &gMap;
    HDC hdc = ::GetDC(NULL);
    if (NULL == hdc)
        return -1;
    for (int i = 0; i < 256; i++)
    {
        iArrayValue = i * (bright + 128);
        if (iArrayValue > 65535)
            iArrayValue = 65535;
            gMap[0][i] =
            gMap[1][i] =
            gMap[2][i] = (WORD)iArrayValue;
    }
    if (FALSE == SetDeviceGammaRamp(hdc, lpGamma))
        return -2;
    return 0;
}

int LightControl::getGamma()
{
    void * lpGamma = NULL;
    WORD gMap[3][256] = {{0}};
    lpGamma = &gMap;
    HDC hdc = ::GetDC(NULL);
    if (NULL == hdc)
        return -1;
    WINBOOL res = GetDeviceGammaRamp(hdc, lpGamma);
    int brightness = 100;
    if (TRUE == res) {
         brightness = gMap[0][1] - 128;
    }

    return brightness;
}
