#pragma once
#include <map>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "Student.h"


struct TNode {

public:
    TNode(Student stud)
        : rating(stud.rating), student(stud), left(nullptr), right(nullptr), same(nullptr)
    {}
    TNode()
        :left(nullptr), right(nullptr), same(nullptr)
    {}
    ~TNode() 
    {}

    double rating = -1;
    Student student;
    TNode* left = nullptr;
    TNode* right = nullptr;
    TNode* same = nullptr;
    TNode* parent = nullptr;
};

class BinarTree
{
public:
    /*
    BinarTree(double rait, int stRef)
        : root(TNode(rait, stRef))
    {}
    */
    BinarTree(Student stud)
        : root(TNode(stud))
    {}
    BinarTree()
    {}
    ~BinarTree() 
    {}

    TNode root; //obzovesh nullptr vse slometsya
    bool exist = false;
    void Add(Student stud) //zapuskat s tolchka root obyavliat
    {
        Add(stud, &root);
    }
    int Obhod()
    {
        int i = 0;
        Obhod(&root, i);
        return i;
    }
    std::vector<Student> Find(double fromD, double toD)
    {
        std::vector<Student> StList = std::vector<Student>();
        FindIn(fromD, toD, StList, &root);
        return StList;
    }
    void Delete(Student stud)
    {
        Delete(stud, &root);
    }

private:
    /*
    void Add(double rait, int stRef, TNode* node)
    {
        if (node->rating > rait)
        {
            if (node->left != nullptr)
            {
                Add(rait, stRef, node->left);
            }
            else
            {
                node->left = new TNode(rait, stRef);
            }
        }
        else if (node->rating < rait)
        {
            if (node->right != nullptr)
            {
                Add(rait, stRef, node->right);
            }
            else
            {
                node->right = new TNode(rait, stRef);
            }
        }
        else
        {
            if (node->same != nullptr)
            {
                Add(rait, stRef, node->same);
            }
            else
            {
                node->same = new TNode(rait, stRef);
            }
        }
    }
    */
    void Add(Student stud, TNode* node)
    {
        if (node == nullptr)
        {
            node = new TNode(stud);
        }
        else if (node->rating > stud.rating)
        {
            if (node->left != nullptr)
            {
                Add(stud, node->left);
            }
            else
            {
                node->left = new TNode(stud);
                node->left->parent = node;
            }
        }
        else if (node->rating < stud.rating)
        {
            if (node->right != nullptr)
            {
                Add(stud, node->right);
            }
            else
            {
                node->right = new TNode(stud);
                node->right->parent = node;
            }
        }
        else
        {
            if (node->same != nullptr)
            {
                Add(stud, node->same);
            }
            else
            {
                node->same = new TNode(stud);
                node->same->parent = node;
            }
        }
    }

    void Obhod(TNode* root, int &i)
    {
        if (root != nullptr)
        {
            ++i;
            std::cout << root->student.rating << "   " << root->student.firstName << "\n";
            Obhod(root->same, i);
            Obhod(root->left, i);
            Obhod(root->right, i);
        }
    }

    void FindIn(double fromD, double toD, std::vector<Student> &list, TNode* node)
    {
        if (node->rating >= fromD && node->rating <= toD)
        {
            list.push_back(node->student);
            if (node->left != nullptr) FindIn(fromD, toD, list, node->left);
            if (node->right != nullptr) FindIn(fromD, toD, list, node->right);
            if (node->same != nullptr) FindIn(fromD, toD, list, node->same);
        }
        if (node->rating < fromD)
        {
            if (node->right != nullptr) FindIn(fromD, toD, list, node->right);
        }
        if (node->rating > toD)
        {
            if (node->left != nullptr) FindIn(fromD, toD, list, node->left);
        }
    }

    bool Delete(Student stud, TNode* node)
    {
        if (node == nullptr) return false;
        if (stud.rating < node->rating)
        {
            Delete(stud, node->left);
        }
        else if(stud.rating > node->rating)
        {
            Delete(stud, node->right);
        }
        else
        {
            if (stud == node->student && node->same != nullptr)
            {
                TNode* s = node->same;
                node->student = s->student;
                node->same = s->same;
                delete s;
            }
            else if(stud != node->student && node->same !=nullptr)
            {
                TNode* n = node;
                TNode* n1 = node;
                while (n->student != stud)
                {
                    n1 = n;
                    n = n->same;
                }
                if (n->same == nullptr)
                {
                    n1->same = nullptr;
                }
                else
                {
                    n1->same = n->same;
                }
            }
            else if (node->left == nullptr && node->right == nullptr)
            {
                if (node->parent->left == node)
                {
                    node->parent->left = nullptr;
                }
                else
                {
                    node->parent->right = nullptr;
                }
                delete node;
            }
            else if (node->left == nullptr && node->right != nullptr)
            {
                TNode* r = node->right;
                node->student = r->student;
                node->rating = r->student.rating;
                node->left = r->left;
                node->same = r->same;
                node->right = r->right;
                delete r;
            }
            else if (node->right == nullptr && node->left != nullptr)
            {
                TNode* l = node->left;
                node->student = l->student;
                node->rating = l->student.rating;
                node->right = l->right;
                node->same = l->same;
                node->left = l->left;
                delete l;
            }
            else if (node->right != nullptr && node->left != nullptr)
            {
                TNode* l = node->left;
                TNode* r = node->right; 
                TNode* rr = node->right->right;
                TNode* rl = node->right->left;
                TNode* n = node->right->left;
                if (rl == nullptr)
                {
                    l->parent = r;
                    rl = l;
                    node->student = node->right->student;
                    node->rating = node->right->student.rating;
                    node->same = r->same;
                    node->left = rl;
                    node->right = rr;
                }
                else
                {
                    while (n->left != nullptr)
                    {
                        n = n->left;
                    }
                    if (rr != nullptr) rr->parent = node;
                    if (rl != nullptr) rl->parent = node;
                    if (node->right->same != nullptr) node->right->same->parent = node;

                    l->parent = n;
                    n->left = l;
                    node->same = r->same;
                    node->student = node->right->student;
                    node->rating = node->right->student.rating;
                    node->left = rl;
                    node->right = rr;
                }
                delete r;
            }
        }
    }
};