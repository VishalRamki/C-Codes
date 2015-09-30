# Generic Stack(s) && Author Info

Code: Generic Stacks

Author: VishalRamki

CurrentVersion: 1.1

Anyhow, yeah so this is a generic stack function/structure for you to make use of. Basically you can push any type of
data, ints, doubles, chars etc. And pop it back out using a pointer. It behaves like a stack. It is a minimal version of
a stack, no other features or stuff. Not sure what else you can add but sure. 

# Why?

Donno. I wanted to I guess.

Kinda wanted to see if I could write it, and I managed to write it some how. It certainly could use improvements
here and there, so thread carefully.

# Usage

Here's how to push ANY variable onto the stack. Since this implementation of Generic Stacks make heavy use of pointers,
you'll need to pass the the pointer to the variable, rather than just the variable.

```c
stackPush(&x, &smallStack); // assuming that smallStack is not declared as a pointer
```

Here's how to pop back out the variables. You can only pop it back into a pointer variable. Currently you just need to
remember what you pushed on the stack and what order. I'll update the code if I can figure out how to do it 
automatically. But for now, you have to remember extactly whats in your stack.

```c
double *tx = (double*)stackPop(&smallStack);
int *y = stackPop(&smallStack);
```

# Current Limitations:
While any VAR can be placed on the stack, only 4 variables have 
debug information assoicated with them. these are: INT, DOUBLE,
CHAR and FLOAT.
 		
The others will be added in time.
 		
# TODO
I haven't tested the stack with arrays. I would like to.
 
# ChangeLog:

[29.09.15]
- Actually ended up doing nothing. Glory.
[30.09.15]
- Added a peekAtTop [getTop()] function to the stack.
- Two typedef structs  created.
  - TYPE_INFO - Holds the variable type information. (enum)
 	- Metadata - holds all related data for the element in the stack.
- Added 3 new functions as well as an enumator to keep track of the type of variables stored with in the stack.
  - getData(), printMeta(), printType()
