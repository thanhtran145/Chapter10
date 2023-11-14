#ifndef ANIMAL_GUESSING_GAME_H
#define ANIMAL_GUESSING_GAME_H

#include <iostream>
#include <string>

using namespace std;

class TreeNode {
public:
    std::string data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::string& value);

};

class AnimalGuessingGame {
public:
    AnimalGuessingGame();
    ~AnimalGuessingGame();

    void playGame();

private:
    TreeNode* taxonomy_root_ptr;

    void playRound(TreeNode*& current);
};

#endif 

