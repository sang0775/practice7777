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
	std::cout << "데이터 입력할 방식을 고르시오." << std::endl;
	std::cout << "1. 데이터배열 직접입력 2. csv파일 불러오기:" << std::endl;
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
		std::cout << "1번이나 2번만 입력받는다." << std::endl;
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


	printf("예측값은 %lf", y);

};
void Line_regression::type_data_array()
{

}
void Line_regression::load_data_array()
{
	//아래는 csv 파일을 열어서 배열로 저장하는 과정이다.
	fopen_s(&pFile, "data2.csv", "rb");
	if (pFile != NULL)
	{
		while (!feof(pFile)) //파일의 끝에 도착할 때까지 반복한다.
		{
			pstr = fgets(strTmp, sizeof(strTmp), pFile); // 한 줄을 저장한다. while을 한 번 거치면 그 다음 줄로 가는 것 같다. (추측:o,확신:x)
														 //printf("%d%d", cnt, rowcnt);
			if (rowcnt >= 1) //2행아래로 읽겠다는 의미이다.
			{
				if (pstr == NULL)break;
				sscanf_s(pstr, "%[^','], %[^','], %[^','], %[^','],%s", // 컴마 앞까지를 문자열 한덩어리로 취급한다.
					value1, (unsigned)sizeof(char) * 10,
					value2, (unsigned)sizeof(char) * 10,
					value3, (unsigned)sizeof(char) * 10,
					value4, (unsigned)sizeof(char) * 10,
					//value5, (unsigned)sizeof(char) * 10,
					output, (unsigned)sizeof(char) * 10);
				//iris[cnt].output, (unsigned)sizeof(char)); //%s, %c인 경우, 사이즈를 표시한다.

				data[cnt].value[0] = atof(value1);  //앞서 처리한 문자열 덩어리 중에서 숫자들은 double로 변환하여 숫자 데이터형으로 바꿈.
				data[cnt].value[1] = atof(value2);
				data[cnt].value[2] = atof(value3);
				data[cnt].value[3] = atof(value4);
				//iris[cnt].value5 = atof(value5);
				data[cnt].output = atof(output);
				//printf("%lf  ", data[cnt].value[0]); //잘된다. 우왕! 지금은 새벽 5시 반 ... 씨뿌루뿌루 넘모 어려워요옹
				//printf("%lf  ", data[cnt].value[1]);
				//printf("%lf  ", data[cnt].value[2]);
				//printf("%lf\n ", data[cnt].value[3]);
				//printf("%lf\n", data[cnt].output);
				cnt++;

			}
			else
				rowcnt++;
		}
		printf("파일 읽기를 마쳤습니다 cnt갯수는 %d.\n",cnt);
		fclose(pFile);
	}
	else
	{
		printf("fail");

	}

}

