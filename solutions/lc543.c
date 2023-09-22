// get the depth of the tree that's root is `node`
int depth(struct TreeNode *node, int *maxDepth) {
    if (!node) {
        return 0;
    }

    int leftDepth = depth(node->left, maxDepth);
    int rightDepth = depth(node->right, maxDepth);
    *maxDepth = fmax(*maxDepth, leftDepth + rightDepth + 1);
    return fmax(leftDepth, rightDepth) + 1;
}

int diameterOfBinaryTree(struct TreeNode* root) {
    int ans = 1;
    (void)depth(root, &ans);
    return ans - 1;
}