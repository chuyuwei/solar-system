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
#include "glew\include\GL\glew.h"
#include "glwidget.h"
#include <QPainter>
#include <QTimer>

#include"stb_image.h"

float duToHu = PI / 180.0;
float Hutodu = 180.0 / PI;
// Window dimensions
const GLuint WIDTH = 1080, HEIGHT = 800;
//! [0]
GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setFixedSize(WIDTH, HEIGHT);
    setAutoFillBackground(false);
	a = 0.0f;
	//初始化太阳模型
	//0.246*Hutodu
	sun = new planet("sun.png", 2, 0.246*Hutodu, 0, glm::vec3(0.0, 0.0, 0.0),NULL);
	mercury = new planet("mercury.png", 0.2, 0.107*Hutodu, 0.07*Hutodu, glm::vec3(-3.08*cos(5 * duToHu)*cos(4 * duToHu), 3.08*sin(5 * duToHu), 3.08*cos(5 * duToHu)*sin(4 * duToHu)),NULL);
	venus = new planet("venus.png", 0.2, 0.0258*Hutodu, 0.0279*Hutodu, glm::vec3(-7.25*cos(15 * duToHu)*cos(2 * duToHu), 7.25*sin(15 * duToHu), -7.25*cos(15 * duToHu)*sin(2 * duToHu)),NULL);
	//earth = new planet("earth.png", 0.5, 6.28*Hutodu, 0.0172*Hutodu, glm::vec3(9.81*cos(7 * duToHu)*cos(64 * duToHu), -9.81*sin(7 * duToHu), -9.81*cos(7 * duToHu)*sin(64 * duToHu)));
	earth = new planet("earth.png", 0.5, 6.28*Hutodu, 0.0172*Hutodu, glm::vec3( 9.81,0, 0),NULL);
	mars = new planet("mars.png", 0.3, 6.120*Hutodu, 0.00914*Hutodu, glm::vec3(-16.46*cos(49 * duToHu)*cos(32 * duToHu), 16.46*sin(49 * duToHu), -16.46*cos(49 * duToHu)*sin(32 * duToHu)),NULL);
	jupiter = new planet("jupiter.png", 0.5, 15.317*Hutodu, 0.00145*Hutodu, glm::vec3(-19 * cos(40 * duToHu)*cos(20 * duToHu), 19 * sin(40 * duToHu), -19 * cos(40 * duToHu)*sin(20 * duToHu)),NULL);
	saturn = new planet("saturn.png", 1.0, 14.741*Hutodu, 0.000583*Hutodu, glm::vec3(-22 * cos(1 * duToHu)*cos(6 * duToHu), 22 * sin(1 * duToHu), 22 * cos(1 * duToHu)*sin(6 * duToHu)),NULL);
	uranus = new planet("uranus.png", 0.3, 14.741*Hutodu, 0.0002048*Hutodu, glm::vec3(25 * cos(52 * duToHu)*cos(41 * duToHu), -25 * sin(52 * duToHu), 25 * cos(52 * duToHu)*sin(41 * duToHu)),NULL);
	neptune = new planet("nepture.png", 0.4, 8.37*Hutodu, 0.0001044*Hutodu, glm::vec3(-35 * cos(56 * duToHu)*cos(61 * duToHu), -35 * sin(56 * duToHu), 35 * cos(56 * duToHu)*sin(61 * duToHu)),NULL);
	moon = new planet("moon.png", 0.1, 0.229*Hutodu, 0.229*Hutodu, glm::vec3(1, 0, 0),earth);
	cameraplanetPos = new planet("camera", 0.5, 0, 6.28*Hutodu, glm::vec3(-0.5, 0.0, 0.0),earth);
	cameraplanetUp = new planet("camera", 0.5, 0, 6.28*Hutodu, glm::vec3(0.0, 1.0, 0.0),earth);
	cameraplanetY = new planet("camera", 0.5, 0, 6.28*Hutodu, glm::vec3(-0.6, 0.0, 0.0),earth);
	fov = 45.0f;
	cameraPos = glm::vec3(0.0f, 0.0f,50.0f);
	cameraUp = glm::vec3(0.0f,1.0f,0.0f);
	cameraY = glm::vec3(0.0f,0.0f,0.0f);
	//cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	//cameraUp = glm::vec3(0.0f, -1.0f, 0.0f);
	//cameraY = glm::vec3(0.5f, 0.0f, 0.0f);
	//glm::mat4 camera;
	//camera[0].x = 1;
	//camera = glm::translate(camera,glm::vec3(1.0f,0.0f,0.0f));
	//camera = glm::rotate(camera, 30.0f, glm::vec3(0.0f,1.0f,0.0f));
	//cout << "cailiao";
}
void GLWidget::animate()
{
	update();
}
GLWidget::~GLWidget()
{

}
void GLWidget::initializeGL()
{
	glewInit();
	glViewport(0, 0, WIDTH, HEIGHT);

	//sun = new planet("sun.png", 0.0f, 1.0f, 1.0f, vec3(0.0f, 0.0f, 0.0f));
	// build and compile our shader zprogram
	// ------------------------------------
	glEnable(GL_DEPTH_TEST);
	ourShader=new Shader("textures.vs", "textures.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	drawRound();
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// load and create a texture 
	// -------------------------

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	ourShader->use();

	//加载图像
	sun->readImage();
	mercury->readImage();
	venus->readImage();
	earth->readImage();
	mars->readImage();
	jupiter->readImage();
	saturn->readImage();
	uranus->readImage();
	neptune->readImage();
	moon->readImage();
	
}
void GLWidget::paintGL()
{
	// render
	// ------
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind Texture
	glBindTexture(GL_TEXTURE_2D, texture);

	ourShader->use();
	glBindVertexArray(VAO);
	glm::mat4 projection;
	projection = glm::perspective(fov, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	ourShader->setMat4("projection", projection);

	//glm::mat4 camerabianhuan=cameraplanet->updatePos(glm::vec3(9.81*cos(7 * duToHu)*cos(64 * duToHu), -9.81*sin(7 * duToHu), -9.81*cos(7 * duToHu)*sin(64 * duToHu)), 0.0172*Hutodu);
	//cameraPos = getm4v3(camerabianhuan, glm::vec3(0.0f, 0.0f, 0.0f));
	//cameraUp = getm4v3(camerabianhuan, glm::vec3(0.0f, 1.0f, 0.0f));
	//cameraY = getm4v3(camerabianhuan, glm::vec3(0.5f, 0.0f, 0.0f));
	glm::mat4 camerabianhuan;
	//camerabianhuan = cameraplanetPos->updatePos(glm::vec3(9.81*cos(7 * duToHu)*cos(64 * duToHu), -9.81*sin(7 * duToHu), -9.81*cos(7 * duToHu)*sin(64 * duToHu)), 0);
	//glm::vec3 Pos = getm4v3(camerabianhuan,glm::vec3(0.0f,0.0f,0.0f));
	//camerabianhuan = cameraplanetUp->updatePos(glm::vec3(9.81*cos(7 * duToHu)*cos(64 * duToHu), -9.81*sin(7 * duToHu), -9.81*cos(7 * duToHu)*sin(64 * duToHu)), 0);
	//glm::vec3 Up = getm4v3(camerabianhuan, glm::vec3(0.0f, 0.0f, 0.0f));
	//camerabianhuan = cameraplanetY->updatePos(glm::vec3(9.81*cos(7 * duToHu)*cos(64 * duToHu), -9.81*sin(7 * duToHu), -9.81*cos(7 * duToHu)*sin(64 * duToHu)), 0);
	//glm::vec3 Y= getm4v3(camerabianhuan, glm::vec3(0.0f, 0.0f, 0.0f));
	camerabianhuan = cameraplanetPos->updatePos(jingdu,weidu, glm::vec3(9.81, 0, 0), 0.0172*Hutodu);
	glm::vec3 Pos = getm4v3(camerabianhuan, glm::vec3(0.0f, 0.0f, 0.0f));
	camerabianhuan = cameraplanetY->updatePos(jingdu,weidu, glm::vec3(9.81, 0, 0), 0.0172*Hutodu);
	glm::vec3 Y = getm4v3(camerabianhuan, glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 view;
	if (viewflag)
		view = glm::lookAt(cameraPos,cameraY,cameraUp);
	else
		view = glm::lookAt(Pos, glm::vec3(Y.x,Pos.y,Y.z), glm::vec3(0.0f,1.0f,0.0f));
	ourShader->setMat4("view", view);

	sun->drawSphere(ourShader);	
	mercury->drawSphere(ourShader);
	venus->drawSphere(ourShader);
	earth->drawSphere(ourShader);
	mars->drawSphere(ourShader);
	jupiter->drawSphere(ourShader);
	saturn->drawSphere(ourShader);
	uranus->drawSphere(ourShader);
	neptune->drawSphere(ourShader);
	moon->drawSphere(ourShader, glm::vec3(9.81,0.0,0.0), 0.0172*Hutodu);

}
void GLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, (GLint)width, (GLint)height);
}
void GLWidget::drawRound()
{
	//确定球的半径为1
	float R = 1;
	//把球横向切成几部
	int statck = 15;
	float statckStep = (float)(PI / statck);
	int slice = 30;
	float sliceStep = (float)(PI / slice);
	int num1 = 0;
	for (int i = 0; i <=statck; i++)
	{
		float alpha0 = (float)(-PI / 2 + i*statckStep);
		float y0 = (float)(R * sin(alpha0));
		float r0 = (float)(R * cos(alpha0));
		//循环每一层圆
		for (int j = 0; j <=(slice * 2); j++){
			float beta = j * sliceStep;
			float x0 = (float)(r0 * cos(beta));
			float z0 = -(float)(r0 * sin(beta));
			vertices[num1] = x0;
			vertices[num1 + 1] = y0;
			vertices[num1 + 2] =z0;

			vertices[num1 + 3] = 1.0/(2*slice)*j;
			vertices[num1 + 4] = 1-1.0/(statck)*i;
			num1 += 5;
		}
	}
	int num2 = 0;
	for (int i = 0; i < statck; i++)
	{
		for (int j = 0; j <=slice * 2; j++)
		{
			
			//if (j == slice * 2)
			//{
			//	indices[0 + num2] = 0 + j + i*slice * 2;
			//	indices[1 + num2] = 0 + slice * 2 + j + i*slice * 2;
			//	indices[2 + num2] = 0 + i*slice * 2;

			//	indices[3 + num2] = 0 + slice * 2 + j + i*slice * 2;
			//	indices[4 + num2] = 0 + slice * 2 + i*slice * 2;
			//	indices[5 + num2] = 0 + i*slice * 2;
			//}
			//else
			//{ 
				indices[0 + num2] = 0 + j + i*(slice * 2+1);
				indices[1 + num2] = 0 + slice * 2+1 + j + i*(slice * 2+1);
				indices[2 + num2] = 1 + j + i*(slice * 2+1);

				indices[3 + num2] = 0 + slice * 2+1 + j + i*(slice * 2+1);
				indices[4 + num2] = 1 + slice * 2+1 + j + i*(slice * 2+1);
				indices[5 + num2] = 1 + j + i*(slice * 2+1);
			//}
			num2 += 6;
		}
	}
	cout << num2 << endl;

	/*vertices[0] = 0.0f;
	vertices[1] = -0.5f;
	vertices[2] = 0.0f;
	vertices[3] = 0.0f;
	vertices[4] = 0.0f;
	vertices[5] = 0.5f;
	vertices[6] = -0.5f;
	vertices[7] = 0.0f;
	vertices[8] = 1.0f;
	vertices[9] = 0.0f;
	vertices[10] = 0.5f;
	vertices[11] = 0.5f;
	vertices[12] = 0.0f;
	vertices[13] = 1.0f;
	vertices[14] = 1.0f;

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;*/
}
void GLWidget::wheelEvent(QWheelEvent *event)
{
	int numdegree = event->delta() / 8/10;
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= numdegree;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
	update();
	event->accept();

}
void GLWidget::mousePressEvent(QMouseEvent *event)
{
	//if (event->buttons() && Qt::LeftButton)
	mouseX = event->pos().x();
	mouseY = event->pos().y();
}
void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	float lastx = mouseX;
	float lasty = mouseY;
	mouseX= event->pos().x();
	mouseY = event->pos().y();
	float xoffset = mouseX - lastx;
	float yoffset = lasty - mouseY;
	float sensitivity = 0.05f;
	xoffset *= sensitivity*(fov/45);
	yoffset *= sensitivity*(fov/45);

	Yaw += xoffset;
	Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	glm::vec3 Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	glm::vec3 Right = glm::normalize(glm::cross(Front, cameraUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	glm::vec3 Up = glm::normalize(glm::cross(Right, Front));
	cameraUp = Up;
	cameraY = cameraPos + Front;
	update();
	//cout << 1;
}
void GLWidget::setaddin(float addin)
{
	sun->setAdd(addin);
	mercury->setAdd(addin);
	venus->setAdd(addin);
	earth->setAdd(addin);
	mars->setAdd(addin);
	jupiter->setAdd(addin);
	saturn->setAdd(addin);
	uranus->setAdd(addin);
	neptune->setAdd(addin);
	moon->setAdd(addin);
	cameraplanetPos->setAdd(addin);
	cameraplanetUp->setAdd(addin);
	cameraplanetY->setAdd(addin);
}
void GLWidget::fastToDay(float a)
{
	sun->setAdd(a);	
	mercury->setAdd(a);
	venus->setAdd(a);
	earth->setAdd(a);
	mars->setAdd(a);
	jupiter->setAdd(a);
	saturn->setAdd(a);
	uranus->setAdd(a);
	neptune->setAdd(a);
	moon->setAdd(a);
	cameraplanetPos->setAdd(a);
	cameraplanetUp->setAdd(a);
	cameraplanetY->setAdd(a);
	paintGL();
	
	
}
glm::vec3 GLWidget::getm4v3(glm::mat4 change, glm::vec3 pos)
{
	glm::vec3 result;
	glm::vec4 nowchange = change*glm::vec4(pos, 1.0f);
	result.x = nowchange.x;
	result.y = nowchange.y;
	result.z = nowchange.z;
	return result;
}

void GLWidget::setViewFlag(bool flag)
{
	viewflag = flag;
	update();
}

void GLWidget::setjingweidu(int weidu, int jingdu)
{
	this->weidu = weidu;
	this->jingdu = jingdu;
}