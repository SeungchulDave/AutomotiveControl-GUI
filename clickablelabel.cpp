#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget *parent) : QWidget(parent) {}

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked1();

    QWidget::mousePressEvent(event);
}
