// KMeansClustering.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Kmc.h"



int main()
{		
	double ndata[nd][train_examples];						//���̸��� ������ ���� �迭
	//double assinged_ndata[nd][train_examples];				//�Ҵ�� �迭�� ��ġ
	double new_centroid[nd][n_centroid];					//�߽��� 3���� ��ġ
	double old_centroid[nd][n_centroid];
	double J;
	Kmc a;
	int count[3];
	a.load_data_train(ndata);										 //������ ���

	a.initialize_centroid(new_centroid, ndata);									//�߽��� ��ġ �ʱ�ȭ

	for (int i = 0; i < iter; i++)										//���� �з�, �߽��� �̵� �ݺ�
	{
		
		//std::cout << "-----" << std::endl;
		J = a.assign_and_shift(new_centroid, ndata, count);
		
		
		//if (k = a.measure_distance(new_centroid, old_centroid) < er)
		{
			//break;
		}
		if (i % 100 == 0)
		{
			for (int j = 0; j < nd; j++)
			{
				std::cout << "   " << new_centroid[j][0] << "   " << new_centroid[j][1] << "    " << new_centroid[j][2] << std::endl;
				
			}
			std::cout << "distortion:------>" << J << std::endl;
			std::cout << "---" << count[0] << "---" << count[1] << "---" << count[2] << std::endl;
		}
			
	}

	a.predict(new_centroid);



    return 0;
}

