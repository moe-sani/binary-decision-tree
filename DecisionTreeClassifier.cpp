#include "DecisionTreeClassifier.h"
#include <cmath>
#include <algorithm>
#include <limits>
#include <iostream>

DecisionTreeClassifier::DecisionTreeClassifier() {
    // Constructor
}

DecisionTreeClassifier::~DecisionTreeClassifier() {
    // Destructor
}

void DecisionTreeClassifier::train(
    const std::vector<std::vector<int>>& features,
    const std::vector<int>& labels
) {
    std::vector<int> indices(features.size());
    for (size_t i = 0; i < indices.size(); ++i) {
        indices[i] = static_cast<int>(i);
    }
    std::cout << "Building a Tree with features:" << features.size() << " X " << features[0].size() << std::endl;
    for(auto n : features)
    {
        for (auto m : n)
        {
            std::cout << m;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    buildTree(features, labels, indices);
}

/*
recursively building the decision tree by splitting nodes based on features that provide the best information gain
features: The entire set of feature vectors.
labels: The corresponding labels for the features.
indices: The indices of the instances (rows) to consider at the current node.

returns: the index of the node it creates in the nodes vector.
*/
int DecisionTreeClassifier::buildTree(
    const std::vector<std::vector<int>>& features,
    const std::vector<int>& labels,
    const std::vector<int>& indices
) {
    if (indices.empty()) {
        return -1; // Empty node
        std::cout << " Empty Node!" << std::endl;
    }
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Building a Tree with indices size of :" << indices.size() << std::endl;
    for(auto n : indices)
    {
        std::cout << n << ":";
        for( auto f : features[n]){
        std::cout << f << " ";
        }
        std::cout << ">" << labels[n] << std::endl;
    }
    std::cout << std::endl;
    Node node;
    node.isLeaf = false;

    // Check if all labels are the same
    int firstLabel = labels[indices[0]];
    bool sameLabel = true;
    for (size_t i = 1; i < indices.size(); ++i) {
        if (labels[indices[i]] != firstLabel) {
            sameLabel = false;
            break;
        }
    }

    if (sameLabel) {
        std::cout << "All labels are the same!" << std::endl;
        node.isLeaf = true;
        node.predictedClass = firstLabel;
        nodes.push_back(node);
        return static_cast<int>(nodes.size()) - 1;
    }

    int bestFeature = findBestSplit(features, labels, indices);
    if (bestFeature == -1) {
        node.isLeaf = true;
        // Determine majority class as the predicted class
        node.predictedClass = labels[indices[0]];
        nodes.push_back(node);
        return static_cast<int>(nodes.size()) - 1;
    }

    node.featureIndex = bestFeature;
    std::unordered_map<int, std::vector<int>> splits;
    for (const auto& index : indices) {
        // creates groups or "splits" where instances sharing the same feature value are grouped together
        splits[features[index][bestFeature]].push_back(index);
    }

    for (const auto& split : splits) {
        node.children[split.first] = buildTree(features, labels, split.second);
    }
    nodes.push_back(node);
    return static_cast<int>(nodes.size()) - 1;
}
// This function calculates the information gain for each feature and selects the one that maximizes the gain. It uses entropy calculations to estimate the purity of subsets generated by splitting the data based on different features. The feature that results in the highest information gain (reduction in entropy) is chosen for splitting the tree node.
int DecisionTreeClassifier::findBestSplit(
    const std::vector<std::vector<int>>& features,
    const std::vector<int>& labels,
    const std::vector<int>& indices
) {
    int numFeatures = features[0].size();
    int numInstances = indices.size();
    // std::cout << ">> findBestSplit: numFeatures:" << numFeatures << "numInstances" << numInstances << std::endl ;

    double bestGain = 0;
    int bestFeature = -1;

    // Calculate the entropy of the current set of instances
    std::unordered_map<int, int> classCounts;
    for (const auto& index : indices) {
        classCounts[labels[index]]++;
    }

    double entropy = 0.0;
    for (const auto& kv : classCounts) {
        double probability = static_cast<double>(kv.second) / numInstances;
        entropy -= probability * log2(probability);
    }

    for (int feature = 0; feature < numFeatures; ++feature) {
        std::unordered_map<int, std::vector<int>> featureValues;
        for (const auto& index : indices) {
            featureValues[features[index][feature]].push_back(index);
        }

        double featureEntropy = 0.0;
        for (const auto& value : featureValues) {
            double valueEntropy = 0.0;
            std::unordered_map<int, int> valueCounts;

            for (const auto& index : value.second) {
                valueCounts[labels[index]]++;
            }

            for (const auto& kv : valueCounts) {
                double probability = static_cast<double>(kv.second) / value.second.size();
                valueEntropy -= probability * log2(probability);
            }

            double valueWeight = static_cast<double>(value.second.size()) / numInstances;
            featureEntropy += valueWeight * valueEntropy;
        }
        double gain = entropy - featureEntropy;
        std::cout << ">>, feature:" << feature << ", gain:" << gain;
        if (gain > bestGain) {
            bestGain = gain;
            bestFeature = feature;
        }
    }
    std::cout << ">> findBestSplit: bestFeature:" << bestFeature << std::endl ;

    return bestFeature;
}


int DecisionTreeClassifier::predict(const std::vector<int>& sample) const {
    return predictTree(sample);
}

int DecisionTreeClassifier::predictTree(const std::vector<int>& sample) const {
    int currentNode = findRootNode(); // Start at the root
    //Traversal through the Tree
    while (!nodes[currentNode].isLeaf) {
        //Finding the Appropriate Child Node
        int featureValue = sample[nodes[currentNode].featureIndex];
        auto it = nodes[currentNode].children.find(featureValue);
        if (it != nodes[currentNode].children.end()) {
            currentNode = it->second;
        } else {
            // If the feature value is not found in the tree, return a default prediction
            std::cerr << "Unknown feature value encountered." << std::endl;
            return nodes[currentNode].predictedClass;
        }
    }
    return nodes[currentNode].predictedClass;
}


void DecisionTreeClassifier::visualizeTree() const {
    std::cout << "Decision Tree Visualization: Nodes:" << nodes.size() << std::endl;
    visualizeNode(findRootNode(),"", false);
}

void DecisionTreeClassifier::visualizeNode(int nodeIndex, const std::string& prefix, bool isTail) const {
    const Node& node = nodes[nodeIndex];

    std::cout << prefix << (isTail ? "└── " : "├── ");

    if (node.isLeaf) {
        std::cout << "Leaf Label: " << node.predictedClass << std::endl;
        return;
    } else {
        std::cout << "F? " << node.featureIndex << std::endl;
    }

    std::string childPrefix = prefix + (isTail ? "    " : "│   ");

    auto it = node.children.begin();
    while (it != node.children.end()) {
        bool isLastChild = std::next(it) == node.children.end();
        visualizeNode(it->second, childPrefix, isLastChild);
        ++it;
    }
}

int DecisionTreeClassifier::findRootNode() const {
    std::vector<bool> isChild(nodes.size(), false);

    // Mark nodes that are children
    for (const auto& node : nodes) {
        for (const auto& child : node.children) {
            isChild[child.second] = true;
        }
    }

    // Find the node that is not a child
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (!isChild[i]) {
            return static_cast<int>(i);
        }
    }

    return -1; // No root node found
}