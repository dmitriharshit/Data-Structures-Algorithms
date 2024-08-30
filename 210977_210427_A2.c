#include <stdio.h>
#include <stdlib.h>

// Data Structure for Matrix:
typedef struct element
{
    int val;
    int row;
    int col;
    struct element *right;
    struct element *down;
} element;

// Data Structure for Row and Column pointer for each row and column:
typedef struct headers
{
    element *next1;
    element *next2;
} headers;

// Helper Function (searches for element in a particular column with row index i):
int find(element *temp, int i)
{
    while (temp != NULL)
    {
        if (temp->row == i)
        {
            return temp->val;
        }
        temp = temp->down;
    }
    return 0;
}

// Multiplication function O(n^4) time (No time constraint given):
void multiply(headers rows1[], headers columns1[], headers rows2[], headers columns2[], int n)
{
    element *temp;
    long long int Curr;
    int j, sum = 0;
    for (int i = 0; i < n; i++)
    {
        temp = rows1[i].next1;
        j = 0;
        while (j < n)
        {
            temp = rows1[i].next1;
            Curr = 0;
            while (temp != NULL)
            {
                Curr = Curr + (temp->val) * (find(columns2[j].next1, temp->col)); //
                temp = temp->right;
            }
            if (Curr)
            {
                printf("%d %d %lld\n", i + 1, j + 1, Curr);
                sum = sum + Curr; // 'sum' stores sum of all non-zero elements.
            }
            j++;
        }
    }
    if (sum == 0)
        printf("NULL MATRIX!");
}

int main()
{
    int n, MatrixNo, r, c, v, o = 1, o1 = 1;
    element *temp1;
    element *los, *pro;
    scanf("%d", &n);
    headers rows1[n], columns1[n], rows2[n], columns2[n]; // array of pointers. (rows[i] contains a pointer for ith row & columns[i] contains a pointer for ith column)
    int currRow1 = 0, currRow2 = 0;

    for (int i = 0; i < n; i++)
    {
        columns1[i].next1 = NULL;
        columns2[i].next1 = NULL;
        rows1[i].next1 = NULL;
        rows2[i].next1 = NULL;
    }

    scanf("%d", &MatrixNo);

    // O(m) time for forming matrices:
    while (MatrixNo)
    {
        if (MatrixNo == 1) // forming matrix-1.
        {
            scanf("%d%d%d", &r, &c, &v);
            r = r - 1;
            c = c - 1;
            if (r > currRow1)
            {
                o = 1;
                currRow1 = r;
            }
            temp1 = malloc(sizeof(element));
            temp1->row = r;
            temp1->col = c;
            temp1->val = v;
            temp1->right = NULL;
            temp1->down = NULL;
            if (o)
            {
                rows1[r].next1 = temp1;
                los = temp1;
                o = 0;
            }
            else
            {
                los->right = temp1; // all elements in same row are connected with 'right' pointer.
                los = temp1;
            }
            if (columns1[c].next1 == NULL)
            {
                columns1[c].next1 = temp1;
                columns1[c].next2 = temp1;
            }
            else
            {
                columns1[c].next2->down = temp1;
                columns1[c].next2 = temp1; // all elements in same column are connected with 'down' pointer.
            }
        }
        else if (MatrixNo == 2) // Forming matrix-2.
        {
            scanf("%d%d%d", &r, &c, &v);
            r = r - 1;
            c = c - 1;
            if (r > currRow2)
            {
                o1 = 1;
                currRow2 = r;
            }
            temp1 = malloc(sizeof(element));
            temp1->row = r;
            temp1->col = c;
            temp1->val = v;
            temp1->right = NULL;
            temp1->down = NULL;
            if (o1)
            {
                rows2[r].next1 = temp1; // all elements in same row are connected with 'right' pointer.
                pro = temp1;
                o1 = 0;
            }
            else
            {
                pro->right = temp1;
                pro = temp1;
            }
            if (columns2[c].next1 == NULL)
            {
                columns2[c].next1 = temp1;
                columns2[c].next2 = temp1;
            }
            else
            {
                columns2[c].next2->down = temp1; // all elements in same column are connected with 'down' pointer.
                columns2[c].next2 = temp1;
            }
        }
        scanf("%d", &MatrixNo);
    }
    // The whole matrix can be made in O(m) space and time but as the assignmnet clearly asked for pointers for each row and column,
    // we had to add row and column pointers as well which increased time and space complexity to O(n+m) time and O(2n+m) space but
    // excluding these row and column pointers, matrix is stored in only O(m) space.
    // For structure of the final matrix so formed refer to the following link:
    // https://drive.google.com/drive/folders/1V2L5yP6vu7naobLl5dxFTnIcJiV6C-AA?usp=sharing
    multiply(rows1, columns1, rows2, columns2, n);
    return 0;
}