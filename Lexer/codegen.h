#pragma once
#include "main.h"
#include "synt.h"
#include "tables.h"

void _generate_code(leaf& _tree, vector<error>& _error_table, ostream& _output, vector<lexem>& idents_table, vector<lexem>& predefined_idents, vector<lexem_row>& lexem_table);
bool _check_for_semantic_errors(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, vector<lexem_row>& lexem_table, string& asm_code);
bool _check_for_SE_program(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, vector<lexem_row>& lexem_table, string& asm_code);
bool _chek_for_SE_statement_list(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, string _program_identifier, vector<lexem_row>& lexem_table, string& asm_code);
bool _chek_for_SE_statement(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, string _program_identifier, vector<lexem_row>& lexem_table, string& asm_code);
bool _chek_for_SE_lable_declarations(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, string _program_identifier, vector<lexem_row>& lexem_table, string& asm_code);
bool _chek_for_SE_lables_list(leaf& _tree, vector<error>& _error_table, vector<lexem>& idents_table, vector<lexem>& predefined_idents, string _program_identifier, vector<lexem_row>& lexem_table, string& asm_code);

