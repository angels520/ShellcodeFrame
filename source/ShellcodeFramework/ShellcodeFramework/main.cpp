#include "ShellcodeFramework.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShellcodeFramework w;
    w.show();
    return a.exec();
}
