#include "include/token.h"
#include <stdlib.h>
#include <locale.h>

token_T* init_token(int type, char* value)
{
    token_T* token = malloc(sizeof(struct TOKEN));
    token->type = type;
    token->value = value;

    return token;
}