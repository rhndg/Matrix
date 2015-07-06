#include "../include/Matrix.hpp"

int main(int argc, char** argv){
	Matrix a = Matrix(10,8,Matrix::IDENTITY);
	a.printMatrix("test.txt");
	cout<<a.determinant();
	int t;
	cin >> t;
	a.linCombRow(0, 4, 2);
	a.printMatrix("changed.txt");
	return 0;
}