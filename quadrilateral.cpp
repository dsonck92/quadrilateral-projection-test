#include "quadrilateral.h"

#include <QPainter>
#include <QMouseEvent>
#include <math.h>

Quadrilateral::Quadrilateral(QWidget *parent) :
    QWidget(parent)
{
    int i;
    for(i = 0;i < 4;i++)
    {
        m_points << QPointF(qrand()%width(),qrand()%height());
    }

    m_selected = -1;
}

void Quadrilateral::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    int i;
    p.setPen(Qt::blue);
    for(i = 0;i < 4;i++)
    {
        p.drawEllipse(m_points[i],3,3);
        p.drawText(m_points[i],QString("%1").arg(i));
    }

    p.drawPolygon(m_points);

    p.setPen(Qt::red);
    p.drawLine(width()/2,0,width()/2,height());
    p.drawLine(0,height()/2,width(),height()/2);
    m_mapped = findMapped();
    p.setPen(Qt::green);
    p.drawLine(width()*m_mapped.x(),0,width()*m_mapped.x(),height());
    p.drawLine(0,height()*m_mapped.y(),width(),height()*m_mapped.y());
}

void Quadrilateral::mousePressEvent(QMouseEvent *ev)
{
    m_selected = -1;
    int i;
    for(i = 0;i < 4;i++)
    {
        if(sqrt(pow(ev->x()-m_points[i].x(),2)+pow(ev->y()-m_points[i].y(),2)) < 3)
            m_selected = i;
    }

}
void Quadrilateral::mouseReleaseEvent(QMouseEvent *ev)
{
    m_selected = -1;
    sort();
    update();
}
void Quadrilateral::mouseMoveEvent(QMouseEvent *ev)
{
    if(m_selected >=0)
    {
        m_points[m_selected] = ev->pos();
    }
    update();
}

void swap(QPointF &a, QPointF &b)
{
    QPointF buffer;
    buffer = a;
    a = b;
    b = buffer;
}

void Quadrilateral::sort()
{
    bool check = true;
    while(check)
    {
        check = false;
        if(m_points[0].x() > m_points[1].x())
        {
            swap(m_points[0],m_points[1]);
            check = true;
        }
        if(m_points[3].x() > m_points[2].x())
        {
            swap(m_points[2],m_points[3]);
            check = true;
        }
        if(m_points[0].y() > m_points[3].y())
        {
            swap(m_points[0],m_points[3]);
            check = true;
        }
        if(m_points[1].y() > m_points[2].y())
        {
            swap(m_points[1],m_points[2]);
            check = true;
        }
    }
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

// Returns a point on
QPointF ratioPoint(const QPointF &a, const QPointF &b, qreal ratio)
{
    return QPointF(a.x()*(1.0-ratio)+b.x()*(0.0+ratio),a.y()*(1.0-ratio)+b.y()*(0.0+ratio));
}

QPointF Quadrilateral::findMapped()
{
    QPointF point(width()/2.0,height()/2.0);

    QPointF t1, t2;
    qreal step = 1.0/2.0;
    qreal ratio = 1.0/2.0;

    QPointF result;

    while(step > 1/1024)
    {
        t1 = ratioPoint(m_points[0],m_points[1],ratio);
        t2 = ratioPoint(m_points[3],m_points[2],ratio);
        step /= 2.0;
        ratio -= step*sgn((t2.x()-t1.x())*(point.y()-t1.y())-(t2.y() - t1.y())*(point.x()-t1.x()));
    }

    result.setX(ratio);

    ratio = 1.0/2.0;
    step  = 1.0/2.0;

    while(step > 1/1024)
    {
        t1 = ratioPoint(m_points[0],m_points[3],ratio);
        t2 = ratioPoint(m_points[1],m_points[2],ratio);
        step /= 2.0;
        ratio += step*sgn((t2.x()-t1.x())*(point.y()-t1.y())-(t2.y() - t1.y())*(point.x()-t1.x()));
    }
    result.setY(ratio);

    return result;
}

Quadrilateral::~Quadrilateral()
{
}
