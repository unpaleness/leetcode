#include <algorithm>
#include <cstdint>
#include <format>
#include <map>
#include <unordered_map>
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
        Tree tree = Tree(nums);
        // tree.output();
        // std::cout << "from min to max\n";
        // size_t it = 0;
        // for (size_t i = min(tree); i != NPOS; i = next(i)) {
        //     const auto& node = tree[i];
        //     std::cout << node.to_string() << '\n';
        //     if (++it > 10) {
        //         break;
        //     }
        // }
        // std::cout.flush();
        // std::cout << "from max to min\n";
        // for (size_t i = max(tree); i != NPOS; i = prev(i)) {
        //     const auto& node = tree[i];
        //     std::cout << node.to_string() << '\n';
        // }
        // std::cout.flush();
        // return {};
        std::unordered_set<Tree::Result, Tree::Result::Hasher> results_set = tree.solve(target);
        std::vector<std::vector<int32_t>> results;
        results.reserve(results_set.size());
        for (const auto& r : results_set) {
            results.push_back(std::move(r.to_vector()));
        }
        return std::move(results);
    }

private:
    class Tree {
    public:
        Tree(const std::vector<int32_t>& nums) {
            if (nums.size() < 2) {
                return;
            }
            for (size_t i = 0; i < nums.size() - 1; ++i) {
                for (size_t j = i + 1; j < nums.size(); ++j) {
                    tryInsertNode(0, nums[i], nums[j], i, j);
                }
            }
            for (const auto n : nums) {
                if (values.count(n)) {
                    ++values[n];
                } else {
                    values.emplace(n, 1);
                }
            }
        }

        struct Result {
            std::map<int32_t, int32_t> values;

            Result(const std::initializer_list<int32_t>& v) {
                for (const auto val : v) {
                    if (values.count(val)) {
                        ++values[val];
                    } else {
                        values.emplace(val, 1);
                    }
                }
            }
            Result(Result&& r) { values = std::move(r.values); }
            bool operator==(const Result& r) const {
                if (values.size() != r.values.size()) {
                    return false;
                }
                for (const auto& pair : values) {
                    if (!r.values.count(pair.first)) {
                        return false;
                    }
                    if (r.values.at(pair.first) != pair.second) {
                        return false;
                    }
                }
                return true;
            }
            std::vector<int32_t> to_vector() const {
                std::vector<int32_t> result;
                result.reserve(4);
                for (const auto& pair : values) {
                    for (size_t i = 0; i < pair.second; ++i) {
                        result.push_back(pair.first);
                    }
                }
                return std::move(result);
            }
            std::string to_string() const {
                std::string res;
                for (const auto& pair : values) {
                    res += std::format("{{{}->{}}}", pair.first, pair.second);
                }
                return std::move(res);
            }

            struct Hasher {
                size_t operator()(const Result& r) const {
                    size_t seed{0};
                    for (const auto& pair : r.values) {
                        seed ^= std::hash<int32_t>{}(pair.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                        seed ^= std::hash<int32_t>{}(pair.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                    }
                    // std::cout << r.to_string() << " = " << seed << std::endl;
                    return seed;
                }
            };
        };

        struct Node {
            int32_t sum{0};
            std::vector<std::pair<int32_t, int32_t>> pairs;
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
                    pairs_str += std::format("{{{},{}}}", pair.first, pair.second);
                }
                return std::format("\033[48;5;208m{}\033[0m [{}] ({},{},{},{})", sum, pairs_str, self, parent, left,
                                   right);
            }
        };
        size_t min() const {
            const Node* node = &tree[0];
            while (node->left != NPOS) {
                node = &tree[node->left];
            }
            return node->self;
        }
        size_t max() const {
            const Node* node = &tree[0];
            while (node->right != NPOS) {
                node = &tree[node->right];
            }
            return node->self;
        }
        size_t next(const size_t index) const {
            const Node* node = &tree[index];
            // std::cout << std::format("{}: {}", __FUNCTION__, node->to_string()) << std::endl;
            const Node* prev_node = nullptr;
            while (node->right == NPOS || (prev_node && node->right == prev_node->self)) {
                // std::cout << std::format("Searching for the first parent with right for {}", node->to_string()) <<
                // std::endl;
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
                // std::cout << std::format("Searching for the first parent with left for {}", node->to_string()) <<
                // std::endl;
                node = &tree[node->left];
            }
            return node->self;
        }
        size_t prev(const size_t index) const {
            const Node* node = &tree[index];
            // std::cout << std::format("{}: {}", __FUNCTION__, node->to_string()) << std::endl;
            const Node* prev_node = nullptr;
            while (node->left == NPOS || (prev_node && node->left == prev_node->self)) {
                // std::cout << std::format("Searching for the first parent with left for {}", node->to_string()) <<
                // std::endl;
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
                // std::cout << std::format("Searching for the first parent with right for {}", node->to_string()) <<
                // std::endl;
                node = &tree[node->right];
            }
            return node->self;
        }
        bool has_enough_values(const Result& result) const {
            for (const auto& pair : result.values) {
                if (!values.count(pair.first)) {
                    return false;
                }
                if (values.at(pair.first) < pair.second) {
                    return false;
                }
            }
            return true;
        }
        void output(const size_t index = 0, const int32_t depth = 0) const {
            if (depth == 0) {
                std::cout << std::format("{}: tree:\n", __FUNCTION__);
            }
            if (index == NPOS) {
                return;
            }
            const auto& node = tree[index];
            std::cout << std::string(depth, ' ') << node.to_string() << '\n';
            output(node.left, depth + 1);
            output(node.right, depth + 1);
            if (depth == 0) {
                std::cout << std::format("{}: values:\n", __FUNCTION__);
                for (const auto& pair : values) {
                    std::cout << std::format("{} = {}\n", pair.first, pair.second);
                }
                std::cout.flush();
            }
        }
        std::unordered_set<Result, Result::Hasher> solve(const int32_t target) const {
            // std::cout << __FUNCTION__ << '\n';
            std::unordered_set<Result, Result::Hasher> results_set;
            size_t i1 = min();
            size_t i2 = max();
            while (i1 != NPOS && i2 != NPOS) {
                const auto& n1 = tree[i1];
                const auto& n2 = tree[i2];
                // std::cout << std::format("n1 = {}\nn2 = {}\n", n1.to_string(), n2.to_string());
                // match n1 + n1
                if (static_cast<int64_t>(n1.sum) == static_cast<int64_t>(target) - static_cast<int64_t>(n1.sum)) {
                    // std::cout << std::format("n1 + n1 == {}\n", static_cast<int64_t>(target));
                    for (size_t i = 0; i < n1.pairs.size(); ++i) {
                        for (size_t j = i; j < n1.pairs.size(); ++j) {
                            Result result{n1.pairs[i].first, n1.pairs[i].second, n1.pairs[j].first, n1.pairs[j].second};
                            if (!has_enough_values(result)) {
                                continue;
                            }
                            results_set.insert(std::move(result));
                        }
                    }
                    i1 = next(i1);
                    // match n2 + n2
                } else if (static_cast<int64_t>(n2.sum) == static_cast<int64_t>(target) - static_cast<int64_t>(n2.sum)) {
                    // std::cout << std::format("n2 + n2 == {}\n", static_cast<int64_t>(target));
                    for (size_t i = 0; i < n2.pairs.size(); ++i) {
                        for (size_t j = i; j < n2.pairs.size(); ++j) {
                            Result result{n2.pairs[i].first, n2.pairs[i].second, n2.pairs[j].first, n2.pairs[j].second};
                            if (!has_enough_values(result)) {
                                continue;
                            }
                            results_set.insert(std::move(result));
                        }
                    }
                    i2 = prev(i2);
                    // match n1 + n2, record all variants
                } else if (static_cast<int64_t>(n1.sum) == static_cast<int64_t>(target) - static_cast<int64_t>(n2.sum)) {
                    // std::cout << std::format("n1 + n2 == {}\n", static_cast<int64_t>(target));
                    for (size_t i = 0; i < n1.pairs.size(); ++i) {
                        for (size_t j = 0; j < n2.pairs.size(); ++j) {
                            Result result{n1.pairs[i].first, n1.pairs[i].second, n2.pairs[j].first, n2.pairs[j].second};
                            if (!has_enough_values(result)) {
                                continue;
                            }
                            results_set.insert(std::move(result));
                        }
                    }
                    i1 = next(i1);
                    i2 = prev(i2);
                } else if (static_cast<int64_t>(n1.sum) < static_cast<int64_t>(target) - static_cast<int64_t>(n2.sum)) {
                    i1 = next(i1);
                } else {
                    i2 = prev(i2);
                }
                if (static_cast<int64_t>(n1.sum) >= static_cast<int64_t>(n2.sum)) {
                    break;
                }
            }
            // std::cout.flush();
            return std::move(results_set);
        }

    private:
        void tryInsertNode(const size_t index, const int32_t v1, const int32_t v2, const int32_t i1, const int32_t i2) {
            const int32_t sum = v1 + v2;
            if (tree.empty()) {
                Node node;
                node.sum = sum;
                node.pairs = {{v1, v2}};
                node.self = index;
                tree.push_back(std::move(node));
                return;
            }
            Node& root = tree[index];
            if (root.sum == sum) {
                for (const auto& pair : root.pairs) {
                    if (pair.first == v1 || pair.second == v2) {
                        return;
                    }
                }
                root.pairs.push_back({v1, v2});
                return;
            }
            size_t& index_next_ref = sum > root.sum ? root.right : root.left;
            if (index_next_ref != NPOS) {
                tryInsertNode(index_next_ref, v1, v2, i1, i2);
            } else {
                index_next_ref = tree.size();
                Node node;
                node.sum = sum;
                node.pairs = {{v1, v2}};
                node.self = index_next_ref;
                node.parent = index;
                tree.push_back(std::move(node));
            }
        }

        std::vector<Node> tree;
        std::unordered_map<int32_t, int32_t> values;
    };
};
