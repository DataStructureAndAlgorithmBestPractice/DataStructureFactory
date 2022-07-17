#include <stdio.h>
#include "LinkedList.h"

int main() {

    LinkedList* vs = AllocateLinkedList(4, 4, 13);
    printf("\nEnd My Friend!\n");
    PushValueLinkedList(vs,"1234567890AB");
    PushValueLinkedList(vs,"1234567890Ab");
    PushValueLinkedList(vs,"1234567890Ac");
    PushValueLinkedList(vs,"1234567890Ad");
    PushValueLinkedList(vs,"1234567890Ae");

    printf("\nEnd My Friend!\n");
    INFOLinkedList(vs);

    PushValueLinkedList(vs,"1234567890dr");
    PushValueLinkedList(vs,"1234007890Ab");
    PushValueLinkedList(vs,"1234567890Ac");
    PushValueLinkedList(vs,"1230367890Ak");
    PushValueLinkedList(vs,"1234564440dy");

    INFOLinkedList(vs);

    printf("\nEnd My Friend!\n");

    PrintContainerData(SearchKeyLinkedList (vs, "1234567890dr")->data);

    printf("\nHello Again!\n");
    DeleteNodeLinkList(vs,"1234567890Ad");
    DeleteNodeLinkList(vs,"1234567890AB");
    DeleteNodeLinkList(vs,"1234564440dy");
    INFOLinkedList(vs);

    PrintContainerData(SearchKeyLinkedList (vs, "1234007890Ab")->data);

    FreeAllNodesLinkedList (vs);
    INFOLinkedList(vs);
    printf("\nHello!\n");
    printf("%p\n",vs->RootNode);
    printf("%p\n",vs->RearNode);
    printf("%p\n",vs->FilledNode);
    printf("%p\n",vs);

    return 0;
}
