#include "SolidObject.h"

#include <glut.h>
#include <vector>

SolidObject::SolidObject()
{
	x = 0;
	y = 0;
	z = 0;
	rotY = 0;
	rotZ = 0;
}

bool SolidObject::render()
{
	glPushMatrix();

	glTranslatef(x, y, z);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotZ, 0.0f, 0.0f, 1.0f);

	m_pMesh->paint();

	glPopMatrix();

	return false;
}

/*ʵ�ú��������ڼ�������3DExploration��openGL�������飬���Դ�����������
*�÷���ֻ���ز�����������Ķ�������
*������
*1.������Ŀ����ѯ3DExploration�Ķ����������������Ŀ��λ��ת���õ���.cpp���ˣ���Ȼ�������Ŀ��3
*2-4.��Ӧ�������������
*����������ܷ���Mesh���У���Ϊ�÷����漰������һ���µ�Mesh��Meshû���Թ��������*/
void SolidObject::loadMesh(unsigned vertexNum, 
	int face_indicies[][6], unsigned faceIndiciesLength, 
	float vertices[][3],  unsigned verticesLength,
	float normals[][3],	 unsigned normalsLength,
	float colorR, float colorG, float colorB)
{
	std::vector<float> vecVertex;
	std::vector<float> vecNormal;
	std::vector<float> vecColor;

	for(unsigned i=0;i<faceIndiciesLength/sizeof(face_indicies[0]);i++)
	{
		for(unsigned j=0;j<3;j++)
		{
			int vi=face_indicies[i][j];
			int ni=face_indicies[i][j+3];//Normal index
			vecVertex.push_back(vertices[vi][0]);
			vecVertex.push_back(vertices[vi][1]);
			vecVertex.push_back(vertices[vi][2]);
			vecNormal.push_back(normals[ni][0]);
			vecNormal.push_back(normals[ni][1]);
			vecNormal.push_back(normals[ni][2]);
			vecColor.push_back(colorR);
			vecColor.push_back(colorG);
			vecColor.push_back(colorB);
		}
	}

	m_pMesh = new Mesh(vertexNum, GL_TRIANGLES);
	m_pMesh->loadColor(vecColor.data(), vecColor.size()*sizeof(float), GL_FLOAT, 3);
	m_pMesh->loadVertex(vecVertex.data(), vecVertex.size()*sizeof(float), GL_FLOAT, 3);
	m_pMesh->loadNormal(vecNormal.data(), vecNormal.size()*sizeof(float), GL_FLOAT);
}

SolidObject::~SolidObject()
{
	delete m_pMesh;
}