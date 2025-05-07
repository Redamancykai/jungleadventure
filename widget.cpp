#include "widget.h"
#include "./ui_widget.h"
#include "character.h"
#include "destroyableobs.h"
#include "obstacle.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    background.load(":/img/bgforest.jpg");

    this->setFixedSize(1456,816);

    // 实现背景图片循环播放
    photoPosition = 0;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::updatephotoPosition);

    // 主角色
    character = new Character(this);
    character->setGeometry(250, 525, 200, 200);
    character->setFocus();

    // 墓碑障碍物
    obstacle = new Obstacle(":/img/gravestone.png", 1362, 600, this);
    obstacle->setGenerateTime(2000, 3000);
    obstacle->setCharacter(character);
    obstacle->hide();
    connect(obstacle, &Obstacle::gameOver, this, &Widget::whenGameOver);

    // 弓箭障碍物
    arrow = new DestroyableObs(":/img/arrow.png", 640, this);
    arrow->setGenerateTime(1000, 2000);
    arrow->setCharacter(character);
    arrow->hide();
    connect(arrow, &DestroyableObs::gameOver, this, &Widget::whenGameOver);

    // 得分显示
    score = 0;
    scoreTimer = new QTimer(this);
    connect(scoreTimer, &QTimer::timeout, this, &Widget::updateScore);

    displayScore = new QLabel(this);
    displayScore->setText(QString("Score:%1").arg(score));
    displayScore->setStyleSheet("QLabel{background-color: transparent; color: white; font-size: 24px; font-weight: bold;}");
    displayScore->setGeometry(1256, 20, 180, 40);
    displayScore->show();

    gameoverWidget = nullptr;
}

Widget::~Widget()
{
    delete ui;
    delete character;
    delete timer;
    delete obstacle;
    delete scoreTimer;
    delete displayScore;
    delete gameoverWidget;
}
