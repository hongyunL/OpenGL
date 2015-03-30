/**
*  ������ڼ̳�����������º�����ʵ��
*
*  void InitList();
*
*/
#include "MeshModel.h"

#include <stdlib.h>
#include <vector>

MeshModel::MeshModel()
{

}

/*װ�ض�������*/
void MeshModel::LoadVertex(void *pSrc, int length, GLenum type, int size)
{
	m_vertexArray.LoadArray(pSrc, length, type, size);
}
/*װ����ɫ*/
void MeshModel::LoadColor(void *pSrc, int length, GLenum type, int size)
{
	m_colorArray.LoadArray(pSrc, length, type, size);
}
/*װ�ط�����*/
void MeshModel::LoadNormal(void *pSrc, int length, GLenum type)
{
	m_normalArray.LoadArray(pSrc, length, type, 3);
}
/*װ������*/
void MeshModel::LoadIndex(void *pSrc, int length, GLenum type)
{
	m_indexArray.LoadArray(pSrc, length, type, 1);
}
/*װ������*/
void MeshModel::LoadTexture(std::string fileName, void *pSrc, int length, GLenum type, int size)
{
	m_texture.LoadTexture(fileName);
	//m_texture.Apply(); //SetRenderMode���
	m_textureArray.LoadArray(pSrc, length, type, size);
}

void MeshModel::SetMatirial(
	const float ambient[4],  //��η����ǿ��
	const float diffuse[4],  //�������ǿ��
	const float specular[4], //���淴���ǿ��
	const float emission[4], //������ɫ
	const float shininess)   //������ָ���������ֲڳ̶�
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient); //���棬�ĸ����ԣ����ó�ʲô��
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

/* ���ȣ���֪����λ������v0 v1 v2 v3���ͷ�����n0 n1 n2 n3����
* (����vi �� ni�������飬����Ϊ3����ʾһ����ά����)
* ��ˣ�ָ��3����ţ�����0,1,2����v0v1v2����ָ��һ��������3�������λ�ã�
* ��ָ��3����ţ�����0,2,4����n0n2n4����ָ��һ��������3������ķ�������
* �Ѹղ�ָ������Ž����һ�𣬼�0��1,2,0,2,4����������һ�����������λ�úͷ��� 
*/
void MeshModel::LoadMeshDataFrom3DE(
	unsigned vertexNum,
	int face_indicies[][6], unsigned faceIndiciesLength,
	float vertices[][3], unsigned verticesLength,
	float normals[][3], unsigned normalsLength,
	float colorR, float colorG, float colorB)
{
	std::vector<float> vecVertex;
	std::vector<float> vecNormal;
	std::vector<float> vecColor;

	for (unsigned i = 0; i<faceIndiciesLength / sizeof(face_indicies[0]); i++)
	{
		for (unsigned j = 0; j<3; j++)
		{
			int vi = face_indicies[i][j];
			int ni = face_indicies[i][j + 3];//Normal index
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

	LoadColor(vecColor.data(), vecColor.size()*sizeof(float), GL_FLOAT, 3);
	LoadVertex(vecVertex.data(), vecVertex.size()*sizeof(float), GL_FLOAT, 3);
	LoadNormal(vecNormal.data(), vecNormal.size()*sizeof(float), GL_FLOAT);
}

void MeshModel::LoadMeshDataWithTexFrom3DE(
	unsigned vertexNum,
	int face_indicies[][9], unsigned faceIndiciesLength,
	float vertices[][3], unsigned verticesLength,
	float normals[][3], unsigned normalsLength,
	std::string fileName,
	float textures[][2], unsigned texturesLength)
{
	std::vector<float> vecVertex;
	std::vector<float> vecNormal;
	std::vector<float> vecTexture;

	for (unsigned i = 0; i<faceIndiciesLength / sizeof(face_indicies[0]); i++)
	{
		for (unsigned j = 0; j<3; j++)
		{
			int vi = face_indicies[i][j];     //������������
			int ni = face_indicies[i][j + 3]; //�����������
			int ti = face_indicies[i][j + 6]; //������������
			vecVertex.push_back(vertices[vi][0]);
			vecVertex.push_back(vertices[vi][1]);
			vecVertex.push_back(vertices[vi][2]);
			vecNormal.push_back(normals[ni][0]);
			vecNormal.push_back(normals[ni][1]);
			vecNormal.push_back(normals[ni][2]);
			vecTexture.push_back(textures[ti][0]);
			vecTexture.push_back(textures[ti][1]);
		}
	}

	LoadVertex(vecVertex.data(), vecVertex.size()*sizeof(float), GL_FLOAT, 3);
	LoadNormal(vecNormal.data(), vecNormal.size()*sizeof(float), GL_FLOAT);
	LoadTexture(fileName, vecTexture.data(), vecTexture.size()*sizeof(float), GL_FLOAT, 2);
}


/*�������*/
void MeshModel::Clear()
{
	m_vertexArray.Clear();
	m_normalArray.Clear();
	m_indexArray.Clear();
	m_colorArray.Clear();
	m_textureArray.Clear(); //����
}

/*����*/
MeshModel::~MeshModel()
{
	Clear();
}
