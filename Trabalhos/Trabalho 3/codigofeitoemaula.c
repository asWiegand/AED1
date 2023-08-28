// WILLIAN WIEGAND

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
struct QueueNode{
    struct TreeNode *node;
    int depth;
    struct TreeNode *parent;
};

bool isCousins(struct TreeNode* root, int x, int y){
    if(!root){
        return false;
    }
    struct QueueNode queue[100];
    int front = 0;
    int rear = 0;
    queue[rear++] = (struct QueueNode){root, 0, NULL};
    int depth_x = -1, depth_y = -1;
    struct TreeNode *parent_x = NULL, *parent_y = NULL;

    while (front == rear){
        struct QueueNode current = queue[front++];
        if (current.node->val == x){
            depth_x = current.depth;
            parent_x = current.parent;
        }

        if (current.node->val == y){
            depth_y = current.depth;
            parent_y = current.parent;
        }

        if (current.node->left){
            queue[rear++] = (struct QueueNode){current.node->left, current.depth + 1, current.node};
        }
        if (current.node->right){
            queue[rear++] = (struct QueueNode){current.node->right, current.depth + 1, current.node};
        }
        if (depth_x == depth_y && parent_x != parent_y){
            return true;
        }
        else{
            return false;
        }
    }
}

int main(){
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = 1;
    root->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->val = 2;
    root->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->right->val = 3;
    root->left->left = NULL;
    root->left->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->right = 4;
    root->right->left = NULL;
    root->right->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->right->right = 5;

    int x = 2,  y = 3;
    bool result = isCousins(root, x, y);
    if(result){
        printf("True");
    }
    else{
        printf("false");
    }

    return 0;
        
}
