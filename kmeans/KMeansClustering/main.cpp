// KMeansClustering.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Kmc.h"



int main()
{		
	double ndata[nd][train_examples];						//아이리스 데이터 담을 배열
	//double assinged_ndata[nd][train_examples];				//할당된 배열의 위치
	double new_centroid[nd][n_centroid];					//중심점 3개의 위치
	double old_centroid[nd][n_centroid];
	double J;
	Kmc a;
	int count[3];
	a.load_data_train(ndata);										 //데이터 담기

	a.initialize_centroid(new_centroid, ndata);									//중심점 위치 초기화

	for (int i = 0; i < iter; i++)										//점의 분류, 중심점 이동 반복
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

