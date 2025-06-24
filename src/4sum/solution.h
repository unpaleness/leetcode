#include <algorithm>
#include <cstdint>
#include <format>
#include <unordered_set>
#include <vector>

#if defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__) || defined(__aarch64__) || defined(_M_X64) || \
    defined(_M_ARM64)
#define NPOS 0xffffffffffffffff
#else
#define NPOS 0xffffffff
#endif

class Solution {
public:
    static std::vector<std::vector<int32_t>> fourSum(const std::vector<int32_t>& nums, const int32_t target) {
        // std::cout << '[';
        // for (size_t i = 0; i < nums.size(); ++i) {
        //     if (i > 0) {
        //         std::cout << ',';
        //     }
        //     std::cout << nums[i];
        // }
        // std::cout << "]\n" << target << '\n';
        // std::cout.flush();
        if (nums.size() < 4) {
            return {};
        }
        std::vector<Node> tree = createTree(nums);
        // outputTree(tree);
        // std::cout << "from min to max\n";
        // size_t it = 0;
        // for (size_t i = min(tree); i != NPOS; i = next(tree, i)) {
        //     const auto& node = tree[i];
        //     std::cout << node.to_string() << '\n';
        //     if (++it > 10) {
        //         break;
        //     }
        // }
        // std::cout.flush();
        // std::cout << "from max to min\n";
        // for (size_t i = max(tree); i != NPOS; i = prev(tree, i)) {
        //     const auto& node = tree[i];
        //     std::cout << node.to_string() << '\n';
        // }
        // std::cout.flush();
        // return {};
        std::unordered_set<Result, Result::Hasher> results_set = solve(tree, target);
        std::vector<std::vector<int32_t>> results;
        results.reserve(results_set.size());
        for (auto& r : results_set) {
            results.push_back(std::move(r.values));
        }
        return std::move(results);
    }

private:
    struct Result {
        std::vector<int32_t> values;

        Result(const std::initializer_list<int32_t>& v) {
            values = v;
            std::sort(values.begin(), values.end());
        }
        Result(const Result& r) {
            values.clear();
            std::copy(r.values.begin(), r.values.end(), values.begin());
        }
        Result(Result&& r) { values = std::move(r.values); }
        bool operator==(const Result& r) const {
            if (values.size() != r.values.size()) {
                return false;
            }
            for (size_t i = 0; i < values.size(); ++i) {
                if (values[i] != r.values[i]) {
                    return false;
                }
            }
            return true;
        }

        struct Hasher {
            size_t operator()(const Result& r) const {
                size_t seed{0};
                for (const auto v : r.values) {
                    seed ^= std::hash<int32_t>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                }
                return seed;
            }
        };
    };
    struct Node {
        int32_t sum{0};
        std::vector<std::pair<int32_t, int32_t>> pairs;
        std::vector<std::pair<size_t, size_t>> indices;
        size_t self{NPOS};
        size_t parent{NPOS};
        size_t left{NPOS};
        size_t right{NPOS};

        std::string to_string() const {
            std::string pairs_str;
            for (size_t i = 0; i < pairs.size(); ++i) {
                if (i > 0) {
                    pairs_str += ',';
                }
                const auto pair = pairs[i];
                const auto index = indices[i];
                pairs_str += std::format("{{\033[38;5;208m{}\033[0m({}),\033[38;5;208m{}\033[0m({})}}", pair.first, index.first, pair.second, index.second);
            }
            // return std::format("{} [{}] ({},{},{},{})", sum, pairs_str, self, parent, left, right);
            return std::format("{} [{}] ({},{},{},{})", sum, pairs_str, self, parent, left, right);
        }
    };

    static std::vector<Node> createTree(const std::vector<int32_t>& nums) {
        if (nums.size() < 2) {
            return {};
        }
        std::vector<Node> tree;
        for (size_t i = 0; i < nums.size() - 1; ++i) {
            for (size_t j = i + 1; j < nums.size(); ++j) {
                tryInsertNode(tree, 0, nums[i], nums[j], i, j);
            }
        }
        return std::move(tree);
    }
    static void tryInsertNode(std::vector<Node>& tree,
                              const size_t index,
                              const int32_t v1,
                              const int32_t v2,
                              const int32_t i1,
                              const int32_t i2) {
        const int32_t sum = v1 + v2;
        if (tree.empty()) {
            Node node;
            node.sum = sum;
            node.pairs = {{v1, v2}};
            node.indices = {{i1, i2}};
            node.self = index;
            tree.push_back(std::move(node));
            return;
        }
        Node& root = tree[index];
        if (root.sum == sum) {
            root.pairs.push_back({v1, v2});
            root.indices.push_back({i1, i2});
            return;
        }
        size_t& index_next_ref = sum > root.sum ? root.right : root.left;
        if (index_next_ref != NPOS) {
            tryInsertNode(tree, index_next_ref, v1, v2, i1, i2);
        } else {
            index_next_ref = tree.size();
            Node node;
            node.sum = sum;
            node.pairs = {{v1, v2}};
            node.indices = {{i1, i2}};
            node.self = index_next_ref;
            node.parent = index;
            tree.push_back(std::move(node));
        }
    }
    static size_t min(const std::vector<Node>& tree) {
        const Node* node = &tree[0];
        while (node->left != NPOS) {
            node = &tree[node->left];
        }
        return node->self;
    }
    static size_t max(const std::vector<Node>& tree) {
        const Node* node = &tree[0];
        while (node->right != NPOS) {
            node = &tree[node->right];
        }
        return node->self;
    }
    static size_t next(const std::vector<Node>& tree, const size_t index) {
        const Node* node = &tree[index];
        // std::cout << std::format("{}: {}", __FUNCTION__, node->to_string()) << std::endl;
        const Node* prev_node = nullptr;
        while (node->right == NPOS || (prev_node && node->right == prev_node->self)) {
            // std::cout << std::format("Searching for the first parent with right for {}", node->to_string()) << std::endl;
            if (node->parent != NPOS) {
                prev_node = node;
                node = &tree[node->parent];
                if (node->sum > prev_node->sum) {
                    return node->self;
                }
            } else {
                return NPOS;
            }
        }
        node = &tree[node->right];
        while (node->left != NPOS) {
            // std::cout << std::format("Searching for the first parent with left for {}", node->to_string()) << std::endl;
            node = &tree[node->left];
        }
        return node->self;
    }
    static size_t prev(const std::vector<Node>& tree, const size_t index) {
        const Node* node = &tree[index];
        // std::cout << std::format("{}: {}", __FUNCTION__, node->to_string()) << std::endl;
        const Node* prev_node = nullptr;
        while (node->left == NPOS || (prev_node && node->left == prev_node->self)) {
            // std::cout << std::format("Searching for the first parent with left for {}", node->to_string()) << std::endl;
            if (node->parent != NPOS) {
                prev_node = node;
                node = &tree[node->parent];
                if (node->sum <= prev_node->sum) {
                    return node->self;
                }
            } else {
                return NPOS;
            }
        }
        node = &tree[node->left];
        while (node->right != NPOS) {
            // std::cout << std::format("Searching for the first parent with right for {}", node->to_string()) << std::endl;
            node = &tree[node->right];
        }
        return node->self;
    }
    static void outputTree(const std::vector<Node>& tree, const size_t index = 0, const int32_t depth = 0) {
        if (depth == 0) {
            std::cout << __FUNCTION__ << '\n';
        }
        if (index == NPOS) {
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
    static bool has_duplicates(const std::pair<size_t, size_t>& p1, const std::pair<size_t, size_t>& p2) {
        return p1.first == p2.first || p1.first == p2.second || p1.second == p2.first || p1.second == p2.second;
    }
    static std::unordered_set<Result, Result::Hasher> solve(const std::vector<Node>& tree, const int32_t target) {
        // std::cout << __FUNCTION__ << '\n';
        std::unordered_set<Result, Result::Hasher> results_set;
        size_t i1 = min(tree);
        size_t i2 = max(tree);
        while (i1 != NPOS && i2 != NPOS) {
            const auto& n1 = tree[i1];
            const auto& n2 = tree[i2];
            // std::cout << std::format("n1 = {}\nn2 = {}\n", n1.to_string(), n2.to_string());
            // match n1 + n1
            if (n1.sum == target - n1.sum) {
                // std::cout << std::format("n1 + n1 == {}\n", target);
                for (size_t i = 0; i < n1.pairs.size() - 1; ++i) {
                    for (size_t j = i + 1; j < n1.pairs.size(); ++j) {
                        // std::cout << std::format("checking set [{},{},{},{}]\n", n1.pairs[i].first, n1.pairs[i].second, n1.pairs[j].first, n1.pairs[j].second);
                        if (has_duplicates(n1.indices[i], n1.indices[j])) {
                            // std::cout << std::format("incides [{},{},{},{}] are not unique. skip\n", n1.indices[i].first, n1.indices[i].second, n1.indices[j].first, n1.indices[j].second);
                            continue;
                        }
                        // std::cout << std::format("adding to result\n");
                        Result result{n1.pairs[i].first, n1.pairs[i].second, n1.pairs[j].first, n1.pairs[j].second};
                        results_set.insert(std::move(result));
                    }
                }
                i1 = next(tree, i1);
                // match n2 + n2
            } else if (n2.sum == target - n2.sum) {
                // std::cout << std::format("n2 + n2 == {}\n", target);
                for (size_t i = 0; i < n2.pairs.size() - 1; ++i) {
                    for (size_t j = i + 1; j < n2.pairs.size(); ++j) {
                        // std::cout << std::format("checking set [{},{},{},{}]\n", n2.pairs[i].first, n2.pairs[i].second, n2.pairs[j].first, n2.pairs[j].second);
                        if (has_duplicates(n2.indices[i], n2.indices[j])) {
                            // std::cout << std::format("incides [{},{},{},{}] are not unique. skip\n", n2.indices[i].first, n2.indices[i].second, n2.indices[j].first, n2.indices[j].second);
                            continue;
                        }
                        // std::cout << std::format("adding to result\n");
                        Result result{n2.pairs[i].first, n2.pairs[i].second, n2.pairs[j].first, n2.pairs[j].second};
                        results_set.insert(std::move(result));
                    }
                }
                i2 = prev(tree, i2);
                // match n1 + n2, record all variants
            } else if (n1.sum == target - n2.sum) {
                // std::cout << std::format("n1 + n2 == {}\n", target);
                for (size_t i = 0; i < n1.pairs.size(); ++i) {
                    for (size_t j = 0; j < n2.pairs.size(); ++j) {
                        // std::cout << std::format("checking set [{},{},{},{}]\n", n1.pairs[i].first, n1.pairs[i].second, n2.pairs[j].first, n2.pairs[j].second);
                        if (has_duplicates(n1.indices[i], n2.indices[j])) {
                            // std::cout << std::format("incides [{},{},{},{}] are not unique. skip\n", n1.indices[i].first, n1.indices[i].second, n2.indices[j].first, n2.indices[j].second);
                            continue;
                        }
                        // std::cout << std::format("adding to result\n");
                        Result result{n1.pairs[i].first, n1.pairs[i].second, n2.pairs[j].first, n2.pairs[j].second};
                        results_set.insert(std::move(result));
                    }
                }
                i1 = next(tree, i1);
                i2 = prev(tree, i2);
            } else if (n1.sum < target - n2.sum) {
                i1 = next(tree, i1);
            } else {
                i2 = prev(tree, i2);
            }
            if (n1.sum >= n2.sum) {
                break;
            }
        }
        // std::cout.flush();
        return std::move(results_set);
    }
};
