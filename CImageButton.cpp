#include "CImageButton.h"
#include <QtGui>

CImageButton::CImageButton(QWidget* pParent):QPushButton(pParent),
    m_bMouseIN(false),
    m_bLeftDown(false),
    m_bLighted(false)
{
}

CImageButton::CImageButton(QWidget *pParent, QSize fixedSize, const QString &toolTipText):QPushButton(pParent),
    m_bMouseIN(false),
    m_bLeftDown(false),
    m_bLighted(false)
{
    setFixedSize(fixedSize);
    setToolTip(toolTipText);
    setFlat(true);
}

CImageButton::~CImageButton()
{
    delete backPix;
    if(m_hover){
        delete m_pHover;
    }
    if(m_normal){
        delete m_pNormal;
    }
    if(m_light){
        delete m_pLighted;
    }
}
void CImageButton::SetPixmap(QPixmap* pNormal,bool hover,QPixmap* pHover,bool normal,QPixmap* pLighted,bool light)
{
    m_hover = hover;
    m_normal = normal;
    m_light =light;
    m_pNormal=pNormal;
    m_pHover=pHover;
    m_pLighted=pLighted;
    backPix = new QPixmap(rect().width(), rect().height());
}

void CImageButton::SetLighted(bool value)
{
    if(value != m_bLighted)
    {
        m_bLighted=value;
        repaint();
    }
}

void CImageButton::paintEvent(QPaintEvent* pEvent)
{
    QPixmap* pPixmap;

    if(m_bLighted || m_bLeftDown)
        pPixmap=m_pLighted;
    else
    {
        if(m_bMouseIN) {
            pPixmap=m_pHover;
            backPix->fill(Qt::green);
        }
        else
        {
            pPixmap=m_pNormal;
            backPix->fill(Qt::transparent);
        }

    }

    QPainter painter;
    painter.begin(this);

    int p_x = rect().x();
    int p_y = rect().y();
    int p_width = rect().width();
    int p_height = rect().height();

    if(pPixmap) {
        painter.drawPixmap(rect(),*backPix); // 绘制背景
        if(m_bLighted || m_bLeftDown)
            painter.drawPixmap(QRect(p_x + 2, p_y + 2, p_width - 2, p_height - 2), *pPixmap); // 绘制偏移，动态效果
        else
            painter.drawPixmap(QRect(p_x + 1, p_y + 1, p_width - 2, p_height - 2), *pPixmap);
    }

    if(text().count() > 0)
        painter.drawText(rect(),Qt::AlignCenter,text());
    painter.end();
}

void CImageButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        m_bLeftDown=true;
        repaint();
    }
    QPushButton::mousePressEvent(e);
}

void CImageButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        m_bLeftDown=false;
        repaint();
    }
    QPushButton::mouseReleaseEvent(e);
}

void CImageButton::enterEvent(QEvent *e)
{
    m_bMouseIN=true;
    repaint();
}

void CImageButton::leaveEvent(QEvent *e)
{
    m_bMouseIN=false;
    repaint();
}
