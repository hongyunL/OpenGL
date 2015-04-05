#include "Bird.h"
#include "model\BirdData.h"
#include "Vector3f.h"
#include "PhysicsConst.h"

Bird::Bird(void)
	: DynamicObject()
{
	m_removable = false;

	loadMesh(BirdData::vertexNum, 
		BirdData::face_indicies, sizeof(BirdData::face_indicies), 
		BirdData::vertices, sizeof(BirdData::vertices), 
		BirdData::normals, sizeof(BirdData::normals), 
		BirdData::r, BirdData::g, BirdData::b);
}

/*��������С��ʱ����
*������
*1-3��λ��
*4,5��ˮƽת�ǡ�����
*6�����ٶ�*/
void Bird::setInitStatus(float x, float y, float z, float rotY, float rotZ, float velocity)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->rotY = rotY;
	this->rotZ = -30;

	/*�����������е��ٶ�*/
	Vector3f vecVelocity;//ע�⣺Vector3fʹ�ñ�׼��ѧ����ϵ��openGLʹ��GL����ϵ�����߼���Ҫ����
	vecVelocity.countProjectLenOnAxis(velocity, rotY + 90, rotZ);
	this->vx = vecVelocity.getY();
	this->vy = vecVelocity.getZ();
	this->vz = vecVelocity.getX();
}

/*�������ĵ�����*/
void Bird::getCenCoordinate(float *pResultX, float *pResultY, float *pResultZ)
{
	*pResultX = x;
	*pResultY = y;
	*pResultZ = z;
}

/*������ײ�뾶*/
float Bird::getRadius()
{
	return 1.5f;
}

/*����ɱʱ����*/
void Bird::killed()
{
	m_removable = true;
}

/*��Ⱦ����Ļ��
*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
bool Bird::render()
{
	this->vy -= PhysicsConst::G;

	DynamicObject::render();

	return m_removable;
}