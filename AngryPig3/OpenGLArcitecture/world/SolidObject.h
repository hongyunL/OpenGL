#pragma once

#include "WorldObject.h"
#include "Mesh.h"

class SolidObject : public WorldObject{
public:
	SolidObject();

	/*��Ⱦ����Ļ��
	*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
	virtual bool render() override;

	~SolidObject();

	float x;
	float y;
	float z;
	float rotY;//�����y�����ת�Ƕȣ�����ˮƽ���еĽǶ�
	float rotZ;//�����z�����ת�Ƕȣ�������

	/*ʵ�ú��������ڼ�������3DExploration��openGL�������飬���Դ�����������
	*�÷���ֻ���ز�����������Ķ�������
	*������
	*1.������Ŀ����ѯ3DExploration�Ķ����������������Ŀ��λ��ת���õ���.cpp���ˣ���Ȼ�������Ŀ��3
	*2-4.��Ӧ�������������
	*5-7.����ģ����ɫ*/
	void loadMesh(unsigned vertexNum, 
		int face_indicies[][6], unsigned faceIndiciesLength, 
		float vertices[][3],  unsigned verticesLength,
		float normals[][3],	 unsigned normalsLength,
		float colorR, float colorG, float colorB);

protected:
	Mesh *m_pMesh;
};