#include "main.h"
#include "tables.h"

string comment(ifstream *t_file, char *ch, string line)
{
	*ch = (char)t_file->get();
	while ((*ch != '*') && (*ch != EOF))
	{
		cout << *ch;
		*ch = (char)t_file->get();
		while (*ch == '*')
		{
			cout << *ch;
			*ch = (char)t_file->get();
			if (*ch == ')')
			{
				cout << *ch;
				cout << "comment";
				return 0;
			}
			if (*ch == EOF)
			{
				cout << "ERROR";
				return 0;
			}
		}
	}
	cout << "ERROR";
}

int main()
{
	setlocale(LC_ALL, "ukr");
	string filename;
	cout << "File name: ";
	//cin >> filename;
	filename = "p";
	filename += ".sim";
	ifstream t_file;
	t_file.open(filename);
	ifstream iden_table;
	iden_table.open("identifiers.txt");
	ifstream separ_table;
	separ_table.open("separators.txt");
	ifstream keyword_table;
	keyword_table.open("keyword.txt");
	ifstream ASCII_table;
	ASCII_table.open("ASCII.txt");
	ofstream lex_row;
	lex_row.open("Lexems.data");
	vector<ASCII_row> ASCII_tab;
	char ch;
	if (!t_file.is_open())
	{
		cout << "File" << filename << " couldn`t be open, or doesn`t exists." << endl;
		system("pause");
		return 0;
	}
	/*for (int i = 0; i < 128; i++)
	{
		if (i >= 0 && i < 8)
			ASCII_table << 6;
		else if (i >= 8 && i < 40)
			ASCII_table << 0;
		else if (i >= 40 && i < 48)
			ASCII_table << 5;
		else if (i >= 48 && i < 58)
			ASCII_table << 1;
		else if (i >= 58 && i < 60)
			ASCII_table << 3;
		else if (i >= 60 && i < 62)
			ASCII_table << 7;
		else if (i >= 62 && i < 65)
			ASCII_table << 8;
		else if (i >= 65 && i < 128)
			ASCII_table << 2;

	}*/
	string line;
	for (int id = 0; id < 128; id++)
	{
		ASCII_table.get(ch);
		ASCII_type[id] = ch;
	}
	ch = (char)t_file.get();
	isalpha(line[0]);
	bool f = false;
	bool coment = false;
	while (ch != EOF)
	{
		if(!f)
			cout << ch;
		f = false;
		switch (ASCII_type[(int)ch])
		{
		case '2':
		{
			while (ASCII_type[(int)ch] == '2' || ASCII_type[(int)ch] == '1')
			{
				ch = (char)t_file.get();
				cout << ch;
				f = true;
			}
			cout << "ident";
			break;
		}
		case '1':
		{
			while (ASCII_type[(int)ch] == '1')
			{
				ch = (char)t_file.get();
				cout << ch;
				f = true;
			}
			if (ASCII_type[(int)ch] == '2')
				cout << "ERROR";
			cout << "num";
			break;
		}
		case '3':
		{
			cout << "separ";
			break;
		}
		case '0':
		{
			while (ASCII_type[(int)ch] == '0')
			{
				ch = (char)t_file.get();
				cout << ch;
				f = true;
			}
			cout << "WS";
			break;
		}
		case '5':
		{
			ch = (char)t_file.get();
			if (ch == '*')
			{
				cout << ch;
				//comment(&t_file, &ch, line);
				ch = (char)t_file.get();
				while (!coment)
				{
					while ((ch != '*') && (ch != EOF))
					{
						cout << ch;
						ch = (char)t_file.get();
						while (ch == '*')
						{
							cout << ch;
							ch = (char)t_file.get();
							if (ch == ')')
							{
								cout << ch;
								cout << "comment";
								coment = true;
								break;
							}
							if (ch == EOF)
							{
								cout << "ERROR1";
							}
						}
					}
					while (ch == '*')
					{
						cout << ch;
						ch = (char)t_file.get();
						if (ch == ')')
						{
							cout << ch;
							cout << "comment";
							coment = true;
							break;
						}
						if (ch == EOF)
						{
							cout << "ERROR1";
						}
					}
				}
				f = true;
			}
			else
			{
				cout << "ERROR2";
				break;
			}
			//cout << "comment";
			break;
		}
		case '6':
		{
			cout << "error/6";
			break;
		}
		//default: cout << ASCII_type[(int)ch];
		}
		if (!f)
			ch = (char)t_file.get();
	}
	cout << endl;
	/*for (int i = 0; i < 128; i++)
		cout << (char)i;
	cout << endl;
	for (int i = 0; i < 128; i++)
		cout << ASCII_type[i];*/
	t_file.close();
	cout << endl;
	system("pause");
	return 0;
}