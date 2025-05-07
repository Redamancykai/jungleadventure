#include "gameoverwidget.h"

GameoverWidget::GameoverWidget(int score, QWidget *parent) : QWidget(parent)
{
    setFixedSize(720, 400);

    gameOverbg.load(":/img/gameoverbg.jpg");

    // 布局设计
    QVBoxLayout *layout = new QVBoxLayout(this);

    gameOverLabel = new QLabel("YOU DIED", this);
    gameOverLabel->setAlignment(Qt::AlignCenter);
    gameOverLabel->setStyleSheet("QLabel{background-color: transparent; color: red; font-size: 48px; font-weight: bold;}");
    layout->addWidget(gameOverLabel);

    scoreLabel = new QLabel(QString("SCORE：%1").arg(score), this);
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setStyleSheet("QLabel{background-color: transparent; color: red; font-size: 48px; font-weight: bold;}");
    layout->addWidget(scoreLabel);

    QFont buttonFont("宋体", 20, 20, 0);

    restartBn = new QPushButton("再来一次", this);
    restartBn->setStyleSheet("QPushButton{background-color : rgba(141, 140, 153, 1);}\
                            QPushButton:hover{background-color : rgba(120, 119, 130, 1);}\
                            QPushButton:pressed{background-color : rgba(82, 82, 89, 1)}");
    restartBn->setFont(buttonFont);
    layout->addWidget(restartBn);
    connect(restartBn, &QPushButton::clicked, this, &::GameoverWidget::whenRetart);

    closeBn = new QPushButton("退出游戏", this);
    closeBn->setStyleSheet("QPushButton{background-color : rgba(141, 140, 153, 1);}\
                             QPushButton:hover{background-color : rgba(120, 119, 130, 1);}\
                             QPushButton:pressed{background-color : rgba(82, 82, 89, 1)}");
    closeBn->setFont(buttonFont);
    layout->addWidget(closeBn);
    connect(closeBn, &QPushButton::clicked, this, &::GameoverWidget::whenShutdown);

    setLayout(layout);

}
