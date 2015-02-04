#include "swatch.hpp"
#include <stdio.h>
#include <sstream>
Swatch::Swatch(QWidget* parent) : QToolButton(parent) {
    setCheckable(false);
}
Swatch::~Swatch() {}

void Swatch::setColor(QRgb color) {
    setColor(QColor(color));
}

void Swatch::setColor(QColor color) {
    std::stringstream red;
    red << color.red();

    std::stringstream green;
    green << color.green();

    std::stringstream blue;
    blue << color.blue();

    m_color = color;
    std::string newStyleSheet = "background-color: rgba("; 
                newStyleSheet += red.str();
                newStyleSheet += ", "; 
                newStyleSheet += green.str(); 
                newStyleSheet += ", "; 
                newStyleSheet += blue.str(); 
                newStyleSheet += ")";

    setStyleSheet(QString(newStyleSheet.c_str()));
}

void Swatch::setColor(int r, int g, int b, int a) {
    setColor(QColor(r, g, b, a));
}

QColor Swatch::color() {
    return m_color;
}

void Swatch::mouseReleaseEvent(QMouseEvent*) {
    //fprintf(stderr, "yoyo\n");
    setDown(false);
    emit swatchPicked(m_color);
}
