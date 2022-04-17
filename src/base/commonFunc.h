#pragma once
#include <assert.h>

class CommonFunc
{
public :
	template <typename T>
	static T VecXAdd(T t1, T t2)
	{
		T tempValue;
		if (t1.size() != t2.size())
		{
			assert(false);
			return tempValue;
		}
		for (int k = 0; k < t1.size(); ++k)
		{
			tempValue[k] = t1[k] + t2[k];
		}
		return tempValue;
	}

	template <typename T>
	static T VecXMinus(T t1, T t2)
	{
		T tempValue;
		if (t1.size() != t2.size())
		{
			assert(false);
			return tempValue;
		}
		for (int k = 0; k < t1.size(); ++k)
		{
			tempValue[k] = t1[k] - t2[k];
		}
		return tempValue;
	}

	//nFlagΪ2,4,8...
	static bool HasFlag(const int& nValue,const int& nFlag)
	{
		return (nValue & nFlag) > 0;
	}
};
