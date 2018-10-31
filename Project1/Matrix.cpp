//#include <iostream>
#include "Matrix.hpp"

Matrix:: Matrix(int rows=1, int columns=1) : m_rows(rows), m_columns(columns)
{
	m_values = new double*[rows];
	for (int i = 0; i < m_rows; i++)
		m_values[i] = new double[m_columns];
}

Matrix:: ~Matrix()
{
	for (int i = 0; i < m_rows; i++)
		delete [] m_values[i];
	delete [] m_values;
}

Matrix:: Matrix(const Matrix &right) : m_rows(right.m_rows), m_columns(right.m_columns)
{
	m_values = new double *[m_rows];
	for (int i = 0; i < m_rows; i++)
		m_values[i] = new double[m_columns];
	for (int i = 0; i < m_rows; i++)
		for (int j = 0; j < m_columns; j++)
			m_values[i][j] = right.m_values[i][j];
}

std::istream &operator>>(std::istream &in, Matrix &right)
{
	for (int i = 0; i < right.m_rows; i++)
		for (int j = 0; j < right.m_columns; j++)
			in >> right.m_values[i][j];
	return in;
}

std::ostream &operator<<(std::ostream &out,const  Matrix &right)
{
	for (int i = 0; i < right.m_rows; i++)
	{
		for (int j = 0; j < right.m_columns; j++)
			out << right.m_values[i][j] << ' ';
		out << '\n';
	}
	out << '\n';
	return out;
}

Matrix& Matrix::operator=(const Matrix& right) {
	if (&right == this) {
		return *this;
	}
	if (m_rows*m_columns == right.m_rows*right.m_columns) {
		for (int i = 0; i < m_rows; i++)
			for (int j = 0; j < m_columns; j++)
				this->m_values[i][j] = right.m_values[i][j];
	}
	else {
		for (int i = 0; i < m_rows; i++)
			delete[] m_values[i];
		delete[] m_values;
		this->m_rows = right.m_rows;
		this->m_columns = right.m_columns;
		m_values = new double*[m_rows];
		for (int i = 0; i < m_rows; i++)
			m_values[i] = new double[m_columns];
		for (int i = 0; i < m_rows; i++)
			for (int j = 0; j < m_columns; j++)
				m_values[i][j] = right.m_values[i][j];
	}
	return *this;
}

Matrix operator+(const Matrix &left, const Matrix &right)
{
	//if (left.m_columns != right.m_columns && left.m_rows != right.m_columns)
	//	return -1;
	Matrix result(left.m_rows,left.m_columns);
	for (int i = 0; i < result.m_rows; i++)
		for (int j = 0; j < result.m_columns; j++)
			result.m_values[i][j] = left.m_values[i][j] + right.m_values[i][j];
	return result;
}

Matrix operator+(const Matrix &left, double scalar)
{
	Matrix result(left.m_rows, left.m_columns);
	for (int i = 0; i < result.m_rows; i++)
		for (int j = 0; j < result.m_columns; j++)
			result.m_values[i][j] = left.m_values[i][j] + scalar;
	return result;
}

Matrix operator+(double scalar,const Matrix &right)
{
	Matrix result(right.m_rows, right.m_columns);
	for (int i = 0; i < result.m_rows; i++)
		for (int j = 0; j < result.m_columns; j++)
			result.m_values[i][j] = right.m_values[i][j] + scalar;
	return result;
}

Matrix operator-(const Matrix &left, const Matrix &right)
{
	Matrix result(left.m_rows, left.m_columns);
	for (int i = 0; i < result.m_rows; i++)
		for (int j = 0; j < result.m_columns; j++)
			result.m_values[i][j] = left.m_values[i][j] - right.m_values[i][j];
	return result;
}

Matrix operator-(const Matrix &left, double scalar)
{
	Matrix result(left.m_rows, left.m_columns);
	for (int i = 0; i < result.m_rows; i++)
		for (int j = 0; j < result.m_columns; j++)
			result.m_values[i][j] = left.m_values[i][j] - scalar;
	return result;
}

Matrix operator-(double scalar, const Matrix &right)
{
	Matrix result(right.m_rows, right.m_columns);
	for (int i = 0; i < result.m_rows; i++)
		for (int j = 0; j < result.m_columns; j++)
			result.m_values[i][j] = scalar - right.m_values[i][j];
	return result;
}

Matrix operator*(const Matrix &left, const Matrix &right)
{
	Matrix result(left.m_rows, right.m_columns);
	for (int i = 0; i < left.m_rows; i++)
		for (int j = 0; j < right.m_columns; j++)
		{
			result.m_values[i][j] = 0;
			for (int k = 0; k < left.m_rows; k++)
				result.m_values[i][j] += left.m_values[i][k] * right.m_values[k][j];
		}
	return result;
}

Matrix operator*(const Matrix &left, double scalar)
{
	Matrix result(left.m_rows, left.m_columns);
	for (int i = 0; i < left.m_rows; i++)
		for (int j = 0; j < left.m_columns; j++)
				result.m_values[i][j] = left.m_values[i][j] * scalar;
	return result;
}

Matrix operator*(double scalar, const Matrix &right)
{
	Matrix result(right.m_rows, right.m_columns);
	for (int i = 0; i < right.m_rows; i++)
		for (int j = 0; j < right.m_columns; j++)
			result.m_values[i][j] = right.m_values[i][j] * scalar;
	return result;
}

Matrix operator/(const Matrix &left, double scalar)
{
	Matrix result(left.m_rows, left.m_columns);
	for (int i = 0; i < left.m_rows; i++)
		for (int j = 0; j < left.m_columns; j++)
			result.m_values[i][j] = left.m_values[i][j] / scalar;
	return result;
}

Matrix operator/(double scalar,const Matrix &right)
{
	Matrix result(right.m_rows, right.m_columns);
	for (int i = 0; i < right.m_rows; i++)
		for (int j = 0; j < right.m_columns; j++)
			result.m_values[i][j] = scalar / right.m_values[i][j];
	return result;
}

Matrix operator^(const Matrix &left, int n)
{
	Matrix result(left);
	for (int i = 0; i < n-1; i++)
		result *= left;
	return result;
}

bool operator==(const Matrix &left, const Matrix &right)
{
	if (left.m_rows == right.m_rows && left.m_columns == right.m_columns)
	{
		for (int i = 0; i < left.m_rows; i++)
			for (int j = 0; j < left.m_columns; j++)
				if (left.m_values[i][j] != right.m_values[i][j])
					return false;
		return true;
	}
	else return false;
}

bool operator !=(const Matrix &left,const Matrix &right)
{
	if (left == right)
		return false;
	return true;
}

Matrix &Matrix::operator+=(const Matrix &right)
{
	Matrix created;
	created= (*this) + right;
	(*this) = created;
	return *this;
}

Matrix &Matrix::operator+=(double scalar)
{
	Matrix result;
	result = (*this) + scalar;
	(*this) = result;
	return *this;
}

Matrix &Matrix::operator-=(const Matrix &right)
{
	Matrix created;
	created = (*this) - right;
	(*this) = created;
	return *this;
}

Matrix &Matrix::operator-=(double scalar)
{
	Matrix result;
	result = (*this) - scalar;
	(*this) = result;
	return *this;
}

Matrix &Matrix::operator*=(const Matrix &right)
{
	Matrix created;
	created = (*this) * right;
	(*this) = created;
	return *this;
}

Matrix &Matrix::operator*=(double scalar)
{
	Matrix created;
	created = (*this) * scalar;
	(*this) = created;
	return *this;
}

Matrix &Matrix::operator+()
{
	return *this;
}

Matrix &Matrix::operator-()
{
	int aux;
	for(int i=0;i<m_rows;i++)
		for (int j = i + 1; j < m_columns; j++)
		{
			aux = m_values[i][j];
			m_values[i][j] = m_values[j][i];
			m_values[j][i] = aux;
		}
	return *this;
}

Matrix Matrix::operator[](int n)
{
	Matrix result;
	if (m_rows==1 && m_columns!=1)
	{
		Matrix rez(1, 1);
		result = rez;
		result.m_values[0][0] = m_values[0][n];
	}
	else if (m_rows != 1 && m_columns == 1)
	{
		Matrix rez(1, 1);
		result = rez;
		result.m_values[0][0] = m_values[n][0];
	}
	else {
		Matrix rez(1, m_columns);
		result = rez;
		for (int j = 0; j < m_columns; j++)
			result.m_values[0][j] = m_values[n][j];
	}
	return result;	
}

int main()
{
	Matrix M1(3,3),M2(2,2);
	std::cin >> M1;
	std::cout << M1;
	//std::cin >> M2;
	//std::cout << M2;
	//std::cin>>M2
	//if (M1 != M2)
		//std::cout << "nu sunt aceeasi matrice" << '\n';
	//else
	//	std::cout << "sunt aceeasi matrice "<<'\n';
	//std::cout << -M1;
	std::cout << M1[1];
	//std::cout << M1;
	system("pause");
	return 0;

}