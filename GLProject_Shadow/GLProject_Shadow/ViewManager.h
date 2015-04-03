#pragma once 

#include <glut.h>

/*����ģʽ���л���ָ������ڻ���2Dͼ��
* ViewOrtho()��ViewPerspective()�ɶԵ��ã����ȵ���ViewOrtho()
* Ĭ�ϲü�����Ϊ��-1,1,-1,1,-1,-1��*/
class ViewManager
{
public:
	ViewManager(){}

	//�л���ͶӰ����Ĭ�ϲü�����Ϊ��-1,1,-1,1,-1,-1��
	static void ViewOrtho(GLdouble left = -1, GLdouble right = 1, GLdouble bottom = -1, GLdouble top = 1)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix(); //���浱ǰ����(ͶӰ����)  
		glLoadIdentity();

		glOrtho(left, right, bottom, top, 1, -1);

		glMatrixMode(GL_MODELVIEW); //���浱ǰ����(��ͼ����)  
		glPushMatrix();
		glLoadIdentity();
	}

	//�л���͸�Ӿ���
	static void ViewPerspective()
	{
		glMatrixMode(GL_PROJECTION);
		glPopMatrix(); //�ָ�ͶӰ����  
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix(); //��ͼ���� 
	}
};