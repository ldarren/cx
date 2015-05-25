#include "./ast.h"
#include <stdio.h>
#include <stdlib.h>

ast_node *readFile(char *fname){
    FILE *fp = fopen(fname, "r");
    if (!fp){
        perror("Error while opering the file.\n");
        exit(EXIT_FAILURE);
    }

    char ch;
    size_t r=0, c=0;
    ast_node *chost=NULL, *cnode=NULL;
    ast_node *host = chost = ast_add_node(NULL, r, c);

    while((ch = fgetc(fp)) != EOF){
        switch(ch){
        case '\r': break;
        case '\n':
            if (!cnode) goto error;
            ast_update_node(cnode, r, c);
            cnode = NULL;
            c=-1;
            r++;
            break;
        case ' ':
        case ';':
            if (!cnode) goto error;
            ast_update_node(cnode, r, c);
            cnode = NULL;
            break;
        default:
            if (!cnode) cnode = ast_add_node(chost, r, c);
            break;
        }
        c++;
    }
    ast_update_node(host, r, c);

error:
    fclose(fp);
    if (host->c2) return NULL;
    return host;
}

int repl(){
    return 0;
}

int run(char *fname){
    ast_node *host = readFile(fname);
    if (!host) return 1;
    ast_clear(host, 0);
    return 0;
}

int main(int argc, char **argv){
    switch(argc){
    case 1:
        return repl();
    case 2:
        return run(argv[1]);
    default:
        printf("Usage: %s [SCRIPT URL]\n", argv[0]);
        break;
    }
    return 0;
}
