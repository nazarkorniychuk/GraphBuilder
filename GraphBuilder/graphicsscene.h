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
    QList<int> visited;
    void DeleteDot(int a);
    QList<int> whereClicked;
    int whereClickedS = -1;
    void BFS();
    void DFS();
    void eulerianPath();
    bool hasEulerianPath();
    void sleep(int x);
};

#endif // GRAPHICSSCENE_H
