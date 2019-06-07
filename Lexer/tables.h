#pragma once
#include "main.h"

struct lexem
{
private:
	string name;
	int type;
	int id;
	string value;
	bool is_printed;
public:
	lexem() { name = "undefined"; type = -1; id = -1; value = ""; is_printed = false; }
	lexem(string lexem_name, int lexem_type, int lexem_id, string lexem_value)
	{
		name = lexem_name; type = lexem_type; id = lexem_id; value = lexem_value;
	}
	void set_lexem(string lexem_name, int lexem_type, int lexem_id, string lexem_value)
	{
		name = lexem_name; type = lexem_type; id = lexem_id; value = lexem_value;
	}
	void print() { cout << name << "\t" << type << "\t" << id << endl; }
	void print_file(ostream& file) { file << name << "\t" << id << endl; }
	string get_name() { return name; }
	int get_type() { return type; }
	int get_id() { return id; }
	string get_value() { return value; }
	bool is_lexem(string lexem_name) { return (name == lexem_name); }
	bool is_lexem_id(int lexem_id) { return (id == lexem_id); }
};

struct lexem_row
{
private:
	lexem* lex;
	int id;
	int row;
	int collumn;
public:
	lexem_row(int lexem_id, int lexem_row_number, int lexem_collumn) { id = lexem_id; row = lexem_row_number; collumn = lexem_collumn; }
	lexem_row(lexem* lexema, int lexem_row_number, int lexem_collumn) { lex = lexema; id = lex->get_id(); row = lexem_row_number; collumn = lexem_collumn; }
	void print() { cout << id << "\t" << row << "\t" << collumn << endl; }
	int get_row_number() { return row; }
	int get_collumn() { return collumn; }
	int get_id() { return id; }
	void print_file(ostream& file) { file << id << "\t" << row << "\t" << collumn << endl; }
	lexem *get_lexem_ptr() { return lex; };
	void set_ptr(lexem *lexema) { lex = lexema; }
};

struct error
{
private:
	int row;
	int collumn;
	string name;
public:
	error(int row_number, int collumn_number, string error) { row = row_number; collumn = collumn_number; name = error; }
	void print()
	{
		cout << name << "(row " << row << ", line " << collumn << ")" << endl;
	}
};

void scanner(vector<lexem>& idents_table, vector<lexem>& const_t, vector<lexem>& keyw_table, vector<lexem>& predefined_idents, vector<error>& error_table,\
	vector<lexem>& predefined_consts, vector<lexem>& separators_table, vector<lexem_row>& lexem_table, ifstream& t_file, ifstream& ASCII_table);
bool search_in_table(vector<lexem> &lexem_table, string lexem_name, int &curr_id);
bool search_in_table_by_id(vector<lexem> &lexem_table, int id);
void fill_lexems_from_file(fstream &file, vector<lexem> *lexem_table, int type);
void fill_constants_from_file(fstream &file, vector<lexem> *lexem_table);
void print_lexem_table(vector<lexem>& lexem, ofstream& strem);
void print_lexem_row_table(vector<lexem_row>& lexem, ofstream& strem);
void p_lexem_row_table(vector<lexem_row>& lexem);
void p_lexem_table(vector<lexem>& lexem);
void print_errors(vector<error>& error_table);
lexem* get_lexem_ptr(vector<lexem> &lexem_table, int id);
void fill_ptr(vector<lexem>& idents_table, vector<lexem>& const_t, vector<lexem>& keyw_table, vector<lexem>& predefined_idents, vector<error>& error_table, \
	vector<lexem>& predefined_consts, vector<lexem>& separators_table, vector<lexem_row>& lexem_table);