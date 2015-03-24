/**
*  ������ڼ̳�����������º�����ʵ��
*
*  void InitList();
*
*/
#pragma once

#include "VertexArray.h"
#include "Texture.h"
#include "GlobalInit.h"

/* 3D����ģ��MeshModel */
class MeshModel{
public:
	MeshModel(); 

	/* �ڼ̳�������д����ѡ�����ʾ�б� */
	//virtual void InitList() = 0;

	//�������
	void SetMatirial(
		const float ambient[4],  //��η����ǿ��
		const float diffuse[4],  //�������ǿ��
		const float specular[4], //���淴���ǿ��
		const float emission[4], //������ɫ
		const float shininess);  //������ָ���������ֲڳ̶�

	/*ʵ�ú��������ڼ�������3DExploration��openGL�������飬���Դ�����������
	*�÷���ֻ���ز�����������Ķ�������
	*������
	*1.������Ŀ����ѯ3DExploration�Ķ����������������Ŀ��λ��ת���õ���.cpp���ˣ���Ȼ�������Ŀ��3
	*2-7.��Ӧ�������������
	*/
	void LoadMeshDataFrom3DE(
		unsigned vertexNum,
		int face_indicies[][6], unsigned faceIndiciesLength,
		float vertices[][3], unsigned verticesLength,
		float normals[][3], unsigned normalsLength,
		float colorR, float colorG, float colorB);

	void LoadMeshDataWithTexFrom3DE(
		unsigned vertexNum,
		int face_indicies[][9], unsigned faceIndiciesLength,
		float vertices[][3], unsigned verticesLength,
		float normals[][3], unsigned normalsLength,
		std::string fileName,
		float textures[][2], unsigned texturesLength);

	/*����*/
	~MeshModel();

	/*�������������������������壬���ɱ���Ҫʹ���������������Ͳ�����private����*/
	void LoadVertex(void *pSrc, int length, GLenum type, int size); //װ�ض������� 
	void LoadColor(void *pSrc, int length, GLenum type, int size);  //װ����ɫ 

	//�������飬����ʹ��
	VertexArray m_vertexArray;

	//���������飬�������ʱʹ��
	VertexArray m_normalArray;

	//��ɫ���飬��ѡһ��1.ֱ��ָ����ɫ �� 2.��������
	VertexArray m_colorArray;
	VertexArray m_textureArray;
	Texture m_texture;

	//�������飬��ѡ
	VertexArray m_indexArray;

private:
	/*���Ʋ�װ�����ݣ����º�����ί�и�VertexArray�����
	* ������
	* 1.ָ��Դ���ݵ�ָ�루��������ָ�����ǿת��void*�����ٴ��Σ���Դ���ݽ�������
	* 2.Դ���ݳ��ȣ��ֽ�����
	* 3.�������ͣ��������б�ѡȡ{GL_INT, GL_UNSIGNED_INT, GL_FLOAT, GL_DOUBLE����}
	* 4.���ٸ����ݱ�ʾһ���㣨�����RGB��ʾ����ɫ���ò���Ϊ3��
	*/
	void LoadNormal(void *pSrc, int length, GLenum type); //װ�ط����� 
	void LoadIndex(void *pSrc, int length, GLenum type);  //װ������ 
	void LoadTexture(std::string fileName, void *pSrc, int length, GLenum type, int size);//װ����������

	/* ��ո��������������� */
	void Clear();

	/* ���� */
	float m_ambient[4];  //��η����ǿ��
	float m_diffuse[4];  //�������ǿ��
	float m_specular[4]; //���淴���ǿ��
	float m_emission[4]; //������ɫ
	float m_shininess;   //������ָ���������ֲڳ̶�
};