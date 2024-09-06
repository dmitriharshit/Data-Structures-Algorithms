#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Linked list based implementation of stack:
typedef struct stack
{
    int val;
    struct stack *down;
} stack;

// Standard Functions on stack:
stack *Push(int x, stack *head)
{
    if (head == NULL)
    {
        head = malloc(sizeof(stack));
        head->val = x;
        head->down = NULL;
        return head;
    }
    stack *temp = malloc(sizeof(stack));
    temp->val = x;
    temp->down = head;
    head = temp;
    return head;
}

stack *Pop(stack *head)
{
    if (head == NULL)
    {
        return 0;
    }
    head = head->down;
    return head;
}

int Top(stack *head)
{
    return head->val;
}

int insidepriority(char x)
{
    if (x == '$')
        return -1;
    if (x == '-' || x == '+')
        return 1;
    if (x == '/' || x == '*')
        return 3;
    if (x == '^')
        return 5;
    if (x == '(')
        return 0;
    return -1;
}

int outsidepriority(char x)
{
    if (x == '$')
        return -1;
    if (x == '+')
        return 1;
    if (x == '-')
        return 2; // So that substraction occurs from right to left.
    if (x == '*')
        return 3;
    if (x == '/') // So that division occurs from right to left.
        return 4;
    if (x == '^')
        return 6;
    if (x == '(')
        return 7;
    return -1;
}

int execute(stack **O_stack, stack **N_stack)
{
    int n1, n2, Ans;
    char o;
    o = Top(*O_stack);
    *O_stack = Pop(*O_stack);
    n1 = Top(*N_stack);
    *N_stack = Pop(*N_stack);
    n2 = Top(*N_stack);
    *N_stack = Pop(*N_stack);
    if (o == '+')
        Ans = n1 + n2;
    else if (o == '-')
        Ans = n2 - n1;
    else if (o == '*')
        Ans = n2 * n1;
    else if (o == '/')
        Ans = n2 / n1;
    else if (o == '^')
        Ans = pow(n2, n1);
    return Ans;
}

int main()
{
    stack *N_stack = NULL, *O_stack = NULL;
    int n, n1, n2;
    scanf("%d\n", &n);
    char a, str[n];
    scanf("%s", str);
    O_stack = Push('$', O_stack);
    N_stack = Push(0, N_stack); // If the first character is operator and not a number.
    for (int i = 0; i < n; i++)
    {
        a = str[i];
        if (a >= 48 && a <= 57)
        {
            n1 = 0;
            while (str[i] >= 48 && str[i] <= 57 && i < n) // If the number is multidigit.
            {
                str[i] = str[i] - '0';
                n1 = n1 * 10 + str[i];
                i++;
            }
            N_stack = Push(n1, N_stack);
            i--;
        }
        else if (a == ')')
        {
            while (Top(O_stack) != '(')
            {
                n2 = execute(&O_stack, &N_stack);
                N_stack = Push(n2, N_stack);
            }
            O_stack = Pop(O_stack);
        }
        else
        {
            while (insidepriority(Top(O_stack)) >= outsidepriority(a))
            {
                n2 = execute(&O_stack, &N_stack);
                N_stack = Push(n2, N_stack);
            }
            O_stack = Push(a, O_stack);
        }
    }
    // In case all operators are in increasing order of priority:
    while (Top(O_stack) != '$')
    {
        n2 = execute(&O_stack, &N_stack);
        N_stack = Push(n2, N_stack);
    }
    printf("%d", N_stack->val);
    return 0;
}