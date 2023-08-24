//
// Created by Diego Pacheco Ferrel on 26/05/23.
//

#ifndef BLOCKCHAIN_AVL_H
#define BLOCKCHAIN_AVL_H

#include <iostream>
#include "node.h"

using namespace std;

template <typename T>
class AVLTree
{
private:
    NodeBT<T> *root;

public:
    AVLTree() : root(nullptr) {}
    void insert(T value)
    {
        insert(this->root, value);
    }
    bool find(T value)
    {
        return find(this->root, value);
    }

    string getPreOrder(){
        return getPreOrder(this->root);
    }

    int height()
    {
        return height(this->root);
    }
    T minValue()
    {
        return minValue(this->root);
    }
    T maxValue()
    {
        return maxValue(this->root);
    }
    bool isBalanced()
    {
        return isBalanced(this->root);
    }
    int size()
    {
        return size(this->root);
    }
    void remove(T value)
    {
        remove(this->root, value);
    }
    void displayPretty()
    {
        displayPretty(this->root, 1);
    }

    ~AVLTree(){
        if(this->root != nullptr){
            this->root->killSelf();
        }
    }

private:
    string getPreOrder(NodeBT<T>* node) {
        if (node == nullptr) {
            return "";
        }

        string result = to_string(node->data) + " ";
        result += getPreOrder(node->left);
        result += getPreOrder(node->right);

        return result;
    }

    void insert(NodeBT<T>*& node, T value) {
        if (node == nullptr) {
            node = new NodeBT<T>(value);
            return;
        }

        if (value < node->data) {
            insert(node->left, value);
        } else if (value > node->data) {
            insert(node->right, value);
        }

        updateHeight(node);
        balance(node);
    }

    bool find(NodeBT<T>* node, T value) {
        if (node == nullptr) {
            return false;
        }

        if (node->data == value) {
            return true;
        }

        if (value < node->data) {
            return find(node->left, value);
        } else {
            return find(node->right, value);
        }
    }

    int height(NodeBT<T>* node) {
        if (node == nullptr) {
            return -1;
        }
        return node->height;
    }

    bool isBalanced(NodeBT<T>* node) {
        if (node == nullptr) {
            return true;
        }

        int bf = balancingFactor(node);
        if (abs(bf) > 1) {
            return false;
        }

        return isBalanced(node->left) and isBalanced(node->right);
    };

    T minValue(NodeBT<T>* node) {
        if (node == nullptr) {
            throw std::out_of_range("El árbol está vacío!");
        }

        if (node->left == nullptr) {
            return node->data;
        }

        return minValue(node->left);
    }

    T maxValue(NodeBT<T>* node) {
        if (node == nullptr) {
            throw std::out_of_range("El árbol está vacío");
        }

        if (node->right == nullptr) {
            return node->data;
        }

        return maxValue(node->right);
    }

    int size(NodeBT<T>* node) {
        if (node == nullptr) {
            return 0;
        }

        return size(node->left) + size(node->right) + 1;
    }

    void remove(NodeBT<T>*& node, T value) {
        if (node == nullptr)
            return;
        else if (value < node->data)
            remove(node->left, value);
        else if (value > node->data)
            remove(node->right, value);
        else
        {
            if (node->left == nullptr and node->right == nullptr)
            {
                delete node; //free
                node = nullptr;
            }
            else if (node->left == nullptr)
            {
                NodeBT<T> *temp = node;
                node = node->right;
                delete temp;
            }
            else if (node->right == nullptr)
            {
                NodeBT<T> *temp = node;
                node = node->left;
                delete temp;
            }
            else
            {
                T temp = maxValue(node->left);
                node->data = temp;
                remove(node->left, temp);
            }
        }

        if(node){
            updateHeight(node);
            balance(node);
        }
    }

    void displayPretty(NodeBT<T> *node, int level){
        if (node == nullptr) {
            return;
        }
        displayPretty(node->right, level + 1);
        for (int i = 0; i < level; i++) {
            cout << "   ";
        }
        cout << node->data << endl;
        displayPretty(node->left, level + 1);
    };

    /*add for avl*/
    int balancingFactor(NodeBT<T> *node){
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    };
    void updateHeight(NodeBT<T> *node){
        if (node == nullptr) {
            return;
        }
        int left_height = height(node->left);
        int right_height = height(node->right);
        node->height = max(left_height, right_height) + 1;
    };
    void balance(NodeBT<T> *&node){
        if (node == nullptr) {
            return;
        }
        if (balancingFactor(node) == 2) {
            if (balancingFactor(node->left) < 0) {
                left_rota(node->left);
            }
            right_rota(node);
        }
        else if (balancingFactor(node) == -2) {
            if (balancingFactor(node->right) > 0) {
                right_rota(node->right);
            }
            left_rota(node);
        }
        updateHeight(node);
    };
    void left_rota(NodeBT<T> *&node){
        NodeBT<T> *temp = node->right;
        node->right = temp->left;
        temp->left = node;
        updateHeight(node);
        updateHeight(temp);
        node = temp;
    };
    void right_rota(NodeBT<T> *&node){
        NodeBT<T> *temp = node->left;
        node->left = temp->right;
        temp->right = node;
        updateHeight(node);
        updateHeight(temp);
        node = temp;
    };
};


#endif //BLOCKCHAIN_AVL_H
