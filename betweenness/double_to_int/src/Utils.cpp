#include "Utils.h"

Utils::Utils()
{
}

bool Utils::AreEqual(double a, double b)
{
	double EPSILON = 0.0000001;
	return fabs(a - b) < EPSILON;
}


Utils::~Utils()
{
}
