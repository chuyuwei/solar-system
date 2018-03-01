#ifndef PLANET
#define PLANET
#include<string>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<shader_s.h>
#include<stb_image.h>
using namespace std;
class planet{
public:
	planet(string texturename, float radius, float zs,float gs,glm::vec3 pos,planet *father){
		this->texturename = texturename;
		this->radius = radius;
		this->zs = zs;
		this->gs = gs;
		this->pos = pos;
		this->startgs = 0;
		this->startzs = 0;
		this->fathergongzhuan = 0;
		this->father = father;
		//对其进行纹理绘制	
		// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	}
	void drawSphere(Shader *shader);
	void drawSphere(Shader *shader,glm::vec3 earthpos,float earthgz);
	glm::mat4 updatePos(float jingdu,float weidu, glm::vec3 earthpos, float earthgz);
	void readImage();
	void setAdd(float addin);
	glm::vec3 getpos();

private:
	string texturename;
	float radius;//月球单位长度
	float zs;//月球自传速度为单位长度
	float startzs;//初始自转位置
	float gs;//月球公转速度为单位长度
	float startgs;//初始公转位置
	glm::vec3 pos;
	int width, height, nrChannels;
	unsigned char *data;
	float add ;
	glm::vec3 currentpos;
	float fathergongzhuan;
	planet *father;

};
#endif 