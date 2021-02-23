#include "data_handler.h"

DataHandler::DataHandler() {
	data_array = new std::vector<Data*>;
	training_data = new std::vector<Data*>;
	test_data = new std::vector<Data*>;
	validation_data = new std::vector<Data*>;
}

DataHandler::~DataHandler() {
	if (data_array) delete data_array;
	if (training_data) delete training_data;
	if (test_data) delete test_data;
	if (validation_data) delete validation_data;
}

void DataHandler::read_everything(std::istream &in) {
	std::string line;
	std::string word;
	while (std::getline(in,line)) {
		std::stringstream ss{ line };
		Data* d = new Data();
		for (int i = 0; i < 7; ++i) {
			std::getline(ss,word,',');
			if (i <= 1) {
				if (word == "vhigh") d->append_to_feature_vector(-4);
				else if (word == "high") d->append_to_feature_vector(2);
				else if (word == "med") d->append_to_feature_vector(4);
				else if (word == "low") d->append_to_feature_vector(6);
			} else if (i == 2) {
				if (word == "2") d->append_to_feature_vector(0);
				else if (word == "3") d->append_to_feature_vector(1);
				else if (word == "4") d->append_to_feature_vector(2);
				else if (word == "5more") d->append_to_feature_vector(3);
			} else if (i == 3) {
				if (word == "2") d->append_to_feature_vector(-3);
				else if (word == "4") d->append_to_feature_vector(0);
				else if (word == "more") d->append_to_feature_vector(6);
			} else if (i == 4) {
				if (word == "small") d->append_to_feature_vector(-3);
				else if (word == "med") d->append_to_feature_vector(4);
				else if (word == "big") d->append_to_feature_vector(8);
			} else if (i == 5) {
				if (word == "high") d->append_to_feature_vector(20);
				else if (word == "med") d->append_to_feature_vector(10);
				else if (word == "low") d->append_to_feature_vector(-10);
			} else {
				d->set_label(word);
			}
		}
		data_array->push_back(d);
	}
	std::cout << "Successfully read and stored " << data_array->size() << " feature vectors." << std::endl;
}

void DataHandler::split_data() {
	std::unordered_set<int> used_indexes;
	int train_size = data_array->size() * TRAIN_SET_PERCENT;
	int test_size = data_array->size() * TEST_SET_PERCENT;
	int valid_size = data_array->size() * VALIDATION_PERCENT;

	// Training Data

	int count = 0;
	while (count < train_size) {
		int rand_index = rand() % data_array->size();
		if (used_indexes.find(rand_index) == used_indexes.end()) {
			training_data->push_back(data_array->at(rand_index));
			used_indexes.insert(rand_index);
			count++;
		}
	}

	// Test Data

	count = 0;
	while (count < test_size) {
		int rand_index = rand() % data_array->size();
		if (used_indexes.find(rand_index) == used_indexes.end()) {
			test_data->push_back(data_array->at(rand_index));
			used_indexes.insert(rand_index);
			count++;
		}
	}

	// Validation Data

	count = 0;
	while (count < valid_size) {
		int rand_index = rand() % data_array->size();
		if (used_indexes.find(rand_index) == used_indexes.end()) {
			validation_data->push_back(data_array->at(rand_index));
			used_indexes.insert(rand_index);
			count++;
		}
	}

	std::cout << "Training data : " << training_data->size() << std::endl;
	std::cout << "Test data : " << test_data->size() << std::endl;
	std::cout << "Validation data : " << validation_data->size() << std::endl;
}

void DataHandler::count_classes() {
	for (unsigned i = 0; i < data_array->size(); ++i) class_map[data_array->at(i)->get_label()]++;
	std::cout << "Successfully Extracted " << class_map.size() << " Unique Classes." << std::endl;
}

std::vector<Data*> *DataHandler::get_training_data() { return training_data; }

std::vector<Data*> *DataHandler::get_test_data() { return test_data; }

std::vector<Data*> *DataHandler::get_validation_data() { return validation_data; }
