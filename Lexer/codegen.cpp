#include "codegen.h"

void _generate_code(leaf& _tree, vector<error>& _error_table, ostream& _output, vector<lexem>& idents_table, vector<lexem>& predefined_idents, vector<lexem_row>& lexem_table)
{
	if (_check_for_semantic_errors(_tree, _error_table, idents_table, predefined_idents, lexem_table))
	{
		return;
	}
	else
	{
		return;
	}
}

bool _check_for_semantic_errors(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, vector<lexem_row>& lexem_table)
{
	if (_check_for_SE_program(_tree.get_child_if_tree_name("<signal-program>", 0), _error_table, idents_table, predefined_idents, lexem_table))
		return true;
	else
		return false;
}

bool _check_for_SE_program(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, vector<lexem_row>& lexem_table)
{
	string _program_identifier = _tree.get_child_if_tree_name("<program>", 1).get_child(0).get_lexem().get_name();
	if (search_in_table_by_id(predefined_idents, _tree.get_child_if_tree_name("<program>", 1).get_child(0).get_lexem().get_id()))
	{
		lexem_row& tmp = search_lexem_row_by_lexem(_tree.get_child(1).get_child(0).get_lexem(), lexem_table);
		_error_table.push_back(error(tmp.get_row_number(), tmp.get_collumn(), \
			"CODE GENERATOR ERROR#3002: Program identifier name is reserved in predefined identifiers '" + tmp.get_lexem_ptr()->get_name() + "' found on "));
		return true;
	}
	if (_chek_for_SE_statement_list(_tree.get_child_if_tree_name("<program>", 3).get_child_if_tree_name("<block>", 2), _error_table, idents_table, predefined_idents, _program_identifier, lexem_table))
		return true;
	else
		return false;
}

bool _chek_for_SE_statement_list(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, string _program_identifier, vector<lexem_row>& lexem_table)
{
	if (_tree.get_child_if_tree_name("<statments-list>", 0).get_node_name() == "<statment>")
	{
		if (_chek_for_SE_statement(_tree.get_child_if_tree_name("<statments-list>", 0), _error_table, idents_table, predefined_idents, _program_identifier, lexem_table))
		{
			return true;
		}
		else if (_chek_for_SE_statement_list(_tree.get_child_if_tree_name("<statments-list>", 1), _error_table, idents_table, predefined_idents, _program_identifier, lexem_table))
		{
			return true;
		}
		else
			return false;
	}
	else
	{
		return false;
	}
}

bool _chek_for_SE_statement(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, string _program_identifier, vector<lexem_row>& lexem_table)
{
	if (_tree.get_child(0).get_node_name() == "<unsigned-integer>")
	{
		if (_chek_for_SE_statement(_tree.get_child(2), _error_table, idents_table, predefined_idents, _program_identifier, lexem_table))
			return true;
		else
			return false;
	}
	else if (_tree.get_child(0).get_lexem().get_id() == 406)
	{
		if (_tree.get_child(1).get_child(0).get_lexem().get_name() == _program_identifier)
		{
			lexem_row& tmp = search_lexem_row_by_lexem(_tree.get_child(1).get_child(0).get_lexem(), lexem_table);
			_error_table.push_back(error(tmp.get_row_number(), tmp.get_collumn(), \
				"CODE GENERATOR ERROR#3001: Using program identifier name '" + tmp.get_lexem_ptr()->get_name() + "' found on "));
			return true;
		}
		else
			return false;
	}
	else
		return false;
}