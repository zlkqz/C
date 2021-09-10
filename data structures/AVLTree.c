# include <stdio.h>
# include <stdlib.h>

typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
    struct node *parent;
    int height;
} node_t;


int get_height(node_t *p){
	if(!p)
		return 0;
	else
		return p->height;
}

node_t* avl_insert(node_t *root, int val){
 
	node_t *s, *A, *B, *C, *p, *fp;
	//依次:插入点, 失衡点(也可能是旋转点),旋转点,旋转点(也可能是插入点=s),动点,跟踪点
	int i, k;//平衡因子 
	
	s = (node_t *)malloc(sizeof(node_t));
	if(!s) return NULL;
	
	s->val = val;
	s->left = s->parent = s->right = NULL;
	s->height = 1;
	
	//类似于指针跟踪技术,p为动指针,A为跟踪指针 
	A = root; A->parent = NULL;
	p = root; p->parent = NULL;
	
	//找出A 
	if(!p)
		root = s;
	else{
		while(p){
			//先找出最近的A->height!=0的结点, 就是最后的失衡点
			i = get_height(p->left) - get_height(p->right); 
			if(i){
				A = p;
				A->parent = p->parent;
			}
			//fp跟踪p,因为下一步p会往下移动,p最终指向s的那一层 
			fp = p;
			if(val < p->val)
				p = p->left;
			else
				p = p->right;
			}//p最终指向NULL就推出循环	 
	} 
	
	//插入, 此时fp是p的前一个结点,p指向空 
	if(val < fp->val)
		fp->left = s;
	else
		fp->right = s;
		
	//确定旋转结点B,修改A的平衡因子
	if(val < A->val)
		B = A->left;
	else
		B = A->right;
 
	A->height++;
	
	//修改路径B到s的高度, B在A的下一层 
	p = B; // p最终指向s, 之前指向的是s这一层,但是是空
 
	while(p != s){
		p->height++;
		if(val < p->val)
			p = p->left; 
		else
			p = p->right;	
	}
	//最终s的高度没有++的 
		
	
	//调整完高度就修改结点和指针, 首先需要判断失衡类型
	//分为LL,LR,RR,RL
	//结点A,B平衡因子在修改指针的过程中会变化,但是路径上的结点不会
	//指针修改包括s结点指针和原来双亲结点指针 
	i = get_height(A->left) - get_height(A->right);
	k = get_height(B->left) - get_height(B->right); 
	
	if(i == 2 && k == 1){//LL
		//B作为旋转结点
		//先改结点指针, 此时s插入在B的左子树下, 原来可以认为B左右子树,A右子树均为空
		A->left = B->right;
		B->right = A;
		
		//考虑原来A结点的指针,改成B后相应的指针也要改变,下面同理
		if(A->parent == NULL)
			root = B;
		else if(A->parent->left == A)
			A->parent->left = B;
		else
			A->parent->right = B;		
	}
	else if(i == -2 && k == -1){//RR
		A->right = B->left;
		B->left = A;
		
		if(A->parent == NULL)
			root = B;
		else if(A->parent->left == A)
			A->parent->left = B;
		else
			A->parent->right = B;	
	}
	else if(i == 2 && k == -1){//LR
		//此时认为C的左右子树空,B逆时针旋转,A顺时针旋转, s插入C的左子树或者右子树 
		//如果C结点也是空,也就是说B右子树空,那么直接插入C=s为B右子树,此时A右子树也是空的 
		C = B->right;
		B->right = C->left;
		A->left = C->right;
		C->left = B;
		C->right = A;
		
		if(A->parent == NULL)
			root = C;
		else if(A->parent->left == A)
			A->parent->left = C;
		else
			A->parent->right = C;
	}
	else if(i == -2 && k == 1){//RL 
		//和LR一样,画图来看就好
		C = B->left;
		A->right = C->left;
		B->left = C->right;
		C->left = A;
		C->right = B;
		
		if(A->parent == NULL)
			root = C;
		else if(A->parent->left == A)
			A->parent->left = C;
		else
			A->parent->right = C;
	}
	return root;
}
