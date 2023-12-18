// DecisionTreeClassifier.h

#ifndef DECISIONTREECLASSIFIER_H
#define DECISIONTREECLASSIFIER_H

#include <vector>
#include <unordered_map>

class DecisionTreeClassifier {
public:
    DecisionTreeClassifier();
    ~DecisionTreeClassifier();

    void train(const std::vector<std::vector<int>>& features, const std::vector<int>& labels);
    int predict(const std::vector<int>& sample) const;
    void visualizeTree() const;
    int findRootNode() const;

private:
    struct Node {
        int featureIndex;
        std::unordered_map<int, int> children;
        int predictedClass;
        bool isLeaf;
    };

    std::vector<Node> nodes;

    int findBestSplit(
        const std::vector<std::vector<int>>& features,
        const std::vector<int>& labels,
        const std::vector<int>& indices
    );

    int buildTree(
        const std::vector<std::vector<int>>& features,
        const std::vector<int>& labels,
        const std::vector<int>& indices
    );

    int predictTree(const std::vector<int>& sample) const;
    void visualizeNode(int nodeIndex, const std::string& prefix, bool isTail) const;
};

#endif /* DECISIONTREECLASSIFIER_H */
