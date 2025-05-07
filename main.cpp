#include "widget.h"
#include "welcomewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WelcomeWidget wel;
    Widget w;

    QObject::connect(&wel, &WelcomeWidget::startGame, [&w]() {
        w.show();
        w.startGame();
    });

    wel.show();
    return a.exec();
}
