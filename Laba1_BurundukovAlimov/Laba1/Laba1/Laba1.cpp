#include <iostream>
using namespace std;

template<class Type>
class Matrix
{
private:
	size_t rows = 0, cols = 0;
	Type** matrix = nullptr;
	int m = 0;
	void getMatrix(int**, int**, int, int, int);
	size_t getDeterminant(int**, int);
public:
	Matrix() {}
	template<class Type> friend istream& operator >>(istream&, Matrix<Type>&);
	template<class Type> ostream& operator <<(ostream&, const Matrix<Type>&);
	Matrix(size_t, size_t);
	~Matrix();
	size_t getDeterminant();
	pair<size_t, size_t> getSize();
	void changeValue(size_t, size_t, Type);
	Type getValue(size_t, size_t);
	Matrix operator +(const Matrix&);
	Matrix operator -(const Matrix&);
	Matrix operator *(const Matrix&);
	bool operator ==(const Matrix&);
	Matrix operator *(int);
	void operator =(const Matrix&);
};

template<class Type>
istream& operator >>(istream& in, Matrix<Type>& matrix)
{
	if (matrix.matrix == nullptr)
	{
		cout << "Введите количество строк: "; in >> matrix.rows;
		cout << "Введите количество столбцов: "; in >> matrix.rows;

		matrix.matrix = new Type * [matrix.rows];
		for (int i = 0; i < matrix.rows; i++)
		{
			matrix.matrix[i] = new Type[matrix._cols];
		}
	}

	cout << "Введите матрицу: " << endl;
	for (int i = 0; i < matrix.rows; i++)
	{
		for (int j = 0; j < matrix._cols; j++)
		{
			cout << "mas[" << i << "][" << j << "]= ";
			in >> matrix.matrix[i][j];
		}
	}

	return in;
}

template<class Type>
ostream& operator<<(ostream& out, const Matrix<Type>& matrix)
{
	if (matrix.matrix == nullptr) throw exception("Матрица пустая!");

	for (int i = 0; i < matrix.rows; i++) {
		for (int j = 0; j < matrix._cols; j++)
			cout << matrix.matrix[i][j] << " ";
		cout << endl;
	}
}

template<class Type>
size_t Matrix<Type>::getDeterminant() {
	if (rows != _cols)
		throw exception("Матрица должна быть квадратной");

	int dimension = rows, j = 0, determinant = 0, f = 1, n = dimension - 1;

	int** auxiliary = new int* [dimension];
	for (int i = 0; i < dimension; i++)
		auxiliary[i] = new int[dimension];

	if (dimension < 1) cout << "Определитель вычислить невозможно!";
	if (dimension == 1) {
		determinant = matrix[0][0];
		return(determinant);
	}
	if (dimension == 2) {
		determinant = matrix[0][0] * matrix[1][1] - (matrix[1][0] * matrix[0][1]);
		return(determinant);
	}
	if (dimension > 2) {
		for (int i = 0; i < dimension; i++) {
			getMatrix(matrix, auxiliary, i, 0, dimension);
			cout << matrix[i][j] << endl;
			determinant = determinant + f * matrix[i][0] * getDeterminant(auxiliary, n);
			f = -f;
		}
	}

	for (int i = 0; i < dimension; i++)
		delete[] auxiliary[i];
	delete[] auxiliary;

	return(determinant);
}

template<class Type>
Matrix<Type>::~Matrix()
{
	if (matrix != nullptr)
	{
		for (int i = 0; i < rows; i++)
			delete[] matrix[i];
		delete[] matrix;

		matrix = nullptr;
	}
}

template<class Type>
Matrix<Type>::Matrix(size_t rows, size_t cols)
{
	this->rows = rows;
	this->_cols = cols;

	matrix = new Type * [rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new Type[_cols]{ 0 };
	}
}

template<class Type>
void Matrix<Type>::getMatrix(int** mas,
	int** aux,
	int i,
	int j,
	int dim)
{
	int ki, kj, di = 0, dj;

	for (ki = 0; ki < dim - 1; ki++) {
		if (ki == i) di = 1;
		dj = 0;
		for (kj = 0; kj < dim - 1; kj++) {
			if (kj == j) dj = 1;
			aux[ki][kj] = mas[ki + di][kj + dj];
		}
	}
}

template<class Type>
size_t Matrix<Type>::getDeterminant(int** mas,
	                  int dim)
{
	int j = 0, determinant = 0, f = 1, n;
	n = dim - 1;
	int** auxiliary;

	auxiliary = new int* [dim];
	for (int i = 0; i < dim; i++)
		auxiliary[i] = new int[dim];

	if (dim < 1) cout << "Определитель вычислить невозможно!";
	if (dim == 1) {
		determinant = mas[0][0];
		return(determinant);
	}
	if (dim == 2) {
		determinant = mas[0][0] * mas[1][1] - (mas[1][0] * mas[0][1]);
		return(determinant);
	}
	if (dim > 2) {
		for (int i = 0; i < dim; i++) {
			getMatrix(mas, auxiliary, i, 0, dim);
			cout << mas[i][j] << endl;
			determinant = determinant + f * mas[i][0] * getDeterminant(auxiliary, n);
			f = -f;
		}
	}

	for (int i = 0; i < dim; i++)
		delete[] auxiliary[i];
	delete[] auxiliary;

	return(determinant);
}

template<class Type>
pair<size_t, size_t> Matrix<Type>::getSize()
{ 
	return make_pair(rows, _cols); 
}

template<class Type>
void Matrix<Type>::changeValue(size_t rows, size_t cols, Type data)
{ 
	matrix[rows][cols] = data; 
}

template<class Type>
Type Matrix<Type>::getValue(size_t rows, size_t cols) { return matrix[rows - 1][cols - 1]; }

template<class Type>
Matrix<Type> Matrix<Type>::operator +(const Matrix& other)
{
	if (rows != other.rows || _cols != other._cols)
		throw exception("Матрицы должны быть одной размерности");

	Matrix matrix(rows, rows);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < _cols; j++)
			matrix.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
	};

	return matrix;
};

template<class Type>
Matrix<Type> Matrix<Type>::operator -(const Matrix& other)
{
	if (rows != other.rows || _cols != other._cols)
		throw exception("Матрицы должны быть одной размерности");

	Matrix matrix(rows, other._cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < _cols; j++)
			matrix.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
	};
	return matrix;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator *(const Matrix& other)
{
	if (_cols != other.rows)
		throw exception("Количество столбцов в первой матрице должно равняться количество строк в второй");

	Matrix matrix(rows, other._cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < other._cols; j++)
		{
			for (int b = 0; b < _cols; b++)
				matrix.matrix[i][j] += matrix[i][b] * other.matrix[b][j];
		};
	};
	return matrix;
}

template<class Type>
bool Matrix<Type>::operator ==(const Matrix& other)
{
	if (rows != other.rows || _cols != other._cols) return false;

	int y = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < _cols; j++)
		{
			if (matrix[i][j] == other.matrix[i][j])
				y++;
		}
	}

	if (y == rows * _cols)
		return true;
	else
		return false;
}

template<class Type>
Matrix<Type> Matrix<Type>::operator *(int value)
{
	Matrix matrix(rows, _cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < _cols; j++)
		{
			matrix.matrix[i][j] = matrix[i][j];
		}
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < _cols; j++)
			matrix.matrix[i][j] *= value;
	}

	return matrix;
}

template<class Type>
void Matrix<Type>::operator =(const Matrix& other)
{
	this->~Matrix();

	this->rows = other.rows;
	this->_cols = other._cols;

	matrix = new Type * [rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new Type[_cols];
	}

	for (int i = 0; i < other.rows; i++)
	{
		for (int j = 0; j < other._cols; j++)
			matrix[i][j] = other.matrix[i][j];
	};
}

int main() {
	setlocale(LC_ALL, "Russian");
	Matrix<int> matrix1(2, 2);
	Matrix<int> matrix2(2, 2);
	Matrix<int> matrix3(2, 2);
	cin >> matrix1;
	cin >> matrix2;
	cin >> matrix3;
	cout << endl;
	cout << matrix1.getValue(1, 2);
	cout << endl;
	matrix1.changeValue(1, 2, 5);
	cout << endl;
	matrix1.getSize();
	cout << endl << matrix3 << endl;
	matrix3 = matrix1 + matrix2;
	cout << endl << matrix3 << endl;
	matrix3 = matrix1 - matrix2;
	cout << endl << matrix3 << endl;
	matrix3 = matrix1 * matrix2;
	cout << endl << matrix3 << endl;
	matrix3 = matrix3 * 3;
	cout << endl;
	cout << matrix1.getDeterminant();
	cout << endl;
	cout << (matrix1 == matrix2);
	return 0;
}