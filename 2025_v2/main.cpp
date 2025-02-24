#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>

void applyStyle(const QString &stylesheetPath);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Debug: Display application directory path
    qDebug() << "App path:" << qApp->applicationDirPath();

    // Path to the default stylesheet
    QString stylesheetPath = qApp->applicationDirPath() + "/styles/theDark.qss";

    // Apply the default stylesheet
    applyStyle(stylesheetPath);

    MainWindow w;
    w.show();

    return app.exec();
}

void applyStyle(const QString &stylesheetPath)
{
    QFile styleFile(stylesheetPath);
    if (styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        QString style = QTextStream(&styleFile).readAll();
        qApp->setStyleSheet(style);
        qDebug() << "Applied stylesheet from:" << stylesheetPath;
        styleFile.close();
    }
    else
    {
        qWarning() << "Failed to open stylesheet file:" << stylesheetPath;
    }
}
