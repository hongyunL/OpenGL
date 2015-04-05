#pragma once

#include <glut.h>

class VertexArray{
public:
	VertexArray();
	/*������
	*1.ָ��Դ���ݵ�ָ�루��������ָ�����ǿת��void*�����ٴ��Σ���Դ���ݽ�������
	*2.Դ���ݳ��ȣ��ֽ�����
	*3.�������ͣ��������б�ѡȡ{GL_INT, GL_UNSIGNED_INT, GL_FLOAT, GL_DOUBLE����}
	*4.���ٸ����ݱ�ʾһ���㣨�����RGB��ʾ����ɫ���ò���Ϊ3��ÿ��Ϊ3�����ݱ�ʾһ�������ɫ��*/
	void loadArray(void *pSrc, int length, GLenum type, int size);

	void* getInfoPointer();

	GLenum getType();

	int getSize();

	void clear();

	~VertexArray();

protected:
	void *m_pInfo;
	GLenum m_type;
	int m_size;
};