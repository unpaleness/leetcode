#include <limits>

#include "treenode.h"

class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        currentValue = INT_MIN;
        rootNode = root;
    }

    int next() {
        return next(true);
    }

    bool hasNext() {
        return next(false) != INT_MAX;
    }

private:
    int currentValue = INT_MIN;
    TreeNode* rootNode = nullptr;

    int next(const bool isMutable) {
        int result = INT_MAX;
        TreeNode* currentNode = rootNode;
        while (currentNode) {
            if (currentNode->val < result && currentNode->val > currentValue) {
                result = currentNode->val;
            }
            if (currentValue < currentNode->val && currentNode->left) {
                currentNode = currentNode->left;
            } else if (currentNode->right) {
                currentNode = currentNode->right;
            } else {
                currentNode = nullptr;
            }
        }
        if (isMutable) {
            currentValue = result;
        }
        return result;
    }
};
