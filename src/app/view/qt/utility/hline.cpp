#include "hline.hpp"

HLine::HLine(QWidget *parent) : QFrame(parent) {
    setFrameShape(QFrame::HLine);
    m_Color = palette().color(QPalette::WindowText);
}

QColor HLine::color() const {
    return m_Color;
}

void HLine::setColor(QColor color) {
    QPalette palette = this->palette();
    palette.setColor(QPalette::WindowText, color);
    setPalette(palette);
    m_Color = color;
}