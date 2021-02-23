#include "data.h"

Data::Data() { feature_vector = new std::vector<int>; }

Data::~Data() { if (feature_vector) delete feature_vector; }

void Data::set_feature_vector(std::vector<int> *vect) { feature_vector = vect; }

void Data::append_to_feature_vector(int val) { feature_vector->push_back(val); }

void Data::set_label(std::string val) { label = val; }

int Data::get_feature_vector_size() { return feature_vector->size(); }

std::string Data::get_label() { return label; }

std::vector<int> *Data::get_feature_vector() { return feature_vector; }
