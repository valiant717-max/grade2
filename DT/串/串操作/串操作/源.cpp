#include<iostream>
#include<cstring>
#include<stdexcept>
using namespace std;

class String {
private:
	char* data;
	int length;
	int* computeNext(const String& pattern)const {
		int* next = new int[pattern.length];
		next[0] = -1;
		int k = -1;
		int j = 0;

		while (j < len - 1) {
			if (k == -1 || pattern.data[j] == patter.data[k]) {
				j++;
				k++;
				next[j] = k;//之所以这样写是因为k实际上代表了当前已经取到的相同的字符数
			}
			else {
				k = next[k];//在不相等的情况下，实际上要实现k不变j向右移动一位的效果
			}
		}
		return next;
	}

public:
	String(const char* str = "") {
		if (str == nullptr) {
			length = 0;
			data = new char[1];
			data[0] = '\0';
		}
		else {
			length = strlen(str);
			data = new char[length + 1];
			strcpy(data, str);
		}
	}

	String(const String& other) {
		length = other.length;
		data = new char[length + 1];
		strcpy(data, other.data);
	}

	~String()
	{
		delete[] data;
	}

	String& operator=(const String& other) {
		if (this != &other) {
			delete[] data;
			length = other.length;
			data = new char[length + 1];
			strcpy(data, other.data);
		}
		return *this;
	}

	int getLength() const {
		return length;
	}

	char charAt(int index) const {
		if (index < 0 || index >= length) {
			throw out_of_range("索引越界");
		}
		return data[index];
	}

	int compareTo(const String& other) const {
		return strcmp(data, other.data);
	}
	
	bool isEmpty() const {
		return length == 0;
	}

	String operator+(const String& other) const {
		char* newData = new char[length + other.length + 1];
		strcpy(newData, data);
		strcat(newData, other.data);
		String result(newData);
		delete[] newDta;
		return result;

	}

	String substring(int start, int len)const {
		if (start < 0 || len<0 || start + len>length) {
			throw out_of_range("子串参数无效");
		}
		char* subStr = new char[len + 1];
		for (int i = 0; i < len; i++) {
			subStr[i] = data[start + i];
		}
		String result(subStr);
		delete[] subStr;
		return result;
	}

	//朴素匹配算法
	int indexOf(const String& pattern)const {
		if (pattern.isEmpty() || length < pattern.length) {
			return -1;
		}
		int i = 0; int j = 0;
		while (i < length && j < pattern.length) {
			if (data[i] == pattern.data[j]) {
				// 字符匹配，继续比较下一个
				i++;
				j++;
			}
			else {
				// 字符不匹配，主串回溯，模式串复位
				i = i - j + 1;
				j = 0;
			}
		}

		if (j == pattern.length) {
			return i - j;
		}
		return -1;
	}


	int KmpIndexOf(const String& pattern) const {
		if (pattern.isEmpty() || length < pattern.length) {
			return -1;
		}
		int* next = computeNext(pattern);
		int i = 0;
		int j = 0;
		while (i < length && j < pattern.length) {
			if (j == -1 || data[i] == pattern.data[j]) {
				i++;
				j++;
			}
			else {
				j = next[j];
			}
		}
		delete[]next;

		if (j == pattern.length) {
			return i - j;
		}
		return -1;
	}

	void print() const {
		cout << data << endl;
	}
};


// 测试函数
int main() {
	try {
		// 创建字符串
		String s1("abcabcabcd");
		String s2("abc");
		String s3("xyz");

		cout << "字符串s1: ";
		s1.print();
		cout << "长度: " << s1.getLength() << endl;

		cout << "字符串s2: ";
		s2.print();
		cout << "长度: " << s2.getLength() << endl;

		// 字符串拼接
		String s4 = s1 + s3;
		cout << "s1 + s3: ";
		s4.print();

		// 字符串比较
		int cmp = s2.compareTo(s3);
		if (cmp < 0) {
			cout << "s2 小于 s3" << endl;
		}
		else if (cmp > 0) {
			cout << "s2 大于 s3" << endl;
		}
		else {
			cout << "s2 等于 s3" << endl;
		}

		// 截取子串
		String sub = s1.substring(3, 4);
		cout << "s1从索引3开始的4个字符: ";
		sub.print();

		// 朴素模式匹配
		int pos1 = s1.indexOf(s2);
		cout << "朴素算法: s2在s1中首次出现的位置: " << pos1 << endl;

		// KMP模式匹配
		int pos2 = s1.kmpIndexOf(s2);
		cout << "KMP算法: s2在s1中首次出现的位置: " << pos2 << endl;

		// 查找不存在的模式串
		int pos3 = s1.indexOf(s3);
		cout << "s3在s1中首次出现的位置: " << pos3 << endl;
	}
	catch (const exception& e) {
		cout << "错误: " << e.what() << endl;
	}

	return 0;
}