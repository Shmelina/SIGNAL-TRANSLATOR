#pragma once
#include "main.h"

struct ASCII_row 
{
private:
	int id;
	char symbol;
	int type;
public:
	ASCII_row(string s) { set_row(s); }
	int get_id() { return id; }
	char get_symbol() { return symbol; }
	int get_type() { return type; }
	void set_id(int i) { id = i; }
	void set_symbol(char s) { symbol = s; }
	void set_type(int t) { type = t; }
	void set_row(string s)
	{
		id = s[2];
		symbol = s[0];
		type = s[4];
	}
	void print_row() { cout << symbol << ';' << id << ';' << type << endl; }
};

char ASCII_type[128];