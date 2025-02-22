#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

typedef struct {
    /* 用于存储要排序数组，r[0]用作哨兵或临时变量 */
    int* r;
    int lenth;
}SqList;

SqList InitSqList();
void swap(SqList* L, int i, int j);
void print(SqList L);
void BubbleSort1(SqList* S);
void BubbleSort2(SqList* S);
void SelectSort(SqList* S);
void InsertSort(SqList* S);
void ShellSort(SqList* S);
void ShellSort2(SqList* S);

void HeapAdjust(SqList* L, int s, int m);
void HeapSort(SqList* L);

void merge(int SR[], int TR[], int i, int m, int n);
void MSort(int SR[], int TR1[], int s, int t);
//递归归并排序
void MergeSort(SqList* L);
//非递归归并排序
void MergePass(int SR[], int TR[], int s, int n);
void MergeSort2(SqList* L);

//快速排序
void QuickSort(SqList* L);
void QSort(SqList* L, int low, int high);
int Partition(SqList* L, int low, int high);


int main() {
    int arr[] = { 42, 17, 89, 63, 5, 71, 34, 98, 22, 56, 80, 11 };
    SqList S = InitSqList();
    for (int i = 1;i <= 12;i++) {
        S.r[i] = arr[i - 1];
        S.lenth++;
    }
    print(S);

    /*BubbleSort1(&S);*/
    /*BubbleSort2(&S);*/
    /*SelectSort(&S);*/
    /*InsertSort(&S);*/
    /*ShellSort(&S);*/
    /*HeapSort(&S);*/
    /*MergeSort(&S);*/
    /*MergeSort2(&S);*/
    QuickSort(&S);

    print(S);

    return 0;
}

SqList InitSqList() {
    SqList S;
    S.lenth = 0;
    S.r = (int*)malloc(sizeof(int) * (MAXSIZE + 1));
    return S;
}

void swap(SqList* L, int i, int j) {
    int temp = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = temp;
}

void print(SqList L) {
    for (int i = 1;i <= L.lenth;i++) {
        printf("%d ", L.r[i]);
    }
    printf("\n");
}

void BubbleSort1(SqList* S) {
    int i, j, k;
    for (k = 0;k < S->lenth - 1;k++) {
        for (i = 1;i < S->lenth - k;i++) {
            j = i + 1;
            if (S->r[i] > S->r[j]) {
                swap(S, i, j);
            }
        }
    }
}

void BubbleSort2(SqList* S) {
    int i, j, k;
    bool flag = true;
    for (k = 0;k < S->lenth - 1 && flag;k++) {
        flag = false;
        for (i = 1;i < S->lenth - k;i++) {
            j = i + 1;
            if (S->r[i] > S->r[j]) {
                swap(S, i, j);
                flag = true;
            }
        }
    }
}

void SelectSort(SqList* S) {
    int i, j, min;
    for (i = 1;i < S->lenth;i++) {
        min = i;
        for (j = i + 1;j <= S->lenth;j++) {
            if (S->r[j] < S->r[min]) {
                min = j;
            }
        }
        if (min != i) {
            swap(S, i, min);
        }
    }
}

void InsertSort(SqList* S) {
    int i, j, k;
    for (k = 1;k < S->lenth;k++) {
        i = k + 1;
        if (S->r[k] > S->r[i]) {
            S->r[0] = S->r[i];
            S->r[i] = S->r[k];
            j = k - 1;
            while (S->r[j] > S->r[0]) {
                S->r[j + 1] = S->r[j];
                j--;
            }
            S->r[j + 1] = S->r[0];
        }
    }
}

void ShellSort(SqList* S) {
    int i, j, k, t;
    int increment = S->lenth;
    do {
        increment = increment / 3 + 1;
        for (t = 1;t <= increment;t++) {
            for (k = t;k + increment <= S->lenth;k += increment) {
                i = k + increment;
                if (S->r[k] > S->r[i]) {
                    S->r[0] = S->r[i];
                    S->r[i] = S->r[k];
                    j = k - increment;
                    while (S->r[j] > S->r[0] && j > 0) {
                        S->r[j + increment] = S->r[j];
                        j -= increment;
                    }
                    S->r[j + increment] = S->r[0];
                }
            }
        }
    } while (increment > 1);
}

void ShellSort2(SqList* S) {
    int i, j;
    int increment = S->lenth;

    while (increment > 1) {
        increment = increment / 3 + 1;  // 增量序列

        for (i = increment; i <= S->lenth; i++) {
            int temp = S->r[i];  // 待插入元素
            j = i - increment;

            // 插入排序
            while (j >= 1 && S->r[j] > temp) {
                S->r[j + increment] = S->r[j];
                j -= increment;
            }
            S->r[j + increment] = temp;
        }
    }
}

/******堆排序******/
void HeapAdjust(SqList* L, int s, int m) {
    int temp, j;
    temp = L->r[s];
    for (j = 2 * s;j <= m;j *= 2) {
        if (j < m&& L->r[j] < L->r[j + 1]) {
            j++;
        }
        if (temp >= L->r[j]) {
            break;
        }
        L->r[s] = L->r[j];
        s = j;
    }
    L->r[s] = temp;
}

void HeapSort(SqList* L) {
    int i;
    for (i = L->lenth / 2;i > 0;i--) {
        HeapAdjust(L, i, L->lenth);
    }
    for (i = L->lenth;i > 1;i--) {
        swap(L, 1, i);
        HeapAdjust(L, 1, i - 1);
    }
}
/******堆排序******/

/******归并排序******/
void merge(int SR[], int TR[], int i, int m, int n) {
    int j, k, l;
    for (j = m + 1, k = i;i <= m && j <= n;k++) {
        if (SR[i] <= SR[j]) {
            TR[k] = SR[i++];
        }
        else {
            TR[k] = SR[j++];
        }
    }

    if (i <= m) {
        for (l = 0;l <= m - i;l++) {
            TR[k + l] = SR[i + l];
        }
    }
    if (j <= n) {
        for (l = 0;l <= n - j;l++) {
            TR[k + l] = SR[j + l];
        }
    }
}

void MSort(int SR[], int TR1[], int s, int t) {
    int m;
    int TR2[MAXSIZE + 1];
    if (s == t) {
        TR1[s] = SR[s];
    }
    else {
        m = (s + t) / 2;
        MSort(SR, TR2, s, m);
        MSort(SR, TR2, m + 1, t);
        merge(TR2, TR1, s, m, t);
    }
}

void MergeSort(SqList* L) {
    MSort(L->r, L->r, 1, L->lenth);
}

/******归并排序******/
void MergePass(int SR[], int TR[], int s, int n) {
    int i = 1;
    while (i <= n - 2 * s + 1) {
        merge(SR, TR, i, i + s - 1, i + 2 * s - 1);
        i = i + 2 * s;
    }

    if (i < n - s + 1) {
        merge(SR, TR, i, i + s - 1, n);
    }
    else {
        while (i <= n) {
            TR[i] = SR[i];
            i++;
        }
    }
}

void MergeSort2(SqList* L) {
    int* TR = (int*)malloc(sizeof(int) * L->lenth);
    int s = 1;
    while (s < L->lenth) {
        MergePass(L->r, TR, s, L->lenth);
        s *= 2;
        MergePass(TR, L->r, s, L->lenth);
        s *= 2;
    }
}
/******归并排序******/

/****快速排序****/
void QuickSort(SqList* L) {
    QSort(L, 1, L->lenth);
}

void QSort(SqList* L, int low, int high) {
    int pivot;
    if (low < high) {
        pivot = Partition(L, low, high);
        QSort(L, low, pivot - 1);
        QSort(L, pivot + 1, high);
    }
}

int Partition(SqList* L, int low, int high) {
    int pivotkey;
    int m = low + (low + high) / 2;
    if (L->r[low] > L->r[high]) {
        swap(L, low, high);
    }
    if (L->r[m] > L->r[high]) {
        swap(L, m, high);
    }
    if (L->r[low] < L->r[m]) {
        swap(L, low, m);
    }
    pivotkey = L->r[low];
    L->r[0] = pivotkey;
    while (low < high) {
        while (low < high && L->r[high] >= pivotkey) {
            high--;
        }
        L->r[low] = L->r[high];
        while (low < high && L->r[low] <= pivotkey) {
            low++;
        }
        L->r[high] = L->r[low];
    }
    L->r[low] = L->r[0];
    return low;
}

/****快速排序****/