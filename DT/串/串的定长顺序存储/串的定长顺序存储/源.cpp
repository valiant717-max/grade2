#include <stdio.h>
#include <string.h>

#define MAX_LEN 100  // 预定义最大长度

// 定长顺序串结构体
typedef struct {
    char ch[MAX_LEN];  // 存储字符的数组
    int length;        // 当前串长度
} SString;

// 初始化串
void initString(SString* s) {
    s->length = 0;
    s->ch[0] = '\0';  // 结束标志
}

// 赋值操作：将字符串常量赋值给串
void assignString(SString* s, const char* str) {
    int len = strlen(str);
    s->length = (len > MAX_LEN) ? MAX_LEN : len;  // 超出最大长度则截断
    strncpy(s->ch, str, s->length);
    s->ch[s->length] = '\0';  // 手动添加结束符
}

// 打印串
void printString(SString s) {
    printf("串内容：%s，长度：%d\n", s.ch, s.length);
}

int main() {
    SString s;
    initString(&s);
    assignString(&s, "hello, world!");
    printString(s);  // 若超过MAX_LEN会被截断
    return 0;
}