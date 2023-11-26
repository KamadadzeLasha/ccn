#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

lexer_T* init_lexer(char* contents)
{
    lexer_T* lexer = malloc(sizeof(struct LEXER));
    lexer->contents = contents;
    lexer->i = 0;
    lexer->c = contents[lexer->i];

    return lexer;
}

void lexer_advance(lexer_T* lexer)
{
    if(lexer->c != '\0' && lexer->i < strlen(lexer->contents))
    {
        lexer->i++;
        lexer->c = lexer->contents[lexer->i];
    }
}

void lexer_skip_whitespace(lexer_T* lexer)
{
    while(lexer->c == ' ' || lexer->c == '\n' || lexer->c == '\t')
    {
        lexer_advance(lexer);
    }
}

token_T* lexer_get_next_token(lexer_T* lexer)
{
    while(lexer->c != '\0' && lexer->i < strlen(lexer->contents))
    {
        if(lexer->c == ' ' || lexer->c == '\n' || lexer->c == '\t')
        {
            lexer_skip_whitespace(lexer);
        }
        if(isalnum(lexer->c))
        {
            return lexer_collect_id(lexer);
        }
        if(lexer->c == '"')
        {
            return lexer_collect_string(lexer);
        }
        switch(lexer->c)
        {
            case '+': return lexer_advance_with_token(lexer, init_token(მიმატება, lexer_get_current_char_as_string(lexer)));
            case '-': return lexer_advance_with_token(lexer, init_token(გამოკლება, lexer_get_current_char_as_string(lexer)));
            case '*': return lexer_advance_with_token(lexer, init_token(გამრავლება, lexer_get_current_char_as_string(lexer)));
            case '/': return lexer_advance_with_token(lexer, init_token(გაყოფა, lexer_get_current_char_as_string(lexer)));

            case '.': return lexer_advance_with_token(lexer, init_token(წერტილი, lexer_get_current_char_as_string(lexer)));
            case ',': return lexer_advance_with_token(lexer, init_token(მძიმე, lexer_get_current_char_as_string(lexer)));
            case ':': return lexer_advance_with_token(lexer, init_token(ორწერტილი, lexer_get_current_char_as_string(lexer)));

            case '=': return lexer_advance_with_token(lexer, init_token(ტოლობა, lexer_get_current_char_as_string(lexer)));
            case '>': return lexer_advance_with_token(lexer, init_token(მეტობა, lexer_get_current_char_as_string(lexer)));
            case '<': return lexer_advance_with_token(lexer, init_token(ნაკლებობა, lexer_get_current_char_as_string(lexer)));

            case '(': return lexer_advance_with_token(lexer, init_token(ფრჩხილი_1, lexer_get_current_char_as_string(lexer)));
            case ')': return lexer_advance_with_token(lexer, init_token(ფრჩხილი_2, lexer_get_current_char_as_string(lexer)));
            
            //case '{': return lexer_advance_with_token(lexer, init_token(მინიჭება, lexer_get_current_char_as_string(lexer)));
            //case '}': return lexer_advance_with_token(lexer, init_token(, lexer_get_current_char_as_string(lexer)));
            
            //case '[': return lexer_advance_with_token(lexer, init_token(მეტობა_ტოლობა, lexer_get_current_char_as_string(lexer)));
            //case ']': return lexer_advance_with_token(lexer, init_token(ნაკლებობა_ტოლობა, lexer_get_current_char_as_string(lexer)));
            //case ';': return lexer_advance_with_token(lexer, init_token(მეტობა_ტოლობა, lexer_get_current_char_as_string(lexer)));

        }
    }
    return (void*) 0;
}

token_T* lexer_collect_string(lexer_T* lexer)
{
    lexer_advance(lexer);

    char* value = calloc(1, sizeof(char));
    value[0] = '\0';
    while(lexer->c != '"'){
        char* temp = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(temp) + 1) * sizeof(char));
        strcat(value, temp);

        lexer_advance(lexer); 
    }

    lexer_advance(lexer);

    return init_token(სტრინგი, value);
}
token_T* lexer_collect_id(lexer_T* lexer){
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while(isalnum(lexer->c)){
        char* temp = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(temp) + 1) * sizeof(char));
        strcat(value, temp);

        lexer_advance(lexer); 
    }
    return init_token(მიმატება, value);      

}

token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token)
{
    lexer_advance(lexer);

    return token;
}

char* lexer_get_current_char_as_string(lexer_T* lexer)
{
    char* str = calloc(2, sizeof(char));
    str[0] = lexer->c;
    str[1] = '\0';

    return str;
}
