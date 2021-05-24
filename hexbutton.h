#ifndef HEXBUTTON_H
#define HEXBUTTON_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtMath>
#include <QPoint>
#include <QPolygon>
#include <QPolygonF>
#include <QVector>
#include <QFont>
#include <QPushButton>
#include <QColor>

class hexButton:public QPushButton
{
public:
    hexButton(QWidget *parent);
    ~hexButton() {}
    void setText(QString text);
    void setColor(int r, int g, int b);
    void setColor(QColor);
    void paintEvent(QPaintEvent *event);
    QString getText();
private:
    int size = 60;
    float x = (pow(3,0.5) / 2);
    QString text;
    QColor color;
    QFont font = QFont("Arial", size*0.2);
    QVector <QPoint> hexaPoints = {
        QPoint(size / 4, 0),
        QPoint(size / 4 + size / 2, 0),
        QPoint(size, size * 0.5 * x),
        QPoint(size / 4 + size / 2, size*x),
        QPoint(size / 4, size*x),
        QPoint(0, size * 0.5 * x)
    };
    QVector <QPointF> hexaPointsF = {
        QPointF(0, size / 4),
        QPointF(0, size / 4 + size / 2),
        QPointF(size * 0.5 * x, size),
        QPointF(size * x, size / 4 + size / 2),
        QPointF(size * x, size / 4),
        QPointF(size * 0.5 * x, 0)
    };
    QPolygon hexa = QPolygon(hexaPoints);
    QPolygonF hexaF = QPolygonF(hexaPointsF);
};

#endif // HEXBUTTON_H
