
#include "x_switch_button.h"
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>

X_Switch_Button::X_Switch_Button(QWidget *parent) : QWidget(parent)
{
    m_space = 2;
    m_radius = 5;
    m_checked = false;
    m_showText = true;
    m_animation = true;

    m_bgColorOn = QColor(0, 180, 255);
    m_bgColorOff = QColor(100, 100, 100);

    m_sliderColorOn= QColor(255, 255, 255);
    m_sliderColorOff = QColor(255, 255, 255);

    m_textColor = QColor(255, 255, 255);

    m_textStrOn = "On";
    m_textStrOff = "Off";

    m_slideStep = 0;
    m_aniStartX = 0;
    m_aniEndX = 0;

    m_aniTimer = new QTimer(this);
    m_aniTimer->setInterval(30);
    connect(m_aniTimer, &QTimer::timeout, this, &X_Switch_Button::updateValue);

#ifdef ENABLE_LOADING
    m_loading = true;
    loading_color = m_bgColorOff;
    m_aniCount = 0;

    m_outRadiuslist[0] = 4;
    m_outRadiuslist[1] = 3;
    m_outRadiuslist[2] = 3;
    m_outRadiuslist[3] = 2;
    m_outRadiuslist[4] = 2;
    m_outRadiuslist[5] = 1;
    m_outRadiuslist[6] = 1;
    m_outRadiuslist[7] = 1;
#endif
}

void X_Switch_Button::drawBackGround(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QColor bgColor = m_checked ? m_bgColorOn : m_bgColorOff;
    if ( ! isEnabled()) {
        bgColor.setAlpha(150);
    }

    painter->setBrush(bgColor);

    QRect rect(0, 0, width(), height());
    int side = qMin(width(), height());

    // Left semicircle
    QPainterPath path1;
    path1.addEllipse(rect.x(), rect.y(), side, side);

    // Right semicircle
    QPainterPath path2;
    path2.addEllipse(rect.width() - side, rect.y(), side, side);

    // Middle rectangle
    QPainterPath path3;
    path3.addRect(rect.x() + side / 2, rect.y(), rect.width() - side, height());

    QPainterPath path = path1 + path2 + path3;
    painter->drawPath(path);

    // Draw text
    // Slider radius
    int sliderWidth = qMin(height(), width()) - m_space * 2 - 5;
    if (m_checked){
        QRect textRect(0, 0, width() - sliderWidth, height());
        painter->setPen(QPen(m_textColor));
        if(showText()) painter->drawText(textRect, Qt::AlignCenter, m_textStrOn);
    } else {
        QRect textRect(sliderWidth, 0, width() - sliderWidth, height());
        painter->setPen(QPen(m_textColor));
        if(showText()) painter->drawText(textRect, Qt::AlignCenter, m_textStrOff);
    }

    painter->restore();
}

void X_Switch_Button::drawSlider(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QColor color = m_checked ? m_sliderColorOn : m_sliderColorOff;

    painter->setBrush(QBrush(color));

    m_sliderWidth = qMin(width(), height()) - m_space * 2;
    QRect rect(m_space + m_aniStartX, m_space, m_sliderWidth, m_sliderWidth);
    painter->drawEllipse(rect);

    painter->restore();
}

#ifdef ENABLE_LOADING
void X_Switch_Button::startLoading()
{
    // Set as not clickable
    this->setDisabled(true);
    m_displayedWhenStopped = false;
    m_aniCount = 0;
    for (int var = 0; var < 8; var++) {
        loading_point[var].setX(m_aniStartX + m_relXList[var]);
    }
    m_aniTimer->start();
}

void X_Switch_Button::stopLoading()
{
    // Set as clickable
    this->setDisabled(false);
    m_aniTimer->stop();
    m_displayedWhenStopped = true;
    update();
}

void X_Switch_Button::drawLoading(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    for (int var = 0; var < 8; ++var) {
        QPen pen(loading_color); // Define pen
        pen.setWidth(1);
        pen.setStyle(Qt::CustomDashLine);
        painter->setPen(pen);
        painter->setBrush(QBrush(loading_color, Qt::SolidPattern));
        painter->drawEllipse(loading_point[var],m_outRadiuslist[var],m_outRadiuslist[var]);
    }

    painter->restore();
}
#endif

void X_Switch_Button::resizeEvent(QResizeEvent *ev)
{
    Q_UNUSED(ev)

    m_sliderWidth = qMin(width(), height()) - m_space * 2;
#ifdef ENABLE_LOADING
    m_outRadius = m_sliderWidth/2 + m_space;
    m_inRadius = m_sliderWidth/2 - m_space*2;

    int x_offset = m_sliderWidth/2 + m_space;
    m_relXList[0] = x_offset + m_inRadius;
    m_relXList[1] = x_offset + m_inRadius*3/4;
    m_relXList[2] = x_offset;
    m_relXList[3] = x_offset - m_inRadius*3/4;
    m_relXList[4] = x_offset - m_inRadius;
    m_relXList[5] = x_offset - m_inRadius*3/4;
    m_relXList[6] = x_offset;
    m_relXList[7] = x_offset + m_inRadius*3/4;

    loading_point[0] = QPoint(m_aniStartX + m_relXList[0], m_outRadius); // Left
    loading_point[1] = QPoint(m_aniStartX + m_relXList[1], m_outRadius-m_inRadius*3/4); // Top-left
    loading_point[2] = QPoint(m_aniStartX + m_relXList[2], m_outRadius-m_inRadius); // Top
    loading_point[3] = QPoint(m_aniStartX + m_relXList[3], m_outRadius-m_inRadius*3/4); // Top-right
    loading_point[4] = QPoint(m_aniStartX + m_relXList[4], m_outRadius); // Right
    loading_point[5] = QPoint(m_aniStartX + m_relXList[5], m_outRadius+m_inRadius*3/4); // Bottom-right
    loading_point[6] = QPoint(m_aniStartX + m_relXList[6], m_outRadius+m_inRadius); // Bottom
    loading_point[7] = QPoint(m_aniStartX + m_relXList[7], m_outRadius+m_inRadius*3/4); // Bottom-left
#endif
}

void X_Switch_Button::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev)

    // Enable anti-aliasing
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    // Draw background
    drawBackGround(&painter);

    // Draw slider
    drawSlider(&painter);

#ifdef ENABLE_LOADING
    // Draw loading animation
    if(false == m_displayedWhenStopped)
        drawLoading(&painter);
#endif

}

void X_Switch_Button::statChanged()
{
    // Calculate step
    m_slideStep = width() / 10;

    // Calculate slider X end coordinate
    if (m_checked) {
        m_aniEndX = width() - height();
    } else {
        m_aniEndX = 0;
    }

    // Check if animation is used
    if (m_animation) {
        m_aniTimer->start();
    } else{
        m_aniStartX = m_aniEndX;
        update();
    }

    if (c_stateChangedCallback) c_stateChangedCallback(m_checked);
}

void X_Switch_Button::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() != Qt::MouseButton::LeftButton) return;

    //Q_UNUSED(ev)
#ifdef ENABLE_LOADING
    if (m_loading) {
        startLoading();
    }
    else
#endif
    {
        m_checked = !m_checked;
        statChanged();
    }
}

void X_Switch_Button::updateValue()
{
#ifdef ENABLE_LOADING
    if(false == m_displayedWhenStopped){
        if(0 != ++m_aniCount%3) return;
        m_aniCount = 0;
        int tmpInt = m_outRadiuslist[0];
        for (int var = 0; var < 7; var++) {
            m_outRadiuslist[var] = m_outRadiuslist[var+1];
        }
        m_outRadiuslist[7] = tmpInt;
    }else
#endif
    {
        if (m_checked) {
            if (m_aniStartX < m_aniEndX) {
                m_aniStartX += m_slideStep;
            } else {
                m_aniStartX = m_aniEndX;
                m_aniTimer->stop();
            }
        } else {
            if (m_aniStartX > m_aniEndX) {
                m_aniStartX -= m_slideStep;
            } else {
                m_aniStartX = m_aniEndX;
                m_aniTimer->stop();
            }
        }
    }

    update();
}

int X_Switch_Button::space() const
{
    return m_space;
}

int X_Switch_Button::radius() const
{
    return m_radius;
}

bool X_Switch_Button::checked() const
{
    return m_checked;
}

bool X_Switch_Button::showText() const
{
    return m_showText;
}

bool X_Switch_Button::animation() const
{
    return m_animation;
}


QColor X_Switch_Button::bgColorOn() const
{
    return m_bgColorOn;
}

QColor X_Switch_Button::bgColorOff() const
{
    return m_bgColorOff;
}

QColor X_Switch_Button::sliderColorOn() const
{
    return m_sliderColorOn;
}

QColor X_Switch_Button::sliderColorOff() const
{
    return m_sliderColorOff;
}

QColor X_Switch_Button::textColor() const
{
    return m_textColor;
}

QString X_Switch_Button::textStrOn() const
{
    return m_textStrOn;
}

QString X_Switch_Button::textStrOff() const
{
    return m_textStrOff;
}

int X_Switch_Button::slideStep() const
{
    return m_slideStep;
}

int X_Switch_Button::aniStartX() const
{
    return m_aniStartX;
}

int X_Switch_Button::aniEndX() const
{
    return m_aniEndX;
}

void X_Switch_Button::setSpace(int space)
{
    if (m_space != space) {
        m_space = space;
        update();
    }
}

void X_Switch_Button::setRadius(int radius)
{
    if (m_radius != radius) {
        m_radius = radius;
        update();
    }
}

void X_Switch_Button::setChecked(bool checked)
{
    if (m_checked != checked) {
        m_checked = checked;
        update();
    }

#ifdef ENABLE_LOADING
    stopLoading();
#endif
    statChanged();
}

#ifdef ENABLE_LOADING
bool X_Switch_Button::loading(){
    return m_loading;
}

void X_Switch_Button::setLoading(bool enabled){
    m_loading = enabled;
}
#endif

void X_Switch_Button::setShowText(bool show)
{
    if (m_showText != show) {
        m_showText = show;
        update();
    }
}

void X_Switch_Button::setAnimation(bool ok)
{
    if (m_animation != ok) {
        m_animation = ok;
        update();
    }
}

void X_Switch_Button::setBgColorOn(const QColor &color)
{
    if (m_bgColorOn != color) {
        m_bgColorOn = color;
        update();
    }
}

void X_Switch_Button::setBgColorOff(const QColor &color)
{
    if (m_bgColorOff != color) {
        m_bgColorOff = color;
        update();
    }
}

void X_Switch_Button::setSliderColorOn(const QColor &color)
{
    if (m_sliderColorOn != color) {
        m_sliderColorOn = color;
        update();
    }
}

void X_Switch_Button::setSliderColorOff(const QColor &color)
{
    if (m_sliderColorOff != color) {
        m_sliderColorOff = color;
        update();
    }
}

void X_Switch_Button::setTextColor(const QColor &color)
{
    if (m_textColor != color) {
        m_textColor = color;
        update();
    }
}


void X_Switch_Button::setTextOn(const QString &text)
{
    if (m_textStrOn != text) {
        m_textStrOn = text;
        update();
    }
}

void X_Switch_Button::setTextOff(const QString &text)
{
    if (m_textStrOff != text) {
        m_textStrOff = text;
        update();
    }
}
