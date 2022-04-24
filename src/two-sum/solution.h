#include <iostream>
#include <vector>

namespace SolutionTools {

struct TreeNode {
    int index{0};
    int value{0};
    TreeNode *left{nullptr};
    TreeNode *right{nullptr};
    TreeNode() : index(0), value(0), left(nullptr), right(nullptr) {
        // std::cerr << __PRETTY_FUNCTION__ << ": index = " << index << ", value = " << value << std::endl;
    }
    TreeNode(const int newIndex, const int newValue) : index(newIndex), value(newValue), left(nullptr), right(nullptr) {
        // std::cerr << __PRETTY_FUNCTION__ << ": index = " << index << ", value = " << value << std::endl;
    }
    ~TreeNode() {
        // std::cerr << __PRETTY_FUNCTION__ << ": index = " << index << ", value = " << value << std::endl;
    }
};

class Tree {
public:
    Tree() {}
    Tree(const std::vector<int>& nums) {
        // std::cerr << __PRETTY_FUNCTION__ << std::endl;
        createNodes(nums);
    }
    ~Tree() {
        // std::cerr << __PRETTY_FUNCTION__ << std::endl;
        cleanNodes();
    }
    TreeNode* getRoot() const { return root; }
    TreeNode* getNodeByValue(const int value) const {
        auto* node = root;
        while (node) {
            if (node->value == value) {
                return node;
            }
            node = value < node->value ? node->left : node->right;
        }
        return nullptr;
    }
private:
    TreeNode* root{nullptr};

    void createNodes(const std::vector<int>& nums) {

        if (!nums.empty()) {
            root = new TreeNode(0, nums[0]);
        }
        for (size_t i = 1; i < nums.size(); ++i) {
            auto* node = root;
            while (true) {
                if (nums[i] < node->value) {
                    if (!node->left) {
                        node->left = new TreeNode(i, nums[i]);
                        break;
                    }
                    node = node->left;
                } else {
                    if (!node->right) {
                        node->right = new TreeNode(i, nums[i]);
                        break;
                    }
                    node = node->right;
                }
            }
        }
    }

    void cleanNodes() {
        cleanNode(root);
    }

    void cleanNode(TreeNode* node) {
        if (!node) {
            return;
        }
        cleanNode(node->left);
        cleanNode(node->right);
        delete node;
    }
};

}

class Solution {
public:
    static std::vector<int> twoSum(const std::vector<int>& nums, const int target) {
        SolutionTools::Tree tree(nums);

        for (size_t i = 0; i < nums.size(); ++i) {
            const auto* node = tree.getNodeByValue(target - nums[i]);
            if (node && node->index != static_cast<int>(i)) {
                return {static_cast<int>(i), node->index};
            }
        }

        return {};
    }
};
