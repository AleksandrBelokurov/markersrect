#include "marker.h"

Marker::Marker(qreal len, QGraphicsItem *parent)
   : QGraphicsItem(parent), impl_(len, this)
{}

QRectF Marker::boundingRect() const
{
    return QRectF();
}

void Marker::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{}

Marker::MarkerImpl::MarkerImpl(qreal len, QGraphicsItem *parent)
   : QGraphicsItem(parent), len_(len)
{
    setFlag(QGraphicsItem::ItemIgnoresTransformations);
}

QRectF Marker::MarkerImpl::boundingRect() const
{
    return QRectF(-len_/2, -len_/2, len_, len_);
}

void Marker::MarkerImpl::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *,
                               QWidget *)
{
   painter->setPen(QPen(Qt::black, 2));
   painter->fillRect(-len_/2, -len_/2, len_, len_, Qt::green);
   painter->drawRect(-len_/2, -len_/2, len_, len_);
}
