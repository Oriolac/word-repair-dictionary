#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include "corrector.h"

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
    char c;
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
		} else if(*fmt == '%' && *(fmt+1) == 'c')
        {
            ++fmt;
            c = (char) va_arg(args, int);
            printf("%c", c);
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
        if(word[0] == '\0')
        {
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
    struct stack s;
    struct element_of_stack elem;

    int min_differences;
    s = create_a_stack();

    print_if_debug(debug_c, "Es busca la paraula amb %s!", corrected_word);

    strcpy(elem.corrected_word, corrected_word);
    elem.editions = 0;
    strcpy(elem.word, word);
    push(&s, elem);
    while(!is_empty(s))
    {
        elem = pop(&s);
        print_if_debug(debug_c, "%s, %s, %i", elem.word, elem.corrected_word, elem.editions);
        sleep(1);
        if(strcmp(elem.corrected_word, "") == 0 || strcmp(elem.word, "") == 0)
        {
            print_if_debug(debug_c, "EOO");
        } else if(corrected_word[0] == word[0]) 
        {
            
        } else
        {
            push_the_differents_possibilities(&s, elem);
        }
        
        
    }
    return 0;
}

void push_the_differents_possibilities(struct stack *s, struct element_of_stack elem)
{
    struct element_of_stack elem2;

    elem2.editions = elem.editions +1;

    strcpy(elem2.word, &elem.word[1]);
    printf("%c\n%c\n", elem.word[0], elem2.word[0]);
    strcpy(elem2.corrected_word, elem.corrected_word);
    print_if_debug(debug_c, "S'afegeix (%s, %s, %i) per addició de lletra", elem2.word, elem2.corrected_word, elem2.editions);
    push(s,elem2);

    strcpy(elem2.corrected_word, &elem.corrected_word[1]);
    print_if_debug(debug_c, "S'afegeix (%s, %s, %i) per canvi de lletra", elem2.word, elem2.corrected_word, elem2.editions);
    push(s, elem2);

    strcpy(elem2.word, elem.word);
    print_if_debug(debug_c, "S'afegeix (%s, %s, %i) per supressió de lletra", elem2.word, elem2.corrected_word, elem2.editions);
    push(s, elem2);
}

struct correct_word find_correct_word(char word[WORD_MAX_LENGTH], char dictionary[DICTIONARY_MAX_LENGTH][WORD_MAX_LENGTH])
{
    int num_differences;
    int i;
    struct correct_word final_word;

    final_word.min_differences = -1;
    for(i = 0; i < DICTIONARY_MAX_LENGTH; i++)
    {
        num_differences = number_of_editions(word, dictionary[i]);
        if(final_word.min_differences < num_differences)
        {
            final_word.min_differences = num_differences;
            strcpy(final_word.corrected_word, dictionary[i]);
        }
    }

    return final_word;

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
            print_if_debug(debug_c, "Paraula incorrecta: %s", words_in_text[i]);
            find_correct_word(words_in_text[i], dictionary);
        }
    }

    fclose(file_diccionari);
    fclose(file_amb_soroll);
    fclose(file_corregit);
    fclose(file_num_edicions);
    exit(0);
}
