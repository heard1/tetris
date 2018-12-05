#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <time.h>
#include <QKeyEvent>
#include <QMouseEvent>
#include <vector>
#include <iostream>
#include <cmath>
#include <QPixmap>

using namespace std;
int flag=-1;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    id = startTimer(100); //建立一个间隔100ms的计时器
    this->setWindowTitle("Tetris for you"); //设置窗体标题
    this->setStyleSheet("background-color:#111"); //设置背景色
    this->startButton = new QPushButton(this); //创建开始游戏按钮
    this->startButton->setFocusPolicy(Qt::NoFocus); //关闭按钮焦点
    this->startButton->setGeometry(QRect(90,280,(117.0/288)*this->width(),(71.0/512)*this->height())); //设置按钮大小
    this->startButton->setStyleSheet("QPushButton{border-image:url(://image/start.png);}" //设置按钮背景图和响应区域
                                "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
    connect(this->startButton,SIGNAL(clicked()),this,SLOT(startGame())); //点击按钮，游戏开始

}
typedef struct Rec{
    int ox,oy;
    int lx,ly;
}rec;

void Widget::startGame(){
    //cout<<id<<endl;
    killTimer(id); //移除定时器
    //begin=1;
    tetris.show(); //转入俄罗斯方块界面
    tetris.InitGame();
    this->hide(); //隐藏界面

}

vector<rec> obj;

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(flag==-1){
        //cout<<event->x()<<" "<<event->y()<<endl;
        x=event->x()-5;
        y=event->y()-5;
    }
}

void Widget::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==id){
        rec tem;
        tem.lx=10; //设置长和宽为10
        tem.ly=10;
        tem.ox=(rand()%60)*SIZE; //方块位置随机生成
        tem.oy=(rand()%80)*SIZE;
        obj.push_back(tem); //存储新生成的方块
        //cout<<sqrt(9)<<endl;
        update(); //更新窗口部件
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPixmap pixmap;
    pixmap = QPixmap("://image/title.png");
    QPainter painter(this);

    painter.setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
    painter.setPen(QPen(Qt::blue,1,Qt::SolidLine));
    painter.drawRect(x,y,SIZE,SIZE); //绘制黄色方块
/*    if(flag==-1){
        obj.clear();
        flag=1;
    }*/
    painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
    for(int i=0; i<obj.size(); i++){ //若黄色方块碰到绿色方块，则吃掉该绿色方块
        if(pow(x-obj[i].ox,2)<81 && pow(y-obj[i].oy,2)<81)
            obj.erase(obj.begin() + i);
    }
    for(int i=0; i<obj.size(); i++) //绘制所有绿色方块
        painter.drawRect(obj[i].ox,obj[i].oy,obj[i].lx,obj[i].ly);
    painter.drawPixmap(22,10,255,255,pixmap); //绘制标题
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up: //黄色方块向上移动
        y-=SIZE;
        if(y<0) y=400-SIZE;
        break;
    case Qt::Key_Down: //黄色方块向下移动
        y+=SIZE;
        if(y>=400) y=0;
        break;
    case Qt::Key_Left: //黄色方块向左移动
        x-=SIZE;
        if(x<0) x=300-SIZE;
        break;
    case Qt::Key_Right: //黄色方块向右移动
        x+=SIZE;
        if(x>=300) x=0;
        break;
    case Qt::Key_Space:
        flag=-flag;
        break;
    default:
        break;
    }
    update();
}

Widget::~Widget()
{
    delete ui;
}
