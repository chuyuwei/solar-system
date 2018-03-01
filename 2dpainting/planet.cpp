#include<planet.h>
#include<glm/glm.hpp>

void planet::drawSphere(Shader *shader)
{	
	glm::mat4 model;	
	//令其进行公转	
	startgs = startgs + gs*add;
	startgs = startgs - (int)startgs + (int)startgs % 360;
	if (pos.y==0)
		model = glm::rotate(model, startgs, glm::vec3(0.0f, 1.0f, 0.0f));
	else
	{
		model = glm::rotate(model, startgs, glm::vec3(1.0f, -pos.x/pos.y, 0.0f));
	}
	//将其移动到初始位置
	model = glm::translate(model, pos);
	//令其进行自转
	startzs = startzs + zs*add;
	startzs = startzs - (int)startzs + (int)startzs % 360;
	model = glm::rotate(model, startzs, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec4 result = glm::inverse(model)*glm::vec4(0.0f,0.0f,0.0f,1.0f);
	currentpos.x = result.x;
	currentpos.y = result.y;
	currentpos.z = result.z;
	//首先对其进行缩放
	model = glm::scale(model, glm::vec3(radius, radius, radius));
	shader->setMat4("model",model);	
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	glDrawElements(GL_TRIANGLES, 5490, GL_UNSIGNED_INT, 0);
}
void planet::drawSphere(Shader *shader, glm::vec3 earthpos, float earthgz)
{
	
	glm::mat4 model;
	//随地球一起转动
	fathergongzhuan = fathergongzhuan + earthgz*add;
	if (earthpos.y == 0)
		model = glm::rotate(model, fathergongzhuan, glm::vec3(0.0f, 1.0f, 0.0f));
	else
	{
		model = glm::rotate(model, fathergongzhuan, glm::vec3(1.0f, -earthpos.x / earthpos.y, 0.0f));
	}
	//随地球一起移动
	model = glm::translate(model, earthpos);
	//令其进行公转	
	startgs = startgs + gs*add;
	startgs = startgs - (int)startgs + (int)startgs % 360;
	if (pos.y == 0)
		model = glm::rotate(model, startgs, glm::vec3(0.0f, 1.0f, 0.0f));
	else
	{
		model = glm::rotate(model, startgs, glm::vec3(1.0f, -pos.x / pos.y, 0.0f));
	}
	//将其移动到初始位置
	model = glm::translate(model, pos);
	//令其进行自转
	startzs = startzs + zs*add;
	startzs = startzs - (int)startzs + (int)startzs % 360;
	model = glm::rotate(model, startzs, glm::vec3(0.0f, 1.0f, 0.0f));
	//首先对其进行缩放
	model = glm::scale(model, glm::vec3(radius, radius, radius));
	shader->setMat4("model", model);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	glDrawElements(GL_TRIANGLES, 5490, GL_UNSIGNED_INT, 0);
}
glm::mat4 planet::updatePos(float jingdu, float weidu, glm::vec3 earthpos, float earthgz)
{
	glm::mat4 model;
	fathergongzhuan = fathergongzhuan + earthgz*add;
	if (earthpos.y == 0)
		model = glm::rotate(model, fathergongzhuan, glm::vec3(0.0f, 1.0f, 0.0f));
	else
	{
		model = glm::rotate(model, fathergongzhuan, glm::vec3(1.0f, -earthpos.x / earthpos.y, 0.0f));
	}
	model = glm::translate(model,earthpos);
	//令其进行公转	
	startgs = startgs + gs*add;
	startgs = startgs - (int)startgs + (int)startgs % 360;
	model = glm::rotate(model, startgs, glm::vec3(0.0, 1.0, 0.0));
	//旋转到对应经纬度
	model = glm::rotate(model,jingdu,glm::vec3(0.0,1.0,0.0));
	model = glm::rotate(model,weidu,glm::vec3(0.0,0.0,-1.0));
	//将其移动到初始位置
	model = glm::translate(model, pos);
	return model;
}
glm::vec3 planet::getpos()
{
	return currentpos;
}
void planet::readImage()
{
	data = stbi_load(texturename.c_str(), &width, &height, &nrChannels, 0);
}


void planet::setAdd(float addin)
{
	add = addin;
}