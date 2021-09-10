#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
    struct node *parent;
    int height;
} node_t;

int get_height(node_t *fuck){
	if(!fuck)
		return 0;
	else
		return fuck->height;
}

node_t* avl_insert(node_t *root, int val){
 
	node_t *s, *AT, *BT, *CT, *pick, *fp;
	int i, k;
	
	s = (node_t *)malloc(sizeof(node_t));
	if(!s) return NULL;
	
	s->val = val;
	s->left = s->parent = s->right = NULL;
	s->height = 1;
	AT = root; AT->parent = NULL;
	pick = root; pick->parent = NULL;
	if(!pick)
		root = s;
	else{
		while(pick){
			i = get_height(pick->left) - get_height(pick->right); 
			if(i){
				AT = pick;
				AT->parent = pick->parent;
			}
			fp = pick;
			if(val < pick->val)
				pick = pick->left;
			else
				pick = pick->right;
			}
	} 
	

	if(val < fp->val)
		fp->left = s;
	else
		fp->right = s;
		
	if(val < AT->val)
		BT = AT->left;
	else
		BT = AT->right;
 
	AT->height++;
	
	pick = BT; 
 
	while(pick != s){
		pick->height++;
		if(val < pick->val)
			pick = pick->left; 
		else
			pick = pick->right;	
	}

	i = get_height(AT->left) - get_height(AT->right);
	k = get_height(BT->left) - get_height(BT->right); 
	
	if(i == 2 && k == 1){

		AT->left = BT->right;
		BT->right = AT;
		
		if(AT->parent == NULL)
			root = BT;
		else if(AT->parent->left == AT)
			AT->parent->left = BT;
		else
			AT->parent->right = BT;		
	}
	else if(i == -2 && k == -1){
		AT->right = BT->left;
		BT->left = AT;
		
		if(AT->parent == NULL)
			root = BT;
		else if(AT->parent->left == AT)
			AT->parent->left = BT;
		else
			AT->parent->right = BT;	
	}
	else if(i == 2 && k == -1){
		CT = BT->right;
		BT->right = CT->left;
		AT->left = CT->right;
		CT->left = BT;
		CT->right = AT;
		
		if(AT->parent == NULL)
			root = CT;
		else if(AT->parent->left == AT)
			AT->parent->left = CT;
		else
			AT->parent->right = CT;
	}
	else if(i == -2 && k == 1){

		CT = BT->left;
		AT->right = CT->left;
		BT->left = CT->right;
		CT->left = AT;
		CT->right = BT;
		
		if(AT->parent == NULL)
			root = CT;
		else if(AT->parent->left == AT)
			AT->parent->left = CT;
		else
			AT->parent->right = CT;
	}
	return root;
}
