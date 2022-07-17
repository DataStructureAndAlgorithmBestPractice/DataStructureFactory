#pragma once

struct BSTNode
{
	struct BSTNode* right;
	struct BSTNode* left;
	struct BSTNode* parent;
	char CVALSS[12];
};

struct BST
{
	struct BSTNode* root;
};
