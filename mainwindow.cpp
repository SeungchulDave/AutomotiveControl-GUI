#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "videoform.h"
#include "focusform.h"
#include "controlform.h"
#include "settingform.h"
#include "messagewidget.h"
#include <QMdiArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ui->mdiArea->setStyleSheet("background-color: rgba(125, 187, 50, 50);");
    videoForm = new VideoForm(this);
    settingForm = new SettingForm(this);
    focusForm = new FocusForm(this);
    controlForm = new ControlForm(this);


    videoForm->setWindowTitle("Video Stream");
    settingForm->setWindowTitle("Setting");
    focusForm->setWindowTitle("Focus");
    controlForm->setWindowTitle("Control");

  //  connect(videoForm, SIGNAL(ipInfo(QString)),settingForm,SLOT(addIP(QString)));
   // connect(videoForm, SIGNAL(focusIp(QString)), focusForm, SLOT(addIP2(QString)));
   // connect(videoForm, SIGNAL(ipInfo(QString)), videoForm, SLOT(ipExpression(QString)));

    connect(focusForm, SIGNAL(car1()), this, SLOT(activateCar1()));
    connect(focusForm, SIGNAL(car2()), this, SLOT(activateCar2()));
    connect(focusForm, SIGNAL(car3()), this, SLOT(activateCar3()));
    connect(focusForm, SIGNAL(car4()), this, SLOT(activateCar4()));;

  //  connect(videoForm, SIGNAL(sendCar1(QImage,QString)), focusForm, SLOT(focusImage(QImage,QString)));
   // connect(videoForm, SIGNAL(sendCar2(QImage,QString)), focusForm, SLOT(focusImage(QImage,QString)));
  //  connect(videoForm, SIGNAL(sendCar3(QImage,QString)), focusForm, SLOT(focusImage(QImage,QString)));
  //  connect(videoForm, SIGNAL(sendCar4(QImage,QString)), focusForm, SLOT(focusImage(QImage,QString)));
    // connect(videoForm, SIGNAL(click()),  videoForm, SLOT(showTab()));


//    connect(messageWidget, SIGNAL(makeSignal()), focusForm, SLOT(makeWidget()));


    QMdiSubWindow *cw = ui->mdiArea->addSubWindow(videoForm);
    videoForm->show();
    ui->mdiArea->addSubWindow(settingForm);
    ui->mdiArea->addSubWindow(focusForm);
    ui->mdiArea->addSubWindow(controlForm);
    ui->mdiArea->setActiveSubWindow(cw);

 //   connect(videoForm->udpSocket, SIGNAL(readyRead()), focusForm, SLOT(focusServer()));
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::focusTab()
{

    qDebug() << "focused" ;
}
void MainWindow::on_actionvideo_triggered()
{
    if(videoForm != nullptr)   {
        videoForm->setFocus();
    }
}
void MainWindow::showFocus()
{
    qDebug() << "showFocus activated";
}
void MainWindow::on_actionsetting_triggered()
{
    if(settingForm != nullptr) {
        settingForm->setFocus();
    }
}

void MainWindow::on_actionFocus_triggered()
{
    if(focusForm != nullptr) {
        focusForm->setFocus();
    }
}


void MainWindow::on_actionControl_triggered()
{
    if(controlForm != nullptr) {
        controlForm->setFocus();
    }
}
void MainWindow::activateCar1()
{
   // qDebug() << "car1";
    connect(videoForm, SIGNAL(sendCar1(QPixmap,QString)), focusForm, SLOT(focusImage(QPixmap,QString)));
    disconnect(videoForm, SIGNAL(sendCar2(QPixmap,QString)), focusForm, SLOT(focusImage(QPixmap,QString)));
    disconnect(videoForm, SIGNAL(sendCar3(QPixmap,QString)), focusForm, SLOT(focusImage(QPixmap,QString)));
    disconnect(videoForm, SIGNAL(sendCar4(QPixmap,QString)), focusForm, SLOT(focusImage(QPixmap,QString)));
}
void MainWindow::activateCar2()
{
   // qDebug() << "car2";
    disconnect(videoForm, SIGNAL(sendCar1(QPixmap,QString)), focusForm, SLOT(focusImage(QPixmap,QString)));
    connect(videoForm, SIGNAL(sendCar2(QPixmap,QString)), focusForm, SLOT(focusImage(QPixmap,QString)));
    disconnect(videoForm, SIGNAL(sendCar3(QPixmap,QString)), focusForm, SLOT(focusImage(QPixmap,QString)));
    disconnect(videoForm, SIGNAL(sendCar4(QPixmap,QString)), focusForm, SLOT(focusImage(QPixmap,QString)));

}
void MainWindow::activateCar3()
{
   // qDebug() << "car3";
    disconnect(videoForm, SIGNAL(sendCar1(QPixmap,QString)), focusForm, SLOT(focusImage(QPixmap,QString)));
    disconnect(videoForm, SIGNAL(sendCar2(QPixmap,QString)), focusForm, SLOT(focusImage(QPixmap,QString)));
    connect(videoForm, SIGNAL(sendCar3(QPixmap,QString)), focusForm, SLOT(focusImage(QPixmap,QString)));
    disconnect(videoForm, SIGNAL(sendCar4(QPixmap,QString)), focusForm, SLOT(focusImage(QPixmap,QString)));

}
void MainWindow::activateCar4()
{
    qDebug() << "car4";
    disconnect(videoForm, SIGNAL(sendCar1(QPixmap,QString)), focusForm, SLOT(focusImage(QPixmap,QString)));
    disconnect(videoForm, SIGNAL(sendCar2(QPixmap,QString)), focusForm, SLOT(focusImage(QPixmap,QString)));
    disconnect(videoForm, SIGNAL(sendCar3(QPixmap,QString)), focusForm, SLOT(focusImage(QPixmap,QString)));
    connect(videoForm, SIGNAL(sendCar4(QPixmap,QString)), focusForm, SLOT(focusImage(QPixmap,QString)));
}
