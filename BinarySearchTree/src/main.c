#include <stdio.h>
#include "CVALHash.h"
int main() {

    printf("Hello, BST!\n");

    struct BinarySearchTree* masTree
            = AllocateBST( 10, 5);

    InsertNodeBST(masTree, "P");
    InsertNodeBST(masTree, "C");
    InsertNodeBST(masTree, "V");
    InsertNodeBST(masTree, "I");
    InsertNodeBST(masTree, "B");

    InsertNodeBST(masTree, "A");
    InsertNodeBST(masTree, "L");
    InsertNodeBST(masTree, "Z");
    InsertNodeBST(masTree, "K");
    InsertNodeBST(masTree, "T");

    InsertNodeBST(masTree, "D");
    InsertNodeBST(masTree, "E");

    InfoTreeBST (masTree);
//
    printf("%i\n", IsKeyAvailableBST(masTree, "I"));
//
    printf("\n--------------BEFORE DELETION (Single Node) --------------\n");
    printf("%i\n", IsKeyAvailableBST(masTree, "A"));
    InfoNodeBST(SearchKeyBST(masTree->Root, "A"));

    printf("\n--------------AFTER DELETION (Single Node)--------------\n");
    SearchAndsDeleteNodeBST (masTree->Root, "A");
    printf("%i\n", IsKeyAvailableBST(masTree, "A"));
    InfoNodeBST(SearchKeyBST(masTree->Root, "A"));
    InfoTreeBST (masTree);

    printf("\n--------------AFTER DELETION (All Nodes)--------------\n");
    DeleteAllBST(masTree);

    InfoTreeBST (masTree);


    /*
    //printf("%i", 'A'<'B');
    srand(time(NULL));
    char** charTable = (char**) calloc(600, sizeof (char*));

    for (int i = 0; i < 600; ++i) {
        charTable[i] = (char*) RandomCVALGen();
        printf("%s\n", charTable[i]);
    }

    */

    return 0;
}

