#include <stdarg.h>

#define NUM_PARAM 5
#define DICTIONARY_MAX_LENGTH 140
#define WORD_MAX_LENGTH 11
#define MAX_WORDS 30

struct correct_word
{
    int min_differences;
    char corrected_word[WORD_MAX_LENGTH];
};

struct stack
{
    int top;
    char stack[MAX_WORDS][WORD_MAX_LENGTH];
};

int look_if_debug_mode(int argc, char ** argv);
int take_words(FILE *file, char text[DICTIONARY_MAX_LENGTH][WORD_MAX_LENGTH]);
void take_word_from_file(FILE *file, char word[WORD_MAX_LENGTH]);
void print_if_debug(int debug, const char *fmt, ...);
void print_string(const char *fmt, va_list args);
int word_appears_in(char *word, char dictionary[DICTIONARY_MAX_LENGTH][WORD_MAX_LENGTH], int length_of_d);
struct correct_word find_correct_word(char word[WORD_MAX_LENGTH], char dictionary[DICTIONARY_MAX_LENGTH][WORD_MAX_LENGTH]);
int number_of_editions(char word[WORD_MAX_LENGTH], char corrected_word[WORD_MAX_LENGTH]);

int is_empty(struct stack s);
int is_full(struct stack s);
char* top(struct stack s);
char* pop(struct stack *s);
int push(struct stack *s, char word[WORD_MAX_LENGTH]);