#include <iostream>
using namespace std;

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
    Node(int k) {
        key = k;
        height = 1;
        left = right = NULL;
    }
};

int height(Node* n) {
    return n ? n->height : 0;
}

int balance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

void update(Node* n) {
    n->height = 1 + max(height(n->left), height(n->right));
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    update(y);
    update(x);
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    update(x);
    update(y);
    return y;
}

Node* rebalance(Node* n) {
    update(n);
    int b = balance(n);

    if (b > 1) {
        if (balance(n->left) < 0) n->left = rotateLeft(n->left);
        return rotateRight(n);
    }
    if (b < -1) {
        if (balance(n->right) > 0) n->right = rotateRight(n->right);
        return rotateLeft(n);
    }
    return n;
}

Node* insert(Node* root, int key) {
    if (root == NULL) return new Node(key);
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    else {
        cout << key << " already in tree, skipped" << endl;
        return root;
    }
    return rebalance(root);
}

Node* minNode(Node* n) {
    while (n->left) n = n->left;
    return n;
}

Node* removeNode(Node* root, int key) {
    if (root == NULL) return NULL;
    if (key < root->key) root->left = removeNode(root->left, key);
    else if (key > root->key) root->right = removeNode(root->right, key);
    else {
        if (root->left == NULL || root->right == NULL) {
            Node* child = root->left ? root->left : root->right;
            delete root;
            return child;
        }
        Node* succ = minNode(root->right);
        root->key = succ->key;
        root->right = removeNode(root->right, succ->key);
    }
    return rebalance(root);
}

// prints tree sideways, root on the left
void printTree(Node* root, int space = 0) {
    if (root == NULL) return;
    printTree(root->right, space + 6);
    for (int i = 0; i < space; i++) cout << " ";
    cout << root->key << endl;
    printTree(root->left, space + 6);
}

// reverse inorder gives largest first
void getLargest(Node* root, int k, int arr[], int& count) {
    if (root == NULL || count >= k) return;
    getLargest(root->right, k, arr, count);
    if (count < k) arr[count++] = root->key;
    getLargest(root->left, k, arr, count);
}

// inorder gives smallest first
void getSmallest(Node* root, int k, int arr[], int& count) {
    if (root == NULL || count >= k) return;
    getSmallest(root->left, k, arr, count);
    if (count < k) arr[count++] = root->key;
    getSmallest(root->right, k, arr, count);
}

// criteria: 1 = max, 2 = min, 3 = sum of k largest
int topK(Node* root, int k, int criteria, int arr[]) {
    int count = 0;
    if (criteria == 2) getSmallest(root, k, arr, count);
    else getLargest(root, k, arr, count);
    return count;
}

void queryTopK(Node* root, int k, int criteria) {
    int arr[100];
    int count = topK(root, k, criteria, arr);
    if (count == 0) {
        cout << "Tree is empty" << endl;
        return;
    }
    cout << "Top " << count << " elements: ";
    int sum = 0;
    for (int i = 0; i < count; i++) {
        cout << arr[i] << " ";
        sum += arr[i];
    }
    cout << endl;
    if (criteria == 3) cout << "Sum = " << sum << endl;
}

Node* deleteTopK(Node* root, int k, int criteria) {
    int arr[100];
    int count = topK(root, k, criteria, arr);
    for (int i = 0; i < count; i++) {
        root = removeNode(root, arr[i]);
        cout << "\nAfter deleting " << arr[i] << ":" << endl;
        printTree(root);
    }
    return root;
}

int main() {
    Node* root = NULL;
    int choice;

    do {
        cout << "\n1. Insert elements\n2. Query top k\n3. Delete top k\n4. Print tree\n0. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            int n;
            cout << "How many elements: ";
            cin >> n;
            for (int i = 0; i < n; i++) {
                int x;
                cin >> x;
                root = insert(root, x);
                cout << "\nAfter inserting " << x << ":" << endl;
                printTree(root);
            }
        } else if (choice == 2 || choice == 3) {
            int k, c;
            cout << "Enter k: ";
            cin >> k;
            cout << "Criteria (1 = max, 2 = min, 3 = sum): ";
            cin >> c;
            if (choice == 2) queryTopK(root, k, c);
            else root = deleteTopK(root, k, c);
        } else if (choice == 4) {
            printTree(root);
        }
    } while (choice != 0);

    return 0;
}
