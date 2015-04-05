#pragma once

#include "MapFunction.h"

template <typename T>

/*�����ࡣ���ڱ�ʾһ�κ�����������һ����Χ����һ����Χ������ӳ�䡣������[0, 200]����ӳ�䵽[200, 500]
*��ѡģ�壺���͡�������*/
class LinearMap : public MapFunction<T>{
public:
	LinearMap<T>()
	{
	}

	/*����Χ����һ��ӳ�亯��*/
	LinearMap<T>(T fromRange[2], T toRange[2])
	{
		this->fromRange[0] = fromRange[0];
		this->fromRange[1] = fromRange[1];
		this->toRange[0] = toRange[0];
		this->toRange[1] = toRange[1];
	}

	/*����Χ����һ��ӳ�亯��*/
	LinearMap<T>(T fromRange0, T fromRange1, T toRange0, T toRange1)
	{
		this->fromRange[0] = fromRange0;
		this->fromRange[1] = fromRange1;
		this->toRange[0] = toRange0;
		this->toRange[1] = toRange1;
	}

	/*����һ��ӳ��Ľ��*/
	T map(T from)
	{
		return (toRange[1] - toRange[0])/(fromRange[1] - fromRange[0])*(from - fromRange[0]) + toRange[0];
	}

protected:
	T fromRange[2];
	T toRange[2];
};