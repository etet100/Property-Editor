
#ifndef CSWITCHPROPERTY_H
#define CSWITCHPROPERTY_H

#include "CBaseProperty.h"
#include "X_Switch_Button/x_switch_button.h"

class CSwitchProperty : public CBaseProperty
{
    public:
        CSwitchProperty(const QByteArray& id, const QString &name, bool value, bool defaultValue = false);
        CSwitchProperty(CBaseProperty *top, const QByteArray& id, const QString &name, bool value, bool defaultValue = false);

        virtual void setValue(int value) const;
        int getValue() const;

        QWidget* createSwitch();

        virtual QVariant getVariantValue() const override;
        void onAdded() override;
        void finishEdit(bool cancel = false) override;

    protected:
        bool m_value;
        bool m_defaultValue;
        X_Switch_Button *m_switch;
};

#endif // CSWITCHPROPERTY_H
