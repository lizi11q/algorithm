#include<stdio.h>
#define MAXSIZE 100
int Search1(int* arr, int n, int key);
int Search2(int* arr, int n, int key);
int Search3(int* arr, int n, int key);
int F[MAXSIZE];
int Search4(int* arr, int n, int key);
int main() {
	//无效数据为arr[0]
	int arr[MAXSIZE] = { 0,11,19,25,32,39,47,60,72,81,93 };
	int result;

	result = Search1(arr, 10, 60);
	printf("%d\n", result);

	result = Search2(arr, 10, 60);
	printf("%d\n", result);

	result = Search3(arr, 10, 60);
	printf("%d\n", result);

	F[0] = 0;
	F[1] = 1;
	for (int i = 2;i < MAXSIZE;i++) {
		F[i] = F[i - 1] + F[i - 2];
	}

	result = Search4(arr, 10, 60);
	printf("%d\n", result);

	return 0;
}
int Search1(int* arr, int n, int key) {
	arr[0] = key;
	int i = n;
	while (arr[i] != key) {
		i--;
	}
	return i;
}
int Search2(int* arr, int n, int key) {
	int low, high, mid;
	low = 1;
	high = n;
	while (low <= high) {
		mid = (low + high) / 2;
		if (key > arr[mid]) {
			low = mid + 1;
		}
		else if (key < arr[mid]) {
			high = mid - 1;
		}
		else {
			return mid;
		}
	}
	return 0;
}
int Search3(int* arr, int n, int key) {
	int low, high, mid;
	low = 1;
	high = n;
	while (low <= high) {
		mid = low + (high - low) * (key - arr[low]) / (arr[high] - arr[low]);
		if (key > arr[mid]) {
			low = mid + 1;
		}
		else if (key < arr[mid]) {
			high = mid - 1;
		}
		else {
			return mid;
		}
	}
	return 0;
}
int Search4(int* arr, int n, int key) {
	int low, high, mid, i, k;
	low = 1;
	k = 0;
	while (n > F[k] - 1) {
		k++;
	}
	for (i = n;i <= F[k] - 1;i++) {
		arr[i] = arr[n];
	}
	high = F[k] - 1;
	while (low <= high) {
		mid = low + F[k - 1] - 1;
		if (key > arr[mid]) {
			low = mid + 1;
			k -= 2;
		}
		else if (key < arr[mid]) {
			high = mid - 1;
			k -= 1;
		}
		else {
			return (mid <= n) ? mid : n;
		}
	}
	return 0;
}