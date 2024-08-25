#include "webview.h"
#include <QUrl>

QWebEngineView* createWebView(QMainWindow* parent) {
    QWebEngineView* view = new QWebEngineView(parent);
    view->setUrl(QUrl("https://www.google.com"));
    return view;
}