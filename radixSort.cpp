#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

vector<int> *countingSort(vector<int> *A, int pow,int min) {
	vector<int> *C = new vector<int>(10);
	for (int i = 0; i < C->size(); i++) {
		C->at(i) = 0;
	}
	for (int i = 0; i < A->size(); i++) {
		C->at((A->at(i)-min) / pow % 10)++;
	}
	for (int i = 1; i < C->size(); i++) {
		C->at(i) = C->at(i) + C->at(i - 1);
	}
	vector<int> *B = new vector<int>(A->size());
	for (int i = A->size() - 1; i >= 0; i--) {
		B->at(C->at((A->at(i)-min) / pow % 10) - 1) = A->at(i);
		C->at((A->at(i)-min) / pow % 10)--;
	}
	for (int i = 0; i < A->size(); i++) {
		A->at(i) = B->at(i);
	}
	return A;
}
vector<int> *radixSort(vector<int>* A)
{
	int min = A->at(0);
	int max = A->at(0);
	for (int i = 0; i < A->size(); i++) {
		if (A->at(i) > max) max = A->at(i);
		if (A->at(i) < min) min = A->at(i);
	}
	int temp = max - min;
	int pow = 1;
	while (temp / pow > 0) {
		countingSort(A, pow, min);
		pow = pow * 10;
	}
	return A;
}
vector<int> *readFile(string filename) {
	vector<int> *A = new vector<int>();
	ifstream myfile(filename);
	if (myfile) {
		int value;
		while (myfile >> value) {
			A->push_back(value);
		}
		myfile.close();
		return A;
	}
	else {
		cout << "File can't be opened";
		exit(0);
	}
}
void outputFile(vector<int> *A) {
	ofstream myfile("out.txt");
	if (myfile) {
		for (int i = 0; i < A->size(); i++) {
			myfile << A->at(i) << " ";
		}
		myfile.close();
	}
	else {
		cout << "File can't be typed into!" << endl;
	}
}

int main(int argc, char** argv) {
	if (argc == 2) {
		outputFile(radixSort(readFile(argv[1])));
	}
	else
		cout << "Neveljavni argumenti: ARAdn1 x, kjer je x pot do datoteke." << endl;
	system("PAUSE");
	return 0;
}