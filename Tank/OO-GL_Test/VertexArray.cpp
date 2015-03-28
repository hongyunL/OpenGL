#include "VertexArray.h"

#include <string.h>

VertexArray::VertexArray()
{
	m_pInfo = NULL;
}

void VertexArray::LoadArray(void *pSrc, int length, GLenum type, int size)
{
	//����ռ�
	m_pInfo = (void*)(new char[length]);
	memcpy(m_pInfo, pSrc, length);

	m_type = type;
	m_size = size;
}

void* VertexArray::GetInfoPointer()
{
	return m_pInfo;
}

GLenum VertexArray::GetType()
{
	return m_type;
}

int VertexArray::GetSize()
{
	return m_size;
}

void VertexArray::Clear()
{
	if(m_pInfo != NULL)
	{
		delete[] m_pInfo;
		m_pInfo = NULL;  //���³�ʼ����������Ұָ��
	}
}

VertexArray::~VertexArray()
{
	Clear();
}