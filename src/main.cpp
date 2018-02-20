/*
#############
Neel Sethia
Brandon Lee
#############
*/

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <vector>
#include <cstring>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "EC.h"
#include "execute.h"

using namespace std;

int main(int argc, char* argv[])
{
	bool check_exit = false;

	do
	{
		prompt();

		char arr1[512];
		char arr2[512];
		int just_temp = 0;
		int sz = 0;
    vector<vector<char *> > cmd_list;
    vector<char *> temp_cmds;

		cin.getline(arr2,512);

		vector<string> vector_separator;
		vector<int> parenthesis;

		// Iterates through the input to locate if '#' exists
		for (unsigned i = 0; arr2[i] != '\0'; ++i)
		{
		  if (arr2[i] == '#')
		  {
			  strncpy(arr1, arr2, i);
			  arr1[i] = '\0';
			  break;
		  }
    	if (i == (strlen(arr2) - 1))
    	{
    		strncpy(arr1, arr2, (i + 1));
    		arr1[i + 1] = '\0';
    	}
    }
		int sepCount = 0;
		int parCount = 0;
		int parenCount = 0;
		for (unsigned i = 0; arr1[i] != '\0'; ++i)
		{
			if (arr1[i] == ';')
			{
				vector_separator.push_back(";");
				sepCount++;
			}
			if (arr1[i] == '&')
			{
				vector_separator.push_back("&&");
				i++;
				sepCount++;
			}
			if (arr1[i] == '|')
			{
				vector_separator.push_back("||");
				i++;
				sepCount++;
			}
			if (arr1[i] == '(')
			{
				parenthesis.push_back(sepCount + 1);
				parenthesis.push_back(sepCount + 1);
				parenCount++;
				parCount++;
			}
			if (arr1[i] == ')')
			{
				parenthesis.at((parCount * 2) - 1) = sepCount;
				parCount--;
				parenCount++;
			}
		}

    // Using the strtok, split the user input into tokens and store it
    // to a new vector;
    vector<char *> vector_command;
    char *pointer;

    pointer = strtok(arr1, "&|;");
    while (pointer != NULL)
    {
       vector_command.push_back(pointer);
       pointer = strtok(NULL, "&|;");
    }

		for (unsigned i = 0; i < vector_command.size(); ++i)
		{
			for (unsigned j = 0; vector_command.at(i)[j] != '\0'; ++j)
			{
				if (vector_command.at(i)[j] == '[')
				{
					vector_command.at(i)[j] = ' ';
				}
				if (vector_command.at(i)[j] == ']')
				{
					vector_command.at(i)[j] = ' ';

					for (unsigned k = 0; vector_command.at(i)[k] != '\0'; k++)
					{
						sz++;
					}
					for (unsigned m = 0; m < 4; m++)
					{
						for (unsigned n = sz + 2; n > 0; --n)
						{
							vector_command.at(i)[n] = vector_command.at(i)[n - 1];
						}
					}
					vector_command.at(i)[sz + 3] = '\0';
					vector_command.at(i)[0] = 't';
					vector_command.at(i)[1] = 'e';
					vector_command.at(i)[2] = 's';
					vector_command.at(i)[3] = 't';
				}
			}
		}

		for (unsigned i = 0; i < vector_command.size(); i++)
		{
			for (unsigned j = 0; vector_command.at(i)[j] != '\0'; j++)
			{
				if( vector_command.at(i)[j] == '(')
				{
					for (unsigned k = j; vector_command.at(i)[k] != '\0'; k++)
					{
						vector_command.at(i)[k] = vector_command.at(i)[k + 1];
					}
				}
				if (vector_command.at(i)[j] == ')')
				{
					for (unsigned k = j; vector_command.at(i)[k] != '\0'; k++)
					{
						vector_command.at(i)[k] = vector_command.at(i)[k + 1];
					}
				}
				if (vector_command.at(i)[j] == '(')
				{
					for (unsigned k = j; vector_command.at(i)[k] != '\0'; k++)
					{
						vector_command.at(i)[k] = vector_command.at(i)[k + 1];
					}
				}
				if (vector_command.at(i)[j] == ')')
				{
					for (unsigned k = j; vector_command.at(i)[k] != '\0'; k++)
					{
						vector_command.at(i)[k] = vector_command.at(i)[k + 1];
					}
				}
			}
		}

    // Gets rid of quotations when echoing user input
    // i.e: echo "print" --> print (not "print")
    for (unsigned i = 0; i < vector_command.size(); ++i)
    {
        for (unsigned j = 0; vector_command.at(i)[j] != '\0'; ++j)
        {
            if (vector_command.at(i)[j] == '\"')
            {
                for (unsigned t = j; vector_command.at(i)[t] != '\0'; ++t)
                {
                    vector_command.at(i)[t] = vector_command.at(i)[t + 1];
   	            }
   	        }
   	    }
   	}
  	char *pointer2;
    for (unsigned i = 0; i < vector_command.size(); ++i)
    {
      pointer2 = strtok(vector_command.at(i), " \t\n");
      while (pointer2 != NULL)
      {
        temp_cmds.push_back(pointer2);
        pointer2 = strtok(NULL, " \t\n");
      }
      cmd_list.push_back(temp_cmds);

      temp_cmds.clear();
    }
		if ((parCount % 2) == 0)
		{
			Execute te;
	    te.isExecute(vector_separator, cmd_list, check_exit, just_temp, parenthesis);
		}
		else
		{
			cout << "Error: odd numbers of parentheses." << endl;
		}
    // Clears the vectors, arrays, pointers
    for (unsigned i = 0; i < 256; ++i)
    {
      arr1[i] = '\0';
      arr2[i] = '\0';
    }
    vector_command.clear();
    vector_separator.clear();
    pointer = NULL;
    cmd_list.clear();
    temp_cmds.clear();
		parenthesis.clear();

	}while (!check_exit);

	return 0;
}
