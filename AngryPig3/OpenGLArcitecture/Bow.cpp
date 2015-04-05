#include "Bow.h"
#include "model\BowData.h"

Bow::Bow(void)
	: SolidObject()
{
	y = 1;
	rotY = 90;
	loadMesh(BowData::vertexNum, 
		BowData::face_indicies, sizeof(BowData::face_indicies), 
		BowData::vertices, sizeof(BowData::vertices), 
		BowData::normals, sizeof(BowData::normals), 
		BowData::r, BowData::g, BowData::b);
}

/*��Ⱦ����Ļ��
*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
bool Bow::render()
{
	SolidObject::render();

	return false;
}