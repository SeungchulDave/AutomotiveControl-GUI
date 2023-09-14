#include "messagewidget.h"
#include "ui_messagewidget.h"

MessageWidget::MessageWidget(QString msgCnt, QString typeEvent,QString year, QString month, QString day,
                             QString hour, QString minute, QString second, QString longitude, QString latitude, QString elevation, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageWidget)
{
    ui->setupUi(this);
    QImage rsaImage(":/new/prefix1/resources/rsa.png");
    QPixmap icon = QPixmap::fromImage(rsaImage);
    ui->iconLabel->setPixmap(icon);
    ui->iconLabel->setScaledContents(true);

    QString leftlon = longitude.left(3);
    QString rightlon = longitude.mid(3,4);

    QString leftlat = latitude.left(1);
    QString rightlat = latitude.mid(1,4);

    qDebug() << longitude;
    qDebug() << latitude;
    ui->typeLabel->setText("RSA Alert");
    ui->countLabel->setText(msgCnt + "회");
    ui->timeLabel->setText( year + "-" + month + "-" + day  + " " + hour + ":" +minute + ":" + second);
    ui->positionLabel->setText("Longitude: " + leftlon +"."+  rightlon + "   "+  "Latitude: " + leftlat + "."+  rightlat  );
    ui->eventLabel->setText(typeEvent);


    if(typeEvent == "513")
    {
        QImage accident(":/new/prefix1/resources/accident.png");
        QPixmap info = QPixmap::fromImage(accident);
        ui->imageLabel->setPixmap(info);
        ui->imageLabel->setScaledContents(true);
    }
   else if(typeEvent == "1300")
    {
        QImage porthole(":/new/prefix1/resources/porthole.png");
        QPixmap info = QPixmap::fromImage(porthole);
        ui->imageLabel->setPixmap(info);
        ui->imageLabel->setScaledContents(true);
    }
    else if(typeEvent == "534")
    {
        QImage stop(":/new/prefix1/resources/stop.png");
        QPixmap info = QPixmap::fromImage(stop);
        ui->imageLabel->setPixmap(info);
        ui->imageLabel->setScaledContents(true);
    }
    else if(typeEvent == "1286")
    {
        QImage blind(":/new/prefix1/resources/pedestrian.png");
        QPixmap info = QPixmap::fromImage(blind);
        ui->imageLabel->setPixmap(info);
        ui->imageLabel->setScaledContents(true);
    }
    else if(typeEvent == "5378")
    {
        QImage fog(":/new/prefix1/resources/fog.png");
        QPixmap info = QPixmap::fromImage(fog);
        ui->imageLabel->setPixmap(info);
        ui->imageLabel->setScaledContents(true);
    }
    else if(typeEvent == "1025")
    {
        QImage construction(":/new/prefix1/resources/construction.png");
        QPixmap info = QPixmap::fromImage(construction);
        ui->imageLabel->setPixmap(info);
        ui->imageLabel->setScaledContents(true);
    }

}
MessageWidget::~MessageWidget()
{
    delete ui;
}
