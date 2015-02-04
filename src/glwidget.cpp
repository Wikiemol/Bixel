#include <stdio.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>
#include <iterator>
#include <QFile>
#include <QString>
#include "glwidget.hpp"
#include "canvaswidget.hpp"
#include "logger.hpp"

//-Public-//
/**
 * @brief Initializes the GLWidget with a parent widget.
 *
 * The constructor initializes all private fields. It then calls #saveHistoryState,
 * QWidget::setFocus, and QWidget::setFocusPolicy(Qt::StrongFocus).
 *
 * @param parent    The parent QWidget.
 */

GLWidget::GLWidget(QWidget* parent) : QGLWidget(QGLFormat(), parent), 
                                      m_dimension(2),
                                      m_gridWidth(m_dimension),
                                      m_gridHeight(m_dimension),
                                      m_currentState(0),
                                      m_bixelWidth(this->width() / (float) (m_gridWidth)),
                                      m_backgroundColor(0, 0, 0),   
                                      m_colorMatrix(m_gridWidth * m_gridHeight, QColor(0, 0, 0, 0)),
                                      m_selectedBixels()
                                      {
    saveHistoryState();
    setFocus();
    setFocusPolicy(Qt::StrongFocus);
}
GLWidget::~GLWidget() {}

//-Public Rendering Functions-//

/**
 * This method draws a square using squareShader.vert and squareShader.frag.
 *
 * @param color         The rgba color of the square.
 *
 * @param position      This attribute specifies the bottom
 *                      left corner of the square. It should
 *                      be a position relative to the Widget
 *                      as it will be normalized for OpenGL.
 *
 * @param outlineOnly   If true, GL_LINE_LOOP will be used to
 *                      draw only the outline of the square.
 */


void GLWidget::drawSquare(QColor color,
                          vec2 position,
                          double size,
                          bool outlineOnly) {

    vec2 nPosition = normalizeCoordinates(position);
    double nWidth = 2 * size / ((double) this->width());
    double nHeight = 2 * size / ((double) this->height());

    float squareVertices[8] = {
                          (float) nPosition.x, (float) nPosition.y,
                          (float) (nPosition.x + nWidth), (float) nPosition.y,
                          (float) (nPosition.x + nWidth), (float) (nPosition.y + nHeight),
                          (float) nPosition.x, (float) (nPosition.y + nHeight)
                        };
    m_squareProgram.bind();

    m_squareProgram.setUniformValue("color", color.red() / 255.0, color.green() / 255.0, color.blue() / 255.0, color.alpha() / 255.0);
    m_squareProgram.setAttributeArray("position", squareVertices, 2);
    if(outlineOnly) {
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    } else {
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
    m_squareProgram.release();
}

//----------------------------------//
/** @name Public Access Methods */
//----------------------------------//


/** 
 * This returns the main colorMatrix as a 2d vector.
 * @todo Copy m_colorMatrix into a 2d vector and
 *       return that instead of the raw colorMatrix.
 * @todo Maybe create setters for colorMatrix.
 */
std::vector<QColor> GLWidget::colorMatrix() {
    return m_colorMatrix;
}

/**
 *  Returns a set of all of the Bixels currently selected.
 *  This needs to be its own set because we want to quickly
 *  - fill a selection with #fillSelected without redrawing
 *    everything.
 *  - insert new selections without redrawing everything
 *  - remove selections without redrawing everything
 *
 *  Having each member of colorMatrix have its own selection
 *  attribute would mean that we would have to redraw
 *  the entire screen everytime we selected or deselected.
 *  @see MOUSE
 */
std::set<GLWidget::ColorMatrixIndex> GLWidget::selectedBixels() {
    return m_selectedBixels;
}

/**
 * @brief The dimension of the GLWidget is the smallest
 *        of #gridWidth and #gridHeight.
 *
 * @todo Get rid of this. See #increaseDimension todos.
 */
int GLWidget::dimension() {
    return m_dimension;
}

/**
 * This is the current width of the grid
 * containing the Bixels. This will always
 * be a multiple of 2.
 */
int GLWidget::gridWidth() {
    return m_gridWidth;
}

/**
 * This is the current height of the grid
 * containing the Bixels. This will always
 * be a multiple of 2.
 */
int GLWidget::gridHeight() {
    return m_gridHeight;
}

/**
 * This is the current color used by 
 * the BRUSH tool.
 */
QColor GLWidget::drawingColor() {
    return m_drawingColor;
}

/**
 * This returns the color of the Bixel in #colorMatrix 
 * at @p i and @p j.
 *
 * @param i     The number of Bixels from the left of the Bixel Grid.
 * @param j     The number of Bixels from the **bottom** of the Bixel Grid.
 */
QColor GLWidget::getColorAt(int i, int j) {
    return m_colorMatrix[colorMatrixIndex(i, j)];
}

/**
 * Returns the tool the user is currently
 * using.
 */
GLWidget::DrawTool GLWidget::tool() {
    return m_currentTool;
}
///@}

//------------------------------------//
/** @name Public Mutator Methods*/
//------------------------------------//

/**
 * Changes the current tool being used to update
 * the widget.
 *
 * @see GLWidget::mousePressEvent(QEvent*)
 * @see GLWidget::mouseMoveEvent(QEvent*)
 */

void GLWidget::changeTool(GLWidget::DrawTool tool) {
    m_currentTool = tool;
}

/**
 * Sets a color at (@p i, @p j) in #colorMatrix to @p color.
 */
void GLWidget::setColorAt(int i, int j, QColor color) {
    setColorAt(colorMatrixIndex(i, j), color);
}

void GLWidget::setColorAt(ColorMatrixIndex i, QColor color) {
    m_colorMatrix[i] = color;
}

/**
 * Sets the current drawing color used by BRUSH, PAINTBUCKET,
 * and #fillSelected.
 * @see drawingColor()
 */
void GLWidget::setDrawingColor(const QColor& color) {
    m_drawingColor = color;
}

///@}

/** @name Public Bixel Selectors 
 *  
 *  These are all methods that add or remove 
 *  Bixels from #selectedBixels.
 */

/**
 *  This will change the color in 
 *  #colorMatrix of all of the
 *  Bixels in #selectedBixels to 
 *  #drawingColor.
 */
void GLWidget::fillSelected() {
    std::set<int>::iterator iter = m_selectedBixels.begin();
    for(; iter != m_selectedBixels.end(); iter++) {
        setColorAt(*iter, drawingColor());
    }
}

/**
 * This will add a Bixel index (@p i, @p j) to #selectedBixels if
 * it is not already selected.
 */
void GLWidget::selectBixelAt(int i, int j) {
    selectBixelAt(colorMatrixIndex(i, j));
}

void GLWidget::selectBixelAt(ColorMatrixIndex i) {
    m_selectedBixels.insert(i);
}

/**
 * This will remove a Bixel index (@p i, @p j) from #selectedBixels
 * if it is already selected. 
 */
void GLWidget::deselectBixelAt(int i, int j) {
    ColorMatrixIndex bixelIndex = colorMatrixIndex(i, j);
    m_selectedBixels.erase(bixelIndex);
}

/**
 * This will clear the set of Bixels in
 * #selectedBixels. It will also call
 * #paintGL.
 */
void GLWidget::deselectAll() {
    m_selectedBixels.clear();
    paintGL();
}

/**
 * This will add every Bixel index to 
 * #selectedBixels. Calls #paintGL.
 */
void GLWidget::selectAll() {
    int i;
    int j;
    for(i = 0; i < m_gridWidth; i++) {
        for(j = 0; j < m_gridHeight; j++) {
            selectBixelAt(i, j);
        }
    }
    paintGL();
}

/**
 * Adds all Bixels within a rectangle between the @p point1 and @p point2
 * to the #selectedBixels. If either point is out of bounds,
 * it will be set to the closest bixel that is in bounds.
 *
 * @param p1    The top left corner of the rectangle to be selected.
 * @param p2    The bottom right corner of the rectangle to be selected. 
 */
void GLWidget::selectRectangle(const std::vector<ColorMatrixIndex>& point1,
                               const std::vector<ColorMatrixIndex>& point2) {
    std::vector<ColorMatrixIndex> p1 = point1;
    std::vector<ColorMatrixIndex> p2 = point2;

    //x boundaries
    if(p1[0] >= m_gridWidth)
        p1[0] = m_gridWidth - 1;
    if(p1[0] < 0)
        p1[0] = 0;
    //y boundaries
    if(p1[1] >= m_gridWidth)
        p1[1] = m_gridWidth - 1;
    if(p1[1] < 0)
        p1[1] = 0;

    //x boundaries
    if(p2[0] >= m_gridWidth)
        p2[0] = m_gridWidth - 1;
    if(p2[0] < 0)
        p2[0] = 0;

    //y boundaries
    if(p2[1] >= m_gridWidth)
        p2[1] = m_gridWidth - 1;
    if(p2[1] < 0)
        p2[1] = 0;

    int min_i = std::min(p1[0], p2[0]);
    int max_i = std::max(p1[0], p2[0]);
    int min_j = std::min(p1[1], p2[1]);
    int max_j = std::max(p1[1], p2[1]);
    int i;
    int j;
    for(i = min_i; i <= max_i; i++) {
        for(j = min_j; j <= max_j; j++) {
            selectBixelAt(i, j);
        }
    }
}
///@}

/**
 * @brief This will load a file @p fileName using QDataStream version (Qt 4.9).
 *
 * The file specified will be read as if it was created with
 * #saveFile. This method calls #paintGL.
 *
 * @return          
 *                  - true if @p fileName was successfully opened
 *                  - false if @p fileName doesn't exist or could not
 *                    be opened
 */

bool GLWidget::openFile(const std::string& fileName) {
    QFile file(QString(fileName.c_str()));
    if(!file.exists()) {
        fprintf(stderr, "File %s does not exist.\n", fileName.c_str());
        return false;
    }
    if(!file.open(QIODevice::ReadOnly)) {
        fprintf(stderr, "Failed to open file %s\n.", fileName.c_str());
        return false;
    }
    QDataStream fileIn(&file);
    fileIn.setVersion(QDataStream::Qt_4_9);

    fileIn >> m_dimension;
    fileIn >> m_gridWidth;
    fileIn >> m_gridHeight;
    int i;
    m_colorMatrix.clear();
    for(i = 0; i < m_gridWidth * m_gridHeight; i++) {
        int r, g, b, a;
        fileIn >> r;
        fileIn >> g;
        fileIn >> b;
        fileIn >> a;
        m_colorMatrix.push_back(QColor(r, g, b, a));
    }
    m_bixelWidth = calculateBixelWidth();
    paintGL();
    return true;
}

/**
 * @brief This will save a file @p fileName using QDataStream version (Qt 4.9).
 *
 * The #dimension, #gridWidth, and #gridHeight are written first as
 * qint32 integers. Then each red, green, blue, and alpha component
 * of every QColor in #colorMatrix are written as qint32 integers.
 *
 * @returns 
 *                      - true if saving succeeded
 *                      - false otherwise
 */
bool GLWidget::saveFile(const std::string& fileName) {
    QFile file(QString(fileName.c_str()));
    if(!file.open(QIODevice::WriteOnly)) {
        fprintf(stderr, "Failed to open file %s.\n", fileName.c_str());
        return false;
    }
    QDataStream fileOut(&file);
    fileOut.setVersion(QDataStream::Qt_4_9);
    fileOut << (qint32) m_dimension;
    fileOut << (qint32) m_gridWidth; 
    fileOut << (qint32) m_gridHeight;
    ColorMatrixIndex i;
    for(i = 0; i < (int) m_colorMatrix.size(); i++) {
        fileOut << (qint32) m_colorMatrix[i].red();
        fileOut << (qint32) m_colorMatrix[i].green();
        fileOut << (qint32) m_colorMatrix[i].blue();
        fileOut << (qint32) m_colorMatrix[i].alpha();
    }

    file.flush();
    file.close();
    return true;
}

/**
 * @brief This will multiply the #dimension of the widget by 2.
 *
 * This will also update the #gridWidth and the #gridHeight.
 *
 * @todo The way I have been dealing with #dimension is ridiculous.
 *       Get rid of m_dimension altogether and use only #gridWidth
 *       and #gridHeight. Create an increaseWidth() and an increaseHeight()
 *       as well as a decreaseWidth/Height.
 */
void GLWidget::increaseDimension() {
    if(m_dimension >= 64) {
        m_dimension = 64;
        return;
    }
    int oldGridWidth = m_gridWidth;
    int oldGridHeight = m_gridHeight;
    //int oldDimension = m_dimension;

    m_dimension = m_dimension * 2;
    m_gridWidth = m_gridWidth * 2;
    m_gridHeight = m_gridHeight * 2;
    m_bixelWidth = calculateBixelWidth();

    std::vector<QColor> newColorMatrix(m_gridWidth * m_gridHeight, QColor(0, 0, 0, 0));
    m_colorMatrix.resize(m_gridWidth * m_gridHeight, QColor(0, 0, 0, 0));

    int i;
    int j;
    for(i = 0; i < oldGridWidth; i++) { 
        for(j = 0; j < oldGridHeight; j++) {
            newColorMatrix[colorMatrixIndex(i, j)] = m_colorMatrix[oldGridHeight * i + j];
        }
    }

    m_colorMatrix = newColorMatrix;
}

/**
 * @todo Get rid of this. See the todos in #increaseDimension.
 */

void GLWidget::decreaseDimension() {
    if(m_dimension <= 1) {
        m_dimension = 1;
        return;
    }
    //int oldDimension = m_dimension;
    //int oldGridWidth = m_gridWidth;
    int oldGridHeight = m_gridHeight;

    m_dimension = m_dimension / 2;
    m_gridWidth = m_gridWidth / 2;
    m_gridHeight = m_gridHeight / 2;
    m_bixelWidth = calculateBixelWidth();

    std::vector<QColor> newColorMatrix(m_gridWidth * m_gridHeight, QColor(0, 0, 0, 0));
    m_colorMatrix.resize(m_gridWidth * m_gridHeight);

    int i;
    int j;
    for(i = 0; i < m_gridWidth; i++) { 
        for(j = 0; j < m_gridHeight; j++) {
            newColorMatrix[colorMatrixIndex(i, j)] = m_colorMatrix[oldGridHeight * i + j];
        }
    }
    m_colorMatrix = newColorMatrix;
}

/**
 * @brief An implementation of the undo function.
 *
 * Moves the #currentState counter back one
 * if the counter is greater than 0.
 * This method calls #paintGL.
 *
 * @todo add CurrentState access method
 */
void GLWidget::undo() {
    if(m_currentState > 0) {
        m_currentState--;
    }
    loadHistoryState(m_currentState);
    paintGL();
}

/**
 * @brief An implementation of redo.
 *
 * Moves the #currentState counter forward
 * if it is less than the number of states
 * that have been saved.
 */
void GLWidget::redo() {
    if(m_currentState < ((int) m_history.size()) - 1) {
        m_currentState++;
    }
    loadHistoryState(m_currentState);
    paintGL();
}


//-Protected Polymorphs-//
/**
 * @todo Make this private.
 */
void GLWidget::initializeGL() {
    if(glewInit() != GLEW_OK) {
        fprintf(stderr, "GLEW failed to initialize.");
    }

    m_lineProgram.addShaderFromSourceFile(QGLShader::Vertex, "res/shaders/lineShader.vert");
    m_lineProgram.addShaderFromSourceFile(QGLShader::Fragment, "res/shaders/lineShader.frag");
    m_lineProgram.link();

    m_squareProgram.addShaderFromSourceFile(QGLShader::Vertex, "res/shaders/squareShader.vert");
    m_squareProgram.addShaderFromSourceFile(QGLShader::Fragment, "res/shaders/squareShader.frag");
    m_squareProgram.link();
    m_squareProgram.enableAttributeArray("position");

    setAutoBufferSwap(false);
}

/**
 * @callergraph
 *
 * Updates the screen. 
 *
 * @todo Give Bixel drawing work to OpenGL.
 *       Use one Mesh instead of many calls
 *       to GL_DRAW_ARRAYS
 */
void GLWidget::paintGL() {
    olilog::log("update screen");
    m_lineProgram.bind();
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    m_lineProgram.release();

    //Drawing 'Bixels', we will give this work to OpenGL in the future.
    //not really sure what I was thinking drawing each square individually.
    int i;
    int j;
    for(i = 0; i < m_gridHeight; i++) {
        for(j = 0; j < m_gridWidth; j++) {
            QColor thisColor = getColorAt(j, i);
            vec2 position = vec2(j*m_bixelWidth, 
                                 i*m_bixelWidth);

            if(thisColor.alpha() != 0) {
                drawSquare(thisColor, 
                           position,
                           m_bixelWidth);
            } else {
                drawSquare(m_backgroundColor,
                           position,
                           m_bixelWidth,
                           false);

                
                drawSquare(QColor(20, 20, 20),
                           position,
                           m_bixelWidth,
                           true);
            }
        }
    }

    std::set<int>::iterator iter;
    for(iter = m_selectedBixels.begin(); iter != m_selectedBixels.end(); iter++) {
        ColorMatrixIndex bixelSelected = (*iter);

        int i = bixelSelected / m_gridHeight;
        int j = bixelSelected % m_gridHeight;

        vec2 position = vec2(i*(m_bixelWidth), 
                             j*(m_bixelWidth));

        QColor thisColor = m_colorMatrix[bixelSelected];

        if(thisColor.red() + 20 > 255) {
            thisColor.setRed(255);
        } else {
            thisColor.setRed(thisColor.red() + 20);
        }

        if(thisColor.green() + 20 > 255) {
            thisColor.setGreen(255);
        } else {
            thisColor.setGreen(thisColor.green() + 20);
        }

        if(thisColor.blue() + 20 > 255) {
            thisColor.setBlue(255);
        } else {
            thisColor.setBlue(thisColor.blue() + 20);
        }

        thisColor.setAlpha(255);

        drawSquare(thisColor,
                   position,
                   m_bixelWidth,
                   false);
        drawSquare(QColor(255, 255, 200),
                   position,
                   m_bixelWidth,
                   true);
    }

    swapBuffers();
}

/**
 * Called whenever the widget is resized.
 * Overrides resizeGL in QGLWidget
 */
void GLWidget::resizeGL(int width, int height) {
    olilog::log("Resizing Screen");
    if(height == 0) { 
        height = 1;
    }
    if(width == 0) {
        width = 1;
    }
    glViewport(0, 0, width, height);
    m_bixelWidth = calculateBixelWidth();
}  


//-Protected Event Handlers-//

/**
 * This method is overwridden from QGLWidget.
 * Called whenever the mouse is pressed within
 * the GLWidget.
 */
void GLWidget::mousePressEvent(QMouseEvent* event) {
    olilog::log("Mouse Pressed");
    std::vector<int> index = convertPositionToBixelIndex(event->x(), event->y());
    switch(m_currentTool) {
        case BRUSH:
            setColorAt(index[0], index[1], m_drawingColor);
            paintGL();
        break;
        case ERASER:
            setColorAt(index[0], index[1], QColor(0, 0, 0, 0));
            paintGL();
        break;
        case MOUSE:
            if((event->modifiers() & Qt::ControlModifier) == Qt::ControlModifier) {
                m_currentMouseIndex = index;
                deselectBixelAt(index[0], index[1]);
            } else {
                m_clickIndex = index;
                m_currentMouseIndex = index;
                selectRectangle(m_clickIndex, m_currentMouseIndex);
            }
            paintGL();
        break;

        default:
            //- Do nothing
        break;
    }
}

/**
 * This method is overridden from QGLWidget.
 * Called whenever the #mousePressEvent has been called
 * abd #mouseReleaseEvent hasn't. 
 */
void GLWidget::mouseMoveEvent(QMouseEvent* event) {
    olilog::log("Mouse Mouse Moved");
    std::vector<int> index = convertPositionToBixelIndex(event->x(), event->y());

    if(index[0] >= m_gridWidth) {
        index[0] = m_gridWidth - 1;
    }
    if(index[0] < 0) {
        index[0] = 0;
    }
    if(index[1] >= m_gridHeight) {
        index[1] = m_gridHeight - 1;
    }
    if(index[1] < 0) {
        index[1] = 0;
    }

    if(index != m_currentMouseIndex) {
        m_currentMouseIndex = index;
        switch(m_currentTool) {
            case BRUSH:
                setColorAt(index[0], index[1], m_drawingColor);
                paintGL();
            break;
            case ERASER:
                setColorAt(index[0], index[1], QColor(0, 0, 0, 0));
                paintGL();
            break;
            case MOUSE:
                if((event->modifiers() & Qt::ControlModifier) == Qt::ControlModifier) {
                    deselectBixelAt(index[0], index[1]);
                } else if ((event->modifiers() & Qt::ShiftModifier) == Qt::ShiftModifier) {
                    selectRectangle(m_clickIndex,
                                 m_currentMouseIndex);
                } else if((event->modifiers() & Qt::AltModifier) == Qt::AltModifier) {
                    selectBixelAt(m_currentMouseIndex[0], m_currentMouseIndex[1]);
                }else {
                    m_selectedBixels.clear();
                    selectRectangle(m_clickIndex,
                                 m_currentMouseIndex);
                }
                paintGL();
            break;
            default:
                //- Do nothing
            break;
        }
    }
}

/**
 *  @brief Called whenever the mouse is released.
 *
 *  We assume that whenever the mouse is released,
 *  there has been a change that we want to save,
 *  so we #saveHistoryState.
 */

void GLWidget::mouseReleaseEvent(QMouseEvent* ) {
    saveHistoryState();
}

/**
 * @brief Called whenever a Key is pressed.
 *
 * This method contains method calls depending on
 * the Key pressed.
 *
 * - **Backspace**: Erases selected Bixels
 * - **Return**: #fillSelected
 * - **Left Square Bracket**: #increaseDimension
 * - **Right Square Bracket**: #decreaseDimension
 */
void GLWidget::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
        case Qt::Key_Backspace:
        {
            std::set<int>::iterator iter;
            for(iter = m_selectedBixels.begin(); iter != m_selectedBixels.end(); iter++) {
                setColorAt(*iter, QColor(0, 0, 0, 0));
            }
            paintGL();
        }
        break;
        case Qt::Key_Return:
            fillSelected();
            paintGL();
        break;
        case Qt::Key_BracketLeft:
            increaseDimension();
            paintGL();
        break;
        case Qt::Key_BracketRight:
            decreaseDimension();
            paintGL();
        break;
    }
}

/**
 * Called whenever a key is released 
 * and focus is on this widget.
 */
void GLWidget::keyReleaseEvent(QKeyEvent*) {
    saveHistoryState();
}

//-Protected Utility Functions-//

/**
 * @brief Saves the current state of the GLWidget.
 * 
 * Will save the #gridWidth, #gridHeight, #dimension, #colorMatrix,
 * and #selectedBixels into a HistoryState and push it into 
 * the history. This is called on every #keyReleaseEvent
 * as well as every #mouseReleaseEvent.
 *
 * Currently the max number of states that can be saved is 99.
 *
 * @see HistoryState
 */
void GLWidget::saveHistoryState() {
    HistoryState stateToSave = HistoryState(this);

    if(m_history.size() == 0) {
        emit stateChanged();
        m_history.push_back(stateToSave);
        return;
    }

    if(m_history[m_currentState] == stateToSave) {
        return;
    }

    if(m_currentState < ((int) m_history.size()) - 1) {
        int i;
        for(i = m_currentState; i < (int) m_history.size(); i++) {
            m_history.pop_back();
        }
    }

    if(m_history.size() < 99) {
        m_currentState++;
        m_history.push_back(stateToSave);
    } else {
        m_history.pop_front();
        m_history.push_back(stateToSave);
    }

    emit stateChanged();
}

/**
 * Loads state specified by @p stateIndex in #history.
 *
 * @returns     
 *              - @c false if the @p stateIndex is larger than
 *                the history or if there is nothing in 
 *                the history
 *              - @c true otherwise
 * @todo        Create history access.
 */
bool GLWidget::loadHistoryState(int stateIndex) {
    if(stateIndex >= (int) m_history.size() || m_history.size() <= 1) {
        return false;
    }

    HistoryState stateToLoad = m_history[stateIndex];
    m_dimension = stateToLoad.dimension_state;
    m_gridWidth = stateToLoad.gridWidth_state;
    m_gridHeight = stateToLoad.gridHeight_state;
    m_colorMatrix = stateToLoad.colorMatrix_state;
    m_selectedBixels = stateToLoad.selectedBixels_state;
    m_bixelWidth = calculateBixelWidth();
    return true;
}

void GLWidget::markBixelAt(int i, int j) {
}

void GLWidget::markBixelAt(ColorMatrixIndex i) {
}

/**
 * Converts a 2d matrix index to a vector index to be used with #colorMatrix.
 *
 * @returns     A ColorMatrixIndex int to be used when accessing an
 *              element of #colorMatrix directly, or searching #selectedBixels.
 */
GLWidget::ColorMatrixIndex GLWidget::colorMatrixIndex(int i, int j) const {
    if(m_colorMatrix.size() != (unsigned)m_gridWidth * m_gridHeight) {
        fprintf(stderr, "colorMatrix of size %lu has not been resized to fit %d x %d. Exiting.\n", 
                         m_colorMatrix.size(), m_gridWidth, m_gridHeight);
        exit(1);
    }
    if((unsigned) (m_gridHeight * i + j) > m_colorMatrix.size()) {
        fprintf(stderr, "Error: ColorMatrixIndex (%d, %d) is out of bounds of %d x %d colorMatrix. Exiting.\n", i, j, m_gridWidth, m_gridHeight);
        exit(1);
    }


    return m_gridHeight*i + j;
}

/**
 * Converts Widget coordinates to openGL coordinates. 
 * @param coord     A vector containing the position relative
 *                  to the GLWidget. 
 * @return          The coordinates normalized with respect to
 *                  the widget's width and height.
 * @todo            Make normalizeCoordinates private
 */
vec2 GLWidget::normalizeCoordinates(vec2 coord) const {
    vec2 newCoords(2.0 * (coord.x / this->width()) - 1.0,
                   2.0 * (coord.y / this->height()) - 1.0);
    return newCoords;
}

//-Private Utility Functions-//


/**
 * Converts a position relative to the Widget to an index of
 * #colorMatrix.
 *
 * @return      A vector of the form <i, j>
 */
std::vector<int> GLWidget::convertPositionToBixelIndex(int x, int y) const {
    std::vector<int> index(2, 0);
    index[0] = (int) (x / m_bixelWidth);
    index[1] = (m_gridHeight - 1) - (int) (y / m_bixelWidth);
    return index; 
}


/**
 * Returns the width of one cell in #colorMatrix relative
 * to GLWidget.
 */
float GLWidget::calculateBixelWidth() {
    return this->width() / ((float) m_gridWidth);
}
