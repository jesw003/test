#ifndef EC_H
#define EC_H

#include <iostream>
#include <cstdlib>

#include <unistd.h>

using namespace std;

//extra credit getlogin and hostname prompt, pretty self explanatory
void prompt(){
	char* name = getlogin();
	char* currPath = new char [512];
	string currPath_s;
	int positionHome;

	if (name == NULL)
	{
		cout << "Error: Cannot get login info." << endl;
		exit(1);
	}

	char hostname[256];

	int hostcheck = gethostname(hostname, 255);

	if(hostcheck == -1)
	{
		cout << "Error: Cannot get login info." << endl;
		exit(1);
	}

	if (getcwd(currPath, 100) == NULL)
	{
		perror("Error");
	}
	currPath_s = currPath;
	positionHome = currPath_s.find(getenv("HOME"));

	if (positionHome == 0)
	{
		currPath_s.replace(positionHome, strlen(getenv("HOME")), "~");
	}

	cout << name << "@" << hostname << ":" << currPath_s.c_str() << "$ ";
	delete[] currPath;

}

#endif
