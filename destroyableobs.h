#ifndef DESTROYABLEOBS_H
#define DESTROYABLEOBS_H
#include "character.h"
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QRect>
#include <QTimer>
#include <QRandomGenerator>
#include <QList>

class Character;

class DestroyableObs : public QWidget
{
    Q_OBJECT
public:
    explicit DestroyableObs(const QString &imagepath, int fixedX, QWidget *parent = nullptr);
    ~DestroyableObs();

    // 整体结构类似于Obstacle，但希望高度随机生成，且具有可被摧毁性质
    QRect getRect(){
        QRect rect = geometry();
        int exactWidth = 128;
        int exactHeight = 64;
        int setX = (rect.width() - exactWidth) / 2;
        int setY = (rect.height() - exactHeight) / 2;
        return QRect(rect.x() + setX, rect.y() + setY, exactWidth, exactHeight);
    }

    void arrowMove(){
        DestroyableObsRect.translate(-moveSpeed, 0);
        setGeometry(DestroyableObsRect);
    }

    void startGenerating(){
        moveTimer->start(16);
        QTimer::singleShot(800, this, &DestroyableObs::generateArrow);
    }

    void setGenerateTime(int minTime, int maxTime){
        this->minTime = minTime;
        this->maxTime = maxTime;
    }

    void setGenerateHeight(int minHeight, int maxHeight){
        this->minHeight = minHeight;
        this->maxHeight = maxHeight;
    }

    void setCharacter(Character *character){
        this->character = character;
    }

    void stopGenerating(){
        moveTimer->stop();
        arrowTimer->stop();
    }

    void resetArrow(){
        stopGenerating();
        qDeleteAll(arrows);
        arrows.clear();
    }

protected:
    void paintEvent(QPaintEvent *event) override{
        QPainter arrowpainter(this);
        arrowpainter.drawPixmap(0, 0, width(), height(), arrowpicture);
    }

signals:
    void gameOver();

private slots:
    void generateArrow();
    void allArrowsMove();

private:
    QRect DestroyableObsRect;
    QPixmap arrowpicture;
    QList<DestroyableObs*> arrows;
    QTimer *moveTimer;
    QTimer *arrowTimer;
    QRandomGenerator randomGen;

    Character *character = nullptr;
    QWidget *parentWidget;

    double moveSpeed;

    int fixedX;

    int minTime;
    int maxTime;
    int minHeight;
    int maxHeight;
};

#endif // DESTROYABLEOBS_H

