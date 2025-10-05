#include<iostream>
using namespace std;
// metodo de ordenamiento arbol binario de busqueda c++
struct Node {
    int data;
    Node* left;
    Node* right;
};
Node* newNode(int data) {
    Node* node = new Node();
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}
Node* insert(Node* root, int data) {
    if (root == nullptr) {
        return newNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}
void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}
int main() {
    Node* root = nullptr;
    int arr[] = {5, 3, 8, 1, 4, 7, 9};
    cout << "Elementos a ordenar: ";
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    int n = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }
    cout << "Elementos ordenados: ";
    inorder(root);
    cout << endl;
    return 0;
}