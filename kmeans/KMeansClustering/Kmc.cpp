#include "stdafx.h"
#include "Kmc.h"


Kmc::Kmc()
{
}


Kmc::~Kmc()
{
}
void Kmc::load_data_train(double data[][train_examples])
{//�Ʒ��� csv ������ ��� �迭�� �����ϴ� �����̴�.
	FILE *pFile;
	char *pstr;
	char strTmp[255];
	int cnt = 0;
	int rowcnt = 0;

	char value[4][10];


	fopen_s(&pFile, "train.csv", "rb");
	if (pFile != NULL)
	{
		while (!feof(pFile)) //������ ���� ������ ������ �ݺ��Ѵ�.
		{
			pstr = fgets(strTmp, sizeof(strTmp), pFile); // �� ���� �����Ѵ�. while�� �� �� ��ġ�� �� ���� �ٷ� ���� �� ����. (����:o,Ȯ��:x)
														 //printf("%d%d", cnt, rowcnt);
			if (rowcnt >= 0) 
			{
				if (pstr == NULL)break;
				sscanf_s(pstr, "%[^','], %[^','], %[^','], %[^',']", // �ĸ� �ձ����� ���ڿ� �ѵ���� ����Ѵ�.
					value[0], (unsigned)sizeof(char) * 10,
					value[1], (unsigned)sizeof(char) * 10,
					value[2], (unsigned)sizeof(char) * 10,
					value[3], (unsigned)sizeof(char) * 10);
				//iris[cnt].output, (unsigned)sizeof(char)); //%s, %c�� ���, ����� ǥ���Ѵ�.

				data[0][cnt] = atof(value[0]);  //�ռ� ó���� ���ڿ� ��� �߿��� ���ڵ��� double�� ��ȯ�Ͽ� ���� ������������ �ٲ�.
				data[1][cnt] = atof(value[1]);
				data[2][cnt] = atof(value[2]);
				data[3][cnt] = atof(value[3]);

				//printf("%lf  ", data[0][cnt]); 
				//printf("%lf  ", data[1][cnt]);
				//printf("%lf  ", data[2][cnt]);
				//printf("%lf  \n", data[3][cnt]);

				cnt++;
				if (cnt > train_examples - 1)
					break;

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

}
void Kmc::initialize_centroid(double cent[][n_centroid], double data[][train_examples])
{
	//�������ִ� �������� �ƹ��ų� 3���� ��Ʈ���̵忡 ����!
	
	//������ ����
	int a = 0;
	int b = 0;
	int c = 0;
	while (((a != b) && (a != c) && (b != c)) == 0)
	{
		srand(time(NULL));
		a = rand() % (train_examples);
		b = rand() % (train_examples);
		c = rand() % (train_examples);
	}
	std::cout <<"a����"<< a <<"b����"<< b <<"c����"<< c << std::endl;
	for (int i = 0; i < nd; i++)
	{
		cent[i][0] = data[i][a];
		cent[i][1] = data[i][b];
		cent[i][2] = data[i][c];
		std::cout << " " << cent[i][0] << "  " << cent[i][1] << " " << cent[i][2] << std::endl;
	}
	std::cout << " ------" << std::endl;

}
double Kmc::assign_and_shift(double cent[][n_centroid], double data1[][train_examples],int cnt[])
{
	double distance[n_centroid][train_examples];
	double cluster[nd][n_centroid];

	double J;

	J = Kmc::cal_train_distance(cent, data1, distance);
	Kmc::train_assign(distance, data1, cluster, cnt);
	Kmc::shift(cent, cluster, cnt);
	

	return J;
}
double Kmc::cal_train_distance(double cent[][n_centroid], double data[][train_examples], double distance[][train_examples])
{
	double val;
	double cost = 0;
	double temp[n_centroid][train_examples];

	for (int i = 0; i < train_examples; i++)
	{
		for (int j = 0; j < n_centroid; j++)
		{
			distance[j][i] = 0;
		}
	}

	for (int k = 0; k < n_centroid; k++)
	{
		for (int i = 0; i < train_examples; i++)
		{
			for (int j = 0; j < nd; j++)
			{
				val = cent[j][k] - data[j][i];
				distance[k][i] = distance[k][i] + val*val;
				temp[k][i] = distance[k][i];
				if (j == nd-1)
				{
				//	std::cout << distance[k][i] <<std::endl;
				}
			}
			distance[k][i] = std::sqrt(distance[k][i]);
		}
	}

	for (int k = 0; k < n_centroid; k++)
	{
		for (int i = 0; i < train_examples; i++)
		{
			cost = cost + temp[k][i];
		}
	}
	cost = cost / (train_examples);
	

	return cost;

}

void Kmc::train_assign(double distance[][train_examples], double data[][train_examples], double clus[][n_centroid],int count[])
{
	int c0 = 0;
	int c1 = 0;
	int c2 = 0;

	for (int i = 0; i < n_centroid ; i++)
	{
		for (int j = 0; j < nd; j++)
		{
			clus[j][i] = 0;
		}
	}

	//������ distnace�� ���ؼ� ������������ �Ҵ��Ŵ
	for(int i = 0; i < train_examples; i++)
	{
		if ( ( (distance[0][i] < distance[1][i]) && (distance[0][i] < distance[2][i])) == 1 )
		{
			for (int j = 0; j < nd; j++)
			{
				clus[j][0] = clus[j][0] + data[j][i];
				
			}
			count[0] = c0++;
		}

		if (((distance[1][i] < distance[0][i]) && (distance[1][i] < distance[2][i])) == 1)
		{
			for (int j = 0; j < nd; j++)
			{
				clus[j][1] = clus[j][1] + data[j][i];
				
			}
			count[1] = c1++;
		}

		if (((distance[2][i] < distance[1][i]) && (distance[2][i] < distance[0][i])) == 1)
		{
			for (int j = 0; j < nd; j++)
			{
				clus[j][2] = clus[j][2] + data[j][i];
				
			}
			count[2] = c2++;
		}
	}
	
}

void Kmc::shift(double cent[][n_centroid],double clus[][n_centroid], int count[])
{
	//centroid ���� �Ҵ�� �����Ϳ��� ��հ����� �ű�
	double sum[nd][n_centroid];

	for (int i = 0; i < n_centroid; i++)
	{
		for (int j = 0; j < nd; j++)
		{
			sum[j][i] = 0;
		}

	}

	for (int i = 0; i < n_centroid; i++)
	{
		for (int j = 0; j < nd; j++)
		{
			sum[j][i] = sum[j][i] + clus[j][i];
		}

	}



	for (int i = 0; i < n_centroid; i++)
	{
		for (int j = 0; j < nd; j++)
		{
			cent[j][i] = sum[j][i] / ((double)count[i]);
		}
	
	}


}

double Kmc::measure_distance(double new_[], double old_[])
{
	return 0;
}
void Kmc::load_data_test(double data[][test_examples])
{//�Ʒ��� csv ������ ��� �迭�� �����ϴ� �����̴�.
	FILE *pFile;
	char *pstr;
	char strTmp[255];
	int cnt = 0;
	int rowcnt = 0;

	char value[4][10];


	fopen_s(&pFile, "test.txt", "rb");
	if (pFile != NULL)
	{
		while (!feof(pFile)) //������ ���� ������ ������ �ݺ��Ѵ�.
		{
			pstr = fgets(strTmp, sizeof(strTmp), pFile); // �� ���� �����Ѵ�. while�� �� �� ��ġ�� �� ���� �ٷ� ���� �� ����. (����:o,Ȯ��:x)
														 //printf("%d%d", cnt, rowcnt);
			if (rowcnt >= 0) //1��Ʒ��� �аڴٴ� �ǹ��̴�.(0�϶� 1 , 1�϶� 2)
			{
				if (pstr == NULL)break;
				sscanf_s(pstr, "%[^','], %[^','], %[^','], %[^',']", // �ĸ� �ձ����� ���ڿ� �ѵ���� ����Ѵ�.
					value[0], (unsigned)sizeof(char) * 10,
					value[1], (unsigned)sizeof(char) * 10,
					value[2], (unsigned)sizeof(char) * 10,
					value[3], (unsigned)sizeof(char) * 10);
				//iris[cnt].output, (unsigned)sizeof(char)); //%s, %c�� ���, ����� ǥ���Ѵ�.

				data[0][cnt] = atof(value[0]);  //�ռ� ó���� ���ڿ� ��� �߿��� ���ڵ��� double�� ��ȯ�Ͽ� ���� ������������ �ٲ�.
				data[1][cnt] = atof(value[1]);
				data[2][cnt] = atof(value[2]);
				data[3][cnt] = atof(value[3]);

				//printf("%lf  ", data[0][cnt]);
				//printf("%lf  ", data[1][cnt]);
				//printf("%lf  ", data[2][cnt]);
				//printf("%lf  \n", data[3][cnt]);

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

}
void Kmc::predict(double cent[][n_centroid])
{
	int count[3];
	double data[nd][test_examples];
	double distance[n_centroid][test_examples];
	Kmc::load_data_test(data);
	Kmc::cal_test_distance(cent, data, distance);
	Kmc::test_assign(distance, data, count);

	//std::cout << "���� ���� ������" << count[2] << std::endl;

	

}
void Kmc::cal_test_distance(double cent[][n_centroid], double data[][test_examples], double distance[][test_examples])
{
	double val;

	for (int i = 0; i < test_examples; i++)
	{
		for (int j = 0; j < n_centroid; j++)
		{
			distance[j][i] = 0;
		}
	}

	for (int k = 0; k < n_centroid; k++)
	{
		for (int i = 0; i < test_examples; i++)
		{
			for (int j = 0; j < nd; j++)
			{
				val = cent[j][k] - data[j][i];
				distance[k][i] = distance[k][i] + val*val;
				if (j == nd - 1)
				{
					//	std::cout << distance[k][i] <<std::endl;
				}
			}
			distance[k][i] = std::sqrt(distance[k][i]);
		}
	}
}
void Kmc::test_assign(double distance[][test_examples], double data[][test_examples], int count[])
{
	int c0 = 0;
	int c1 = 0;
	int c2 = 0;
	//������ distnace�� ���ؼ� ������������ �Ҵ��Ŵ
	for (int i = 0; i < test_examples; i++)
	{
		if (((distance[0][i] < distance[1][i]) && (distance[0][i] < distance[2][i])) == 1)
		{
			c0++;
		}

		if (((distance[1][i] < distance[0][i]) && (distance[1][i] < distance[2][i])) == 1)
		{
			c1++;
		}

		if (((distance[2][i] < distance[1][i]) && (distance[2][i] < distance[0][i])) == 1)
		{
			c2++;
		}
	}
	std::cout << "---" << c0 << "---" << c1 << "---" << c2 << std::endl;

}
