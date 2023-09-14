#ifndef FOCUSFORM_H
#define FOCUSFORM_H
#include "videoform.h"
#include <QtXml/QDomDocument>
#include <QWidget>
#include <QUdpSocket>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <qnetwork.h>
namespace Ui {
class FocusForm;

}
class MessageWidget;
class FocusForm : public QWidget
{
    Q_OBJECT

public:
    explicit FocusForm(QWidget *parent = nullptr);
    ~FocusForm();

signals:

    void car1();
    void car2();
    void car3();
    void car4();
    void widgetSignal(QString, QString, QString, QString, QString, QString,QString, QString, QString, QString, QString);


private slots:


    void focusImage(QPixmap,QString);

    void camServer();
    void messageServer();

    void makeWidget(QString, QString, QString, QString, QString, QString,QString, QString, QString, QString, QString);


    void on_car1PushButton_clicked();
    void on_car2PushButton_clicked();
    void on_ca3PushButton_clicked();
    void on_pushButton_4_clicked();

    void on_connect_PushButton_clicked();

    void on_disconnect_PushButton_clicked();



private:
    Ui::FocusForm *ui;
    QUdpSocket* camSocket;
    QUdpSocket* messageSocket;

    VideoForm* videoForm;

    QString text;
    QString popup;

    MessageWidget* messageWidget;


    int flag;
    int rsaflag;

    int stopCnt;
    int slowCnt;




};

#endif // FOCUSFORM_H
