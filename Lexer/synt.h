#pragma once
#include "main.h"
#include "tables.h"

struct leaf
{
private:
	vector<leaf> child;
	lexem *lex;
	int level;
	string name;
public:
	leaf() { level = 0; lex = NULL; name = "_tree"; };
	leaf(int level_number, string node_name) { level = level_number; lex = NULL; name = node_name; };
	leaf(int level_number, lexem *lexema) { lex = lexema; level = level_number; name = ""; };
	void delete_last_child() 
	{ 
		if (child.size() > 0)
			child.pop_back();
	};
	void set_node(int n_level, string n_name)
	{
		level = n_level;
		name = n_name;
	}
	void add_child(lexem *lexema)
	{
		child.push_back(leaf(level + 1, lexema));
	}
	void add_child(string name)
	{
		child.push_back(leaf(level + 1, name));
		lex = NULL;
	}
	leaf& get_child(int i)
	{
		if (i < child.size() && i >= 0)
			return child[i];
	}
	lexem get_lexem()
	{
		return *lex;
	}
	string get_node_name()
	{
		return name;
	}
	leaf& get_child_by_lexem(string lexem_name)
	{
		for (auto &i : child)
		{
			if (i.get_lexem().get_name() == lexem_name)
				return i;
			else
				i.get_child_by_lexem(lexem_name);
		}
	}
	bool search_for_lexem_name(string lexem_name)
	{
		for (auto &i : child)
		{
			if (i.get_lexem().get_name() == lexem_name)
				return true;
			else
				i.search_for_lexem_name(lexem_name);
		}
		return false;
	}
	leaf& get_child_if_tree_name(string tree_name, int i)
	{
		if (tree_name == name)
			return child[i];
	}
	void print_tree()
	{
		for (int i = 0; i < level; i++)
			cout << "..";
		if (lex != NULL)
			cout << lex->get_id() << "    " <<lex->get_name() << endl;
		else
			cout << name << endl;
		for (auto &i : child)
			i.print_tree();
	}
	void print_to_file(ostream &output)
	{
		for (int i = 0; i < level; i++)
			output << "|  ";
		if (lex != NULL)
			output << "|->" << lex->get_id() << "    " << lex->get_name() << endl;
		else
			output << "|->" << name << endl;
		for (auto &i : child)
			i.print_to_file(output);
	}
};

bool synt(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table);
bool _signal_program(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table);
bool _program(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table);
bool _procedure_identifier(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table);
bool _block(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table);
bool _declarations(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table);
bool _lable_declarations(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table);
bool _lables_list(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table);
bool _statments_list(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table);
bool _statment(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table);
bool _variable_identifier(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table);
bool _unsigned_integer(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table);
bool add_child_with_iteration(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table);