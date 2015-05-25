#include "./ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t NODE_SIZE = sizeof(ast_node);

void append_child(ast_node *host, ast_node *child){
    ast_node *head = host->head;
    if (head){
        ast_node *tail = head->prev;
        tail->next = child;
        head->prev = child;
        child->next = head;
        child->prev = tail;
        return;
    }
    host->head = child;
    child->next = child;
    child->prev = child;
}

ast_node *ast_add_node(ast_node *host, size_t r, size_t c){

    ast_node *node = (ast_node *)malloc(NODE_SIZE);
    memset(node, 0, NODE_SIZE);
    node->r1 = r;
    node->c1 = c;
    if (!host) return node;
    append_child(host, node);
    return node;
}

void ast_update_node(ast_node *self, size_t r, size_t c){
    if (!self) return;
    self->r2 = r;
    self->c2 = c;
}

void ast_clear(ast_node *from, ast_node *to){
    if (!from) return;

    ast_node *next = from->next;
    if (next && next != to){
        if (to){
            ast_clear(next, to);
        }else{
            ast_node *prev = from->prev;
            prev->next = next;
            next->prev = prev;
        }
    }

    ast_clear(from->head, from->head);
    printf("remove start[%zu, %zu] end[%zu, %zu]\n", from->r1, from->c1, from->r2, from->c2);
    free(from);
}
