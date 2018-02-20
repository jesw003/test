#ifndef EXECUTE_H
#define EXECUTE_H

#include <cstring>
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
//#include <boost/algorithm/string.hpp>

#include "istest.h"

using namespace std;

class Execute
{
  public:
    //runs the execution where certain conditions will be handled such as various commands that may
    // be entered
    void Execution(vector<string> separators, vector<vector<char *> > cmds, bool & exit_check, bool & check_previous, string previous, string exit1, string test, int flag_check, vector<int> & parenthesis, int exit_loop)
    {
      for (unsigned i = 0; i < separators.size() + 1; ++i)
      {
        if (exit_loop > 0)
        {
          return;
        }
        //input stored in temp arr
      	char *temp_arr[512];
        memset(temp_arr, '\0', sizeof(temp_arr));

        if (separators.size() != 0)
        {
          if (i != 0)
          {
          	previous = separators.at(i - 1);
          }
        }

        if (check_previous)
        {
        	if (previous == ";")
          {
      			for (unsigned hh = 0; hh < cmds.at(i).size(); ++hh)
          	{
          		temp_arr[hh] = const_cast<char *>(cmds.at(i).at(hh));
          	}
          	if (strcmp(temp_arr[0], exit1.c_str()) == 0)
          	{
          		exit_check = true;
          	  exit(0);
              return;
            }
            // ============= TEST ==============
            if (strcmp(temp_arr[0], test.c_str()) == 0)
            {
              //cout << "Dumm1" << endl;
              Test icle;
              icle.isTest(temp_arr, check_previous);
            }
            // ==================================

            else
            {
              if (flag_check > 0)
              {
                if (parenthesis.size() != 0)
                {
                  int start = parenthesis.at(0);
                  int end = parenthesis.at(1);
                  int paren_size = parenthesis.size();

                  if (paren_size == 2)
                  {
                    parenthesis.pop_back();
                    parenthesis.pop_back();
                  }
                  else
                  {
                    for (unsigned i = 0; i + 2 < paren_size; ++i)
                    {
                      parenthesis.at(i) = parenthesis.at(i + 2);
                    }
                    parenthesis.pop_back();
                    parenthesis.pop_back();
                  }
                  vector<string> new_connector;
                  for (unsigned i = start - 1; i < end; ++i)
                  {
                    new_connector.push_back(separators.at(i));
                  }

                  vector<vector<char *> > new_cmd;
                  for (unsigned i = start - 1; i < end; ++i)
                  {
                    new_cmd.push_back(cmds.at(i));
                  }

                  int new_check = 0;
                  isExecute(new_connector, new_cmd, exit_check, new_check, parenthesis);
                  if (exit_check)
                  {
                    exit(0);
                  }

                }
              }

              if (strcmp(temp_arr[0], "cd") == 0)
              {
                char newDirectory[512];
                char currDirectory[512];

                if (getcwd(currDirectory,512) == NULL)
                {
                  perror("Get current working directory failed.");
                }
                setenv("PWD", currDirectory, 1);
                if (temp_arr[1] == '\0')
                {
                  strcpy(newDirectory, getenv("HOME"));
                }
                else if (strcmp(temp_arr[1], "-") == 0)
                {
                  strcpy(newDirectory, getenv("OLDPWD"));
                }
                else
                {
                  strcpy(newDirectory, temp_arr[1]);
                }
                errno = 0;
                chdir(newDirectory);
                if (errno > 0 || errno < 0)
          			{
          				perror("Error");
          			}
          			else if (errno == 0)
          			{
          				if (strcmp(currDirectory, newDirectory) != 0)
          				{
          					setenv("OLDPWD", currDirectory, 1);
          				}
          				setenv("PWD", newDirectory, 1);
          			}
              }

      				pid_t PID = fork();
      				pid_t PARENT;

      				if (PID < 0)
      				{
                //cout << "exedum1" << endl;
      					perror("Error Occurred\n");
      					exit(-1);
      				}
              else if (PID != 0)
              {
                if ((PARENT = wait(NULL)) < 0)
                {
                  perror("Waiting Error");
                  exit(-1);
                }
              }
      				else
      				{
      					check_previous = true;
      					int run = execvp(temp_arr[0], temp_arr);
                //TODO:
                //cout << run << endl;
      					if (run < 0)
      					{
                  //cout << "exedum" << endl;
      						perror("Error Occurred\n");
      						check_previous = false;

                  if (separators.at(0) == "&&")
                  {
                    if (parenthesis.size() != 0)
                    {
                      if (parenthesis.at(0) != 1)
                      {
                        if (check_previous == false)
                        {
                          cmds.clear();
                          separators.clear();
                          exit_loop++;
                          return;
                        }
                      }
                    }
                  }
      					}
      				}
            }
    			}
          else if (previous == "&&")
          {
            //cout << previous << endl;
            for (unsigned hh = 0; hh < cmds.at(i).size(); ++hh)
            {
              temp_arr[hh] = const_cast<char *>(cmds.at(i).at(hh));
            }
            if (strcmp(temp_arr[0], exit1.c_str()) == 0)
            {
              exit_check = true;
              return;
            }
            //from below, will check if any test functionality is called
            // ===== TEST
            if (strcmp(temp_arr[0], test.c_str()) == 0)
            {
              //cout << "dumm2" << endl;
              Test icle;
              icle.isTest(temp_arr, check_previous);
              return;
            }
            // =====
            else
            {
              if (flag_check > 0)
              {
                if (parenthesis.size() != 0)
                {
                  int start = parenthesis.at(0);
                  int end = parenthesis.at(1);
                  int paren_size = parenthesis.size();

                  if (paren_size == 2)
                  {
                    parenthesis.pop_back();
                    parenthesis.pop_back();
                  }
                  else
                  {
                    for (unsigned i = 0; i + 2 < paren_size; ++i)
                    {
                      parenthesis.at(i) = parenthesis.at(i + 2);
                    }
                    parenthesis.pop_back();
                    parenthesis.pop_back();
                  }
                  vector<string> new_connector;
                  for (unsigned i = start - 1; i < end; ++i)
                  {
                    new_connector.push_back(separators.at(i));
                  }

                  vector<vector<char *> > new_cmd;
                  for (unsigned i = start - 1; i < end; ++i)
                  {
                    new_cmd.push_back(cmds.at(i));
                  }

                  int new_check = 0;
                  isExecute(new_connector, new_cmd, exit_check, new_check, parenthesis);
                  if (exit_check)
                  {
                    exit(0);
                  }
                }
              }
            }
            if (strcmp(temp_arr[0], "cd") == 0)
            {
              char newDirectory[512];
              char currDirectory[512];

              if (getcwd(currDirectory,512) == NULL)
              {
                perror("Get current working directory failed.");
              }
              setenv("PWD", currDirectory, 1);
              if (temp_arr[1] == '\0')
              {
                strcpy(newDirectory, getenv("HOME"));
              }
              else if (strcmp(temp_arr[1], "-") == 0)
              {
                strcpy(newDirectory, getenv("OLDPWD"));
              }
              else
              {
                strcpy(newDirectory, temp_arr[1]);
              }
              errno = 0;
              chdir(newDirectory);
              if (errno > 0 || errno < 0)
              {
                perror("Error");
              }
              else if (errno == 0)
              {
                if (strcmp(currDirectory, newDirectory) != 0)
                {
                  setenv("OLDPWD", currDirectory, 1);
                }
                setenv("PWD", newDirectory, 1);
              }
            }

            pid_t PID = fork();
            pid_t PARENT;

            if (PID < 0)
            {
              //cout << "piderrr" << endl;
              perror("Error Occurred\n");
              exit(-1);
            }
            else if (PID != 0)
            {
              if ((PARENT = wait(NULL)) < 0)
              {
                perror("Waiting Error");
                exit(-1);
              }
            }
            else
            {
              check_previous = true;
              int run = execvp(temp_arr[0], temp_arr);
              if (run < 0)
              {
                //cout << "belpid" << endl;
                perror("Error Occurred\n");
                check_previous = false;

                if (separators.at(0) == "&&")
                {
                  if (parenthesis.size() != 0)
                  {
                    if (parenthesis.at(0) > 1)
                    {
                      if (check_previous == true)
                      {
                        cmds.clear();
                        separators.clear();
                        exit_loop++;
                        return;
                      }
                    }
                  }
                }
              }
            }
          }
          else if (previous == "||")
          {
            check_previous = true;
            if (parenthesis.size() == 2)
            {
              return;
            }
          }

        }
    		else
    		{
    			if (previous == ";")
    			{
    				for (unsigned hh = 0; hh < cmds.at(i).size(); ++hh)
    				{
    					temp_arr[hh] = const_cast<char *>(cmds.at(i).at(hh));
    				}
    				if (strcmp(temp_arr[0], exit1.c_str()) == 0)
    				{
    					exit_check = true;
    					return;
    				}
            if (strcmp(temp_arr[0], test.c_str()) == 0)
            {
              //cout << "dumm3" << endl;
              Test icle;
              icle.isTest(temp_arr, check_previous);
              return;
            }
            else
            {
              if (flag_check > 0)
              {
                if (parenthesis.size() != 0)
                {
                  int start = parenthesis.at(0);
                  int end = parenthesis.at(1);
                  int paren_size = parenthesis.size();

                  if (paren_size == 2)
                  {
                    parenthesis.pop_back();
                    parenthesis.pop_back();
                  }
                  else
                  {
                    for (unsigned i = 0; i + 2 < paren_size; ++i)
                    {
                      parenthesis.at(i) = parenthesis.at(i + 2);
                    }
                    parenthesis.pop_back();
                    parenthesis.pop_back();
                  }
                  vector<string> new_connector;
                  for (unsigned i = start - 1; i < end; ++i)
                  {
                    new_connector.push_back(separators.at(i));
                  }

                  vector<vector<char *> > new_cmd;
                  for (unsigned i = start - 1; i < end; ++i)
                  {
                    new_cmd.push_back(cmds.at(i));
                  }

                  int new_check = 0;
                  isExecute(new_connector, new_cmd, exit_check, new_check, parenthesis);
                  if (exit_check)
                  {
                    exit(0);
                  }
                }
              }

              if (strcmp(temp_arr[0], "cd") == 0)
              {
                char newDirectory[512];
                char currDirectory[512];

                if (getcwd(currDirectory,512) == NULL)
                {
                  perror("Get current working directory failed.");
                }
                setenv("PWD", currDirectory, 1);
                if (temp_arr[1] == '\0')
                {
                  strcpy(newDirectory, getenv("HOME"));
                }
                else if (strcmp(temp_arr[1], "-") == 0)
                {
                  strcpy(newDirectory, getenv("OLDPWD"));
                }
                else
                {
                  strcpy(newDirectory, temp_arr[1]);
                }
                errno = 0;
                chdir(newDirectory);
                if (errno > 0 || errno < 0)
          			{
          				perror("Error");
          			}
          			else if (errno == 0)
          			{
          				if (strcmp(currDirectory, newDirectory) != 0)
          				{
          					setenv("OLDPWD", currDirectory, 1);
          				}
          				setenv("PWD", newDirectory, 1);
          			}
              }


              pid_t PID = fork();
      				pid_t PARENT;

      				if (PID < 0)
      				{
                //cout << "pid2" << endl;
      					perror("Error Occurred\n");
      					exit(-1);
      				}
              else if (PID != 0)
              {
                if ((PARENT = wait(NULL)) < 0)
                {
                  perror("Waiting Error");
                  exit(-1);
                }
              }
      				else
      				{
      					check_previous = true;
      					int run = execvp(temp_arr[0], temp_arr);
      					if (run < 0)
      					{
                  //cout << "belpid2" << endl;
      						perror("Error Occurred\n");
      						check_previous = false;
      					}
      				}
            }
    			}
          else if (previous == "&&")
          {
              check_previous = false;
              if (parenthesis.size() == 2)
              {
                exit(0);
                return;
              }
          }

          else if (previous == "||")
          {
            for (unsigned hh = 0; hh < cmds.at(i).size(); ++hh)
            {
              temp_arr[hh] = const_cast<char *>(cmds.at(i).at(hh));
            }
            if (strcmp(temp_arr[0], exit1.c_str()) == 0)
            {
              exit_check = true;
              return;
            }

            if (strcmp(temp_arr[0], test.c_str()) == 0)
            {
              //cout << "dumm4" << endl;
              Test icle2;
              icle2.isTest(temp_arr, check_previous);
              return;
            }
            else
            {
              if (flag_check > 0)
              {
                if (parenthesis.size() != 0)
                {
                  int start = parenthesis.at(0);
                  int end = parenthesis.at(1);
                  int paren_size = parenthesis.size();

                  if (paren_size == 2)
                  {
                    parenthesis.pop_back();
                    parenthesis.pop_back();
                  }
                  else
                  {
                    for (unsigned i = 0; i + 2 < paren_size; ++i)
                    {
                      parenthesis.at(i) = parenthesis.at(i + 2);
                    }
                    parenthesis.pop_back();
                    parenthesis.pop_back();
                  }
                  vector<string> new_connector;
                  for (unsigned i = start - 1; i < end; ++i)
                  {
                    new_connector.push_back(separators.at(i));
                  }

                  vector<vector<char *> > new_cmd;
                  for (unsigned i = start - 1; i < end; ++i)
                  {
                    new_cmd.push_back(cmds.at(i));
                  }

                  int new_check = 0;
                  isExecute(new_connector, new_cmd, exit_check, new_check, parenthesis);
                  if (exit_check)
                  {
                    exit(0);
                  }
                }
              }
            }
            if (strcmp(temp_arr[0], "cd") == 0)
            {
              char newDirectory[512];
              char currDirectory[512];

              if (getcwd(currDirectory,512) == NULL)
              {
                perror("Get current working directory failed.");
              }
              setenv("PWD", currDirectory, 1);
              if (temp_arr[1] == '\0')
              {
                strcpy(newDirectory, getenv("HOME"));
              }
              else if (strcmp(temp_arr[1], "-") == 0)
              {
                strcpy(newDirectory, getenv("OLDPWD"));
              }
              else
              {
                strcpy(newDirectory, temp_arr[1]);
              }
              errno = 0;
              chdir(newDirectory);
              if (errno > 0 || errno < 0)
              {
                perror("Error");
              }
              else if (errno == 0)
              {
                if (strcmp(currDirectory, newDirectory) != 0)
                {
                  setenv("OLDPWD", currDirectory, 1);
                }
                setenv("PWD", newDirectory, 1);
              }
            }
            pid_t PID = fork();
            pid_t PARENT;

            if (PID < 0)
            {
              //cout << "pid3" << endl;
              perror("Error Occurred\n");
              exit(-1);
            }
            else if (PID != 0)
            {
              if ((PARENT = wait(NULL)) < 0)
              {
                perror("Waiting Error");
                exit(-1);
              }
            }
            else
            {
              check_previous = true;
              int run = execvp(temp_arr[0], temp_arr);
              if (run < 0)
              {
                //cout << "again" << endl;
                  perror("Error Occurred\n");
                  check_previous = false;
              }
            }
          }
        }
      }
    }
    void isExecute(vector<string> separators, vector<vector<char *> > cmds, bool & exit_check, int flag_check, vector<int> & parenthesis)
    {
    	string previous = ";";
    	string exit1 = "exit";
      string clear = "clear";
      string test = "test";
      bool check_previous = true;
      int temp_clear = 0;

      int command_size = cmds.size();
      int separator_size = separators.size();
      bool size_valid = true;

      if (separators.size() == 0)
      {
        if (cmds.size() == 1)
        {
          // Checks if there is exit
          if (strcmp(exit1.c_str(), cmds.at(0).at(0)) == 0)
          {
            // this needs to exit the terminal
            exit_check = true;
            exit(0);
          }

          // Checks if there is clear
          if (cmds.at(0).size() == 0)
          {
            return;
          }
          else if (strcmp(clear.c_str(), cmds.at(0).at(0)) == 0)
          {
            temp_clear = 1;
          }
        }
      }

      if (command_size == 0)
      {
        if (separator_size != 0)
        {
          cout << "Error: No commands preceeding connector" << endl;
          size_valid = false;
        }
        else
        {
          return;
        }
      }
      if (command_size <= separator_size)
      {
        if (temp_clear != 1)
        {
          cout << "Error" << endl;
          return;
        }
      }
      int exit_loop = 0;
      if (size_valid)
      {
        Execution(separators, cmds, exit_check, check_previous, previous, exit1,
          test, flag_check, parenthesis, exit_loop);
      }
      if (exit_loop > 0)
      {
        return;
      }
    }
};

#endif
