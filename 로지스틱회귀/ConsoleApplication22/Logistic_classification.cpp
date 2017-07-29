#include "stdafx.h"
#include "Logistic_classification.h"



Logistic_classification::Logistic_classification()
{
}

Logistic_classification::~Logistic_classification()
{
}

void Logistic_classification::get_data()
{
	int a;
	std::cout << "������ �Է��� ����� ���ÿ�." << std::endl;
	std::cout << "1. �����͹迭 �����Է� 2. csv���� �ҷ�����:" << std::endl;
	std::cin >> a;
	switch (a)
	{
	case 1:
		Logistic_classification::type_data_array();
		break;
	case 2:
		Logistic_classification::load_data_array();
		break;
	default:
		std::cout << "1���̳� 2���� �Է¹޴´�." << std::endl;
	}
}

void Logistic_classification::output_converter()
{
	for (int i = 0; i < cnt; i++)
	{
		//printf("--%s-- \n", output_original[i]);
		if (strcmp(output_original[i], "Iris-setosa") == 0)
		{
			output1[i] = 1;
			//printf("%d ----\n", output1[i]);
		}
		else
		{
			output1[i] = 0;
			//printf("%d ----\n", output1[i]);
		}

	}

	//printf("1����ȯ ��-----\n");

	for (int i = 0; i < cnt; i++)
	{
		//printf("--%s-- \n", output_original[i]);
		if (strcmp(output_original[i], "Iris-versicolor") == 0)
		{
			output2[i] = 1;
			//printf("%d ----\n", output2[i]);
		}
		else
		{
			output2[i] = 0;
			//printf("%d ----\n", output2[i]);
		}
	}
	//printf("2����ȯ ��-----\n");
	for (int i = 0; i < cnt; i++)
	{
		//printf("--%s-- \n", output_original[i]);
		if (strcmp(output_original[i], "Iris-virginica") == 0)
		{
			output3[i] = 1;
			//printf("%d ----\n", output3[i]);
		}
		else
		{
			output3[i] = 0;
			//printf("%d ----\n", output3[i]);
		}
	}
	//printf("3����ȯ ��-----\n");

}

void Logistic_classification::cal_hypo(double hypo_part[],double theta_[]) 
{
	for (int i = 0; i < cnt; i++)
	{
		hypo_part[i] = 0;
		for (int j = 0; j < weight; j++)
		{
			hypo_part[i] = hypo_part[i] + theta_[j] * data[i].value[j];
		}
	}

	for (int i = 0; i < cnt; i++)
	{
		hypo_part[i] = Logistic_classification::Logistic_function(hypo_part[i]);
	}
}

void Logistic_classification::cal_grad(double theta[], int output[])
{
	double* hypo = new double[cnt];
	double* y = new double[cnt];

	Logistic_classification::cal_hypo(hypo, theta);

	for (int j = 0; j < weight; j++)
	{
		grad[j] = 0;

		for (int i = 0; i < cnt; i++)
		{
			y[i] = output[i];
			double x = data[i].value[j];
			grad[j] = grad[j] + (hypo[i] - y[i])*x;
		}
	}

	delete[] hypo;
	delete[] y;
};

double Logistic_classification::Logistic_function(double input)
{
	return (1.0) / (1.0 + exp(( -1.0 )*input));
}

double Logistic_classification::gradiant_descent(double theta_old[])
{
	double theta_new[weight];

	for (int j = 0; j < weight; j++)
	{
		theta_new[j] = theta_old[j] - learning_rate * grad[j] / (double)(cnt + 1);
	}
	for (int j = 0; j < weight; j++)
	{
		theta_old[j] = theta_new[j];
	}



	return 0;

}

void Logistic_classification::cost_function()
{

}

void Logistic_classification::predict(double theta11[],double theta22[], double theta33[])
{
	double* hypo1 = new double[cnt];
	double* hypo2 = new double[cnt];
	double* hypo3 = new double[cnt];

	//Logistic_classification::cal_hypo(hypo1, theta11);
	//Logistic_classification::cal_hypo(hypo2, theta22);
	//Logistic_classification::cal_hypo(hypo3, theta33);


}

void Logistic_classification::type_data_array()
{

}

void Logistic_classification::load_data_array()
{
	fopen_s(&pFile, "iris2.csv", "rb");
	if (pFile != NULL)
	{
		while (!feof(pFile)) 
		{
			pstr = fgets(strTmp, sizeof(strTmp), pFile); 
														
			if (rowcnt >= 0) 
			{
				if (pstr == NULL)break;
				sscanf_s(pstr, "%[^','], %[^','], %[^','], %[^','], %s", // �ĸ� �ձ����� ���ڿ� �ѵ���� ����Ѵ�.
					value1, (unsigned)sizeof(char) * 10,
					value2, (unsigned)sizeof(char) * 10,
					value3, (unsigned)sizeof(char) * 10,
					value4, (unsigned)sizeof(char) * 10,
					output, (unsigned)sizeof(char) * 30);
				//%s, %c�� ���, ����� ǥ���Ѵ�.
				//���ڿ��� ��� �������� size���� �Էµ� string���� ũ�⺸�� ���� ��� ������ �Է��� �ȵǰ�, ������ ���� ����

				data[cnt].value[0] = 1;
				data[cnt].value[1] = atof(value1);  //�ռ� ó���� ���ڿ� ��� �߿��� ���ڵ��� double�� ��ȯ�Ͽ� ���� ������������ �ٲ�.
				data[cnt].value[2] = atof(value2);
				data[cnt].value[3] = atof(value3);
				data[cnt].value[4] = atof(value4);
				strcpy(output_original[cnt], output);

				printf("%lf  ", data[cnt].value[0]); 
				printf("%lf  ", data[cnt].value[1]);
				printf("%lf  ", data[cnt].value[2]);
				printf("%lf  ", data[cnt].value[3]);
				printf("%lf  ", data[cnt].value[4]);
				printf("--%s-- \n", output_original[cnt]); //�迭�� ��쿡 ���ڿ��� ���� �� �������� �޸� �Ҵ�(����)����� ���ڿ����� ����. 
				cnt++;
			
			}
			else
				rowcnt++;
		}
		printf("���� �б⸦ ���ƽ��ϴ� cnt������ %d.\n", cnt);
		fclose(pFile);
	}
	else
	{
		printf("fail");

	}
	

	Logistic_classification::output_converter();
}

//get_data -> load_data_array -> output_converter -> cal_grad(cal-hypo) -> gradiant_descent