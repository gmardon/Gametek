//
// Create by gmardon
//
#include <QApplication>
#include <src/gui/MainWindow.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.resize(640, 512);
    window.show();
    window.openASMFile("../../resources/cgb_boot.asm");
    return app.exec();
}