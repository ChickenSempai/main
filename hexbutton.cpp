#include "hexbutton.h"

#include <QPainter>
#include <QSizePolicy>
#include <QPen>
#include <QStyle>
#include <QStyleOptionButton>

hexButton::hexButton(QWidget *parent): QPushButton(parent)
{

    this->setMinimumSize(size + 10, size + 10);
//    this->text = nullptr;
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->color = QColor(241, 186, 82);
    this->setFlat(true);
    font.setWeight(500);
    font.setStyleStrategy(QFont::PreferAntialias);
}


void hexButton::setText(QString _text)
{
    this->text = _text;
    this->update();
}

void hexButton::setColor(int r, int g, int b)
{
    this->color = QColor(r,g,b);
    this->update();
}

void hexButton::setColor(QColor color)
{
    this->color = color;
    this->update();
}


void hexButton::paintEvent(QPaintEvent *)
{
    QPainter qp(this);
    QStyleOptionButton opt;
    this->initStyleOption(&opt);
    this->style()->drawControl(QStyle::CE_PushButton, &opt, &qp, this);
    qp.end();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    QPolygonF basePoly(hexaF);
    double ss = 0.98;
    basePoly.translate(QPointF(size*(1.03-ss)*0.8, size*(1.19-ss)*0.6*x));
    painter.drawPolygon(basePoly);
    auto plist = hexaPointsF;
    plist.push_back(hexaPointsF[0]);
    float s = 0.98;
    painter.translate(QPointF(size*(1.03-s)*0.8, size*(1.2-s)*0.6*x));
    painter.scale(s, s);
    painter.setPen(QPen(QColor(0, 0, 0), (size*0.016)* (1/s)));
    painter.drawPolyline(plist);
    painter.resetTransform();
//    if (text.size() != 0){
//        QPen pen_text;
//        pen_text.setBrush(QColor(0,0,0));
//        painter.setPen(pen_text);
//        painter.setFont(font);
//        painter.drawText(0, 0, size+10, size*x+20, Qt::AlignCenter, text);
//    }
    painter.end();
}

QString hexButton::getText()
{
    return text;
}
