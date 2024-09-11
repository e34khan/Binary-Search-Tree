#include "binary-search-tree.h"
#include <algorithm>
#include <queue>

BinarySearchTree::Node::Node(DataType newval) {
    val = newval;
    left = nullptr;
    right = nullptr;
}

int BinarySearchTree::getNodeDepth(Node* n) const {
    if(n == nullptr){
        return -1;
    }
    else if(n->left == nullptr && n->right == nullptr){
        return 0;
    }
    else{
        return 1 + std::max(getNodeDepth(n->left), getNodeDepth(n->right));
    }
}

BinarySearchTree::BinarySearchTree() {
    root_ = nullptr;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree() {
    std::queue<Node*> queue;
    queue.push(root_);

    while(!queue.empty()){
        Node* current = queue.front();
        queue.pop();

        if(current != nullptr){
            if(current->left != nullptr){
                queue.push(current->left);
            }

            if(current->right != nullptr){
                queue.push(current->right);
            }

            delete current;
            current = nullptr;
        }
    }
}

unsigned int BinarySearchTree::size() const {
 return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const {
    Node* current = root_;
    while(current->right != nullptr){
        current = current->right;
    }
    return current->val;
}

BinarySearchTree::DataType BinarySearchTree::min() const {
    Node* current = root_;
    while(current->left != nullptr){
        current = current->left;
    }
    return current->val;
}

unsigned int BinarySearchTree::depth() const {
    return getNodeDepth(root_);
}

void BinarySearchTree::print() const {

}

bool BinarySearchTree::exists(DataType val) const {
    Node* temp = root_;

    while(temp != nullptr){
        if(temp->val == val){
            return true;
        }
        else if(val > temp->val){
            temp = temp->right;
        }
        else if(val < temp->val){
            temp = temp->left;
        }
    }
    return false;
}

BinarySearchTree::Node* BinarySearchTree::getRootNode() {
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress() {
    return &root_;
}

bool BinarySearchTree::insert(DataType val) {
    if(exists(val)){
        return false;
    }

    if(root_ == nullptr){
        root_ = new Node(val);
        size_++;
        return true;
    }

    Node* temp = root_;
    Node* parent = root_;
    while(temp != nullptr){
        parent = temp;
        if(val > temp->val){
            temp = temp->right;
        }
        else if(val < temp->val){
            temp = temp->left;
        }
    }

    Node* newNode = new Node(val);
    if(val > parent->val){
        parent->right = newNode;
    }
    else if(val < parent->val){
        parent->left = newNode;
    }

    size_++;
    return true;
}

bool BinarySearchTree::remove(DataType val) {
    Node* temp = root_;
    Node* parent = root_;

    while(temp != nullptr){
        if(temp->val == val){
            if(temp->left == nullptr && temp->right == nullptr){
                if(temp == root_) {
                    delete temp;
                    root_ = nullptr;
                }
                else if(parent->left == temp) {
                    delete temp;
                    parent->left = nullptr;
                }
                else {
                    delete temp;
                    parent->right = nullptr;
                }
            }

            else if(temp->left == nullptr){
                if(temp == root_) {
                    root_ = temp->right;
                }
                else if(parent->left == temp) {
                    parent->left = temp->right;
                }
                else {
                    parent->right = temp->right;
                }
                delete temp;
            }

            else if(temp->right == nullptr){
                if(temp == root_) {
                    root_ = temp->left;
                }
                else if(parent->left == temp) {
                    parent->left = temp->left;
                }
                else {
                    parent->right = temp->left;
                }
                delete temp;
            }

            else {
                Node* successor = temp->right;
                bool isLeftChild = false;
                Node* successor_parent = temp;

                while(successor->left != nullptr){
                    successor_parent = successor;
                    successor = successor->left;
                    isLeftChild = true;
                }

                temp->val = successor->val;

                //if it is the leaf node
                if(successor->right == nullptr){
                    if(isLeftChild) successor_parent->left = nullptr;
                    else successor_parent->right = nullptr;
                }
                else { //if it is the branch node. its right child is not empty
                    if(isLeftChild) successor_parent->left = successor->right;
                    else successor_parent->right = successor->right;
                }
                delete successor;
                return true;
            }
            size_--;
            return true;
        }
        else if (val < temp->val) {
            parent = temp;
            temp = temp->left;
        }
        else {
            parent = temp;
            temp = temp->right;
        }
    }
    return false;
}








