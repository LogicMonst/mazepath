#pragma once
#include "vecx.h"

template <typename T>
class Vec4 :public VecX<T>
{
public:
	Vec4();
	Vec4(const Vec4<T>& xValue);
	Vec4(T tParam01, T tParam02, T tParam03, T tParam04);
	Vec4(std::initializer_list<T> il);
	void operator=(const Vec4<T>& xValue);
	~Vec4();

public:
	T& x;
	T& y;
	T& width;
	T& height;

};

template <typename T>
void Vec4<T>::operator=(const Vec4<T>& xValue)
{
	VecX<T>::Copy(xValue);
}


template <typename T>
Vec4<T>::Vec4() :VecX<T>(4)
, x(VecX<T>::m_tParam[0])
, y(VecX<T>::m_tParam[1])
, width(VecX<T>::m_tParam[2])
, height(VecX<T>::m_tParam[3])
{
}

template <typename T>
Vec4<T>::Vec4(T tParam01, T tParam02, T tParam03, T tParam04) :VecX<T>({ tParam01, tParam02,tParam03,tParam04 })
, x(VecX<T>::m_tParam[0])
, y(VecX<T>::m_tParam[1])
, width(VecX<T>::m_tParam[2])
, height(VecX<T>::m_tParam[3])
{
}
template <typename T>
Vec4<T>::Vec4(std::initializer_list<T> il) : VecX<T>(il)
, x(VecX<T>::m_tParam[0])
, y(VecX<T>::m_tParam[1])
, width(VecX<T>::m_tParam[2])
, height(VecX<T>::m_tParam[3])
{
}
template <typename T>
Vec4<T>::Vec4(const Vec4<T>& xValue) : VecX<T>(xValue)
, x(VecX<T>::m_tParam[0])
, y(VecX<T>::m_tParam[1])
, width(VecX<T>::m_tParam[2])
, height(VecX<T>::m_tParam[3])
{

}

template <typename T>
Vec4<T>::~Vec4()
{
}

