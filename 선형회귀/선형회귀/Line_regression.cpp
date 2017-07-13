#include "stdafx.h"
#include "Line_regression.h"
Line_regression::Line_regression()
{
}
Line_regression::~Line_regression()
{
}
void Line_regression::get_data()
{
	int a;
	std::cout << "������ �Է��� ����� ���ÿ�." << std::endl;
	std::cout << "1. �����͹迭 �����Է� 2. csv���� �ҷ�����:" << std::endl;
	std::cin >> a;
	switch (a)
	{
	case 1:
		type_data_array();
		break;
	case 2:
		load_data_array();
		break;
	default:
		std::cout << "1���̳� 2���� �Է¹޴´�." << std::endl;
	}
};
double Line_regression::gradiant_descent(double theta_old[])
{
	m = cnt + 1;
	//printf("%lf  %lf  %lf  %lf \n",theta_new[0], theta_new[1], theta_new[2],theta_new[3], theta_new[4]);
	sum[0] = 0;
	sum[1] = 0;
	sum[2] = 0;
	sum[3] = 0;
	sum[4] = 0;

	for(i = 0;i < m+1; i++)
	{
		y = data[i].output;
		hypo = theta_old[0] 
			+ theta_old[1] * data[i].value[0]
			+ theta_old[2] * data[i].value[1]
			+ theta_old[3] * data[i].value[2]
			+ theta_old[4] * data[i].value[3];
		sum[0] = sum[0] + (hypo - y) * 1;
		sum[1] = sum[1] + (hypo - y) * data[i].value[0];
		sum[2] = sum[2] + (hypo - y) * data[i].value[1];
		sum[3] = sum[3] + (hypo - y) * data[i].value[2];
		sum[4] = sum[4] + (hypo - y) * data[i].value[3];	
	}
	//cost_value = cost_value + (hypo - y)*(hypo - y) / (2 * m);
	//printf("%lf\n", cost_value);
			
	theta_new[0] = theta_old[0] - learning_rate * 1.0 / ((double)m) * sum[0];
	theta_new[1] = theta_old[1] - learning_rate * 1.0 / ((double)m) * sum[1];
	theta_new[2] = theta_old[2] - learning_rate * 1.0 / ((double)m) * sum[2];
	theta_new[3] = theta_old[3] - learning_rate * 1.0 / ((double)m) * sum[3];
	theta_new[4] = theta_old[4] - learning_rate * 1.0 / ((double)m) * sum[4];

	theta_old[0] = theta_new[0];
	theta_old[1] = theta_new[1];
	theta_old[2] = theta_new[2];
	theta_old[3] = theta_new[3];
	theta_old[4] = theta_new[4];
	//printf("%lf %lf %lf %lf\n\n", theta_old[1], theta_old[2], theta_old[3], theta_old[4]);
	return cost_value;
}

void Line_regression::prediction(double a[],double k[])
{

	printf("%lf %lf %lf %lf\n",a[1],a[2],a[3],a[4]);
	printf("%lf %lf %lf %lf\n\n", k[1], k[2], k[3], k[4]);
	y = k[0] + k[1] * a[1] + k[2] * a[2] + k[3] * a[3] + k[4] * a[4];

	m = 30;
	//for (i = 0; i < m; i++)
	//{

		//printf("%lf", data[i].output);
	//	cost_value= cost_value + 1.0 / (2 * m)*(y - data[i].output)*(y - data[i].output);
	//	printf("%lf\n", cost_value);
	//}


	printf("�������� %lf", y);

};
void Line_regression::type_data_array()
{

}
void Line_regression::load_data_array()
{
	//�Ʒ��� csv ������ ��� �迭�� �����ϴ� �����̴�.
	fopen_s(&pFile, "data2.csv", "rb");
	if (pFile != NULL)
	{
		while (!feof(pFile)) //������ ���� ������ ������ �ݺ��Ѵ�.
		{
			pstr = fgets(strTmp, sizeof(strTmp), pFile); // �� ���� �����Ѵ�. while�� �� �� ��ġ�� �� ���� �ٷ� ���� �� ����. (����:o,Ȯ��:x)
														 //printf("%d%d", cnt, rowcnt);
			if (rowcnt >= 1) //2��Ʒ��� �аڴٴ� �ǹ��̴�.
			{
				if (pstr == NULL)break;
				sscanf_s(pstr, "%[^','], %[^','], %[^','], %[^','],%s", // �ĸ� �ձ����� ���ڿ� �ѵ���� ����Ѵ�.
					value1, (unsigned)sizeof(char) * 10,
					value2, (unsigned)sizeof(char) * 10,
					value3, (unsigned)sizeof(char) * 10,
					value4, (unsigned)sizeof(char) * 10,
					//value5, (unsigned)sizeof(char) * 10,
					output, (unsigned)sizeof(char) * 10);
				//iris[cnt].output, (unsigned)sizeof(char)); //%s, %c�� ���, ����� ǥ���Ѵ�.

				data[cnt].value[0] = atof(value1);  //�ռ� ó���� ���ڿ� ��� �߿��� ���ڵ��� double�� ��ȯ�Ͽ� ���� ������������ �ٲ�.
				data[cnt].value[1] = atof(value2);
				data[cnt].value[2] = atof(value3);
				data[cnt].value[3] = atof(value4);
				//iris[cnt].value5 = atof(value5);
				data[cnt].output = atof(output);
				//printf("%lf  ", data[cnt].value[0]); //�ߵȴ�. ���! ������ ���� 5�� �� ... ���ѷ�ѷ� �Ѹ� ��������
				//printf("%lf  ", data[cnt].value[1]);
				//printf("%lf  ", data[cnt].value[2]);
				//printf("%lf\n ", data[cnt].value[3]);
				//printf("%lf\n", data[cnt].output);
				cnt++;

			}
			else
				rowcnt++;
		}
		printf("���� �б⸦ ���ƽ��ϴ� cnt������ %d.\n",cnt);
		fclose(pFile);
	}
	else
	{
		printf("fail");

	}

}

