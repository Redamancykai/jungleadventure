#ifndef CHARACTER_H
#define CHARACTER_H

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QKeyEvent>
#include <QRect>
#include <QTimer>
#include <QString>

class Character : public QWidget
{
    Q_OBJECT
public:
    explicit Character(QWidget *parent = nullptr);
    ~Character();

    // 实际角色范围远小于切割矩形范围，调整合适大小使碰撞检测更合理
    // 返回实际矩形位置
    QRect getRect(){
        QRect rect = geometry();
        int exactWidth = 120;
        int exactHeight = 140;
        int setX = (rect.width() - exactWidth) / 2;
        int setY = (rect.height() - exactHeight) / 2;
        return QRect(rect.x() + setX, rect.y() + setY, exactWidth, exactHeight);
    }

    // 播放死亡动画
    void playDeathFrame(){
        if(currentAction != "death"){
            currentAction = "death";
            currentFrame = 0;
            update();
            return;
        }
    }

    QString getCurrentAction(){
        return currentAction;
    }

    // 重置角色状态
    void resetCharacter(){
        currentAction = "run";
        jumpCount = 0;
        setGeometry(250, 525, 200, 200);
        actionTimer->start(100);
    }

protected:
    // 播放人物动作图片
    void paintEvent(QPaintEvent *event) override{
        QPainter chpainter(this);
        if (currentAction == "stand") {
            chpainter.drawPixmap(0, 0, width(), height(), standFrames[currentFrame]);
        }
        else if (currentAction == "run") {
            chpainter.drawPixmap(0, 0, width(), height(), runFrames[currentFrame]);
        }
        else if (currentAction == "attack") {
            chpainter.drawPixmap(0, 0, width(), height(), attackFrames[currentFrame]);
        }
        else if (currentAction == "death") {
            chpainter.drawPixmap(0, 0, width(), height(), deathFrames[currentFrame]);
        }
    }

    // 按键控制
    void keyPressEvent(QKeyEvent *event) override{
        int dx = 0, dy = 0;
        switch (event->key()) {
        case Qt::Key_F: // 攻击键
            if(currentAction != "attack"){
                currentAction = "attack";
                currentFrame = 0;
                update();
                return;
            }
            break;
        case Qt::Key_Space: // 跳跃键
            if(jumpCount < 2 && !event->isAutoRepeat()){
                jumpCount++;

                jumpTime = 0.0;
                Y0 = y();
                X0 = x();
                Vy = 600;
                jumpTimer->start(16);

                currentAction = "stand";
                currentFrame = 0;
                update();

                return;
            }
            move(x() + dx, y() + dy);
            break;
        }
    }

private slots:
    // 播放人物动画
    void updateactionFrame() {
        if (currentAction == "stand") {
            currentFrame = (currentFrame + 1) % standFrames.size();
        }
        else if (currentAction == "run") {
            currentFrame = (currentFrame + 1) % runFrames.size();
        }
        else if (currentAction == "attack") {
            currentFrame++;
            if(currentFrame >= attackFrames.size()){
                currentAction = "run";
                currentFrame = 0;
            }
        }
        else if (currentAction == "death") {
            currentFrame++;
            if(currentFrame >= deathFrames.size()){
                currentFrame = deathFrames.size() - 1;
                actionTimer->stop();
            }
        }
        update();
    }

    // 播放跳跃动画
    void updateJump(){
        jumpTime += 0.016;
        double newY = Y0 - Vy * jumpTime + 0.5 * gravity * jumpTime * jumpTime * 60;
        move(X0, newY);

        // 检查跳跃是否结束
        if (y() >= groundY) {
            jumpCount = 0;
            jumpTimer->stop();
            if(currentAction != "death"){
                currentAction = "run";
            }
        }

        update();
    }

private:
    QRect maincharacter;

    // 角色动画
    QPixmap actionSheet;
    QTimer *actionTimer;
    QVector<QPixmap> standFrames;
    QVector<QPixmap> runFrames;
    QVector<QPixmap> attackFrames;
    QVector<QPixmap> deathFrames;
    QRect characterRect;
    int currentFrame;
    QString currentAction;

    // 角色跳跃
    int jumpCount; //允许二连跳
    QTimer *jumpTimer;
    double jumpTime;
    double Y0;
    double X0;
    double Vy;
    double Vx;
    double gravity;
    int groundY;

};

#endif // CHARACTER_H
