#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <iostream>
#include "data.h"
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <unordered_set>

class DataHandler {
	std::vector<Data*> *data_array;
	std::vector<Data*> *training_data;
	std::vector<Data*> *test_data;
	std::vector<Data*> *validation_data;

	int num_classes;
	int feature_vector_size;
	std::map<std::string,int> class_map;

	const double TRAIN_SET_PERCENT = 0.75;
	const double TEST_SET_PERCENT = 0.20;
	const double VALIDATION_PERCENT = 0.05;
public:
	DataHandler();
	~DataHandler();

	void read_everything(std::istream &in);
	void split_data();
	void count_classes();

	std::vector<Data*> *get_training_data();
	std::vector<Data*> *get_test_data();
	std::vector<Data*> *get_validation_data();
};

#endif
