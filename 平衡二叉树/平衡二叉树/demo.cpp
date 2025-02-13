#include<stdio.h>
#include<stdlib.h>
#define LH 1
#define EH 0
#define RH -1

typedef struct BiTNode {
	int data;
	int bf;
	struct BiTNode* lchild, * rchild;
}BiTNode,*BiTree;

void R_Rotate(BiTree* T);
void L_Rotate(BiTree* T);
void LeftBalance(BiTree* T);
void RightBalance(BiTree* T);
bool insertAVL(BiTree* T, int e, bool* taller);

int main() {
	int i;
	int a[] = { 3,2,1,4,5,6,7,10,9,8 };
	BiTree T = NULL;
	bool taller;

	for (i = 0;i < 10;i++) {
		insertAVL(&T, a[i], &taller);
	}
	return 0;
}

void R_Rotate(BiTree* T) {
	BiTree L;
	L = (*T)->lchild;
	(*T)->lchild = L->rchild;
	L->rchild = (*T);
	*T = L;
}

void L_Rotate(BiTree* T) {
	BiTree L;
	L = (*T)->rchild;
	(*T)->rchild = L->lchild;
	L->lchild = (*T);
	(*T) = L;
}

void LeftBalance(BiTree* T) {
	BiTree L, Lr;
	L = (*T)->lchild;
	switch (L->bf) {
	case LH:
		(*T)->bf = EH;
		L->bf = EH;
		R_Rotate(T);
		break;
	case RH:
		Lr = L->rchild;
		switch (Lr->bf) {
		case LH:
			(*T)->bf = RH;
			L->bf = EH;
			break;
		case EH:
			(*T)->bf = EH;
			L->bf = EH;
			break;
		case RH:
			(*T)->bf = EH;
			L->bf = LH;
			break;
		}
		Lr->bf = EH;
		L_Rotate(&(*T)->lchild);
		R_Rotate(T);
		break;
	}
}

void RightBalance(BiTree* T) {
	BiTree R, Rl;
	R = (*T)->rchild;
	switch (R->bf) {
	case RH:
		(*T)->bf = EH;
		R->bf = EH;
		L_Rotate(T);
		break;
	case LH:
		Rl = R->lchild;
		switch (Rl->bf) {
		case LH:
			(*T)->bf = EH;
			R->bf = RH;
			break;
		case EH:
			(*T)->bf = EH;
			R->bf = EH;
			break;
		case RH:
			(*T)->bf = LH;
			R->bf = EH;
			break;
		}
		Rl->bf = EH;
		R_Rotate(&(*T)->rchild);
		L_Rotate(T);
		break;
	}
}

bool insertAVL(BiTree* T, int e, bool* taller) {
	if (!*T) {
		*T = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;
		*taller = true;
	}
	else {
		if (e == (*T)->data) {
			*taller = false;
			return false;
		}
		else if (e < (*T)->data) {
			if (!insertAVL(&(*T)->lchild, e, taller)) {
				return false;
			}
			if (*taller) {
				switch ((*T)->bf) {
				case LH:
					LeftBalance(T);
					*taller = false;
					break;
				case EH:
					(*T)->bf = LH;
					*taller = true;
					break;
				case RH:
					(*T)->bf = EH;
					*taller = false;
					break;
				}
			}
		}
		else {
			if (!insertAVL(&(*T)->rchild, e, taller)) {
				return false;
			}
			if (*taller) {
				switch ((*T)->bf) {
				case RH:
					RightBalance(T);
					*taller = false;
					break;
				case EH:
					(*T)->bf = RH;
					*taller = true;
					break;
				case LH:
					(*T)->bf = EH;
					*taller = false;
					break;
				}
			}
		}
	}
	return true;
}