#ifndef CIMAGEBUTTON_H
#define CIMAGEBUTTON_H

#include <QPushButton>

// 自定义按钮
class CImageButton : public QPushButton
{
    Q_OBJECT

public:
    CImageButton(QWidget *parent);
    CImageButton(QWidget *parent, QSize fixedSize, const QString &toolTipText);
    ~CImageButton();
    void SetPixmap(QPixmap* pNormal,bool hover,QPixmap* pHover,bool normal,QPixmap* pLighted,bool light);
    void SetLighted(bool value);
public:
    void paintEvent(QPaintEvent* pEvent);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
protected:
    bool m_bLighted;
    bool m_bMouseIN;
    bool m_bLeftDown;
    QPixmap* m_pHover;
    bool m_hover = true;
    QPixmap* m_pNormal;
    bool m_normal = false;
    QPixmap* m_pLighted;
    bool m_light = false;
    QPixmap *backPix;
};

#endif // CIMAGEBUTTON_H
