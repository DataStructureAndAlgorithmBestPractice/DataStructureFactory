#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* A Flexible Linked-List Container (Currently CVAL) */
struct ContainerData
{
    char* StrData;
};

/* Linked-List Node */
struct LinkedListNode
{
    struct LinkedListNode* next;
    struct LinkedListNode* prev;
    struct ContainerData*  data;

};

/* Linked-List First Node Chosen As the representative For All List Elements */
typedef struct FirstLinkedListNode
{
    // First Node Address
    struct LinkedListNode* RootNode;
    // Last Node Address
    struct LinkedListNode* RearNode;
    // Filled Node Address
    struct LinkedListNode* FilledNode;
    // Filled Node Numbers
    size_t SizeLinkedList;
    // Linked-List Capacity
    size_t CapacityLinkedList;
    // Further Appending Size
    size_t AppendSizeLinkedList;
    // String Container Size
    size_t ContainerStrSize;

} LinkedList;

/* Allocation API For CVAL Manipulations */
struct ContainerData* CVAL2ContainerData (const char* RefChr, size_t StrCount);

/* Visualize Data Container (Currently CVAL) */
void PrintContainerData (const struct ContainerData* dt);

/* Free ContainerData Data (Currently CVAL) */
void FreeContainerData (struct ContainerData* dt);

/* Checks If LinkedList Is Empty */
bool IsEmptyLinkedList(const LinkedList* Root);

/* Constructing A Linked-List Node */
struct LinkedListNode* CreateNodeLinkedList (struct LinkedListNode* prevPtr, struct LinkedListNode* nextPtr);

/* Initiating The Linked-List */
LinkedList* CreateLinkedList (size_t LLInitialCapacity, size_t LLAppendSize, size_t LLStrSize);

/* Allocating Pool Of Memory Linked-List Elements */
LinkedList* AllocateLinkedList (size_t LLInitialCapacity, size_t LLAppendSize, size_t LLStrSize);

/* Free Single Node Linked-List Elements */
void FreeSingleNodeLinkedList (struct LinkedListNode* LL);

/* Free All Linked-List Elements */
void FreeAllNodesLinkedList (LinkedList* RLL);

/* Reallocate Linked-List Elements */
void ReAllocateLinkedList (LinkedList* RLL);

/* Set A Single Linked-List Element */
void PushValueLinkedList (LinkedList* RLL, const char* cvalstr);

/* Search For A Specific Key Inside The Linked-List, Return NULL If Not Found */
struct LinkedListNode* SearchKeyLinkedList (LinkedList* RLL, const char* cvalstr);

/* Search For A Specific Key Inside The Linked-List, Return 0 If Not Found */
bool DeleteNodeLinkList(LinkedList* RLL, const char* cvalstr);

/* Print All Linked-List Elements*/
void INFOLinkedList (const LinkedList* RLL);

/* Delete First Node Of The Linked-List */
struct LinkedListNode*  DeleteFirstNodeLinkList (LinkedList* RLL, struct LinkedListNode* FNodePtr);

/* Delete Mid Node Of The Linked-List */
struct LinkedListNode*  DeleteMidNodeLinkList (LinkedList* RLL, struct LinkedListNode* MidNodePtr);

/* Delete Rear Node Of The Linked-List */
struct LinkedListNode*  DeleteRearNodeLinkList (LinkedList* RLL, struct LinkedListNode* RearNodePtr);

/* Delete Node From Any Location Of The Linked-List, */
struct LinkedListNode* PopNodeFromAnyLocationLinkList (LinkedList* RLL, struct LinkedListNode* NodePtr);

#endif //LINKEDLIST_H
