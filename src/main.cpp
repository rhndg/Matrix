#include "../include/Matrix.hpp"

int main(int argc, char** argv){
	Matrix a = Matrix(100, 100, Matrix::RANDOM);
	a.scaleCol(6, 0);
	a.linCombCol(6, 4, 2); 

	a.printMatrix("a.txt");
	vector<Matrix*>LUP = a.LUP();
	LUP[0]->printMatrix("L.txt");
	LUP[1]->printMatrix("U.txt");
	LUP[2]->printMatrix("P.txt");
	LUP[0]->mult(LUP[1])->printMatrix("LU");
	cout << a.determinant() << endl;
	
	int t;
	cin >> t;
	return t;
}