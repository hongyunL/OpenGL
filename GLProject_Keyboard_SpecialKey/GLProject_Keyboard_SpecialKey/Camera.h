#pragma once

/*OpenGL�����᷽��
*	x�᣺��Ļ���½�->���½�
*	y�᣺��Ļ���½�->���Ͻ�
*	z�᣺����
* ����ڷŷ�������x��������ͷ������y��������
*/
class Camera{
public:
	Camera();

	void SetEyePos(float eyeX, float eyeY, float eyeZ);
	void SetTargetPos(float targetX, float targetY, float targetZ);

	/*�����˳ƻ�������
	* ������
	*	1.����	
	*	2.���Ұڽ�
	*	3.��������*/
	void SetViewAngleWithTargetFixed(float distance, float rotY, float rotZ);

	/*��һ�˳ƻ�����Χ
	* ������
	*	1.���Ұڽ�
	*	2.��������*/
	void SetViewAngleWithEyeFixed(float rotY, float rotZ);

	/* Ӧ������� */
	void Apply();

	/* ������Ұ���� */
	void UpdatePerspective(float aspect, float ratioWH);

private:
	float m_eyeX;
	float m_eyeY;
	float m_eyeZ;

	float m_targetX;
	float m_targetY;
	float m_targetZ;

	/*������Ұ������*/
	float m_aspect;  //��Ұ��ȽǶ�
	float m_ratioWH; //��߱�
	float m_near;
	float m_far;
};