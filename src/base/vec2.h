#pragma once
#include "vecx.h"

template <typename T>
class Vec2 :public VecX<T>
{
public:
	Vec2();
	Vec2(const Vec2<T>& xValue);
	Vec2(T tParam01, T tParam02);
	Vec2(std::initializer_list<T> il);
	void operator=(const Vec2<T>& xValue);
	~Vec2();

public:
	T& x;
	T& y;

};

template <typename T>
void Vec2<T>::operator=(const Vec2<T>& xValue)
{
	VecX<T>::Copy(xValue);
}


template <typename T>
Vec2<T>::Vec2() :VecX<T>(2)
, x(VecX<T>::m_tParam[0])
, y(VecX<T>::m_tParam[1])
{
}

template <typename T>
Vec2<T>::Vec2(T tParam01, T tParam02) :VecX<T>({ tParam01, tParam02 })
, x(VecX<T>::m_tParam[0])
, y(VecX<T>::m_tParam[1])
{
}
template <typename T>
Vec2<T>::Vec2(std::initializer_list<T> il) : VecX<T>(il)
, x(VecX<T>::m_tParam[0])
, y(VecX<T>::m_tParam[1])
{
}
template <typename T>
Vec2<T>::Vec2(const Vec2<T>& xValue) : VecX<T>(xValue)
, x(VecX<T>::m_tParam[0])
, y(VecX<T>::m_tParam[1])
{

}

template <typename T>
Vec2<T>::~Vec2()
{
}

