#ifndef MARKER_H
#define MARKER_H

#include <QGraphicsItem>
#include <QPainter>

class Marker : public QGraphicsItem
{
public:
    Marker (qreal len, QGraphicsItem *parent = nullptr);
    QRectF boundingRect (void) const override;
    void paint (QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
private:
    class MarkerImpl : public QGraphicsItem
    {
    public:
       MarkerImpl (qreal len, QGraphicsItem *parent = nullptr);
       QRectF boundingRect (void) const override;
       void paint (QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    private:
       qreal len_;
    };
    MarkerImpl impl_;
};

#endif // MARKER_H
