#include "controlform.h"
#include "ui_controlform.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDateTime>
#include <QMenu>
#include <QTreeWidgetItem>

ControlForm::ControlForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlForm)

{
    ui->setupUi(this);

    QImage logoImage(":/new/prefix1/resources/ways1.png");
    QPixmap logo = QPixmap::fromImage(logoImage);
    logo = logo.scaled(ui->logoLabel->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->logoLabel->setPixmap(logo);

    controlServer = new QTcpServer(this);

    connect(controlServer,SIGNAL(newConnection()), this, SLOT(carConnect()));

    if (!controlServer->listen(QHostAddress::Any, PORT_NUMBER)) {
        QMessageBox::critical(this, tr("Chatting Server"), \
                          tr("Unable to start the server: %1.") \
                                                               .arg(controlServer->errorString( )));
        close( );
        return;
    }

    qDebug() << "Start Listening..";

    ui->clientTreeWidget->setColumnWidth(0,175);

    ui->messageTreeWidget->setColumnWidth(0,100);
    ui->messageTreeWidget->setColumnWidth(1,100);
    ui->messageTreeWidget->setColumnWidth(2,100);
    ui->messageTreeWidget->setColumnWidth(3,150);
    ui->messageTreeWidget->setColumnWidth(4,150);

}
void ControlForm::carConnect()
{
    QTcpSocket *carConnection = controlServer->nextPendingConnection();
    connect(carConnection, SIGNAL(readyRead()), SLOT(receiveData()));
    connect(carConnection, SIGNAL(disconnected()), SLOT(removeCar()));

//    connect(carConnection, SIGNAL(readyRead( )), SLOT(receiveData()));
//    connect(carConnection, SIGNAL(disconnected( )), SLOT(removeClient()));
    qDebug() << "New Car is connected.";

}

void ControlForm::receiveData( )
{



    QTcpSocket *carConnection = dynamic_cast<QTcpSocket *>(sender( ));
    QByteArray bytearray = carConnection->read(BLOCK_SIZE);

    Chat_Status type;
    char data[1020];
    memset(data, 0, 1020);

    QString ip = carConnection->peerAddress().toString();
    QString senderIp = ip.split(":").last();

    quint16 port = carConnection->peerPort();
    QString name = QString::fromStdString(data);

    QDataStream in(&bytearray, QIODevice::ReadOnly);
    in.device()->seek(0);
    in >> type;
    in.readRawData(data, 1020);


    qDebug() << senderIp << " : " << type;

    switch(type) {
    case Chat_Login:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            if(item->text(0) != "-") {
                item->setText(0, "-");
            }
            clientSocketHash[name] = carConnection;
        }
        break;
    case Chat_In:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            if(item->text(0) != "O") {
                item->setIcon(0, QIcon(":/new/prefix1/resources/login.png"));
            }
            clientNameHash[port] = name;
            if(clientSocketHash.contains(name))
                clientSocketHash[name] = carConnection;
        }
        break;
    case Chat_Talk: {
        foreach(QTcpSocket *sock, clientSocketHash.values()) {
            qDebug() << sock->peerPort();
            if(clientNameHash.contains(sock->peerPort()) && port != sock->peerPort()) {
                QByteArray sendArray;
                sendArray.clear();
                QDataStream out(&sendArray, QIODevice::WriteOnly);
                out << Chat_Talk;
                sendArray.append("<font color=lightsteelblue>");
                sendArray.append(clientNameHash[port].toStdString().data());
                sendArray.append("</font> : ");
                sendArray.append(name.toStdString().data());
                sock->write(sendArray);
                qDebug() << sock->peerPort();
            }
        }

        QTreeWidgetItem* item = new QTreeWidgetItem(ui->messageTreeWidget);
        item->setText(0, senderIp);
        item->setText(1, QString::number(port));
        item->setText(2, QString::number(clientIDHash[clientNameHash[port]]));
       // item->setText(3, clientNameHash[port]);
        item->setText(3, QString(data));
        item->setText(4, QDateTime::currentDateTime().toString());
        item->setToolTip(4, QString(data));
        ui->messageTreeWidget->addTopLevelItem(item);

        for(int i = 0; i < ui->messageTreeWidget->columnCount(); i++)
            ui->messageTreeWidget->resizeColumnToContents(i);


    }
    break;
    case Chat_Out:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
            if(item->text(0) != "-") {
                item->setText(0, "-");
            }
            clientNameHash.remove(port);
        }
        break;

    }


 }
void ControlForm::removeCar()
{

}
ControlForm::~ControlForm()
{
    if(controlServer->isListening())
        controlServer->close( );
    if(controlServer->isListening())
        controlServer->close( );
    delete ui;
}
