#include "TankBarrel.h"
#include "TankBarrelData.h"

#include "ProjectToAxis.h"

#include <math.h>

#include <iostream>////////////////////////////////

TankBarrel::TankBarrel() : Object()
{
	m_meshModel.LoadMeshDataWithTexFrom3DE(TankBarrelData::vertexNum,
		TankBarrelData::face_indicies, sizeof(TankBarrelData::face_indicies),
		TankBarrelData::vertices, sizeof(TankBarrelData::vertices),
		TankBarrelData::normals, sizeof(TankBarrelData::normals),
		std::string(TankBarrelData::texureFileName),
		TankBarrelData::textures, sizeof(TankBarrelData::textures));

	m_speed = 0;
}

void TankBarrel::Move()
{
	
}

void TankBarrel::Render()
{
	
	glPushMatrix(); //������������ϵ
	
	glTranslatef(m_x, m_y, m_z); //�ٶȱ仯���λ��

	/*������ת�������������ĵ����壬rotY rotZ����Ӱ�����������λ��
	* ������ת���Ĳ����������ĵ����壬rotY rotZ��Ӱ�����������λ�ã�*/

	glTranslatef(-3, 0, 0); //rotY��ת�����������Ͳ������x�Ḻ�����ƶ�3����λ��
	glRotatef(m_rotY, 0.0f, 1.0f, 0.0f); 
	
	glTranslatef(1, 0, 0); //rotZ��ת�����������Ͳ������x�Ḻ�����ƶ�2����λ��
	glRotatef(m_rotZ, 0.0f, 0.0f, 1.0f);
	glTranslatef(2, 0, 0);

	float x = 0, y = 0, z = 0;

	/*����������൱���ڣ�m_x-3, m_y, m_z��*/
	m_x -= 3;
	m_x += 3 * cos(m_rotY*3.14 / 180)*cos(m_rotZ*3.14 / 180);
	m_z -= 3 * sin(m_rotY*3.14 / 180)*cos(m_rotZ*3.14 / 180);

	/*��0.75����Ϊ������ת�᳤Ϊ3��������ת�᳤Ϊ2���������ʱ��ͳһ��������3��
	* ���Լ����y����֮�������ƶ�1/4�ͻ���ԭ������Ͳָ���غϣ�ֻ��x����СһЩ */
	m_y += 2 * cos(m_rotY*3.14 / 180)*sin(m_rotZ*3.14 / 180) * 0.75;
	

	PaintModel(TankBarrelData::vertexNum);

	glPopMatrix();
}



//�����ڿ�λ��
void TankBarrel::GetMuzzlePos(float *retX, float *retY, float *retZ)
{
	float x = 0, y = 0, z = 0;
	ProjectToAxis::CountProjectLenOnAxis(&x, &y, &z, TankBarrelData::LENGTH / 2, m_rotY, m_rotZ);

	*retX = m_x + x;
	*retY = m_y + y;
	*retZ = m_z - z;


}