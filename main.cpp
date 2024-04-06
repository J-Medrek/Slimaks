#include <QApplication>
#include "interface/WizualizatorSymulacji.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    WizualizatorSymulacji widget;
    widget.show();
    return QApplication::exec();
}
