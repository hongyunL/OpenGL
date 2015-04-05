#pragma once

#include "VertexArray.h"

/*3D�������ڱ�ʾ�����ģ��*/
class Mesh{
public:
	enum ColorMode{COLOR, TEXTURE};

	/*���Ƽ�ʹ���޲ι���*/
	Mesh();

	/*������
	*1.������Ŀ
	*2.��ͼģʽ�����б���ѡȡ��{GL_LINES, GL_TRIANGLES}*/
	Mesh(unsigned vertexAmount, GLenum paintMode = GL_TRIANGLES); //��ÿ��������Ϊһ��������������

	/*�������*/
	void clear();

	/*��������Ļ��*/
	void paint();

	/*���Ʋ�װ������
	*������
	*1.ָ��Դ���ݵ�ָ�루��������ָ�����ǿת��void*�����ٴ��Σ���Դ���ݽ�������
	*2.Դ���ݳ��ȣ��ֽ�����
	*3.�������ͣ��������б�ѡȡ{GL_INT, GL_UNSIGNED_INT, GL_FLOAT, GL_DOUBLE����}
	*4.���ٸ����ݱ�ʾһ���㣨�����RGB��ʾ����ɫ���ò���Ϊ3��
	*/
	/*װ�ض�������*/
	void loadVertex(void *pSrc, int length, GLenum type, int size);
	/*װ����ɫ*/
	void loadColor(void *pSrc, int length, GLenum type, int size);
	/*װ�ط�����*/
	void loadNormal(void *pSrc, int length, GLenum type);
	/*װ������*/
	void loadIndex(void *pSrc, int length, GLenum type);

	/*����*/
	~Mesh();

	/*��ʼ����Ⱦ����(��ʹ��Mesh֮ǰ����)
	*�򿪱����޳�
	*�趨�����ɫΪ��ɫ
	*��ƽ������
	*�򿪻�ϣ��趨alpha��Ϸ���
	*���塰���桱�Ļ��Ʒ���
	*
	*������
	*1.�Ƿ�Ӧ�ö�����������ͼ
	*2.�Ƿ�������
	*3.ָ����ɫ�ķ�ʽ����ѡһ{TEXTURE, COLOR}TEXTURE��ʾ��ɫ����������ͼ��COLOR��ʾֱ��ָ����ɫ
	*4.��������Ļ��Ʒ��򣬶�ѡһ{GL_CCW, GL_CW}CCW��ʾ��ʱ��Ϊ���棬CW��ʾ˳ʱ��Ϊ����
	*/
	static void InitMesh(bool usingIndex = true, bool usingLighting = true, ColorMode colorMode = TEXTURE, GLenum mode = GL_CCW);

	/*���塰���桱�Ļ��Ʒ��򣬲���ΪGL_CCW����ʱ�룩��GL_CW��˳ʱ�룩*/
	static void SetFrontFace(GLenum mode);

	/*�趨�µĻ滭ģʽ
	*����ͬ��ʼ������*/
	static void SetRenderMode(bool usingIndex = true, bool usingLighting = true, ColorMode colorMode = TEXTURE);

protected:
	//�������飬����ʹ��
	VertexArray m_vertexArray; 

	//���������飬�������ʱʹ��
	VertexArray m_normalArray;

	//��ɫ���飬��ѡһ��1.ֱ��ָ����ɫ �� 2.��������
	VertexArray m_colorArray;
	VertexArray m_textureArray;

	//�������飬��ѡ
	VertexArray m_indexArray;

	unsigned m_vertexAmount;
	GLenum m_paintMode;

	/*��Ⱦ״̬*/
	static bool m_usingIndex;
	static bool m_usingLighting;
	static ColorMode m_colorMode;
};