#ifndef MATRIX_H

#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;

class Matrix{
private:
	float tolerance = 0.000001;
	bool order1(pair<int,int>p1,pair<int,int>p2);
public:
	enum matTypes{RANDOM,IDENTITY,ZERO};
	/**
	dimension of matrix
	**/
	pair<int,int> dim;
	/**
	true if matrix is dense
	**/
	bool isDense;
	/**
	each vector is a column the int is the index of matrixElements
	**/
	int** denseMatrix;
	/**
	int index is Row number and vector first is col num and second is index if matrixElements
	**/
	map<int,map<int,int> > sparseMatrixRow;
	/**
	int index is Col number and vector first is row num and second is index if matrixElements
	**/
	map<int,map<int,int> > sparseMatrixCol;
	/**
	main elements in matrix
	**/
	vector<float> matrixElements;
	/**
	is true if augmented
	**/
	bool isAugment;
	/**
	augmented matrix
	**/
	Matrix* augMatrix;
	/**
	constructor for sparse dense and empty matrix
	sparse-((row,col)val)
	dense-dinamically allocated array (2d ) with dim N*M
	empty-sparse by default 0*0
	**/
	Matrix(map<pair<int,int>,float> sparse,int N,int M);
	Matrix(float** dense,int N,int M);
	Matrix(int N, int M, matTypes T);
	Matrix();
	Matrix(const Matrix &obj);

	~Matrix();
	/**
	Toggle between sparse and dense matrices
	**/
	void toggle();
	/**
	multiplies Matrix
	**/
	void set(int r,int c, float val);
	float get(int r,int c);
	void rowExchange(int r1,int r2);
	void colExchange(int c1,int c2);
	// r1->r1+k*r2
	void linCombRow(int r1,int r2, float k);
	// c1->c1+k*c2
	void linCombCol(int c1,int c2, float k);
	void scaleCol(int c,float k);
	void scaleRow(int r,float k);
	void augment(Matrix* m);
	bool isSymetric();
	double determinant();
	int getRank();
	void printMatrix(string s);
	void random(int maxMod);
	//&L &U &P
	vector<Matrix*> LUP();
	// Matrix* retAugment();
	Matrix* mult(Matrix* m);
	// Matrix* exp(int n);
	// Matrix* add(Matrix m);
	// Matrix* scale(float c);
	// Matrix* transpose();
	// Matrix* inverse();
	// Matrix* RRE();
	// Matrix* Cholesky();

};

#endif
