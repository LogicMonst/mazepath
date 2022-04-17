#pragma once
#include <initializer_list>
#include <assert.h>
#include <vcruntime_string.h>

template <typename T>
class VecX
{
public:
	//VecX();
	VecX(const VecX<T>& xValue);
	VecX(int nLength);
	VecX(std::initializer_list<T> il);
	~VecX();
	bool operator==(const VecX<T>& xValue);
	bool operator!=(const VecX<T>& xValue);
	T& operator[](const int& nIndex);
	const T& operator[](const int& nIndex) const;
	//void operator=(const VecX<T>& xValue);
	int size();


protected:
	void initWithLength(int nLength);
	void Copy(const VecX<T>& xValue);


protected:
	T* m_tParam;
	int m_nLength;

	T m_tDefault;
};

template <typename T>
VecX<T>::VecX(const VecX<T>& xValue)
{
	initWithLength(xValue.m_nLength);
	Copy(xValue);
}

//template <typename T>
//VecX<T>::VecX()
//	:m_nLength(0)
//	, m_tParam(nullptr)
//{
//
//}

template <typename T>
VecX<T>::VecX(int nLength)
{
	initWithLength(nLength);
}

template <typename T>
VecX<T>::VecX(std::initializer_list<T> il)
{
	initWithLength(il.size());
	int nLength = 0;
	for (auto myIterator = il.begin(); myIterator != il.end(); ++myIterator)
	{
		m_tParam[nLength++] = *(myIterator);
	}
}

template <typename T>
VecX<T>::~VecX()
{
	delete[] m_tParam;
	m_tParam = nullptr;
	m_nLength = 0;
}

template <typename T>
void VecX<T>::Copy(const VecX<T>& xValue)
{
	assert(m_nLength == xValue.m_nLength);
	memcpy(m_tParam, xValue.m_tParam, sizeof(T) * m_nLength);
}

template <typename T>
T& VecX<T>::operator[](const int& nIndex)
{
	if (nIndex < m_nLength)
	{
		return m_tParam[nIndex];
	}
	assert(false);
	return m_tDefault;
}

template <typename T>
const T& VecX<T>::operator[](const int& nIndex) const
{
	if (nIndex < m_nLength)
	{
		return m_tParam[nIndex];
	}
	assert(false);
	return m_tDefault;
}

template <typename T>
int VecX<T>::size()
{
	return m_nLength;
}

template <typename T>
void VecX<T>::initWithLength(int nLength)
{
	m_nLength = nLength;
	m_tParam = new T[m_nLength];
	memset(m_tParam, 0, sizeof(T) * m_nLength);
}


template <typename T>
bool VecX<T>::operator==(const VecX<T>& xValue)
{
	if (m_nLength != xValue.m_nLength)
	{
		return false;
	}
	for (int k = 0; k < m_nLength; ++k)
	{
		if (m_tParam[k] != xValue.m_tParam[k])
		{
			return false;
		}
	}
	return true;
}

template <typename T>
bool VecX<T>::operator!=(const VecX<T>& xValue)
{
	return !(*this == xValue);
}
