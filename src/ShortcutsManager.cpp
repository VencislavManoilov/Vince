#include "ShortcutsManager.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>

ShortcutsManager::ShortcutsManager(QMainWindow* parent, std::function<void()> addNewTabFunc, std::function<void()> closeCurrentTabFunc)
    : QObject(parent), addNewTab(addNewTabFunc), closeCurrentTab(closeCurrentTabFunc)
{
    newTabAction = new QAction(tr("New Tab"), parent);
    newTabAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_T));
    connect(newTabAction, &QAction::triggered, this, &ShortcutsManager::onAddNewTab);

    closeTabAction = new QAction(tr("Close Tab"), parent);
    closeTabAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_W));
    connect(closeTabAction, &QAction::triggered, this, &ShortcutsManager::onCloseCurrentTab);
}

void ShortcutsManager::onAddNewTab() {
    if (addNewTab) {
        addNewTab();
    }
}

void ShortcutsManager::onCloseCurrentTab() {
    if (closeCurrentTab) {
        closeCurrentTab();
    }
}
