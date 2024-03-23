// This file is a part of "G-Pilot (formerly Candle)" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich
// Copyright 2024 BTS

#include "QExtDoubleSpinBox.h"
#include <QDebug>

QExtDoubleSpinBox::QExtDoubleSpinBox(QWidget *parent) : QDoubleSpinBox(parent)
{
    this->setFocusPolicy(Qt::ClickFocus);
}

void QExtDoubleSpinBox::setOnEditingFinished(EventCallback callback)
{
    editingFinishedCallback = callback;
}

void QExtDoubleSpinBox::setOnEditingCancelled(EventCallback callback)
{
    editingCancelledCallback = callback;
}

void QExtDoubleSpinBox::focusOutEvent(QFocusEvent *event)
{
    Q_UNUSED(event);

    editingFinishedCallback();
}

void QExtDoubleSpinBox::keyPressEvent(QKeyEvent *event)
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

    QDoubleSpinBox::keyPressEvent(event);
}

