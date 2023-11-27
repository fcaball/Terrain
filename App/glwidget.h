/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <iostream>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include "logo.h"
#include "mesh.h"
#include <QOpenGLTexture>
#include <QTime>
#include <QTimer>
#include <QCursor>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    static bool isTransparent() { return m_transparent; }
    static void setTransparent(bool t) { m_transparent = t; }

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    Mesh object;
    void loadOFF(std::string file);
    void UpdateResolution(int res);
    void UpdateTerrain(QString imgname);
    void UpdateBiome(QString imgname);

    int getResolution();

    bool wireframe;
    bool tool_active;
    bool mode_pres;

    float angle_speed;

    QTimer timer;
    QTime last_time;
    int last_count;
    int frame_count;

public slots:
    // Completer : ajouter des slots pour signaler appliquer le changement de rotation
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void cleanup();
    void DrawCircle();
    void Hand_Tool();

signals:

    // Completer : ajouter des signaux pour signaler des changement de rotation
    void objectRotChangeOnX(int angle);
    void objectRotChangeOnY(int angle);
    void objectRotChangeOnZ(int angle);
    void UpdateFPS(int newFPS);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override
    {
        // Lorsque le clic de souris est relâché, restaurer le curseur par défaut
        if (!tool_active)
        {
            QPixmap customCursorPixmap("./drag.png");
            QCursor customCursor(customCursorPixmap);
            setCursor(customCursor);
        }

        // Appel de la fonction de la classe de base pour traiter l'événement
        QWidget::mouseReleaseEvent(event);
    }
    void WheelEvent(QWheelEvent *event);
    void enterEvent(QEvent *event) override
    {
        if (!tool_active)
        {
            QPixmap customCursorPixmap("./drag.png");
            QCursor customCursor(customCursorPixmap);
            setCursor(customCursor);
        }

    }

    void leaveEvent(QEvent *event) override
    {
        setCursor(Qt::ArrowCursor);
    }

private:
    void setupVertexAttribs();
    glm::vec3 GetWorldPosition();
    bool m_core;
    int m_xRot;
    int m_yRot;
    int m_zRot;
    QPoint m_last_position;
    QOpenGLShaderProgram *m_program;
    int m_mvp_matrix_loc;
    int m_normal_matrix_loc;
    int m_light_pos_loc;
    QMatrix4x4 m_projection;
    QMatrix4x4 m_view;
    QMatrix4x4 m_model;
    static bool m_transparent;

    int mouseX, mouseY;

    bool hm_active = false;
    QOpenGLTexture *hmap;

    bool biome_active = false;
    bool mouseMovePressed = false;
    bool mouseRotatePressed = false;
    bool mouseZoomPressed = false;
    int lastX = 0;
    int lastY = 0;
    int lastZoom = 0;

    QVector3D cam_position;
    QVector3D cam_front;
    QVector3D cam_up;

    QVector<QVector2D> biome_data;

    QOpenGLVertexArrayObject vao_;
    QOpenGLBuffer vertexBuffer_ = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer indexBuffer_ = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    QOpenGLBuffer m_texturebuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

    QOpenGLBuffer m_biomebuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
};

#endif
