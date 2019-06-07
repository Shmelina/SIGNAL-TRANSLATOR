#include "codegen.h"

void _generate_code(leaf& _tree, vector<error>& _error_table, ostream& _output, vector<lexem>& idents_table, vector<lexem>& predefined_idents, vector<lexem_row>& lexem_table, vector<i_table>& links_table, vector<i_table>& lables_table, vector<i_table>& IOports_table)
{
	string asm_code = "";
	_check_for_semantic_errors(_tree, _error_table, idents_table, predefined_idents, lexem_table, asm_code, links_table, lables_table, IOports_table);
	_output << asm_code;
	return;
}

void _check_for_semantic_errors(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, vector<lexem_row>& lexem_table, string& asm_code, vector<i_table>& links_table, vector<i_table>& lables_table, vector<i_table>& IOports_table)
{
	_check_for_SE_program(_tree.get_child_if_tree_name("<signal-program>", 0), _error_table, idents_table, predefined_idents, lexem_table, asm_code, links_table, lables_table, IOports_table);
	return;
}

void _check_for_SE_program(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, vector<lexem_row>& lexem_table, string& asm_code, vector<i_table>& links_table, vector<i_table>& lables_table, vector<i_table>& IOports_table)
{
	string _program_identifier = _tree.get_child_if_tree_name("<program>", 1).get_child(0).get_lexem().get_lexem_ptr()->get_name();
	asm_code += _program_identifier + " SEGMENT\n";
	if (search_in_table_by_id(predefined_idents, _tree.get_child_if_tree_name("<program>", 1).get_child(0).get_lexem().get_id()))
	{
		_error_table.push_back(error(_tree.get_child(1).get_child(0).get_lexem().get_row_number(), _tree.get_child(1).get_child(0).get_lexem().get_collumn(), \
			"CODE GENERATOR ERROR#3002: Program identifier name is reserved in predefined identifiers '" + _tree.get_child(1).get_child(0).get_lexem().get_lexem_ptr()->get_name() + "' found on "));
		return;
	}
	if (_tree.get_child_if_tree_name("<program>", 3).get_child_if_tree_name("<block>", 0).get_child_if_tree_name("<declarations>", 0).get_child_if_tree_name("<lable-declarations>", 0).get_node_name() != "<empty>")
		_chek_for_SE_lable_declarations(_tree.get_child_if_tree_name("<program>", 3).get_child_if_tree_name("<block>", 0).get_child_if_tree_name("<declarations>", 0), _error_table, idents_table, predefined_idents, _program_identifier, lexem_table, asm_code, lables_table);
	
	_chek_for_SE_statement_list(_tree.get_child_if_tree_name("<program>", 3).get_child_if_tree_name("<block>", 2), _error_table, idents_table, predefined_idents, _program_identifier, lexem_table, asm_code, links_table, lables_table, IOports_table);
	asm_code += _program_identifier + " ENDS";
	return;
}

void _chek_for_SE_lable_declarations(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, string _program_identifier, vector<lexem_row>& lexem_table, string& asm_code, vector<i_table>& lables_table)
{
	string _lable = _tree.get_child_if_tree_name("<lable-declarations>", 1).get_child(0).get_lexem().get_lexem_ptr()->get_name();
	lables_table.push_back(i_table(_lable, "D"));
	asm_code += "LABEL " + _lable + "\n";
	if(_tree.get_child_if_tree_name("<lable-declarations>", 2).get_node_name() == "<lables-list>")
		_chek_for_SE_lables_list(_tree.get_child_if_tree_name("<lable-declarations>", 2), _error_table, idents_table, predefined_idents, _program_identifier, lexem_table, asm_code, lables_table);
	return;
}

void _chek_for_SE_lables_list(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, string _program_identifier, vector<lexem_row>& lexem_table, string& asm_code, vector<i_table>& lables_table)
{
	if (_tree.get_child_if_tree_name("<lables-list>", 0).get_node_name() == "<empty>")
		return;
	string _lable = _tree.get_child_if_tree_name("<lables-list>", 1).get_child(0).get_lexem().get_lexem_ptr()->get_name();
	bool found = false;
	for(auto &_l : lables_table)
		if (_l.get_var() == _lable)
		{
			_error_table.push_back(error(_tree.get_child_if_tree_name("<lables-list>", 1).get_child(0).get_lexem().get_row_number(), _tree.get_child_if_tree_name("<lables-list>", 1).get_child(0).get_lexem().get_collumn(), \
				"CODE GENERATOR ERROR#3003: Redeclaration of label '" + _tree.get_child_if_tree_name("<lables-list>", 1).get_child(0).get_lexem().get_lexem_ptr()->get_name() + "' found on "));
			found = true;
		}
	if (!found)
	{
		asm_code += "LABEL " + _lable + "\n";
		lables_table.push_back(i_table(_lable, "D"));
	}
	if (_tree.get_child_if_tree_name("<lables-list>", 2).get_node_name() == "<lables-list>")
		_chek_for_SE_lables_list(_tree.get_child_if_tree_name("<lables-list>", 2), _error_table, idents_table, predefined_idents, _program_identifier, lexem_table, asm_code, lables_table);
	return;
}

void _chek_for_SE_statement_list(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, string _program_identifier, vector<lexem_row>& lexem_table, string& asm_code, vector<i_table>& links_table, vector<i_table>& lables_table, vector<i_table>& IOports_table)
{
	if (_tree.get_child_if_tree_name("<statments-list>", 0).get_node_name() == "<empty>")
		asm_code += "\tNOP\n";
	if (_tree.get_child_if_tree_name("<statments-list>", 0).get_node_name() == "<statment>")
	{
		_chek_for_SE_statement(_tree.get_child_if_tree_name("<statments-list>", 0), _error_table, idents_table, predefined_idents, _program_identifier, lexem_table, asm_code, links_table, lables_table, IOports_table);
		_chek_for_SE_statement_list(_tree.get_child_if_tree_name("<statments-list>", 1), _error_table, idents_table, predefined_idents, _program_identifier, lexem_table, asm_code, links_table, lables_table, IOports_table);
		return;
	}
	else
	{
		return;
	}
}

void _chek_for_SE_statement(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, string _program_identifier, vector<lexem_row>& lexem_table, string& asm_code, vector<i_table>& links_table, vector<i_table>& lables_table, vector<i_table>& IOports_table)
{
	if (_tree.get_child(0).get_node_name() == "<unsigned-integer>")
	{
		string _lable = _tree.get_child(0).get_child(0).get_lexem().get_lexem_ptr()->get_name();
		lables_table.push_back(i_table(_lable, "C"));
		asm_code += _lable + ":\n";
		_chek_for_SE_statement(_tree.get_child(2), _error_table, idents_table, predefined_idents, _program_identifier, lexem_table, asm_code, links_table, lables_table, IOports_table);
		return;
	}
	else if (_tree.get_child(0).get_lexem().get_id() == 406)
	{
		string link_var = _tree.get_child(1).get_child(0).get_lexem().get_lexem_ptr()->get_name();
		string link_val = _tree.get_child(3).get_child(0).get_lexem().get_lexem_ptr()->get_name();
		bool found = false;
		if (link_var == _program_identifier)
		{
			_error_table.push_back(error(_tree.get_child(1).get_child(0).get_lexem().get_row_number(), _tree.get_child(1).get_child(0).get_lexem().get_collumn(), \
				"CODE GENERATOR ERROR#3001: Using program identifier name '" + link_var + "' found on "));
			return;
		}
		for (auto &p : IOports_table)
			if (p.get_var() == link_val)
			{
				found = true;
				break;
			}
		if (found)
		{
			asm_code += "\t;;LINK " + link_var + ", " + link_val + "\n";
			return;
		}
		else
		{
			_error_table.push_back(error(_tree.get_child(3).get_child(0).get_lexem().get_row_number(), _tree.get_child(3).get_child(0).get_lexem().get_collumn(), \
				"CODE GENERATOR ERROR#3005: Port '" + link_val + "' is not declared found on "));
			return;
		}
	}
	else if (_tree.get_child(0).get_lexem().get_id() == 405)
	{
		string link_var = _tree.get_child(1).get_child(0).get_lexem().get_lexem_ptr()->get_name();
		bool f = false;
		for(auto &link : lables_table)
			if (link.get_var() == link_var && link.get_val() == "C")
			{
				f = true;
				break;
			}
		if (!f)
			if (!_tree.search_for_lexem_name(link_var))
			{
				_error_table.push_back(error(_tree.get_child(1).get_child(0).get_lexem().get_row_number(), _tree.get_child(1).get_child(0).get_lexem().get_collumn(), \
					"CODE GENERATOR ERROR#3004: Using undeclared link '" + _tree.get_child(1).get_child(0).get_lexem().get_lexem_ptr()->get_name() + "' found on "));
				return;
			}
			else
			{
				asm_code += "\tJMP " + link_var + "\n";
				return;
			}
		else
		{
			asm_code += "\tJMP " + link_var + "\n";
			return;
		}
	}
	else if (_tree.get_child(0).get_lexem().get_id() == 404)
	{
		string port = _tree.get_child(1).get_child(0).get_lexem().get_lexem_ptr()->get_name();
		string port_purp;
		bool found = false;
		for (auto &p : IOports_table)
			if (p.get_var() == port)
			{
				port_purp = p.get_val();
				found = true;
				break;
			}
		if (found)
		{
			if (port_purp == "I")
			{
				asm_code += "\t;;IN " + port + "\n";
			}
			else if (port_purp == "O")
			{
				_error_table.push_back(error(_tree.get_child(1).get_child(0).get_lexem().get_row_number(), _tree.get_child(1).get_child(0).get_lexem().get_collumn(), \
					"CODE GENERATOR ERROR#3006: Port '" + port + "' is not for input found on "));
			}
			else
			{
				for (auto &p : IOports_table)
					if (p.get_var() == port)
					{
						p.set_val("I");
						break;
					}
				asm_code += "\t;;IN " + port + "\n";
			}
		}
		else
		{
			_error_table.push_back(error(_tree.get_child(1).get_child(0).get_lexem().get_row_number(), _tree.get_child(1).get_child(0).get_lexem().get_collumn(), \
				"CODE GENERATOR ERROR#3005: Port '" + port + "' is not declared found on "));
		}
		return;
	}
	else if (_tree.get_child(0).get_lexem().get_id() == 407)
	{
		string port = _tree.get_child(1).get_child(0).get_lexem().get_lexem_ptr()->get_name();
		string port_purp;
		bool found = false;
		for (auto &p : IOports_table)
			if (p.get_var() == port)
			{
				port_purp = p.get_val();
				found = true;
				break;
			}
		if (found)
		{
			if (port_purp == "I")
			{
				_error_table.push_back(error(_tree.get_child(1).get_child(0).get_lexem().get_row_number(), _tree.get_child(1).get_child(0).get_lexem().get_collumn(), \
					"CODE GENERATOR ERROR#3007: Port '" + port + "' is not for output found on "));
			}
			else if (port_purp == "O")
			{
				asm_code += "\t;;OUT " + port + "\n";
			}
			else
			{
				for (auto &p : IOports_table)
					if (p.get_var() == port)
					{
						p.set_val("O");
						break;
					}
				asm_code += "\t;;OUT " + port + "\n";
			}
		}
		else
		{
			_error_table.push_back(error(_tree.get_child(1).get_child(0).get_lexem().get_row_number(), _tree.get_child(1).get_child(0).get_lexem().get_collumn(), \
				"CODE GENERATOR ERROR#3005: Port '" + port + "' is not declared found on "));
		}
		return;
	}
	else
		return;
}

void fill_IOports_from_file(ifstream& IOports, vector<i_table>* IOports_table)
{
	string name, value;
	while (!IOports.eof())
	{
		IOports >> name >> value;
		IOports_table->push_back(i_table(name, value));
	}
}

string search_value_by_name(vector<i_table>& IOports_table, string name)
{
	for (auto &rec : IOports_table)
		if (rec.get_var() == name)
			return rec.get_val();
	return NULL;
}