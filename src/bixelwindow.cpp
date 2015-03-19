#include "bixelwindow.hpp"
#include <QMenuBar>
#include <QAction>
#include <QKeySequence>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QFileInfo>
#include <QPushButton>
#include <stdio.h>
BixelWindow::BixelWindow(QWidget* parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), m_fileName(""), m_saveUpToDate(true) {
    QMenuBar* mainMenuBar = this->menuBar();

    QMenu* fileMenu = mainMenuBar->addMenu("File");
        new_file = fileMenu->addAction("New");
        new_file->setShortcut(QKeySequence("Ctrl+n"));
        QObject::connect(new_file, SIGNAL(triggered()), this, SIGNAL(new_file_signal()));

        save = fileMenu->addAction("Save");
        this->addAction(save);
        save->setShortcut(QKeySequence("Ctrl+s"));
        QObject::connect(save, SIGNAL(triggered()), this, SLOT(save_slot()));

        save_as = fileMenu->addAction("Save As");
        this->addAction(save_as);
        save_as->setShortcut(QKeySequence("Ctrl+Shift+s"));
        QObject::connect(save_as, SIGNAL(triggered()), this, SLOT(save_as_slot()));

        open = fileMenu->addAction("Open");
        this->addAction(open);
        open->setShortcut(QKeySequence("Ctrl+o"));
        QObject::connect(open, SIGNAL(triggered()), this, SLOT(open_slot()));

        export_image = fileMenu->addAction("Export Image");
        this->addAction(export_image);
        export_image->setShortcut(QKeySequence("Ctrl+e"));
        QObject::connect(export_image, SIGNAL(triggered()), this, SLOT(export_image_slot()));

        preferences = fileMenu->addAction("Preferences");
        preferences->setShortcut(QKeySequence("Ctrl+p"));

    QMenu* editMenu = mainMenuBar->addMenu("Edit");
        undo = editMenu->addAction("Undo");
        this->addAction(undo);
        undo->setShortcut(QKeySequence("Ctrl+z"));
        QObject::connect(undo, SIGNAL(triggered()), this, SIGNAL(undo_signal()));

        redo = editMenu->addAction("Redo");
        this->addAction(redo);
        redo->setShortcut(QKeySequence("Shift+Ctrl+z"));
        QObject::connect(redo, SIGNAL(triggered()), this, SIGNAL(redo_signal()));

        copy = editMenu->addAction("Copy");
        copy->setShortcut(QKeySequence("Ctrl+c"));

        cut = editMenu->addAction("Cut");
        cut->setShortcut(QKeySequence("Ctrl+x"));

        paste = editMenu->addAction("Paste");
        paste->setShortcut(QKeySequence("Ctrl+v"));

        select_all = editMenu->addAction("Select All");
        this->addAction(select_all);
        select_all->setShortcut(QKeySequence("Ctrl+a"));
        QObject::connect(select_all, SIGNAL(triggered()), this, SIGNAL(select_all_signal()));

        deselect_all = editMenu->addAction("Deselect All");
        this->addAction(deselect_all);
        deselect_all->setShortcut(QKeySequence("esc"));
        QObject::connect(deselect_all, SIGNAL(triggered()), this, SIGNAL(deselect_all_signal()));

    QMenu* viewMenu = mainMenuBar->addMenu("View");
        QMenu* zoomMenu = viewMenu->addMenu("Zoom");
            zoom_in = zoomMenu->addAction("Zoom in");
            this->addAction(zoom_in);
            zoom_in->setShortcut(QKeySequence("Ctrl+="));
            QObject::connect(zoom_in, SIGNAL(triggered()), this, SIGNAL(zoom_in_signal()));

            zoom_out = zoomMenu->addAction("Zoom out");
            this->addAction(zoom_out);
            zoom_out->setShortcut(QKeySequence("Ctrl+-"));
            QObject::connect(zoom_out, SIGNAL(triggered()), this, SIGNAL(zoom_out_signal()));

            custom_zoom = zoomMenu->addAction("Custom Zoom");
        reset_view = viewMenu->addAction("Reset View");
        reset_view->setShortcut(QKeySequence("Ctrl+r"));
    setWindowTitle(QString("New File"));
}

BixelWindow::~BixelWindow() {
    QList<QAction*> actionList = actions();
    QList<QAction*>::iterator iter;
    for(iter = actionList.begin(); iter != actionList.end(); iter++) {
        delete (*iter);
    }
}

void BixelWindow::open_slot() {
    if(!m_saveUpToDate) {
        QMessageBox currentFileNotSavedDialog(this);
        currentFileNotSavedDialog.setText("If you continue, you will lose unsaved work. Is this okay?");
        currentFileNotSavedDialog.addButton(QMessageBox::Ok);
        currentFileNotSavedDialog.addButton(QMessageBox::Cancel);
        currentFileNotSavedDialog.exec();
        if(currentFileNotSavedDialog.clickedButton() == currentFileNotSavedDialog.button(QMessageBox::Cancel)) {
            return;
        }
    }
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("All Bixel files (*.bixl)");
    if(dialog.exec()) {
        m_fileName = dialog.selectedFiles()[0].toStdString();
        open_slot(m_fileName);
    }
}

void BixelWindow::open_slot(std::string fileName) {
        setWindowTitle(fileName.c_str());
        emit open_signal(fileName);
        m_saveUpToDate = true;
}

void BixelWindow::export_image_slot() {
    QStringList filters;
    filters << "All files (*)";
    filters << "png (*.png)";

    QFileDialog dialog(this);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setDefaultSuffix("png");
    dialog.setNameFilters(filters);

    QString fileName;
    if(dialog.exec()) {
        fileName = dialog.selectedFiles()[0];
        QFileInfo file(fileName);
    }

    emit export_image_signal(fileName.toStdString());
}

void BixelWindow::save_as_slot() {
    QStringList filters;
    filters << "All files (*)";
    filters << "Bixel (*.bixl)";

    QFileDialog dialog(this);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    //dialog.setConfirmOverwrite(true);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setDefaultSuffix("bixl");
    dialog.setNameFilters(filters);

    if(dialog.exec()) {
        m_fileName = dialog.selectedFiles()[0].toStdString();
        QFileInfo file(QString(m_fileName.c_str()));
        std::string suffix = file.suffix().toStdString();
        if(suffix.compare("bixl") != 0) {
            QMessageBox wrongSuffixDialog(this);
            wrongSuffixDialog.setText(QString("You have specified a non-default file extension."));
            wrongSuffixDialog.setInformativeText(QString(("Are you sure you want to replace the default 'bixl' \
file extension and use '" + suffix + "' instead?").c_str()));

            QPushButton* useSuffix = wrongSuffixDialog.addButton(QString(("Use " + suffix).c_str()), QMessageBox::AcceptRole);
            QPushButton* useBixl = wrongSuffixDialog.addButton(QString("Use bixl"), QMessageBox::AcceptRole);
            wrongSuffixDialog.exec();
            delete useSuffix;
            delete useBixl;

            if(wrongSuffixDialog.clickedButton()->text() == useBixl->text()) {
                m_fileName = file.baseName().toStdString() + ".bixl";
                dialog.selectFile(QString(m_fileName.c_str()));
                dialog.exec();
            }

        }
        emit save_as_signal(m_fileName);
        m_saveUpToDate = true;
        setWindowTitle(QString(m_fileName.c_str()));
    }
}

void BixelWindow::save_slot() {
    if(m_fileName != "") {
        m_saveUpToDate = true;
        emit save_as_signal(m_fileName);
        setWindowTitle(QString(m_fileName.c_str()));
    } else {
        save_as_slot();
    }
}

void BixelWindow::stateChanged() {
    if(m_saveUpToDate) {
        QString fileUnsavedName = windowTitle();
        fileUnsavedName += "*";
        setWindowTitle(fileUnsavedName);
    }
    m_saveUpToDate = false;
}
