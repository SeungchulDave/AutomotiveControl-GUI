 #include "focusform.h"
#include "qpainter.h"
#include "ui_focusform.h"
#include <QDebug>
#include <QPixmap>
#include "messagewidget.h"
#include  <QListWidgetItem>
#include <QListWidget>
#include <QtXml/QDomDocument>

#define MSG_MAX_SIZE 1024

enum X_FLAG { F_CON, F_DIS, F_RUN, F_ERR, F_INFO };
enum X_TYPE { T_KEEP, T_STOP, T_WAIT, T_FASTER, T_SLOW, T_ALIVE };

struct GUIData {
    char msg[MSG_MAX_SIZE];
    uint32_t type, flag;
};

FocusForm::FocusForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FocusForm)
{
    ui->setupUi(this);

    quint16 port =  9999;
    camSocket = new QUdpSocket(this);
    camSocket->bind(QHostAddress::Any, port);

    quint16 port2 =  2234;
    messageSocket = new QUdpSocket(this);
    messageSocket->bind(QHostAddress::Any, port2);

    connect(camSocket, SIGNAL(readyRead()), this, SLOT(camServer()));

    connect(messageSocket, SIGNAL(readyRead()), this, SLOT(messageServer()));


    connect(this ,SIGNAL(widgetSignal(QString, QString, QString, QString, QString, QString,QString, QString, QString, QString, QString)), this,
            SLOT( makeWidget(QString, QString, QString, QString, QString, QString, QString, QString ,QString, QString, QString)));



    if(camSocket->state() == QUdpSocket::BoundState )
    {
        qDebug() << "Connected";
        ui->connect_PushButton->setDisabled(true);
        ui->disconnect_PushButton->setDisabled(false);
    }
    else

    {
        ui->disconnect_PushButton->setDisabled(true);
        ui->connect_PushButton->setDisabled(false);
    }

    text = " ";
    popup = " ";
    stopCnt = 0;
    slowCnt = 0;
    flag = 0;


}
void FocusForm::focusImage(QPixmap focus, QString ip)
{


    QImage warning2(":/new/prefix1/resources/bblind4.png");
    QImage warning = warning2.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap blind = QPixmap::fromImage(warning);

    QPixmap Viewer(focus.width(), focus.height());
    Viewer.fill(Qt::transparent);

        QPainter painter(&Viewer);
         painter.drawPixmap(0,0,focus);

        if( text == "STOP" )
        {

        painter.setPen(Qt::red);

        stopCnt++;

        if(stopCnt % 30 == 0 || stopCnt % 30 == 1)
        {
            text = " ";
        }

        }
        else if( text == "SLOW")
        {

        painter.setPen(QColorConstants::Svg::orange);
        slowCnt++;

        if( slowCnt % 30 == 0 || slowCnt % 30 == 1 )

        {
            text = " ";
        }

       }

       painter.setFont(QFont("Arial", 20));

       painter.drawText(QPoint(125, 130),  text);

       if( popup == "513" )
       {
        flag++;
        QImage accident2(":/new/prefix1/resources/rsa_accident.png");
        QImage accident = accident2.scaled(160, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPixmap info = QPixmap::fromImage(accident);
        painter.drawPixmap(180,10, info);
        if(flag % 30 == 0 || flag % 30 == 1 || flag % 30 ==2)
        {
            popup = " ";
        }
       }

       else if ( popup == "1300" )
       {
        flag++;
        QImage porthole2(":/new/prefix1/resources/rsa_porthole.png");
        QImage porthole = porthole2.scaled(110, 110, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPixmap info = QPixmap::fromImage(porthole);
        painter.drawPixmap(195,15, info);
        if(flag % 30 == 0 || flag % 30 == 1 || flag % 30 ==2)
        {
            popup = " ";
        }
       }

       else if ( popup == "534" )
       {
        flag++;
        QImage stop2(":/new/prefix1/resources/rsa_stopcar.png");
        QImage stop = stop2.scaled(160, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPixmap info = QPixmap::fromImage(stop);
        painter.drawPixmap(180,10, info);
        if(flag % 30 == 0 || flag % 30 == 1 || flag % 30 ==2 )
        {
            popup = " ";
        }
       }
       else if ( popup == "1286" )
       {
        flag++;
        QImage blind2(":/new/prefix1/resources/rsa_pedestrian.png");
        QImage blind = blind2.scaled(160, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPixmap info = QPixmap::fromImage(blind);
        painter.drawPixmap(180,10, info);
        if(flag % 30 == 0 || flag % 30 == 1 || flag % 30 ==2 )
        {
            popup = " ";
        }
       }
       else if ( popup == "5378" )
       {
        flag++;
        QImage fog(":/new/prefix1/resources/fog.png");
        QPixmap info = QPixmap::fromImage(fog);
        painter.drawPixmap(230,10, info);
        if(flag % 30 == 0 || flag % 30 == 1 || flag % 30 ==2 )
        {
            popup = " ";
        }
       }
       else if ( popup == "1025" )
       {
        flag++;
        QImage construction2(":/new/prefix1/resources/rsa_construction.png");
             QImage construction = construction2.scaled(160, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPixmap info = QPixmap::fromImage(construction);
        painter.drawPixmap(180,10, info);
        if(flag % 30 == 0 || flag % 30 == 1 || flag % 30 ==2 )
        {
            popup = " ";
        }
       }




        ui->showLabel->setPixmap(Viewer);
        ui->showLabel->setScaledContents(true);

       rsaflag = 0;


}
void FocusForm::messageServer()
{

     rsaflag = 1;

    GUIData GUI;

    QByteArray messageData;
    QHostAddress sender;
    quint16 senderPort;

    X_FLAG flag;
    X_TYPE type;

    messageData.resize(messageSocket->pendingDatagramSize());
    messageSocket->readDatagram(messageData.data(), messageData.size(),&sender,&senderPort);

     QString senderIpAddress = sender.toString().split(":").last();

    memcpy(&GUI, messageData.data(), sizeof(GUIData));

    // qDebug() <<"Message: " << GUI.msg;
    // qDebug() << "flag: "   << GUI.flag;
   //  qDebug() << "type: "   << GUI.type;


     QString xmlString = QString::fromUtf8(GUI.msg);

     ui->textEdit->setPlainText(xmlString);

     QDomDocument doc;

     if(doc.setContent(xmlString)){
        QDomElement RoadSideAlert = doc.documentElement();

        QDomElement msgCnt1 = RoadSideAlert.firstChildElement("msgCnt");


            QString msgCnt = msgCnt1.text();
        QDomElement typeEvent1 = RoadSideAlert.firstChildElement("typeEvent");

            QString typeEvent = typeEvent1.text();
        popup = typeEvent;



        QDomElement utcTime = RoadSideAlert.firstChildElement("position").firstChildElement("utcTime");

            // year 및 month 엘리먼트의 값을 가져오기
            QDomElement yearElement = utcTime.firstChildElement("year");
            QDomElement monthElement = utcTime.firstChildElement("month");
            QDomElement dayElement = utcTime.firstChildElement("day");
            QDomElement hourElement = utcTime.firstChildElement("hour");
            QDomElement minuteElement = utcTime.firstChildElement("minute");
            QDomElement secondElement = utcTime.firstChildElement("second");

                QString year = yearElement.text();
                QString month = monthElement.text();
                QString day = dayElement.text();
                QString hour = hourElement.text();
                QString minute = minuteElement.text();
                QString second = secondElement.text();        


            QDomElement longElement = RoadSideAlert.firstChildElement("position").firstChildElement("long");
            QDomElement latElement = RoadSideAlert.firstChildElement("position").firstChildElement("lat");
            QDomElement elevationElement = RoadSideAlert.firstChildElement("position").firstChildElement("elevation");


                QString longitude = longElement.text();
                QString latitude = latElement.text();
                QString elevation = elevationElement.text();


                emit widgetSignal(msgCnt, typeEvent, year, month, day, hour, minute, second, longitude, latitude, elevation);


     }



     switch(GUI.type)
     {
     case T_KEEP:
     {
        qDebug() << "I Got a Keep Sign";


     }
     break;
     case T_STOP:
     {
         qDebug() << "I Got a Stop Sign";

         text = "STOP";
     }
     break;
     case T_WAIT:
     {
         qDebug() << "I Got a Wait Sign";
     }
     break;
     case T_FASTER:
     {
         qDebug() << "I Got a FASTER Sign";
     }
     break;
     case T_ALIVE:
     {
         qDebug() << "I Got a Alive Sign";
     }
     break;
     case T_SLOW:
     {
         qDebug() << "I Got a Slow Sign";

         text = "SLOW";
     }
     break;

     }
}
void FocusForm::camServer()
{


    QByteArray imageData;

    QHostAddress sender;
    quint16 senderPort;

    imageData.resize(camSocket->pendingDatagramSize());
    camSocket->readDatagram(imageData.data(), imageData.size(),&sender,&senderPort);

     QString senderIpAddress = sender.toString().split(":").last();

    ui->rsu_ip_lineedit->setText(senderIpAddress);

    QByteArray decodedData = QByteArray::fromBase64(imageData);
    std::vector<uchar> imageBuffer(decodedData.begin(), decodedData.end());

    cv::Mat frame =  cv::imdecode(imageBuffer, cv::IMREAD_COLOR);
    QImage camImage(frame.data, frame.cols, frame.rows, frame.channels()*frame.cols, QImage::Format_BGR888);

    QPixmap camPixmap = QPixmap::fromImage(camImage);

    ui->rsuLabel->setPixmap(camPixmap);
    ui->rsuLabel->setScaledContents(true);
}

FocusForm::~FocusForm()
{
    delete ui;
}

void FocusForm::on_car1PushButton_clicked()
{
    emit car1();

    ui->textEdit->clear();
    ui->listWidget->clear();
}
void FocusForm::on_car2PushButton_clicked()
{
    emit car2();

     ui->textEdit->clear();
       ui->listWidget->clear();

}
void FocusForm::on_ca3PushButton_clicked()
{
    emit car3();

     ui->textEdit->clear();
      ui->listWidget->clear();
}
void FocusForm::on_pushButton_4_clicked()
{
    emit car4();

     ui->textEdit->clear();
      ui->listWidget->clear();
}
void FocusForm::on_connect_PushButton_clicked()
{
    if(camSocket->state() == QUdpSocket::UnconnectedState)

    {
        quint16 port = 9999;
        camSocket->bind(QHostAddress::Any, port);
        ui->connect_PushButton->setDisabled(true);
        ui->disconnect_PushButton->setDisabled(false);
    }
}
void FocusForm::on_disconnect_PushButton_clicked()
{
    if (camSocket->state() == QUdpSocket::BoundState) {
        camSocket->close();
        ui->disconnect_PushButton->setDisabled(true);
        ui->connect_PushButton->setDisabled(false);


        QImage disconnect2(":/new/prefix1/resources/disconnect.png");
        QPixmap disconnect = QPixmap::fromImage(disconnect2);

        ui->rsuLabel->setPixmap(disconnect);
        ui->rsu_ip_lineedit->clear();

    }

}
void FocusForm::makeWidget(QString msgCnt, QString typeEvent, QString year, QString month, QString day, QString hour, QString minute, QString second, QString longitude, QString latitude, QString elevation)
{
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(QSize(380, 120));

    MessageWidget *message = new MessageWidget(msgCnt, typeEvent, year, month, day, hour, minute, second, longitude, latitude, elevation);


    ui->listWidget->insertItem(0,item);
    ui->listWidget->setItemWidget(item, message);
}

