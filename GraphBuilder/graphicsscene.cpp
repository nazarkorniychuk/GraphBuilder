#include "graphicsscene.h"
#include <QDebug>
GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent)
{
    this->setBackgroundBrush(Qt::gray);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    int radius = 20;

    if(this->parent->NumberOfDots <= 49){
        bool flag = true;
        for(int i = 0; i < this->parent->NumberOfDots; ++i){
            if(((this->parent->Graph[i][i]->x() - mouseEvent->scenePos().x() + radius)*(this->parent->Graph[i][i]->x() - mouseEvent->scenePos().x() + radius) + (this->parent->Graph[i][i]->y() - mouseEvent->scenePos().y() + radius)*(this->parent->Graph[i][i]->y() - mouseEvent->scenePos().y() + radius)) < (radius) * (radius)){
                qDebug() << "InDot";
                if(isClicked){
                    if(whereClicked == i){
                        this->DeleteDot(i);
                        this->isClicked = false;
                        this->whereClicked = -1;
                        qDebug() << "1";
                    }else{
                        if(this->parent->Graph[whereClicked][i] == nullptr){
                            this->parent->Graph[whereClicked][i] = this->parent->Graph[i][i];
                            this->parent->Graph[i][whereClicked] = this->parent->Graph[whereClicked][whereClicked];
                        }else{
                            this->parent->Graph[whereClicked][i] = nullptr;
                            this->parent->Graph[i][whereClicked] = nullptr;

                        }
                        this->isClicked = false;
                        this->whereClicked = -1;
                    }
                }else{
                    this->isClicked = true;
                    this->whereClicked = i;
                }
                flag = false;
                break;
            } else if(((this->parent->Graph[i][i]->x() - mouseEvent->scenePos().x() + radius)*(this->parent->Graph[i][i]->x() - mouseEvent->scenePos().x() + radius) + (this->parent->Graph[i][i]->y() - mouseEvent->scenePos().y() + radius)*(this->parent->Graph[i][i]->y() - mouseEvent->scenePos().y() + radius)) < (2*radius) * (2*radius)){
                flag = false;
                break;
            }
        }
        if(flag){
            this->parent->Graph[this->parent->NumberOfDots][this->parent->NumberOfDots] = new QPoint(mouseEvent->scenePos().x() - radius, mouseEvent->scenePos().y() - radius);
            this->parent->NumberOfDots++;
            this->isClicked = false;
            this->whereClicked = -1;
        }
    }
    this->UpdateScene();
}

void GraphicsScene::UpdateScene()
{
    int radius = 20;
    this->clear();
    for(int i = 0; i < this->parent->NumberOfDots; ++i){
        for(int j = i+1; j < this->parent->NumberOfDots; ++j){
            if(this->parent->Graph[i][j] != nullptr){
                QGraphicsLineItem* line = new QGraphicsLineItem(this->parent->Graph[i][i]->x() + radius, this->parent->Graph[i][i]->y()+ radius, this->parent->Graph[i][j]->x()+ radius, this->parent->Graph[i][j]->y()+ radius);
                this->addItem(line);
            }
        }
        QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(this->parent->Graph[i][i]->x(), this->parent->Graph[i][i]->y(), radius*2, radius*2);
        if(i==whereClicked){
            ellipse->setBrush(Qt::blue);
        }else{
            ellipse->setBrush(Qt::green);
        }
        QGraphicsTextItem *text = new QGraphicsTextItem(QString::number(i+1));
        text->setPos(this->parent->Graph[i][i]->x() + 12, this->parent->Graph[i][i]->y()+ 8);

        this->addItem(ellipse);
        this->addItem(text);

    }

}

void GraphicsScene::DeleteDot(int a)
{

    for(int i = 0; i < a; ++i){
        for(int j = a; j < this->parent->NumberOfDots; ++j){
            this->parent->Graph[i][j] = this->parent->Graph[i][j+1];
            this->parent->Graph[j][i] = this->parent->Graph[j+1][i];
        }
    }
    for(int i = a; i < this->parent->NumberOfDots; ++i){
        for(int j = a; j < this->parent->NumberOfDots; ++j){
            this->parent->Graph[i][j] = this->parent->Graph[i+1][j+1];
            this->parent->Graph[j][i] = this->parent->Graph[j+1][i+1];
        }
    }
    for(int i = 0; i < this->parent->NumberOfDots; ++i){
        this->parent->Graph[i][this->parent->NumberOfDots] = nullptr;
        this->parent->Graph[this->parent->NumberOfDots][i] = nullptr;
    }
    this->parent->NumberOfDots--;

}


