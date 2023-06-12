#pragma once
#include "Student.h"
#include <stdio.h>
#include <iostream>
#include <vector>




class TreeNode
{
    int t;
    Student* studs;
    TreeNode** C;
    int n;
    bool leaf;
public:
    TreeNode(int t1, bool leaf1)
    {
        t = t1;
        leaf = leaf1;
        studs = new Student[2 * t - 1];
        C = new TreeNode * [2 * t];

        n = 0;
    }

    void AddNonFull(Student stud)
    {
        int i = n - 1;

        if (leaf == true)
        {
            while (i >= 0 && studs[i] > stud)
            {
                studs[i + 1] = studs[i];
                i--;
            }

            studs[i + 1] = stud;
            n = n + 1;
        }
        else
        {
            while (i >= 0 && studs[i] > stud)
                i--;

            if (C[i + 1]->n == 2 * t - 1)
            {
                splitChild(i + 1, C[i + 1]);

                if (studs[i + 1] < stud)
                    i++;
            }
            C[i + 1]->AddNonFull(stud);
        }
    }
    void traverse()
    {
        int i;
        for (i = 0; i < n; i++)
        {
            if (leaf == false)
                C[i]->traverse();
            std::cout << " " << studs[i].lastName << std::endl;
        }

        if (leaf == false)
            C[i]->traverse();
    }
    void splitChild(int i, TreeNode* y)
    {
        TreeNode* z = new TreeNode(y->t, y->leaf);
        z->n = t - 1;

        for (int j = 0; j < t - 1; j++)
            z->studs[j] = y->studs[j + t];

        if (y->leaf == false)
        {
            for (int j = 0; j < t; j++)
                z->C[j] = y->C[j + t];
        }

        y->n = t - 1;
        for (int j = n; j >= i + 1; j--)
            C[j + 1] = C[j];

        C[i + 1] = z;

        for (int j = n - 1; j >= i; j--)
            studs[j + 1] = studs[j];

        studs[i] = y->studs[t - 1];
        n = n + 1;

    }

    void FindFrom(std::string str, std::vector<Student>& list)
    {
        int i;
        for (i = 0; i < n; i++)
        {
            if (leaf == false)
                C[i]->FindFrom(str, list);
            if (studs[i] >= str) list.push_back(studs[i]);
        }

        if (leaf == false)
            C[i]->FindFrom(str, list);
    }

    friend class BTree;
};

class BTree
{
    TreeNode* root;
    int t;
public:
    bool exist = false;
    BTree(int temp)
    {
        root = nullptr;
        t = temp;
    }

    void traverse()
    {
        if (root != nullptr)
            root->traverse();
    }

    void Add(Student stud)
    {
        if (root == nullptr)
        {
            root = new TreeNode(t, true);
            root->studs[0] = stud;
            root->n = 1;
        }
        else
        {
            if (root->n == 2 * t - 1)
            {
                TreeNode* s = new TreeNode(t, false);

                s->C[0] = root;
                s->splitChild(0, root);

                int i = 0;
                if (s->studs[0] < stud)
                    i++;
                s->C[i]->AddNonFull(stud);

                root = s;
            }
            else
                root->AddNonFull(stud);
        }
    }

    std::vector<Student> FindFrom(std::string str)
    {
        std::vector<Student> studList = std::vector<Student>();
        root->FindFrom(str, studList);
        return studList;
    }
};