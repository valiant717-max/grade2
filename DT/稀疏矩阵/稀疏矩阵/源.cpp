#include<iostream>
#include<vector>
#include<stdexcept>
#include<algorithm>
using namespace std;

struct Triple {
	int row;
	int col;
	int value;
};

class SparseMatrix {
private:
	vector<Triple> data;
	int rows;
	int cols;
	int nonZeroCount;
public:
	SparseMatrix(int r = 0, int c = 0) : rows(r), cols(c), nonZeroCount(0), data() {};

	//创建稀疏矩阵
	void createFromInput() {
		cin >> rows >> cols;
		cin >> nonZeroCount;
		if (nonZeroCount > rows * cols) {
			throw invalid_argument("Non-zero count exceeds matrix size.");
		}
		for (int i = 0; i < nonZeroCount; i++) {
			Triple t;
			cin >> t.row >> t.col >> t.value;
			if (t.row >= rows || t.col >= cols) {
				throw out_of_range("Row or column index out of range.");
			}
			data.push_back(t);
		}
		sort(data.begin(), data.end(), [](const Triple&a,const Triple& b) {
			if (a.row != b.row)return a.row < b.row;
			return a.col < b.col;
			});
	}

	//打印稀疏矩阵
	void print() const {
		int idx = 0;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (idx < nonZeroCount && data[idx].row == i && data[idx].col == j) {
					cout << data[idx].value << " ";
					idx++;
				} 
				else {
					cout << "0 ";
				}
			}
			cout << endl;
		}
	}

	//转置稀疏矩阵
	SparseMatrix transpose()const {
		SparseMatrix result(cols, rows);
		result.nonZeroCount = nonZeroCount;
		if (nonZeroCount == 0)return result;
		vector<int> colCounts(cols, 0);
		//统计每一列非0元素的个数
		for (const auto& t : data) {
			colCounts[t.col]++;
		}
		//计算第i列的第一个非0元素在转置后矩阵中的起始位置
		vector<int> colStarts(cols, 0);
		for (int i = 1; i < cols; i++) {
			colStarts[i] = colStarts[i - 1] + colCounts[i - 1];
		}
		//重点理解：将元素放到转置后矩阵的正确位置
		for (const auto& t : data) {
			int pos = colStarts[t.col]++;
			result.data[pos] = { t.col, t.row, t.value };
		}
		return result;
	}

	//矩阵加法
	SparseMatrix add(const SparseMatrix& other) const {
		if (rows != other.rows || cols != other.cols) {
			throw invalid_argument("Matrices dimensions do not match for addition.");
		}
		SparseMatrix result(rows, cols);
		int i = 0, j = 0;
		while (i < nonZeroCount && j < other.nonZeroCount) {
			if (data[i].row < other.data[j].row ||
				(data[i].row == other.data[j].row && data[i].col < other.data[j].col)) {
				result.data.push_back(data[i]);
				i++;
			}
			else if (data[i].row > other.data[j].row ||
				(data[i].row == other.data[j].row && data[i].col > other.data[j].col)) {
				result.data.push_back(other.data[j]);
				j++;
			}
			else {
				int summedValue = data[i].value + other.data[j].value;
				if (summedValue != 0) {
					result.data.push_back({ data[i].row, data[i].col, summedValue });
				}
				i++;
				j++;
			} 
		}
		//处理剩余元素
		while (i < nonZeroCount) {
			result.data.push_back(data[i]);
			i++;
		}
		while (j < other.nonZeroCount) {
			result.data.push_back(other.data[j]);
			j++;
		}
		result.nonZeroCount = result.data.size();
		return result;
	}

	//矩阵乘法
	SparseMatrix multiply(const SparseMatrix& other) const {
		if (cols != other.rows) {
			throw invalid_argument("Matrices dimensions do not match for multiplication.");
		}
		SparseMatrix result(rows, other.cols);
		if (nonZeroCount == 0 || other.nonZeroCount == 0) {
			return result;
		}
		SparseMatrix otherT = other.transpose();
		for (int i = 0; i < nonZeroCount; ) {
			int r = data[i].row;// 当前行
			vector<int> rowA(cols, 0);// 存储当前行的非0元素
			// 收集当前行的非0元素
			while (i < nonZeroCount && data[i].row == r) {
				rowA[data[i].col] = data[i].value;
				i++;
			} 
			// 计算当前行与otherT的每一行的点积
			for (int j = 0; j < otherT.nonZeroCount; ) {
				int c = otherT.data[j].row; 
				vector<int> colB(otherT.cols, 0);
				while (j < otherT.nonZeroCount && otherT.data[j].row == c) {
					colB[otherT.data[j].col] = otherT.data[j].value;
					j++;
				}
				int sum = 0;
				for (int k = 0; k < cols; k++) {
					sum += rowA[k] * colB[k];
				}
				if (sum != 0) {
					result.data.push_back({ r, c, sum });
				}
			}
		}
		result.nonZeroCount = result.data.size();
		return result;
	}
	// 获取矩阵行数
	int getRows() const { return rows; }
	// 获取矩阵列数
	int getCols() const { return cols; }
};

int main() {
	try {
		SparseMatrix matA, matB;
		cout << "Enter matrix A (rows cols nonZeroCount followed by row col value for each non-zero element):" << endl;
		matA.createFromInput();
		cout << "Matrix A:" << endl;
		matA.print();

		cout << "Enter matrix B (rows cols nonZeroCount followed by row col value for each non-zero element):" << endl;
		matB.createFromInput();
		cout << "Matrix B:" << endl;
		matB.print();

		SparseMatrix matC = matA.add(matB);
		cout << "Matrix A + B:" << endl;
		matC.print();

		if (matA.getCols() == matB.getRows()) {
			SparseMatrix matD = matA.multiply(matB);
			cout << "Matrix A * B:" << endl;
			matD.print();
		}
		else {
			cout << "Matrix A and B cannot be multiplied due to dimension mismatch." << endl;
		}

		SparseMatrix matAT = matA.transpose();
		cout << "Transpose of Matrix A:" << endl;
		matAT.print();
	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
	}
	return 0;
}