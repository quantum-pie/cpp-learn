#include <string>
#include <iostream>

using namespace std;

class Node {
public:
    bool word = false;  // Node's "word" label
    Node* children[26]; // children[0] corresponds to 'a', children[1] to 'b', etc.
    Node();             // Node constructor
};

Node::Node(void) {
    for(int i = 0; i < 26; ++i) {
        children[i] = NULL;
    }
}

class MultiwayTrie {
public:
    Node* root = new Node();  // root node of Multiway Trie
    bool find(string word);   // "find" function of MultiwayTrie class
    void insert(string word); // "insert" function of MultiwayTrie class
    void remove(string word); // "remove" function of MultiwayTrie class
};

/* Return true if MultiwayTrie contains word, otherwise return false */
bool MultiwayTrie::find(string word) {
    Node* current_node = root;
    for(char c : word)
    {
        int c_idx = c - 'a';
        current_node = current_node->children[c_idx];
        if(!current_node)
        {
            return false;
        }
    }
    return current_node->word;
}

/* Insert word into MultiwayTrie (return nothing) */
void MultiwayTrie::insert(string word) {
    Node* current_node = root;
    for(char c : word)
    {
        int c_idx = c - 'a';
        Node** child_dptr = current_node->children + c_idx;
        if(!*child_dptr)
        {
            *child_dptr = new Node();
        }
        current_node = *child_dptr;
    }
    current_node->word = true;
}

/* Remove word from MultiwayTrie (return nothing) */
void MultiwayTrie::remove(string word) {
    Node* current_node = root;
    for(char c : word)
    {
        int c_idx = c - 'a';
        current_node = current_node->children[c_idx];
        if(!current_node)
        {
            return;
        }
    }
    current_node->word = false;
}

int main()
{
    MultiwayTrie* tr = new MultiwayTrie;
    tr->insert("hi");
    cout << tr->find("hi") << tr->find("hello");
    return 0;
}