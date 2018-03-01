/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
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
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
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

#ifndef GLWIDGET_H
#define GLWIDGET_H
#include"shader_s.h"
#include <QOpenGLWidget>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<time.h>
#include<math.h>
#include<vector>
#include<planet.h>
#include<QWheelEvent>
using namespace std;
#define PI 3.1415
#define SPEEDUP 3
//! [0]
class Helper;

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
	GLWidget(QWidget *parent);
	virtual ~GLWidget();
	void setaddin(float addin);
	void fastToDay(float a);
	glm::vec3 getm4v3(glm::mat4 change,glm::vec3 pos);
	void setViewFlag(bool flag);
	void setjingweidu(int weidu,int jingdu);

public slots:
	void animate();

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void wheelEvent(QWheelEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	//void mouseMoveEvent(QMouseEvent *event);

private:
	unsigned int VBO, VAO, EBO;
	Shader *ourShader;
	unsigned int texture;
	clock_t startTime, endTime;
	GLfloat a;
	float vertices[4880] = {};
	unsigned int indices[5490] = {};
	void drawRound();
	//ÐÐÐÇ
	planet *sun;
	planet *mercury;
	planet *venus;
	planet *earth;
	planet *mars;
	planet *jupiter;
	planet *saturn;
	planet *uranus;
	planet *neptune;
	planet *moon;
	planet *cameraplanetPos;
	planet *cameraplanetUp;
	planet *cameraplanetY;
	float fov;
	int mouseX, mouseY;
	glm::vec3 cameraPos;
	glm::vec3 cameraUp;
	glm::vec3 cameraY;
	float Yaw = -90.0f;
	float Pitch = 0.0f;
	bool viewflag = true;
	float weidu = 0;
	float jingdu = 0;
	
};
//! [0]

#endif
