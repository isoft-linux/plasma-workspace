/*****************************************************************
ksmserver - the KDE session management server

Copyright 2000 Matthias Ettrich <ettrich@kde.org>

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

#ifndef SHUTDOWNDLG_H
#define SHUTDOWNDLG_H

#include <QQuickView>
#include <QPushButton>
#include <kworkspace.h>

class QMenu;
class QTimer;
class QTimeLine;
class QLabel;
class LogoutEffect;

namespace Plasma
{
    class Svg;
    class FrameSvg;
}

class QQuickView;

// The confirmation dialog
class KSMShutdownDlg : public QQuickView
{
    Q_OBJECT

public:
    static bool confirmShutdown(
            bool maysd, bool choose, KWorkSpace::ShutdownType& sdtype, QString& bopt, const QString& theme );

    bool result() const;
    bool exec();

public Q_SLOTS:
    void accept();
    void reject();
    void slotLogout();
    void slotHalt();
    void slotReboot();
    void slotReboot(int);
    void slotSuspend(int);
    void slotLockScreen();

Q_SIGNALS:
    void accepted();
    void rejected();

protected:
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

private:
    KSMShutdownDlg( QWindow* parent, bool maysd, bool choose, KWorkSpace::ShutdownType sdtype, const QString& theme );
    KWorkSpace::ShutdownType m_shutdownType;
    QString m_bootOption;
    QStringList rebootOptions;
    bool m_result : 1;
};

#endif
