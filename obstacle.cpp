#include "obstacle.h"
#include "widget.h"

Obstacle::Obstacle(const QString &imagePath, int fixedX, int fixedY, QWidget *parent)
    : QWidget(parent), moveSpeed(0), randomGen(), fixedX(fixedX), fixedY(fixedY)
{
    obstaclepicture.load(":/img/gravestone.png");

    // 初始化墓碑障碍物
    obstacleRect = QRect(0, 0, 94, 106);
    setFixedSize(94, 106);

    parentWidget = parent;

    moveTimer = new QTimer(this);
    obstacleTimer = new QTimer(this);

    connect(obstacleTimer, &QTimer::timeout, this, &Obstacle::generateObstacle);
    connect(moveTimer, &QTimer::timeout, this, &Obstacle::allobstaclesMove);

}

void Obstacle::allobstaclesMove(){
    for(int i = 0; i < obstacles.size(); i++){
        Obstacle *obstacle = obstacles[i];
        obstacle->obstacleMove();

        // 实现碰撞检测，如果有重叠游戏结束，给出gameOver信号
        if(character && character->getRect().intersects(obstacle->getRect())){
            emit gameOver();
            return;
        }

        // 实现动态清除
        if(obstacle->getRect().right() < 0){
            obstacles.removeAt(i);
            delete obstacle;
            i--;
        }
    }

    if (parentWidget) {
        parentWidget->update();
    }
}

void Obstacle::generateObstacle() {
    double speed = 5;

    // 创建障碍物
    Obstacle *obstacle = new Obstacle(":/img/gravestone.png", fixedX, fixedY, parentWidget);

    obstacle->moveSpeed = speed;
    obstacle->setFixedSize(94,106);

    int x = parentWidget->width() - obstacle->width();
    obstacle->move(x, fixedY);
    obstacle->obstacleRect.moveTo(x, fixedY);
    // 墓碑障碍物的生成位置显示有误，后添加上面一行代码解决，可能是之前被初始化位置干扰
    obstacle->raise();
    obstacles.append(obstacle);
    obstacle->show();

    Widget *widget = qobject_cast<Widget*>(parentWidget);
    if(widget->Widget::getScore() >= 0 && widget->Widget::getScore() <= 2000 ){
        minTime = 3000;
        maxTime = 4000;
    }
    else if(widget->Widget::getScore() > 2000 && widget->Widget::getScore() <= 4000 ){
        minTime = 2500;
        maxTime = 3500;
    }
    else if(widget->Widget::getScore() > 4000 && widget->Widget::getScore() <= 6000 ){
        minTime = 2000;
        maxTime = 3000;
    }
    else{
        minTime = 1500;
        maxTime = 2500;
    }

    int interval = randomGen.bounded(minTime, maxTime + 1);
    obstacleTimer->start(interval);
}

Obstacle::~Obstacle(){
    qDeleteAll(obstacles);
    obstacles.clear();
    delete moveTimer;
    delete obstacleTimer;
}
