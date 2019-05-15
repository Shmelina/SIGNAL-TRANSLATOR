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
		tree.add_child(lexem_table[iterator].get_lexem_ptr());
		iterator++;
		int i = 1;
		tree.add_child("<procedure-identifier>");
		if (_procedure_identifier(lexem_table, tree.get_child(i), iterator, error_table))
		{
			if (lexem_table[iterator].get_id() == 59)
			{
				tree.add_child(lexem_table[iterator].get_lexem_ptr());
				iterator++;
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
					tree.delete_last_child();
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
		tree.add_child(lexem_table[iterator].get_lexem_ptr());
		iterator++;
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
			tree.add_child(lexem_table[iterator].get_lexem_ptr());
			iterator++;
			i = 2;
			tree.add_child("<statments-list>");
			if (_statments_list(lexem_table, tree.get_child(i), iterator, error_table))
			{
				if (lexem_table[iterator].get_id() == 408)
				{
					 
					tree.add_child(lexem_table[iterator].get_lexem_ptr());
					iterator++;
					return true;
				}
				else
				{
					error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
						"PARSER ERROR#2003: Keyword 'END' expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
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
				"PARSER ERROR#2003: Keywors 'BEGIN' expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
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
		tree.add_child(lexem_table[iterator].get_lexem_ptr());
		iterator++;
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
					tree.add_child(lexem_table[iterator].get_lexem_ptr());
					iterator++;
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
			error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
				"PARSER ERROR#2005: Unsigned integer expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
			tree.delete_last_child();
			return false;
		}
	}
	else
	{
		error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
			"PARSER ERROR#2003: Keyword 'LABEL' or empty lexem expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
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
		tree.add_child(lexem_table[iterator].get_lexem_ptr());
		iterator++;
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
			error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
				"PARSER ERROR#2005: Unsigned integer expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
			tree.delete_last_child();
			return false;
		}
	}
	else
	{
		error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
			"PARSER ERROR#2005: Comma or empty lexem expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
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
		error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
			"PARSER ERROR#2005: Statment or empty lexem expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
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
			tree.add_child(lexem_table[iterator].get_lexem_ptr());
			iterator++;
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
				"PARSER ERROR#2006: Colon expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
			return true;
		}
	}
	else if (lexem_table[iterator].get_id() == 405)
	{
		tree.delete_last_child();
		tree.add_child(lexem_table[iterator].get_lexem_ptr());
		iterator++;
		tree.add_child("<unsigned-integer>");
		i = 1;
		if (_unsigned_integer(lexem_table, tree.get_child(i), iterator, error_table))
		{ 
			if (lexem_table[iterator].get_id() == 59)
			{ 
				tree.add_child(lexem_table[iterator].get_lexem_ptr());
				iterator++;
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
			error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
				"PARSER ERROR#2005: Unsigned integer expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
			tree.delete_last_child();
			return false;
		}
	}
	else if (lexem_table[iterator].get_id() == 406)
	{
		tree.delete_last_child();
		tree.add_child(lexem_table[iterator].get_lexem_ptr());
		iterator++;
		tree.add_child("<variable-identifier>");
		i = 1;
		if (_variable_identifier(lexem_table, tree.get_child(i), iterator, error_table))
		{
			if (lexem_table[iterator].get_id() == 44)
			{
				tree.add_child(lexem_table[iterator].get_lexem_ptr());
				iterator++;
				tree.add_child("<unsigned-integer>");
				i = 3;
				if (_unsigned_integer(lexem_table, tree.get_child(i), iterator, error_table))
				{
					if (lexem_table[iterator].get_id() == 59)
					{
						tree.add_child(lexem_table[iterator].get_lexem_ptr());
						iterator++;
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
					error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
						"PARSER ERROR#2005: Unsigned integer expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
					tree.delete_last_child();
					return false;
				}
			}
			else
			{
				error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
					"PARSER ERROR#2008: Comma expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
				return false;
			}
		}
		else
		{
			error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
				"PARSER ERROR#2006: Variable identifier expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
			tree.delete_last_child();
			return false;
		}
	}
	else if (lexem_table[iterator].get_id() == 404)
	{ 
		tree.delete_last_child();
		tree.add_child(lexem_table[iterator].get_lexem_ptr());
		iterator++;
		tree.add_child("<unsigned-integer>");
		i = 1;
		if (_unsigned_integer(lexem_table, tree.get_child(i), iterator, error_table))
		{
			if (lexem_table[iterator].get_id() == 59)
			{
				tree.add_child(lexem_table[iterator].get_lexem_ptr());
				iterator++;
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
			error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
				"PARSER ERROR#2005: Unsigned integer expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
			tree.delete_last_child();
			return false;
		}
	}
	else if (lexem_table[iterator].get_id() == 407)
	{
		tree.delete_last_child();
		tree.add_child(lexem_table[iterator].get_lexem_ptr());
		iterator++;
		tree.add_child("<unsigned-integer>");
		i = 1;
		if (_unsigned_integer(lexem_table, tree.get_child(i), iterator, error_table))
		{ 
			if (lexem_table[iterator].get_id() == 59)
			{ 
				tree.add_child(lexem_table[iterator].get_lexem_ptr());
				iterator++;
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
			error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
				"PARSER ERROR#2005: Unsigned integer expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
			tree.delete_last_child();
			return false;
		}
	}
	else
	{
		error_table.push_back(error(lexem_table[iterator].get_row_number(), lexem_table[iterator].get_collumn(), \
			"PARSER ERROR#2007: Unsigned integer or Keywords 'GOTO' or 'LINK' or 'IN' or 'OUT' expected but '" + lexem_table[iterator].get_lexem_ptr()->get_name() + "' found on "));
		tree.delete_last_child();
		return false;
	}
}

bool _variable_identifier(vector<lexem_row>& lexem_table, leaf& tree, int& iterator, vector<error>& error_table)
{
	if (lexem_table[iterator].get_id() >= 1000)
	{
		tree.add_child(lexem_table[iterator].get_lexem_ptr());
		iterator++;
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
		tree.add_child(lexem_table[iterator].get_lexem_ptr());
		iterator++;
		return true;
	}
	else
	{
		return false;
	}

}