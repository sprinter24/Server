#pragma once

#include <string>


struct Student 
{
public:
	std::string firstName;
	std::string lastName;
	std::string patronymic;
	int group;
	double rating;
	std::string info;

	bool operator == (const Student &other)
	{
		if (firstName == other.firstName && lastName == other.lastName && patronymic == other.patronymic && group == other.group && fabs(rating - other.rating) <1e-10 && info == other.info)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator != (const Student &other)
	{
		if (firstName != other.firstName || lastName != other.lastName || patronymic != other.patronymic || group != other.group || fabs(rating - other.rating) > 1e-10 || info != other.info)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator >(const Student& other) //sravnenie dlya B dereva
	{
		int l = lastName.size();
		int ol = other.lastName.size();
		for (int i = 0; i < l && i < ol; ++i)
		{
			if (lastName[i] > other.lastName[i])
			{
				return true;
			}
			if (lastName[i] < other.lastName[i])
			{
				return false;
			}
		}
		if (l > ol)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator <(const Student& other)  //sravnenie dlya B dereva
	{
		int l = lastName.size();
		int ol = other.lastName.size();
		for (int i = 0; i < l && i < ol; ++i)
		{
			if (lastName[i] < other.lastName[i])
			{
				return true;
			}
			if (lastName[i] > other.lastName[i])
			{
				return false;
			}
		}
		if (l < ol)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator >(const std::string& str)  //sravnenie dlya B dereva
	{
		int strl = str.length();
		int l = lastName.length();
		if (l < strl) return false;
		for (int i = 0; i < strl; ++i)
		{
			if (lastName[i] < str[i]) return false;
		}
		return true;
	}
	 
	bool operator >=(const std::string& str) //sravnenie dlya polzovatelya
	{
		int strl = str.length();
		int l = lastName.length();
		if (str == "") return true;
		if (l < strl) return false;
		for (int i = 0; i < strl; ++i)
		{
			if (lastName[i] != str[i]) return false;
		}
		return true;
	}
	Student()
		: group(0), rating(0), info("NoInfo"), firstName("NO"), lastName("NO"), patronymic("NO")
	{}

	Student(std::string firstName_, std::string lastName_, std::string patronymic_ , int group_, double rating_, std::string info_) :
		 group(group_), rating(rating_), info(info_), firstName(firstName_), lastName(lastName_), patronymic(patronymic_)
	{}
	~Student()
	{}
};


