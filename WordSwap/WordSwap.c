#pragma warning(disable:4996) // dont alert error on unsafe call fopen
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

#define WRONG_ARGUMENTS (-1)
#define FILE_NOT_EXISTS (-2)
#define ERROR_IN_CODE (-3);
#define OUT_OF_MEMORY (-4);

/* returns array of split words in document*/
char ** split(char * fileName);
/* gets file and length and returns it as an array of chars*/
char * getWord(FILE * file, int wordLength);
/* get amount of words in file */
int getWordCount(char * fileName);
/* swap first file with words from the second file */
int swapWords(char * textFileName, char * wordFileName);
/* checks if word is in array if it is returns new word */
char * wordInArray(char * word, char ** wordList, int wordListLength);
/* copy temp to main file */
int copyFile(char * source, char * destination);

int main(int argc, char * argv[])
{
	/* check that 3 arguments where given */
	if (argc != 3) {
		printf("ERROR: not enough arguments\n");
		printf("Usage: swap words in file 1 from file 2\n");
		printf("       second file need to have a space between the 2 words\n");
		printf("       that are wanted to be swapped, each pair in a new line\n");
		return WRONG_ARGUMENTS;
	}
	int success = swapWords(argv[1], argv[2]);
	if (success != 0)
		return success;
	success = copyFile("temp.txt", argv[1]);
	return success;
}

int swapWords(char * textFileName, char * wordFileName)
{
	char ** newWords = split(wordFileName);
	if (newWords == NULL)
	{
		return FILE_NOT_EXISTS;
	}
	int swapLength = getWordCount(wordFileName);
	if (swapLength < 0)
		return swapLength;
	FILE * runner = fopen(textFileName, "r");/*runs on the file looks for words and their lengths*/
	FILE * original = fopen(textFileName, "r");/* after getting word either write back or swap */
	FILE * tempFile = fopen("temp.txt", "w");
	if (runner == NULL || original == NULL)
	{
		printf("file %s does not exist\n", textFileName);
		return FILE_NOT_EXISTS;
	}
	if (tempFile == NULL) {
		printf("error in code, contact creator\n");
		return ERROR_IN_CODE;
	}
	char c;
	int letterCounter = 0;
	int nonLetters = 1;
	int index = 0;
	do {
		/* see word length */
		do {
			c = fgetc(runner);
			if (isalpha(c))
				letterCounter++;
		} while (c != EOF && isalpha(c));
		/* see non letters word length in order to skip them */
		do {
			c = fgetc(runner);
			if (!isalpha(c))
				nonLetters++;
		} while (c != EOF && !isalpha(c));
		char * word = getWord(original, letterCounter);
		char * punctuation = getWord(original, nonLetters);
		char * tempWord = wordInArray(word, newWords, swapLength);
		if (word == NULL || punctuation == NULL)
		{
			printf("System out of memory\n");
			return OUT_OF_MEMORY;
		}
		if (tempWord != NULL)
		{
			fputs(tempWord, tempFile);
		}
		else
		{
			fputs(word, tempFile);
		}
		fputs(punctuation, tempFile);
		letterCounter = 1;
		nonLetters = 1;
		/* free mallocs */
		free(word);
		free(punctuation);
	} while (c != EOF);
	fclose(runner);
	fclose(original);
	fclose(tempFile);
	for (int i = 0; i < swapLength; i++)
		free(newWords[i]);
	free(newWords);
	return 0;
}
char ** split(char * fileName)
{
	FILE * splitter = fopen(fileName, "r");/*runs on the file looks for words and their lengths*/
	FILE * original = fopen(fileName, "r");
	if (splitter == NULL || original == NULL)
	{
		printf("file %s does not exist\n", fileName);
		return NULL;
	}
	int wordCount = getWordCount(fileName);
	if (wordCount < 1)
	{
		printf("no words in %s\n", fileName);
		return NULL;
	}
	char ** words = malloc(wordCount * sizeof(char*));
	if (words == NULL)
	{
		printf("System out of memory\n");
		return NULL;
	}
	char c;
	int letterCounter = 0;
	int nonLetters = 1;
	int index = 0;
	do {
		/* see word length */
		do {
			c = fgetc(splitter);
			if (isalpha(c))
				letterCounter++;
		} while (c != EOF && isalpha(c));
		/* see non letters word length in order to skip them */
		do {
			c = fgetc(splitter);
			if (!isalpha(c))
				nonLetters++;
		} while (c != EOF && !isalpha(c));
		char * word = getWord(original, letterCounter);
		for (int i = 0; i < nonLetters; i++)
		{
			fgetc(original);
		}
		words[index++] = word;
		letterCounter = 1;
		nonLetters = 1;
		//Cant free word here because i return an array that points at it
	} while (c != EOF);
	fclose(original);
	fclose(splitter);
	return words;
}

int getWordCount(char * fileName)
{
	FILE * file = fopen(fileName, "r");
	if (file == NULL)
	{
		printf("file %s does not exist\n", fileName);
		return FILE_NOT_EXISTS;
	}
	int wordCount = 0;
	char c;
	char temp = EOF;
	do {
		c = fgetc(file);
		if (isalpha(temp) && !isalpha(c))
			wordCount++;
		temp = c;
	} while (c != EOF);
	return wordCount;
}

char * getWord(FILE * file, int wordLength)
{
	char * word = malloc(wordLength + 1);
	if (word == NULL)
	{
		printf("System out of memory\n");
		return NULL;
	}
	fgets(word, wordLength + 1, file);
	return word;
}

char * wordInArray(char * word, char ** wordList, int wordListLength)
{
	for (int i = 0; i < wordListLength - 1; i += 2)
	{
		if (strcmp(word, wordList[i]) == 0)
			return wordList[i + 1];
	}
	return NULL;
}
int copyFile(char * source, char * destination)
{
	FILE * fSource = fopen(source, "r");
	FILE * fDest = fopen(destination, "w");
	if (fSource == NULL || fDest == NULL)
		return FILE_NOT_EXISTS;
	char c;

	while (EOF != (c = fgetc(fSource)))
	{
		fputc(c, fDest);
	}
	fclose(fSource);
	fclose(fDest);
	remove("temp.txt");
	return 0;
}