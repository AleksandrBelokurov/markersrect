#include "graphicsview.h"
#include "rectitem.h"

#include <QtGui/QMouseEvent>

GraphicsView::GraphicsView()
    : scene_(new QGraphicsScene())
{
    RectItem* rect1 = new RectItem(QRectF(0, 0, 320, 320));
    RectItem* rect2 = new RectItem(QRectF(-200, -100, 320, 320));
    scene_->addItem(rect1);
    scene_->addItem(rect2);
    setScene(scene_);
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0)
        scale(0.5, 0.5);
    else
        scale(2.0, 2.0);
}
