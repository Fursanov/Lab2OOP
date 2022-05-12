#ifndef PAINT_H
#define PAINT_H

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>

#include <paintscene.h>

namespace Ui {
class Paint;
}

class Paint : public QWidget
{
    Q_OBJECT

public:
    explicit Paint(QWidget *parent = 0);
    ~Paint();

private:
    Ui::Paint *ui;
    QTimer *timer;
    paintScene *scene;
    paintScene *scene1;

private:
    void resizeEvent(QResizeEvent * event);
public:
    void change();
private slots:
    void slotTimer();
    void on_comboBox_currentIndexChanged(int index);
    void on_spinBox_valueChanged(int arg1);
    void on_comboBox_2_currentIndexChanged(int index);
    void on_comboBox_3_currentIndexChanged(int index);
    void on_comboBox_4_currentIndexChanged(int index);
    void on_comboBox_5_currentIndexChanged(int index);
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_radioButton_4_clicked();
    void on_radioButton_5_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_comboBox_6_currentIndexChanged(int index);
    void on_checkBox_2_clicked();
    void on_checkBox_3_clicked();
    void on_checkBox_clicked();
    void on_pushButton_3_clicked();
};

#endif // PAINT_H
