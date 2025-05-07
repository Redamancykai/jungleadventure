#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H
#include <QPainter>
#include <QPixmap>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>

class WelcomeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter bgpainter(this);
        QPixmap bg = welcomebg.scaled(1456, 816, Qt::IgnoreAspectRatio);
        bgpainter.drawPixmap(0, 0, width(), height(), bg);
    }

private slots:
    void whenStart(){
        emit startGame();
        close();
    }

    void whenHelp(){
        QMessageBox::information(this, "帮助信息",
                                 "Welcome to Jungle Adventure ！\n\n"
                                 "操作说明：\n"
                                 "- 按 [Space] 键跳跃（支持二段跳）。\n"
                                 "- 按 [F] 键攻击，击破箭矢可获得100分。\n"
                                 "- 躲避障碍物，撞到障碍物或未击破的箭会导致游戏结束。\n"
                                 "- 游戏每秒自动加100分，尽可能跑得更远吧！\n\n"
                                 "Let's Go！");
    }

signals:
    void startGame();

private:
    QPixmap welcomebg;
    QLabel *titleLabel;
    QPushButton *startBn;
    QPushButton *helpBn;

};

#endif // WELCOMEWIDGET_H
