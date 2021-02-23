#ifndef KNN_H
#define KNN_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "data.h"

class KNN {
	int k;
	std::vector<Data*> *neighbours;
	std::vector<Data*> *training_data;
	std::vector<Data*> *test_data;
	std::vector<Data*> *validation_data;

public:
	KNN(int);
	KNN();
	~KNN();

	void find_knearest(Data* query_point);
	void set_training_data(std::vector<Data*> *vect);
	void set_test_data(std::vector<Data*> *vect);
	void set_validation_data(std::vector<Data*> *vect);
	void set_k(int val);

	std::string predict();
	double calculate_distance(Data* query_point, Data* input);
	double validate_performance();
	double test_performance();
};

#endif
