/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qvariant.h"

#include "qicon.h"
#include "qsizepolicy.h"

#include "private/qvariant_p.h"
#include <private/qmetatype_p.h>

QT_BEGIN_NAMESPACE


static void construct(QVariant::Private *x, const void *copy)
{
    switch (x->type) {
#ifndef QT_NO_ICON
    case QVariant::Icon:
        v_construct<QIcon>(x, copy);
        break;
#endif
    case QVariant::SizePolicy:
        v_construct<QSizePolicy>(x, copy);
        break;
    default:
        Q_ASSERT(false);
        return;
    }
    x->is_null = !copy;
}

static void clear(QVariant::Private *d)
{
    switch (d->type) {
#ifndef QT_NO_ICON
    case QVariant::Icon:
        v_clear<QIcon>(d);
        break;
#endif
    case QVariant::SizePolicy:
        v_clear<QSizePolicy>(d);
        break;
    default:
        Q_ASSERT(false);
        return;
    }

    d->type = QVariant::Invalid;
    d->is_null = true;
    d->is_shared = false;
}


static bool isNull(const QVariant::Private *d)
{
    switch(d->type) {
#ifndef QT_NO_ICON
    case QVariant::Icon:
        return v_cast<QIcon>(d)->isNull();
#endif
    default:
        Q_ASSERT(false);
    }
    return true;
}

static bool compare(const QVariant::Private *a, const QVariant::Private *b)
{
    Q_ASSERT(a->type == b->type);
    switch(a->type) {
#ifndef QT_NO_ICON
    case QVariant::Icon:
        return false;
#endif
    case QVariant::SizePolicy:
        return *v_cast<QSizePolicy>(a) == *v_cast<QSizePolicy>(b);
    default:
        Q_ASSERT(false);
    }
    return false;
}


static const QVariant::Handler widgets_handler = {
    construct,
    clear,
    isNull,
#ifndef QT_NO_DATASTREAM
    0,
    0,
#endif
    compare,
    0,
    0,
#if !defined(QT_NO_DEBUG_STREAM) && !defined(Q_BROKEN_DEBUG_STREAM)
    0
#else
    0
#endif
};

extern Q_CORE_EXPORT const QMetaTypeInterface *qMetaTypeWidgetsHelper;

#define QT_IMPL_METATYPEINTERFACE_WIDGETS_TYPES(MetaTypeName, MetaTypeId, RealName) \
    QT_METATYPE_INTERFACE_INIT(RealName),

static const QMetaTypeInterface qVariantWidgetsHelper[] = {
    QT_FOR_EACH_STATIC_WIDGETS_CLASS(QT_IMPL_METATYPEINTERFACE_WIDGETS_TYPES)
};

#undef QT_IMPL_METATYPEINTERFACE_WIDGETS_TYPES

extern Q_GUI_EXPORT const QVariant::Handler *qt_widgets_variant_handler;

void qRegisterWidgetsVariant()
{
    qt_widgets_variant_handler = &widgets_handler;
    qMetaTypeWidgetsHelper = qVariantWidgetsHelper;
}
Q_CONSTRUCTOR_FUNCTION(qRegisterWidgetsVariant)

void qUnregisterWidgetsVariant()
{
    qt_widgets_variant_handler = 0;
    qMetaTypeWidgetsHelper = 0;
}
Q_DESTRUCTOR_FUNCTION(qUnregisterWidgetsVariant)


QT_END_NAMESPACE
