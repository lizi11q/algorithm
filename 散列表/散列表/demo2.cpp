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
    // Ѱ��С�ڵ���HashSize�����������Ϊp
    while (p >= 2) {
        int flag = 1;
        for (int i = 2; i <= p / 2; i++) { // �Ż�ѭ������Ϊi*i <= p����Ч
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

    // ʾ����ɾ���Ͳ��Ҳ���
    int addr;
    if (SearchHash(H, 63, &addr)) {
        printf("�ҵ�Ԫ��63����ַ��%d\n", addr);
        DeleteHash(&H, 63);
        printf("ɾ��Ԫ��63���ٴβ��ң�%s\n", SearchHash(H, 63, &addr) ? "����" : "������");
    }

    free(H.elem); // �ͷŶ�̬������ڴ�
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
    return key % p; // pΪС��HashSize���������
}

bool InsertHash(HashTable* H, int key) {
    if (H->count == HashSize) return false;
    int addr = Hash(key);
    // ����̽������ͻ��ʹ��%HashSizeȷ����Խ��
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
            return false; // �����ղۣ�˵��������
        }
        *addr = (*addr + 1) % HashSize; // ��ȷ̽�ⲽ��
    } while (*addr != startAddr); // ѭ���ص����˵���ѱ������в�λ
    return false;
}