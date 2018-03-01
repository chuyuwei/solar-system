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
		//��������������	
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
	float radius;//����λ����
	float zs;//�����Դ��ٶ�Ϊ��λ����
	float startzs;//��ʼ��תλ��
	float gs;//����ת�ٶ�Ϊ��λ����
	float startgs;//��ʼ��תλ��
	glm::vec3 pos;
	int width, height, nrChannels;
	unsigned char *data;
	float add ;
	glm::vec3 currentpos;
	float fathergongzhuan;
	planet *father;

};
#endif 