#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
#include <vector>

class Data {
	std::vector<int> *feature_vector;
	std::string label;

public:
	Data();
	~Data();

	void set_feature_vector(std::vector<int> *);
	void append_to_feature_vector(int);
	void set_label(std::string);

	int get_feature_vector_size();
	std::string get_label();

	std::vector<int> *get_feature_vector();
};

#endif
