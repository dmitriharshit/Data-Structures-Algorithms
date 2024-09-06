#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Node structure:
typedef struct binarytree
{
    long long int val;
    int leftsize;
    int rightsize;
    struct binarytree *left;
    struct binarytree *right;
} BST;
BST **array;
int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int size(BST *root) // returns number of nodes in subtree
{
    if (root == NULL)
    {
        return 1;
    }
    return size(root->left) + size(root->right);
}

void convertToArray(BST *root, int *p)
{
    if (root == NULL)
    {
        return;
    }
    convertToArray(root->left, p);
    array[*p] = root;
    *p = *p + 1;
    convertToArray(root->right, p);
}

BST *sortedArrayToBST(int left, int right)
{
    int mid = (left + right) / 2;
    if (left >= right)
        return NULL;
    array[mid]->left = sortedArrayToBST(left, mid);
    array[mid]->leftsize = mid - left;
    array[mid]->rightsize = right - mid - 1;
    array[mid]->right = sortedArrayToBST(mid + 1, right);
    return array[mid];
}

BST *balance(BST *root)
{
    int n = size(root);
    array = (BST **)malloc((n - 1) * sizeof(BST *)); // array of node pointers
    int p = 0;
    convertToArray(root, &p);          // stores the pointers of all node of subtree in increasing order of key value
    root = sortedArrayToBST(0, n - 1); // converts the sorted array to perfectly balanced binary search tree
    free(array);
    return root;
}

BST *makenew(int a) // makes new node
{
    BST *temp = (BST *)malloc(sizeof(BST));
    temp->leftsize = 0;
    temp->rightsize = 0;
    temp->left = NULL;
    temp->right = NULL;
    temp->val = a;
    return temp;
}

BST *insert(int a, BST *root)
{
    BST *node = root->right, *prevnode = root;
    if (node == NULL)
    {
        root->right = makenew(a);
        return root;
    }
    while (node != NULL)
    {
        if (node->val < a)
        {
            if (node->rightsize >= 3 * (node->leftsize)) // if condition for nearly balanced tree is violated
            {
                prevnode->right = balance(node);
                node = prevnode->right;
                prevnode->rightsize = max(node->leftsize, node->rightsize) + 1;
            }
            node->rightsize++;
            prevnode = node;
            node = node->right;
        }
        else
        {
            if (node->leftsize >= 3 * (node->rightsize)) // same for left subtree
            {
                prevnode->left = balance(node);
                node = prevnode->left;
                prevnode->leftsize = max(node->leftsize, node->rightsize) + 1;
            }
            node->leftsize++;
            prevnode = node;
            node = node->left;
        }
    }
    if (prevnode->val < a)
        prevnode->right = makenew(a);
    else
        prevnode->left = makenew(a);
    return root;
}
int main()
{
    FILE *file1;
    file1 = fopen("Question_4a.csv", "w+"); // stores data for Q4(a)
    FILE *file2;
    file2 = fopen("Question_4b.csv", "w+"); // stores data for Q4(b)

    BST *root = makenew(-99999999); // One extra node. The whole BST lies at the right of this node

    long long int n = 10000000, j, i;
    double total_time = 0; // stores total time for ith insertion i.e., total time from i=1 to i
    for (i = 1; i <= n; i++)
    {
        clock_t start_t, end_t;
        double total_t;
        start_t = clock();
        root = insert(i, root);
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        total_time = total_time + total_t;
        if (i % 50000 == 0)
        {
            printf("%lld, %f\n", i, total_time);
        }
        if (i >= 100000 && i <= 1000000)
        {
            printf("%lld, %f\n", i, total_t);
        }
    }
    printf("DONE");
    return 0;
}