#include "Matrix.h"

Matrix::Matrix(double** elements, int rows, int collumns) : elements(elements), rows(rows), collumns(collumns) {}

Matrix::Matrix(const Matrix& toCopy) {
	this->collumns = toCopy.collumns;
	this->rows = toCopy.rows;

	this->elements = (double**)malloc(toCopy.rows * sizeof(double*));
	for (int i = 0; i < toCopy.rows; i++) {
		this->elements[i] = (double*)malloc(toCopy.collumns * sizeof(double));
	}

	for (int i = 0; i < toCopy.rows; i++) {
		for (int j = 0; j < toCopy.collumns; j++) {
			this->elements[i][j] = toCopy.elements[i][j];
		}
	}
}

Matrix::Matrix(int rows, int collumns, bool isRandom) {
	double** elementTests = (double**)malloc(rows * sizeof(double*));
	for (int i = 0; i < rows; i++) {
		elementTests[i] = (double*)malloc(collumns * sizeof(double));
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < collumns; j++) {
			if (isRandom) elementTests[i][j] = (double)rand();
			else elementTests[i][j] = i == j ? 1 : 0;
		}
	}

	this->elements = elementTests;
	this->rows = rows;
	this->collumns =  collumns;
}

Matrix::~Matrix(){
	for (int i = 0; i < this->rows; i++) {
		delete this->elements[i];
	}
}

int Matrix::getRows() const{
	return this->rows;
}
int Matrix::getCollumns() const{
	return this->collumns;
}

double Matrix::getElement(int row, int collumn) const {
	if (row < 0 || row > this->rows || collumn < 0 || collumn > this->collumns) return -1;

	return this->elements[row][collumn];
}

int* Matrix::size() const{
	int size[2] = { this->rows, this->collumns };
	return size;
}
double Matrix::getDeterminant(){
	if (!this->isSquareMatrix()) return NULL;
	if (this->determinant) return this->determinant;

	if (this->collumns == 2) {
		return this->getElement(0, 0) * this->getElement(1, 1) - this->getElement(0, 1) * this->getElement(1, 0);
	}

	this->determinant = this->getDiagonalProductsSum() - this->getDiagonalProductsSum(true);

	return this->determinant;
}

bool Matrix::isSquareMatrix() const {
	return this->rows == this->collumns && this->rows > 0;
}

bool Matrix::isIdentityMatrix() const {
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->collumns; j++) {
			if (i == j && this->getElement(i, j) != 1) return false;
			if (i != j && this->getElement(i, j) != 0) return false;
		}
	}

	return true;
}


double Matrix::getDiagonalProductsSum(bool invert_direction) const {

	double productsSum = 0;
	if (invert_direction) {
		for (int i = this->collumns - 1; i >= 0; i--) {
			double diagonalProduct = 1;
			int targetCollumn = i;
			for (int j = 0; j < this->rows; j++) {
				diagonalProduct *= this->getElement(j, targetCollumn);
				targetCollumn += targetCollumn == 0? this->collumns - 1 : -1;
			}
			productsSum += diagonalProduct;
		}
	}
	else {
		for (int i = 0 ; i < this->collumns; i++) {
			double diagonalProduct = 1;
			int targetCollumn = i;
			for (int j = 0; j < this->rows; j++) {
				diagonalProduct *= this->getElement(j, targetCollumn);
				targetCollumn += targetCollumn + 1 == this->collumns ? -targetCollumn: 1;
			}
			productsSum += diagonalProduct;
		}
	}
	return productsSum;
}


Matrix Matrix::transposed() const{
	double** newMatrixElements = (double**)malloc(this->collumns * sizeof(double*));
	for (int i = 0; i < this->collumns; i++) {
		newMatrixElements[i] = (double*)malloc(this->rows * sizeof(double));
	}

	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->collumns; j++) {
			newMatrixElements[j][i] = this->getElement(i,j);
		}
	}

	Matrix result(newMatrixElements, this->collumns, this->rows);

	return result;
}

double Matrix::cofactor(int row, int collumn) {
	double** auxiliarElements = (double**)malloc((this->rows - 1) * sizeof(double*));
	for (int i = 0; i < this->rows - 1; i++) {
		auxiliarElements[i] = (double*)malloc((this->collumns - 1) * sizeof(double));
	}

	for (int i = 0; i < this->rows - 1; i++) {
		for (int j = 0; j < this->collumns - 1; j++) {
			int auxRow = i < row ? i : i + 1;
			int auxCollumn = j < collumn ? j : j + 1;
			auxiliarElements[i][j] = this->getElement(auxRow, auxCollumn);
		}
	}

	Matrix auxiliar(auxiliarElements, this->rows - 1, this->collumns - 1);
	return auxiliar.getDeterminant() * pow(-1, row + collumn + 2);
}

Matrix Matrix::cofactorMatrix() {
	double** auxiliarElements = (double**)malloc((this->rows) * sizeof(double*));
	for (int i = 0; i < this->rows; i++) {
		auxiliarElements[i] = (double*)malloc((this->collumns) * sizeof(double));
	}

	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->collumns; j++) {
			auxiliarElements[i][j] = this->cofactor(i, j);
		}
	}

	return Matrix(auxiliarElements, this->rows, this->collumns);
}

Matrix Matrix::inverseMatrix() {
	Matrix cof = this->cofactorMatrix();
	double det = this->getDeterminant();

	return cof.transposed() * (1 / det);
}

Matrix Matrix::operator+(const Matrix& otherMatrix) const{

	Matrix result = otherMatrix;

	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.collumns; j++) {
			result.elements[i][j] = this->elements[i][j] + otherMatrix.elements[i][j];
		}
	}

	return result;
}

Matrix Matrix::operator-() const {
	return *this * (-1);
}

Matrix Matrix::operator-(const Matrix& otherMatrix) const{
	return *this + (- otherMatrix);
}

Matrix Matrix::operator*(const Matrix& otherMatrix) const{
	double** newMatrixElements = (double**)malloc(this->rows * sizeof(double*));
	for (int i = 0; i < this->rows; i++) {
		newMatrixElements[i] = (double*)malloc(otherMatrix.collumns * sizeof(double));
	}

	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < otherMatrix.collumns; j++) {
			double element = 0;
			for (int k = 0; k < this->collumns; k++) {
				element += this->elements[i][k] * otherMatrix.elements[k][j];
			}
			newMatrixElements[i][j] = element;
		}
	}

	Matrix result(newMatrixElements, this->rows, otherMatrix.collumns);
	return result;
}

Matrix Matrix::operator*(const double right) const{

	Matrix result = *this;
	
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.collumns; j++) {
			result.elements[i][j] = right * this->elements[i][j];
		}
	}

	return result;
}

Matrix Matrix::operator/(const double right) const{
	return *this * (1 / right);
}

bool Matrix::operator==(const Matrix& otherMatrix) const {
	if (this->size() != otherMatrix.size()) return false;
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->collumns; j++) {
			if (this->elements[i][j] != otherMatrix.elements[i][j]) return false;
		}
	}

	return true;
}

bool Matrix::operator!=(const Matrix& otherMatrix) const {
	return !(*this == otherMatrix);
}

ostream& operator<<(ostream& os, const Matrix& matrix) {
	for (int i = 0; i < matrix.getRows(); i++) {
		if(i != 0) os << endl;
		for (int j = 0; j < matrix.getCollumns(); j++) {
			os << matrix.getElement(i,j) << " ";
		}
	}
	return os;
}

Matrix Matrix::operator!() {
	return this->inverseMatrix();
}