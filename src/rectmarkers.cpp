#include "rectmarkers.h"
#include "rectitem.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

RectMarkers::RectMarkers(QRectF rect, RectItem *rectItem, QGraphicsItem *parent)
    : QGraphicsItem(parent),
      rect_(rect)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
    editableRectItem_ = rectItem;
    dash_ = new DashRectItem(rect, this);
    for (int i = TopLeft; i <= CenterLeft; i++) {
        markers_[i] = new Marker(markerSize_, this);
    }
    placeMarkers(rect);
    setZValue(1.0);
}

QRectF RectMarkers::boundingRect() const
{
    qreal dx = rect_.width() * border_;
    if (dx < markerSize_) dx = markerSize_;
    qreal dy = rect_.height() * border_;
    if (dy < markerSize_) dy = markerSize_;
    QRectF outerRect = rect_.adjusted(-dx, -dy, dx, dy);
    return outerRect;
}

void RectMarkers::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{}

void RectMarkers::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    setEditDirection(event->pos());
    decorateCursor();
    QGraphicsItem::hoverMoveEvent(event);
}

void RectMarkers::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::ArrowCursor);
    QGraphicsItem::hoverLeaveEvent(event);
}

void RectMarkers::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QRectF rect = calcRect(event->pos());
    resizeRect(rect);
    if (!resizeDirections_.any()) {
        QGraphicsItem::mouseMoveEvent(event);
    }
    scene()->update();
}

void RectMarkers::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (!resizeDirections_.any()) {
        QGraphicsItem::mouseReleaseEvent(event);
        editableRectItem_->setPos(pos());
    } else {
        QRectF rect = calcRect(event->pos());
        resizeRect(rect);
        rect_ = rect;
        editableRectItem_->setRect(rect);
    }
}

void RectMarkers::setEditDirection(QPointF pos)
{
    qreal dx = rect_.width() * border_;
    qreal dy = rect_.height() * border_;
    QRectF innerRect = rect_.adjusted(dx, dy, -dx, -dy);

    if (pos.x() < innerRect.left()) {
        resizeDirections_.horizontal = resizeDirections_.Left;
        horizontalDistance_ = rect_.left() - pos.x();
    } else if (pos.x() > innerRect.right()) {
        resizeDirections_.horizontal = resizeDirections_.Right;
        horizontalDistance_ = rect_.right() - pos.x();
    } else {
        resizeDirections_.horizontal = resizeDirections_.HorzNone;
    }

    if (pos.y() < innerRect.top()) {
        resizeDirections_.vertical = resizeDirections_.Top;
        verticalDistance_ = rect_.top() - pos.y();
    } else if (pos.y() > innerRect.bottom()) {
        resizeDirections_.vertical = resizeDirections_.Bottom;
        verticalDistance_ = rect_.bottom() - pos.y();
    } else {
        resizeDirections_.vertical = resizeDirections_.VertNone;
    }
}

void RectMarkers::decorateCursor()
{
    if (((resizeDirections_.horizontal == resizeDirections_.Left)
            && (resizeDirections_.vertical == resizeDirections_.Top)) ||
            ((resizeDirections_.horizontal == resizeDirections_.Right)
             && (resizeDirections_.vertical == resizeDirections_.Bottom)))
        setCursor(Qt::SizeFDiagCursor);

    if (((resizeDirections_.horizontal == resizeDirections_.Right)
            && (resizeDirections_.vertical == resizeDirections_.Top)) ||
        ((resizeDirections_.horizontal == resizeDirections_.Left)
         && (resizeDirections_.vertical == resizeDirections_.Bottom)))
        setCursor(Qt::SizeBDiagCursor);

    if (!resizeDirections_.any()) {
        setCursor(Qt::SizeAllCursor);
    } else if (resizeDirections_.vertical == resizeDirections_.VertNone) {
        setCursor(Qt::SizeHorCursor);
    } else if (resizeDirections_.horizontal == resizeDirections_.HorzNone) {
        setCursor(Qt::SizeVerCursor);
    }
}

void RectMarkers::placeMarkers(QRectF rect)
{
    int x = rect.x();
    int y = rect.y();
    int width = rect.width();
    int height = rect.height();

    markers_[TopLeft]->setPos(x, y);
    markers_[TopCenter]->setPos(x + width/2, y);
    markers_[TopRight]->setPos(x + width, y);
    markers_[CenterRight]->setPos(x + width, y + height/2);
    markers_[BottomRight]->setPos(x + width, y + height);
    markers_[BottomCenter]->setPos(x + width/2, y + height);
    markers_[BottomLeft]->setPos(x, y + height);
    markers_[CenterLeft]->setPos(x, y + height/2);
}

QRectF RectMarkers::calcRect(QPointF pos)
{
    qreal left = rect_.left();
    qreal top = rect_.top();
    qreal right = left + rect_.width();
    qreal bottom = top + rect_.height();
    qreal min = markerSize_ * 2;

    if (resizeDirections_.horizontal == resizeDirections_.Left) {
        left = pos.x() + horizontalDistance_;
        if (left > (right - min)) left = (right - min);
    } else if (resizeDirections_.horizontal == resizeDirections_.Right) {
        right = pos.x() + horizontalDistance_;
        if (right < (left + min)) right = (left + min);
    }

    if (resizeDirections_.vertical == resizeDirections_.Top) {
        top = pos.y() + verticalDistance_;
        if (top > (bottom - min)) top = (bottom - min);
    } else if (resizeDirections_.vertical == resizeDirections_.Bottom) {
        bottom = pos.y() + verticalDistance_;
    }

    qreal width = right-left;
    qreal height = bottom-top;
    if (width < min) width = min;
    if (height < min) height = min;

    return QRectF(left, top, width, height);
}

void RectMarkers::resizeRect(QRectF rect)
{
    prepareGeometryChange();
    dash_->setRect(rect);
    placeMarkers(rect);
}
