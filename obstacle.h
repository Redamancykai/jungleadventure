#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "character.h"
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QRect>
#include <QTimer>
#include <QRandomGenerator>
#include <QList>

class Character;

class Obstacle : public QWidget
{
    Q_OBJECT
public:
    explicit Obstacle(const QString &imagePath, int fixedX, int fixedY, QWidget *parent = nullptr);
    ~Obstacle();

    QRect getRect(){
        QRect rect = geometry();
        int exactWidth = 84;
        int exactHeight = 96;
        int setX = (rect.width() - exactWidth) / 2;
        int setY = (rect.height() - exactHeight) / 2;
        return QRect(rect.x() + setX, rect.y() + setY, exactWidth, exactHeight);
    }


    // 墓碑向左移动
    // 理论上移动速度最好和背景图片移动速度一样，但是不方便控制游戏难度
    void obstacleMove(){
        obstacleRect.translate(-moveSpeed, 0);
        setGeometry(obstacleRect);
    }

    void startGenerating(){
        moveTimer->start(16);
        QTimer::singleShot(1000, this, &Obstacle::generateObstacle);
        // 直接生成似乎会造成前两个障碍物间隔较近，延迟1s执行
    }

    void setGenerateTime(int minTime, int maxTime){
        this->minTime = minTime;
        this->maxTime = maxTime;
    }

    void setCharacter(Character *character){
        this->character = character;
    }

    void stopGenerating(){
        moveTimer->stop();
        obstacleTimer->stop();
    }

    void resetObstacle(){
        stopGenerating();
        qDeleteAll(obstacles);
        obstacles.clear();
    }

signals:
    void gameOver();

protected:
    void paintEvent(QPaintEvent *event) override{
        QPainter obstaclePainter(this);
        obstaclePainter.drawPixmap(0,0,width(),height(),obstaclepicture);
    }

private slots:
    void allobstaclesMove();

    void generateObstacle();

private:
    QPixmap obstaclepicture;
    QRect obstacleRect;

    QList<Obstacle*> obstacles;
    QTimer *obstacleTimer;
    QRandomGenerator randomGen;
    QWidget *parentWidget;
    int minTime;
    int maxTime;
    int fixedX;
    int fixedY;

    QTimer *moveTimer;
    double moveSpeed;

    Character *character = nullptr;
};

#endif // OBSTACLE_H
