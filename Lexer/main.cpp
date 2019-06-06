#include "main.h"
#include "tables.h"
#include "synt.h"
#include "codegen.h"

int main()
{
	setlocale(LC_ALL, "ukr");
	string filename, fname;
	cout << "File name: ";
	cin >> fname;
	filename = fname + ".sim";
	ifstream t_file;
	t_file.open(filename);
	ifstream IOports;
	IOports.open("IOports.txt");
	fstream ident_table;
	ident_table.open("identifiers.txt");
	fstream const_table;
	const_table.open("constants.txt");
	ofstream separ_table;
	separ_table.open("separators.txt");
	fstream keyword_table;
	keyword_table.open("keyword.txt");
	ifstream ASCII_table;
	ASCII_table.open("ASCII.txt");
	ofstream lex_row;
	lex_row.open("lexem_row.txt");
	ofstream lex_table;
	lex_table.open("idents_table.txt");
	ofstream constants_table;
	constants_table.open("constants_table.txt");
	ofstream asm_code;
	asm_code.open(fname + ".asm");
	ofstream tree_file;
	tree_file.open("tree.txt");
	vector<lexem> idents_table;
	vector<lexem> const_t;
	vector<lexem> keyw_table;
	vector<lexem> predefined_idents;
	vector<lexem> predefined_consts;
	vector<lexem> separators_table;
	vector<error> error_table;
	vector<lexem_row> lexem_table;
	leaf tree;

	fill_lexems_from_file(ident_table, &predefined_idents, 2);
	fill_lexems_from_file(keyword_table, &keyw_table, 4);
	fill_constants_from_file(const_table, &predefined_consts);

	ident_table.close();
	keyword_table.close();
	const_table.close();

	if (!t_file.is_open())
	{
		cout << "File" << filename << " couldn`t be open, or doesn`t exists." << endl;
		system("pause");
		return 0;
	}

	scanner(idents_table, const_t, keyw_table, predefined_idents, error_table, predefined_consts, separators_table, lexem_table, t_file, ASCII_table);
	
	if (lexem_table.size() == 0)
	{
		cout << "File" << filename << " is empty." << endl;
		system("pause");
		return 0;
	}

	print_lexem_row_table(lexem_table, lex_row);
	print_lexem_table(const_t, constants_table);
	print_lexem_table(idents_table, lex_table);
	print_lexem_table(separators_table, separ_table);

	char ch;
	while (true)
	{
		cout << "Print tables? Y/N: ";
		cin >> ch;
		if (ch == 'Y' or ch == 'y')
		{
			cout << "Lexem row:" << endl;
			p_lexem_row_table(lexem_table);
			cout << endl;
			cout << "Const table:" << endl;
			p_lexem_table(const_t);
			cout << endl;
			cout << "Identifier table:" << endl;
			p_lexem_table(idents_table);
			cout << endl;
			cout << "Separator table:" << endl;
			p_lexem_table(separators_table);
			cout << endl;
			break;
		}
		else if (ch == 'N' or ch == 'n')
		{
			ch = ' ';
			break;
		}
		else
			cout << "Wrong choise." << endl;
	}

	ASCII_table.close();
	lex_row.close();
	lex_table.close();
	constants_table.close();
	t_file.close();

	int tree_iter = 0;
	synt(lexem_table, tree, tree_iter, error_table);

	while (true)
	{
		cout << "Print syntaxis tree? Y/N: ";
		cin >> ch;
		if (ch == 'Y' or ch == 'y')
		{
			tree.print_tree();
			break;
		}
		else if (ch == 'N' or ch == 'n')
		{
			ch = ' ';
			break;
		}
		else
			cout << "Wrong choise." << endl;
	}

	if (error_table.size() == 0)
		_generate_code(tree, error_table, asm_code, idents_table, predefined_idents, lexem_table);

	print_errors(error_table);
	tree.print_to_file(tree_file);
	system("pause");
	return 0;
}