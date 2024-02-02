#include "mainModule/mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;

    /*
    bool t3 = false;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "taskManager_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            t3 = app.installTranslator(&translator);
            break;
        }
    }*/

    //QString app_dir_path = QApplication::applicationDirPath();
    QString translation_path = QString("D:/Programms/Qt/Projects/taskManager/languages/taskManager_ru_RU.qm");
    bool t1 = translator.load(":/taskManager_ru_RU.qm"); // not actually ru but...
    bool t2 = app.installTranslator(&translator);

    qDebug() << translation_path;
    qDebug() << t1 << ' ' << t2;

    MainWindow w;
    w.show();
    return app.exec();
}
