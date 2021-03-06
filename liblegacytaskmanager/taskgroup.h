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

 ***************************************************************************/

#ifndef TASKGROUP_H
#define TASKGROUP_H

#include <QtGui/QIcon>

#include "abstractgroupableitem.h"
#include "legacytaskmanager_export.h"
#include "launcheritem.h"

namespace LegacyTaskManager
{
class GroupManager;

/**
 * TaskGroup, a container for tasks and subgroups
 */
class LEGACYTASKMANAGER_EXPORT TaskGroup : public AbstractGroupableItem
{
    Q_OBJECT
public:
    TaskGroup(GroupManager *parent, const QString& name);
    TaskGroup(GroupManager *parent);
    ~TaskGroup() override;

    GroupManager *manager() const;
    ItemList members() const;
    WindowList winIds() const override;
    WindowList directMemberwinIds() const;

    AbstractGroupableItem *getMemberByWId(WId id);
    AbstractGroupableItem *getMemberById(int id);
    //including subgroups
    int totalSize();

    QIcon icon() const override;
    void setIcon(const QIcon &icon);

    QString name() const override;
    void setName(const QString &newName);

    ItemType itemType() const override;
    /**
    * @deprecated: use itemType() instead
    **/
    LEGACYTASKMANAGER_DEPRECATED bool isGroupItem() const override;
    bool isRootGroup() const;

    /** only true if item is in this group */
    bool hasDirectMember(AbstractGroupableItem * item) const;
    /** only true if item is in this or any sub group */
    bool hasMember(AbstractGroupableItem * item) const;
    /** Returns Direct Member group if the passed item is in a subgroup */
    AbstractGroupableItem * directMember(AbstractGroupableItem *) const;

    int desktop() const override;
    bool isShaded() const override;
    bool isMaximized() const override;
    bool isMinimized() const override;
    bool isFullScreen() const override;
    bool isKeptBelowOthers() const override;
    bool isAlwaysOnTop() const override;
    bool isActionSupported(NET::Action) const override;
    /** returns true if at least one member is active */
    bool isActive() const override;
    /** returns true if at least one member is demands attention */
    bool demandsAttention() const override;
    bool isOnAllDesktops() const override;
    bool isOnCurrentDesktop() const override;
    void addMimeData(QMimeData *mimeData) const override;
    QUrl launcherUrl() const override;

    /**
     * Sorting strategies may use this to move items around
     * @param oldIndex the index the item to be moved is currently at
     * @param newIndex the index the item will be moved to
     */
    bool moveItem(int oldIndex, int newIndex);

public Q_SLOTS:
    /** the following are functions which perform the corresponding actions on all member tasks */
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

    /** close all members of this group */
    void close() override;

    /** add item to group */
    void add(AbstractGroupableItem *item, int insertIndex = -1);

    /** remove item from group */
    void remove(AbstractGroupableItem *);

    /** remove all items from group */
    void clear();

Q_SIGNALS:
    /** inform visualization about wat is added and removed */
    void itemAboutToBeAdded(AbstractGroupableItem *item, int index);
    void itemAdded(AbstractGroupableItem *item);
    void itemAboutToBeRemoved(AbstractGroupableItem *item);
    void itemRemoved(AbstractGroupableItem *item);
    void groupEditRequest();
    /** inform visualization about position change */
    void itemAboutToMove(AbstractGroupableItem *item, int currentIndex, int newIndex);
    void itemPositionChanged(AbstractGroupableItem *item);
    /** The group changed the desktop, is emitted in the toDesktop function */
    void movedToDesktop(int newDesk);
    void checkIcon(TaskGroup *group);

private:
    Q_PRIVATE_SLOT(d, void itemDestroyed(AbstractGroupableItem *item))
    Q_PRIVATE_SLOT(d, void itemChanged(::LegacyTaskManager::TaskChanges changes))
    Q_PRIVATE_SLOT(d, void signalRemovals())

    class Private;
    Private * const d;
};


} // LegacyTaskManager namespace

#endif
