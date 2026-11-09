#include <iostream>
#include <string>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = NULL;
    }
};

// min heap of node pointers
class MinHeap {
    Node* arr[100];
    int size;

public:
    MinHeap() { size = 0; }

    int getSize() { return size; }

    void insert(Node* n) {
        int i = size++;
        arr[i] = n;
        while (i > 0 && arr[(i - 1) / 2]->freq > arr[i]->freq) {
            swap(arr[i], arr[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    Node* extractMin() {
        Node* top = arr[0];
        arr[0] = arr[--size];
        int i = 0;
        while (true) {
            int l = 2 * i + 1, r = 2 * i + 2, small = i;
            if (l < size && arr[l]->freq < arr[small]->freq) small = l;
            if (r < size && arr[r]->freq < arr[small]->freq) small = r;
            if (small == i) break;
            swap(arr[i], arr[small]);
            i = small;
        }
        return top;
    }
};

Node* buildHuffman(string s, int f[]) {
    MinHeap heap;
    for (int i = 0; i < (int)s.length(); i++)
        heap.insert(new Node(s[i], f[i]));

    while (heap.getSize() > 1) {
        Node* a = heap.extractMin();
        Node* b = heap.extractMin();
        Node* parent = new Node('$', a->freq + b->freq);
        parent->left = a;
        parent->right = b;
        heap.insert(parent);
    }
    return heap.extractMin();
}

// preorder: node, left, right
void printCodes(Node* root, string code) {
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) {
        cout << root->ch << ": " << code << endl;
        return;
    }
    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

int main() {
    string s;
    int n;
    cout << "Enter number of characters: ";
    cin >> n;
    cout << "Enter the characters (no spaces): ";
    cin >> s;
    int f[100];
    cout << "Enter frequencies:" << endl;
    for (int i = 0; i < n; i++) {
        cout << s[i] << ": ";
        cin >> f[i];
    }

    Node* root = buildHuffman(s, f);
    cout << "\nHuffman codes (preorder):" << endl;
    printCodes(root, "");
    return 0;
}
