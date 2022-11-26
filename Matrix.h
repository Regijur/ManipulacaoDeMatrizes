#pragma once
#include <iostream>
#include <math.h>

using namespace std;

class Matrix
{
public:
	Matrix(double** elements, int rows, int collumns);
	Matrix(int rows, int collumns, bool isRandom = true);
	Matrix(const Matrix &toCopy);
	~Matrix();
	int getRows() const;
	int getCollumns() const;
	double getElement(int row, int collumn) const;
	int* size() const;
	double getDeterminant();
	Matrix transposed() const;
	double getDiagonalProductsSum(bool invert_direction = false) const;
	bool isSquareMatrix() const;
	bool isIdentityMatrix() const;
	double cofactor(int row, int collumn);
	Matrix cofactorMatrix();
	Matrix inverseMatrix();

	Matrix operator+(const Matrix& otherMatrix) const;
	Matrix operator-(const Matrix& otherMatrix) const;
	Matrix operator-() const;
	Matrix operator*(const Matrix& otherMatrix) const;
	Matrix operator*(const double right) const;
	Matrix operator/(const double right) const;
	bool operator!=(const Matrix& otherMatrix) const;
	bool operator==(const Matrix& otherMatrix) const;
	friend ostream& operator<<(ostream& os, const Matrix& matrix);
	Matrix operator!();

private:
	int rows;
	int collumns;
	double** elements;
	double determinant = NULL;
};

