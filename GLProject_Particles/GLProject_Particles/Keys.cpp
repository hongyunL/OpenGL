#include "Keys.h"

#include <windows.h>

Keys::Keys()
{
	Clear();
}

//������еİ�����Ϣ 
void Keys::Clear()
{
	//��ָ�����ڴ�ģ�����㣬��һ������Ϊ�ڴ���׵�ַ���ڶ�������Ϊ�ڴ�Ĵ�С
	ZeroMemory(&m_KeyDown, sizeof(m_KeyDown));
}

//�ж�ĳ�����Ƿ���
bool Keys::IsPressed(unsigned int key)
{
	return (key < MAX_KEYS) ? (m_KeyDown[key] == true) : false;
}

//����ĳ���������� 
void Keys::SetPressed(unsigned int key)
{
	if (key < MAX_KEYS) m_KeyDown[key] = true;
}

//����ĳ�������ͷ� 
void Keys::SetReleased(unsigned int key)
{
	if (key < MAX_KEYS) m_KeyDown[key] = false;
}