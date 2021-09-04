#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include<QGraphicsView>

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView();   
protected:
    void wheelEvent(QWheelEvent *event) override;
private:
    QGraphicsScene* scene_;
};

#endif // GRAPHICSVIEW_H
