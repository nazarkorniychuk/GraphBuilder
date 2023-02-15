#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QList>
#include "mainwindow.h"
class GraphicsScene : public QGraphicsScene
{
public:
    explicit GraphicsScene(QObject *parent = 0);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    MainWindow* parent;
    void UpdateScene();
};

#endif // GRAPHICSSCENE_H
