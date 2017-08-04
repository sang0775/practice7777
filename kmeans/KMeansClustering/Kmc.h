#pragma once


class Kmc
{
public:
	Kmc();
	~Kmc();

	void Kmc::load_data_train(double data[][train_examples]);
	void Kmc::initialize_centroid(double cent[][n_centroid], double data[][train_examples]);
	double Kmc::assign_and_shift(double cent[][n_centroid], double data1[][train_examples],int cnt[]);
	double Kmc::measure_distance(double new_[], double old_[]);
    void Kmc::load_data_test(double data[][test_examples]);
	void Kmc::predict(double cent[][n_centroid]);
	
private:
	
	double Kmc::cal_train_distance(double cent[][n_centroid], double data[][train_examples], double distance[][train_examples]);
	void Kmc::cal_test_distance(double cent[][n_centroid], double data[][test_examples], double distance[][test_examples]);
	void Kmc::train_assign(double distance[][train_examples], double data[][train_examples], double clus[][n_centroid], int count[]);
	void Kmc::test_assign(double distance[][test_examples], double data[][test_examples], int count[]);
	void Kmc::shift(double cent[][n_centroid], double clus[][n_centroid], int count[]);

};

