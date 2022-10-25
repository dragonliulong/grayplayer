/*弃用

#include "MultimediaVGL.h"
#include "MultimediaResource.h"
#include "MultimediaTime.h"
#include <QSurface>
#include <QSurfaceFormat>
#include <QLayout>
#include <QResizeEvent>

QWaitCondition paintWaiter;

//------------------------------------------------------------------------------------------------------------

#define GET_GLSTR(x) "#version 330 core\n"#x

const char* vsrc = GET_GLSTR(
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec2 aTexCoord;

    out vec2 TexCoord;

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
        TexCoord = aTexCoord;
    }

);

const char* fsrc_yuv420 = GET_GLSTR(
    out vec4 FragColor;
    in vec2 TexCoord;
    uniform sampler2D texY;
    uniform sampler2D texU;
    uniform sampler2D texV;

    void main()
    {
        vec3 yuv;
        vec3 rgb;

        yuv.x = texture(texY, TexCoord).r;
        yuv.y = texture(texU, TexCoord).r-0.5;
        yuv.z = texture(texV, TexCoord).r-0.5;

        rgb = mat3(1.0, 1.0, 1.0,
                   0.0, -0.3455, 1.779,
                   1.4075, -0.7169, 0.0) * yuv;

        FragColor = vec4(rgb, 1.0);
    }
);

const char* fsrc_nv12 = GET_GLSTR(
    out vec4 FragColor;
    in vec2 TexCoord;
    uniform sampler2D texY;
    uniform sampler2D texUV;

    void main()
    {
        vec3 yuv;
        vec3 rgb;

        yuv.x = texture(texY, TexCoord).r-0.0625;
        yuv.y = texture(texUV, TexCoord).r-0.5;
        yuv.z = texture(texUV, TexCoord).r-0.5;

        rgb = mat3(1.0, 1.0, 1.0,
                   0.0, -0.3455, 1.779,
                   1.4075, -0.7169, 0.0) * yuv;

        FragColor = vec4(rgb, 1.0);
    }
);

//-----------------------------------------------------------------------------------------------------

VideoGL::VideoGL(QWidget* parent) : QOpenGLWidget(parent)
{
    connect(&timer,&QTimer::timeout,this,&VideoGL::timeoutEvent);
    timer.setTimerType(Qt::PreciseTimer);  //精确的
    updateTime=0;

    videoW=get_video_w();
    videoH=get_video_h();
}

void VideoGL::initializeGL()
{
    initializeOpenGLFunctions();

    //------------------------------纹理------------------------------------------------------

    glGenTextures(1,&idY);
    glBindTexture(GL_TEXTURE_2D,idY);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,videoW,videoH,0,GL_RED,GL_UNSIGNED_BYTE,nullptr);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenTextures(1,&idU);
    glBindTexture(GL_TEXTURE_2D,idU);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,videoW >> 1, videoH >> 1,0,GL_RED,GL_UNSIGNED_BYTE,nullptr);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenTextures(1,&idV);
    glBindTexture(GL_TEXTURE_2D,idV);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,videoW >> 1, videoH >> 1,0,GL_RED,GL_UNSIGNED_BYTE,nullptr);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //------------------------------pbo-------------------------------------------------------

    pboY=new QOpenGLBuffer(QOpenGLBuffer::PixelUnpackBuffer);
    pboY->create();
    pboY->bind();
    pboY->allocate(videoW*videoH);
    pboY->release();

    pboU=new QOpenGLBuffer(QOpenGLBuffer::PixelUnpackBuffer);
    pboU->create();
    pboU->bind();
    pboU->allocate(videoW*videoH/4);
    pboU->release();

    pboV=new QOpenGLBuffer(QOpenGLBuffer::PixelUnpackBuffer);
    pboV->create();
    pboV->bind();
    pboV->allocate(videoW*videoH/4);
    pboV->release();

    //------------------------------------------------------------------------------------------

    program.addShaderFromSourceCode(QOpenGLShader::Fragment,fsrc_yuv420);
    program.addShaderFromSourceCode(QOpenGLShader::Vertex,vsrc);
    program.link();
    program.bind();

    float vertices[] = {
        -1.0, -1.0,  0.0,  0.0,  1.0,        //左下
         1.0, -1.0,  0.0,  1.0,  1.0,        //右下
        -1.0,  1.0,  0.0,  0.0,  0.0,        //左上
         1.0,  1.0,  0.0,  1.0,  0.0         //右上
    };

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);  //设置为一次修改，多次使用(坐标不变,变得只是像素点)

    //初始化VAO,设置顶点数据状态(顶点，法线，纹理坐标等)
    vao.create();
    vao.bind();

    program.setAttributeBuffer(0, GL_FLOAT, 0, 3, 5 * sizeof(float));   //设置aPos顶点属性
    program.setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(float), 2, 5 * sizeof(float));   //设置aColor顶点颜色
    program.enableAttributeArray(0);
    program.enableAttributeArray(1);

    program.setUniformValue("texY", 0);
    program.setUniformValue("texU", 1);
    program.setUniformValue("texV", 2);  

    //清理颜色缓冲区
    glClearColor(0, 0, 0, 1);
}

void VideoGL::start(int x)
{
    if(x!=updateTime) updateTime=x;
    timer.start(updateTime);
}

void VideoGL::stop()
{ timer.stop(); }

void VideoGL::timeoutEvent()
{ VideoPlayerWaiter.wakeAll(); }

//-------------------------------------------------------------------------------------------------------------

void VideoGL::paint()
{
    update();
}

void VideoGL::paintGL()
{
    YUV yuv=get_yuv_front();

    if(yuv.buffer)
    {
        //----------------Y----------------

        pboY->bind();
        pboY->write(0, yuv.buffer, videoW*videoH);
        glActiveTexture(GL_TEXTURE0 + 0);
        glBindTexture(GL_TEXTURE_2D,idY);
        glTexSubImage2D(GL_TEXTURE_2D,0,0,0,videoW,videoH,GL_RED,GL_UNSIGNED_BYTE,NULL);
        pboY->release();

        //----------------U----------------

        pboU->bind();
        pboU->write(0, yuv.buffer+videoW*videoH, videoW*videoH/4);
        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D,idU);
        glTexSubImage2D(GL_TEXTURE_2D,0,0,0,videoW >> 1, videoH >> 1,GL_RED,GL_UNSIGNED_BYTE,NULL);
        pboU->release();

        //----------------V----------------

        pboV->bind();
        pboV->write(0, yuv.buffer+videoW*videoH*5/4, videoW*videoH/4);
        glActiveTexture(GL_TEXTURE0 + 2);
        glBindTexture(GL_TEXTURE_2D,idV);
        glTexSubImage2D(GL_TEXTURE_2D,0,0,0,videoW >> 1, videoH >> 1,GL_RED,GL_UNSIGNED_BYTE,NULL);
        pboV->release();

        //-----------------------------------

        glViewport((width()-realW)/2, (height()-realH), realW, realH);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        //设置video时间
        set_video_time(yuv.time_at);
        set_video_clock(av_gettime());
    }

    pop_yuv();
    paintWaiter.wakeAll();
}

void VideoGL::resizeGL(int,int)
{
    double p1=(double)videoW/(double)videoH;     // get_video_w() / get_video_h()
    double p2=(double)width()/(double)height();


    if(p1 < p2)
    {
        realW = p1 * height();
        realH = height();
    }
    else
    {
        realH = width() / p1;
        realW = width();
    }

    glViewport((width()-realW)/2, (height()-realH), realW, realH);
}

VideoGL::~VideoGL()
{
    program.release();
    vao.release();
    vbo.release();
}

*/
