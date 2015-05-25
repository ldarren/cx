#ifndef __CX_AST_H__
#define __CX_AST_H__

#include <stddef.h>

typedef struct ast_node{
    size_t r1;
    size_t c1;
    size_t r2;
    size_t c2;
    struct ast_node *prev;
    struct ast_node *next;
    struct ast_node *host;
    struct ast_node *head;
}ast_node;

extern const size_t AST_NODE_SIZE;

ast_node *ast_add_node(ast_node *host, size_t r, size_t c);
void ast_update_node(ast_node *self, size_t r, size_t c);
void ast_clear(ast_node *from, ast_node *to);

#endif // __CX_AST_H__
