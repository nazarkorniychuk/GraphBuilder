#include "graphicsscene.h"
GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent)
{
    this->setBackgroundBrush(Qt::white);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    int radius = 20;
    if(this->parent->NumberOfDots < 49){
        bool flag = true;
        for(int i = 0; i < this->parent->NumberOfDots; ++i){
            if(((this->parent->Graph[i][i]->x() - mouseEvent->scenePos().x() + radius)*(this->parent->Graph[i][i]->x() - mouseEvent->scenePos().x() + radius) + (this->parent->Graph[i][i]->y() - mouseEvent->scenePos().y() + radius)*(this->parent->Graph[i][i]->y() - mouseEvent->scenePos().y() + radius)) < (2*radius) * (2*radius)){
                flag = false;
                break;
            }
        }
        if(flag){
            this->parent->Graph[this->parent->NumberOfDots][this->parent->NumberOfDots] = new QPoint(mouseEvent->scenePos().x() - radius, mouseEvent->scenePos().y() - radius);
            this->parent->NumberOfDots++;
            this->UpdateScene();
        }
    }
}

void GraphicsScene::UpdateScene()
{
    int radius = 20;
    this->clear();
    for(int i = 0; i < this->parent->NumberOfDots; ++i){
        QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(this->parent->Graph[i][i]->x(), this->parent->Graph[i][i]->y(), radius*2, radius*2);
        //ellipse->setBrush(Qt::black);
        QGraphicsTextItem *text = new QGraphicsTextItem(QString::number(i+1));
        text->setPos(this->parent->Graph[i][i]->x() + 12, this->parent->Graph[i][i]->y()+ 8);
        this->addItem(ellipse);
        this->addItem(text);
    }
}
