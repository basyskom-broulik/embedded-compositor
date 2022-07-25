#include <QtCore/QDebug>
#include <QtCore/QUrl>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine appEngine(QUrl("qrc:///main.qml"));
  return app.exec();
}