typedef void *Void;
struct StackNode{
	  Void  ele ;
      struct StackNode *next;
};
typedef  struct StackNode NodeClass;
typedef  NodeClass *Node;

struct StackStruct{
    Node n;
    int top;
};
typedef struct StackStruct StackClass;
typedef StackClass *Stack;

Stack createStack();
int isEmpty(Stack s);
int sizeS(Stack s);
Stack push (Stack s ,Void ele);
Void pop(Stack s );
Void peek(Stack s );
void freeStack(Stack s);


