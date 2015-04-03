#pragma once

//#include "MathConst.h"
#include "GLPointf.h"

//ƽ�淽��Ϊ: ax + by + cz + d = 0
typedef struct
{
	float a;
	float b;
	float c;
	float d;
}
PlaneEq;

//��������
class TriangleFace
{
public:
	TriangleFace();

	void CalculatePlane(GLPointf v1, GLPointf v2, GLPointf v3); //setPlaneEq()

	//~TriangleFace();

//private:
	//TriangleFace(const TriangleFace& other){}
	//TriangleFace& operator=(const TriangleFace& other){}

	unsigned int faceIndices[3];	//���������3������ֵ
	PlaneEq planeEq;				//ƽ����ʽ��4������
	unsigned int neighbourFace[3];  //3�������������
	bool lighted;					//�Ƿ�Ϊ������
};