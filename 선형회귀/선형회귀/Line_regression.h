#pragma once
#define learning_rate 0.00001
class Line_regression
{
public:
	Line_regression();
	~Line_regression();
	static void get_data();
	static double Line_regression::gradiant_descent(double theta_old[]);
	static void Line_regression::prediction(double a[],double k[]);
	
private:
	static void type_data_array();
	static void load_data_array();

};
struct data_array
{
	double value[4];
	double output;
}static data[150];
static FILE *pFile;
static char *pstr;
static char strTmp[255];
static char* token;
static int cnt, rowcnt;
static int i;
static char value1[10];
static char value2[10];
static char value3[10];
static char value4[10];
static char output[10];
static double sum[5];
static double cost_value;
static int c;
static double theta_new[5];
static double diff[4];
static int k;
static int m;
static double y;
static double some[4];
static double diff2;
static double hypo;