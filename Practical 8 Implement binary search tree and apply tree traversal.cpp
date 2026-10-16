#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int d) : data(d), left(nullptr), right(nullptr) {}
};

// Insert (duplicates ignored)
Node* insert(Node* node, int key) {
    if (!node) return new Node(key);
    if (key < node->data) node->left = insert(node->left, key);
    else if (key > node->data) node->right = insert(node->right, key);
    return node;
}

// Search
bool search(Node* node, int key) {
    if (!node) return false;
    if (key == node->data) return true;
    return key < node->data ? search(node->left, key) : search(node->right, key);
}

// Delete
Node* deleteNode(Node* node, int key) {
    if (!node) return nullptr;
    if (key < node->data) node->left = deleteNode(node->left, key);
    else if (key > node->data) node->right = deleteNode(node->right, key);
    else {
        if (!node->left) { Node* r = node->right; delete node; return r; }
        if (!node->right) { Node* l = node->left; delete node; return l; }
        Node* succ = node->right;               // inorder successor
        while (succ->left) succ = succ->left;
        node->data = succ->data;
        node->right = deleteNode(node->right, succ->data);
    }
    return node;
}

// Traversals
void inorder(Node* n) {
    if (!n) return;
    inorder(n->left);
    cout << n->data << " ";
    inorder(n->right);
}

void preorder(Node* n) {
    if (!n) return;
    cout << n->data << " ";
    preorder(n->left);
    preorder(n->right);
}

void postorder(Node* n) {
    if (!n) return;
    postorder(n->left);
    postorder(n->right);
    cout << n->data << " ";
}

void levelOrder(Node* n) {
    if (!n) return;
    queue<Node*> q;
    q.push(n);
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        cout << cur->data << " ";
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}

void freeTree(Node* n) {
    if (!n) return;
    freeTree(n->left);
    freeTree(n->right);
    delete n;
}

int main() {
    Node* root = nullptr;
    int choice, val, n;

    while (true) {
        cout << "\n--- BST Menu ---\n"
             << "1. Insert one value\n"
             << "2. Insert multiple values\n"
             << "3. Search\n"
             << "4. Delete\n"
             << "5. Inorder\n"
             << "6. Preorder\n"
             << "7. Postorder\n"
             << "8. Level order\n"
             << "9. Exit\n"
             << "Choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> val;
                root = insert(root, val);
                break;
            case 2:
                cout << "How many values? ";
                cin >> n;
                cout << "Enter " << n << " values: ";
                while (n--) { cin >> val; root = insert(root, val); }
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> val;
                cout << (search(root, val) ? "Found" : "Not found") << "\n";
                break;
            case 4:
                cout << "Enter value to delete: ";
                cin >> val;
                root = deleteNode(root, val);
                break;
            case 5: cout << "Inorder: ";     inorder(root);    cout << "\n"; break;
            case 6: cout << "Preorder: ";    preorder(root);   cout << "\n"; break;
            case 7: cout << "Postorder: ";   postorder(root);  cout << "\n"; break;
            case 8: cout << "Level order: "; levelOrder(root); cout << "\n"; break;
            case 9:
                freeTree(root);
                cout << "Bye!\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}
