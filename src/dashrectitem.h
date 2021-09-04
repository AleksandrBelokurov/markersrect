#ifndef DASHRECTITEM_H
#define DASHRECTITEM_H

#include <QGraphicsItem>

class DashRectItem : public QGraphicsRectItem
{
public:
    DashRectItem(QRectF rect, QGraphicsItem* parent = nullptr);
    QRectF boundingRect (void) const override;
    void paint (QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void setRect(QRectF rect);
protected:
    QRectF rect_;
};

#endif // DASHRECTITEM_H
