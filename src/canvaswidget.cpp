#pragma GCC diagnostic ignored "-Wswitch"
#include <string>
#include <stdlib.h>
#include <sstream>
#include "canvaswidget.hpp"
#include "bixelwindow.hpp"

//-Public-//
CanvasWidget::CanvasWidget(QWidget* parent) : QWidget(parent), zoom(1.0), clickPosition(0, 0), m_fileName("") {
    CanvasWidget::openGLWidget = new GLWidget(this); 
    openGLWidget->installEventFilter(this);
    QObject::connect(&colorPicker, SIGNAL(currentColorChanged(QColor)), this, SLOT(setCurrentColor(QColor)));
    setCurrentColor(QColor(128, 200, 128));
    changeTool(GLWidget::MOUSE);

    mainWindow = window();

    QObject::connect(openGLWidget, SIGNAL(stateChanged()), this, SIGNAL(stateChanged()));

    //Handling menu actions//
    QObject::connect(mainWindow, SIGNAL(deselect_all_signal()), this, SLOT(deselectAll()));
    QObject::connect(mainWindow, SIGNAL(select_all_signal()), this, SLOT(selectAll()));
    QObject::connect(mainWindow, SIGNAL(zoom_in_signal()), this, SLOT(zoomIn()));
    QObject::connect(mainWindow, SIGNAL(zoom_out_signal()), this, SLOT(zoomOut()));
    QObject::connect(mainWindow, SIGNAL(undo_signal()), this, SLOT(undo()));
    QObject::connect(mainWindow, SIGNAL(redo_signal()), this, SLOT(redo()));
    QObject::connect(mainWindow, SIGNAL(open_signal(std::string)), this, SLOT(open(std::string)));
    QObject::connect(mainWindow, SIGNAL(save_as_signal(std::string)), this, SLOT(saveAs(std::string)));
}

CanvasWidget::~CanvasWidget() {
    delete openGLWidget;
}

int CanvasWidget::getCurrentTool() {
    return currentTool;
}

//-Public Slots-//

/**
 * Changes the current tool being used to update
 * the widget. This function calls GLWidget::changeTool(int)
 * on the underlying GLWidget.
 *
 * @param tool      A GLWidget::DrawTool enum
 *                  that represents the tool the
 *                  widget should use.
 *
 * @see CanvasWidget::mousePressEvent(QEvent*)
 * @see CanvasWidget::mouseMoveEvent(QEvent*)
 * @see GLWidget::changeTool(int)
 */

void CanvasWidget::changeTool(int tool) {
    currentTool = (GLWidget::DrawTool) tool;

    openGLWidget->changeTool(currentTool);
}

void CanvasWidget::openColorPicker() {
    fprintf(stderr, "Color Picker Open\n");
    colorPicker.setCurrentColor(currentColor);
    colorPicker.open();
}

void CanvasWidget::setCurrentColor(const QColor& color) {
    currentColor = color;

    std::stringstream red;
    red << color.red();

    std::stringstream green;
    green << color.green();

    std::stringstream blue;
    blue << color.blue();

    std::string styleSheet = "background-color: rgb(";
                styleSheet += red.str();
                styleSheet += ",";
                styleSheet += green.str(); 
                styleSheet += ",";
                styleSheet += blue.str();
                styleSheet += ")";
    openGLWidget->setDrawingColor(color);
    emit colorChanged(QString::fromStdString(styleSheet));
}

void CanvasWidget::deselectAll() {
    openGLWidget->deselectAll();
}

void CanvasWidget::selectAll() {
    openGLWidget->selectAll();
}

void CanvasWidget::zoomIn() {
    zoom += 0.1;
    updateSize();
}

void CanvasWidget::zoomOut() {
    if(zoom > 0.1) {
        zoom -= 0.1;
    }
    updateSize();
}

//Called directly by resizeEvent
void CanvasWidget::updateSize() {
    //QMargins margins = contentsMargins();

    //int maxMargin = std::max(std::max(std::max(margins.left(), margins.right()), margins.top()), margins.bottom());

    if(this->width() > this->height()) {
        openGLWidget->resize(zoom * (this->height()), zoom * (this->height()));
    } else {
        openGLWidget->resize(zoom * (this->width()), zoom * (this->width()));
    }

    openGLWidget->move(this->width() * 0.5 - openGLWidget->width() * 0.5,
                       this->height() * 0.5 - openGLWidget->height() * 0.5);
}

void CanvasWidget::undo() {
    openGLWidget->undo();
}

void CanvasWidget::redo() {
    openGLWidget->redo();
}

void CanvasWidget::open(std::string fileName) {
    openGLWidget->openFile(fileName);
}

void CanvasWidget::saveAs(std::string fileName) {
    m_fileName = fileName;
    openGLWidget->saveFile(fileName);
}

//-Protected EventHandlers-//
void CanvasWidget::resizeEvent(QResizeEvent*) {
    updateSize();
}

void CanvasWidget::paintEvent(QPaintEvent*) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void CanvasWidget::mousePressEvent(QMouseEvent* event) {
    switch(currentTool) {
        case GLWidget::HAND:
            clickPosition.set(event->globalX(), event->globalY());
        break;
    }
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent* ) {}

void CanvasWidget::mouseMoveEvent(QMouseEvent* event) {
    switch(currentTool) {
        case GLWidget::HAND:
            vec2 change = vec2(event->globalX(), event->globalY()) - clickPosition;
            CanvasWidget::openGLWidget->move(openGLWidget->x() + change.x, openGLWidget->y() + change.y);
            clickPosition.set(event->globalX(), event->globalY());
        break;
    }
}

//-Private-//

bool CanvasWidget::eventFilter(QObject*, QEvent* event) {
    //-Maybe check if object is child of this class later-//
    switch(event->type()) {
        case QEvent::MouseButtonPress:
            mousePressEvent((QMouseEvent*) event);
        break;

        case QEvent::MouseMove:
            mouseMoveEvent((QMouseEvent*) event);
        break;

        case QEvent::MouseButtonRelease:
            mouseReleaseEvent((QMouseEvent*) event);
        break;
    }
    return false;
}
