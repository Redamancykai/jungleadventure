#include "character.h"

Character::Character(QWidget *parent)
    : QWidget{parent}
{
    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    actionSheet.load(":/img/maincharacter.png");
    int frameWidth = 256;
    int frameHeight = 256;

    // 切割人物素材图（1024*1024）
    for (int i = 0; i < 4; i++) {
        standFrames.append(actionSheet.copy(i * frameWidth, 0, frameWidth, frameHeight));
    }
    for (int i = 0; i < 4; i++) {
        runFrames.append(actionSheet.copy(i * frameWidth, frameHeight, frameWidth, frameHeight));
    }
    for (int i = 0; i < 4; i++) {
        attackFrames.append(actionSheet.copy(i * frameWidth, 2 * frameHeight, frameWidth, frameHeight));
    }
    for (int i = 0; i < 4; i++) {
        deathFrames.append(actionSheet.copy(i * frameWidth, 3 * frameHeight, frameWidth, frameHeight));
    }


    // 初始化角色
    setGeometry(100, 100, frameWidth, frameHeight);
    characterRect = QRect(0, 0, frameWidth, frameHeight);
    currentFrame = 0;
    currentAction = "run";

    // 初始化人物动画定时器
    actionTimer = new QTimer(this);
    connect(actionTimer, &QTimer::timeout, this, &Character::updateactionFrame);
    actionTimer->start(100);

    // 初始化跳跃参数
    jumpCount = 0;
    jumpTimer = new QTimer(this);
    connect(jumpTimer, &QTimer::timeout, this, &Character::updateJump);
    jumpTime = 0.0;
    Vy = 600.0;
    Vx = 0.0;
    gravity = 15.0;
    groundY = 525;
}

Character::~Character() {
    delete actionTimer;
    delete jumpTimer;
}
