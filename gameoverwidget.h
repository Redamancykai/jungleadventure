#ifndef GAMEOVERWIDGET_H
#define GAMEOVERWIDGET_H
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>
#include <QPushButton>

class GameoverWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameoverWidget(int score, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter bgpainter(this);
        QPixmap bg = gameOverbg.scaled(720, 400, Qt::IgnoreAspectRatio);
        bgpainter.drawPixmap(0, 0, width(), height(), bg);
    }

private slots:
    void whenRetart(){
        emit reStart();
        close();
    }

    void whenShutdown(){
        emit shutDown();
        close();
    }

signals:
    void reStart();
    void shutDown();

private:
    QPixmap gameOverbg;
    QLabel *gameOverLabel;
    QLabel *scoreLabel;
    QPushButton *restartBn;
    QPushButton *closeBn;
};

#endif // GAMEOVERWIDGET_H

