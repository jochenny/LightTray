#include "tray.h"

#include <QGuiApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QScreen>
#include <QDebug>
#include <QLabel>
#include "lightcontrol.h"

tray::tray()
{
    m_rc = new LightControl;

    m_startupAction.setText("a");
    m_quitAction.setText("b");
    m_menu.addAction(&m_startupAction);
    m_menu.addAction(&m_quitAction);
    m_trayIcon.setContextMenu(&m_menu);

    m_trayIcon.setIcon(QIcon(":/images/bad.png"));
    m_trayIcon.setVisible(true);
    m_trayIcon.show();

    connect(&m_trayIcon, &QSystemTrayIcon::activated, this, &tray::on_trayActivated);
    connect(&m_brightSlider, &QSlider::valueChanged, m_rc, &RangeControl::setValue);

    QScreen *screen = QGuiApplication::primaryScreen();
    const QRect deskRect = screen->availableGeometry();
    // 横向
    m_brightSlider.setOrientation(Qt::Horizontal);
    const int width = 500;
    const int height = 30;
    m_brightSlider.setFixedSize(width, height);
    // 置于右下角
    m_brightSlider.setGeometry(deskRect.width() - width,
                               deskRect.height() - height,
                               width,
                               height);
    m_brightSlider.setFocusPolicy(Qt::StrongFocus);

    m_brightSlider.setTickInterval(50);
    m_brightSlider.setTickPosition(QSlider::TicksAbove);

    Qt::WindowFlags flags;
    flags |= Qt::FramelessWindowHint;   // 去窗口头
    flags |= Qt::WindowStaysOnTopHint;  // 置顶
    flags |= Qt::Popup;                 // 类似模态，点击窗口外关闭窗口
    m_brightSlider.setWindowFlags(flags);
    // 滑块在释放时valueChanged()
//    m_brightSlider.setTracking(false);

    m_brightSlider.setMaximum(m_rc->maximum());
    m_brightSlider.setMinimum(m_rc->minimum());
    m_brightSlider.setValue(m_rc->value());

    m_brightSlider.setStyleSheet("QSlider{ \
                                 border-color: #bcbcbc; \
                                 } \
                                 QSlider::groove:horizontal { \
                                      border: 1px solid #999999; \
                                     height: 1px; \
                                    margin: 0px 0;\
                                 left: 5px; right: 5px;\
                                  }\
                                 QSlider::handle:horizontal { \
                                      border: 0px ; \
                                      border-image:  url(:/images/heart.png);\
                                      width: 15px;                                           \
                                      margin: -7px -7px -7px -7px;                  \
                                 } \
                                 QSlider::add-page:horizontal{\
                                 background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 #bcbcbc, stop:0.25 #bcbcbc, stop:0.5 #bcbcbc, stop:1 #bcbcbc); \
                                 }\
                                 QSlider::sub-page:horizontal{                               \
                                  background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 #439cf3, stop:0.25 #439cf3, stop:0.5 #439cf3, stop:1 #439cf3);                     \
                                 }");

//    QSystemTrayIcon *trayIcon = new QSystemTrayIcon();
//    trayIcon->setIcon(QIcon(":/images/bad.png"));
//    trayIcon->setVisible(true);

}

void tray::on_trayActivated(QSystemTrayIcon::ActivationReason reason)
{

    if (reason == QSystemTrayIcon::ActivationReason::Trigger) {
        qDebug() << m_rc->value();

        double per = static_cast<double>(m_brightSlider.value()) / (m_brightSlider.maximum() - m_brightSlider.minimum());

        int x = static_cast<int>(per * width());

        m_brightSlider.valueLabel.setNum(m_brightSlider.value());

        m_brightSlider.valueLabel.setGeometry(this->x() + x, this->y() - 30, 30, 30);
    //    m_brightSlider.valueLabel.show();
        m_brightSlider.show();
    }


}

tray::ClickSlider::ClickSlider(QWidget *parent)
{
    Q_UNUSED(parent);
    qDebug() << value();
//    valueLabel.setParent(this);
    valueLabel.setStyleSheet("color: white;");
    valueLabel.setWindowFlags(Qt::FramelessWindowHint);
    valueLabel.setAttribute(Qt::WA_TranslucentBackground, true);//窗体背景全透明
//    m_valueLabel.setStyleSheet("background:transparent;");
    valueLabel.setNum(0);
    valueLabel.show();
    connect(this, &QSlider::valueChanged, this, [this](int value){
        valueLabel.setNum(value);
        valueLabel.show();
    });
}

void tray::ClickSlider::mousePressEvent(QMouseEvent *ev)
{
    valueLabel.setGeometry(this->x() + ev->x(), this->y() - 30, 30, 30);

    // 不在控件范围内
    qDebug() << ev->x() << "," << ev->y();
    qDebug() << width() << "," << height();
    if (ev->x() < 0 || ev->x() > width() ||
        ev->y() < 0 || ev->y() > height()) {
        qDebug() << ev->x() << "," << ev->y();
        this->hide();
        valueLabel.hide();
        return;
    }

    double x = static_cast<double>(ev->pos().x());

    double per = x / width();

    int value = per * (maximum() - minimum()) + minimum();


    setValue(value);

    QSlider::mousePressEvent(ev);
}

void tray::ClickSlider::mouseMoveEvent(QMouseEvent *ev)
{

    valueLabel.setGeometry(this->x() + ev->x(), this->y() - 30, 30, 30);

    // 不在控件范围内
    qDebug() << ev->x() << "," << ev->y();
    qDebug() << width() << "," << height();
    if (ev->x() < 0 || ev->x() > width() ||
        ev->y() < 0 || ev->y() > height()) {
        qDebug() << ev->x() << "," << ev->y();
        this->hide();
        valueLabel.hide();
        return;
    }

    double x = static_cast<double>(ev->pos().x());

    double per = x / width();

    int value = per * (maximum() - minimum()) + minimum();


    setValue(value);

    QSlider::mouseMoveEvent(ev);
}
