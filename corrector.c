#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define NUM_PARAM 5
#define DICTIONARY_MAX_LENGTH 140
#define WORD_MAX_LENGTH 11
#define MAX_WORDS 30

int look_if_debug_mode(int argc, char ** argv);
int take_words(FILE *file, char text[DICTIONARY_MAX_LENGTH][WORD_MAX_LENGTH]);
void take_word_from_file(FILE *file, char word[WORD_MAX_LENGTH]);
void print_if_debug(int debug, const char *fmt, ...);
void print_string(const char *fmt, va_list args);
int word_appears_in(char *word, char dictionary[DICTIONARY_MAX_LENGTH][WORD_MAX_LENGTH], int length_of_d);
void find_correct_word(char word[WORD_MAX_LENGTH], char dictionary[DICTIONARY_MAX_LENGTH][WORD_MAX_LENGTH]);
int number_of_editions(char word[WORD_MAX_LENGTH], char corrected_word[WORD_MAX_LENGTH]);

int debug_c;

void print_if_debug(int debug, const char *fmt, ...)
{
	va_list	args;

	if(debug)
	{
	    printf("DEBUG => ");
	    va_start(args,fmt);
		print_string(fmt, args);
	}
}


void print_string(const char *fmt, va_list args)
{
	char *string;
	int i;
	while( *fmt != '\0')
	{
		if(*fmt == '%' && *(fmt+1) == 's')
		{
			++fmt;
			string = va_arg(args,char*);
			printf("%s", string);
		} else if(*fmt == '%' && *(fmt+1)== 'i')
		{
			++fmt;
			i = va_arg(args,int);
			printf("%i", i);
		} else {
			printf("%c", *fmt);
		}
		++fmt;
	}
	printf("\n");
}


void take_word_from_file(FILE *file, char word[WORD_MAX_LENGTH])
{
    char actual_c;
    int i;
    actual_c = fgetc(file);
    i = 0;
    while(actual_c != EOF && actual_c != ' ' && actual_c != '\n' && i < WORD_MAX_LENGTH)
    {
        word[i] = actual_c;
        actual_c = fgetc(file);
        i++;
    }
    word[i] = '\0';
}

int take_words(FILE *file, char text[DICTIONARY_MAX_LENGTH][WORD_MAX_LENGTH])
{
    int i;
    char word[WORD_MAX_LENGTH];

    for(i=0; i < DICTIONARY_MAX_LENGTH; i++)
    {
        take_word_from_file(file, word);
        if(word[0] != '\0')
        {
            print_if_debug(debug_c, "S'agafa la paraula num. %i => %s", i +1, word);
        } else {
            return i;
        }
        strcpy(text[i], word);
    }
    return i;
}

int look_if_debug_mode(int argc, char ** argv)
{
    int i;
    for(i = 0; i < argc; i++)
    {
        if (strcmp("-d", argv[i]) == 0)
        {
            print_if_debug(1, "MODE DEBUG ON.");
            return 1;
        }
    }
    return 0;
}


int word_appears_in(char *word, char dictionary[DICTIONARY_MAX_LENGTH][WORD_MAX_LENGTH], int length_of_d)
{
    int i;

    for(i = 0; i < length_of_d; i++)
    {
        if(strcmp(word, dictionary[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int number_of_editions(char word[WORD_MAX_LENGTH], char corrected_word[WORD_MAX_LENGTH])
{
    int visited = 0;
}

void find_correct_word(char word[WORD_MAX_LENGTH], char dictionary[DICTIONARY_MAX_LENGTH][WORD_MAX_LENGTH])
{
    int min_differences;
    int num_differences;
    int i;
    min_differences = -1;
    for(i = 0; i < DICTIONARY_MAX_LENGTH; i++)
    {
        num_differences = number_of_editions(word, dictionary[i]);
        if(min_differences < num_differences)
        {
            min_differences = num_differences;
        }
    }
}

int main(int argc, char ** argv)
{
    FILE *file_diccionari;
    FILE *file_amb_soroll;
    FILE *file_corregit;
    FILE *file_num_edicions;

    int i;
    int length_text;

    char dictionary[DICTIONARY_MAX_LENGTH][WORD_MAX_LENGTH];
    char words_in_text[MAX_WORDS][WORD_MAX_LENGTH];

    if(argc < NUM_PARAM)
    {
        printf("ERROR. Falten arguments\n");
        exit(-1);
    }

    debug_c = look_if_debug_mode(argc, argv);

    file_diccionari = fopen(argv[1], "r");
    file_amb_soroll = fopen(argv[2], "r");
    file_corregit = fopen(argv[3], "w");
    file_num_edicions = fopen(argv[4], "w");

    print_if_debug(debug_c, "S'agafen les paraules del fitxer %s", argv[1]);
    take_words(file_diccionari, dictionary);

    print_if_debug(debug_c, "S'agagen les paraules del fitxer %s", argv[2]);
    length_text = take_words(file_amb_soroll, words_in_text);

    for(i = 0; i < length_text; i++)
    {
        if(!word_appears_in(words_in_text[i], dictionary, DICTIONARY_MAX_LENGTH))
        {
            find_correct_word(words_in_text[i], dictionary);
        }
    }

    fclose(file_diccionari);
    fclose(file_amb_soroll);
    fclose(file_corregit);
    fclose(file_num_edicions);
    exit(0);
}
