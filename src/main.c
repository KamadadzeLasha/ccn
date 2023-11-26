#include <stdio.h>
#include "include/lexer.h"
#include <locale.h>


int main(int argc, char* argv[]){
    setlocale(LC_ALL, "");
    lexer_T* lexer = init_lexer(
        "n.1. dasawyisi \n n.2. shemoitane y \n n.3. y := y + 15 \n n.4. gamovitanot y \n n.5. dasasruli"
    );
    token_T* token = (void*) 0;
    while((token = lexer_get_next_token(lexer)) != (void*) 0)
    {
        printf("TOKEN(%d, %s)\n", token->type, token->value);
    }

    return 0;
}