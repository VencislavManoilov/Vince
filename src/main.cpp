#include <QApplication>
#include <QMainWindow>
#include <QWebEngineView>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.resize(1024, 768);

    // Create a QWebEngineView and set it as the central widget
    QWebEngineView* view = new QWebEngineView(&window);
    view->setUrl(QUrl("https://www.google.com"));
    window.setCentralWidget(view);

    window.show();

    return app.exec();
}