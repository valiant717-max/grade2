#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 4  // 每个块存储的字符数（可调整）

// 块节点结构体
typedef struct Block {
    char ch[BLOCK_SIZE];  // 块内字符数组
    struct Block* next;   // 指向下一块的指针
} Block;

// 块链串结构体（记录头指针、尾指针和总长度）
typedef struct {
    Block* head;   // 头节点
    Block* tail;   // 尾节点
    int length;    // 总长度
} BLString;

// 初始化块链串
void initBLString(BLString* s) {
    s->head = s->tail = NULL;
    s->length = 0;
}

// 插入字符到块链（尾部添加）
void appendChar(BLString* s, char c) {
    if (s->length == 0) {  // 空串时创建第一个块
        s->head = (Block*)malloc(sizeof(Block));
        s->tail = s->head;
        s->head->next = NULL;
    }
    else {
        // 计算当前尾块已用长度：length % BLOCK_SIZE
        int used = s->length % BLOCK_SIZE;
        if (used == 0) {  // 尾块已满，新建块
            Block* newBlock = (Block*)malloc(sizeof(Block));
            s->tail->next = newBlock;
            s->tail = newBlock;
            s->tail->next = NULL;
        }
    }
    // 计算当前字符在块中的位置
    int pos = s->length % BLOCK_SIZE;
    s->tail->ch[pos] = c;
    s->length++;
}

// 从字符串常量构建块链串
void assignBLString(BLString* s, const char* str) {
    initBLString(s);  // 先清空
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        appendChar(s, str[i]);
    }
}

// 打印块链串
void printBLString(BLString s) {
    if (s.length == 0) {
        printf("空串，长度：0\n");
        return;
    }
    printf("串内容：");
    Block* p = s.head;
    int count = 0;
    while (p != NULL && count < s.length) {
        for (int i = 0; i < BLOCK_SIZE && count < s.length; i++) {
            printf("%c", p->ch[i]);
            count++;
        }
        p = p->next;
    }
    printf("，长度：%d\n", s.length);
}

// 销毁块链串（释放所有块）
void destroyBLString(BLString* s) {
    Block* p = s->head;
    while (p != NULL) {
        Block* temp = p;
        p = p->next;
        free(temp);
    }
    s->head = s->tail = NULL;
    s->length = 0;
}

int main() {
    BLString s;
    assignBLString(&s, "block chain string");
    printBLString(s);
    destroyBLString(&s);  // 释放所有节点
    return 0;
}