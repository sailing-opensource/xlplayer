#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QDebug>

class ClickableLabel :public QLabel
{
    Q_OBJECT
public:
    ClickableLabel(QWidget* parent = Q_NULLPTR) : QLabel(parent) {}
    ~ClickableLabel() { qDebug() << "release label" << index; }

    int index = 0;

signals:
    void clicked(int index);

private:
    void mouseReleaseEvent(QMouseEvent* ev)
    {
        if (ev != nullptr && ev->button() == Qt::LeftButton)
        {
            emit clicked(index);	//emit signal
        }
    }
    void enterEvent(QEvent*)
    {
        setCursor(QCursor(Qt::PointingHandCursor)); // change cursor
    }
    void leaveEvent(QEvent*)
    {
        setCursor(QCursor(Qt::ArrowCursor));
    }
};

#endif // CLICKABLELABEL_H
