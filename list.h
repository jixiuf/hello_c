typedef void* Void;
struct ListStructNode{
	Void ele;
	struct ListStructNode *next;
};
typedef struct ListStructNode ListNodeClass;
typedef  ListNodeClass *ListNode;

struct ListStruct{
	int size;
	ListNode nodes;
};
typedef struct ListStruct ListClass;
typedef ListClass *List;
List list_create();
void list_merge_at(List headList ,int index ,List tailList);
void list_append(List headList, List tailList);
void list_delete_at(List list ,int index);
void list_delete_last(List list );
void list_inverse (List list );
void list_add_at (List list ,Void ele,int index );
void list_add (List list ,Void ele );
void list_modify_at (List list ,Void ele ,int index );
 int list_sizeOf(List list);

Void list_get_at(List list,int index);
Void list_get_last(List list);
void list_free(List list);
void list_swap(List list ,int x ,int y);
