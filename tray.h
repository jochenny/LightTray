#ifndef TRAY_H
#define TRAY_H
#include <QLabel>
#include <QMenu>
#include <QSlider>
#include <QSystemTrayIcon>
#include "rangecontrol.h"

///
/// \brief The tray class
/// 1. 亮度图标是亮度的百分比圆
/// 2. 亮度条放在menu中调节
///
class tray : public QWidget
{
    Q_OBJECT
public:
    tray();

private:

    void on_trayActivated(QSystemTrayIcon::ActivationReason reason);

    // 系统托盘
    QSystemTrayIcon m_trayIcon;
    // 托盘菜单
    QMenu m_menu;
    // 开机自启功能
    QAction m_startupAction;
    // 退出功能
    QAction m_quitAction;
    // 调节亮度滑条
    RangeControl *m_rc;

    class ClickSlider : public QSlider{
    public:
        ClickSlider(QWidget *parent = nullptr);
        ~ClickSlider() {};
        QLabel valueLabel;
        void mousePressEvent(QMouseEvent *ev) override;
        void mouseMoveEvent(QMouseEvent *ev) override;
    };

    ClickSlider m_brightSlider;
};

#endif // TRAY_H
