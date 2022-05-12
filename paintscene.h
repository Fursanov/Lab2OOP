#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
class paintScene: public QGraphicsScene
{

    Q_OBJECT

public:
    QList<QGraphicsLineItem*> MyLines;
    QList<QGraphicsEllipseItem*> MyEllipses;
    QList<QGraphicsRectItem*> MyRects;
    QList<QGraphicsPolygonItem*> MyPolygons;
    QList<QList<QGraphicsLineItem*>> MyPolyLines;
    QList<int> i={0,0,0,0,0};
    QList<QColor> colorlist={Qt::red,Qt::green,Qt::blue,Qt::black, Qt::yellow, Qt::white};
    int x0=0;
    int y0=0;
    int x1=0;
    int y1=0;
    int wight=1;
    QColor MyColor=Qt::black;
    explicit paintScene(QObject *parent = 0);
    ~paintScene();

private:
    // Для рисования используем события мыши
    void addlines(QGraphicsSceneMouseEvent * event);
    void copyline(QGraphicsSceneMouseEvent * event);
    void checkline(QGraphicsSceneMouseEvent *event);
    void moveline(QGraphicsSceneMouseEvent *event);
    void addellipse(QGraphicsSceneMouseEvent * event);
    void copyellipse(QGraphicsSceneMouseEvent * event);
    void checkellipse(QGraphicsSceneMouseEvent *event);
    void moveellipse(QGraphicsSceneMouseEvent *event);
    void addrect(QGraphicsSceneMouseEvent * event);
    void copyrect(QGraphicsSceneMouseEvent * event);
    void checkrect(QGraphicsSceneMouseEvent *event);
    void moverect(QGraphicsSceneMouseEvent *event);
    void addpolygon(QGraphicsSceneMouseEvent * event);
    void endpolygon(QKeyEvent *event);
    void checkpolygon(QGraphicsSceneMouseEvent * event);
    void copypolygon(QGraphicsSceneMouseEvent *event);
    void movepolygon(QGraphicsSceneMouseEvent *event);
    void addpolyline(QGraphicsSceneMouseEvent * event);
    void endpolyline(QKeyEvent *event);
    void copypolyline(QGraphicsSceneMouseEvent * event);
    void checkpolyline(QGraphicsSceneMouseEvent *event);
    void movepolyline(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

};

#endif // PAINTSCENE_H
