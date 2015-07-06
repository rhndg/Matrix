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
	if (T == Matrix::RANDOM)
		random(10000000);
	isAugment = false;
	srand(time(NULL));
}

Matrix::Matrix(){
  dim=pair<int,int>(0,0);
  isDense=true;
  isAugment=false;
  srand(time(NULL));
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
float Matrix::detHelper(vector<int> rows, vector<int> cols){
	if (rows.size() == 0)
		return 1;
	float sum=0,t=1;
	int r = rows[0];
	rows.erase(rows.begin());
	for (int i = 0; i != cols.size(); i++){
		vector<int> temp = cols;
		temp.erase(temp.begin() + i);
		if (get(r, cols[i])!=0)
			sum += t*get(r, cols[i])*detHelper(rows, temp);
		t *= -1;
	}
	return sum;
}
float Matrix::determinant(){
	if (isDense){
		if (dim.first != dim.second)
			return 0;
		vector<int>temp;
		for (int i = 0; i != dim.first; i++)
			temp.push_back(i);
		return detHelper(temp, temp);
	}
	else{
		//TODO
	}
}
// int Matrix::getRank(){
// 	if (isDense){

// 	}
// 	else{
// 		//TODO
// 	}
// }

// Matrix Matrix::retAugment(){
// 	if (isDense){

// 	}
// 	else{
// 		//TODO
// 	}
// }
// Matrix Matrix::mult(Matrix m){
//   if (isDense){

//   }
//   else{
//     //TODO
//   }
// }
// Matrix Matrix::exp(int n){
//   if (isDense){

//   }
//   else{
//     //TODO
//   }
// }
// Matrix Matrix::add(Matrix m){
//   if (isDense){

//   }
//   else{
//     //TODO
//   }
// }
// Matrix Matrix::scale(float c){
//   if (isDense){

//   }
//   else{
//     //TODO
//   }
// }
// Matrix Matrix::transpose(){
// 	if (isDense){

// 	}
// 	else{
// 		//TODO
// 	}
// }
// Matrix Matrix::inverse(){
// 	if (isDense){

// 	}
// 	else{
// 		//TODO
// 	}
// }
// Matrix Matrix::RRE(){
// 	if (isDense){

// 	}
// 	else{
// 		//TODO
// 	}
// }
// Matrix Matrix::Cholesky(){
//   if (isDense){

//   }
//   else{
//     //TODO
//   }
// }