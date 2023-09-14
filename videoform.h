#ifndef VIDEOFORM_H
#define VIDEOFORM_H

#include <QWidget>
#include <QUdpSocket>
#include <QImage>
#include <qnetwork.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QMouseEvent>

namespace Ui {
class VideoForm;
class SettingForm;

}

class VideoForm : public QWidget
{
    Q_OBJECT

public:
    explicit VideoForm(QWidget *parent = nullptr);
    ~VideoForm();
    QImage daveImage;
    QPixmap davePixmap;

    sockaddr_in server;
    void loadImageData();

    QString ip[4];

    QString ip1;

    QImage rorateImage(const QImage &image, int angle,const QPoint &center);

    // bool eventFilter(QObject *target, QEvent *event);

signals:
    void ipInfo(QString);
    void focusIp(QString);
    void sendCar1(QPixmap,QString);
    void sendCar2(QPixmap,QString);
    void sendCar3(QPixmap,QString);
    void sendCar4(QPixmap,QString);
    void doubleClicked();
    void click2();
private:
    Ui::VideoForm *ui;

    int curspeed;
    int curspeed2;
    int curspeed3;
    int curspeed4;

    QImage rotateArrow;


private slots:


    void videoServer();



    QString ipExpression(QString);
public:
    QUdpSocket* udpSocket;



};

#endif // VIDEOFORM_H
