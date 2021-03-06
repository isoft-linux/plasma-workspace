/********************************************************************
Copyright 2016  Eike Hein <hein.org>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) version 3, or any
later version accepted by the membership of KDE e.V. (or its
successor approved by the membership of KDE e.V.), which shall
act as a proxy defined in Section 6 of version 3 of the license.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/

#ifndef ABSTRACTASKSMODELIFACE_H
#define ABSTRACTASKSMODELIFACE_H

#include <QObject>

#include "taskmanager_export.h"

namespace TaskManager
{

/**
 * @short Pure virtual method interface for tasks model implementations.
 *
 * This is the pure virtual method interface implemented by AbstractTasksModel,
 * as well as other model classes in this library which cannot inherit from
 * AbstractTasksModel.
 *
 * @author Eike Hein <hein@kde.org>
 **/

class TASKMANAGER_EXPORT AbstractTasksModelIface
{
public:
    virtual ~AbstractTasksModelIface() {}

    /**
     * Request activation of the task at the given index. Implementing classes
     * are free to interpret the meaning of "activate" themselves depending on
     * the nature and state of the task, e.g. launch or raise a window task.
     *
     * @param index An index in this tasks model.
     **/
    virtual void requestActivate(const QModelIndex &index) = 0;

    /**
     * Request an additional instance of the application backing the task at
     * the given index.
     *
     * @param index An index in this tasks model.
     **/
    virtual void requestNewInstance(const QModelIndex &index) = 0;

    /**
     * Request the task at the given index be closed.
     *
     * @param index An index in this tasks model.
     **/
    virtual void requestClose(const QModelIndex &index) = 0;

    /**
     * Request starting an interactive move for the task at the given index.
     *
     * This is meant for tasks that have an associated window, and may be
     * a no-op when there is no window.
     *
     * @param index An index in this tasks model.
     **/
    virtual void requestMove(const QModelIndex &index) = 0;

    /**
     * Request starting an interactive resize for the task at the given index.
     *
     * This is meant for tasks that have an associated window, and may be a
     * no-op when there is no window.
     *
     * @param index An index in this tasks model.
     **/
    virtual void requestResize(const QModelIndex &index) = 0;

    /**
     * Request toggling the minimized state of the task at the given index.
     *
     * This is meant for tasks that have an associated window, and may be
     * a no-op when there is no window.
     *
     * @param index An index in this tasks model.
     **/
    virtual void requestToggleMinimized(const QModelIndex &index) = 0;

    /**
     * Request toggling the maximized state of the task at the given index.
     *
     * This is meant for tasks that have an associated window, and may be
     * a no-op when there is no window.
     *
     * @param index An index in this tasks model.
     **/
    virtual void requestToggleMaximized(const QModelIndex &index) = 0;

    /**
     * Request toggling the keep-above state of the task at the given index.
     *
     * This is meant for tasks that have an associated window, and may be
     * a no-op when there is no window.
     *
     * @param index An index in this tasks model.
     **/
    virtual void requestToggleKeepAbove(const QModelIndex &index) = 0;

    /**
     * Request toggling the keep-below state of the task at the given index.
     *
     * This is meant for tasks that have an associated window, and may be
     * a no-op when there is no window.
     *
     * @param index An index in this tasks model.
     **/
    virtual void requestToggleKeepBelow(const QModelIndex &index) = 0;

    /**
     * Request toggling the fullscreen state of the task at the given index.
     *
     * This is meant for tasks that have an associated window, and may be
     * a no-op when there is no window.
     *
     * @param index An index in this tasks model.
     **/
    virtual void requestToggleFullScreen(const QModelIndex &index) = 0;

    /**
     * Request toggling the shaded state of the task at the given index.
     *
     * This is meant for tasks that have an associated window, and may be
     * a no-op when there is no window.
     *
     * @param index An index in this tasks model.
     **/
    virtual void requestToggleShaded(const QModelIndex &index) = 0;

    /**
     * Request moving the task at the given index to the specified virtual
     * desktop.
     *
     * This is meant for tasks that have an associated window, and may be
     * a no-op when there is no window.
     *
     * @param index An index in this tasks model.
     * @param desktop A virtual desktop number.
     **/
    virtual void requestVirtualDesktop(const QModelIndex &index, qint32 desktop = -1) = 0;

    /**
     * Request informing the window manager of new geometry for a visual
     * delegate for the task at the given index. The geometry should be in
     * screen coordinates.
     *
     * FIXME: Doesn't deal with the long-standing problem of multiple
     * delegates in multiple applets.
     *
     * @param index An index in this tasks model.
     * @param geometry Visual delegate geometry in screen coordinates.
     * @param delegate The delegate. Implementations are on their own with
     * regard to extracting information from this, and should take care to
     * reject invalid objects.
     **/
    virtual void requestPublishDelegateGeometry(const QModelIndex &index, const QRect &geometry,
        QObject *delegate = nullptr) = 0;
};

}

#endif
