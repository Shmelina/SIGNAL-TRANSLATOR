#include "tables.h"

void scanner(vector<lexem>& idents_table, vector<lexem>& const_t, vector<lexem>& keyw_table, vector<lexem>& predefined_idents, vector<error>& error_table,\
	vector<lexem>& predefined_consts, vector<lexem>& separators_table, vector<lexem_row>& lexem_table, ifstream& t_file, ifstream& ASCII_table)
{
	char ASCII_type[128];
	char ch;
	int curr_id;
	string line;
	for (int id = 0; id < 128; id++)
	{
		ASCII_table.get(ch);
		ASCII_type[id] = ch;
	}
	ch = (char)t_file.get();
	bool f = false;
	bool coment = false;
	int row_number = 1;
	int collumn_number = 1;
	int collumn_started;
	int id = 0;
	int ident_id = predefined_idents[predefined_idents.size() - 1].get_id();
	int constant_id = predefined_consts[predefined_consts.size() - 1].get_id();
	while (ch != EOF)
	{
		line = "";
		f = false;
		coment = false;
		switch (ASCII_type[(int)ch])
		{
		case '2':
		{
			collumn_started = collumn_number;
			line += ch;
			while (ASCII_type[(int)ch] == '2' || ASCII_type[(int)ch] == '1')
			{
				ch = (char)t_file.get();
				line += ch;
				collumn_number++;
				f = true;
			}
			line.erase(line.end() - 1);
			if (!((search_in_table(idents_table, line, curr_id))
				or (search_in_table(predefined_idents, line, curr_id))
				or (search_in_table(keyw_table, line, curr_id))))
			{
				ident_id++;
				idents_table.push_back(lexem(line, 2, ident_id, ""));
				curr_id = ident_id;
			}
			lexem_table.push_back(lexem_row(curr_id, row_number, collumn_started));
			break;
		}
		case '1':
		{
			line += ch;
			collumn_started = collumn_number;
			while (ASCII_type[(int)ch] == '1')
			{
				ch = (char)t_file.get();
				line += ch;
				collumn_number++;
				f = true;
			}
			if (ASCII_type[(int)ch] == '2')
			{
				error_table.push_back(error(row_number, collumn_number, "LEXER ERROR#1003: Character after number on "));
				do
				{
					ch = (char)t_file.get();
					collumn_number++;
				} while (ASCII_type[(int)ch] == '2' or ASCII_type[(int)ch] == '1');
				break;
			}
			line.erase(line.end() - 1);
			if (!((search_in_table(const_t, line, curr_id))
				or (search_in_table(predefined_consts, line, curr_id))))
			{
				constant_id++;
				const_t.push_back(lexem(line, 1, constant_id, ""));
				curr_id = constant_id;
			}
			lexem_table.push_back(lexem_row(curr_id, row_number, collumn_started));
			break;
		}
		case '3':
		{
			line += ch;
			if (!(search_in_table(separators_table, line, curr_id)))
				separators_table.push_back(lexem(line, 3, (int)ch, ""));
			lexem_table.push_back(lexem_row(int(ch), row_number, collumn_number));
			break;
		}
		case '0':
		{
			if (ch == '\n')
			{
				row_number++;
				collumn_number = 0;
			}
			while (ASCII_type[(int)ch] == '0')
			{
				ch = (char)t_file.get();
				if (ch == '\n')
				{
					row_number++;
					collumn_number = 1;
				}
				else
					collumn_number++;
				f = true;
			}
			break;
		}
		case '5':
		{
			line += ch;
			collumn_started = collumn_number;
			ch = (char)t_file.get();
			collumn_number++;
			if (ch == '*')
			{
				line += ch;
				ch = (char)t_file.get();
				collumn_number++;
				while (!coment)
				{
					if (ch == EOF)
					{
						error_table.push_back(error(row_number, collumn_number, "LEXER ERROR#1001: Unexepted end of file or unclosed comment on "));
						break;
					}
					while ((ch != '*') && (ch != EOF))
					{
						line += ch;
						if (ch == '\n')
						{
							row_number++;
							collumn_number = 0;
						}
						ch = (char)t_file.get();
						collumn_number++;
						while (ch == '*')
						{
							line += ch;
							ch = (char)t_file.get();
							collumn_number++;
							if (ch == ')')
							{
								line += ch;
								coment = true;
								break;
							}
							if (ch == EOF)
							{
								coment = true;
								error_table.push_back(error(row_number, collumn_number, "LEXER ERROR#1001: Unexepted end of file or unclosed comment on "));
								break;
							}
						}
						if (coment)
							break;
					}
					if (coment)
						break;
					while (ch == '*')
					{
						line += ch;
						ch = (char)t_file.get();
						collumn_number++;
						if (ch == ')')
						{
							line += ch;
							coment = true;
							break;
						}
						if (ch == EOF)
						{
							coment = true;
							error_table.push_back(error(row_number, collumn_number, "LEXER ERROR#1001: Unexepted end of file or unclosed comment on "));
							break;
						}
					}
				}
			}
			else
			{
				error_table.push_back(error(row_number, collumn_number, "LEXER ERROR#1002: Character '*' is missing after '(' in commetn on "));
				break;
			}
			break;
		}
		case '6':
		{
			string s(1, ch);
			error_table.push_back(error(row_number, collumn_number, "LEXER ERROR#1006 Unavilable character:\t" + s + " on "));
			break;
		}
		default:
		{
			string s(1, ch);
			error_table.push_back(error(row_number, collumn_number, "LEXER ERROR#1006 Unavilable character:\t" + s + " on "));
			break;
		}
		}
		if (!f)
		{
			ch = (char)t_file.get();
			collumn_number++;
		}
	}

	fill_ptr(idents_table, const_t, keyw_table, predefined_idents, error_table, predefined_consts, separators_table, lexem_table);
}

void fill_lexems_from_file(fstream &file, vector<lexem> *lexem_table, int type)
{
	string name;
	int id;
	while (!file.eof())
	{
		file >> name >> id;
		lexem_table->push_back(lexem(name, type, id, ""));
	}
}

void fill_constants_from_file(fstream &file, vector<lexem> *lexem_table)
{
	string name;
	int id;
	string value;
	while (!file.eof())
	{
		file >> name >> id >> value;
		lexem_table->push_back(lexem(name, 3, id, value));
	}
}

bool search_in_table(vector<lexem> &lexem_table, string lexem_name, int &curr_id)
{
	for (int i = 0; i < lexem_table.size(); i++)
		if (lexem_table[i].is_lexem(lexem_name))
		{
			curr_id = lexem_table[i].get_id();
			return true;
		}
	return false;
}

bool search_in_table_by_id(vector<lexem> &lexem_table, int id)
{
	for (int i = 0; i < lexem_table.size(); i++)
		if (lexem_table[i].is_lexem_id(id))
			return true;
	return false;
}

lexem* get_lexem_ptr(vector<lexem> &lexem_table, int id)
{
	for (int i = 0; i < lexem_table.size(); i++)
		if (lexem_table[i].is_lexem_id(id))
			return &lexem_table[i];
}

void print_lexem_table(vector<lexem>& lexem, ofstream& strem)
{
	for (int i = 0; i < lexem.size(); i++)
		lexem[i].print_file(strem);
}

void print_lexem_row_table(vector<lexem_row>& lexem, ofstream& strem)
{
	for (int i = 0; i < lexem.size(); i++)
		lexem[i].print_file(strem);
}

void p_lexem_table(vector<lexem>& lexem)
{
	cout << "lexem" << "\t" << "type" << "\t" << "id" << endl;
	for (int i = 0; i < lexem.size(); i++)
		lexem[i].print();
}

void p_lexem_row_table(vector<lexem_row>& lexem)
{
	cout << "id" << "\t" << "row" << "\t" << "collumn" << endl;
	for (int i = 0; i < lexem.size(); i++)
		lexem[i].print();
}

void print_errors(vector<error>& error_table)
{
	for (int i = 0; i < error_table.size(); i++)
		error_table[i].print();
}

void fill_ptr(vector<lexem>& idents_table, vector<lexem>& const_t, vector<lexem>& keyw_table, vector<lexem>& predefined_idents, vector<error>& error_table, \
	vector<lexem>& predefined_consts, vector<lexem>& separators_table, vector<lexem_row>& lexem_table)
{
	for (auto &lexem : lexem_table)
	{
		int id = lexem.get_id();
		if (id > 0 and id <= 255)
			lexem.set_ptr(get_lexem_ptr(separators_table, id));
		else if (id > 400 and id <= 500)
			lexem.set_ptr(get_lexem_ptr(keyw_table, id));
		else if (id > 500 and id <= 1000)
		{
			if (search_in_table_by_id(const_t, id))
				lexem.set_ptr(get_lexem_ptr(const_t, id));
			else if (search_in_table_by_id(predefined_consts, id))
				lexem.set_ptr(get_lexem_ptr(predefined_consts, id));
		}
		else if (id > 1000)
		{
			if (search_in_table_by_id(idents_table, id))
				lexem.set_ptr(get_lexem_ptr(idents_table, id));
			else if (search_in_table_by_id(predefined_idents, id))
				lexem.set_ptr(get_lexem_ptr(predefined_idents, id));
		}
	}
}