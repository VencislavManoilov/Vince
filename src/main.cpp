#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QLineEdit>
#include <QToolBar>
#include <QTabWidget>
#include <QWebEngineView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QAction>
#include <QShortcut>
#include <QKeySequence>
#include <QMenuBar>
#include "webview.h"
#include <regex>

class BrowserWindow : public QMainWindow {
    Q_OBJECT

public:
    BrowserWindow() {
        setWindowTitle("Vince Browser");
        resize(1024, 768);

        // Create the toolbar with a search bar and buttons
        QToolBar* toolbar = new QToolBar(this);
        QLineEdit* searchBar = new QLineEdit(toolbar);

        toolbar->addWidget(searchBar);
        addToolBar(toolbar);

        // Create the tab widget
        tabWidget = new QTabWidget(this);
        tabWidget->setMovable(true);
        tabWidget->setTabsClosable(true);
        connect(tabWidget, &QTabWidget::tabCloseRequested, this, &BrowserWindow::closeCurrentTab);

        // Create the new tab button
        QPushButton* newTabButton = new QPushButton("+", this);

        // Add the new tab button to the right corner of the tab bar
        tabWidget->setCornerWidget(newTabButton, Qt::TopRightCorner);

        setCentralWidget(tabWidget);

        // Connect the toolbar buttons
        connect(newTabButton, &QPushButton::clicked, this, &BrowserWindow::addNewTab);
        connect(searchBar, &QLineEdit::returnPressed, this, &BrowserWindow::navigateToUrl);

	// Shortcuts
        QAction* newTabAction = new QAction(tr("New Tab"), this);
        newTabAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_T));
        connect(newTabAction, &QAction::triggered, this, &BrowserWindow::addNewTab);

        QAction* closeTabAction = new QAction(tr("Close Tab"), this);
        closeTabAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_W));
        connect(closeTabAction, &QAction::triggered, this, &BrowserWindow::closeCurrentTab);

        // Add actions to the menu bar
        QMenu* fileMenu = menuBar()->addMenu(tr("File"));
        fileMenu->addAction(newTabAction);
        fileMenu->addAction(closeTabAction);

        // Add the initial tab
        addNewTab();
    }

private slots:
    void addNewTab() {
        QWebEngineView* view = createWebView(this);
        tabWidget->addTab(view, "New Tab");
        tabWidget->setCurrentWidget(view);

        // Update tab title when the page title changes
        connect(view, &QWebEngineView::titleChanged, this, [=](const QString& title) {
            tabWidget->setTabText(tabWidget->indexOf(view), title);
            });
    }

    void closeCurrentTab() {
        if (tabWidget->count() > 1) {
            tabWidget->removeTab(tabWidget->currentIndex());
        } else {
            this->close();
        }
    }

    void navigateToUrl() {
        QLineEdit* searchBar = findChild<QLineEdit*>();
        if (searchBar && tabWidget->currentWidget()) {
            QWebEngineView* view = qobject_cast<QWebEngineView*>(tabWidget->currentWidget());
            if (view) {
                std::string searchText = searchBar->text().toStdString();

                // Check if searchText is a URL
                std::regex urlRegex(R"(^(https?://)?([a-zA-Z0-9-]+\.)+[a-zA-Z]{2,6}(/[\w\-\.~:/?#[\]@!$&'()*+,;=]*)?$)");
		if (std::regex_match(searchText, urlRegex)) {
                    // If the URL does not have a scheme, prepend "https://"
                    if (searchText.find("http://") != 0 && searchText.find("https://") != 0) {
                        searchText = "https://" + searchText;
                    }
                } else {
                    // If not a URL, treat it as a search query (example with Google)
                    searchText = "https://www.google.com/search?q=" + QUrl::toPercentEncoding(QString::fromStdString(searchText)).toStdString();
                }

                searchBar->setText(QString::fromStdString(searchText));

                view->setUrl(QUrl(QString::fromStdString(searchText)));
            }
        }
    }

private:
    QTabWidget* tabWidget;
};

// Include the generated MOC file
#include "main.moc"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    BrowserWindow window;
    window.show();

    return app.exec();
}
