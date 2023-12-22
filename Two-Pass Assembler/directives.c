#include "headers.h"

#define SINGLE_QUOTE 39

// List of valid directives
enum directives {
	// Although ERROR is not a valid directive, 
	// its presence helps the isDirective() function
	ERROR, BASE, BYTE, END, RESB, RESW, START
};

// Returns the value associated with a BYTE directive
int getByteValue(int directiveType, char* string)
{
    int value = 0;
    if (directiveType == BYTE)
    {
        if (strstr(string, "X'") != NULL)
        {
            const char* hexValue = strchr(string, '\'');
            if (hexValue != NULL)
            {
                hexValue++;
                value = strtol(hexValue, NULL, 16);
                return value;
            }
        }

        if (strstr(string, "C'") != NULL)
        {
            const char* charValue = strchr(string, '\'');
            if (charValue != NULL)
            {
                charValue++;
                char* endQuote = strchr(charValue, '\'');
                if (endQuote != NULL)
                {
                    int length = endQuote - charValue;
                    for (int i = 0; i < length; i++)
                    {
                        value = (value << 8) + charValue[i];
                    }
                    return value;
                }
            }
        }
    }
    return value;
}

// Returns the number of bytes required to store the BYTE directive value in memory
int getMemoryAmount(int directiveType, char* string)
{
	char hex[9] = { '\0' };
	int temp = 0;

	switch (directiveType)
	{
		case BASE:
		case END:
		case START:
			return 0;
			break;
		case BYTE:
			if (string[0] == 'X')
			{
				if (strlen(string) != 5)
				{
					displayError(OUT_OF_RANGE_BYTE, string);
					exit(-1);
				}
				else
					return 1;
			}
			else if (string[0] == 'C')
				return strlen(string) - 3;
			break;
		case RESB:
			return strtol(string, NULL, 10);
			break;
		case RESW:
			return strtol(string, NULL, 10) * 3;
			break;
	}
	return -1; // Should not happen
}

// Returns true if the provided directive type is the BASE directive; otherwise, false
bool isBaseDirective(int directiveType)
{
	return (directiveType == BASE);
}

// Returns true if the provided directive type is the BYTE directive; otherwise, false
bool isDataDirective(int directiveType)
{
	return (directiveType == BYTE);
}

// Tests whether the provided string is a valid directive
// Returns true if string is valid directive; otherwise, false
int isDirective(char* string) 
{
	if (strcmp(string, "BASE") == 0) { return BASE; }
	else if (strcmp(string, "BYTE") == 0) { return BYTE; }
	else if(strcmp(string, "END") == 0) { return END; }
	else if (strcmp(string, "RESB") == 0) { return RESB; }
	else if (strcmp(string, "RESW") == 0) { return RESW; }
	else if (strcmp(string, "START") == 0) { return START; }
	else { return ERROR; }
}

// Returns true if the provided directive type is the END directive; otherwise, false
bool isEndDirective(int directiveType)
{
	return (directiveType == END);
}

// Returns true if the provided directive type is the RESB or RESW directive; otherwise, false
bool isReserveDirective(int directiveType)
{
	return ((directiveType == RESB) || (directiveType == RESW));
}

// Returns true if the provided directive type is the START directive; otherwise, false
bool isStartDirective(int directiveType)
{
	return (directiveType == START);
}