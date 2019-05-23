#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int data;
	struct Node *lchild;
	struct Node *rchild;
}*root=NULL;

void Insert(int key)
{
	struct Node *t=root;
	struct Node *r, *p;

	p = (struct Node *)malloc(sizeof(struct Node));
	p->data = key;
	p->lchild = p->rchild = NULL;

	if (root == NULL) {
		root = p;
		return;
	}

	while (t != NULL) {
		r = t;
		if (key < t->data)
			t = t->lchild;
		else if (key > t->data)
			t = t->rchild;
		else
			return;
	}
	
	if (key < r->data)
		r->lchild = p;
	else
		r->rchild = p;
}

void Inorder(struct Node *p)
{
	if (p) {
		Inorder(p->lchild);
		printf("%d ", p->data);
		Inorder(p->rchild);
	}
}

struct Node *Search(int key)
{
	struct Node *t=root;

	while (t != NULL) {
		if (key == t->data)
			return t;
		else if (key < t->data)
			t = t->lchild;
		else
			t = t->rchild;
	}
	return NULL;
}

struct Node *Rinsert(struct Node *p, int key)
{
	struct Node *t=NULL;

	if (p == NULL) {
		t = (struct Node *)malloc(sizeof(struct Node));
		t->data = key;
		t->lchild = t->rchild = NULL;
		return t;
	}

	if (key < p->data)
		p->lchild = Rinsert(p->lchild, key);
	else if (key > p->data)
		p->rchild = Rinsert(p->rchild, key);
	return p;
}

int Height(struct Node *p)
{
	int x, y;

	if (p == NULL)
		return 0;
	x = Height(p->lchild);
	y = Height(p->rchild);
	return x>y?x+1:y+1;
}

struct Node *Inpre(struct Node *p)
{
	while(p && p->rchild!=NULL)
    	p = p->rchild;
	 return p;
}

struct Node *Insucc(struct Node *p)
{
	while(p && p->lchild!=NULL)
    	p = p->lchild;
	return p;
}

struct Node *Delete(struct Node *p, int key)
{
	struct Node *q;

	if (p == NULL)
		return NULL;
	if (p->lchild == NULL && p->rchild == NULL){
		if (p == root)
			root = NULL;
		free(p);
		return NULL;
	}
	if (key < p->data)
		p->lchild = Delete(p->lchild, key);
	else if (key > p->data)
		p->rchild = Delete(p->rchild, key);
	else {
		if (Height(p->lchild) > Height(p->rchild)) {
			q = Inpre(p->lchild);
			p->data = q->data;
			p->lchild = Delete(p->lchild, key);
		} else {
			q = Insucc(p->rchild);              	
			p->data = q->data;
		   	p->rchild = Delete(p->rchild, key);
		}
	}
	return p;
}

int main()
{
	struct Node *temp;

#if 0
	Insert(10);
	Insert(5);
	Insert(20);
	Insert(8);
	Insert(30);
#endif

	root = Rinsert(root, 10);
	Rinsert(root, 5);
	Rinsert(root, 20);
	Rinsert(root, 8);
	Rinsert(root, 30);
	
	Delete(root, 20);

	Inorder(root);
	printf("\n");

	temp = Search(20);
	if ( temp != NULL)
		printf("Element %d is found\n", temp->data);
	else
		printf("Element is not found\n");

	return 0;
}
