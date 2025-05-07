#include "destroyableobs.h"
#include "widget.h"

DestroyableObs::DestroyableObs(const QString &imagepath, int fixedX, QWidget *parent)
    : QWidget(parent), moveSpeed(0), randomGen(), fixedX(fixedX)
{
    arrowpicture.load(":/img/arrow.png");

    DestroyableObsRect = QRect(0, 0, 128, 128);
    setFixedSize(128, 128);

    parentWidget = parent;

    moveTimer = new QTimer(this);
    arrowTimer = new QTimer(this);

    connect(arrowTimer, &QTimer::timeout, this, &DestroyableObs::generateArrow);
    connect(moveTimer, &QTimer::timeout, this, &DestroyableObs::allArrowsMove);

    minTime = 3000;
    maxTime = 5000;

    minHeight = 200;
    maxHeight = 500;
}

void DestroyableObs::generateArrow(){
    double speed = 10;

    // 创建箭矢
    DestroyableObs *arrow = new DestroyableObs(":/img/arrow.png", fixedX, parentWidget);

    arrow->moveSpeed = speed;
    arrow->setFixedSize(128,128);

    int x = parentWidget->width() - arrow->width();
    int y = randomGen.bounded(minHeight, maxHeight + 1);
    arrow->move(x, y);
    arrow->DestroyableObsRect.moveTo(x, y);
    arrow->raise();
    arrows.append(arrow);
    arrow->show();

    int interval = randomGen.bounded(minTime, maxTime + 1);
    arrowTimer->start(interval);
}

void DestroyableObs::allArrowsMove(){
    for(int i = 0; i < arrows.size(); i++){
        DestroyableObs *arrow = arrows[i];
        arrow->arrowMove();

        // 碰撞检测，如果此时角色正在攻击则摧毁弓箭，反之游戏结束
        // 注意这里释放内存的顺序！！

        bool ifDelete = false;

        if(arrow->getRect().right() < 0){
            ifDelete = true;
        }

        else if(character && character->getRect().intersects(arrow->getRect())){
            if(character->getCurrentAction() == "attack"){
                ifDelete = true;

                // 摧毁箭矢奖励分数
                Widget *widget = qobject_cast<Widget*>(parentWidget);
                widget->bonusScore(100);
            }
            else{
                emit gameOver();
                return;
            }
        }

        // 统一释放确保安全
        if(ifDelete){
            arrows.removeAt(i);
            delete arrow;
            i--;
        }
    }

    if(parentWidget){
        parentWidget->update();
    }
}

DestroyableObs::~DestroyableObs(){
    qDeleteAll(arrows);
    arrows.clear();
    delete moveTimer;
    delete arrowTimer;
}
