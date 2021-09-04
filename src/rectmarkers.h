#ifndef RECTMARKERS_H
#define RECTMARKERS_H

#include <QGraphicsItemGroup>
#include "marker.h"
#include "dashrectitem.h"

class RectItem;

class RectMarkers : public QGraphicsItem
{
public:
    RectMarkers(QRectF rect, RectItem* parentRect, QGraphicsItem* parent = nullptr);
    QRectF boundingRect (void) const override;
    void paint (QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent * event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
private:
    QRectF rect_;
    int markerSize_ = 16;
    qreal border_ = 0.025;
    enum MakrerPos {
        TopLeft,
        TopCenter,
        TopRight,
        CenterRight,
        BottomRight,
        BottomCenter,
        BottomLeft,
        CenterLeft,
    };
    Marker* markers_[8];
    DashRectItem* dash_;
    RectItem* editableRectItem_;
    struct ResizeDirections
    {
        enum { HorzNone, Left, Right } horizontal;
        enum { VertNone, Top, Bottom } vertical;
        bool any() { return horizontal || vertical; }
    };
    ResizeDirections resizeDirections_;
    qreal horizontalDistance_;
    qreal verticalDistance_;
    void setEditDirection(QPointF pos);
    void decorateCursor();
    void placeMarkers(QRectF rect);
    QRectF calcRect(QPointF pos);
    void resizeRect(QRectF rect);
};

#endif // RECTMARKERS_H
