#ifndef LIGHTICON_H
#define LIGHTICON_H

#include <QIcon>
#include <QPaintDevice>



class LightIcon : public QIcon
{
public:
    LightIcon();

    void paintEvent(QPaintEvent *event) override;
};

#endif // LIGHTICON_H
