#pragma once
#include "vecx.h"

template <typename T>
class Vec3 :public VecX<T>
{
public:
	Vec3();
	Vec3(const Vec3<T>& xValue);
	Vec3(T tParam01, T tParam02, T tParam03);
	Vec3(std::initializer_list<T> il);
	void operator=(const Vec3<T>& xValue);
	~Vec3();

public:
	T& x;
	T& y;
	T& z;

};

template <typename T>
void Vec3<T>::operator=(const Vec3<T>& xValue)
{
	VecX<T>::Copy(xValue);
}


template <typename T>
Vec3<T>::Vec3() :VecX<T>(3)
, x(VecX<T>::m_tParam[0])
, y(VecX<T>::m_tParam[1])
, z(VecX<T>::m_tParam[2])
{
}

template <typename T>
Vec3<T>::Vec3(T tParam01, T tParam02, T tParam03) :VecX<T>({ tParam01, tParam02,tParam03 })
, x(VecX<T>::m_tParam[0])
, y(VecX<T>::m_tParam[1])
, z(VecX<T>::m_tParam[2])
{
}
template <typename T>
Vec3<T>::Vec3(std::initializer_list<T> il) : VecX<T>(il)
, x(VecX<T>::m_tParam[0])
, y(VecX<T>::m_tParam[1])
, z(VecX<T>::m_tParam[2])
{
}
template <typename T>
Vec3<T>::Vec3(const Vec3<T>& xValue) : VecX<T>(xValue)
, x(VecX<T>::m_tParam[0])
, y(VecX<T>::m_tParam[1])
, z(VecX<T>::m_tParam[2])
{

}

template <typename T>
Vec3<T>::~Vec3()
{
}

