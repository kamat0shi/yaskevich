#include <QApplication>
#include "../Headers/Mainwindow.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Магазин Vapes");
    window.resize(400, 300);
    window.show();

    return app.exec();
}