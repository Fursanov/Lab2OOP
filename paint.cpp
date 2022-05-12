#include "paint.h"
#include "ui_paint.h"
#include <cmath>
#include <QGraphicsItem>

Paint *temppaint;
paintScene *tempscene;
QList<QComboBox*> tempbox;

bool enddraw=false;
bool transformcheck=false;
bool copycheck=false;
bool movecheck=false;

QList<QRadioButton*> radiobox;



Paint::Paint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Paint)
{
    ui->setupUi(this);
    temppaint=this;
    scene = new paintScene(this);       // Инициализируем графическую сцену

    tempscene=scene;

    tempbox={ui->comboBox,ui->comboBox_2,ui->comboBox_3,ui->comboBox_4,ui->comboBox_5};

    tempbox[1]->setVisible(false);
    tempbox[2]->setVisible(false);
    tempbox[3]->setVisible(false);
    tempbox[4]->setVisible(false);
    radiobox={ui->radioButton,ui->radioButton_2,ui->radioButton_3,ui->radioButton_4,ui->radioButton_5};

    ui->comboBox_6->addItems({"red","green","blue","black","yellow","white"});
    ui->graphicsView->setScene(scene);
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Paint::slotTimer);
    timer->start(100);
}

Paint::~Paint()
{
    delete ui;
}

void Paint::slotTimer()
{
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(radiobox[0]->isChecked()==true&&movecheck==false)
        if(copycheck==false)
            tempscene->addlines(event);
        else
            tempscene->copyline(event);
    if(radiobox[1]->isChecked()==true&&movecheck==false)
        if(copycheck==false)
            tempscene->addellipse(event);
        else
            tempscene->copyellipse(event);
    if(radiobox[2]->isChecked()==true&&movecheck==false)
        if(copycheck==false)
            tempscene->addrect(event);
        else
            tempscene->copyrect(event);
    if(radiobox[3]->isChecked()==true&&movecheck==false)
        if(copycheck==false)
            tempscene->addpolygon(event);
        else
            tempscene->copypolygon(event);
    if(radiobox[4]->isChecked()==true)
        if(copycheck==false&&movecheck==false)
            tempscene->addpolyline(event);
        else
            tempscene->copypolyline(event);
}

void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(radiobox[0]->isChecked()==true)
        if(copycheck==false&&movecheck==false)
            tempscene->checkline(event);
        else
            tempscene->moveline(event);
    if(radiobox[1]->isChecked()==true)
        if(copycheck==false&&movecheck==false)
            tempscene->checkellipse(event);
        else
            tempscene->moveellipse(event);
    if(radiobox[2]->isChecked()==true)
        if(copycheck==false&&movecheck==false)
            tempscene->checkrect(event);
        else
            tempscene->moverect(event);
    if(radiobox[3]->isChecked()==true)
        if(copycheck==false&&movecheck==false)
            tempscene->checkpolygon(event);
        else
            tempscene->movepolygon(event);
    if(radiobox[4]->isChecked()==true)
        if(copycheck==false&&movecheck==false)
            tempscene->checkpolyline(event);
        else
            tempscene->movepolyline(event);
}

void paintScene::keyPressEvent(QKeyEvent *event)
{
    if(radiobox[3]->isChecked()==true)
        tempscene->endpolygon(event);
    if(radiobox[4]->isChecked()==true)
        tempscene->endpolyline(event);
}


void paintScene::addlines(QGraphicsSceneMouseEvent *event)
{
    x0=event->scenePos().x()-round(wight/2);
    y0=event->scenePos().y()-round(wight/2);
    if(transformcheck==false)
    {
        MyLines.append(tempscene->addLine(QLineF(x0,y0,x0,y0),QPen(MyColor,wight)));
        tempscene->i[0]=MyLines.size();
        tempbox[0]->addItem(QString("line %1").arg(tempscene->i[0]));
        tempbox[0]->setCurrentIndex(tempscene->i[0]-1);
    }
}

void paintScene::copyline(QGraphicsSceneMouseEvent *event)
{
    MyLines.append(tempscene->addLine(MyLines[tempscene->i[0]-1]->line(),QPen(MyColor,wight)));
    tempscene->i[0]=MyLines.size();
    tempbox[0]->addItem(QString("line %1").arg(tempscene->i[0]));
    tempbox[0]->setCurrentIndex(tempscene->i[0]-1);
}


void paintScene::checkline(QGraphicsSceneMouseEvent *event)
{
    x1=event->scenePos().x();
    y1=event->scenePos().y();
    if(!MyLines.empty())
    {
    MyLines[tempscene->i[0]-1]->setLine(x0,y0,x1,y1);
    }
}

void paintScene::moveline(QGraphicsSceneMouseEvent *event)
{
    x1=MyLines[tempscene->i[0]-1]->line().p2().x()-MyLines[tempscene->i[0]-1]->line().p1().x();
    y1=MyLines[tempscene->i[0]-1]->line().p2().y()-MyLines[tempscene->i[0]-1]->line().p1().y();
    MyLines[tempscene->i[0]-1]->setLine(0+event->scenePos().x(),0+event->scenePos().y(),x1+event->scenePos().x(),y1+event->scenePos().y());
}



void paintScene::addellipse(QGraphicsSceneMouseEvent *event)
{
    x0=event->scenePos().x();
    y0=event->scenePos().y();
    if(transformcheck==false)
        {
            MyEllipses.append(tempscene->addEllipse(2*(x0-round(x0/2)),2*(y0-round(y0/2)),2*(x0-x0),2*(y0-y0),QPen(Qt::NoPen),QBrush(MyColor)));
            tempscene->i[1]=MyEllipses.size();
            tempbox[1]->addItem(QString("ellipse %1").arg(tempscene->i[1]));
            tempbox[1]->setCurrentIndex(tempscene->i[1]-1);
        }
}

void paintScene::copyellipse(QGraphicsSceneMouseEvent *event)
{

    MyEllipses.append(tempscene->addEllipse(MyEllipses[tempscene->i[1]-1]->rect(),QPen(Qt::NoPen),QBrush(MyColor)));
    tempscene->i[1]=MyEllipses.size();
    tempbox[1]->addItem(QString("ellipse %1").arg(tempscene->i[1]));
    tempbox[1]->setCurrentIndex(tempscene->i[1]-1);
}

void paintScene::checkellipse(QGraphicsSceneMouseEvent *event)
{
    x1=event->scenePos().x();
    y1=event->scenePos().y();
    MyEllipses[tempscene->i[1]-1]->setRect(2*(x0-round(x1/2)),2*(y0-round(y1/2)),2*(x1-x0),2*(y1-y0));
}

void paintScene::moveellipse(QGraphicsSceneMouseEvent *event)
{
    MyEllipses[tempscene->i[1]-1]->setPos(event->scenePos().x()-MyEllipses[tempscene->i[1]-1]->rect().center().x(),event->scenePos().y()-MyEllipses[tempscene->i[1]-1]->rect().center().y());;
}


void paintScene::addrect(QGraphicsSceneMouseEvent *event)
{
    x0=event->scenePos().x();
    y0=event->scenePos().y();
    if(transformcheck==false)
        {
            MyRects.append(tempscene->addRect(2*(x0-round(x0/2)),2*(y0-round(y0/2)),2*(x0-x0),2*(y0-y0),QPen(Qt::NoPen),QBrush(MyColor)));
            tempscene->i[2]=MyRects.size();
            tempbox[2]->addItem(QString("rectangle %1").arg(tempscene->i[2]));
            tempbox[2]->setCurrentIndex(tempscene->i[2]-1);
        }
}

void paintScene::copyrect(QGraphicsSceneMouseEvent *event)
{
    MyRects.append(tempscene->addRect(MyRects[tempscene->i[2]-1]->rect(),QPen(Qt::NoPen),QBrush(MyColor)));
    tempscene->i[2]=MyRects.size();
    tempbox[2]->addItem(QString("rectangle %1").arg(tempscene->i[2]));
    tempbox[2]->setCurrentIndex(tempscene->i[2]-1);
}

void paintScene::checkrect(QGraphicsSceneMouseEvent *event)
{
    x1=event->scenePos().x();
    y1=event->scenePos().y();
    MyRects[tempscene->i[2]-1]->setRect(2*(x0-round(x1/2)),2*(y0-round(y1/2)),2*(x1-x0),2*(y1-y0));
}

void paintScene::moverect(QGraphicsSceneMouseEvent *event)
{
    MyRects[tempscene->i[2]-1]->setPos(event->scenePos().x()-MyRects[tempscene->i[2]-1]->rect().center().x(),event->scenePos().y()-MyRects[tempscene->i[2]-1]->rect().center().y());;
}

QList<QPolygon> poly;

void paintScene::addpolygon(QGraphicsSceneMouseEvent *event)
{
    x0=event->scenePos().x();
    y0=event->scenePos().y();
    if(enddraw==false&&transformcheck==false)
    {
        tempscene->i[3]++;
        tempbox[3]->addItem(QString("polygon %1").arg(tempscene->i[3]));
        tempbox[3]->setCurrentIndex(tempscene->i[3]-1);
        enddraw=true;
        poly.append(QPolygon());
        poly[tempscene->i[3]-1]<<QPoint(x0,y0);
        MyPolygons.append(tempscene->addPolygon(poly[tempscene->i[3]-1],QPen(MyColor,wight)));
    }
    else
    {
        poly[tempscene->i[3]-1]<<QPoint(x0,y0);
        MyPolygons[tempscene->i[3]-1]->setPolygon(poly[tempscene->i[3]-1]);
    }
}

void paintScene::endpolygon(QKeyEvent *event)
{
    int key=event->key();
    if(key==Qt::Key_Return&&enddraw==true)
    {
        enddraw=false;
    }
}

void paintScene::copypolygon(QGraphicsSceneMouseEvent *event)
{

    tempscene->i[3]++;
    tempbox[3]->addItem(QString("polygon %1").arg(tempscene->i[3]));
    tempbox[3]->setCurrentIndex(tempscene->i[3]-1);
    poly.append(poly[tempscene->i[3]-2]);
    MyPolygons.append(tempscene->addPolygon(poly[tempscene->i[3]-1],QPen(MyColor,wight)));
}

void paintScene::checkpolygon(QGraphicsSceneMouseEvent *event)
{
    x1=event->scenePos().x();
    y1=event->scenePos().y();
    poly[tempscene->i[3]-1].setPoint(poly[tempscene->i[3]-1].count()-1,x1,y1);
    MyPolygons[tempscene->i[3]-1]->setPolygon(poly[tempscene->i[3]-1]);
}

void paintScene::movepolygon(QGraphicsSceneMouseEvent *event)
{
    MyPolygons[tempscene->i[3]-1]->setPos(event->scenePos().x(),event->scenePos().y());
}

void paintScene::addpolyline(QGraphicsSceneMouseEvent *event)
{
    x0=event->scenePos().x();
    y0=event->scenePos().y();
    if(enddraw==false&&transformcheck==false)
        {
            tempscene->i[4]++;
            tempbox[4]->addItem(QString("polline %1").arg(tempscene->i[4]));
            tempbox[4]->setCurrentIndex(tempscene->i[4]-1);
            enddraw=true;
            MyPolyLines.append(QList<QGraphicsLineItem*>());
            MyPolyLines[tempscene->i[4]-1].append(tempscene->addLine(QLineF(x0,y0,x0,y0),QPen(MyColor,wight)));
        }
        else
        {
            x0=MyPolyLines[tempscene->i[4]-1][MyPolyLines[tempscene->i[4]-1].count()-1]->line().p2().x();
            y0=MyPolyLines[tempscene->i[4]-1][MyPolyLines[tempscene->i[4]-1].count()-1]->line().p2().y();
            MyPolyLines[tempscene->i[4]-1].append(tempscene->addLine(QLineF(x0,y0,x0,y0),QPen(MyColor,wight)));
        }
}

QList<QLineF> temppLine;

void paintScene::copypolyline(QGraphicsSceneMouseEvent *event)
{
    if(movecheck==false)
    {
        tempscene->i[4]++;
        tempbox[4]->addItem(QString("polline %1").arg(tempscene->i[4]));
        tempbox[4]->setCurrentIndex(tempscene->i[4]-1);
        MyPolyLines.append(QList<QGraphicsLineItem*>());
        for(int j=0;j<MyPolyLines[tempscene->i[4]-2].count();j++)
        {
        temppLine.append(MyPolyLines[tempscene->i[4]-2][j]->line());
        MyPolyLines[tempscene->i[4]-1].append(tempscene->addLine(MyPolyLines[tempscene->i[4]-2][j]->line(),QPen(MyColor,wight)));
        }
    }
    else
        for(int j=0;j<MyPolyLines[tempscene->i[4]-1].count();j++)
        {
        temppLine.append(MyPolyLines[tempscene->i[4]-1][j]->line());
        }

}

void paintScene::endpolyline(QKeyEvent *event)
{
    int key=event->key();
    if(key==Qt::Key_Return&&enddraw==true)
    {
        enddraw=false;
    }
}

void paintScene::checkpolyline(QGraphicsSceneMouseEvent *event)
{
    if(!MyPolyLines.empty())
       {
       MyPolyLines[tempscene->i[4]-1][MyPolyLines[tempscene->i[4]-1].count()-1]->setLine(x0,y0,event->scenePos().x(),event->scenePos().y());
       }
}

void paintScene::movepolyline(QGraphicsSceneMouseEvent *event)
{
   for(int j=0;j<MyPolyLines[tempscene->i[4]-1].count();j++)
   {
       MyPolyLines[tempscene->i[4]-1][j]->setLine(temppLine[j].p1().x()+event->scenePos().x(),temppLine[j].p1().y()+event->scenePos().y(),temppLine[j].p2().x()+event->scenePos().x(),temppLine[j].p2().y()+event->scenePos().y());
   }
}

void Paint::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}

void Paint::on_spinBox_valueChanged(int arg1)
{
    tempscene->wight=arg1;
}

void Paint::on_comboBox_currentIndexChanged(int index)
{
    tempscene->i[0]=index+1;
}

void Paint::on_comboBox_2_currentIndexChanged(int index)
{
    tempscene->i[1]=index+1;
}

void Paint::on_comboBox_3_currentIndexChanged(int index)
{
    tempscene->i[2]=index+1;
}

void Paint::on_comboBox_4_currentIndexChanged(int index)
{
    tempscene->i[3]=index+1;
}

void Paint::on_comboBox_5_currentIndexChanged(int index)
{
    tempscene->i[4]=index+1;
}

void Paint::on_radioButton_clicked()
{
    tempbox[0]->setVisible(true);
    tempbox[1]->setVisible(false);
    tempbox[2]->setVisible(false);
    tempbox[3]->setVisible(false);
    tempbox[4]->setVisible(false);
}

void Paint::on_radioButton_2_clicked()
{
    tempbox[0]->setVisible(false);
    tempbox[1]->setVisible(true);
    tempbox[2]->setVisible(false);
    tempbox[3]->setVisible(false);
    tempbox[4]->setVisible(false);
}

void Paint::on_radioButton_3_clicked()
{
    tempbox[0]->setVisible(false);
    tempbox[1]->setVisible(false);
    tempbox[2]->setVisible(true);
    tempbox[3]->setVisible(false);
    tempbox[4]->setVisible(false);
}

void Paint::on_radioButton_4_clicked()
{
    tempbox[0]->setVisible(false);
    tempbox[1]->setVisible(false);
    tempbox[2]->setVisible(false);
    tempbox[3]->setVisible(true);
    tempbox[4]->setVisible(false);
}

void Paint::on_radioButton_5_clicked()
{
    tempbox[0]->setVisible(false);
    tempbox[1]->setVisible(false);
    tempbox[2]->setVisible(false);
    tempbox[3]->setVisible(false);
    tempbox[4]->setVisible(true);
}

void Paint::on_pushButton_clicked()
{
    for(int j=1;j<=tempscene->MyLines.count();j++)
    {
        delete tempscene->MyLines[j-1];
    }
    for(int j=1;j<=tempscene->MyEllipses.count();j++)
    {
        delete tempscene->MyEllipses[j-1];
    }
    for(int j=1;j<=tempscene->MyRects.count();j++)
    {
        delete tempscene->MyRects[j-1];
    }
    for(int j=1;j<=tempscene->MyPolygons.count();j++)
    {
        delete tempscene->MyPolygons[j-1];
    }
    for(int j=1;j<=tempscene->MyPolyLines.count();j++)
    {
        for(int k=0;k<=tempscene->MyPolyLines[j-1].count()-1;k++)
        {
            delete tempscene->MyPolyLines[j-1][k];
        }
        tempscene->MyPolyLines[j-1].clear();
    }
    tempscene->MyLines.clear();
    tempscene->MyEllipses.clear();
    tempscene->MyRects.clear();
    tempscene->MyPolygons.clear();
    poly.clear();
    tempscene->i={0,0,0,0,0};
    tempbox[0]->clear();
    tempbox[1]->clear();
    tempbox[2]->clear();
    tempbox[3]->clear();
    tempbox[4]->clear();
}

void Paint::on_pushButton_2_clicked()
{
    if(radiobox[0]->isChecked()==true)
        if(tempscene->MyLines.isEmpty()==false)
        {
            tempbox[0]->removeItem(tempscene->MyLines.count()-1);
            QGraphicsLineItem *tempq=tempscene->MyLines[tempscene->MyLines.count()-1];
            tempscene->MyLines.removeOne(tempscene->MyLines[tempscene->MyLines.count()-1]);
            delete tempq;
        }
    if(radiobox[1]->isChecked()==true)
        if(tempscene->MyEllipses.isEmpty()==false)
        {
            tempbox[1]->removeItem(tempscene->MyEllipses.count()-1);
            QGraphicsEllipseItem *tempq=tempscene->MyEllipses[tempscene->MyEllipses.count()-1];
            tempscene->MyEllipses.removeOne(tempscene->MyEllipses[tempscene->MyEllipses.count()-1]);
            delete tempq;
        }
    if(radiobox[2]->isChecked()==true)
        if(tempscene->MyRects.isEmpty()==false)
        {
            tempbox[2]->removeItem(tempscene->MyRects.count()-1);
            QGraphicsRectItem *tempq=tempscene->MyRects[tempscene->MyRects.count()-1];
            tempscene->MyRects.removeOne(tempscene->MyRects[tempscene->MyRects.count()-1]);
            delete tempq;
        }
    if(radiobox[3]->isChecked()==true)
        if(tempscene->MyPolygons.isEmpty()==false)
        {
            tempbox[3]->removeItem(tempscene->MyPolygons.count()-1);
            QGraphicsPolygonItem *tempq=tempscene->MyPolygons[tempscene->MyPolygons.count()-1];
            tempscene->MyPolygons.removeOne(tempscene->MyPolygons[tempscene->MyPolygons.count()-1]);
            delete tempq;
            poly.clear();
        }
    if(radiobox[3]->isChecked()==true)
        if(tempscene->MyPolygons.isEmpty()==false)
        {
            tempbox[3]->removeItem(tempscene->MyPolyLines.count()-1);
            for(int k=0;k<=tempscene->MyPolyLines[tempscene->MyPolyLines.count()-1].count()-1;k++)
            {
                delete tempscene->MyPolyLines[tempscene->MyPolyLines.count()-1][k];
            }
            tempscene->MyPolyLines[tempscene->MyPolyLines.count()-1].clear();
        }
}

void Paint::on_comboBox_6_currentIndexChanged(int index)
{
    tempscene->MyColor=tempscene->colorlist[index];
}

void Paint::on_checkBox_2_clicked()
{
    if(copycheck)
        copycheck=false;
    else
    {
    copycheck=true;
    movecheck=false;
    transformcheck=false;
    temppaint->ui->checkBox->setChecked(false);
    temppaint->ui->checkBox_3->setChecked(false);
    }
}

void Paint::on_checkBox_3_clicked()
{
    if(movecheck)
        movecheck=false;
    else
    {
    movecheck=true;
    copycheck=false;
    transformcheck=false;
    temppaint->ui->checkBox->setChecked(false);
    temppaint->ui->checkBox_2->setChecked(false);
    }
}

void Paint::on_checkBox_clicked()
{
    if(transformcheck)
        transformcheck=false;
    else
    {
    transformcheck=true;
    copycheck=false;
    movecheck=false;
    temppaint->ui->checkBox_2->setChecked(false);
    temppaint->ui->checkBox_3->setChecked(false);
    }
}

void Paint::on_pushButton_3_clicked()
{
    QImage image(scene->width(), scene->height(), QImage::Format_ARGB32_Premultiplied);
    image.fill(NULL);
    QPainter painter(&image);
    scene->render(&painter);
    image.save("/home/kapustka/check/mypicture.png");
}
