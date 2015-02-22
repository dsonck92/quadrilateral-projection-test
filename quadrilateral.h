#ifndef QUADRILATERAL_H
#define QUADRILATERAL_H

#include <QWidget>

class Quadrilateral : public QWidget
{
    Q_OBJECT

    QVector<QPointF> m_points;
    int m_selected;
    QPointF m_mapped,m_point;
    int m_iterations;
    bool m_showAlgorithm;

public:
    explicit Quadrilateral(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

    void sort();

    QPointF findMapped(QPainter *p=0);
    ~Quadrilateral();

public slots:
    void setIterations(int iter){m_iterations = iter;update();}
    void showAlgorithm(bool show){m_showAlgorithm = show;update();}

};

#endif // QUADRILATERAL_H
