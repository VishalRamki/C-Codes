#include <stdio.h>
#include <stdlib.h>

typedef struct stackEle {
	void *stackElement; // holds a pointer to the element
	struct stackEle *below; // below = null means the top of the stack 
} element;

typedef struct stack {
	element *stack;
	int stackSize;
} Stack;

element *createStackElement(void *ptr);
void *stackPop(Stack *stackPtr);
void stackPush(void *ptrToElement, Stack *stackPtr);


int main (int argc, char *argv[]) {
	
	Stack smallStack;
	// init
	smallStack.stack = NULL;
	smallStack.stackSize = 0;	
	
	int x = 4;
	double t = 1.0;
	
	stackPush(&x, &smallStack);
	stackPush(&t, &smallStack);
	
	double *tx = (double*)stackPop(&smallStack);
	int *y = stackPop(&smallStack);
	
	char *qq = stackPop(&smallStack);
	
	//printf("TX: %0.2f\n", *tx);
	printf("Y: %d\n", *y);
	
	return 0;
}

element *createStackElement(void *ptr) {
	element *tmp = (element*)malloc(sizeof(int)); // ptr size is either 4 or 8 bytes depending on machine
	if (tmp == NULL) {
		// I'm lazy.
		printf("Unable To Allocate.");
		return NULL;
	}
	
	tmp->stackElement = ptr;
	tmp->below = NULL;
	return tmp;
}

void stackPush(void *ptrToElement, Stack *stackPtr) {
	
	element *a = createStackElement(ptrToElement);
	
	if (stackPtr->stackSize == 0) { // empty stack, push to the top
		stackPtr->stackSize += 1;
		stackPtr->stack = a;
	} else {
		// increase stack size
		stackPtr->stackSize += 1;
		
		// save the remainder of the list
		element *tmp = stackPtr->stack;
		stackPtr->stack = a;
		// push the list below the top element a
		a->below = tmp;
	}
	
}

void *stackPop(Stack *stackPtr) {
	if (stackPtr->stackSize != 0 && stackPtr->stack != NULL) {
		
		// reduce the stackSize by one element
		stackPtr->stackSize--;
		
		// create a store funnel out the element
		element *tmp = stackPtr->stack;
		stackPtr->stack = tmp->below;
		// create a ptr holder and free element
		void *holder = tmp->stackElement;
		free(tmp);
		// return the element
		return holder;
		
	} else {
		
		// debug and error checking
		printf("STACK [%d] IS EMPTY.\n", stackPtr);
		return NULL;
	}
}
