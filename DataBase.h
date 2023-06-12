#pragma once

#include <iostream>
#include <Vector>
#include <fstream>
#include <map>

#include "Parser.h"
#include "Student.h"
#include "BinarTree.h"
#include "BTree.h"
#include "HashSet.h"


class DataBase
{
public:
	DataBase() {}

	std::vector<Student> studentList = std::vector<Student>();
	std::vector<Student> selection = std::vector<Student>();
	HashSet hashSet;
	Parser parser;

	void LoadData(std::string path)
	{
		std::cout << "Loading in base started\n";;

		std::ifstream file(path);

		std::string name;
		std::string lastName;
		std::string patronymic;
		std::string info;
		int group;
		int maxGroup = 0;
		double rating;


		if (file.is_open()) 
		{
			int i = 0;
			std::string line;
			while (!file.eof())
			{
				file >> name >> lastName >> patronymic >> group >> rating >> info;
				Add(Student(name, lastName, patronymic, group, rating, info)); // hashset b list sozdautsa tut
				++i;
				if (group > maxGroup)
				{
					maxGroup = group;
				}
			}
			std::cout << "Loading comleted successfully\n";
			std::cout << "Students count: " << i << std::endl;
		}
		else 
		{
			std::cout << "Incorrect file path\n";
		}
		file.close();
		
	} 

	void Add(Student student_)
	{
		studentList.push_back(student_);
		hashSet.Add(student_);
	}

	void Show() 
	{
		for (int i = 0; i < studentList.size(); ++i) 
		{
			std::cout << studentList[i].firstName << "  " << studentList[i].group << "  " << studentList[i].rating << "  " << studentList[i].info << "\n";
		}
	}

	std::string ReadLine(std::string str)
	{
		Parser::commandType com = parser.CommandDefine(str);
		if (com == Parser::error_W) return "Incorect input";
		else if (com == Parser::insert_W)
		{
			std::string name;
			std::string lastName;
			std::string patronymic;
			std::string info;
			std::string gr;
			std::string r;
			int group;
			double rating;
			int i = 7;
			if (str.size() < 7) return "Incorect input";
			for (i; i < str.size() && str[i] != ' '; ++i) name += str[i];
			++i;
			for (i; i < str.size() && str[i] != ' '; ++i) lastName += str[i];
			++i;
			for (i; i < str.size() && str[i] != ' '; ++i) patronymic += str[i];
			++i;
			for (i; i < str.size() && str[i] != ' '; ++i) gr += str[i];
			++i;
			for (i; i < str.size() && str[i] != ' '; ++i) r += str[i];
			++i;
			for (i; i < str.size(); ++i) info += str[i];
			if (name == "" || lastName == "" || patronymic == "" || gr == "" || r == "") return "Incorect input";

			try
			{
				group = stoi(gr);
				rating = stod(r);
			}
			catch (...)
			{
				return "Incorect input";
			}

			if (group < 0) return "Incorect input";
			if (rating < 3 || rating > 5 ) return "Incorect input";
			if (info == "") info = "NO INFO";
			Student stud = Student(name, lastName, patronymic, group, rating, info);
			for (int i = 0; i < studentList.size(); ++i) if (stud == studentList[i]) return "This student is already exist";
			Add(stud);
			return "Student added";
		}
		else if(com == Parser::remowe_W)
		{
			if (str == "remove selected")
			{
				std::vector<Student> studList = std::vector<Student>();
				for (int i = 0; i < selection.size(); ++i) hashSet.DeleteFromBinarTree(selection[i]);
				for (int i = 0; i < selection.size(); ++i)
				{
					for (int j = 0; j < studentList.size(); ++j)
					{
						if (studentList[j] == selection[i])
						{
							studentList.erase(studentList.begin() + j);
						}
					}
				}
				hashSet.DeleteFromBTree(studentList);
				//std::cout << "Student count: " << studentList.size() << std::endl;
				//studentList = studList;
				selection.clear();
			}
			else return "Incorect input";
			return "Student count: " + std::to_string(studentList.size()); // ne nado
		}
		else if (com == Parser::select_W)
		{
			std::string var;
			std::string lName;
			std::string gr;
			std::string rt;
			int gr1, gr2;
			double rt1, rt2;
			int i = 7;
			if (str == "select all")
			{
				selection = hashSet.Find("", 0, hashSet.maxGroup, 0, 6);
				//std::cout << "Students selected: " << selection.size() << std::endl;
				return "Students selected: " + std::to_string(studentList.size());
			}
			if (str.size() < 7) return "Incorect input";
			for (i; i < str.size() && str[i] != ' '; ++i) lName += str[i];
			++i;
			for (i; i < str.size() && str[i] != ' '; ++i) gr += str[i];
			++i;
			for (i; i < str.size() && str[i] != ' '; ++i) rt += str[i];
			++i;
			for (i; i < str.size(); ++i) gr += str[i];
			bool stf = false;
			for (i = 0; i < gr.size(); ++i)
			{
				if (gr[i] == '-') stf = true;
			}
			if (gr == "_")
			{
				gr1 = 0;
				gr2 = hashSet.maxGroup;
			}
			else if (stf)
			{
				if (gr[0] == '-')
				{
					try
					{
						std::string g;
						for (int j = 1; j < gr.size(); ++j)
						{
							g += gr[j];
						}
						gr1 = 0;
						gr2 = std::stoi(g);
					}
					catch (...)
					{
						return "Incorect input";
					}
				}
				else if(gr[gr.size() - 1] == '-')
				{
					try
					{
						std::string g;
						for (int j = 0; j < gr.size() - 1; ++j)
						{
							g += gr[j];
						}
						gr1 = stoi(g);
						gr2 = hashSet.maxGroup;
					}
					catch(...) 
					{
						return "Incorect input";
					}
				}
				else
				{
					try
					{
						std::string g1, g2;
						int j = 0;
						for (j; j < gr.size() && gr[j] != '-'; ++j)
						{
							g1 += gr[j];
						}
						for (++j; j < gr.size() && gr[j] != '-'; ++j)
						{
							g2 += gr[j];
						}
						gr1 = stoi(g1);
						gr2 = stoi(g2);
					}
					catch (...)
					{
						return "Incorect input";
					}
				}
			}
			else
			{
				try
				{
					gr1 = stoi(gr);
					gr2 = gr1;
				}
				catch (...)
				{
					return "Incorect input";
				}
			}

			stf = false;

			for (i = 0; i < rt.size(); ++i)
			{
				if (rt[i] == '-') stf = true;
			}
			if (rt == "_")
			{
				rt1 = 0;
				rt2 = 6;
			}
			else if (stf)
			{
				if (rt[0] == '-')
				{
					try
					{
						std::string r;
						for (int j = 1; j < rt.size(); ++j)
						{
							r += rt[j];
						}
						rt1 = 0;
						rt2 = stod(r);
					}
					catch (...)
					{
						return "Incorect input";
					}
				}
				else if (rt[rt.size() - 1] == '-')
				{
					try
					{
						std::string r;
						for (int j = 0; j < rt.size() - 1; ++j)
						{
							r += rt[j];
						}
						rt1 = stod(r);
						rt2 = 5;
					}
					catch (...)
					{
						return "Incorect input";
					}
				}
				else
				{
					try
					{
						std::string r1, r2;
						int j = 0;
						for (j; j < rt.size() && rt[j] != '-'; ++j)
						{
							r1 += rt[j];
						}
						for (++j; j < rt.size(); ++j)
						{
							r2 += rt[j];
						}
						rt1 = stod(r1);
						rt2 = stod(r2);
					}
					catch (...)
					{
						return "Incorect input";
					}
				}
			}
			else
			{
				try
				{
					rt1 = stod(rt);
					rt2 = rt1;
				}
				catch (...)
				{
					return "Incorect input";
				}
			}
			selection = hashSet.Find(lName, gr1, gr2, rt1, rt2);
			//std::cout << "Students selected: " << selection.size() << std::endl;
			return "Students selected: " + std::to_string(selection.size());;
		}
		else if(com == Parser::reselect_W)
		{
		std::string var;
		std::string lName;
		std::string gr;
		std::string rt;
		int gr1, gr2;
		double rt1, rt2;
		int i = 9;
		if (str.size() < 9) return "Incorect input";
		for (i; i < str.size() && str[i] != ' '; ++i) lName += str[i];
		++i;
		for (i; i < str.size() && str[i] != ' '; ++i) gr += str[i];
		++i;
		for (i; i < str.size() && str[i] != ' '; ++i) rt += str[i];
		++i;
		for (i; i < str.size(); ++i) gr += str[i];
		bool stf = false;
		for (i = 0; i < gr.size(); ++i)
		{
			if (gr[i] == '-') stf = true;
		}
		if (gr == "_")
		{
			gr1 = 0;
			gr2 = hashSet.maxGroup;
		}
		else if (stf)
		{
			if (gr[0] == '-')
			{
				try
				{
					std::string g;
					for (int j = 1; j < gr.size(); ++j)
					{
						g += gr[j];
					}
					gr1 = 0;
					gr2 = stoi(g);
				}
				catch (...)
				{
					return "Incorect input";
				}
			}
			else if (gr[gr.size() - 1] == '-')
			{
				try
				{
					std::string g;
					for (int j = 0; j < gr.size() - 1; ++j)
					{
						g += gr[j];
					}
					gr1 = stoi(g);
					gr2 = hashSet.maxGroup;
				}
				catch (...)
				{
					return "Incorect input";
				}
			}
			else
			{
				try
				{
					std::string g1, g2;
					int j = 0;
					for (j; j < gr.size() && gr[j] != '-'; ++j)
					{
						g1 += gr[j];
					}
					for (++j; j < gr.size() && gr[j] != '-'; ++j)
					{
						g2 += gr[j];
					}
					gr1 = stoi(g1);
					gr2 = stoi(g2);
				}
				catch (...)
				{
					return "Incorect input";
				}
			}
		}
		else
		{
			try
			{
				gr1 = stoi(gr);
				gr2 = gr1;
			}
			catch (...)
			{
				return "Incorect input";
			}
		}

		stf = false;

		for (i = 0; i < rt.size(); ++i)
		{
			if (rt[i] == '-') stf = true;
		}
		if (rt == "_")
		{
			rt1 = 0;
			rt2 = 6;
		}
		else if (stf)
		{
			if (rt[0] == '-')
			{
				try
				{
					std::string r;
					for (int j = 1; j < rt.size(); ++j)
					{
						r += rt[j];
					}
					rt1 = 0;
					rt2 = stod(r);
				}
				catch (...)
				{
					return "Incorect input";
				}
			}
			else if (rt[rt.size() - 1] == '-')
			{
				try
				{
					std::string r;
					for (int j = 0; j < rt.size() - 1; ++j)
					{
						r += rt[j];
					}
					rt1 = stod(r);
					rt2 = 5;
				}
				catch (...)
				{
					return "Incorect input";
				}
			}
			else
			{
				try
				{
					std::string r1, r2;
					int j = 0;
					for (j; j < rt.size() && rt[j] != '-'; ++j)
					{
						r1 += rt[j];
					}
					for (++j; j < rt.size(); ++j)
					{
						r2 += rt[j];
					}
					rt1 = stod(r1);
					rt2 = stod(r2);
				}
				catch (...)
				{
					return "Incorect input";
				}
			}
		}
		else
		{
			try
			{
				rt1 = stod(rt);
				rt2 = rt1;
			}
			catch (...)
			{
				return "Incorect input";
			}
		}
		Reselect(lName, gr1, gr2, rt1, rt2);
		//std::cout << "Students selected: " << selection.size() << std::endl; //tut
		return "Students selected: " + std::to_string(selection.size());;
		} 
		else if (com == Parser::print_W)
		{
		     if (str != "print") return "Incorect input";
			 return ShowSelection();
		}
	}

	bool SaveData(std::string path)
	{
		std::ofstream file(path);
		if (studentList.size() == 0)
		{
			file.close();
			return false;
		}
		for (int i = 0; i < studentList.size() - 1; ++i)
		{
			file << studentList[i].firstName << " " 
				<< studentList[i].lastName << " " 
				<< studentList[i].patronymic << " " 
				<< studentList[i].group << " " 
				<< studentList[i].rating << " " 
				<< studentList[i].info 
				<< std::endl;
		}
		file << studentList[studentList.size() - 1].firstName << " "
			<< studentList[studentList.size() - 1].lastName << " "
			<< studentList[studentList.size() - 1].patronymic << " "
			<< studentList[studentList.size() - 1].group << " "
			<< studentList[studentList.size() - 1].rating << " "
			<< studentList[studentList.size() - 1].info;
		file.close();
		return true;
	}

private:
		void Reselect(std::string fromName, int fromGroup, int toGroup, double fromRating, double toRating)
		{
			std::vector<Student> v = std::vector<Student>();
			std::string fr = fromName;
			if (fr == "_") fr = "";
			for (int i = 0; i < selection.size(); ++i)
			{
				if (selection[i] >= fr
					&& selection[i].group >= fromGroup
					&& selection[i].group <= toGroup
					&& selection[i].rating >= fromRating
					&& selection[i].rating <= toRating
					) v.push_back(selection[i]);
			}
			selection = v;
		}

		std::string ShowSelection()
		{
			std::string str = "";
			for (int i = 0; i < selection.size(); ++i)
			{
				str += selection[i].firstName + "   " + selection[i].lastName + "   " + selection[i].patronymic + "   " + std::to_string(selection[i].group) + "   " + std::to_string(selection[i].rating) + "   " + selection[i].info + "\n";
				//std::cout << selection[i].firstName << "  " << selection[i].lastName << "  " << selection[i].patronymic << "  " << selection[i].group << "  " << selection[i].rating << "  " << selection[i].info << std::endl;
			}
			if (selection.size() == 0) str = "NO STUDENTS";
			if (str.size() >= 4095) str = "The list is too big to show";
			return str;
		}
};

