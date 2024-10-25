#include <QApplication>
#include "../Headers/Mainwindow.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.setWindowTitle("Магазин Vapes");
    window.resize(800, 600);
    window.show();
    return app.exec();  // Вернулось к стандартному вызову app.exec()
}