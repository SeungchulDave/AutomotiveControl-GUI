#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QDialog>

namespace Ui {
class MessageWidget;
}

class MessageWidget : public QDialog
{
    Q_OBJECT

public:
    explicit MessageWidget(QString msgCnt, QString typeEvent,QString year, QString month, QString day,
                           QString hour, QString minute, QString second, QString longitude, QString latitude, QString elevation, QWidget *parent = nullptr);
    ~MessageWidget();
signals:
   void makeSignal();


private:
    Ui::MessageWidget *ui;
    QString msgCnt, typeEvent, year, month, day, hour, minute, second, longitude, latitude, elevation;

private slots:

};

#endif // MESSAGEWIDGET_H
