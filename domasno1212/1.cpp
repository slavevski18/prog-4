#include <bits/stdc++.h>
using namespace std;

struct TNode {
    bool end;
    vector<TNode*> children;

    TNode() : end(false), children(26, nullptr) {}

    ~TNode() {
        for (int i = 0; i < (int)children.size(); i++) {
            TNode* child = children[i];
            delete child;
        }
    }
};

class Trie {
private:
    TNode* root;

public:
    Trie() {
        root = new TNode();
    }

    ~Trie() {
        delete root;
    }

    void insert(const string& word) {
        TNode* current = root;

        for (int i = 0; i < (int)word.size(); i++) {
            char ch = word[i];
            if (!isalpha(ch)) {
                continue;
            }

            ch = tolower(ch);
            int index = ch - 'a';

            if (current->children[index] == nullptr) {
                current->children[index] = new TNode();
            }

            current = current->children[index];
        }

        current->end = true;
    }

    bool search(const string& word) const {
        TNode* current = root;

        for (int i = 0; i < (int)word.size(); i++) {
            char ch = word[i];
            if (!isalpha(ch)) {
                continue;
            }

            ch = tolower(ch);
            int index = ch - 'a';

            if (current->children[index] == nullptr)
                return false;

            current = current->children[index];
        }
        return current->end;
    }
};

int main() {
    Trie trie;
    ifstream file("wiki-100k.txt");

    if (!file.is_open()) {
        cout << "Error" << endl;
        return 1;
    }

    string word;
    int count = 0;

    while (getline(file, word)) {
        trie.insert(word);
        count++;
    }

    file.close();

    cout << count << endl;

    cout << trie.search("manchester") << endl;
    cout << trie.search("united") << endl;
    cout << trie.search("the") << endl;
    cout << trie.search("best") << endl;
    cout << trie.search("club") << endl;
    cout << trie.search("in") << endl;
    cout << trie.search("the") << endl;
    cout << trie.search("world") << endl;


    return 0;
}
