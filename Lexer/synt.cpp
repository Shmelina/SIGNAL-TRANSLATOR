#include "tables.h"
#include "synt.h"

bool synt(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table)
{
	tree.set_node(0, "<signal-program>");
	if (_signal_program(lexem_table, tree, iterator, error_table))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool _signal_program(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table)
{
	tree.add_child("<program>");
	if (_program(lexem_table, tree.get_child(0), iterator, error_table))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool _program(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table)
{
	if (lexem_table[iterator].get_id() == 401)
	{
		if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
			return false;
		int i = 1;
		tree.add_child("<procedure-identifier>");
		if (_procedure_identifier(lexem_table, tree.get_child(i), iterator, error_table))
		{
			if (lexem_table[iterator].get_id() == 59)
			{
				if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
					return false;
				i = 3;
				tree.add_child("<block>");
				if (_block(lexem_table, tree.get_child(i), iterator, error_table))
				{
					if (lexem_table[iterator].get_id() == 46)
					{
						tree.add_child(lexem_table[iterator].get_lexem_ptr());
						return true;
					}
					else
					{
						error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
							"PARSER ERROR#2004: Dot expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
						return false;
					}
				}
				else
				{
					//tree.delete_last_child();
					return false;
				}
			}
			else
			{
				error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
					"PARSER ERROR#2003: Semicolon expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
				return false;
			}
		}
		else
		{
			if (iterator >= lexem_table.size())
				return false;
			error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
				"PARSER ERROR#2002: Procedure identifier expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
			tree.delete_last_child();
			return false;
		}
	}
	else
	{
		error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(),\
			"PARSER ERROR#2001: Keyword 'PROGRAM' expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
		return false;
	}
}

bool _procedure_identifier(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table)
{
	if (lexem_table[iterator].get_id() >= 1000)
	{
		if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
			return false;
		return true;
	}
	else
	{
		return false;
	}
}

bool _block(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table)
{
	int i = 0;
	tree.add_child("<declarations>");
	if (_declarations(lexem_table, tree.get_child(i), iterator, error_table))
	{
		if (lexem_table[iterator].get_id() == 403)
		{
			if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
				return false;
			i = 2;
			tree.add_child("<statments-list>");
			if (_statments_list(lexem_table, tree.get_child(i), iterator, error_table))
			{
				if (lexem_table[iterator].get_id() == 408)
				{
					 
					if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
						return false;
					return true;
				}
				else
				{
					error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
						"PARSER ERROR#2008: Keyword 'END' expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
					return false;
				}
			}
			else
			{
				tree.delete_last_child();
				return false;
			}
		}
		else
		{
			error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
				"PARSER ERROR#2007: Keywors 'BEGIN' expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
			return false;
		}
	}
	else
	{
		tree.delete_last_child();
		return false;
	}
}

bool _declarations(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table)
{
	int i = 0;
	tree.add_child("<lable-declarations>");
	if (_lable_declarations(lexem_table, tree.get_child(i), iterator, error_table))
	{
		return true;
	}
	else
	{
		tree.delete_last_child();
		return false;
	}
}

bool _lable_declarations(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table)
{
	if (lexem_table[iterator].get_id() == 403)
	{	 
		tree.add_child("<empty>");
		return true;
	}
	else if (lexem_table[iterator].get_id() == 402)
	{
		if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
			return false;
		int i = 1;
		tree.add_child("<unsigned-integer>");
		if (_unsigned_integer(lexem_table, tree.get_child(i), iterator, error_table))
		{	 
			i = 2;
			tree.add_child("<lables-list>");
			if (_lables_list(lexem_table, tree.get_child(i), iterator, error_table))
			{
				 
				if (lexem_table[iterator].get_id() == 59)
				{
					if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
						return false;
					return true;
				}
				else
				{
					error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
						"PARSER ERROR#2003: Semicolon expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
					return false;
				}
			}
			else
			{
				tree.delete_last_child();
				return false;
			}
		}
		else
		{
			if (iterator >= lexem_table.size())
				return false;
			error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
				"PARSER ERROR#2005: Unsigned integer expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
			tree.delete_last_child();
			return false;
		}
	}
	else
	{
		error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
			"PARSER ERROR#2009: Keyword 'LABEL' or empty lexem expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
		return false;
	}
}

bool _lables_list(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table)
{
	if (lexem_table[iterator].get_id() == 59)
	{
		tree.add_child("<empty>");
		return true;
	}
	else if (lexem_table[iterator].get_id() == 44)
	{
		if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
			return false;
		int i = 1;
		tree.add_child("<unsigned-integer>");
		if (_unsigned_integer(lexem_table, tree.get_child(i), iterator, error_table))
		{
			i = 2;
			tree.add_child("<lables-list>");
			if (_lables_list(lexem_table, tree.get_child(i), iterator, error_table))
			{
				return true;
			}
			else
			{
				tree.delete_last_child();
				return false;
			}
		}
		else
		{
			if (iterator >= lexem_table.size())
				return false;
			error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
				"PARSER ERROR#2005: Unsigned integer expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
			tree.delete_last_child();
			return false;
		}
	}
	else
	{
		error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
			"PARSER ERROR#2010: Comma or empty lexem expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
		return false;
	}
}

bool _statments_list(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table)
{
	int i = 0;
	tree.add_child("<statment>");
	if (lexem_table[iterator].get_id() == 408)
	{
		tree.delete_last_child();
		tree.add_child("<empty>");
		return true;
	}
	else if (_statment(lexem_table, tree.get_child(i), iterator, error_table))
	{
		i = 1;
		tree.add_child("<statments-list>");
		if (_statments_list(lexem_table, tree.get_child(i), iterator, error_table))
		{
			return true;
		}
		else
		{
			tree.delete_last_child();
			return false;
		}
	}
	else
	{
		if (iterator >= lexem_table.size())
			return false;
		error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
			"PARSER ERROR#2011: Statment or empty lexem expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
		tree.delete_last_child();
		return false;
	}
}

bool _statment(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table)
{
	int i = 0;
	tree.add_child("<unsigned-integer>");
	if (_unsigned_integer(lexem_table, tree.get_child(i), iterator, error_table))
	{
		if (lexem_table[iterator].get_id() == 58)
		{
			if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
				return false;
			i = 2;
			tree.add_child("<statment>");
			if (_statment(lexem_table, tree.get_child(i), iterator, error_table))
			{
				return true;
			}
			else
			{ 
				tree.delete_last_child();
				return false;
			}
		}
		else
		{
			error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
				"PARSER ERROR#2012: Colon expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
			return false;
		}
	}
	else if (lexem_table[iterator].get_id() == 405)
	{
		if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
			return false;
		tree.add_child("<unsigned-integer>");
		i = 1;
		if (_unsigned_integer(lexem_table, tree.get_child(i), iterator, error_table))
		{ 
			if (lexem_table[iterator].get_id() == 59)
			{ 
				if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
					return false;
				return true;
			}
			else
			{
				error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
					"PARSER ERROR#2003: Semicolon expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
				return false;
			}
		}
		else
		{
			if (iterator >= lexem_table.size())
				return false;
			error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
				"PARSER ERROR#2005: Unsigned integer expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
			tree.delete_last_child();
			return false;
		}
	}
	else if (lexem_table[iterator].get_id() == 406)
	{
		if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
			return false;
		tree.add_child("<variable-identifier>");
		i = 1;
		if (_variable_identifier(lexem_table, tree.get_child(i), iterator, error_table))
		{
			if (lexem_table[iterator].get_id() == 44)
			{
				if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
					return false;
				tree.add_child("<unsigned-integer>");
				i = 3;
				if (_unsigned_integer(lexem_table, tree.get_child(i), iterator, error_table))
				{
					if (lexem_table[iterator].get_id() == 59)
					{
						if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
							return false;
						return true;
					}
					else
					{
						error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
							"PARSER ERROR#2003: Semicolon expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
						return false;
					}
				}
				else
				{
					if (iterator >= lexem_table.size())
						return false;
					error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
						"PARSER ERROR#2005: Unsigned integer expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
					tree.delete_last_child();
					return false;
				}
			}
			else
			{
				error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
					"PARSER ERROR#20010: Comma expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
				return false;
			}
		}
		else
		{
			if (iterator >= lexem_table.size())
				return false;
			error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
				"PARSER ERROR#2006: Variable identifier expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
			tree.delete_last_child();
			return false;
		}
	}
	else if (lexem_table[iterator].get_id() == 404)
	{ 
		if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
			return false;
		tree.add_child("<unsigned-integer>");
		i = 1;
		if (_unsigned_integer(lexem_table, tree.get_child(i), iterator, error_table))
		{
			if (lexem_table[iterator].get_id() == 59)
			{
				if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
					return false;
				return true;
			}
			else
			{
				error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
					"PARSER ERROR#2003: Semicolon expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
				return false;
			}
		}
		else
		{
			if (iterator >= lexem_table.size())
				return false;
			error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
				"PARSER ERROR#2005: Unsigned integer expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
			tree.delete_last_child();
			return false;
		}
	}
	else if (lexem_table[iterator].get_id() == 407)
	{
		if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
			return false;
		tree.add_child("<unsigned-integer>");
		i = 1;
		if (_unsigned_integer(lexem_table, tree.get_child(i), iterator, error_table))
		{ 
			if (lexem_table[iterator].get_id() == 59)
			{ 
				if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
					return false;
				return true;
			}
			else
			{
				error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
					"PARSER ERROR#2003: Semicolon expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
				return false;
			}
		}
		else
		{
			if (iterator >= lexem_table.size())
				return false;
			error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
				"PARSER ERROR#2005: Unsigned integer expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
			tree.delete_last_child();
			return false;
		}
	}
	else
	{
		if (iterator >= lexem_table.size())
			return false;
		error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
			"PARSER ERROR#2013: Unsigned integer or empty lexem or Keywords 'GOTO' or 'LINK' or 'IN' or 'OUT' expected but '" \
			+ lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
		tree.delete_last_child();
		return false;
	}
}

bool _variable_identifier(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table)
{
	if (lexem_table[iterator].get_id() >= 1000)
	{
		if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
			return false;
		return true;
	}
	else
	{
		return false;
	}
}

bool _unsigned_integer(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table)
{
	if (lexem_table[iterator].get_id() >= 500 and lexem_table[iterator].get_id() < 1000)
	{
		if (!add_child_with_iteration(lexem_table, tree, iterator, error_table))
			return false;
		return true;
	}
	else
	{
		return false;
	}
}

bool add_child_with_iteration(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table)
{
	tree.add_child(lexem_table[iterator].get_lexem_ptr());
	iterator++;
	if (iterator >= lexem_table.size())
	{
		error_table.push_back(error(lexem_table[iterator - 1].get_row_number(), lexem_table[iterator - 1].get_collumn(), \
			"PARSER ERROR#2000: Unexepted end of code. Last lexem '" + lexem_table[iterator - 1].get_lexem_ptr()->get_name() + "' found on "));
		return false;
	}
	return true;
}