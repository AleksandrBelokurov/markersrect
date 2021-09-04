#ifndef RECTITEM_H
#define RECTITEM_H

#include <QGraphicsItem>
#include "rectmarkers.h"

class RectItem : public QGraphicsItem
{
public:
    RectItem(QRectF rect, QGraphicsItem* parent = nullptr);
    QRectF boundingRect (void) const override;
    void paint (QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void setPos(QPointF pos);
    void setRect(QRectF rect);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    QRectF rect_;
    RectMarkers* markers_;
};

#endif // RECTITEM_H
