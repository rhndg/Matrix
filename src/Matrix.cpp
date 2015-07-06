#include "../include/Matrix.hpp"

Matrix::Matrix(map<pair<int,int>,float> sparse,int N,int M){
  dim=pair<int,int>(N,M);
  isDense=false;
  denseMatrix = new int*[N];
  for (int i = 0; i != N; i++)
	  denseMatrix[i] = new int[M];
  isAugment=false;
  srand(time(NULL));
}

Matrix::Matrix(float** dense,int N,int M){
  dim=pair<int,int>(N,M);
  isDense=true;
  denseMatrix=new int*[N];
  for (int i = 0; i != N; i++)
	  denseMatrix[i] = new int[M];
  for(int i=0;i!=M*N;i++){
    matrixElements.push_back(dense[i%N][i/N]);
    denseMatrix[i%N][i/N]=matrixElements.size()-1;
  }
  isAugment=false;
  srand(time(NULL));
}

Matrix::Matrix(int N, int M ,Matrix::matTypes T){
	dim = pair<int, int>(N, M);
	isDense = true;
	denseMatrix = new int*[N];
	for (int i = 0; i != N; i++)
		denseMatrix[i] = new int[M];

	for (int i = 0; i != M*N; i++){
		if (T == Matrix::IDENTITY && i%N == i / N)
			matrixElements.push_back(1);
		else
			matrixElements.push_back(0);
		denseMatrix[i%N][i / N] = matrixElements.size() - 1;
	}
	
	isAugment = false;
	srand(time(NULL));
	if (T == Matrix::RANDOM)
		random(10);
}

Matrix::Matrix(){
  dim=pair<int,int>(0,0);
  isDense=true;
  isAugment=false;
  srand(time(NULL));
}


Matrix::Matrix(const Matrix &obj){
	matrixElements = obj.matrixElements;
	isDense = obj.isDense;
	dim = obj.dim;
	if (isDense){
		denseMatrix = new int*[dim.first];
		for (int i = 0; i != dim.first; i++)
			denseMatrix[i] = new int[dim.second];
		for (int i = 0; i != dim.first*dim.second; i++){
			denseMatrix[i%dim.first][i / dim.first] = obj.denseMatrix[i%dim.first][i / dim.first];
		}
	}
	else{
		sparseMatrixCol = obj.sparseMatrixCol;
		sparseMatrixRow = obj.sparseMatrixRow;
	}
	isAugment = false;
}


Matrix::~Matrix(){
	for (int i = 0; i != dim.first; i++)
		delete[] denseMatrix[i];
	delete[] denseMatrix;
}

bool Matrix::order1(pair<int,int>p1,pair<int,int>p2){
	if(p2.first>p1.first)
		return true;
	if (p2.second > p1.second)
		return true;
	return false;
}
void Matrix::set(int r,int c, float val){
	if (abs(val) < tolerance)
		val = 0;
  if(isDense){
    matrixElements[denseMatrix[r][c]]=val;
  }
  else{
    //TODO
  }
}

float Matrix::get(int r,int c){
  if(isDense){
    return matrixElements[denseMatrix[r][c]];
  }
  else{
    //TODO
  }
}
void Matrix::rowExchange(int r1,int r2){
  if(isDense){
    for(int i=0;i!=dim.second;i++)
      swap(denseMatrix[r1][i],denseMatrix[r2][i]);
    if(isAugment) 
      for(int i=0;i!=augMatrix->dim.second;i++)
        swap(augMatrix->denseMatrix[r1][i],augMatrix->denseMatrix[r2][i]);
    }
  else{
    //TODO
  }
}
void Matrix::colExchange(int c1, int c2){
  if(isDense){
    for(int i=0;i!=dim.first;i++)
      swap(denseMatrix[i][c1],denseMatrix[i][c2]);
    if(isAugment)
      for(int i=0;i!=augMatrix->dim.first;i++)
        swap(augMatrix->denseMatrix[i][c1],augMatrix->denseMatrix[i][c2]);
    }
  else{
    //TODO
  }
}

void Matrix::linCombRow(int r1, int r2, float k){
  if(isDense){
    for(int i=0;i!=dim.second;i++)
      matrixElements[denseMatrix[r1][i]]+=k*matrixElements[denseMatrix[r2][i]];
    if(isAugment) 
      for(int i=0;i!=augMatrix->dim.second;i++)
        augMatrix->matrixElements[augMatrix->denseMatrix[r1][i]]+=k*augMatrix->matrixElements[augMatrix->denseMatrix[r2][i]];
    }
  else{
    //TODO
  }
}

void Matrix::linCombCol(int c1, int c2, float k){
  if(isDense){
    for(int i=0;i!=dim.first;i++)
      matrixElements[denseMatrix[i][c1]]+=k*matrixElements[denseMatrix[i][c2]];
    if(isAugment) 
      for(int i=0;i!=augMatrix->dim.first;i++)
        augMatrix->matrixElements[augMatrix->denseMatrix[i][c1]]+=k*augMatrix->matrixElements[augMatrix->denseMatrix[i][c2]];
    }
  else{
    //TODO
  }
}

void Matrix::scaleCol(int c, float k){
  if(isDense){
    for(int i=0;i!=dim.first;i++)
      matrixElements[denseMatrix[i][c]]*=k;
    if(isAugment) 
      for(int i=0;i!=augMatrix->dim.first;i++)
        augMatrix->matrixElements[augMatrix->denseMatrix[i][c]]*=k;
    }
  else{
    //TODO
  }
}
void Matrix::scaleRow(int r, float k){
  if(isDense){
    for(int i=0;i!=dim.second;i++)
      matrixElements[denseMatrix[r][i]]*=k;
    if(isAugment) 
      for(int i=0;i!=augMatrix->dim.second;i++)
        augMatrix->matrixElements[augMatrix->denseMatrix[r][i]]*=k;
    }
  else{
    //TODO
  }
}

void Matrix::augment(Matrix* m){
  augMatrix=m;
  isAugment = true;
}
bool Matrix::isSymetric(){
  if(dim.first!=dim.second)
    return false;
  if(isDense){
    for(int i=0;i!=dim.first;i++)
      for(int j=0;j!=i;j++)
        if(matrixElements[denseMatrix[i][j]]!=matrixElements[denseMatrix[j][i]])
          return false;
    return true;
  }
  else{
    //TODO
  }
}
void Matrix::printMatrix(string s){
	ofstream outFile;
	outFile.open(("../log/" + s).c_str());

	if (isDense){
		for (int i = 0; i != dim.first; i++){
			for (int j = 0; j != dim.second; j++)
				outFile << matrixElements[denseMatrix[i][j]]<<"\t";
			outFile << endl << endl;
		}
	}
	else{
		//TODO
	}
	outFile.close();
}
void Matrix::random(int maxMod){
	if (isDense){
		for (int i = 0; i != matrixElements.size(); i++)
			matrixElements[i] = float(rand() % maxMod);
	}
	else{
		//TODO
	}
}

double Matrix::determinant(){
	if (isDense){
		if (dim.first != dim.second)
			return 0;
		vector<Matrix*>LU=LUP();
		double det = 1;
		for (int i = 0; i != dim.first; i++){
			det *= LU[1]->get(i, i);
			if (abs(LU[1]->get(i, i)) < tolerance)
				return 0;
		}
		return det;
	}
	else{
		//TODO
	}
}

vector<Matrix*> Matrix::LUP(){
	if (isDense){
		Matrix* L;
		Matrix* U;
		Matrix* P;
		L = new  Matrix(dim.first, dim.first, Matrix::IDENTITY);
		P = new  Matrix(dim.first, dim.first, Matrix::ZERO);
		U = new  Matrix();
		*U = *this;
		vector<pair<int, int> > rs;
		vector<float> cs;
		vector<int> cr, ir;
		for (int i = 0; i != dim.first; i++){
			cr.push_back(i);
			ir.push_back(i);
		}
		

		int r = 0 , c = 0;
		while (c != dim.second){
			if (r == dim.first)
				break;

			int r_=r;
			while (abs(U->get(r_, c)) < tolerance){
				U->set(r_, c, 0);
				r_++;
				if (r_ == dim.first)
					break;
			}
			if (r_ != dim.first){
				if (r_ != r){
					U->rowExchange(r_, r);
					rs.push_back(pair<int, int>(r_, r));
					cs.push_back(0);
				}
				float pivot = U->get(r, c);
				for (int i = r + 1; i != dim.first; i++){
					if (U->get(i, c) != 0){
						rs.push_back(pair<int, int>(i, r));
						cs.push_back(-1.0*(U->get(i, c) / pivot));
						U->linCombRow(i, r, -(U->get(i, c) / pivot));
						U->set(i, c, 0);
					}
				}
				r++;
			}
			c++;
		}
		vector<pair<int, int> > rs_;
		vector<float > cs_;
		for (int i = rs.size() - 1; i != -1; i--){
			if (cs[i] == 0){
				swap(cr[rs[i].first], cr[rs[i].second]);
				ir[cr[rs[i].first]] = rs[i].first;
				ir[cr[rs[i].second]] = rs[i].second;
			}
			else{
				cs_.push_back(cs[i]);
				rs_.push_back(pair<int, int>(ir[rs[i].first], ir[rs[i].second]));
			}
		}
		for (int i = 0; i != rs_.size(); i++){
			L->linCombRow(rs_[i].first,rs_[i].second,-1*cs_[i]);
		}
		for (int i = 0; i != cr.size(); i++)
			P->set(i, cr[i], 1);

		Matrix* Ans[] = { L, U , P };
		return vector<Matrix*>(Ans, Ans + 3);
	}
	else{

	}
}

// int Matrix::getRank(){
// 	if (isDense){

// 	}
// 	else{
// 		//TODO
// 	}
// }

// Matrix* Matrix::retAugment(){
// 	if (isDense){

// 	}
// 	else{
// 		//TODO
// 	}
// }
Matrix* Matrix::mult(Matrix* m){
	if (dim.second != m->dim.first)
		return NULL;
	Matrix* Ans;
	Ans = new Matrix(dim.first,m->dim.second,Matrix::ZERO);
	if (isDense){
		for (int i = 0; i != Ans->dim.first*Ans->dim.second; i++){
			float sum = 0;
			for (int j = 0; j != dim.second; j++){
				sum += get(i / Ans->dim.second, j)*m->get(j, i % Ans->dim.second);
			}
			if (abs(sum) < tolerance)
				sum = 0;
			Ans->set(i / Ans->dim.second, i%Ans->dim.second, sum);
		}
		return Ans;
  }
  else{
    //TODO
  }
}
// Matrix* Matrix::exp(int n){
//   if (isDense){

//   }
//   else{
//     //TODO
//   }
// }
// Matrix* Matrix::add(Matrix m){
//   if (isDense){

//   }
//   else{
//     //TODO
//   }
// }
// Matrix* Matrix::scale(float c){
//   if (isDense){

//   }
//   else{
//     //TODO
//   }
// }
// Matrix* Matrix::transpose(){
// 	if (isDense){

// 	}
// 	else{
// 		//TODO
// 	}
// }
// Matrix* Matrix::inverse(){
// 	if (isDense){

// 	}
// 	else{
// 		//TODO
// 	}
// }
// Matrix* Matrix::RRE(){
// 	if (isDense){

// 	}
// 	else{
// 		//TODO
// 	}
// }
// Matrix* Matrix::Cholesky(){
//   if (isDense){

//   }
//   else{
//     //TODO
//   }
// }