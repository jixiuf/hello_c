#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

int parse_args(char* line,char*** params_out);
void free_args(char** params,int len);

#endif
