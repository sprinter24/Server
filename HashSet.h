#pragma once

#include <vector>
#include <algorithm>
#include "BTree.h"
#include "BinarTree.h"
#include "DataBase.h"


class HashSet
{
public:
	HashSet()
	{}

	int maxGroup = 0;
	std::vector<BTree> bTrees = std::vector<BTree>();
	std::vector<BinarTree> binarTrees = std::vector<BinarTree>();

	void Add(Student stud)
	{
		int group = stud.group;
		if (group > maxGroup)
		{
			Expand(stud.group);
		}
		if (!binarTrees[group].exist)
		{
			binarTrees[group].root = TNode(stud);
			binarTrees[group].exist = true;
		}
		else
		{
			binarTrees[group].Add(stud);
		}

		if (!bTrees[group].exist)
		{
			bTrees[group].Add(stud);
			bTrees[group].exist = true;
		}
		else
		{
			bTrees[group].Add(stud);
		}
	}

	void DeleteFromBinarTree(Student stud)
	{
		if (binarTrees[stud.group].root.left == nullptr
			&& binarTrees[stud.group].root.right == nullptr
			&& binarTrees[stud.group].root.same == nullptr
			) binarTrees[stud.group].exist = false;
		else
		binarTrees[stud.group].Delete(stud);
	}

	std::vector<Student> Find(std::string fromName, int fromGroup, int toGroup, double fromRating, double toRating)
	{
		std::vector<Student> listByName = std::vector<Student>();
		std::vector<Student> listByRating = std::vector<Student>();
		std::vector<Student> var = std::vector<Student>();
 		for (int i = fromGroup; i <= toGroup && i<=maxGroup; ++i)
		{
			if (bTrees[i].exist)
			{
				if (fromName == "_") var = bTrees[i].FindFrom("");
				else var = bTrees[i].FindFrom(fromName);
				listByName.insert(listByName.end(), var.begin(), var.end());
				var.clear();
				var = binarTrees[i].Find(fromRating, toRating);
				listByRating.insert(listByRating.end(), var.begin(), var.end());
				var.clear();
			}
		}
		return Intersection(listByName, listByRating);
	}

	void DeleteFromBTree(std::vector<Student> studs)
	{
		for (int i = 0; i <= maxGroup; ++i)
		{
			bTrees[i].exist = false;
			bTrees[i] = BTree(4);
		}
		for (int i = 0; i < studs.size(); ++i)
		{
			if (!bTrees[studs[i].group].exist)
			{
				bTrees[studs[i].group].Add(studs[i]);
				bTrees[studs[i].group].exist = true;
			}
			else
			{
				bTrees[studs[i].group].Add(studs[i]);
			}
		}
	}

private:
	std::vector<Student> Intersection(std::vector<Student> &v1, std::vector<Student> &v2)
	{
		std::vector<Student> res = std::vector<Student>();
		for (int i = 0; i < v1.size(); ++i)
		{
			for (int j = 0; j < v2.size(); ++j)
			{
				if (v1[i] == v2[j]) res.push_back(v1[i]);
			}
		}
		return res;
	}

	void Expand(int groupCount)
	{
		for (int i = maxGroup; i <= groupCount; ++i)
		{
			bTrees.push_back(BTree(4));
			binarTrees.push_back(BinarTree());
		}
		if (maxGroup < groupCount)
		{
			maxGroup = groupCount;
		}
	}
};

