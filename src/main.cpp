#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QLineEdit>
#include <QTabWidget>
#include <QWebEngineView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QAction>
#include <QShortcut>
#include <QKeySequence>
#include <QMenuBar>
#include "webview.h"
#include "ShortcutsManager.h"
#include <regex>

class BrowserWindow : public QMainWindow {
    Q_OBJECT

public:
    BrowserWindow() {
        setWindowTitle("Vince Browser");
        resize(1024, 768);

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

        // Add the initial tab
        addNewTab();
    }

    void addNewTab() {
        // Create a new widget to hold both the search bar and the web view
        QWidget* tab = new QWidget;
        QVBoxLayout* layout = new QVBoxLayout(tab);

        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);

        // Create the search bar specific to this tab
        QLineEdit* searchBar = new QLineEdit(tab);

        // Create the web view specific to this tab
        QWebEngineView* view = createWebView(this);

        // Add the search bar and the web view to the layout
        layout->addWidget(searchBar);
        layout->addWidget(view);

        // Set the layout for the tab widget
        tab->setLayout(layout);

        // Add the new tab with the composite widget (search bar + web view)
        tabWidget->addTab(tab, "New Tab");
        tabWidget->setCurrentWidget(tab);

        // Connect the search bar to navigate the web view when Enter is pressed
        connect(searchBar, &QLineEdit::returnPressed, [=]() {
            QUrl url = UrlRefactor(searchBar->text().toStdString());
            searchBar->setText(url.toString());
            view->setUrl(url);
            view->setFocus();
        });

        // Update tab title when the page title changes
        connect(view, &QWebEngineView::titleChanged, this, [=](const QString& title) {
            tabWidget->setTabText(tabWidget->indexOf(tab), title);
        });

        connect(view, &QWebEngineView::urlChanged, this, [=](const QUrl& url) {
            searchBar->setText(url.toString());
        });

        tabWidget->setStyleSheet("QTabWidget::pane { margin: 0px; padding: 0px; border: 0px; }");
        tabWidget->setContentsMargins(0, 0, 0, 0);
    }

    void closeCurrentTab() {
        if (tabWidget->count() > 1) {
            tabWidget->removeTab(tabWidget->currentIndex());
        }
        else {
            this->close();
        }
    }

private slots:
    QUrl UrlRefactor(std::string url) {
        std::string searchText = url;

        // Check if searchText is a URL
        std::regex urlRegex(R"(^(https?://)?([a-zA-Z0-9-]+\.)+[a-zA-Z]{2,6}(/[\w\-\.~:/?#[\]@!$&'()*+,;=]*)?$)");
        if (std::regex_match(searchText, urlRegex)) {
            // If the URL does not have a scheme, prepend "https://"
            if (searchText.find("http://") != 0 && searchText.find("https://") != 0) {
                searchText = "https://" + searchText;
            }
        }
        else {
            // If not a URL, treat it as a search query (example with Google)
            searchText = "https://www.google.com/search?q=" + QUrl::toPercentEncoding(QString::fromStdString(searchText)).toStdString();
        }

        return QString::fromStdString(searchText);
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
    // Create the ShortcutsManager and pass the BrowserWindow's functions
    ShortcutsManager shortcutsManager(&window, 
                                      [&window]() { window.addNewTab(); }, 
                                      [&window]() { window.closeCurrentTab(); });
    window.show();

    return app.exec();
}
