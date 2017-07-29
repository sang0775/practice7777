#pragma once


class Logistic_classification
{
public:
	Logistic_classification();
	~Logistic_classification();
	static void Logistic_classification::get_data();
	static double Logistic_classification::gradiant_descent(double theta_old[]);
	static void Logistic_classification::cost_function();

	static void Logistic_classification::cal_grad(double theta[], int output[]);
	static void Logistic_classification::cal_hypo(double hypo_part[], double theta_[]);
	static double Logistic_classification::Logistic_function(double input);

	static void Logistic_classification::predict(double theta11[], double theta22[], double theta33[]);

private:
	static void Logistic_classification::type_data_array();
	static void Logistic_classification::load_data_array();
	static void Logistic_classification::output_converter();


};
struct data_array
{
	double value[5];
}static data[250];

static char output_original[250][30];
static FILE *pFile;
static char *pstr;
static char strTmp[1000];
static char* token;
static int cnt, rowcnt;
static double grad[weight];
static char value1[10];
static char value2[10];
static char value3[10];
static char value4[10];
static char output[30];


static int output1[150];
static int output2[150];
static int output3[150];