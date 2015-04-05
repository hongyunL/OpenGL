#include "Mountain.h"
#include "model\MountainData.h"

Mountain::Mountain(void)
	: SolidObject()
{
	x = 32;
	y = 0.5;
	rotY = -90;
	loadMesh(MountainData::vertexNum, 
		MountainData::face_indicies, sizeof(MountainData::face_indicies), 
		MountainData::vertices, sizeof(MountainData::vertices), 
		MountainData::normals, sizeof(MountainData::normals), 
		MountainData::color[0], MountainData::color[1], MountainData::color[2]);
}

/*��Ⱦ����Ļ��
*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
bool Mountain::render()
{
	glPushMatrix();

	glScalef(1, 3.5, 1);

	SolidObject::render();

	glPopMatrix();

	return false;
}

Mountain::~Mountain(void)
{
}
