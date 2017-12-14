//单层 感知器代码
#include <iostream>
using namespace std;

int n = 0;


float calcMat(float * matrixesA, float *matrixesB, int numOfW)
{
	float tmp = 0;
	for (int i = 0; i < numOfW; i++)
	{
		tmp += matrixesA[i] * matrixesB[i];
	}
	return tmp;
}

float calcSgn(float value)
{
	if (value > 0 || value == 0)
		return 1;
	else
		return -1;
}

bool campare(float valueY, float valueX)
{
	if (valueY == valueX)
		return true;
	else
		return false;
}

void calcNewWeight(float lr, float *oldWeight, float *matrixesX, float valueD, float valueO, int numOfW)
{
	float *newWeight = (float*)malloc(numOfW*sizeof(float));
	for (int i = 0; i < numOfW; i++)
	{
		newWeight[i] = oldWeight[i] + lr*(valueD - valueO)*matrixesX[i];
	}
	memcpy(oldWeight, newWeight, numOfW*sizeof(float));
	free(newWeight);
}


void updateWeight(float *weight0, float *matX, float *matD,int numOfD,int numOfW)//numOfD 为期望输出的个数 numOfW为权重的个数
{
	int count = n % numOfD;
	n++;
	float xw = calcMat(weight0, &matX[count * numOfW], numOfW);
	float sgn = calcSgn(xw);

	bool c = campare(matD[count], sgn);
	if (!c)
	{
		calcNewWeight(0.1, weight0, &matX[count * numOfW], matD[count], sgn, numOfW);
		for (int i = 0; i < numOfW; i++)
			cout << weight0[i] << endl;
		cout << "----" << endl;
		updateWeight(weight0, matX, matD, numOfD, numOfW);
	}
	else
	{
		for (int i = 0; i < numOfD; i++)
		{
			float xwNew = calcMat(weight0, &matX[i * numOfW], numOfW);
			float sgnNew=calcSgn(xwNew);
			if (!campare(matD[i], sgnNew))
				updateWeight(weight0, matX, matD, numOfD, numOfW);
		}
		return;
	}
}

/*
matX[12] =	{   -1,  1,  -2,    0,//x1
				-1,  0, 1.5, -0.5, //x2
				-1, -1,   1,  0.5 };//x3
*/
int main()
{
	float weight0[4] = { 0.5, 1, -1, 0 };
	float matX[12] = { -1, 1, -2, 0, -1, 0, 1.5, -0.5, -1, -1, 1, 0.5 };
	float matD[3] = { -1, -1, 1 };
	updateWeight(weight0, matX, matD,3,4);








	//for (int i = 0; i < 4; i++)
	//	cout << weight1[i] << endl;

	return 0;
}