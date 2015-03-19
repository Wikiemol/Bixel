#ifndef BIXELWINDOW_HPP
#define BIXELWINDOW_HPP

#include <QMainWindow>
#include <QAction>

/**
 * @todo Figure out how to keep focus on glWidget. Maybe make al glWidget keyboard actions QActions in the menu?
 */
class BixelWindow : public QMainWindow {
    Q_OBJECT
    public:

        //File
        QAction* new_file;
        QAction* save;
        QAction* save_as;
        QAction* open;
        QAction* export_image;
        QAction* preferences;
        QAction* undo;
        QAction* redo;

        //Edit
        QAction* copy;
        QAction* cut;
        QAction* paste;
        QAction* select_all;
        QAction* deselect_all;

        //View
        QAction* reset_view;
        //View->zoom
        QAction* zoom_in;
        QAction* zoom_out;
        QAction* custom_zoom;

        BixelWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);
        ~BixelWindow();

    public slots:
        void open_slot(std::string fileName);
    private slots:
        void open_slot();
        void save_as_slot();
        void save_slot();
        void export_image_slot();
        void stateChanged();

    signals:
        //File
        void new_file_signal();
        void save_signal();
        void save_as_signal(const std::string& fileName);
        void open_signal(const std::string& fileName);
        void export_image_signal(const std::string& fileName);
        void preferences_signal();
        void undo_signal();
        void redo_signal();

        //Edit
        void copy_signal();
        void cut_signal();
        void paste_signal();
        void select_all_signal();
        void deselect_all_signal();

        //View
        void reset_view_signal();
        //View->zoom
        void zoom_in_signal();
        void zoom_out_signal();
        void custom_zoom_signal();
    private:
        std::string m_fileName;
        bool m_saveUpToDate;
};
#endif
