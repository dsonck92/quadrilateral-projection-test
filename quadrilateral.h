#ifndef QUADRILATERAL_H
#define QUADRILATERAL_H

#include <QWidget>

class Quadrilateral : public QWidget
{
    Q_OBJECT

    QVector<QPointF> m_points;
    int m_selected;
    QPointF m_mapped;

public:
    explicit Quadrilateral(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

    void sort();

    QPointF findMapped();
    ~Quadrilateral();

};

#endif // QUADRILATERAL_H
