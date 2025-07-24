#pragma once

// Used to store data about a symbol
typedef struct symbol
{
	char name[NAME_SIZE];
	int address;
} symbol;

// Pass 1 functions
void displaySymbolTable(struct symbol* symbolTable[]);
void initializeSymbolTable(struct symbol* symbolTable[]);
void insertSymbol(struct symbol* symbolTable[], char symbolName[], int symbolAddress);

// Pass 2 functions
int getSymbolAddress(struct symbol* symbolArray[], char* string);
