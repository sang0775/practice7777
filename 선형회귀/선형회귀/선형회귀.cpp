// ����ȸ��.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Line_regression.h"


int main()
{
	int cc;
	double result;
	
	Line_regression::get_data();
	double theta_old_[5];
	theta_old_[0] = 1;
	theta_old_[1] = 1;
	theta_old_[2] = 1;
	theta_old_[3] = 1;
	theta_old_[4] = 1;
	cost_value = 0;

	for (cc = 0; cc < 2000; cc++)
	{
		cost_value=Line_regression::gradiant_descent(theta_old_);

	}
	printf("����ϰ� ��\n\n");
	printf("%lf\n\n", cost_value);
	printf("%lf %lf %lf %lf\n\n", theta_old_[1], theta_old_[2], theta_old_[3], theta_old_[4]);

	some[0] = 1;
	some[1] = 43;
	some[2] = 29;
	some[3] = 10;
	some[4] = 19;
	result = 0;
	printf("%lf %lf %lf %lf\n\n", theta_old_[1], theta_old_[2], theta_old_[3], theta_old_[4]);
	Line_regression::prediction(some,theta_old_);

    return 0;
}

