#include <stdio.h>
#include "tokenizer.h"
#include "parser.h"

int main() {
    char line[256];
    line[0] = 0;

    while (fgets(line, 256, stdin) != NULL) {
        struct token_list_t* token_list = tokenizer_tokenize(line);
        struct ast_node_t* ast = parser_build_ast(token_list);

        for (int32_t idx = 0;idx < token_list->length;idx++) {
            struct token_t* token = &token_list->tokens[idx];
            printf("[TOKEN]\n");
            printf("Token Type: %s\n", tokenizer_type_to_string(token->type));
            printf("Token Value: %d\n", token->value);
        }

        int32_t result = parser_evaluate(ast);
        printf("[RESULT]\n");
        printf("%d\n", result);

        parser_free_ast(ast);
        tokenizer_free_token_list(token_list);
    }

    return 0;
}
