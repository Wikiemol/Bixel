#ifndef CANVASWIDGET_HPP
#define CANVASWIDGET_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <QWidget>
#include <QResizeEvent>
#include <QString>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>
#include <QMargins>
#include <QAbstractButton>
#include <QMouseEvent>
#include <QColorDialog>
#include <QColor>
#include "glwidget.hpp"
#include "vec2.hpp"

class CanvasWidget : public QWidget {
    Q_OBJECT
    public:

        CanvasWidget(QWidget* parent = 0);
        ~CanvasWidget();
        int getCurrentTool();

    public slots:
        void changeTool(int tool);
        void openColorPicker();
        //void selectSwatch();
        void setCurrentColor(const QColor& color);
        void deselectAll();
        void selectAll();
        void zoomIn();
        void zoomOut();
        void updateSize();
        void undo();
        void redo();
        void open(std::string fileName);
        void saveAs(std::string fileName);
    signals:
        void colorChanged(const QString& styleSheet);
        void stateChanged();

    protected:
        void resizeEvent(QResizeEvent* event);
        void paintEvent(QPaintEvent*);
        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);

    private:
        GLWidget* openGLWidget;
        float zoom;
        QColorDialog colorPicker; 
        GLWidget::DrawTool currentTool;
        QColor currentColor;
        vec2 clickPosition;
        QWidget* mainWindow;
        std::string m_fileName;

        bool eventFilter(QObject* object, QEvent* event);

};
#endif
