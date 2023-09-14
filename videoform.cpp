#include "videoform.h"
#include "ui_videoform.h"

#include <QPixmap>
#include <QHostAddress>
#include <QDebug>
#include <iostream>
#include <QImage>
#include <QPainter>
#include <QTransform>



using namespace std;
using namespace cv;
#define MAX_BUFFER_SIZE 1024
struct Info
{
    int32_t speed;

    int32_t degree;
};

struct Village
{

    char abc[1024];
    int32_t medium;
    int32_t big;


};

VideoForm::VideoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoForm)
{
    ui->setupUi(this);

    quint16 port = 1234;
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, port);

    //    quint16 port2 = 2234;
    //    messageSocket = new QUdpSocket(this);
    //    messageSocket->bind(QHostAddress::Any, port2);

    //  connect(messageSocket, SIGNAL(readyRead()), this, SLOT(messageServer()));
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(videoServer()));
    //   connect(obuSocket, SIGNAL(readyRead()), this, SLOT(obuServer()));

   // connect(ui->verticalSlider, &QSlider::valueChanged, this, &VideoForm::on_slider_valueChanged);

    curspeed = 0;
    curspeed2 = 0;
    curspeed3 = 0;
    curspeed4 = 0;

}
QString VideoForm::ipExpression(QString ip1)
{
    //  qDebug() << ip1;
    return ip1;
}

QImage rotateImage(const QImage &image, int angle, const QPoint &center)
{
    QTransform transform;


    transform.rotate(angle); // 각도만큼 회전


    return image.transformed(transform);

}

void VideoForm::videoServer()
{
    Info carInfo;


    QByteArray Buffer;
    QByteArray totalData;


    Buffer.resize(udpSocket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    //    udpSocket->readDatagram(Buffer.data(),Buffer.size(),&sender,&senderPort);
    //    daveImage.loadFromData(Buffer);

    // while (udpSocket->hasPendingDatagrams()) {
    totalData.resize(udpSocket->pendingDatagramSize());
    udpSocket->readDatagram(totalData.data(), totalData.size(),&sender,&senderPort);
    //    imageData.append(Buffer);

    //   }
    QString senderIpAddress = sender.toString().split(":").last();

   // qDebug() << "ip[0]1: "<<ip[0];

 //   qDebug() << " Start ";

    if(ip[0].isEmpty())
    {
        ip[0] = senderIpAddress;
    }
    else if ( senderIpAddress != ip[0] && ip[1].isEmpty())
    {
        ip[1] = senderIpAddress;
    }
   else  if ( senderIpAddress != ip[0] && senderIpAddress != ip[1] && ip[2].isEmpty())
    {
        ip[2] = senderIpAddress;
    }
    else if ( senderIpAddress != ip[0] && senderIpAddress != ip[1] && senderIpAddress != ip[2] && ip[3].isEmpty())
    {
        ip[3] = senderIpAddress;
    }



    qDebug() << "ip[0]" << ip[0];
    qDebug() << "ip[1]" << ip[1];
    QByteArray infoData = totalData.mid(totalData.size() - sizeof(Info));


  //  qDebug() << "infoData Size" << infoData.size();

  //  qDebug() << "infoData ssize" << sizeof(Info);

    memcpy(&carInfo,infoData.data(), sizeof(Info));

   // qDebug() << "degree: " << carInfo.degree;
   // qDebug() << "speed: "  << carInfo.speed;



    QByteArray decodedData = QByteArray::fromBase64(totalData);
    std::vector<uchar> imageBuffer(decodedData.begin(), decodedData.end());


    //  qDebug() << senderIpAddress;

    cv::Mat frame =  cv::imdecode(imageBuffer, cv::IMREAD_COLOR);

    int height = frame.rows;
    int width = frame.cols;

    int channel = frame.channels();
    int bytesPerLine = channel * width;

    QImage iconImage(":/new/prefix1/resources/stream.png");
    QPixmap icon = QPixmap::fromImage(iconImage);
    icon = icon.scaled(ui->iconLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->iconLabel->setPixmap(icon);

    QImage carImage(":/new/prefix1/resources/car.png");
    QPixmap carIcon = QPixmap::fromImage(carImage);

    QImage busImage(":/new/prefix1/resources/bus.png");
    QPixmap busIcon = QPixmap::fromImage(busImage);

    QImage testimage(frame.data, width, height, bytesPerLine, QImage::Format_BGR888);

    QPixmap testpixmap = QPixmap::fromImage(testimage);

    QPixmap Viewer(testpixmap.width(), testpixmap.height());
    Viewer.fill(Qt::transparent);

    // Resize the image to the desired size (e.g., 200x200)

  //  QString degree1 = ui->handle->text();
  //  int degree = degree1.toInt();

  //  QImage wheel2("C:\\TestStraming\\build-TestStreaming-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\yellow.png");


//    QImage arrowheel2("arrowheel.png");
//    QImage arrowheel = arrowheel2.scaled(  120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation);


    ui->video_label_1->setStyleSheet("background-color: rgba(125, 187, 50, 50);");
    ui->video_label_2->setStyleSheet("background-color: rgba(125, 187, 50, 50);");
    ui->video_label_3->setStyleSheet("background-color: rgba(125, 187, 50, 50);");
    ui->video_label_4->setStyleSheet("background-color: rgba(125, 187, 50, 50);");

    ui->video_label_4->installEventFilter(new QObject);
    ui->video_label_4->setMouseTracking(true);



    QImage tachometer2(":/new/prefix1/resources/porsche.png");
    QImage tachometer = tachometer2.scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap tacho = QPixmap::fromImage(tachometer);


    QImage wheel2(":/new/prefix1/resources/red.png");
    QImage wheel = wheel2.scaled(  120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation);


    QImage arrow3(":/new/prefix1/resources/second.png");
    QImage arrow2 = arrow3.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //QPixmap arrow = QPixmap::fromImage(arrow2);


    QImage warning2(":/new/prefix1/resources/bblind4.png");
    QImage warning = warning2.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap blind = QPixmap::fromImage(warning);


    if (senderIpAddress == ip[0] )
    {
         int32_t degree1 = 90;
         degree1 = carInfo.degree;
         int32_t degree2 = degree1 - 75;


         QPoint center(wheel.width() / 2, wheel.height() / 2);

         QImage rotatedImage = rotateImage(wheel, degree2, center);

         QPixmap overlay = QPixmap::fromImage(rotatedImage);

         int pointx = 105;
         int pointy = 188;

         int centerX = rotatedImage.width() / 2;
         int centerY = rotatedImage.height() / 2;

         int arrowx = 205;
         int arrowy = 222;

         int realSpeed = carInfo.speed;

         int clusterspeed = (9*curspeed + realSpeed) / 10;

         curspeed = clusterspeed;

         QPoint arrowCenter(arrow2.width() / 2, arrow2.height() / 2);
         QImage rotateArrow = rotateImage(arrow2, clusterspeed , arrowCenter);

         QPainter painter(&Viewer);
         QPixmap overlayArrow = QPixmap::fromImage(rotateArrow);

         QString speed = QString::number(carInfo.speed);

         painter.setPen(QColorConstants::Svg::blueviolet);
         painter.setFont(QFont("Arial", 20));
         painter.drawPixmap(0,0,testpixmap);           //자동차 화면
         painter.drawPixmap(pointx - centerX,pointy - centerY,overlay);
         painter.drawPixmap(arrowx  - (rotateArrow.width() / 2) , arrowy - (rotateArrow.height() / 2 )  , overlayArrow);

         painter.drawPixmap(155,140,tacho);

        ui->video_label_1->setPixmap(Viewer);
        ui->video_label_1->setScaledContents(true);

        carIcon = carIcon.scaled(ui->Car1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->Car1->setPixmap(carIcon);

        emit sendCar1(Viewer,senderIpAddress);
    }
    else if ( senderIpAddress == ip[1] )
    {

        int32_t degree1 = 90;
        degree1 = carInfo.degree;
        int32_t degree2 = degree1 - 75;


        QPoint center(wheel.width() / 2, wheel.height() / 2);

        QImage rotatedImage = rotateImage(wheel, degree2, center);

        QPixmap overlay = QPixmap::fromImage(rotatedImage);

        int pointx = 105;
        int pointy = 185;

        int centerX = rotatedImage.width() / 2;
        int centerY = rotatedImage.height() / 2;

        int arrowx = 195;
        int arrowy = 222;

        int realSpeed = carInfo.speed;

        int clusterspeed = (9*curspeed2 + realSpeed) / 10;

        curspeed2 = clusterspeed;

        QPoint arrowCenter(arrow2.width() / 2, arrow2.height() / 2);
        QImage rotateArrow = rotateImage(arrow2, clusterspeed , arrowCenter);

        int arrowcenterX = rotateArrow.width() / 2;
        int arrowcenterY = rotateArrow.height() / 2;

        QPainter painter(&Viewer);
        QPixmap overlayArrow = QPixmap::fromImage(rotateArrow);

        QString speed = QString::number(carInfo.speed);

        painter.setPen(QColorConstants::Svg::blueviolet);
        painter.setFont(QFont("Arial", 20));
        painter.drawPixmap(0,0,testpixmap);           //자동차 화면
        painter.drawPixmap(pointx - centerX,pointy - centerY,overlay);
        painter.drawPixmap(arrowx  - (rotateArrow.width() / 2) , arrowy - (rotateArrow.height() / 2 )  , overlayArrow);

        painter.drawPixmap(155,160,tacho);
        ui->video_label_2->setStyleSheet("background-color: rgba(125, 187, 50, 50);");
        ui->video_label_2->setPixmap(Viewer);
        ui->video_label_2->setScaledContents(true);

        emit sendCar2(Viewer,senderIpAddress);

        carIcon = carIcon.scaled(ui->Car2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->Car2->setPixmap(carIcon);
    }
    else if ( senderIpAddress == ip[2] )
    {

        int32_t degree1 = 90;
        degree1 = carInfo.degree;
        int32_t degree2 = degree1 - 75;


        QPoint center(wheel.width() / 2, wheel.height() / 2);

        QImage rotatedImage = rotateImage(wheel, degree2, center);

        QPixmap overlay = QPixmap::fromImage(rotatedImage);

        int pointx = 105;
        int pointy = 185;

        int centerX = rotatedImage.width() / 2;
        int centerY = rotatedImage.height() / 2;

        int arrowx = 195;
        int arrowy = 222;

        int realSpeed = carInfo.speed;

        int clusterspeed = (9*curspeed3 + realSpeed) / 10;

        curspeed3 = clusterspeed;

        QPoint arrowCenter(arrow2.width() / 2, arrow2.height() / 2);
        QImage rotateArrow = rotateImage(arrow2, clusterspeed , arrowCenter);

        int arrowcenterX = rotateArrow.width() / 2;
        int arrowcenterY = rotateArrow.height() / 2;

        QPainter painter(&Viewer);
        QPixmap overlayArrow = QPixmap::fromImage(rotateArrow);

        QString speed = QString::number(carInfo.speed);

        painter.setPen(QColorConstants::Svg::blueviolet);
        painter.setFont(QFont("Arial", 20));
        painter.drawPixmap(0,0,testpixmap);           //자동차 화면
        painter.drawPixmap(pointx - centerX,pointy - centerY,overlay);
        painter.drawPixmap(arrowx  - (rotateArrow.width() / 2) , arrowy - (rotateArrow.height() / 2 )  , overlayArrow);

        painter.drawPixmap(155,160,tacho);


        ui->video_label_3->setPixmap(Viewer);
        ui->video_label_3->setScaledContents(true);
        carIcon = carIcon.scaled(ui->Car3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->Car3->setPixmap(carIcon);

        emit sendCar3(Viewer,senderIpAddress);
    }

    else if ( senderIpAddress == ip[3] )
    {
        int32_t degree1 = 90;
        degree1 = carInfo.degree;
        int32_t degree2 = degree1 - 75;


        QPoint center(wheel.width() / 2, wheel.height() / 2);

        QImage rotatedImage = rotateImage(wheel, degree2, center);

        QPixmap overlay = QPixmap::fromImage(rotatedImage);

        int pointx = 105;
        int pointy = 185;

        int centerX = rotatedImage.width() / 2;
        int centerY = rotatedImage.height() / 2;

        int arrowx = 195;
        int arrowy = 222;

        int realSpeed = carInfo.speed;

        int clusterspeed = (9*curspeed4 + realSpeed) / 10;

        curspeed4 = clusterspeed;

        QPoint arrowCenter(arrow2.width() / 2, arrow2.height() / 2);
        QImage rotateArrow = rotateImage(arrow2, clusterspeed , arrowCenter);

        int arrowcenterX = rotateArrow.width() / 2;
        int arrowcenterY = rotateArrow.height() / 2;

        QPainter painter(&Viewer);
        QPixmap overlayArrow = QPixmap::fromImage(rotateArrow);

        QString speed = QString::number(carInfo.speed);

        painter.setPen(QColorConstants::Svg::blueviolet);
        painter.setFont(QFont("Arial", 20));
        painter.drawPixmap(0,0,testpixmap);           //자동차 화면
        painter.drawPixmap(pointx - centerX,pointy - centerY,overlay);
        painter.drawPixmap(arrowx  - (rotateArrow.width() / 2) , arrowy - (rotateArrow.height() / 2 )  , overlayArrow);

        painter.drawPixmap(155,160,tacho);
        ui->video_label_4->setPixmap(Viewer);
        ui->video_label_4->setScaledContents(true);

        busIcon = busIcon.scaled(ui->Car4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->Car4->setPixmap(busIcon);

        emit sendCar4(Viewer,senderIpAddress);
    }



}
VideoForm::~VideoForm()
{
    delete ui;
}
