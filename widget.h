#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QMessageBox>
#include <QLabel>
#include <QApplication>
#include "character.h"
#include "obstacle.h"
#include "destroyableobs.h"
#include "gameoverwidget.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Character;
class Obstacle;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void startGame(){
        timer->start(8);
        scoreTimer->start(10);
        QTimer::singleShot(1000, this, [this]() {
            obstacle->startGenerating();
            arrow->startGenerating();
        });
    }

    int getScore(){
        return score;
    }

    void bonusScore(int bonus){
        score += bonus;
        displayScore->setText(QString("Score:%1").arg(score));
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter bgpainter(this);

        // 背景图片循环播放，实现动态效果
        bgpainter.drawPixmap(0, 0, background, photoPosition, 0, width(), height());
        if (photoPosition + width() > background.width()) {
            bgpainter.drawPixmap(background.width() - photoPosition, 0, background, 0, 0, photoPosition + width() - background.width(), background.height());
        }
    }


private slots:
    // 一张图片播放完从头播放
    void updatephotoPosition() {
        photoPosition += 2;
        if (photoPosition >= background.width()) {
            photoPosition = 0;
        }
        update();
    }

    // 游戏结束时执行此函数
    void whenGameOver(){
        timer->stop();
        obstacle->stopGenerating();
        character->playDeathFrame();
        arrow->stopGenerating();

        scoreTimer->stop();

        // 防止内存泄漏
        if (gameoverWidget) {
            delete gameoverWidget;
            gameoverWidget = nullptr;
        }

        gameoverWidget = new GameoverWidget(score, this);
        gameoverWidget->move(368, 208);
        connect(gameoverWidget, &GameoverWidget::reStart, this, &Widget::exeRestart);
        connect(gameoverWidget, &GameoverWidget::shutDown, this, &Widget::exeShutdown);
        gameoverWidget->show();

    }

    void updateScore(){
        score ++;
        displayScore->setText(QString("Score:%1").arg(score));
    }

    void exeRestart(){
        // 对所有数据进行初始化
        score = 0;
        displayScore->setText(QString("Score: %1").arg(score));

        photoPosition = 0;
        update();

        character->setFocus();
        character->resetCharacter();

        obstacle->resetObstacle();
        arrow->resetArrow();

        timer->start(8);
        scoreTimer->start(10);
        QTimer::singleShot(1000, this, [this]() {
            obstacle->startGenerating();
            arrow->startGenerating();
        });
    }

    void exeShutdown(){
        QApplication::quit();
    }


private:
    Ui::Widget *ui;

    QPixmap background;
    int photoPosition;
    QTimer *timer;

    Character *character;

    Obstacle *obstacle;

    DestroyableObs *arrow;

    QLabel *displayScore;
    QTimer *scoreTimer;
    int score = 0;

    GameoverWidget *gameoverWidget = nullptr;

};


#endif // WIDGET_H
