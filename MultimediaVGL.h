#ifndef MULTIMEDIAVGL_H
#define MULTIMEDIAVGL_H

/* 弃用
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QWaitCondition>
#include <QThread>
#include <QTimer>
#include <QMutex>

extern QWaitCondition paintWaiter;

class VideoGL : public QOpenGLWidget ,  protected QOpenGLFunctions
{
    Q_OBJECT

public:
    VideoGL(QWidget* parent=0);
    ~VideoGL();

public slots:
    void start(int);
    void stop();
    void timeoutEvent();
    void paint();

private:
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram program;
    GLuint idY,idU,idV;

    QOpenGLBuffer* pboY,* pboU,* pboV;

    QTimer timer;
    int updateTime;
    int videoW,videoH;
    int realW,realH;

protected:
    void initializeGL() override ;
    void paintGL() override ;
    void resizeGL(int,int) override ;
};

*/

#endif // MULTIMEDIAVGL_H
