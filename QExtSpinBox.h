// This file is a part of "G-Pilot (formerly Candle)" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich
// Copyright 2024 BTS

#ifndef QEXTSPINBOX_H
#define QEXTSPINBOX_H

#include <QSpinBox>
#include <QKeyEvent>
#include "Callbacks.h"

class QExtSpinBox : public QSpinBox
{
    public:
        QExtSpinBox(QWidget *parent = nullptr);
        void setOnEditingFinished(EventCallback callback);
        void setOnEditingCancelled(EventCallback callback);

    protected:
        void focusOutEvent(QFocusEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;

    private:
        EventCallback editingFinishedCallback;
        EventCallback editingCancelledCallback;
};

#endif // QEXTSPINBOX_H
