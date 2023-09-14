#include "settingform.h"
#include "ui_settingform.h"
#include <videoform.h>
#include <QDebug>
#include <opencv2/opencv.hpp>

#include <QFileDialog>
#include <QString>
struct Info
{
    int32_t speed;
    int32_t degree;
};


SettingForm::SettingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingForm)
{
    ui->setupUi(this);

//    quint16 port3 = 2234;
//    obuSocket = new QUdpSocket(this);
//    obuSocket->bind(QHostAddress::Any, port3);

//    connect(obuSocket, SIGNAL(readyRead()), this, SLOT(obuServer()));


}

SettingForm::~SettingForm()
{
    delete ui;
}
//void SettingForm::obuServer()
//{

//    Info carInfo;
//    QByteArray datagram;
//    QHostAddress obuSender;
//    quint16 obuPort;


//    datagram.resize(obuSocket->pendingDatagramSize());
//    obuSocket->readDatagram(datagram.data(), datagram.size(), &obuSender, &obuPort);
//     QString obuIpAddress = obuSender.toString().split(":").last();

//    if (datagram.size() == sizeof(Info))
//    {

//        memcpy(&carInfo, datagram.constData(), sizeof(carInfo));
//        //     qDebug() << "car speed: " << carInfo.speed << Qt::endl;
//        qDebug() << "car degree: " << carInfo.degree ;
//    }

//    if ( obuIpAddress == "192.168.4.54")
//    {

//        ui->car1_DegreeLabel->setText(QString::number(carInfo.degree));
//        ui->car1_SpeedLabel->setText(QString::number(carInfo.speed));
//    }


//}
void SettingForm::addIP(QString ip)
{
    if ( ip == "192.168.4.54")
    {ui->lineEdit->setText(ip);
    }
    else if (ip == "192.168.4.63")
    {
        ui->lineEdit_2->setText(ip);
    }
    else if (ip == "192.168.4.95")
    {
        ui->lineEdit_3->setText(ip);
    }
    else
    {
        ui->lineEdit_4->setText(ip);
    }

}



