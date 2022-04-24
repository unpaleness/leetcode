#include <iostream>
#include <vector>

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

void output(SolutionTools::TreeNode* node, const size_t level = 0, const NodeType nodeType = NodeType::Root) {
    if (!node) {
        return;
    }
    std::cerr << std::string(level, ' ') << nodeTypeToString(nodeType) << ' ' << node->value << std::endl;
    output(node->left, level + 1, NodeType::Left);
    output(node->right, level + 1, NodeType::Right);
}

int main() {
    // std::vector<int> nums = {18431, 12317, 22079, 13080, 11966, 17766, 25621, 8649, 5718, 32481, 17689, 15250, 25270, 23506, 14937, 16609, 2022};
    // std::vector<int> nums = {3, 2, 4};
    // auto* tree = new SolutionTools::Tree(nums);
    // output(tree->getRoot());
    // delete tree;

    // const auto result = Solution::twoSum({2, 7, 11, 15}, 9);
    const auto result = Solution::twoSum({3, 3}, 6);
    for (const auto it : result) {
        std::cout << ' ' << it;
    }
    std::cout << std::endl;

    return 0;
}
