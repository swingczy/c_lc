/**
 * 257 binary-tree-paths
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void dfs(struct TreeNode *node, char **ans, int *ans_len, char *curr, int curr_len) {
    if (!node->left && !node->right) {
        int len = sprintf(curr + curr_len, "%d", node->val);
        ans[*ans_len] = malloc(sizeof(char) * (curr_len + len + 1));
        strcpy(ans[*ans_len], curr);
        ans[curr_len + len] = '\0';
        *ans_len += 1;
        return;
    }

    curr_len += sprintf(curr + curr_len, "%d->", node->val);
    if (node->left) {
        dfs(node->left, ans, ans_len, curr, curr_len);
    }
    if (node->right) {
        dfs(node->right, ans, ans_len, curr, curr_len);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** binaryTreePaths(struct TreeNode* root, int* returnSize){
    char *curr = malloc(sizeof(char) * 600);
    int curr_len = 0;

    char **ans = malloc(sizeof(char*) * 7);
    int ans_len = 0;

    dfs(root, ans, &ans_len, curr, curr_len);

    *returnSize = ans_len;
    return ans;
}
