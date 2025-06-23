#include <cstdint>
#include <format>
#include <vector>

class Solution {
public:
    static std::vector<std::vector<int32_t>> fourSum(std::vector<int32_t>& nums, int32_t target) {
        std::vector<Node> tree = createTree(nums);
        outputTree(tree);
        std::vector<std::vector<int32_t>> results;
        // for (size_t i = min(tree); i != 0xffffffffffffffff; i = next(tree, i)) {
        //     const auto& node = tree[i];
        //     std::cout << node.to_string() << '\n';
        // }
        // std::cout.flush();
        // for (size_t i = max(tree); i != 0xffffffffffffffff; i = prev(tree, i)) {
        //     const auto& node = tree[i];
        //     std::cout << node.to_string() << '\n';
        // }
        // std::cout.flush();
        size_t i1 = min(tree);
        size_t i2 = max(tree);
        while (i1 != 0xffffffffffffffff && i2 != 0xffffffffffffffff) {

        }
        return results;
    }
private:
    struct Node {
        int32_t sum { 0 };
        std::vector<std::pair<int32_t, int32_t>> pairs;
        size_t self { 0xffffffffffffffff };
        size_t parent { 0xffffffffffffffff };
        size_t left { 0xffffffffffffffff };
        size_t right { 0xffffffffffffffff };

        std::string to_string() const {
            std::string pairs_str;
            for (size_t i = 0; i < pairs.size(); ++i) {
                if (i > 0) {
                    pairs_str += ',';
                }
                const auto pair = pairs[i];
                pairs_str += std::format("{{{},{}}}", pair.first, pair.second);
            }
            // return std::format("{} [{}] ({},{},{},{})", sum, pairs_str, self, parent, left, right);
            return std::format("{} [{}]", sum, pairs_str);
        }
    };

    static std::vector<Node> createTree(const std::vector<int32_t>& nums) {
        if (nums.size() < 2) {
            return {};
        }
        std::vector<Node> tree;
        Node root;
        root.sum = 0;
        root.pairs = {{ nums[0], nums[1] }};
        root.self = 0;
        tree.push_back(std::move(root));
        for (size_t i = 0; i < nums.size() - 1; ++i) {
            for (size_t j = i + 1; j < nums.size(); ++j) {
                tryInsertNode(tree, 0, nums[i], nums[j]);
            }
        }
        return std::move(tree);
    }
    static void tryInsertNode(std::vector<Node>& tree, const size_t index, const int32_t v1, const int32_t v2) {
        const int32_t sum = v1 + v2;
        Node& root = tree[index];
        if (root.sum == sum) {
            for (const auto& pair : root.pairs) {
                if (pair.first == v1 || pair.first == v2) {
                    return;
                }
            }
            root.pairs.push_back({v1, v2});
            return;
        }
        size_t& index_next_ref = sum > root.sum ? root.right : root.left;
        if (index_next_ref != 0xffffffffffffffff) {
            tryInsertNode(tree, index_next_ref, v1, v2);
        } else {
            index_next_ref = tree.size();
            Node node;
            node.sum = sum;
            node.pairs = {{ v1, v2 }};
            node.self = index_next_ref;
            node.parent = index;
            tree.push_back(std::move(node));
        }
    }
    static size_t min(const std::vector<Node>& tree) {
        const Node* node = &tree[0];
        while (node->left != 0xffffffffffffffff) {
            node = &tree[node->left];
        }
        return node->self;
    }
    static size_t max(const std::vector<Node>& tree) {
        const Node* node = &tree[0];
        while (node->right != 0xffffffffffffffff) {
            node = &tree[node->right];
        }
        return node->self;
    }
    static size_t next(const std::vector<Node>& tree, const size_t index) {
        const Node* node = &tree[index];
        size_t index_prev = index;
        do {
            if (node->right != 0xffffffffffffffff && node->right != index_prev) {
                return node->right;
            }
            const int32_t sum { node->sum };
            index_prev = node->self;
            if (node->parent != 0xffffffffffffffff) {
                node = &tree[node->parent];
                if (node->sum > sum) {
                    return node->self;
                }
            } else {
                return 0xffffffffffffffff;
            }
        } while (true);
    }
    static size_t prev(const std::vector<Node>& tree, const size_t index) {
        const Node* node = &tree[index];
        size_t index_prev = index;
        do {
            if (node->left != 0xffffffffffffffff && node->left != index_prev) {
                return node->left;
            }
            const int32_t sum { node->sum };
            index_prev = node->self;
            if (node->parent != 0xffffffffffffffff) {
                node = &tree[node->parent];
                if (node->sum < sum) {
                    return node->self;
                }
            } else {
                return 0xffffffffffffffff;
            }
        } while (true);
    }
    static void outputTree(const std::vector<Node>& tree, const size_t index = 0, const int32_t depth = 0) {
        if (index == 0xffffffffffffffff) {
            return;
        }
        const auto& node = tree[index];
        std::cout << std::string(depth, ' ') << node.to_string() << '\n';
        outputTree(tree, node.left, depth + 1);
        outputTree(tree, node.right, depth + 1);
        if (depth == 0) {
            std::cout.flush();
        }
    }
};
