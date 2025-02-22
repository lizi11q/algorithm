//#include<stdio.h>
//#include<stdlib.h>
//#define MAXSIZE 100
//
//typedef struct {
//	/* 用于存储要排序数组，r[0]用作哨兵或临时变量 */
//	int* r;
//	int lenth;
//}SqList;
//
//SqList InitSqList();
//void swap(SqList* L, int i, int j);
//void print(SqList L);
//void BubbleSort1(SqList* S);
//void BubbleSort2(SqList* S);
//void SelectSort(SqList* S);
//void InsertSort(SqList* S);
//void ShellSort(SqList* S);
//
//
//int main() {
//	int arr[] = { 42, 17, 89, 63, 5, 71, 34, 98, 22, 56, 80, 11 };
//	SqList S = InitSqList();
//	for (int i = 1;i <= 12;i++) {
//		S.r[i] = arr[i - 1];
//		S.lenth++;
//	}
//	print(S);
//
//	/*BubbleSort1(&S);*/
//
//	/*BubbleSort2(&S);*/
//
//	/*SelectSort(&S);*/
//
//	/*InsertSort(&S);*/
//
//	ShellSort(&S);
//
//
//	print(S);
//
//	return 0;
//}
//
//SqList InitSqList() {
//	SqList S;
//	S.lenth = 0;
//	S.r = (int*)malloc(sizeof(int) * (MAXSIZE + 1));
//	return S;
//}
//
//void swap(SqList* L, int i, int j) {
//	int temp = L->r[i];
//	L->r[i] = L->r[j];
//	L->r[j] = temp;
//}
//
//void print(SqList L) {
//	for (int i = 1;i <= L.lenth;i++) {
//		printf("%d ", L.r[i]);
//	}
//	printf("\n");
//}
//
//void BubbleSort1(SqList* S) {
//	int i, j, k;
//	for (k = 0;k < S->lenth - 1;k++) {
//		for (i = 1;i < S->lenth - k;i++) {
//			j = i + 1;
//			if (S->r[i] > S->r[j]) {
//				swap(S, i, j);
//			}
//		}
//	}
//}
//
//void BubbleSort2(SqList* S) {
//	int i, j, k;
//	bool flag = true;
//	for (k = 0;k < S->lenth - 1 && flag;k++) {
//		flag = false;
//		for (i = 1;i < S->lenth - k;i++) {
//			j = i + 1;
//			if (S->r[i] > S->r[j]) {
//				swap(S, i, j);
//				flag = true;
//			}
//		}
//	}
//}
//
//void SelectSort(SqList* S) {
//	int i, j, min;
//	for (i = 1;i < S->lenth;i++) {
//		min = i;
//		for (j = i + 1;j <= S->lenth;j++) {
//			if (S->r[j] < S->r[min]) {
//				min = j;
//			}
//		}
//		if (min != i) {
//			swap(S, i, min);
//		}
//	}
//}
//
//void InsertSort(SqList* S) {
//	int i, j, k;
//	for (k = 1;k < S->lenth;k++) {
//		i = k + 1;
//		if (S->r[k] > S->r[i]) {
//			S->r[0] = S->r[i];
//			S->r[i] = S->r[k];
//			j = k - 1;
//			while (S->r[j] > S->r[0]) {
//				S->r[j + 1] = S->r[j];
//				j--;
//			}
//			S->r[j + 1] = S->r[0];
//		}
//	}
//}
//
//void ShellSort(SqList* S) {
//	int i, j, k, t;
//	int increment = S->lenth;
//	do {
//		increment = increment / 3 + 1;
//		for (t = 1;t <= increment;t++) {
//			for (k = t;k + increment <= S->lenth;k += increment) {
//				i = k + increment;
//				if (S->r[k] > S->r[i]) {
//					S->r[0] = S->r[i];
//					S->r[i] = S->r[k];
//					j = k - increment;
//					while (S->r[j] > S->r[0] && j > 0) {
//						S->r[j + increment] = S->r[j];
//						j -= increment;
//					}
//					S->r[j + increment] = S->r[0];
//				}
//			}
//		}
//	} while (increment > 1);
//}
//
//void ShellSort2(SqList* S) {
//	int i, j;
//	int increment = S->lenth;
//
//	while (increment > 1) {
//		increment = increment / 3 + 1;  // 增量序列
//
//		for (i = increment; i <= S->lenth; i++) {
//			int temp = S->r[i];  // 待插入元素
//			j = i - increment;
//
//			// 插入排序
//			while (j >= 1 && S->r[j] > temp) {
//				S->r[j + increment] = S->r[j];
//				j -= increment;
//			}
//			S->r[j + increment] = temp;
//		}
//	}
//}