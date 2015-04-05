#include "GunBase.h"
#include "model\GunBaseData.h"

GunBase::GunBase(void)
	: SolidObject()
{
	y = 0.8;
	loadMesh(GunBaseData::vertexNum, 
		GunBaseData::face_indicies, sizeof(GunBaseData::face_indicies), 
		GunBaseData::vertices, sizeof(GunBaseData::vertices), 
		GunBaseData::normals, sizeof(GunBaseData::normals), 
		GunBaseData::r, GunBaseData::g, GunBaseData::b);
}

/*��Ⱦ����Ļ��
*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
bool GunBase::render()
{
	SolidObject::render();

	return false;
}