
#include "CSwitchProperty.h"
#include <QPlainTextEdit>
#include <QVBoxLayout>

CSwitchProperty::CSwitchProperty(const QByteArray& id, const QString &name, bool value, bool defaultValue)
    : CBaseProperty(id, name), m_value(value), m_defaultValue(defaultValue)
{
}

CSwitchProperty::CSwitchProperty(CBaseProperty *top, const QByteArray& id, const QString &name, bool value, bool defaultValue)
    : CBaseProperty(top, id, name), m_value(value), m_defaultValue(defaultValue)
{
}

void CSwitchProperty::setValue(int value) const
{
    m_switch->setChecked(value);
}

int CSwitchProperty::getValue() const
{
    return m_switch->checked();
}

QWidget *CSwitchProperty::createSwitch()
{
    QWidget *container = new QWidget();

    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);

    m_switch = new X_Switch_Button(container);
    m_switch->setFixedSize(35, 16);
    m_switch->setTextOff("");
    m_switch->setTextOn("");
    m_switch->setStateChangedCallback([this](bool newState) {
        Q_UNUSED(newState);

        emitValueChanged();
    });

    container->setLayout(layout);
    layout->addWidget(m_switch);

    return container;
}

QVariant CSwitchProperty::getVariantValue() const
{
    return QVariant(getValue());
}

void CSwitchProperty::onAdded()
{
    this->treeWidget()->setItemWidget(
        this,
        1,
        createSwitch()
    );
}

// Ugly hack to prevent the editor from deleting our widget
void CSwitchProperty::finishEdit(bool cancel)
{
    Q_UNUSED(cancel);

    treeWidget()->setFocus();
}

