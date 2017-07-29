// ConsoleApplication22.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
#pragma once
#include "stdafx.h"
#include "Logistic_classification.h"



int main()
{

	double theta1[weight];
	double theta2[weight];
	double theta3[weight];
	
	for (int i = 0; i < weight; i++)
	{
		theta1[i] = 0;
		theta2[i] = 0;
		theta3[i] = 0;
	}

	Logistic_classification::get_data();

	for (int cc = 0; cc < iter; cc++)
	{

		Logistic_classification::cal_grad(theta1, output1);
		//Logistic_classification::cal_grad(theta2, output2);
		//Logistic_classification::cal_grad(theta2, output3);

		Logistic_classification::gradiant_descent(theta1);
		//Logistic_classification::gradiant_descent(theta2);
		//Logistic_classification::gradiant_descent(theta3);

		if ((cc % 50000) == 0)
		{
			printf("%lf %lf %lf %lf %lf \n\n", theta1[0], theta1[1], theta1[2], theta1[3], theta1[4]);
			//printf("%d \n", cc);
		}
	}
	

    return 0;
}

