/* CS261- Assignment 1 - Q.5*/
/* Name: Vlad Predovic Kevin Sliker
 * Date: 4/7/2015
 * Solution description: Prompts the user for a word
 * and then converts it to studly caps.
 * Visual Studio 2013
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently
preconditions:  the character
postconditions : none.*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently
preconditions:  the character
postconditions : none.*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

/*function which feeds values into our caps converters
through the use of for loops.
preconditions:  the character array pointer
postconditions : none.*/
void studly(char* word){
     /*Convert to studly caps*/
	for (int i = 0; i < strlen(word); i++){
		if (i % 2 == 0){
			if (word[i] >= 'a' && word[i] <= 'z'){   //had to look this up. I'm surprised it will pick up the caps lock like this.
				word[i] = toUpperCase(word[i]);
			}
		}
		else{
			if (word[i] >= 'A' && word[i] <= 'Z'){
				word[i] = toLowerCase(word[i]);
			}
		}
	}
}

int main(){
    /*Read word from the keyboard using scanf*/
	char word[100];
	printf("Enter a word: ");
	scanf("%79s", word);
    /*Call studly*/
	studly(word);
    /*Print the new word*/
	printf("Take your new word!! %s\n ", word);
    return 0;
}
