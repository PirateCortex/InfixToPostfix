#include <stdio.h>
#include <ctype.h>
#include<stdlib.h>

typedef struct {    
    char   ch;      
    int   num;   
    
} StackData;

// typedef struct
// {
//   char ch;
// } StackData;

typedef struct node {    
    StackData   data;      
    struct   node   *next;   
} Node, *NodePtr; 

typedef struct stackType {    
    NodePtr   top;   
} 
StackType, *Stack;

Stack initStack() {    
    Stack sp = (Stack) 
    malloc(sizeof(StackType));    
    sp -> top = NULL;    
    return   sp;   
}

int empty(Stack S) {    
    return (S -> top == NULL); 
}

void push(Stack S, StackData d) {    
    NodePtr np = (NodePtr) malloc(sizeof(Node));    
    np -> data = d;    
    np -> next = S -> top;    
    S -> top = np; 
}

StackData pop(Stack S) {    
    if (empty(S)) {       
        printf("\nAttempt to pop an empty stack\n");       
        exit(1);      
    }      
    
    StackData hold = S -> top -> data;    
    NodePtr temp = S -> top;    
    S -> top = S -> top -> next;    
    free(temp);      
    return   hold;   
}

StackData peek(Stack S) {    
    if (!empty(S)) return S -> top -> data; 
} 

int main ()
{
  int readConvert (char[]);

  void printPostfix (char[], int);
  char post[50];
  int n = readConvert (post);
  printPostfix (post, n);
  
  printf("\n\nThe evaluation is: \n%d", eval(post, n));
  
  return 0;
}

int readConvert(char post[]) {    
    char getToken(void), token, c;    
    int   precedence(char);      
    StackData   temp;      
    int j = 0;    
    Stack S = initStack();
    printf("Type an infix expression and press Enter\n");    
    token = getToken();    
    while (token != '\n') {       
        if   (isdigit(token)) post[j++] = token; 
        else if(token == '^') {
            temp.ch = token;
            push(S, temp);
        }
        else if (token == '(') {          
            temp.ch   =   token;            
            push(S,   temp);     
        }
        else if (token == ')')          
        while ((c = pop(S).ch) != '(') 
        post[j++] = c;   
        else {          
            while (!empty(S) && precedence(peek(S).ch)   >=   precedence(token))       
            post[j++] = pop(S).ch;          
            temp.ch   =   token;            
            push(S,   temp);     }       
            token   =   getToken();      
    }      
    while (!empty(S)) 
    post[j++] = pop(S).ch;    
    return j;  
}

void printPostfix(char post[], int n) {    
    int   j;
    
    printf("\nThe postfix form is \n");  
    
    for (j = 0; j < n; j++) {
        printf("%c ", post[j]);    
    }
}

char getToken() {    
    char   ch;      
    while ((ch = getchar()) == ' ');
    return ch;
}

int precedence(char c) {    
    if (c == '(') return 0;    
    if (c == '+' || c == '-') return 3;    
    if (c == '*' || c == '/') return 5;
    if(c == '^') return 7;
}

int eval(char post[], int n) {    
    
    int j, a, b, c;    
    
    StackData   temp;      
    Stack S = initStack();
    
    for (j = 0; j < n; j++) {       
        if   (isdigit(post[j]))   {            
            temp.num   =   post[j]   -   '0'; 
            push(S,   temp);     
            
        }   
        else {          
            b   =   pop(S).num;            
            a   =   pop(S).num;            
            if (post[j] == '+') c = a + b;          
            else if (post[j] == '-') c = a - b;          
            else if (post[j] == '*') c = a * b;
            else if (post[j] == '^') {
                c = 1;
                for(int i = 0; i < b; i++) {
                    
                    c *= a;
                }
            }
            else c = a / b;    
            temp.num = c;          
            push(S,   temp);     
                
        }    
    } 
    
    return   pop(S).num; 
        
    }
    
