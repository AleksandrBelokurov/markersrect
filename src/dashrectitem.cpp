#include "dashrectitem.h"

#include <QPainter>

DashRectItem::DashRectItem(QRectF rect, QGraphicsItem *parent)
    : QGraphicsRectItem(parent),
      rect_(rect)
{}

QRectF DashRectItem::boundingRect() const
{
    return rect_;
}

void DashRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen = QPen(Qt::gray, 2);
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
    painter->drawRect(rect_);
}

void DashRectItem::setRect(QRectF rect)
{
    rect_ = rect;
}
