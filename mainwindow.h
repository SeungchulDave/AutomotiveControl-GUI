#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class VideoForm;
class SettingForm;
class FocusForm;
class ControlForm;
class MessageWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionvideo_triggered();
    void on_actionsetting_triggered();
    void showFocus();
    void on_actionFocus_triggered();
    void on_actionControl_triggered();
    void focusTab();

    void activateCar1();
    void activateCar2();
    void activateCar3();
    void activateCar4();

private:
    Ui::MainWindow *ui;
    VideoForm *videoForm;
    SettingForm *settingForm;
    FocusForm *focusForm;
    ControlForm *controlForm;
    MessageWidget *messageWidget;

};
#endif // MAINWINDOW_H
