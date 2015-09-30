
typedef enum {
	INT, CHAR, DOUBLE, FLOAT
} TYPE_INFO;


typedef struct {
	TYPE_INFO elementType;
} Metadata;

typedef struct stackEle {
	void *stackElement; // holds a pointer to the element
	Metadata *elementMeta; // holds the metadata relating to the stackElement
	struct stackEle *below; // below = null means the top of the stack 
} element;

typedef struct stack {
	element *stack;
	int stackSize;
} Stack;

element *createStackElement(void *ptr, TYPE_INFO _type);
void *stackPop(Stack *stackPtr);
void stackPush(void *ptrToElement, TYPE_INFO _type, Stack *stackPtr);

void *getTop(Stack *stackPtr);
Metadata *getData(element *ptrToElement);
void printMeta(Metadata *md);
char *printType(TYPE_INFO _t);


int main (int argc, char *argv[]) {
	
	Stack smallStack;
	// init
	smallStack.stack = NULL;
	smallStack.stackSize = 0;	
	
	int x = 4;
	double t = 1.0;
	
	stackPush(&x, INT, &smallStack);
	stackPush(&t, DOUBLE, &smallStack);
	
	printf("Before popping the first element, we check the top and print the metadata:\n");
	printMeta(getData(getTop(&smallStack)));
	printf("\n");
	
	printf("We pop The First Element.\n");
	double *tx = (double*)stackPop(&smallStack);
	
	printf("Now we get data for the new top.\n");
	printMeta(getData(getTop(&smallStack)));
	printf("\n");
	printf("We Pop That.\n");
	int *y = stackPop(&smallStack);
	
	printf("Now we Basically Just to a quick if empty test.\n");
	char *qq = stackPop(&smallStack);
	
	printf("TX: %0.2f\n", *tx);
	printf("Y: %d\n", *y);
	
	return 0;
}

element *createStackElement(void *ptr, TYPE_INFO _type) {
	element *tmp = (element*)malloc(sizeof(int)); // ptr size is either 4 or 8 bytes depending on machine
	if (tmp == NULL) {
		// I'm lazy.
		printf("Unable To Allocate.");
		return NULL;
	}
	
	tmp->stackElement = ptr;
	tmp->elementMeta = (Metadata*)malloc(sizeof(Metadata));
	
	// some error checking for memory (this is a force of habit btw.)
	if (tmp->elementMeta == NULL) {
		printf("Metadata cannot be created in Stack Element @%p\n", tmp);
	} else {
		// Insert all metadata here.
		tmp->elementMeta->elementType = _type;
	}
		
	tmp->below = NULL;
	return tmp;
}

void stackPush(void *ptrToElement, TYPE_INFO _type, Stack *stackPtr) {
	
	element *a = createStackElement(ptrToElement, _type);
	
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
		printf("STACK [@%p] IS EMPTY.\n", stackPtr);
		return NULL;
	}
}

void *getTop(Stack *stackPtr) {
	if (stackPtr == NULL || stackPtr->stackSize == 0) return NULL;
	return stackPtr->stack; // stack is the top of the list anyway;
}

Metadata *getData(element *ptrToElement) {
	// Function returns a copy of the meta associated with
	// the element found in the 'ptrToElement'.
	
	if (ptrToElement == NULL) {
		return NULL;
	}
	
	return ptrToElement->elementMeta;
	
}

void printMeta(Metadata *md) {
	if (md == NULL) {
		printf("Metadata is NULL. No Data can be printed.\n");
	}
	
	printf("Metadata located @%p\n", md);
	printf("Type of Data: %s\n", printType(md->elementType));
}

char *printType(TYPE_INFO _t) {
	switch (_t) {
		case INT:
			return "Integer";
		case CHAR:
			return "Char";
		case DOUBLE:
			return "Double";
		case FLOAT:
			return "Float";
		default:
			return "No Type Assoication";
	}
}
