// #include "IrisData.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "DecisionTreeClassifier.h"

int main() {
    std::ifstream file("../binarized_data.txt"); // Replace with your dataset file name
    std::vector<std::vector<int>> features;
    std::vector<int> labels;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<int> row;
            std::stringstream ss(line);
            int val;
            while (ss >> val) {
                row.push_back(val);
            }
            labels.push_back(row.back());
            row.pop_back(); // Remove label for features
            features.push_back(row);
        }
        file.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
        return 1;
    }

    // Displaying the stored data (for demonstration purposes)
    std::cout << "Features:" << std::endl;
    for (const auto& val : features) {
        std::cout << val[0] << ".." << val[8] << "|";
    }
    std::cout << std::endl;

    std::cout << "\nLabels:" << std::endl;
    for (const auto& label : labels) {
        std::cout << label << " ";
    }
    std::cout << std::endl;

    // Creating an instance of DecisionTreeClassifier
    DecisionTreeClassifier dtClassifier;

    // Training the decision tree classifier
    dtClassifier.train(features, labels);

    std::cout << "training finished";

    // Visualize the tree structure
    std::cout << "Decision Tree Structure:" << dtClassifier.findRootNode() << std::endl;
    dtClassifier.visualizeTree(); // Assuming the root node index is 0

    // Sample data for prediction
    std::vector<int> sampleToPredict0 = {0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0 }; // label is 0

    // Predicting the class for the sample
    int predictedClass = dtClassifier.predict(sampleToPredict0);

    std::cout << "Predicted class for the sample: " << predictedClass << std::endl;


    return 0;
}
