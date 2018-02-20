#ifndef __ISTEST_H__
#define __ISTEST_H__
#include "execute.h"

using namespace std;

class Test {
  public:
    void isTest(char* arr[512], bool &check_prev)
    {
        /* The purpose of this function is to use the test command along with
        various flags that may appear with any command entered in.
        We will use the S_ISREG and S_ISDIR macros along with stat()
        functionality to accomplish this further.
        */
        struct stat sb;
        string flag;
        flag = arr[1];

        if (flag != "-e" && flag != "-d" && flag != "-f")
        {
          if (arr[2] == '\0')
          {
            flag = "-e";

            // This checks if there is a slash before test and fixes it
            // i.e: [ /test/file/path ]
            string test = arr[1];
            string test2;
            if (test.at(0) == '/')
            {
              for (unsigned i = 0; i < test.size(); ++i)
              {
                test2.push_back(test.at(i));
              }
              arr[1] = (char *)test2.c_str();
            }
          }
          else
          {
            cout << "Error. Did not use -e, -d, or -f." <<endl;
            exit(1);
          }
        }

        if (flag == "-d")
        {
          // This checks if there is a slash before test and fixes it
          // i.e: [ /test/file/path ]
          string test = arr[2];
          string test2;
          if (test.at(0) == '/')
          {
            for (unsigned i = 0; i < test.size(); ++i)
            {
              test2.push_back(test.at(i));
            }
            arr[1] = (char *)test2.c_str();
          }
          if (stat(arr[2], & sb) == -1)
          {
            cout << "(False)" << endl;
            check_prev = false;
            return;
          }
          else
          {
            switch (sb.st_mode & S_IFMT)
            {
              case S_IFDIR: printf("(True)\n"); check_prev = true; break;
              default: printf("(False)\n"); check_prev = false; break;
            }
          }
        }
        else if (flag == "-f")
        {
          // This checks if there is a slash before test and fixes it
          // i.e: [ /test/file/path ]
          string test = arr[2];
          string test2;
          if (test.at(0) == '/')
          {
            for (unsigned i = 0; i < test.size(); ++i)
            {
              test2.push_back(test.at(i));
            }
            arr[1] = (char *)test2.c_str();
          }
          if (stat(arr[2], & sb) == -1)
          {
            cout << "(False)" << endl;
            check_prev = false;
            return;
          }
          else
          {
            switch (sb.st_mode & S_IFMT)
            {
              case S_IFREG: printf("(True)\n"); check_prev = true; break;
              default: printf("(False)\n"); check_prev = false; break;
            }
          }
        }
        else
        {
          if (arr[2] != '\0')
          {
            // This checks if there is a slash before test and fixes it
            // i.e: [ /test/file/path ]
            string test = arr[1];
            string test2;
            if (test.at(0) == '/')
            {
              for (unsigned i = 0; i < test.size(); ++i)
              {
                test2.push_back(test.at(i));
              }
              arr[2] = (char *)test2.c_str();
            }
          }
          if (arr[2] == '\0')
          {
            if (stat(arr[1], & sb) == -1)
            {
              cout << "(False)" << endl;
              check_prev = false;
              return;
            }
            else
            {
              switch (sb.st_mode & S_IFMT)
              {
                case S_IFREG: printf("(True)\n"); check_prev = true; break;
                case S_IFDIR: printf("(True)\n"); check_prev = true; break;
                default: printf("(False)\n"); check_prev = false; break;
              }
              return;
            }
          }
          if (stat(arr[2], & sb) == -1)
          {
            cout << "(False)" << endl;
            check_prev = false;
            return;
          }
          else
          {
            switch (sb.st_mode & S_IFMT)
            {
              case S_IFREG: printf("(True)\n"); check_prev = true; break;
              case S_IFDIR: printf("(True)\n"); check_prev = true; break;
              default: printf("(False)\n"); check_prev = false; break;
            }
          }
        }
        return;
    }
};


#endif
