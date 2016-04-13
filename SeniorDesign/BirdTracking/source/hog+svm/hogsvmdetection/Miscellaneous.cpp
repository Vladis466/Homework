#include"Miscellaneous.h"

#include <stdio.h>
#include "stdlib.h"
#include <io.h>
#include "string.h"
void TraceTime()
{
	
}
char* getfolder(const char* filename, char* folder)
{
	if(filename == 0)
		return 0;
	int index = strlen(filename);
	index --;
	while(filename[index] == '\\' || filename[index] == '/')
	{
		index --;
	}
	for(int i = index; i >= 0; i --)
	{
		if((filename[i] != '\\' && filename[i + 1] == '\\') || (filename[i] != '/' && filename[i + 1] == '/'))
		{
			for(int j = 0; j <= i; j ++)
			{
				folder[j] = filename[j];
			}
			folder[i + 1] = 0;
			break;
		}
	}
	
	
	return folder;
}
char* getextension(const char* filename)
{
	static char ext[128];
	memset(ext,0,128);
	if(filename == 0)
		return 0;

	
	
	return ext;
}