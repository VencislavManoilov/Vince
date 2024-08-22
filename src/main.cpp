#include <QApplication>
#include <QWebEngineView>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWebEngineView view;
    view.setUrl(QUrl("http://google.com"));
    view.resize(1024, 768);
    view.show();

    return app.exec();
}