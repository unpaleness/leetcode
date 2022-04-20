#include <iostream>
#include <string>

#include "solution.h"

enum class NodeType : uint8_t {
    Root = 0,
    Left = 1,
    Right = 2,
};

static inline std::string nodeTypeToString(const NodeType nodeType) {
    switch (nodeType) {
        case NodeType::Root: return "Root";
        case NodeType::Left: return "Left";
        case NodeType::Right: return "Right";
        default: return "";
    }
}

void outputAndClean(TreeNode* node, const size_t level = 0, const NodeType nodeType = NodeType::Root) {
    if (!node) {
        return;
    }
    std::cout << std::string(level, ' ') << nodeTypeToString(nodeType) << ' ' << node->val << std::endl;
    outputAndClean(node->left, level + 1, NodeType::Left);
    outputAndClean(node->right, level + 1, NodeType::Right);
    delete node;
}

int main() {
    auto* bst = new TreeNode(INT_MIN, nullptr, new TreeNode(7, new TreeNode(3), new TreeNode(15, new TreeNode(9), new TreeNode(20))));
    auto* iterator = new BSTIterator(bst);

    std::cout << iterator->next() << std::endl;
    std::cout << iterator->next() << std::endl;
    std::cout << iterator->hasNext() << std::endl;
    std::cout << iterator->next() << std::endl;
    std::cout << iterator->hasNext() << std::endl;
    std::cout << iterator->next() << std::endl;
    std::cout << iterator->hasNext() << std::endl;
    std::cout << iterator->next() << std::endl;
    std::cout << iterator->hasNext() << std::endl;

    delete iterator;
    outputAndClean(bst);

    return 0;
}
