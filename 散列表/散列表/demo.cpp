//#include<stdio.h>
//#include<stdlib.h>
//#define HashSize 15
//#define NULLKEY -22222
//#define DELETE -11111
//int p;
//
//typedef struct {
//	int* elem;
//	int count;
//}HashTable;
//
//HashTable InitHashTable();
//int Hash(int key);
//bool InsertHash(HashTable* H, int key);
//bool DeleteHash(HashTable* H, int key);
//bool SearchHash(HashTable H, int key, int* addr);
//
//int main() {
//	p = HashSize;
//	int flag = 0;
//	while (p>=2) {
//		flag = 1;
//		for (int i = 2;i < p - 1;i++) {
//			if (p % i == 0) {
//				flag = 0;
//				break;
//			}
//		}
//		if (flag) {
//			break;
//		}
//		p--;
//	}
//
//	HashTable H = InitHashTable();
//	int arr[] = { 34,78,15,92,56,23,87,41,63,29,74,50 };
//	for (int i = 0;i < sizeof(arr) / sizeof(int);i++) {
//		InsertHash(&H, arr[i]);
//	}
//
//
//	return 0;
//}
//
//HashTable InitHashTable() {
//	HashTable H;
//	H.count = 0;
//	H.elem = (int*)malloc(sizeof(int) * HashSize);
//	for (int i = 0;i < HashSize;i++) {
//		H.elem[i] = NULLKEY;
//	}
//	return H;
//}
//
//int Hash(int key) {
//	return key % p;
//}
//bool InsertHash(HashTable* H, int key) {
//	if (H->count == HashSize)return false;
//	int addr = Hash(key);
//	while (H->elem[addr] != NULLKEY && H->elem[addr] != DELETE) {
//		addr++;
//	}
//	H->elem[addr] = key;
//	H->count++;
//	return true;
//}
//
//bool DeleteHash(HashTable* H, int key) {
//	if (H->count == 0)return false;
//	int addr;
//	SearchHash(*H, key, &addr);
//	H->elem[addr] = DELETE;
//	return true;
//}
//
//bool SearchHash(HashTable H, int key, int* addr) {
//	if (H.count == 0)return false;
//	*addr = Hash(key);
//	while (H.elem[*addr] != key) {
//		*addr = (*addr + 1) % p;
//		if (H.elem[*addr] == NULLKEY || *addr == Hash(key)) {
//			return false;
//		}
//	}
//	return true;
//}