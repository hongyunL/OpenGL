#include "Bullet.h"

#include "model\BulletData.h"
#include "Vector3f.h"

#include <iostream>

Bullet::Bullet(void)
	: DynamicObject()
{
	m_time = 0;
	m_removable = false;

	m_pMesh = new Mesh(2, GL_LINES);
	m_pMesh->loadVertex(BulletData::vertex, sizeof(BulletData::vertex), GL_FLOAT, 3);
	m_pMesh->loadColor(BulletData::color, sizeof(BulletData::color), GL_FLOAT, 4);
}

/*���ݳ�ʼλ�úͽǶ�{ˮƽת�ǡ�����}����������*
*����λ��
*���ýǶ�
*���ó��ٶ�*/
void Bullet::setInitStatus(float x, float y, float z, float rotY, float rotZ, float velocity)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->rotY = rotY;
	this->rotZ = rotZ;

	/*�����������е��ٶ�*/
	Vector3f vecVelocity;//ע�⣺Vector3fʹ�ñ�׼��ѧ����ϵ��openGLʹ��GL����ϵ�����߼���Ҫ����
	vecVelocity.countProjectLenOnAxis(velocity, rotY + 90, rotZ);
	this->vx = vecVelocity.getY();
	this->vy = vecVelocity.getZ();
	this->vz = vecVelocity.getX();
}

void Bullet::getFrontCoord(float *pRetX, float *pRetY, float *pRetZ)
{
	Vector3f vecBullet;//�ӵ��İ뷽������

	vecBullet.countProjectLenOnAxis(BulletData::LENGTH/2.0f, 90+rotY, rotZ);

	//offset[XYZ]ʹ��GL����ϵ��
	float offsetX = vecBullet.getY();
	float offsetY = vecBullet.getZ();
	float offsetZ = vecBullet.getX();

	*pRetX = x + offsetX;
	*pRetY = y + offsetY;
	*pRetZ = z + offsetZ;
}

void Bullet::getBackCoord(float *pRetX, float *pRetY, float *pRetZ)
{
	Vector3f vecBullet;//�ӵ��İ뷽������
	vecBullet.countProjectLenOnAxis(BulletData::LENGTH/2.0f, 90+rotY, rotZ);

	//offset[XYZ]ʹ��GL����ϵ��
	float offsetX = vecBullet.getY();
	float offsetY = vecBullet.getZ();
	float offsetZ = vecBullet.getX();

	*pRetX = x - offsetX;
	*pRetY = y - offsetY;
	*pRetZ = z - offsetZ;
}

/*������Ŀ��ʱ����*/
void Bullet::hitTarget()
{
	m_removable = true;
}

/*��Ⱦ����Ļ��
*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
bool Bullet::render()
{
	m_time++;

	if(m_time > BulletData::MAX_TIME)
		m_removable = true;

	DynamicObject::render();

	return m_removable;
}