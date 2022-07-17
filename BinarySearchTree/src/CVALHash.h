
#ifndef TREEHASH_CVALHASH_H
#define TREEHASH_CVALHASH_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include <time.h>

    struct tree_node
    {
        char*  CVALData;
        struct tree_node *right_child;
        struct tree_node *left_child;
    };

    struct BinarySearchTree
    {
        struct tree_node* Root;
        struct tree_node* Reserved;
        size_t PoolCapacity;
        size_t FutureCapAdd;
    };

    // int To char
    char IntToChar (int i);

    // char To int
    int CharToInt (char c);

    // BST Total Summary
    void InfoBST (const struct BinarySearchTree* bst);

    // Checks Whether The Whole Tree Is Empty Or Not
    bool IsTreeEmptyBST(const struct BinarySearchTree* Bt);

    // Checks Whether A Single Tree Node Is Empty Or Not
    bool IsNodeEmptyBST(const struct tree_node* trnode);

    // Isolating The Node Pointers
    struct tree_node* IsolateSingleNodeBST (struct tree_node* trnode);

    // PreOrder Transversal
    void PreorderTransversalBST (const struct BinarySearchTree* BST);

    // Evaluete The Preorder Transversal For A SubTree
    void PreOrderSubTreeBST (const struct tree_node* trnode);

    // Create Single BST Node
    struct tree_node* CreateSingleBSTNode (const struct tree_node* lnode, const struct tree_node* rnode, const char* CVALchr);

    // Allocate Tree
    struct BinarySearchTree* AllocateBST (const size_t InitNodeCount, const size_t SubsNodeCount);

    // ReAllocate Tree
    struct BinarySearchTree* ReAllocateBST (struct BinarySearchTree* BST);

    // Get Node From Pool
    struct tree_node* PoolOutBST (struct BinarySearchTree* BST);

    // Search In Binary Tree
    struct tree_node* SearchKeyBST (const struct tree_node* root, const char* cvalkey);

    // Get Min Node Ptr
    struct tree_node* GetMinKeyBST (const struct tree_node *root);

    // Insert CVAL Key
    struct BinarySearchTree* InsertNodeBST (struct BinarySearchTree* BST, const char* cvalkey);

    // Send Node To Pool
    struct BinarySearchTree* Root2PoolBST (struct BinarySearchTree* BST, struct tree_node* removedNode);

    // Specifys Whether A Node Is Its Parents Right Child
    bool IsNodeRightChildBST (struct tree_node* trNode);

    // Specifys Whether A Node Is Its Parents Left Child
    bool IsNodeLeftChildBST (struct tree_node* trNode);

    // Specifys Whether A Node Is A Leaf
    bool IsNodeLeafBST (const struct tree_node* trNode);

    // Sending A Node To The
    struct tree_node* SearchAndsDeleteNodeBST (struct tree_node* root,  const char* cvalkey);

    // Free A Single Node From BST
    bool FreeSingleNodeBST (struct tree_node* trNode);

    // Returns True/False Whether There Is a Key Or Not
    bool IsKeyAvailableBST(const struct BinarySearchTree* BST, const char* cvalKey);

    bool DeleteSubTree (struct tree_node* trNode);

    bool DeleteAllBST (struct BinarySearchTree* BST);

    // Print Node Tree Data
    void InfoNodeBST (const struct tree_node* trNode);

    // Print Tree Data
    void InfoTreeBST (const struct BinarySearchTree* bst);

    // Print Node Tree Data
    void ReservedNodeMarching (const struct BinarySearchTree* BST);

    // CVAL RANDOM-GEN
    const char* RandomCVALGen();

#endif //TREEHASH_CVALHASH_H

