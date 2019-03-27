//
// Created by dawid on 24.03.19.
//

#ifndef BST_BST_HPP
#define BST_BST_HPP
#include <iostream>
using namespace std;

template <typename T>
class BST
{
    friend std::ostream& operator<<(std::ostream& os, const BST<T> &tree)
    {
        tree.printBST(os, tree.root);
        return os << "\n";
    }

    friend void swap(BST<T>& first, BST<T>& second)
    {
        using std::swap;

        swap(first.root, second.root);
        second.root = nullptr;
    }

public:
    struct Node {
        T value;
        Node *left, *right, *parent;
    };

    BST() : root(nullptr) { }
    BST(const BST& other);
    BST(BST&& other) noexcept;
    ~BST() {  destroyer(root); }

    BST<T>& operator=(const BST<T>& other);
    BST<T>& operator=(BST<T>&& other);

    bool isEmpty() const { return root == nullptr; }
    Node* insert(T value);
    Node* search(T value) const;
    void remove(Node* removeNode);
    void remove(T removeVal);
    Node* root;
    int Size() const;
    int Size(Node*) const;
    void printInorder();
    void printInorder(struct Node*);

private:


    void destroyer(Node* Node)
    {
        if(Node != NULL)
        {
            destroyer(Node->left);
            destroyer(Node->right);
            delete Node;
        }
    }

    void copy(Node* &origin, const Node* sourceNode)
    {
        if(sourceNode == nullptr)
            origin == nullptr;
        else
        {
            origin = new Node;
            origin->value = sourceNode->value;
            copy(origin->left, sourceNode->left);
            copy(origin->right, sourceNode->right);
        }

    }




};
#endif //BST_BST_HPP

template <typename T>
BST<T>::BST(const BST<T>& other)
        : root(nullptr)
{

    if(other.root != nullptr)
        copy(this->root, other.root);
}

template <typename T>
BST<T>::BST(BST<T>&& other) noexcept
        : root(nullptr)
{


    swap(*this, other);
}

template <typename T>
BST<T>& BST<T>::operator=(const BST<T>& other)
{


    BST temp(other);
    swap(*this, temp);
    return *this;
}

template <typename T>
BST<T>& BST<T>::operator=(BST<T>&& other)
{

    swap(*this, other);
    return *this;
}
template <typename T>
int BST<T>::Size() const  {
    if(root == nullptr)
        return 0;
    else
        return (Size(root->left) + 1 + Size(root->right));
}
template <typename T>
int BST<T>::Size(Node* leaf) const  {
    if(root == nullptr)
        return 0;
    else
        return (Size(root->left) + 1 + Size(root->right));
}
template <typename T>
auto BST<T>::insert(T value) -> Node*
{
    if(root == nullptr)
    {
        root = new Node;
        root->value = value;
        root->left = nullptr;
        root->right = nullptr;

        return root;
    }
    else
    {
        Node* temp = root;
        Node* temp2 = nullptr;

        Node* pass = new Node;
        pass->value = value;
        pass->left = nullptr;
        pass->right = nullptr;

        while(temp != nullptr)
        {
            if (value > temp->value)
            {
                temp2 = temp;
                temp = temp->right;
            }

            else if (value <= temp->value)
            {
                temp2 = temp;
                temp = temp->left;
            }

        }

        if (value > temp2->value)
        {
            temp2->right = pass;
            pass->parent = temp2;
        }
        else if(value <= temp2->value)
        {
            temp2->left = pass;
            pass->parent = temp2;
        }

        return pass;
    }
}
template <typename T>
void BST<T>::printInorder(){
    if(root == nullptr){
        cout<<"Tree is NULL"<<endl;
        return;
    }
    printInorder(root);
}
template <typename T>
void BST<T>::printInorder(struct Node* node)
{
    if (node == NULL)
        return;


    printInorder(node->left);


    cout << node->value << " ";


    printInorder(node->right);
}
template <typename T>
auto BST<T>::search(T value) const -> Node*
{
    if (root == nullptr)
    {
        return nullptr;
    }

    Node* temp = root;

    while(temp != nullptr)
    {
        if (value == temp->value)
            return temp;

        else if (value > temp->value)
            temp = temp->right;

        else if (value < temp->value)
            temp = temp->left;
    }

    if (temp == nullptr)
        return nullptr;
}

template <typename T>
void BST<T>::remove(Node* rmNode)
{
    if(rmNode == nullptr)
    {

        return;
    }

    if(rmNode != nullptr)
    {
        if (rmNode->left == nullptr && rmNode->right == nullptr)
        {
            Node* parent = rmNode->parent;

            if(parent->left == rmNode)
                parent->left = nullptr;
            else if (parent->right == rmNode)
                parent->right = nullptr;

            delete rmNode;
        }
        else if( (rmNode->left != nullptr && rmNode->right == nullptr) )
        {
            Node* parent = rmNode->parent;

            if (parent->left == rmNode)
                parent->left = rmNode->left;
            else if (parent->right == rmNode)
                parent->right = rmNode->left;

            delete rmNode;
        }

        else if(rmNode->left == nullptr && rmNode->right != nullptr)
        {
            Node* parent = rmNode->parent;

            if(parent->left == rmNode)
                parent->left = rmNode->right;
            else if (parent->right == rmNode)
                parent->right = rmNode->right;

            delete rmNode;
        }
        else if (rmNode->left != nullptr && rmNode->right != nullptr)
        {
            Node* successor = rmNode->right;

            if(successor->left == nullptr)
            {
                T tempVal = successor->value;

                remove(successor->value);

                rmNode->value = tempVal;
                return;
            }

            else if (successor->left != nullptr)
            {
                Node* temp = successor;

                while (temp != nullptr)
                {
                    successor = temp;
                    temp = temp->left;
                }

                T tempVal = successor->value;

                remove(successor->value);

                rmNode->value = tempVal;
                return;
            }
        }
    }
}

template <typename T>
void BST<T>::remove(T removeVal)
{
    Node* rmNode = search(removeVal);
    if(rmNode != nullptr)
        remove(rmNode);
    else
       cout<<"Tree is empty"<<endl;
}

