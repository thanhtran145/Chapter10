#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool inquire(string prompt);
char inputChar(string prompt, char yes, char no);
string inputString(string prompt, bool spaces);

template <class Item>
class AnimalGuessing
{
private:
	Item data_field;
	AnimalGuessing* left_field;
	AnimalGuessing* right_field;

	static string remove_brackets(const string& str)
	{
		string result = str;
		result.erase(remove(result.begin(), result.end(), '['), result.end());
		result.erase(remove(result.begin(), result.end(), ']'), result.end());
		result.erase(remove(result.begin(), result.end(), '('), result.end());
		result.erase(remove(result.begin(), result.end(), ')'), result.end());
		return result;
	}

	static AnimalGuessing<Item>* build_tree_from_file(ifstream& file)
	{
		string line;
		getline(file, line);

		if (line.empty())
		{
			return nullptr;
		}

		AnimalGuessing<Item>* root = new AnimalGuessing<Item>(remove_brackets(line));

		// Check if the node is a question or a leaf node
		if (line.front() == '[')
		{
			// Recursive call for left and right children (questions)
			root->left() = build_tree_from_file(file);
			root->right() = build_tree_from_file(file);
		}

		return root;
	}

public:

	// TYPEDEF
	typedef Item value_type;

	// CONSTRUCTOR
	AnimalGuessing(const Item& init_data = Item(), AnimalGuessing* init_left = nullptr, AnimalGuessing* init_right = nullptr)
	{
		data_field = init_data;
		left_field = init_left;
		right_field = init_right;
	}

	// MODIFICATION MEMBER FUNCTIONS
	Item& data() { return data_field; }
	AnimalGuessing*& left() { return left_field; }
	AnimalGuessing*& right() { return right_field; }
	void set_data(const Item& new_data) { data_field = new_data; }
	void set_left(AnimalGuessing* new_left) { left_field = new_left; }
	void set_right(AnimalGuessing* new_right) { right_field = new_right; }

	// CONSTANT MEMBER FUNCTIONS
	const Item& data() const { return data_field; }
	const AnimalGuessing* left() const { return left_field; }
	const AnimalGuessing* right() const { return right_field; }
	bool is_leaf() const
	{
		return (left_field == nullptr) && (right_field == nullptr);
	}

	// MEMBER FUNTIONS
	void tree_clear(AnimalGuessing<Item>*& root_ptr)
	{
		AnimalGuessing<Item>* child;
		if (root_ptr != nullptr)
		{
			child = root_ptr->left();
			tree_clear(child);
			child = root_ptr->right();
			tree_clear(child);
			delete root_ptr;
			root_ptr = nullptr;
		}
	}

	AnimalGuessing<Item>* tree_copy(const AnimalGuessing<Item>* root_ptr)
	{
		AnimalGuessing<Item>* l_ptr;
		AnimalGuessing<Item>* r_ptr;
		if (root_ptr == nullptr)
			return nullptr;
		else
		{
			l_ptr = tree_copy(root_ptr->left());
			r_ptr = tree_copy(root_ptr->right());
			return new AnimalGuessing<Item>
				(root_ptr->data(), l_ptr, r_ptr);
		}
	}

	static AnimalGuessing<Item>* beginning_tree(const string& file_name)
	{
		ifstream file(file_name);

		if (file.fail())
		{
			return nullptr;
		}

		// Call a helper function to recursively build the tree
		return build_tree_from_file(file);
	}

	void ask_and_move(AnimalGuessing<string>*& current_ptr)
	{
		cout << "\n\t\t\t" << current_ptr->data();
		if (inquire(" (Y-yes/N-no) "))
			current_ptr = current_ptr->left();
		else
			current_ptr = current_ptr->right();
	}

	void learn(AnimalGuessing<string>* leaf_ptr)
	{
		string guess_animal; // The animal that was just guessed
		string correct_animal; // The animal that the user was thinking of
		string new_question; // A question to distinguish the two animals
		// Set strings for the guessed animal, correct animal, and a new question.
		guess_animal = leaf_ptr->data();

		correct_animal = inputString("\n\t\t\tI give up. What are you ? ", false);

		cout << "\n\t\t\tPlease type a yes/no question that will distinguish a " << correct_animal << " from a " << guess_animal << ".";

		new_question = inputString("\n\t\t\tYour question: ", true);

		// Put the new question in the current node, and add two new children.
		leaf_ptr->set_data(new_question);
		cout << "\n\t\t\tAs a " << correct_animal << ", " << new_question;
		if (inquire(" (Y-yes/N-no) "))
		{
			leaf_ptr->set_left(new AnimalGuessing<string>(correct_animal));
			leaf_ptr->set_right(new AnimalGuessing<string>(guess_animal));
		}
		else
		{
			leaf_ptr->set_left(new AnimalGuessing<string>(guess_animal));
			leaf_ptr->set_right(new AnimalGuessing<string>(correct_animal));
		}
	}

	void play(AnimalGuessing<string>* current_ptr)
	{
		cout << "\n\t\t\tThink of an animal, then ";
		system("pause");
		while (!current_ptr->is_leaf())
			ask_and_move(current_ptr);
		cout << "\n\t\t\tMy guess is " << current_ptr->data();
		if (!inquire(". Am I right? "))
			learn(current_ptr);
		else
			cout << "\n\t\t\tI knew it all along!\n";
	}


	void save_tree_to_file(const string& file_name)
	{
		ofstream file(file_name);

		if (file.fail())
		{
			cout << "\n\t " + file_name + " can not be opened";
			return;
		}

		save_tree_to_file_recursive(file, this); // Start with an initial indentation level of 0
		cout << "\n\t\tGame has been saved to " + file_name << "\n\n";
	}

	static void save_tree_to_file_recursive(ofstream& file, AnimalGuessing<string>* root)
	{
		if (root == nullptr)
		{
			return;
		}

		if (root->is_leaf())
		{
			file << "(" << root->data() << ")\n";
		}
		else
		{
			file << "[" << root->data() << "]\n";

			// Recursive calls for left and right children with increased indentation level
			save_tree_to_file_recursive(file, root->left());
			save_tree_to_file_recursive(file, root->right());
		}
	}

	void menu()
	{
		AnimalGuessing<string>* taxonomy_root_ptr;

		// Use the correct function name: beginning_tree
		taxonomy_root_ptr = AnimalGuessing<string>::beginning_tree("animal.txt");

		if (taxonomy_root_ptr == nullptr)
		{
			cout << "\n\tanimal.txt can not be opened\n";
			return;
		}

		char choice;

		do {
			system("cls");
			cout << "\n\t3> Animal Guessing Game";
			cout << "\n\t" << string(82, char(205));
			cout << "\n\n\tA game tree for a simple game of 'animal' twenty questions would look like: \n";

			cout << "\n\t\t\t\t[ Is it a mammal? ]\n";
			cout << "\t\t                    /         \\" << endl;
			cout << "\t\t                   /           \\" << endl;
			cout << "\t\t [ Does it have stripes? ]     [ Is it a bird? ]" << endl;
			cout << "\t\t         /       \\                  /       \\" << endl;
			cout << "\t\t        /         \\                /         \\" << endl;
			cout << "\t\t  ( Zebra )    ( Lion )    [ Does it fly? ]  ( Gila monster )" << endl;
			cout << "\t\t                             /       \\" << endl;
			cout << "\t\t                            /         \\" << endl;
			cout << "\t\t                     ( Eagle )     ( Penguin )" << endl;

			cout << "\n\n\tA learning version of twenty questions: one that not only plays the game, but learns new\n\tobjects when it loses.\n";
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
				do
					play(taxonomy_root_ptr);
				while (inquire("\n\t\t\tShall we play again? "));

				cout << "\n\t\t\tThanks for teaching me a thing or two.\n";
			}
					break;
			case 'B': 
			{
				taxonomy_root_ptr->save_tree_to_file("animal.txt");
				system("pause");
			}
					break;
			case '0': {
				return;
			}
			}
		} while (true);
	}
};
