#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <iomanip>
#include "checkfile.h"
#define GRAPH_DEEGREE 4
#define INF 999 
struct min_inf
{
	int min_i = 0, min_j=0;
	int weight =INF;
};

using namespace std;

int** size_mass(int& n, int& m) {
	int** mass = new int* [n];
	for (int i = 0; i < n; ++i) {
		mass[i] = new int[m];
	}
	return mass;
}

min_inf findMin_(int** matrix, int size, int start) {
	min_inf min;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (matrix[i][j] != INF && matrix[i][j] < min.weight) {
				min.min_i = i;
				min.min_j = j;
				min.weight = matrix[i][j];
			}
		}
	}
	return min;
}

void make_null(int** matrix, int size) {
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			matrix[i][j] = INF;
		}
	}
}

int** input_graph(ifstream& inp, int** matrix)
{
	int i, j;
	while (!inp.eof())
	{
		inp >> i >> j;
		inp >> matrix[i][j];
		matrix[j][i] = matrix[i][j];
	}
	return matrix;
}


int** find_MOT(int size, int** matrix, int** result, int start, set<int>& visited) {
	visited.insert(start);
	min_inf min;
	while (visited.size() != size) {
		min = findMin_(matrix, size, start);
		if (min.weight != INF) {
			if (visited.find(min.min_j) == visited.end()) {
				result[min.min_i][min.min_j] = min.weight;
				matrix[min.min_i][min.min_j] = matrix[min.min_j][min.min_i] = INF;
				visited.insert(min.min_j);
			}
			else {
				matrix[min.min_i][min.min_j] = matrix[min.min_j][min.min_i] = INF;
			}
		}
		else {
			start++;
		}
	}
	return result;
}

void print_matr(int** matr, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			cout << setw(4) << matr[i][j];
		}
		cout << endl;
	}
}


int main() {
	setlocale(LC_ALL, "Ru");
	int** graph,** MOT, size, exit;
	string _FNAME;
	ifstream filein;
	set<int> visited;
	
	do
	{
		cout << "Введите имя файла: \n";
		cin >> _FNAME;
		_FNAME = check_mask(_FNAME);
		filein.open(_FNAME, ios::in);
		filein >> size;
		graph = size_mass(size, size);
		MOT = size_mass(size, size);
		make_null(graph, size);
		make_null(MOT, size);
		graph = input_graph(filein, graph);
		filein.close();
		cout << "Исходный граф:\n";
		print_matr(graph, size);
		cout << endl;
		MOT = find_MOT(size, graph, MOT, 0, visited);
		cout << "Минимальное остовное дерево:\n";
		print_matr(MOT, size);
		delete[] graph;
		delete[] MOT;
		cout << "Продолжать работу с программой? 1.Yes 2.No\n";
		while (true)
		{
			cin >> exit;
			if (exit == 1 || exit == 2) break;
			cout << "Ошибка\n";
		}
	} while (exit !=2);
	return 0;
}