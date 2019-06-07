#pragma once
#include "main.h"
#include "synt.h"
#include "tables.h"

struct i_table
{
private:
	string var;
	string val;
public:
	i_table(string variable, string value) { var = variable; val = value; }
	string get_var() { return var; };
	string get_val() { return val; };
	void set_val(string value) { val = value; };
};

void fill_IOports_from_file(ifstream& IOports, vector<i_table>* IOports_table);
string search_value_by_name(vector<i_table>& IOports_table, string name);
void print_i_table_to_file(vector<i_table>& table, ofstream& file);

void _generate_code(leaf& _tree, vector<error>& _error_table, ostream& _output, vector<lexem>& idents_table, vector<lexem>& predefined_idents, vector<lexem_row>& lexem_table, vector<i_table>& links_table, vector<i_table>& lables_table, vector<i_table>& IOports_table);
void _check_for_semantic_errors(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, vector<lexem_row>& lexem_table, string& asm_code, vector<i_table>& links_table, vector<i_table>& lables_table, vector<i_table>& IOports_table);
void _check_for_SE_program(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, vector<lexem_row>& lexem_table, string& asm_code, vector<i_table>& links_table, vector<i_table>& lables_table, vector<i_table>& IOports_table);
void _chek_for_SE_statement_list(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, string _program_identifier, vector<lexem_row>& lexem_table, string& asm_code, vector<i_table>& links_table, vector<i_table>& lables_table, vector<i_table>& IOports_table);
void _chek_for_SE_statement(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, string _program_identifier, vector<lexem_row>& lexem_table, string& asm_code, vector<i_table>& links_table, vector<i_table>& lables_table, vector<i_table>& IOports_table);
void _chek_for_SE_lable_declarations(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, string _program_identifier, vector<lexem_row>& lexem_table, string& asm_code, vector<i_table>& lables_table);
void _chek_for_SE_lables_list(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, string _program_identifier, vector<lexem_row>& lexem_table, string& asm_code, vector<i_table>& lables_table);
void _chek_for_SE_statement_list_lables(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, string _program_identifier, vector<lexem_row>& lexem_table, string& asm_code, vector<i_table>& links_table, vector<i_table>& lables_table, vector<i_table>& IOports_table);
void _chek_for_SE_statement_lables(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, string _program_identifier, vector<lexem_row>& lexem_table, string& asm_code, vector<i_table>& links_table, vector<i_table>& lables_table, vector<i_table>& IOports_table);
