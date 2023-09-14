#include "customlabel.h"
CustomLabel::CustomLabel(QWidget *parent) : QLabel(parent)
{


   // videoForm = new VideoForm(this);
 //   connect(this, SIGNAL(click()), mainWindow, SLOT(showFocus()));


}
void CustomLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {   emit click2();
        qDebug() << " clicked";
    }
    QLabel::mouseDoubleClickEvent(event);
}
