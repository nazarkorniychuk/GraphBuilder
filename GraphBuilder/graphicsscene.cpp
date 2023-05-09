#include "graphicsscene.h"
#include <QDebug>
#include <QList>
#include <QThread>
#include <QTime>
#include <QTimer>
#include <QEventLoop>
#include <QMessageBox>
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

                if(whereClickedS > -1){
                    if(whereClickedS == i){
                        this->DeleteDot(i);
                        this->whereClickedS = -1;
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

    for(int i = 0; i < this->visited.length(); ++i){
        QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(this->parent->Graph[this->visited[i]][this->visited[i]]->x(), this->parent->Graph[this->visited[i]][this->visited[i]]->y(), radius*2, radius*2);
        ellipse->setBrush(Qt::yellow);

        QGraphicsTextItem *text = new QGraphicsTextItem(QString::number(this->visited[i]+1));
        text->setPos(this->parent->Graph[this->visited[i]][this->visited[i]]->x() + 12, this->parent->Graph[this->visited[i]][this->visited[i]]->y()+ 8);

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

    if(this->whereClickedS > -1){
        this->whereClicked.push_back(this->whereClickedS);
        this->whereClickedS = -1;
        visited.push_back(this->whereClicked[0]);
        while(visited.length() != this->parent->NumberOfDots){
            int Len = visited.length();
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
            if(Len == visited.length()){
                break;
            }
            this->sleep(3000);
            this->UpdateScene();
        }
        this->sleep(3000);
        this->whereClicked.clear();
        this->UpdateScene();
    }
    if(visited.length() == this->parent->NumberOfDots){
        QMessageBox::about(this->parent, "Чи звязний граф?", "Граф - звязний");
    }else{
        QMessageBox::about(this->parent, "Чи звязний граф?", "Граф - не звязний");
    }
    this->visited.clear();
}

void GraphicsScene::DFS()
{
    if(this->whereClickedS > -1){
        this->whereClicked.push_back(this->whereClickedS);
        this->whereClickedS = -1;
        this->visited.push_back(this->whereClicked[0]);
        QList<int> QuequVisited;
        QuequVisited.push_back(this->whereClicked[0]);
        while(this->visited.length() != this->parent->NumberOfDots){
            bool Step = false;
            for(int i = 0; i < 50; ++i){
                Step = false;
                for(int j = 0; j < this->visited.length(); ++j){
                    if((i != this->visited[j]) && (this->parent->Graph[this->whereClicked[0]][i] != nullptr) && (this->whereClicked[0] != i)){
                        Step = true;
                    }else if(i == this->visited[j]){
                        Step = false;
                        break;
                    }
                }
                if(Step){
                    this->whereClicked[0] = i;
                    visited.push_back(this->whereClicked[0]);
                    QuequVisited.push_back(this->whereClicked[0]);
                    break;
                }
            }
            if(!Step){
                qDebug() << "!STEP" << this->whereClicked[0];

                if(QuequVisited.length() > 1){
                    this->whereClicked[0] = QuequVisited[QuequVisited.length() - 2];
                    QuequVisited.pop_back();
                }else{
                    break;
                }
                for(int t = 0; t < QuequVisited.length(); ++t){
                    qDebug() << "Visited" << QuequVisited[t];
                }

            }



            this->sleep(500);
            this->UpdateScene();
        }
        this->sleep(500);
        this->whereClicked.clear();
        this->UpdateScene();
    }
    if(visited.length() == this->parent->NumberOfDots){
        QMessageBox::about(this->parent, "Чи звязний граф?", "Граф - звязний");
    }else{
        QMessageBox::about(this->parent, "Чи звязний граф?", "Граф - не звязний");
    }
    this->visited.clear();
}

void GraphicsScene::eulerianPath()
{
    QList<int> QuequVisited;
    QList<int> Path;
    QList<int> Path1;
    int t = 0;
    int current = this->whereClickedS;
    int NumOfE = 0;
    for(int i = 0; i < this->parent->NumberOfDots; i++){
        for(int j = 0; j < this->parent->NumberOfDots; j++){
            if((this->parent->Graph[i][j] != nullptr) && (i != j)){
                NumOfE++;
            }
        }
    }
    NumOfE = NumOfE/2;
    //QuequVisited.push_back(current);
    Path.push_back(current);
    this->whereClicked.clear();
    this->whereClicked.push_back(this->whereClickedS);
    this->whereClickedS = -1;
    //this->visited.clear();
    //this->visited.push_back(this->whereClicked[0]);
    if(this->hasEulerianPath()){
        while(true){
            bool Step = false;
            for(int i = 0; i < 50; ++i){
                if(QuequVisited.length() == 0){
                    if((this->parent->Graph[this->whereClicked[0]][i] != nullptr) && (this->whereClicked[0] != i)){
                        Step = true;
                    }
                }
                for(int j = 0; j < QuequVisited.length()/2; ++j){
                    if((!(((i == QuequVisited[2*j]) && ( this->whereClicked[0] == QuequVisited[2*j+1])) || ((i == QuequVisited[2*j + 1]) && ( this->whereClicked[0] == QuequVisited[2*j])))) && (this->parent->Graph[this->whereClicked[0]][i] != nullptr) && (this->whereClicked[0] != i)){
                    Step = true;
                }
                    else if(((i == QuequVisited[2*j]) && ( this->whereClicked[0] == QuequVisited[2*j+1])) || ((i == QuequVisited[2*j + 1]) && ( this->whereClicked[0] == QuequVisited[2*j]))){
                        Step = false;
                        break;
                    }
                }
                if(Step){
                    t = 0;
                    QuequVisited.push_back(this->whereClicked[0]);
                    QuequVisited.push_back(i);
                    this->whereClicked[0] = i;
                    Path.push_back(this->whereClicked[0]);
                    break;
                }
            }

            if(!Step){
                    if(t == 0){
                        for(int i = 0; i < Path1.length(); ++i){
                            Path.push_back(Path1[i]);
                        }
                        Path1.clear();
                        for(int i = Path.length()-1; i >= 0; i--){
                            Path1.push_back(Path[i]);
                        }
                        Path.clear();
                        t++;
                        this->whereClicked[0] = Path1.first();
                        Path.push_back(Path1.first());
                        Path1.pop_front();

                    }
                    else{
                        this->whereClicked[0] = Path1.first();
                        Path.push_back(Path1.first());
                        Path1.pop_front();
                    }
            }

            this->sleep(500);
            this->UpdateScene();
            for(int t = 0; t < Path.length(); ++t){
                qDebug() << "Path" << Path[t];
                }
            qDebug() << "PathF";
            if((QuequVisited.length()/2 == NumOfE) && (Path1.length() == 0)){
                break;
            }
        }
        for(int i = 0; i < Path.length(); i++){
            this->whereClicked[0] = Path[i];
            this->visited.push_back(Path[i]);
            this->sleep(500);
            this->UpdateScene();
        }
        QMessageBox::about(this->parent, "Чи існує ейлерів шлях?", "Ейлерів існує");
    }
    else{
        QMessageBox::about(this->parent, "Чи існує ейлерів шлях?", "Ейлерового шляху не існує");
    }
    this->whereClicked.clear();
    this->visited.clear();
}

bool GraphicsScene::hasEulerianPath()
{
    int k = 0;
    for(int i = 0; i < this->parent->NumberOfDots; i++){
        for(int j = 0; j < this->parent->NumberOfDots; j++){
            if((this->parent->Graph[i][j] != nullptr) && (i != j)){
                k++;
            }
        }
        if(k == 0){
            return 0;
        }
        k = 0;
    }
    int oddDegreeCount = 0;
        for (int i = 0; i < this->parent->NumberOfDots; i++) {
            int degree = 0;
            for (int j = 0; j < this->parent->NumberOfDots; j++) {
                degree += int(this->parent->Graph[i][j] != nullptr);
            }

            if ((degree-1) % 2 != 0) {
                oddDegreeCount++;
            }
        }
        return (oddDegreeCount == 0) || (oddDegreeCount == 2);
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


