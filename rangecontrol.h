#ifndef RANGECONTROL_H
#define RANGECONTROL_H
#include <QObject>

class RangeControl : public QObject
{
    Q_OBJECT
public:
    RangeControl();

    int maximum() const;
    void setMaximum(int maximum);

    int minimum() const;
    void setMinimum(int minimum);

    virtual int value() const;
    virtual void setValue(int value);

private:
    int m_maximum;
    int m_minimum;
    int m_value;
};

#endif // RANGECONTROL_H
