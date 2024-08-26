#ifndef SHORTCUTSMANAGER_H
#define SHORTCUTSMANAGER_H

#include <QObject>
#include <QMainWindow>
#include <QAction>

class ShortcutsManager : public QObject {
    Q_OBJECT

public:
    ShortcutsManager(QMainWindow* parent, std::function<void()> addNewTabFunc, std::function<void()> closeCurrentTabFunc);

private slots:
    void onAddNewTab();
    void onCloseCurrentTab();

private:
    QAction* newTabAction;
    QAction* closeTabAction;
    std::function<void()> addNewTab;
    std::function<void()> closeCurrentTab;
};

#endif
