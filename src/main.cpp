#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QLineEdit>
#include <QTabWidget>
#include <QWebEngineView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QAction>
#include <QTabBar>
#include <QShortcut>
#include <QKeySequence>
#include <QMenuBar>
#include <QStyleOption>
#include <QPainter>
#include "webview.h"
#include "ShortcutsManager.h"
#include <regex>

class BrowserWindow : public QMainWindow {
    Q_OBJECT

public:
    BrowserWindow() {
        setWindowTitle("Vince Browser");
        resize(1024, 768);

        // Disable the window frame to create a custom title bar
        setWindowFlags(Qt::FramelessWindowHint);

        // Create the tab widget
        tabWidget = new QTabWidget(this);
        tabWidget->setMovable(true);
        tabWidget->setTabsClosable(true);
        tabWidget->setElideMode(Qt::ElideRight); // To handle long tab titles
        connect(tabWidget, &QTabWidget::tabCloseRequested, this, &BrowserWindow::closeCurrentTab);

        // Create window control buttons
        QPushButton* minimizeButton = new QPushButton("-", this);
        QPushButton* maximizeButton = new QPushButton("□", this);
        QPushButton* closeButton = new QPushButton("x", this);

        minimizeButton->setFixedSize(25, 23);
        maximizeButton->setFixedSize(25, 23);
        closeButton->setFixedSize(25, 23);

        connect(minimizeButton, &QPushButton::clicked, this, &BrowserWindow::showMinimized);
        connect(maximizeButton, &QPushButton::clicked, this, &BrowserWindow::toggleMaximized);
        connect(closeButton, &QPushButton::clicked, this, &BrowserWindow::close);

        // Add the new tab button to the right side of the tab bar
        QPushButton* newTabButton = new QPushButton("+", this);
        newTabButton->setFixedSize(23, 23);
        connect(newTabButton, &QPushButton::clicked, this, &BrowserWindow::addNewTab);

        // Layout for the tab bar and controls
        QHBoxLayout* titleBarLayout = new QHBoxLayout();
        titleBarLayout->addWidget(tabWidget);
        titleBarLayout->addWidget(newTabButton);

        // Adding stretch to ensure buttons stay on the right
        titleBarLayout->addStretch(1);

        titleBarLayout->addWidget(minimizeButton);
        titleBarLayout->addWidget(maximizeButton);
        titleBarLayout->addWidget(closeButton);
        titleBarLayout->setSpacing(0);
        titleBarLayout->setContentsMargins(0, 0, 0, 0);

        // Create a widget to hold the title bar layout
        QWidget* titleBarWidget = new QWidget(this);
        titleBarWidget->setLayout(titleBarLayout);

        // Set the custom title bar
        setMenuWidget(titleBarWidget);

        // Create initial tab
        addNewTab();

        // Ensure the central widget is a blank container, so the web view can expand
        QWidget* centralWidget = new QWidget(this);
        QVBoxLayout* centralLayout = new QVBoxLayout(centralWidget);
        centralLayout->addWidget(tabWidget);
        centralLayout->setContentsMargins(0, 0, 0, 0);
        setCentralWidget(centralWidget);
    }

    void addNewTab() {
        // Create a new widget to hold both the search bar and the web view
        QWidget* tab = new QWidget;
        QVBoxLayout* layout = new QVBoxLayout(tab);

        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);

        // Create the search bar and web view specific to this tab
        QLineEdit* searchBar = new QLineEdit(tab);
        QWebEngineView* view = createWebView(this);

        layout->addWidget(searchBar);
        layout->addWidget(view);

        // Set the layout for the tab widget
        tab->setLayout(layout);

        // Add the new tab with the composite widget (search bar + web view)
        tabWidget->addTab(tab, "New Tab");
        tabWidget->setCurrentWidget(tab);

        // Connect the search bar to navigate the web view when Enter is pressed
        connect(searchBar, &QLineEdit::returnPressed, [searchBar, view, this]() {
            QUrl url = UrlRefactor(searchBar->text().toStdString());
            searchBar->setText(url.toString());
            view->setUrl(url);
            view->setFocus();
        });

        // Update tab title when the page title changes
        connect(view, &QWebEngineView::titleChanged, this, [=](const QString& title) {
            tabWidget->setTabText(tabWidget->indexOf(tab), title);
        });

        // Update url when the page url changes
        connect(view, &QWebEngineView::urlChanged, this, [=](const QUrl& url) {
            searchBar->setText(url.toString());
        });

        // Removes extra padding from tab
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

protected:
    // Reimplement paintEvent to draw the custom window frame and background
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event);

        QStyleOption opt;
        opt.initFrom(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
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

    void toggleMaximized() {
        if (isMaximized()) {
            showNormal();
        }
        else {
            showMaximized();
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
    // Create the ShortcutsManager and pass the BrowserWindow's functions
    ShortcutsManager shortcutsManager(&window, 
                                      [&window]() { window.addNewTab(); }, 
                                      [&window]() { window.closeCurrentTab(); });
    window.show();

    return app.exec();
}
