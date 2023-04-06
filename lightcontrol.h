#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H

#include "rangecontrol.h"

class LightControl : public RangeControl
{
public:
    LightControl();

    void setValue(int value) override;
    void setBright(int bright);

private:
    int setGamma(int bright);
    int getGamma();
};

#endif // LIGHTCONTROL_H
