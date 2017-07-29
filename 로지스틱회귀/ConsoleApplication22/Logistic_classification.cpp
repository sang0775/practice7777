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
	std::cout << "데이터 입력할 방식을 고르시오." << std::endl;
	std::cout << "1. 데이터배열 직접입력 2. csv파일 불러오기:" << std::endl;
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
		std::cout << "1번이나 2번만 입력받는다." << std::endl;
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

	//printf("1번변환 끝-----\n");

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
	//printf("2번변환 끝-----\n");
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
	//printf("3번변환 끝-----\n");

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
				sscanf_s(pstr, "%[^','], %[^','], %[^','], %[^','], %s", // 컴마 앞까지를 문자열 한덩어리로 취급한다.
					value1, (unsigned)sizeof(char) * 10,
					value2, (unsigned)sizeof(char) * 10,
					value3, (unsigned)sizeof(char) * 10,
					value4, (unsigned)sizeof(char) * 10,
					output, (unsigned)sizeof(char) * 30);
				//%s, %c인 경우, 사이즈를 표시한다.
				//문자열의 경우 지정해준 size값이 입력된 string값의 크기보다 작을 경우 데이터 입력이 안되고, 에러가 뜨지 않음

				data[cnt].value[0] = 1;
				data[cnt].value[1] = atof(value1);  //앞서 처리한 문자열 덩어리 중에서 숫자들은 double로 변환하여 숫자 데이터형으로 바꿈.
				data[cnt].value[2] = atof(value2);
				data[cnt].value[3] = atof(value3);
				data[cnt].value[4] = atof(value4);
				strcpy(output_original[cnt], output);

				printf("%lf  ", data[cnt].value[0]); 
				printf("%lf  ", data[cnt].value[1]);
				printf("%lf  ", data[cnt].value[2]);
				printf("%lf  ", data[cnt].value[3]);
				printf("%lf  ", data[cnt].value[4]);
				printf("--%s-- \n", output_original[cnt]); //배열의 경우에 문자열을 넣을 때 동적으로 메모리 할당(선언)해줘야 문자열대입 가능. 
				cnt++;
			
			}
			else
				rowcnt++;
		}
		printf("파일 읽기를 마쳤습니다 cnt갯수는 %d.\n", cnt);
		fclose(pFile);
	}
	else
	{
		printf("fail");

	}
	

	Logistic_classification::output_converter();
}

//get_data -> load_data_array -> output_converter -> cal_grad(cal-hypo) -> gradiant_descent