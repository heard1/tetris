#ifndef WIDGET_H
#define WIDGET_H
#include "tetris.h"
#include <QWidget>
#include <QPushButton>
#include <QLayout>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    virtual void paintEvent(QPaintEvent *event); //场景刷新
    virtual void timerEvent(QTimerEvent *event); //定时器事件
    virtual void keyPressEvent(QKeyEvent *event); //键盘响应
    virtual void mouseMoveEvent(QMouseEvent *event); //鼠标移动响应
    ~Widget();

public slots:
    void startGame(); //开始游戏

private:
    QPushButton *startButton; //开始游戏按钮
    Ui::Widget *ui;
    int x,y;
    int id; //计时器id
    int SIZE=10; //方块边长
    Tetris tetris;
};

#endif // WIDGET_H
