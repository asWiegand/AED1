#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

int findDepth(struct TreeNode* root, int val, int parent_val, int depth) {
    if (root == NULL) {
        return -1;
    }

    if (root->val == val) {
        return depth;
    }

    int leftDepth = findDepth(root->left, val, root->val, depth + 1);
    int rightDepth = findDepth(root->right, val, root->val, depth + 1);

    if (leftDepth != -1) {
        return leftDepth;
    }
    return rightDepth;
}

bool isCousins(struct TreeNode* root, int x, int y) {
    int xDepth = findDepth(root, x, -1, 0);
    int yDepth = findDepth(root, y, -1, 0);

    if (xDepth != -1 && yDepth != -1 && xDepth == yDepth) {
        return findDepth(root, x, -1, 0) != findDepth(root, y, -1, 0);
    }

    return false;
}

int main() {
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = 1;
    root->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->val = 2;
    root->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->right->val = 3;
    root->left->left = NULL;
    root->left->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->right->val = 4;
    root->right->left = NULL;
    root->right->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->right->right->val = 5;

    root->left->right->left = NULL; // Setting the left child of node with value 4
    root->left->right->right = NULL; // Setting the right child of node with value 4
    root->right->right->left = NULL; // Setting the left child of node with value 5
    root->right->right->right = NULL; // Setting the right child of node with value 5

    int x = 4, y = 3;
    bool result = isCousins(root, x, y);
    if (result)
        printf("True.\n");
    else
        printf("False.\n");

    return 0;
}
