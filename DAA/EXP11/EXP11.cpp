#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

// A node in the Huffman Tree
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char character, int frequency) {
        ch = character;
        freq = frequency;
        left = right = nullptr;
    }
};

// Custom comparator to order the priority queue (Min-Heap) by frequency
struct compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Recursively traverse the tree to generate and map the binary codes
void generateCodes(Node* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (root == nullptr) return;

    // If it's a leaf node, store the generated code
    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = code;
    }

    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

// Function to decode the encoded binary string back to the original text
string decode(Node* root, string encodedString) {
    string decodedText = "";
    Node* current = root;
    
    for (char bit : encodedString) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        // Reached a leaf node
        if (current->left == nullptr && current->right == nullptr) {
            decodedText += current->ch;
            current = root; // Reset back to root for the next character
        }
    }
    return decodedText;
}

void buildHuffmanTree(string text) {
    // 1. Calculate the frequency of each character
    unordered_map<char, int> freqMap;
    for (char ch : text) {
        freqMap[ch]++;
    }

    // 2. Create a min-heap and insert all characters as single-node trees
    priority_queue<Node*, vector<Node*>, compare> pq;
    for (auto pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Handle edge case where the text has only one unique character