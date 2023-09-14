#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H
#include <focusform.h>
#include <QLabel>
#include <QMouseEvent>
#include <videoform.h>

class CustomLabel : public QLabel
{
    Q_OBJECT
class MainWindow;
public:
    explicit CustomLabel(QWidget *parent = nullptr);

signals:
    void click2();

protected:
           // Add custom functionality or override QLabel's virtual functions if needed.

   MainWindow *mainWindow;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

   private:
   // VideoForm *videoForm;

};
#endif // CUSTOMLABEL_H
