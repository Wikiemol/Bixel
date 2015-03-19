#include <stdio.h>
#include "bixelgrid.hpp"
#include "canvaswidget.hpp"
#include "vec2.hpp"
#include "bixelwindow.hpp"
#include "swatch.hpp"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QToolBar>
#include <QToolButton>
#include <QIcon>
#include <QButtonGroup>
#include <QPalette>
#include <QFrame>
#include <QAction>
#include <QGraphicsDropShadowEffect>
#include <QKeySequence>
#include <QMainWindow>
#include <QMenuBar>

int main(int args, char *argv[]) {
    QApplication app(args, argv);
    app.setApplicationName("Bixel");

    BixelWindow* mainWindow = new BixelWindow();

    QWidget* centralWidget = new QWidget();
    mainWindow->setCentralWidget(centralWidget);

        QHBoxLayout* boxLayout = new QHBoxLayout();
        boxLayout->setSpacing(0);
        boxLayout->setContentsMargins(0, 0, 0, 0);

            //-ToolBar-//
            QToolBar* toolBar = new QToolBar();
            toolBar->setOrientation(Qt::Vertical);
            toolBar->setFixedWidth(30);

                QButtonGroup* tools = new QButtonGroup(); 
                tools->setExclusive(true);

                QPushButton* mouse = new QPushButton();
                mouse->setShortcut(QKeySequence("q"));
                mouse->setIcon(QIcon("res/icons/mouse.png"));
                mouse->setCheckable(true);
                mouse->setFixedHeight(30);
                mouse->click();
                toolBar->addWidget(mouse);
                tools->addButton(mouse);
                tools->setId(mouse, BixelGrid::MOUSE);

                QPushButton* paintBrush = new QPushButton();
                paintBrush->setShortcut(QKeySequence("a"));
                paintBrush->setIcon(QIcon("res/icons/paintbrush.png"));
                paintBrush->setCheckable(true);
                paintBrush->setFixedHeight(30);
                toolBar->addWidget(paintBrush);
                tools->addButton(paintBrush);
                tools->setId(paintBrush, BixelGrid::BRUSH);

                QPushButton* eraser = new QPushButton();
                eraser->setShortcut(QKeySequence("z"));
                eraser->setIcon(QIcon("res/icons/eraser.png"));
                eraser->setCheckable(true);
                eraser->setFixedHeight(30);
                toolBar->addWidget(eraser);
                tools->addButton(eraser);
                tools->setId(eraser, BixelGrid::ERASER);

                QPushButton* eyeDrop = new QPushButton();
                //eyeDrop->setShortcut(QKeySequence("z"));
                eyeDrop->setIcon(QIcon("res/icons/eyedrop.png"));
                eyeDrop->setCheckable(true);
                eyeDrop->setFixedHeight(30);
                toolBar->addWidget(eyeDrop);
                tools->addButton(eyeDrop);
                tools->setId(eyeDrop, BixelGrid::EYEDROP);

                QPushButton* hand = new QPushButton();
                hand->setShortcut(QKeySequence("h"));
                hand->setIcon(QIcon("res/icons/hand.png"));
                hand->setCheckable(true);
                hand->setFixedHeight(30);
                toolBar->addWidget(hand);
                tools->addButton(hand);
                tools->setId(hand, BixelGrid::HAND);

                QPushButton* zoom = new QPushButton();
                //zoom->setShortcut(QKeySequence(""));
                zoom->setIcon(QIcon("res/icons/zoom.png"));
                zoom->setCheckable(true);
                zoom->setFixedHeight(30);
                toolBar->addWidget(zoom);
                tools->addButton(zoom);
                tools->setId(zoom, BixelGrid::ZOOM);

                toolBar->addSeparator();

                QToolButton* paintColor = new QToolButton();
                paintColor->setStyleSheet("background-color: rgb(255, 128, 128)");
                toolBar->addWidget(paintColor);

                toolBar->addSeparator();

                Swatch* swatch_1 = new Swatch();
                swatch_1->setColor(0x588C7E);
                toolBar->addWidget(swatch_1);

                Swatch* swatch_2 = new Swatch();
                swatch_2->setColor(0xF2E394);
                toolBar->addWidget(swatch_2);

                Swatch* swatch_3 = new Swatch();
                swatch_3->setColor(0xF2AE72);
                toolBar->addWidget(swatch_3);

                Swatch* swatch_4 = new Swatch();
                swatch_4->setColor(0xD96459);
                toolBar->addWidget(swatch_4);

                Swatch* swatch_5 = new Swatch();
                swatch_5->setColor(0x8C4646);
                toolBar->addWidget(swatch_5);

            boxLayout->addWidget(toolBar);

            //-OpenGL Drawing Canvas-//
            CanvasWidget* canvas = new CanvasWidget(mainWindow);
            canvas->setStyleSheet("background-color: rgb(50, 50, 50)");
            boxLayout->addWidget(canvas);

            QObject::connect(tools, SIGNAL(buttonReleased(int)), canvas, SLOT(changeTool(int)));
            QObject::connect(paintColor, SIGNAL(clicked(bool)), canvas, SLOT(openColorPicker()));
            QObject::connect(canvas, SIGNAL(colorChanged(QString)), paintColor, SLOT(setStyleSheet(QString)));
            QObject::connect(canvas, SIGNAL(stateChanged()), mainWindow, SLOT(stateChanged()));

            QObject::connect(swatch_1, SIGNAL(swatchPicked(QColor)), canvas, SLOT(setCurrentColor(QColor)));
            QObject::connect(swatch_2, SIGNAL(swatchPicked(QColor)), canvas, SLOT(setCurrentColor(QColor)));
            QObject::connect(swatch_3, SIGNAL(swatchPicked(QColor)), canvas, SLOT(setCurrentColor(QColor)));
            QObject::connect(swatch_4, SIGNAL(swatchPicked(QColor)), canvas, SLOT(setCurrentColor(QColor)));
            QObject::connect(swatch_5, SIGNAL(swatchPicked(QColor)), canvas, SLOT(setCurrentColor(QColor)));

            canvas->setCurrentColor(QColor(128, 200, 128));
            if(args >= 2) {
                mainWindow->open_slot(argv[1]);
            }
        centralWidget->setLayout(boxLayout);

    mainWindow->showMaximized();
    return app.exec();
}
