// This file is a part of "G-Pilot (formerly Candle)" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich
// Copyright 2024 BTS

#include "QExtSpinBox.h"
#include <QDebug>

QExtSpinBox::QExtSpinBox(QWidget *parent) : QSpinBox(parent)
{
    this->setFocusPolicy(Qt::ClickFocus);
}

void QExtSpinBox::setOnEditingFinished(EventCallback callback)
{
    editingFinishedCallback = callback;
}

void QExtSpinBox::setOnEditingCancelled(EventCallback callback)
{
    editingCancelledCallback = callback;
}

void QExtSpinBox::focusOutEvent(QFocusEvent *event)
{
    Q_UNUSED(event);

    editingFinishedCallback();
}

void QExtSpinBox::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        editingFinishedCallback();

        return;
    }

    if (event->key() == Qt::Key_Escape)
    {
        editingCancelledCallback();

        return;
    }

    QSpinBox::keyPressEvent(event);
}
