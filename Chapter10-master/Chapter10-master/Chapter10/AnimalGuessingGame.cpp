#include "AnimalGuessingGame.h"

TreeNode::TreeNode(const string& value) : data(value), left(nullptr), right(nullptr) {}

AnimalGuessingGame::AnimalGuessingGame() {
    taxonomy_root_ptr = new TreeNode("Is it a mammal?");
    taxonomy_root_ptr->left = new TreeNode("Does it have stripes?");
    taxonomy_root_ptr->left->right = new TreeNode("Lion");
    taxonomy_root_ptr->left->left = new TreeNode("Zebra");
    taxonomy_root_ptr->right = new TreeNode("Is it a bird?");
    taxonomy_root_ptr->right->left = new TreeNode("Does it fly?");
    taxonomy_root_ptr->right->left->left = new TreeNode("Eagle");
    taxonomy_root_ptr->right->left->right = new TreeNode("Penguin");
    taxonomy_root_ptr->right->right = new TreeNode("Gila monster");
}

AnimalGuessingGame::~AnimalGuessingGame() {
    // Clean up memory (In a real-world application, proper memory management would be needed)
    delete taxonomy_root_ptr->left->left->left;
    delete taxonomy_root_ptr->left->left->right;
    delete taxonomy_root_ptr->left->left;
    delete taxonomy_root_ptr->left->right;
    delete taxonomy_root_ptr->left;
    delete taxonomy_root_ptr->right->left->left;
    delete taxonomy_root_ptr->right->left->right;
    delete taxonomy_root_ptr->right->left;
    delete taxonomy_root_ptr->right->right;
    delete taxonomy_root_ptr->right;
    delete taxonomy_root_ptr;
}

void AnimalGuessingGame::playRound(TreeNode*& current) {
    char response;

    // Traverse the tree until a leaf node is reached
    while (current->left != nullptr || current->right != nullptr) {
        cout << current->data << " (y/n): ";
        cin >> response;

        if (response == 'y') {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    // Make a guess
    cout << "My guess is " << current->data << ". Am I right? (y/n): ";
    cin >> response;

    if (response == 'y') {
        cout << "Yes, I knew it all along!\n";
    }
    else {
        // If the guess is wrong, learn from the user
        string newAnimal;
        cout << "I give up. What are you? ";
        cin.ignore(); // Clear newline character from previous input
        getline(std::cin, newAnimal);

        cout << "Please specify a yes/no question that distinguishes a "
            << newAnimal << " from a " << current->data << ": ";
        string newQuestion;
        getline(std::cin, newQuestion);

        cout << "As a " << newAnimal << ", does it " << newQuestion << " (y/n): ";
        cin >> response;

        // Update the taxonomy tree
        current->right = new TreeNode(newAnimal);
        current->left = new TreeNode(current->data);
        current->data = newQuestion;
        if (response == 'y') {
            swap(current->left, current->right);
        }
    }
}

void AnimalGuessingGame::playGame() {
    // Print instructions
    cout << "Welcome to the Animal Guessing Game!\n";
    cout << "Think of an animal, and I will try to guess it.\n";

    // Main game loop
    char playAgain;
    do {
        // Play one round of the game
        TreeNode* current = taxonomy_root_ptr;
        playRound(current);

        // Ask the user if they want to play again
        cout << "Shall we play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y');
}
