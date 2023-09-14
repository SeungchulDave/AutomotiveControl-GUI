#ifndef SETTINGFORM_H
#define SETTINGFORM_H

#include <QWidget>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QTemporaryDir>
#include <qnetwork.h>
#include <QUdpSocket>

namespace Ui {
class SettingForm;
}

class SettingForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingForm(QWidget *parent = nullptr);
    ~SettingForm();



private slots:
    void addIP(QString);


private:
    Ui::SettingForm *ui;


};

#endif // SETTINGFORM_H
