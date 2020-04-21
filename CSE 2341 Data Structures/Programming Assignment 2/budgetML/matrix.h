#ifndef BUDGETMATRIX
#define BUDGETMATRIX

#include <iostream>
#include "../DSlib/DSVector.h"

class Matrix{
	private:
		double* matrix = nullptr;
		int rows = 0;
		int columns = 0;

	public:
		Matrix(){}
		Matrix(int, int);
		Matrix(int**, int, int);
		Matrix(const Matrix&);
		~Matrix();

		Matrix& operator=(const Matrix&);
		double* operator[](const int);
		Matrix transpose();
		Matrix operator+(const Matrix&);
		Matrix operator-(const Matrix&);
		Matrix operator*(const Matrix&);
		Matrix operator*(const int);
		double sum();

		int row_count()	{return rows;}
		int col_count()	{return columns;}
		DSVector<double> get_row_vector(const int);
		DSVector<double> get_col_vector(const int);
		void print();
};

Matrix Hadamard_mul(Matrix&, Matrix&);
Matrix Kronecker_mul(Matrix&, Matrix&);
Matrix horizontal_cat(Matrix&, Matrix&);

Matrix::Matrix(int rows, int columns){
	matrix = new double[rows * columns];
	for(int i = 0; i < rows * columns; i++){
		matrix[i] = 0;
	}
	this->rows = rows;
	this->columns = columns;
}

Matrix::Matrix(int** array, int rows, int columns){
	matrix = new double[rows * columns];
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			matrix[i * columns + j] = array[i][j];
		}
	}
	this->rows = rows;
	this->columns = columns;
}

Matrix::Matrix(const Matrix& source){
	matrix = new double[source.rows * source.columns];
	this->rows = source.rows;
	this->columns = source.columns;
	for(int i = 0; i < source.rows; i++){
		for(int j = 0; j < source.columns; j++){
			matrix[i * columns + j] = source.matrix[i * columns + j];
		}
	}
}

Matrix::~Matrix(){
	delete[] matrix;
}

Matrix& Matrix::operator=(const Matrix& source){
	delete[] matrix;
	matrix = new double[source.rows * source.columns];
	this->rows = source.rows;
	this->columns = source.columns;	for(int i = 0; i < source.rows; i++){
		for(int j = 0; j < source.columns; j++){
			matrix[i * columns + j] = source.matrix[i * columns + j];
		}
	}

	return *this;
}

double* Matrix::operator[](const int row){
	double* row_pointer = matrix + row * columns;
	return row_pointer;
}

Matrix Matrix::transpose(){
	Matrix transpose = Matrix(columns, rows);
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			transpose[j][i] = matrix[i * columns + j];
		}
	}
	return transpose;
}

Matrix Matrix::operator+(const Matrix& addend){
	Matrix sum = Matrix(rows, columns);
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			sum[i][j] = matrix[i * columns + j] + addend.matrix[i * columns + j];
		}
	}
	return sum;
}

Matrix Matrix::operator-(const Matrix& minuend){
	Matrix difference = Matrix(rows, columns);
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			difference[i][j] = matrix[i * columns + j] - minuend.matrix[i * columns + j];
		}
	}
	return difference;
}

Matrix Matrix::operator*(const Matrix& factor){
	Matrix product = Matrix(rows, factor.columns);
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < factor.columns; j++){
			for(int k = 0; k < columns; k++){
				product[i][j] += matrix[i * columns + k] * factor.matrix[k * factor.columns + j];
			}
		}
	}
	return product;
}

Matrix Matrix::operator*(const int scalar){
	Matrix product = Matrix(rows, columns);
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			product[i][j] = matrix[i * columns + j] * scalar;
		}
	}
	return product;
}

double Matrix::sum(){
	double sum = 0.0;
	for(int i = 0; i < rows * columns; i++){
		sum += matrix[i];
	}
	return sum;
}

DSVector<double> Matrix::get_row_vector(const int row){
	DSVector<double> row_vector = DSVector<double>();
	for(int i = 0; i < columns; i++){
		row_vector.push_back(matrix[row * columns + i]);
	}
	return row_vector;
}

DSVector<double> Matrix::get_col_vector(const int column){
	DSVector<double> col_vector = DSVector<double>();
	for(int i = 0; i < rows; i++){
		col_vector.push_back(matrix[i * columns + column]);
	}
	return col_vector;
}

void Matrix::print(){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			std::cout << matrix[i * columns + j] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

Matrix Hadamard_mul(Matrix& factor1, Matrix& factor2){
	Matrix product = Matrix(factor1.row_count(), factor1.col_count());
	for(int i = 0; i < factor1.row_count(); i++){
		for(int j = 0; j < factor1.col_count(); j++){
			product[i][j] = factor1[i][j] * factor2[i][j];
		}
	}
	return product;
}

Matrix Kronecker_mul(Matrix& factor1, Matrix& factor2){
	Matrix product = Matrix(factor1.row_count() * factor2.row_count(), factor1.col_count() * factor2.col_count());
	for(int i = 0; i < factor1.row_count(); i++){
		for(int j = 0; j < factor2.row_count(); j++){
			for(int k = 0; k < factor1.col_count(); k++){
				for(int l = 0; l < factor2.col_count(); l++){
					product[factor1.row_count() * i + j][factor1.col_count() * k + l] = factor1[i][k] * factor2[j][l];
				}
			}
		}
	}
	return product;
}

Matrix horizontal_cat(Matrix& augend, Matrix& addend){
	Matrix concatenation = Matrix(augend.row_count(), augend.col_count() + addend.col_count());
	for(int i = 0; i < augend.row_count(); i++){
		for(int j = 0; j < (augend.col_count() + addend.col_count()); j++){
			if(j < augend.col_count()){
				concatenation[i][j] = augend[i][j];
			}
			else{
				concatenation[i][j] = addend[i][j - augend.col_count()];
			}
		}
	}
	return concatenation;
}

#endif