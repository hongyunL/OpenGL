#include "Castle.h"
#include "model\CastleData.h"

Castle::Castle(void)
	: SolidObject()
{
	x = -10;
	y = 10;

	rotY = 180;

	loadMesh(CastleData::vertexNum, 
		CastleData::face_indicies, sizeof(CastleData::face_indicies), 
		CastleData::vertices, sizeof(CastleData::vertices), 
		CastleData::normals, sizeof(CastleData::normals), 
		CastleData::r, CastleData::g, CastleData::b);
}

/*��Ⱦ����Ļ��
*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
bool Castle::render()
{
	SolidObject::render();

	return false;
}