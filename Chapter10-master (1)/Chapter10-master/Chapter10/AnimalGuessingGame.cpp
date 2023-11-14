#include "AnimalGuessingGame.h"

//precondition: going to call the default constructor class
//postcondition: going to then initialize the privates 
AnimalGuessingGame::AnimalGuessingGame() : question(""), left(NULL), right(NULL), root(NULL) {}

//precondition: going to call the constructor class
//postcondition: going to then initialize the privates and data will now have newData
AnimalGuessingGame::AnimalGuessingGame(const string& newQuestion) :question(newQuestion), left(NULL), right(NULL), root(NULL) {}


//precondition: going to call the tree that will hold the information
//postcondition: going to then call the root that hold the nodes, going to set the root, left subtree, and then right subtree
void AnimalGuessingGame::theTree() {
    //the root
    root = new AnimalGuessingGame("Is it a mammal?");
    //left subtree
    root->left = new AnimalGuessingGame("Does it have stripes?");
    root->left->left = new AnimalGuessingGame("Zebra");
    root->left->right = new AnimalGuessingGame("Lion");
    //right subtree
    root->right = new AnimalGuessingGame("Is it a bird?");
    root->right->left = new AnimalGuessingGame("Does it fly?");
    root->right->left->left = new AnimalGuessingGame("Eagle");
    root->right->left->right = new AnimalGuessingGame("Penguin");
    root->right->right = new AnimalGuessingGame("Gila monster");
}

//precondition: going to call the animal guessing game
//postcondition: going to then call the recursive function deleteEntireTree() and pass in the root and then set it to NULL
AnimalGuessingGame::~AnimalGuessingGame() {
    //deallocate the memory
    delete(root);
    //make sure the root is set to null to show that there are no more nodes or else it will have garbage data
    root = NULL;
}
//precondition: going to pass in the animal guessing class class
//postcondition: going to then delete the node (deallocate the nodes so memory does not leak)
void AnimalGuessingGame::deleteEntireTree(AnimalGuessingGame* node) {
    if (node == NULL) {
        return;
    }
    //first delete the left subtree 
    deleteEntireTree(node->left);
    //then delete the right subtree
    deleteEntireTree(node->right);

    //delete the current node
    delete node;
}

//precondition: going to pass in the class that is a node as an argument
//postcondition:
void AnimalGuessingGame::playGame(AnimalGuessingGame* node) 
{
    while (node->left && node->right) 
    {
        //call the nodes, and ask the questions
        char choice = inputChar("\n\t" + node->question + " (Y-yes/no): ", static_cast<string>("YN)"));

        //if yes then go to the left subtree
        if (toupper(choice) == 'Y') 
        {
            node = node->left;
        }
        //if no then go to the right subtree
        else if (toupper(choice) == 'N') {
            node = node->right;
        }
    }

    char choice2 = inputChar("\n\tMy guess is " + node->question + ". Am i right (Y-yes/N-no): ", static_cast<string>("YN"));

    if (toupper(choice2) == 'Y')
    {
        cout << "\n\tYes, I knew it all along!\n\n";
    }
    else {
        // If the guess is wrong, learn from the user
        
        string newAnimal = inputString("\n\tI give up. What are you ? ", false);

        string newQuestion = inputString("\n\tPlease specify a yes/no question that distinguishes a " + newAnimal + " from a " + node->question + ": ", true);
       
        char choice3 = inputChar("\n\tAs a " + newAnimal + ", does it " + newQuestion + " (Y-yes/N-no): ", static_cast<string>("YN"));

        //update the  tree
        node->right = new AnimalGuessingGame(newAnimal);
        node->left = new AnimalGuessingGame(node->question);
        node->question = newQuestion;

        if (toupper(choice3) == 'Y') 
        {
            swap(node->left, node->right);
        }
    }
}

//precondition: going to pass in two arguments that one acdepts teh ndoe, the other one to open the file
//postcondition: going to then write to the file
void AnimalGuessingGame::saveToFile(AnimalGuessingGame* node, ostream& file) {
    //if root (nodes) are null then return (base stop)
    if (node == NULL) {
        return;
    }
    //add the left first
    saveToFile(node->left, file);
    //then add the right one
    saveToFile(node->right, file);
    //save the current node's question to the file
    file << node->question << endl;
}

//precondition: going to print the information
//postcondition: going to create a menu that has options 
void AnimalGuessingGame::mainInformation() {
    system("cls");
    char choice;
    //create text file that opens and write to file
    ofstream textFile;
    textFile.open("animal.txt");
    do {
        cout << "\n\t3> Animal Guessing Game";
        cout << "\n\t" << string(82, char(205));
        cout << "\n\n\tA game tree for a simple game of 'animal' twenty questions would look like: \n";
        cout << "\n\n\n\n\tA learning version of twenty questions: one that not only plays the game, but learns new\n\tobjects when it loses.\n";
        cout << "\n\n\tWelcome to Animal Guessing Game";
        cout << "\n\t" << string(82, char(205));
        cout << "\n\t\tA> Play the game";
        cout << "\n\t\tB> Save the game file";
        cout << "\n\t" << string(82, char(205));
        cout << "\n\t\t0> return";
        cout << "\n\t" << string(82, char(205)) << "\n";
        choice = inputChar("\t\tOption: ", static_cast<std::string>("AB0"));

        switch (toupper(choice)) {
        case 'A': {
            system("cls");
            cout << "\n\tThink of animal and press the RETURN/ENTER key to begin...";
            system("pause");
            playGame(root);
            system("pause");
            system("cls");
        }
                break;
        case 'B': {
            saveToFile(root, textFile);
            //closing file
            textFile.close();
        }
                break;
        case '0': {
            return;
        }
        }
    } while (true);
}
