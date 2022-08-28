#include<stdio.h>
#include<malloc.h>


typedef struct node
{
	struct node* left;
	struct node* right;
	int height;
	int value;
} node;

node* make_tree(int value_to_add, node** mem1)
{
	node* new_node = (*mem1)++;

	new_node->value = value_to_add;
	new_node->height = 1;
	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}

int Height(node* tree)
{
	return (tree == NULL) ? 0 : tree->height;
}

void fixHeight(node* tree)
{
	int left_height = Height(tree->left),
		right_height = Height(tree->right);

	if (left_height > right_height)
		tree->height = left_height + 1; 
	else
		tree->height = right_height + 1;
	
}

node* rotateRight(node* tree)
{
	node* new_root = tree->left;
	tree->left = new_root->right;
	new_root->right = tree;

	fixHeight(tree);
	fixHeight(new_root);

	return new_root;
}

node* rotateLeft(node* tree)
{
	node* new_root = tree->right;
	tree->right = new_root->left;
	new_root->left = tree;

	fixHeight(tree);
	fixHeight(new_root);

	return new_root;
}


node* balance_tree(node* tree)
{
	node* LeftTree = tree->left,
		* RightTree = tree->right;

	fixHeight(tree);

	if (Height(RightTree) - Height(LeftTree) == 2)
	{
		if (Height(RightTree->right) < Height(RightTree->left))
			tree->right = rotateRight(RightTree);
		return rotateLeft(tree);
	}
	if (Height(RightTree) - Height(LeftTree) == -2)
	{
		if (Height(LeftTree->right) > Height(LeftTree->left))
			tree->left = rotateLeft(LeftTree);
		return rotateRight(tree);
	}
	return tree;
}

node* add_to_tree(node* tree, int value_to_add, node** mem1)
{
	if (tree == NULL)
	{
		return make_tree(value_to_add, mem1);
	}
	else
	{
		if (tree->value >= value_to_add)
		{
			if (tree->left == NULL)
				tree->left = make_tree(value_to_add, mem1);
			else
				tree->left = add_to_tree(tree->left, value_to_add, mem1);
		}
		else
		{
			if (tree->right == NULL)
				tree->right = make_tree(value_to_add, mem1);
			else
				tree->right = add_to_tree(tree->right, value_to_add, mem1);
		}
		return balance_tree(tree);
	}
}

int main(void)
{
	int n,           // amount of vertexes
		value_to_add;
	node* tree = NULL;
	if (scanf_s("%d", &n) != 1)  // ?
	{
		printf("");
		return 1;
	}
	node* storage = (node*)malloc(n * sizeof(node)); // storage for nodes

	if (storage == NULL)
	{
		printf("Couldn't allocate memory for storage");
		return 1;
	}

	node* mem = storage; // pointer to the first position int storage
	node** mem1 = &mem;
	for (int i = 0; i < n; i++)
	{
		scanf_s("%d", &value_to_add); // reading input numbers
		tree = add_to_tree(tree, value_to_add, mem1); // adding to the tree
	}

	printf("%d\n", Height(tree));
	free(storage);
	return 0;
}
