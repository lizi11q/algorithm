#include<stdio.h>
#include<stdlib.h>

typedef struct BiTNode {
	int data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

bool SearchBST(BiTree T, int key, BiTree f, BiTree* p);
bool InsertBST(BiTree* T, int key);
bool Delete(BiTree* p);
bool DeleteBST(BiTree* T, int key);
void InOrderTraverse(BiTree T);

int main() {
	int i;
	int a[] = { 62,88,58,47,35,73,51,99,37,93 };
	BiTree T = NULL;

	for (i = 0;i < 10;i++) {
		InsertBST(&T, a[i]);
	}

	InOrderTraverse(T);
	printf("\n");

	DeleteBST(&T, 47);
	DeleteBST(&T, 88);

	InOrderTraverse(T);

	return 0;
}

bool SearchBST(BiTree T, int key, BiTree f, BiTree* p) {
	if (!T) {
		*p = f;
		return false;
	}
	else if (key == T->data) {
		*p = T;
		return true;
	}
	else if (key < T->data) {
		SearchBST(T->lchild, key, T, p);
	}
	else {
		SearchBST(T->rchild, key, T, p);
	}
}

bool InsertBST(BiTree* T, int key) {
	BiTree p, s;
	if (!SearchBST(*T, key, NULL, &p)) {
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;
		s->lchild = s->rchild = NULL;
		if (!p) {
			*T = s;
		}
		else if (key < p->data) {
			p->lchild = s;
		}
		else {
			p->rchild = s;
		}
		return true;
	}
	return false;
}

bool Delete(BiTree* p) {
	BiTree q, s;
	if ((*p)->rchild == NULL) {
		q = *p;
		*p = (*p)->lchild;
		free(q);
	}
	else if ((*p)->lchild == NULL) {
		q = *p;
		*p = (*p)->rchild;
		free(q);
	}
	else {
		q = *p;
		s = (*p)->lchild;
		while (s->rchild) {
			q = s;
			s = s->rchild;
		}
		(*p)->data = s->data;
		if (q != *p) {
			q->rchild = s->lchild;
		}
		else {
			q->lchild = s->lchild;
		}
		free(s);
	}
	return true;
}

bool DeleteBST(BiTree* T, int key) {
	if (!*T) {
		return false;
	}
	else {
		if ((*T)->data == key) {
			Delete(T);
		}
		else if (key < (*T)->data) {
			DeleteBST(&(*T)->lchild, key);
		}
		else {
			DeleteBST(&(*T)->rchild, key);
		}
	}
}

void InOrderTraverse(BiTree T) {
	if (!T) {
		return;
	}
	InOrderTraverse(T->lchild);
	printf("%d ", T->data);
	InOrderTraverse(T->rchild);
}