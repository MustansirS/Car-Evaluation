#include "knn.h"
#include <iomanip>
#include <utility>
#include <algorithm>
#include <math.h>
#include <limits>
#include <map>
#include <set>
#include "data_handler.h"

struct Cmp
{
    bool operator() (const std::pair<unsigned, double> &a, const std::pair<unsigned, double> &b)
    {
        return a.second < b.second;
    }
};

KNN::KNN(int val) : k{val} {}

KNN::KNN() {}

KNN::~KNN() {}

void KNN::find_knearest(Data* query_point) {
	neighbours = new std::vector<Data*>;
	std::set<std::pair<unsigned,double>, Cmp> indexes;
	for (unsigned i = 0; i < training_data->size(); ++i) {
		indexes.insert(std::make_pair(i,calculate_distance(query_point,training_data->at(i))));
	}
	int count = 0;
	for (auto it : indexes) {
		neighbours->push_back(training_data->at(it.first));
		count++;
		if (count == k) break;
	}
}

void KNN::set_training_data(std::vector<Data*> *vect) { training_data = vect; }

void KNN::set_test_data(std::vector<Data*> *vect) { test_data = vect; }

void KNN::set_validation_data(std::vector<Data*> *vect) { validation_data = vect; }

void KNN::set_k(int val) { k = val; }

std::string KNN::predict() {
	std::map<std::string,int> class_freq;
	int max = 0;
	std::string label;
	for (unsigned i = 0; i < neighbours->size(); ++i) {
		class_freq[neighbours->at(i)->get_label()]++;
		if (class_freq[neighbours->at(i)->get_label()] > max) {
			max = class_freq[neighbours->at(i)->get_label()];
			label = neighbours->at(i)->get_label();
		}
	}
	delete neighbours;
	return label;
}

double KNN::calculate_distance(Data* query_point, Data* input) {
	double distance = 0.0;
	if (query_point->get_feature_vector_size() != input->get_feature_vector_size()) {
		std::cout << "Error, Size mismatch!" << std::endl;
		exit(1);
	}
	for (unsigned i = 0; i < query_point->get_feature_vector_size(); ++i) {
		distance += pow(query_point->get_feature_vector()->at(i)-input->get_feature_vector()->at(i),2);
	}
	distance = sqrt(distance);
	return distance;
}

double KNN::validate_performance() {
	double current_performance = 0;
	int count = 0;
	int data_index = 0;
	bool guessed = false;
	for (Data *query_point : *validation_data) {
		find_knearest(query_point);
		std::string prediction = predict();
		if (prediction == query_point->get_label()) {
			count++;
			guessed = true;
		} else guessed = false;
		data_index++;
		current_performance = ((double)count*100.000)/((double)data_index);
		std::cout << data_index << ". " << "Current Performance: " << std::fixed << std::setprecision(3) << current_performance << "   ";
		if (guessed) std::cout << "Guessed " << prediction << " correctly!" << std::endl;
		else std::cout << "I'm sorry :( I guessed " << prediction << " instead of " << query_point->get_label() << std::endl;
	}
	return current_performance;
}

double KNN::test_performance() {
	double current_performance = 0;
	int count = 0;
	int data_index = 0;
	bool guessed = false;
	for (Data *query_point : *test_data) {
		find_knearest(query_point);
		std::string prediction = predict();
		if (prediction == query_point->get_label()) {
			count++;
			guessed = true;
		} else guessed = false;
		data_index++;
		current_performance = ((double)count*100.000)/((double)data_index);
		std::cout << data_index << ". " << "Test Performance: " << std::fixed << std::setprecision(3) << current_performance << "   ";
		if (guessed) std::cout << "Guessed " << prediction << " correctly!" << std::endl;
		else std::cout << "I'm sorry :( I guessed " << prediction << " instead of " << query_point->get_label() << std::endl;
	}
	return current_performance;
}

int main() {
	DataHandler *dh = new DataHandler();
	std::ifstream datafile{"car.data"};
	dh->read_everything(datafile);
	dh->split_data();
	dh->count_classes();
	KNN *knn = new KNN();
	knn->set_training_data(dh->get_training_data());
	knn->set_test_data(dh->get_test_data());
	knn->set_validation_data(dh->get_validation_data());
	// double performance;
	knn->set_k(1);
	// double best = knn->validate_performance();
	// int best_k = 1;
	// for (int k = 2; k <= 30; ++k) {
	// 	knn->set_k(k);
	// 	performance = knn->validate_performance();
	// 	if (performance >= best) {
	// 		best_k = k;
	// 		best = performance;
	// 	}
	// }
	// knn->set_k(best_k);
	knn->test_performance();
	// std::cout << "The best k was " << best_k << std::endl;
	delete knn;
	delete dh;
}
