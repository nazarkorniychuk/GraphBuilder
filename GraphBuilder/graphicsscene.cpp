#include "graphicsscene.h"
#include <QDebug>
#include <QList>
#include <QThread>
#include <QTime>
#include <QTimer>
#include <QEventLoop>
GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent)
{
    this->setBackgroundBrush(Qt::gray);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    int radius = 20;
    qDebug() << "mouse";
    if(this->parent->NumberOfDots <= 49){
        bool flag = true;
        for(int i = 0; i < this->parent->NumberOfDots; ++i){
            if(((this->parent->Graph[i][i]->x() - mouseEvent->scenePos().x() + radius)*(this->parent->Graph[i][i]->x() - mouseEvent->scenePos().x() + radius) + (this->parent->Graph[i][i]->y() - mouseEvent->scenePos().y() + radius)*(this->parent->Graph[i][i]->y() - mouseEvent->scenePos().y() + radius)) < (radius) * (radius)){
                qDebug() << "InDot";
                if(whereClickedS > -1){
                    if(whereClickedS == i){
                        this->DeleteDot(i);
                        this->whereClickedS = -1;
                        qDebug() << "1";
                    }else{
                        if(this->parent->Graph[whereClickedS][i] == nullptr){
                            this->parent->Graph[whereClickedS][i] = this->parent->Graph[i][i];
                            this->parent->Graph[i][whereClickedS] = this->parent->Graph[whereClickedS][whereClickedS];
                        }else{
                            this->parent->Graph[whereClickedS][i] = nullptr;
                            this->parent->Graph[i][whereClickedS] = nullptr;

                        }
                        this->whereClickedS = -1;
                    }
                }else{
                    this->whereClickedS = i;
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
            this->whereClickedS = -1;
        }
    }
    this->UpdateScene();
}

void GraphicsScene::UpdateScene()
{
    qDebug() << "Update";
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
        ellipse->setBrush(Qt::green);

        QGraphicsTextItem *text = new QGraphicsTextItem(QString::number(i+1));
        text->setPos(this->parent->Graph[i][i]->x() + 12, this->parent->Graph[i][i]->y()+ 8);

        this->addItem(ellipse);
        this->addItem(text);

    }
    if(this->whereClickedS > -1) {
        QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(this->parent->Graph[this->whereClickedS][this->whereClickedS]->x(), this->parent->Graph[this->whereClickedS][this->whereClickedS]->y(), radius*2, radius*2);
        ellipse->setBrush(Qt::blue);

        QGraphicsTextItem *text = new QGraphicsTextItem(QString::number(this->whereClickedS+1));
        text->setPos(this->parent->Graph[this->whereClickedS][this->whereClickedS]->x() + 12, this->parent->Graph[this->whereClickedS][this->whereClickedS]->y()+ 8);

        this->addItem(ellipse);
        this->addItem(text);
    }
    for(int i = 0; i < this->whereClicked.length(); ++i){
        QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(this->parent->Graph[this->whereClicked[i]][this->whereClicked[i]]->x(), this->parent->Graph[this->whereClicked[i]][this->whereClicked[i]]->y(), radius*2, radius*2);
        ellipse->setBrush(Qt::red);

        QGraphicsTextItem *text = new QGraphicsTextItem(QString::number(this->whereClicked[i]+1));
        text->setPos(this->parent->Graph[this->whereClicked[i]][this->whereClicked[i]]->x() + 12, this->parent->Graph[this->whereClicked[i]][this->whereClicked[i]]->y()+ 8);

        this->addItem(ellipse);
        this->addItem(text);
    }
    qDebug() << "UpdateEND";
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

void GraphicsScene::BFS()
{
    QList<int> visited;
    if(this->whereClickedS > -1){
        this->whereClicked.push_back(this->whereClickedS);
        this->whereClickedS = -1;
        visited.push_back(this->whereClicked[0]);
        while(visited.length() != this->parent->NumberOfDots){
            QList<int> t;
            for(int i = 0; i < this->whereClicked.length(); ++i){
                for(int j = 0; j < 50; ++j){
                    if(this->parent->Graph[this->whereClicked[i]][j] != nullptr){

                        bool flag = false;
                        for(int r = 0; r < visited.length(); ++r){
                            if(visited[r] == j) flag = true;
                        }
                        if(!flag){
                            t.push_back(j);
                            visited.push_back(j);
                        }
                    }
                }
            }
            this->whereClicked = t;
            for(int i = 0; i < this->whereClicked.length(); ++i){
                qDebug() << this->whereClicked[i] << " ";
            }
            this->sleep(3000);
            this->UpdateScene();

            qDebug() << "SleepEND";
        }
        this->sleep(3000);
        this->whereClicked.clear();
        this->UpdateScene();
    }
}

void GraphicsScene::sleep(int x)
{
    QTimer *t= new QTimer();
   t->setSingleShot(true);
   t->start(x);//this is the time to sleep in this case 60 seconds
   QEventLoop pause;
   connect(t, SIGNAL(timeout()), &pause, SLOT(quit()));
   pause.exec();//keeps the program responsive
}


