#include<iostream>
#include<cstring>
#include<stdexcept>
using namespace std;

class String {
private:
	char* data;
	int length;
public:
	String(const char* str = "") {
		if (str == nullptr) {
			length = 0;
			data = new char[1];
			data[0] = '\0';
		}
		else {
			length = strlen(str);
			data = new char[length+1];
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
			throw out_of_range("Ë÷ÒýÔ½½ç");
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
		delete[] newData;
		return result;
	}


};