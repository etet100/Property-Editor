// This file is a part of "G-Pilot (formerly Candle)" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich
// Copyright 2024 BTS

#ifndef QEXTDOUBLESPINBOX_H
#define QEXTDOUBLESPINBOX_H

#include <QDoubleSpinBox>
#include <QKeyEvent>
#include "Callbacks.h"

class QExtDoubleSpinBox : public QDoubleSpinBox
{
    public:
        QExtDoubleSpinBox(QWidget *parent = nullptr);
        void setOnEditingFinished(EventCallback callback);
        void setOnEditingCancelled(EventCallback callback);

    protected:
        void focusOutEvent(QFocusEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;

    private:
        EventCallback editingFinishedCallback;
        EventCallback editingCancelledCallback;
};

#endif // QEXTDOUBLESPINBOX_H
