#include "rangecontrol.h"

RangeControl::RangeControl()
{

}

int RangeControl::maximum() const
{
    return m_maximum;
}

void RangeControl::setMaximum(int maximum)
{
    m_maximum = maximum;
}

int RangeControl::minimum() const
{
    return m_minimum;
}

void RangeControl::setMinimum(int minimum)
{
    m_minimum = minimum;
}

int RangeControl::value() const
{
    return m_value;
}

void RangeControl::setValue(int value)
{
    m_value = value;
}
