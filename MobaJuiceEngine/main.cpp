#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

#include <iostream>
#include <SDL.h>
#include <GL\glew.h>
#include "Dictionary.h"
using namespace std;


int main(int argc, char *argv[]){
	Dictionary<int> dict;
	dict.SaveWithObject("number1", 1);
	return 0;
}