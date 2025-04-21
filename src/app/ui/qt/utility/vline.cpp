#include "vline.hpp"

VLine::VLine(QWidget *parent) : QFrame(parent) {
    setFrameShape(QFrame::VLine);
    m_Color = palette().color(QPalette::WindowText);
}

QColor VLine::color() const {
    return m_Color;
}

void VLine::setColor(QColor color) {
    QPalette palette = this->palette();
    palette.setColor(QPalette::WindowText, color);
    setPalette(palette);
    m_Color = color;
}