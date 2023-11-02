// empty tree's height is 0
int getTreeHeight(struct TreeNode *root);

// root's idx is 1
bool nodeExist(struct TreeNode *root, const int height, const int nodeIdx);

int countNodes(struct TreeNode* root){
    const int treeHeight = getTreeHeight(root);
    if (treeHeight == 0) { // empty
        return 0;
    }

    // A tree with height `h`(h>0), it's total number of node is between [ 2^(h-1), 2^h - 1]
    int minNodes = pow(2, treeHeight - 1);
    int maxNodes = pow(2, treeHeight) - 1;

    while (minNodes < maxNodes) {
        int midNode = minNodes + (maxNodes - minNodes + 1) / 2; // right child first
        if (nodeExist(root, treeHeight, midNode)) {
            // if exist，N >= midNode, else, N < midNode
            minNodes = midNode;
        } else {
            maxNodes = midNode - 1;
        }
    }

    return minNodes;
}

int getTreeHeight(struct TreeNode *root) {
    int height = 0;
    while (root) {
        height++;
        root = root->left;
    }
    return height;
}

bool nodeExist(struct TreeNode *root, const int height, const int node) {
    // represent node in binary, in the path from `root` to `node`, go left: 0; go right: 1

    int bit = 1 << (height - 2); // node in level `height`, it needs `height` bits, the heighest bit need no judge
    struct TreeNode *p = root;
    while (p && bit > 0) { // get the bit from high to low
        if ((bit & node) != 0) {
            p = p->right;
        } else {
            p = p->left;
        }

        bit >>= 1;
    }

    return p != NULL;
}
