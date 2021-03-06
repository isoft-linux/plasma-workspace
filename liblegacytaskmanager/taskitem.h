/*****************************************************************

Copyright 2008 Christian Mollekopf <chrigi_1@hotmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

******************************************************************/

#ifndef TASKITEM_H
#define TASKITEM_H

#include <abstractgroupableitem.h>
#include <startup.h>
#include <task.h>
#include <legacytaskmanager_export.h>

#include <QtGui/QIcon>

namespace LegacyTaskManager
{

class GroupManager;
class TaskItemPrivate;

/**
 * Wrapper class so we do not have to use the Task class directly and the Task* remains guarded
 */
class LEGACYTASKMANAGER_EXPORT TaskItem : public AbstractGroupableItem
{
    Q_OBJECT
public:
    /** Creates a taskitem for a task*/
    TaskItem(QObject *parent, Task *item);
    /** Creates a taskitem for a startuptask*/
    TaskItem(QObject *parent, Startup *item);
    ~TaskItem() override;
    /** Sets the taskpointer after the startup pointer */
    void setTaskPointer(Task *task);
    /** Returns a pointer to the  Task; may be NULL */
    Task *task() const;

    WindowList winIds() const override;

    Startup *startup() const;
    ItemType itemType() const override;
    /**
    * @deprecated: use itemType() instead
    **/
    LEGACYTASKMANAGER_DEPRECATED bool isGroupItem() const override;

    QIcon icon() const override;

    QString name() const override;
    QString taskName() const;

    QStringList activities() const;
    QStringList activityNames(bool includeCurrent = true) const;

    bool isStartupItem() const override;
    bool isOnCurrentDesktop() const override;
    bool isOnAllDesktops() const override;
    int desktop() const override;
    bool isShaded() const override;
    bool isMaximized() const override;
    bool isMinimized() const override;
    bool isFullScreen() const override;
    bool isKeptBelowOthers() const override;
    bool isAlwaysOnTop() const override;
    bool isActive() const override;
    bool demandsAttention() const override;
    bool isActionSupported(NET::Action) const override;
    void addMimeData(QMimeData *mimeData) const override;
    void setLauncherUrl(const QUrl &url);
    void setLauncherUrl(const AbstractGroupableItem *item);
    QUrl launcherUrl() const override;
    static QUrl launcherUrlFromTask(GroupManager *groupManager, Task *task, Startup *startup = 0);
    static bool launcherUrlIsKnown(const QUrl &url);
    static QIcon launcherIconFromUrl(const QUrl &url);
    void resetLauncherCheck();

public Q_SLOTS:
    void toDesktop(int) override;

    void setShaded(bool) override;
    void toggleShaded() override;

    void setMaximized(bool) override;
    void toggleMaximized() override;

    void setMinimized(bool) override;
    void toggleMinimized() override;

    void setFullScreen(bool) override;
    void toggleFullScreen() override;

    void setKeptBelowOthers(bool) override;
    void toggleKeptBelowOthers() override;

    void setAlwaysOnTop(bool) override;
    void toggleAlwaysOnTop() override;

    void close() override;
    void taskDestroyed();

Q_SIGNALS:
    /** Indicates that the startup task now is a normal task */
    void gotTaskPointer();

private:
    Q_PRIVATE_SLOT(d, void filterChange(::LegacyTaskManager::TaskChanges change))

    friend class TaskItemPrivate;
    TaskItemPrivate * const d;
};

} // LegacyTaskManager namespace

#endif
