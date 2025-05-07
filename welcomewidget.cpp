#include "welcomewidget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1456, 816);

    welcomebg.load(":/img/welcomebg.jpg");

    QVBoxLayout *layout = new QVBoxLayout(this);

    titleLabel = new QLabel("Jungle Adventure", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("QLabel{background-color: transparent; color: #B22222; font-size: 128px; font-weight: bold; font-family: Ink Free}");
    layout->addWidget(titleLabel);

    QFont buttonFont("宋体", 20, 20, 0);

    startBn = new QPushButton("开始游戏", this);
    startBn->setStyleSheet("QPushButton{background-color : rgba(141, 140, 153, 1);}\
                            QPushButton:hover{background-color : rgba(120, 119, 130, 1);}\
                            QPushButton:pressed{background-color : rgba(82, 82, 89, 1)}");
    startBn->setFont(buttonFont);
    layout->addWidget(startBn);
    connect(startBn, &QPushButton::clicked, this, &WelcomeWidget::whenStart);

    helpBn = new QPushButton("帮助", this);
    helpBn->setStyleSheet("QPushButton{background-color : rgba(141, 140, 153, 1);}\
                            QPushButton:hover{background-color : rgba(120, 119, 130, 1);}\
                            QPushButton:pressed{background-color : rgba(82, 82, 89, 1)}");
    helpBn->setFont(buttonFont);
    layout->addWidget(helpBn);
    connect(helpBn, &QPushButton::clicked, this, &WelcomeWidget::whenHelp);

    setLayout(layout);
}

