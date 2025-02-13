#include <stdio.h>
#include <stdlib.h>
#define HashSize 15
#define NULLKEY -22222
#define DELETE -11111
int p;

typedef struct {
    int* elem;
    int count;
} HashTable;

HashTable InitHashTable();
int Hash(int key);
bool InsertHash(HashTable* H, int key);
bool DeleteHash(HashTable* H, int key);
bool SearchHash(HashTable H, int key, int* addr);

int main() {
    p = HashSize;
    // 寻找小于等于HashSize的最大质数作为p
    while (p >= 2) {
        int flag = 1;
        for (int i = 2; i <= p / 2; i++) { // 优化循环条件为i*i <= p更高效
            if (p % i == 0) {
                flag = 0;
                break;
            }
        }
        if (flag) break;
        p--;
    }

    HashTable H = InitHashTable();
    int arr[] = { 34, 78, 15, 92, 56, 23, 87, 41, 63, 29, 74, 50 };
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
        InsertHash(&H, arr[i]);
    }

    // 示例：删除和查找操作
    int addr;
    if (SearchHash(H, 63, &addr)) {
        printf("找到元素63，地址：%d\n", addr);
        DeleteHash(&H, 63);
        printf("删除元素63后，再次查找：%s\n", SearchHash(H, 63, &addr) ? "存在" : "不存在");
    }

    free(H.elem); // 释放动态分配的内存
    return 0;
}

HashTable InitHashTable() {
    HashTable H;
    H.count = 0;
    H.elem = (int*)malloc(sizeof(int) * HashSize);
    for (int i = 0; i < HashSize; i++) {
        H.elem[i] = NULLKEY;
    }
    return H;
}

int Hash(int key) {
    return key % p; // p为小于HashSize的最大质数
}

bool InsertHash(HashTable* H, int key) {
    if (H->count == HashSize) return false;
    int addr = Hash(key);
    // 线性探测解决冲突，使用%HashSize确保不越界
    while (H->elem[addr] != NULLKEY && H->elem[addr] != DELETE) {
        addr = (addr + 1) % HashSize;
    }
    H->elem[addr] = key;
    H->count++;
    return true;
}

bool DeleteHash(HashTable* H, int key) {
    int addr;
    if (!SearchHash(*H, key, &addr)) return false;
    H->elem[addr] = DELETE;
    H->count--;
    return true;
}

bool SearchHash(HashTable H, int key, int* addr) {
    if (H.count == 0) return false;
    *addr = Hash(key);
    int startAddr = *addr;
    do {
        if (H.elem[*addr] == key) {
            return true;
        }
        if (H.elem[*addr] == NULLKEY) {
            return false; // 遇到空槽，说明不存在
        }
        *addr = (*addr + 1) % HashSize; // 正确探测步长
    } while (*addr != startAddr); // 循环回到起点说明已遍历所有槽位
    return false;
}