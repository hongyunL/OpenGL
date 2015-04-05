#include "Pig.h"
#include "model\PigData.h"

Pig::Pig(void)
	: SolidObject()
{
	y = 1;
	loadMesh(PigData::vertexNum, 
		PigData::face_indicies, sizeof(PigData::face_indicies), 
		PigData::vertices, sizeof(PigData::vertices), 
		PigData::normals, sizeof(PigData::normals), 
		PigData::r, PigData::g, PigData::b);
}

/*��Ⱦ����Ļ��
*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
bool Pig::render()
{
	SolidObject::render();

	return false;
}