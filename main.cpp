#include <QApplication>
#include "mainwindow.h"
#include <QScreen>
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    
    
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect area = screen ->availableGeometry(); //gives us usable space
    int margin = 20;
    window.move(
        area.x() + area.width() - window.width() - margin,
        area.y() + area.height() - window.height() - margin
    );


    window.show();

    return app.exec();
}