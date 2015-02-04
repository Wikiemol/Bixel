#ifndef SWATCH_HPP
#define SWATCH_HPP
#include <QToolButton>
#include <string>
class Swatch : public QToolButton {
    Q_OBJECT

    public:
        Swatch(QWidget* parent = 0);
        ~Swatch();
        void setColor(QRgb color);
        void setColor(QColor color);
        void setColor(int r, int g, int b, int a = 255);
        QColor color();

    signals:
        void swatchPicked(const QColor& color);

    protected:
        void mouseReleaseEvent(QMouseEvent*);

    private:
        QColor m_color;

};
#endif
