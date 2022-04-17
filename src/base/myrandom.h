#pragma once
#include <random>

class MyRandom
{
public:
	MyRandom();
	~MyRandom();
	static MyRandom* GetInstance();


	unsigned int getRandom(unsigned int nMax);	//[0,nMax)
	unsigned int getRandom();

	void resetSeed(int nSeed);

protected:
	bool init();

protected:
	static MyRandom* s_pMyRandom;
	static std::default_random_engine m_randomEngine;
};
