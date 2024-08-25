#include <QApplication>
#include <QMainWindow>
#include <QLineEdit>
#include <QToolBar>
#include "webview.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.resize(1024, 768);

    // Create the toolbar with a search bar
    QToolBar* toolbar = new QToolBar(&window);
    QLineEdit* searchBar = new QLineEdit(toolbar);
    toolbar->addWidget(searchBar);
    window.addToolBar(toolbar);

    // Create the web view using the function from webview.cpp
    QWebEngineView* view = createWebView(&window);
    window.setCentralWidget(view);

    window.show();

    // Connect search bar to navigate to the URL entered
    QObject::connect(searchBar, &QLineEdit::returnPressed, [&]() {
        view->setUrl(QUrl(searchBar->text()));
    });

    return app.exec();
}