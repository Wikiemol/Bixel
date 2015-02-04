#ifndef GLWIDGET_HPP
#define GLWIDGET_HPP

#include <GL/glew.h>
#include <QGLWidget>
#include <QGLShaderProgram>
#include <QColor>
#include <string>
#include <stdio.h>
#include <vector>
#include <deque>
#include <set>
#include "vec2.hpp"

/** @task Adding a m_markedBixels vector that will contain every 
 *        Bixel that has been changed since the last call
 *        to #paintGL.
 *        - Create the member variable ***
 *        - Create a markBixel(int i, int j) method
 *        - Go through every mutator of #colorMatrix
 *          and add a call to markBixel(int i, int j)
 *        - Update paintGL to draw only the bixels that have
 *          been marked.
 */

/**
 *  @brief A Widget for rendering and drawing Bixels.
 *
 *  The GLWidget is used as the canvas for the user to
 *  draw and edit .bixl files using various tools. The
 *  Widget is defined by a grid of width 
 *  #gridWidth and height #gridHeight.
 *
 *  @see        CanvasWidget
 *  @todo1      Make sure delicate members like m_colorMatrix
 *              and m_selectedBixels are only accessed through
 *              accessor and mutator methods.
 *  @todo       Rename this class to BixelGrid or something
 */

class GLWidget : public QGLWidget {
    Q_OBJECT


    typedef int ColorMatrixIndex;
    public:

        /** Represents the tools in the toolbar 
         *  @see  CanvasWidget::changeTool(int)
         *  @see  GLWidget::changeTool(int)
         *  @todo Move HAND and ZOOM to an enum
         *        in CanvasWidget.
         *  @todo Implement EYEDROP
         *  @todo Add a PaintBucket tool.
         *  @todo Add a Magic wand tool.
         *  @todo Flesh out tools enum documentation
         */
        enum DrawTool { MOUSE,  ///< Used to select Bixels
                        BRUSH, ///<  Used to Color Bixels
                        PAINTBUCKET, 
                        ERASER, ///< Used to set Bixel color to (0, 0, 0, 0)
                        EYEDROP, ///< The Eyedrop Tool
                        HAND, ///< The Hand Tool
                        ZOOM ///< The Zoom Tool
                       }; 


        GLWidget(QWidget* parent = 0);
        ~GLWidget();
        void drawSquare(QColor color, 
                        vec2 position,
                        double size,
                        bool outlineOnly = false);
        void fillSelected();
        void markBixelAt(int i, int j);
        void markBixelAt(ColorMatrixIndex i);
        void selectBixelAt(int i, int j);
        void selectBixelAt(ColorMatrixIndex i);
        void deselectBixelAt(int i, int j);
        void deselectAll();
        void selectAll();
        void selectRectangle(const std::vector<int>& p1,
                             const std::vector<int>& p2);
        bool saveFile(const std::string& fileName);
        bool openFile(const std::string& fileName);

        //Access Methods
        QColor getColorAt(int i, int j);
        DrawTool tool();
        int dimension();
        int gridWidth();
        int gridHeight();
        QColor drawingColor();
        std::vector<QColor> colorMatrix();
        std::set<ColorMatrixIndex> selectedBixels();

        //Mutator Methods
        void changeTool(DrawTool tool);
        void setColorAt(int i, int j, QColor color);
        void setColorAt(ColorMatrixIndex i, QColor color);
        void setDrawingColor(const QColor& color);

        void increaseDimension();
        void decreaseDimension();
        void undo();
        void redo();

    protected:
        /**
         * @brief This struct stores the current state of a GLWidget.
         *
         * The struct stores the width and height of the Bixel Grid,
         * the dimension of the Bixel grid, the color of every
         * Bixel, and all of the selected Bixels.
         *
         * @see GLWidget
         * @see GLWidget::saveHistoryState()
         * @see GLWidget::loadHistoryState(int)
         * @see GLWidget::undo()
         * @see GLWidget::redo()
         */

        struct HistoryState {
            int dimension_state;
            int gridWidth_state;
            int gridHeight_state;
            std::vector<QColor> colorMatrix_state;
            std::set<int> selectedBixels_state;

            /**
             * The History state constructor takes a snapshot
             * of the current Widget, saving all of the important
             * attributes.
             * @param widgetToSave      A pointer to the widget
             *                          to be saved.
             */
            HistoryState(GLWidget* widgetToSave) {
                dimension_state = widgetToSave->dimension();
                gridWidth_state = widgetToSave->gridWidth();
                gridHeight_state = widgetToSave->gridHeight();
                colorMatrix_state = widgetToSave->colorMatrix();
                selectedBixels_state = widgetToSave->selectedBixels();
            }

            bool operator==(HistoryState b) {
                if (b.dimension_state == dimension_state &&
                    b.gridWidth_state == gridWidth_state &&
                    b.gridHeight_state == gridHeight_state &&
                    b.colorMatrix_state == colorMatrix_state &&
                    b.selectedBixels_state == selectedBixels_state) {
                    return true;
                }
                return false;
            }
        };

        void initializeGL();
        void paintGL();
        void resizeGL(int width, int height);
        void mousePressEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void keyPressEvent(QKeyEvent* event);
        void keyReleaseEvent(QKeyEvent*);

        void saveHistoryState();
        bool loadHistoryState(int stateIndex);
        ColorMatrixIndex colorMatrixIndex(int i, int j) const;
        vec2 normalizeCoordinates(vec2 coord) const;

    signals:
        void stateChanged();

    private:

        /// @cond PRIVATE_FIELDS 
        //-Shader Programs-//
        QGLShaderProgram m_lineProgram;
        QGLShaderProgram m_squareProgram;

        int m_dimension;
        int m_gridWidth;
        int m_gridHeight;
        DrawTool m_currentTool;
        int m_currentSize;
        int m_currentState;
        float m_bixelWidth;
        QColor m_drawingColor;
        QColor m_backgroundColor;
        std::vector<int> m_currentMouseIndex;
        std::vector<int> m_clickIndex;

        // Access a color at an index in
        // this vector only with a 
        // ColorMatrixIndex.
        std::vector<QColor> m_colorMatrix; 

        // Stores the bixels that are selected.
        std::set<int> m_selectedBixels;

        // Stores the bixels that have been changed.
        std::set<int> m_markedBixels;
        std::deque<HistoryState> m_history;

        ///@endcond

        std::vector<int> convertPositionToBixelIndex(int x, int y) const;
        float calculateBixelWidth();
};


#endif
