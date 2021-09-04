#include "rectitem.h"
#include "dashrectitem.h"

#include <QGraphicsScene>

RectItem::RectItem(QRectF rect, QGraphicsItem* parent)
    : QGraphicsItem(parent),
      rect_(rect),
      markers_(new RectMarkers(rect, this))
{
    setFlag(QGraphicsItem::ItemIsSelectable);
}

QRectF RectItem::boundingRect() const
{
    return rect_;
}

void RectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(QPen(Qt::blue, 12));
    painter->fillRect(rect_, Qt::magenta);
    painter->drawRect(rect_);
    if (isSelected()) {
        if (scene() != markers_->scene())
            scene()->addItem(markers_);
    } else {
        if (scene() == markers_->scene())
            scene()->removeItem(markers_);
    }
}

void RectItem::setPos(QPointF pos)
{
    QGraphicsItem::setPos(pos);
    scene()->update();
}

void RectItem::setRect(QRectF rect)
{
    rect_ = rect;
}

void RectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    QGraphicsItem::mousePressEvent(event);
}
