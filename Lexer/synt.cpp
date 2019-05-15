#include "tables.h"
#include "synt.h"

bool synt(vector<lexem_row>& lexem_table, leaf& tree, int& iterator)
{
	tree.set_node(0, "<signal-program>");
	if (_signal_program(lexem_table, tree, iterator))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool _signal_program(vector<lexem_row>& lexem_table, leaf& tree, int& iterator)
{
	tree.add_child("<program>");
	if (_program(lexem_table, tree.get_child(0), iterator))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool _program(vector<lexem_row>& lexem_table, leaf& tree, int& iterator)
{
	if (lexem_table[iterator].get_id() == 401)
	{
		tree.add_child(lexem_table[iterator].get_lexem_ptr());
		iterator++;
		int i = 1;
		tree.add_child("<procedure-identifier>");
		if (_procedure_identifier(lexem_table, tree.get_child(i), iterator))
		{
			if (lexem_table[iterator].get_id() == 59)
			{
				tree.add_child(lexem_table[iterator].get_lexem_ptr());
				iterator++;
				i = 3;
				tree.add_child("<block>");
				if (_block(lexem_table, tree.get_child(i), iterator))
				{
					if (lexem_table[iterator].get_id() == 46)
					{
						tree.add_child(lexem_table[iterator].get_lexem_ptr());
						return true;
					}
					else
					{
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
		return false;
	}
}



bool _procedure_identifier(vector<lexem_row>& lexem_table, leaf& tree, int& iterator)
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

bool _block(vector<lexem_row>& lexem_table, leaf& tree, int& iterator)
{
	int i = 0;
	tree.add_child("<declarations>");
	if (_declarations(lexem_table, tree.get_child(i), iterator))
	{
		if (lexem_table[iterator].get_id() == 403)
		{
			tree.add_child(lexem_table[iterator].get_lexem_ptr());
			iterator++;
			i = 2;
			tree.add_child("<statments-list>");
			if (_statments_list(lexem_table, tree.get_child(i), iterator))
			{
				if (lexem_table[iterator].get_id() == 408)
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
			else
			{
				tree.delete_last_child();
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		tree.delete_last_child();
		return false;
	}
}

bool _declarations(vector<lexem_row>& lexem_table, leaf& tree, int& iterator)
{
	int i = 0;
	tree.add_child("<lable-declarations>");
	if (_lable_declarations(lexem_table, tree.get_child(i), iterator))
	{
		return true;
	}
	else
	{
		tree.delete_last_child();
		return false;
	}
}

bool _lable_declarations(vector<lexem_row>& lexem_table, leaf& tree, int& iterator)
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
		if (_unsigned_integer(lexem_table, tree.get_child(i), iterator))
		{	 
			i = 2;
			tree.add_child("<lables-list>");
			if (_lables_list(lexem_table, tree.get_child(i), iterator))
			{
				 
				if (lexem_table[iterator].get_id() == 59)
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
			else
			{
				tree.delete_last_child();
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
		return false;
	}
}

bool _lables_list(vector<lexem_row>& lexem_table, leaf& tree, int& iterator)
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
		if (_unsigned_integer(lexem_table, tree.get_child(i), iterator))
		{
			i = 2;
			tree.add_child("<lables-list>");
			if (_lables_list(lexem_table, tree.get_child(i), iterator))
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
			tree.delete_last_child();
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool _statments_list(vector<lexem_row>& lexem_table, leaf& tree, int& iterator)
{
	int i = 0;
	tree.add_child("<statment>");
	if (lexem_table[iterator].get_id() == 408)
	{
		tree.delete_last_child();
		tree.add_child("<empty>");
		return true;
	}
	else if (_statment(lexem_table, tree.get_child(i), iterator))
	{
		i = 1;
		tree.add_child("<statments-list>");
		if (_statments_list(lexem_table, tree.get_child(i), iterator))
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
		tree.delete_last_child();
		return false;
	}
}

bool _statment(vector<lexem_row>& lexem_table, leaf& tree, int& iterator)
{
	int i = 0;
	tree.add_child("<unsigned-integer>");
	if (_unsigned_integer(lexem_table, tree.get_child(i), iterator))
	{
		if (lexem_table[iterator].get_id() == 58)
		{
			tree.add_child(lexem_table[iterator].get_lexem_ptr());
			iterator++;
			i = 2;
			tree.add_child("<statment>");
			if (_statment(lexem_table, tree.get_child(i), iterator))
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
		if (_unsigned_integer(lexem_table, tree.get_child(i), iterator))
		{ 
			if (lexem_table[iterator].get_id() == 59)
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
		else
		{
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
		if (_variable_identifier(lexem_table, tree.get_child(i), iterator))
		{
			if (lexem_table[iterator].get_id() == 44)
			{
				tree.add_child(lexem_table[iterator].get_lexem_ptr());
				iterator++;
				tree.add_child("<unsigned-integer>");
				i = 3;
				if (_unsigned_integer(lexem_table, tree.get_child(i), iterator))
				{
					if (lexem_table[iterator].get_id() == 59)
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
				else
				{
					tree.delete_last_child();
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
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
		if (_unsigned_integer(lexem_table, tree.get_child(i), iterator))
		{
			if (lexem_table[iterator].get_id() == 59)
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
		else
		{
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
		if (_unsigned_integer(lexem_table, tree.get_child(i), iterator))
		{ 
			if (lexem_table[iterator].get_id() == 59)
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
		else
		{
			tree.delete_last_child();
			return false;
		}
	}
	else
	{
		tree.delete_last_child();
		return false;
	}
}

bool _variable_identifier(vector<lexem_row>& lexem_table, leaf& tree, int& iterator)
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

bool _unsigned_integer(vector<lexem_row>& lexem_table, leaf& tree, int& iterator)
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