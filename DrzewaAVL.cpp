// DrzewaAVL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>

/////////////////////////////////////////
///             Drzewa AVL            ///
/////////////////////////////////////////

typedef struct AVL_node 
{
	int key;
	unsigned char height;
	struct AVL_node* left;
	struct AVL_node* right;
	AVL_node(int k) { key = k; left = right = NULL; height = 1; }
} AVL_node;

AVL_node* createTreeAVL(int* array, int start, int end);
AVL_node* findMaxAVL(AVL_node* root);
void printInOrderAVL(AVL_node* root);
void printPreOrderAVL(AVL_node* root);
void deletePostOrderAVL(AVL_node* root);
void printSubtreeAVL(AVL_node* root);
AVL_node* searchAVL(AVL_node* root, int key);


unsigned char height(AVL_node* p);
int bfactor(AVL_node* p);
void fixheight(AVL_node* p);
AVL_node* rotateright(AVL_node* p);
AVL_node* balance(AVL_node* p);

/////////////////////////////////////////
///             Drzewa BST            ///
/////////////////////////////////////////

typedef struct BST_node
{
	int key;
	struct BST_node* left;
	struct BST_node* right;
} BST_node;

BST_node* createTreeBST(int* array, int n);
BST_node* findMaxBST(BST_node* root);
void printInOrderBST(BST_node* root);
void printPreOrderBST(BST_node* root);
void deletePostOrderBST(BST_node* root);
void printSubtreeBST(BST_node* root); //void printSubtreeBST(int key);
BST_node* searchBST(BST_node* root, int key); //BST_node* searchBST(int key);


void shellSort(int* array, int n);

/////////////////////////////////////////
///             Debug main            ///
/////////////////////////////////////////
//TO DO: repair createTreeAVL(),deleteTreeAVL(), create deleteNodesAVL(), make all BST, 
int main()
{

	system("pause");
	return 0;
}

/////////////////////////////////////////
///             Release main          ///
/////////////////////////////////////////
/*
int main()
{
	const int n = 7;
	int array[n] = {1, 2, 3, 4, 5, 6, 7};
	bool isDone = false, isCorrectAnswer = false;
	AVL_node* testA;
	BST_node* testB;

	while (!isDone) {
		char tree;
		int answer;
		
		while (!isCorrectAnswer) {
			puts("Choose tree to build:");
			puts("   'a' - AVL-tree;");
			puts("   'b' - BST-tree;");
			scanf("%c", &tree);

			switch (tree) {
			case 'a':
				AVL_node* testA = createTreeAVL(array, 0, n - 1);
				puts("AVL-tree builded succesfully.");
				isCorrectAnswer = true;
				break;
			case 'b':
				BST_node* testB = createTreeBST(array, n);
				puts("BST-tree builded succesfully.");
				isCorrectAnswer = true;
				break;
			default:
				puts("Incorrect answer. Try again.");
				break;
			}
		}

		isCorrectAnswer = false;

		while (!isCorrectAnswer) {
			puts("What do you want to do with a tree:");
			puts("  1  Find way to max value;");
			puts("  2  Delete few elements;");
			puts("  3  Print tree in-order;");
			puts("  4  Print tree pre-order;");
			puts("  5  Delete tree post-order;");
			puts("  6  Print subtree from given key;");
			puts("  7  Balance tree using rotation;");
			puts("  8  Change tree type;");
			puts("  9  Exit;");
			puts("Give your answer:");
			scanf("%d", &answer);

			if (tree == 'a') {
				switch (answer) {
				case 1:
					findMaxAVL(testA);
					break;
				case 2:
					
					break;
				case 3:
					puts("In-order:");
					printInOrderAVL(testA);
					break;
				case 4:
					puts("Pre-order:");
					printPreOrderAVL(testA);
					break;
				case 5:
					puts("Deleting AVL-tree in post-order...");
					deletePostOrderAVL(testA);
					puts("AVL-tree deleted.");
					break;
				case 6:
					puts("Print subtree:");
					printSubtreeAVL(testA);
					break;
				case 7:
					puts("Balancing AVL-tree...");
					balance(testA);
					puts("AVL-tree balanced.");
					break;
				case 8:
					isCorrectAnswer = true;
					break;
				case 9:
					puts("Exited");
					return 0;
				default:
					puts("Incorrect answer. Try again.");
					break;
				}
			}
			else {
				switch (answer) {
				case 1:

					break;
				case 2:

					break;
				case 3:

					break;
				case 4:

					break;
				case 5:

					break;
				case 6:

					break;
				case 7:

					break;
				case 8:
					isCorrectAnswer = true;
					break;
				case 9:
					puts("Exited");
					return 0;
				default:
					puts("Incorrect answer. Try again.");
					break;
				}
			puts("");
			}
		}


	
	}
	return 0;
}
*/
AVL_node* createTreeAVL(int* array, int start, int end) {
	int median = (start + end + 1) / 2;
	AVL_node* root = new AVL_node(array[median]);

	if (start < end) {
		root->left = createTreeAVL(array, start, median - 1);
		root->right = createTreeAVL(array, median + 1, end);
	}
	return root;
}

AVL_node* findMaxAVL(AVL_node* root) {
	if (!root) {
		puts("AVL-tree is empty.");
		return root;
	}

	while (root->right) {
		printf("--> %d ", root->key);
		root = root->right;
	}

	printf("--> %d\nMax element: %d\n", root->key, root->key);
	return root;
}

void printInOrderAVL(AVL_node* root) {
	if (!root) {
		puts("AVL-tree is empty.");
		return;
	}
	if (root->left) printInOrderAVL(root->left);
	printf("%d ", root->key);
	if (root->right) printInOrderAVL(root->right);	
}

void printPreOrderAVL(AVL_node* root) {
	if (!root) {
		puts("AVL-tree is empty.");
		return;
	}
	printf("%d ", root->key);
	if (root->left) printPreOrderAVL(root->left);
	if (root->right) printPreOrderAVL(root->right);
}

void deletePostOrderAVL(AVL_node* root) {
	if (!root) {
		puts("AVL-tree is empty.");
		return;
	}

	if(root->left) deletePostOrderAVL(root->left);// if (root->left) printPreOrderAVL(root->left);
	if(root->right) deletePostOrderAVL(root->right);// if (root->right) printPreOrderAVL(root->right);
	delete root;
}

void printSubtreeAVL(AVL_node* root) {
	int key;
	AVL_node* result;

	puts("Type root key of subtree:");
	scanf("%d", &key);
	
	result = searchAVL(root, key);
	
	if (!result) {
		puts("No such element.");
	}
	else {
		printInOrderAVL(result);
	}
}

AVL_node* searchAVL(AVL_node* root, int key) {
	if (!root || root->key == key) {
		return root;
	}

	if (root->key < key)
		return searchAVL(root->left, key);

	return searchAVL(root->right, key);
}


unsigned char height(AVL_node* p) {
	return p ? p->height : 0;
}

int bfactor(AVL_node* p) {
	return height(p->right) - height(p->left);
}

void fixheight(AVL_node* p) {
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr ? hl : hr) + 1;
}

AVL_node* rotateright(AVL_node* p) {
	AVL_node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

AVL_node* rotateleft(AVL_node* q) 
{
	AVL_node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

AVL_node* balance(AVL_node* p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

/*AVL_node* insert(AVL_node* p, int k) // вставка ключа k в дерево с корнем p
{
	if (!p) return AVL_node(k);
	if (k<p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}*/

void shellSort(int* array, int n) {
	int gap = 1;
	while (gap < n / 3) {
		gap = 3 * gap + 1;
	}

	while (gap > 0) {
		for (int i = gap; i < n; i += gap) {
			for (int j = i; j > 0 && array[j] < array[j - gap]; j -= gap) {
				int temp = array[j];
				array[j] = array[j - gap];
				array[j - gap] = temp;
				//swap(&array[j], &array[j - gap]);
			}
		}
		gap = --gap / 3;
	}
}

BST_node* createTreeBST(int* array, int n){
	BST_node* root = new BST_node(array[0]);
	BST_node* node = root;
	for(int i = 1; i < n; i++){
		while(node){
			if(array[i] < node->key){ 
				if(node->left) node = node->left; 
				else{ 
					node->left = new BST_node(array[i]);
					break;
				}
			}else{
				if(node->right) node = node->right;
				else{
					node->right = new BST_node(array[i]); 
					break;
				}
			}
		}
		node = root;
	}
	return root;
}

BST_node* findMaxBST(BST_node* root){
	if(!root){
		puts("BST-tree is empty.");
		return root;
	}

	while(root->right){
		printf("--> %d ", root->key);
		root = root->right;
	}

	printf("--> %d\nMax element: %d\n", root->key, root->key);
	return root;
}

void printInOrderBST(BST_node* root){
	if(!root){
		puts("BST-tree is empty.");
		return;
	}
	if(root->left) printInOrderBST(root->left);
	printf("%d ", root->key);
	if(root->right) printInOrderBST(root->right);
}

void printPreOrderBST(BST_node* root){
	if(!root){
		puts("BST-tree is empty.");
		return;
	}
	printf("%d ", root->key);
	if(root->left) printPreOrderBST(root->left);
	if(root->right) printPreOrderBST(root->right);
}

void deletePostOrderBST(BST_node* root){
	if(!root){
		puts("BST-tree is empty.");
		return;
	}

	if(root->left) deletePostOrderBST(root->left);
	if(root->right) deletePostOrderBST(root->right);
	delete root;
}

void printSubtreeBST(BST_node* root){
	int key;
	BST_node* result;

	puts("Type root key of subtree:");
	scanf("%d", &key);

	result = searchBST(root, key);

	if(!result){
		puts("No such element.");
	} else{
		printInOrderBST(result);
	}
}

BST_node* searchBST(BST_node* root, int key){
	if(!root || root->key == key){
		return root;
	}

	if(root->key < key)
		return searchBST(root->left, key);

	return searchBST(root->right, key);
}

