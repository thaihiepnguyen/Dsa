#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isWord;
    TrieNode() {
        isWord = false;
    }
};

class Trie {
private:
    TrieNode* _root;
    void _findWords(vector<string>& result, TrieNode* node, string prefix) {
        if (node->isWord == true) {
            result.push_back(prefix);
        }
        for (auto i = node->children.begin(); i != node->children.end(); i++) {
            char character = i->first; TrieNode* child = i->second;
            _findWords(result, child, prefix + character);
        }
    }
    
    void _freeMemory(TrieNode* root) {
        if (root->children.empty()) {
            delete root;
            return;
        }
        for (auto i = root->children.begin(); i != root->children.end(); i++) {
            _freeMemory(i->second);
        }
    }
public:
    Trie() {
        _root = new TrieNode();
    }
    void insert(string key) {
        TrieNode* node = _root;
        for (char charactor : key) {
            if (node->children.find(charactor) == node->children.end()) {
                node->children[charactor] = new TrieNode();
            }
            node = node->children[charactor];
        }
        node->isWord = true;
    }
    
    vector<string> search(string prefix) {
        vector<string> result;
        TrieNode* node = _root;
        for (char character : prefix) {
            if (node->children.find(character) == node->children.end()) {
                cout << "Not found!" << endl;
                return result;
            }
            node = node->children[character];
        }
        
        _findWords(result, node, prefix);
        
        return result;
    }
    
    ~Trie() {
        _freeMemory(_root);
    }
};

int main(int argc, const char * argv[]) {
    vector<string> keys = {
        "apple", "application hihi", "api", "bomman", "banana"
    };

    Trie* trie = new Trie();
    for (string key : keys) {
        trie->insert(key);
    }
    
    vector<string> result = trie->search("appdd");
    
    for (string item : result) {
        cout << item << endl;
    }
    
    return 0;
}
