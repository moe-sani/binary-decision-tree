# Decision Tree Classifier

This C++ implementation demonstrates a basic Decision Tree Classifier used for classification tasks. It constructs a decision tree based on provided features and labels and makes predictions on new instances.

## Overview

The decision tree classifier consists of:

- **DecisionTreeClassifier.h**: Header file containing the declaration of the DecisionTreeClassifier class.
- **DecisionTreeClassifier.cpp**: Implementation file containing the methods of the DecisionTreeClassifier class.
- **Main.cpp**: An example usage demonstrating how to train the classifier and make predictions.
- **binarized_data.cpp**: An example binary dataset classifying features into 3 categories. 

The data format is as follows:
    • F = Feature
    • C = Class

F F F F F F F F F F F F F F F F C

0 0 1 1 0 0 0 1 0 0 1 0 0 0 0 0 1
0 1 0 0 0 0 0 1 0 1 0 0 0 0 0 1 2
0 1 0 0 0 0 1 0 0 0 1 1 0 0 0 1 2
0 0 1 1 0 0 1 0 0 0 0 1 0 0 0 0 0


## Features

- Constructs a decision tree based on features and labels.
- Uses information gain to select the best feature for node splitting.
- Predicts the class of new instances based on the trained decision tree.
- Provides visualization of the decision tree structure.

## Usage

### Training the Classifier

To train the classifier, provide the feature vectors and corresponding labels. Use the `train()` method to build the decision tree.

```cpp
// Sample data for training
std::vector<std::vector<int>> trainingFeatures = { /* Your training features here */ };
std::vector<int> trainingLabels = { /* Your training labels here */ };

// Creating an instance of DecisionTreeClassifier
DecisionTreeClassifier dtClassifier;

// Training the decision tree classifier
dtClassifier.train(trainingFeatures, trainingLabels);

```

### Making Predictions
Use the predict() or predictTree() method to predict the class of a new instance.

```cpp
// Sample data for prediction
std::vector<int> sampleToPredict = { /* Features of the sample to predict */ };

// Predicting the class for the sample
int predictedClass = dtClassifier.predict(sampleToPredict);

std::cout << "Predicted class for the sample: " << predictedClass << std::endl;
```

### Visualizing the Tree
You can visualize the decision tree structure using the visualizeTree() method.

```cpp
dtClassifier.visualizeTree();
```

## How to Run
Clone the repository.
Compile the code using a C++ compiler.
Run the compiled executable.

sample output:
```
training finishedDecision Tree Structure:24
Decision Tree Visualization: Nodes:25
├── F? 10
│   ├── F? 11
│   │   ├── F? 15
│   │   │   ├── Leaf Label: 1
│   │   │   └── F? 6
│   │   │       ├── Leaf Label: 1
│   │   │       └── Leaf Label: 2
│   │   └── F? 15
│   │       ├── F? 1
│   │       │   ├── F? 6
│   │       │   │   ├── Leaf Label: 2
│   │       │   │   └── Leaf Label: 2
│   │       │   └── F? 6
│   │       │       ├── Leaf Label: 2
│   │       │       └── Leaf Label: 2
│   │       └── F? 1
│   │           ├── Leaf Label: 2
│   │           └── Leaf Label: 1
│   └── F? 1
│       ├── Leaf Label: 2
│       └── F? 6
│           ├── Leaf Label: 0
│           └── F? 11
│               ├── Leaf Label: 0
│               └── Leaf Label: 0

Predicted class for the sample: 1
```

## Contributors
[Moe Sani](https://github.com/moe-sani)
## License
This project is licensed under the MIT License.
