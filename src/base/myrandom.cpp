#include "myrandom.h"
#include <time.h>
#include <windows.h>


MyRandom* MyRandom::s_pMyRandom = nullptr;

std::default_random_engine MyRandom::m_randomEngine;

MyRandom::MyRandom()
{

}

MyRandom::~MyRandom()
{

}

bool MyRandom::init()
{
	auto tempMax = (m_randomEngine.max)();
	auto tempTme = time(0);
	m_randomEngine.seed(GetTickCount64() % tempMax);
	m_randomEngine.discard(tempTme%5099);

	return true;
}

MyRandom* MyRandom::GetInstance()
{
	if (!s_pMyRandom)
	{
		s_pMyRandom = new MyRandom();
		s_pMyRandom->init();
	}
	return s_pMyRandom;
}

unsigned int MyRandom::getRandom(unsigned int nMax)
{
	return m_randomEngine() % nMax;
}

unsigned int MyRandom::getRandom()
{
	return m_randomEngine();
}

void MyRandom::resetSeed(int nSeed)
{
	m_randomEngine.seed(nSeed);
}

