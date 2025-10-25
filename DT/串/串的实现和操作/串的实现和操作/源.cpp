 #include <iostream>
#include <cstring>
#include <stdexcept>

using namespace std;

// 串的抽象数据类型实现
class String {
private:
    char* data;  // 存储字符串
    int length;  // 字符串长度

public:
    // 带默认参数的构造函数,支持无参构造对象
    String(const char* str = "") {
        if (str == nullptr) {
            length = 0;
            data = new char[1];
            data[0] = '\0';
        }
        else {
            length = strlen(str);
           //strlen 的参数必须是 const char*
            data = new char[length + 1];
            strcpy(data, str);
        }
    }

    // 拷贝构造函数
    String(const String& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }

    // 析构函数
    ~String() {
        delete[] data;
    }

    // 赋值运算符重载
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }
        return *this;//this 是一个指向当前对象的指针,*this解引用得到当前对象本身，具体返回的是对象的副本还是引用，取决于函数的返回类型
        //return *this 支持链式赋值如s1 = s2 = s3,返回当前对象的引用正好可以作为下一次赋值的右操作数
    }

    // 获取字符串长度
    int getLength() const {
        return length;
    }

    // 获取指定位置的字符
    char charAt(int index) const {
        if (index < 0 || index >= length) {
            throw out_of_range("索引越界");
        }
        return data[index];
    }

    // 字符串拼接
    String operator+(const String& other) const {
        char* newData = new char[length + other.length + 1];
        strcpy(newData, data);
        strcat(newData, other.data);

        String result(newData);
        delete[] newData;
        return result;
    }

    // 字符串比较
    int compareTo(const String& other) const {
        return strcmp(data, other.data);
    }

    // 判断是否为空串
    bool isEmpty() const {
        return length == 0;
    }

    // 截取子串
    String substring(int start, int len) const {
        if (start < 0 || len < 0 || start + len > length) {
            throw out_of_range("子串参数无效");
        }

        char* subStr = new char[len + 1];
        for (int i = 0; i < len; i++) {
            subStr[i] = data[start + i];
        }
        subStr[len] = '\0';

        String result(subStr);
        delete[] subStr;
        return result;
    }

    // 朴素模式匹配算法
    // 返回模式串在主串中首次出现的位置，若未找到返回-1
    int indexOf(const String& pattern) const {
        if (pattern.isEmpty() || length < pattern.length) {
            return -1;
        }

        int i = 0;  // 主串索引
        int j = 0;  // 模式串索引 

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

        // 若模式串完全匹配，返回起始位置
        if (j == pattern.length) {
            return i - j;
        }

        return -1;
    }

    // KMP模式匹配算法
    int kmpIndexOf(const String& pattern) const {
        if (pattern.isEmpty() || length < pattern.length) {
            return -1;
        }

        int* next = computeNext(pattern);  // 计算next数组
        int i = 0;  // 主串索引
        int j = 0;  // 模式串索引

        while (i < length && j < pattern.length) {
            if (j == -1 || data[i] == pattern.data[j]) {
                i++;
                j++;
            }
            else {
                j = next[j];  // 利用next数组避免主串回溯
            }
        }

        delete[] next;

        if (j == pattern.length) {
            return i - j;
        }

        return -1;
    }

    // 打印字符串
    void print() const {
        cout << data << endl;
//data是一个以'\0'结尾的字符串，则cout << data会正确输出整个字符串
    }

private:
    // 计算KMP算法中的next数组
    int* computeNext(const String& pattern) const {
        int len = pattern.length;
        int* next = new int[len];
        next[0] = -1;

        int k = -1;  // 前缀长度
        int j = 0;   // 后缀索引的下一个位置

        while (j < len - 1) {
            if (k == -1|| pattern.data[j] == pattern.data[k]) {
//k==-1说明之前没有匹配的前缀，直接从 0 开始尝试匹配,如果不匹配则将数组的第j位存入0，同时将k重新置为-1，依然从头开始匹配
//若字符相等：当前前缀和后缀可以延长，因此 k（前缀长度）加 1，j（当前位置）加 1，此时 next[j] = k（记录当前最长匹配长度）。 
//由于一开始的时候k设置成了-1.所以k++得到的就是下一个位置的前缀和长度  
                k++; 
                j++;
                next[j] = k;
            }
            else {
                k = next[k];
//若字符不相等说明当前前缀无法匹配，需要缩短前缀长度。通过 k = next[k] 回溯到更短的前缀（利用已计算的 next 值，避免从头匹配），直到找到匹配的前缀或 k = -1
            }
        }

        return next;
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
