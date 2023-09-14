#ifndef CONTROLFORM_H
#define CONTROLFORM_H

#include <QWidget>
#include <QHash>
#include <QList>

class QLabel;
class QTcpServer;
class QTcpSocket;
typedef enum {
    Chat_Login,
    Chat_In,
    Chat_Talk,
    Chat_Out

} Chat_Status;
namespace Ui {
class ControlForm;
}

class ControlForm : public QWidget
{
    Q_OBJECT

public:
    explicit ControlForm(QWidget *parent = nullptr);
    ~ControlForm();

private:
    Ui::ControlForm *ui;
    QTcpServer *controlServer;
    int PORT_NUMBER = 1009;
    int BLOCK_SIZE = 1024;

    QHash<quint16, QString> clientNameHash;
    QHash<QString, QTcpSocket*> clientSocketHash;
    QHash<QString, int> clientIDHash;
private slots:
    void carConnect();
    void receiveData();
    void removeCar();


};

#endif // CONTROLFORM_H
