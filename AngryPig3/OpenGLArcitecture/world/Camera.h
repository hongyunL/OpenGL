#pragma once

class Camera{
public:
	Camera();

	/*�趨�۾����۲�㣩λ��*/
	void setEyePos(float eyeX, float eyeY, float eyeZ);

	/*�趨�۲����ģ����۲�㣩λ��*/
	void setCenterPos(float centerX, float centerY, float centerZ);

	/*�̶�����λ�ã����ݾ���͹۲�Ƕȣ��Ƕ��ƣ��趨�۾�λ��
	*������
	*1.����
	*��������lΪ���Թ۲�����Ϊ��㣬�۾���۲����ĵķ���Ϊ����
	*2.����l ��xzƽ���ڵ�ͶӰ�����y���ת�� ����x����ָ����Ϊ0�㣩
	*3.����l ��xzƽ��ļн� ������λ������ʱ�Ƕ�Ϊ0�㣬���Ͽ�ʱ�Ƕ�Ϊ����*/
	void setViewAngleWithCenterFixed(float distance, float rotY, float rotZ);

	/*�̶��۾�λ�ã����ݹ۲�Ƕȣ��Ƕ��ƣ��趨�۲��λ�ã��൱�ڵ�һ�ӽǣ�
	*������
	*��������lΪ�����۾�Ϊ��㣬���ߵķ���Ϊ���߷���
	*1.����l ��xzƽ���ڵ�ͶӰ�����y���ת�� ����x����ָ����Ϊ0�㣩
	*2.����l ��xzƽ��ļн� ������λ������ʱ�Ƕ�Ϊ0�㣬���Ͽ�ʱ�Ƕ�Ϊ����*/
	void setViewAngleWithEyeFixed(float rotY, float rotZ);

	/*�����߱�*/
	void setRatioWH(float ratioWH);

	/*�ӵ����ߵ��ӽǹ۲쳡��
	*�����������������cam�Ѿ��趨�ò���������cam.apply()�ͻ���cam���ӽ���ʾ����*/
	void apply();

protected:
	/*ʹ�������������Ұ����*/
	void updatePerspective();

	/*�۾����۲�㣩��λ��*/
	float m_eyeX;
	float m_eyeY;
	float m_eyeZ;

	/*�۲����ģ����۲�㣩��λ��*/
	float m_centerX;
	float m_centerY;
	float m_centerZ;

	/*������Ұ������*/
	float m_aspect;//��Ұ��ȽǶ�
	float m_ratioWH;
	float m_near;
	float m_far;
};