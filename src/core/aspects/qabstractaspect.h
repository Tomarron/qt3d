/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QT3D_QABSTRACTASPECT_H
#define QT3D_QABSTRACTASPECT_H

#include <QObject>
#include <QSharedPointer>
#include <Qt3DCore/qt3dcore_global.h>
#include <Qt3DCore/qjobproviderinterface.h>

QT_BEGIN_NAMESPACE

class QWindow;
class QSurface;

namespace Qt3D {

class QAspectManager;
class QNode;
class QEntity;
class QAbstractAspectPrivate;
class QSceneObserverInterface;
class QJobManagerInterface;
class QBackendNodeFunctor;

typedef QSharedPointer<QBackendNodeFunctor> QBackendNodeFunctorPtr;

class QT3DCORESHARED_EXPORT QAbstractAspect : public QObject, public QJobProviderInterface
{
    Q_OBJECT

public:
    enum AspectType {
        AspectRenderer,
        AspectAnimation,
        AspectCollision,
        AspectPhysics,
        AspectPhysicsAndCollision,
        AspectAI,
        AspectAudio,
        AspectOther
    };

    explicit QAbstractAspect(AspectType aspectType, QObject *parent = 0);

    AspectType aspectType() const;

    void registerAspect(QEntity *rootObject);

    QJobManagerInterface *jobManager() const;

    virtual QSceneObserverInterface *sceneObserver() const = 0;

protected:
    QAbstractAspect(QAbstractAspectPrivate &dd, QObject *parent = 0);

    template<class Frontend>
    void registerBackendType(QBackendNodeFunctorPtr);
    void registerBackendType(const std::type_info &info, QBackendNodeFunctorPtr functor);

private:
    virtual void setRootEntity(QEntity *rootObject) = 0;
    virtual void onInitialize(QSurface *surface) = 0;
    virtual void onCleanup() = 0;

    Q_DECLARE_PRIVATE(QAbstractAspect)
    // These are only called by the aspect manager
    friend class QAspectManager;
};

template<class Frontend>
void QAbstractAspect::registerBackendType(QBackendNodeFunctorPtr functor)
{
    registerBackendType(typeid(Frontend), functor);
}

} // namespace Qt3D

QT_END_NAMESPACE

Q_DECLARE_METATYPE(Qt3D::QAbstractAspect *)

#endif // QT3D_ABSTRACTASPECT_H
