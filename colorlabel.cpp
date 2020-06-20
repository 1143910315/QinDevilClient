#include "colorlabel.h"

#include <QPainter>
#include <qevent.h>

ColorLabel::ColorLabel(QWidget *parent, Qt::WindowFlags f) : QLabel(parent, f), textColor(0, 0, 0) {
}

ColorLabel::ColorLabel(const QString &text, QWidget *parent, Qt::WindowFlags f) : QLabel(text, parent, f), textColor(0, 0, 0) {
}

void ColorLabel::paintEvent(QPaintEvent *event) {
    (void)event;
    //QLabel::paintEvent(event);
    QPainter painter(this);
    QRectF rectangle = QRectF(0, 0, this->width(), this->height());
    int total = colors.count();
    if(total > 0) {
        painter.setPen(Qt::NoPen);
        QRectF localRectF = QRectF();
        qreal height = rectangle.height() / total;
        localRectF.setX(rectangle.x());
        localRectF.setRight(rectangle.right());
        for(int i = 0 ; i < total; ++i) {
            localRectF.setY(rectangle.y() + i * height);
            localRectF.setHeight(height);
            painter.setBrush(QBrush(colors[i]));
            painter.drawRect(localRectF);
        }
    }
    painter.setPen(QPen(textColor));
    //qDebug("%d %d %d %d", (int)rectangle.x(), (int)rectangle.y(), (int)rectangle.width(), (int)rectangle.height());
    painter.drawText(rectangle, Qt::AlignVCenter, this->text());
}

void ColorLabel::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        leftClick = true;
        if(rightClick == true) {
            cancel = true;
        }
    } else if(event->button() == Qt::RightButton) {
        rightClick = true;
        if(leftClick == true) {
            cancel = true;
        }
    }
}

void ColorLabel::mouseReleaseEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        leftClick = false;
        if(cancel) {
            if(rightClick) {
                emit multipleChecked(false);
                //qDebug("emit multipleChecked(false);");
            }
        } else {
            emit singleChecked();
            //qDebug("emit singleChecked();");
        }
    } else if(event->button() == Qt::RightButton) {
        rightClick = false;
        if(cancel) {
            if(leftClick) {
                emit multipleChecked(false);
                //qDebug("emit multipleChecked(false);");
            }
        } else {
            emit multipleChecked(true);
            //qDebug("emit multipleChecked(true);");
        }
    }
    if(leftClick == false && rightClick == false) {
        cancel = false;
    }
}
