#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
int parse_args(char* line,char*** params_out){
  int str_len=strlen(line);
  char* ptrs[strlen(line)/2];
  char *p=line;
  char **params ,**p2;
  int i,index,ptr_index=0,index_total=0;
  while(*p!=0){
    index=get_next_token(p,&ptrs[ptr_index++]);
    if(index==-1){
      for ( i = 0; i < ptr_index-1; ++i){
        free(ptrs[i]);
      }
      fprintf(stderr,"parse command error");
      return -1;
    }else{
      p=p+index;
    }
  }
  params=(char**)calloc(ptr_index,sizeof(char*));
  p2=params;
  for ( i = 0; i < ptr_index; ++i){
    *p2=ptrs[i];
    p2++;
  }

  *params_out= params;
  /* printf ("%p\n",params_out); */
  /* printf ("%p\n",&params); */
  return ptr_index;
}
/*
 * parse line ,
 *  got_token is  the address of a  point of the first parameter token,
 *  you need free it ,because it is malloc.
 *
  @return the index of or -1 if the format of line is invalid
 */
int get_next_token(char* line,char** got_token){
  int head=1;
  int quote=0;
  int translate=0;
  char c, *p=line;
  int i =0,index=0;
  int parse_done=0;
  int len=strlen(line);
  char token[len+1];
  for ( i = 0; i < len; ++i){
    c= *p;
    p++;
    if (c!=' '&&c!='\t'){
      head=0;
    }
    if (c==' '||c=='\t'){
      if (head==1){
        continue;
      }else{
        if (quote==1){
          token[index++]=c;
        }else{
          if(translate==1){
            token[index++]='\\';
          }
          token[index++]=0;
          parse_done=1;
          break;
        }
      }
    }else if (c=='\\'){
      if (translate==0){
        translate=1;
      }else{
        translate=0;
        token[index++]='\\';
      }
    }else if (c=='\"'){
      if(translate==1){
        token[index++]='\"';
      }else{
        if (quote==1){
          token[index++]=0;
          index++;
          parse_done=1;
          break;
        }else{
          quote=1;
        }
      }
    }else {
      if (translate==1){
        token[index++]='\\';
      }
      token[index++]=c;
    }
  }
  if (parse_done==0){
    token[index++]=0;
    if(quote==1){
      return -1;
    }
  }
  p = (char*) malloc(index+1);
  strcpy(p,token);
  *got_token = p;
  return index;
}
void free_args(char** params,int len){
  char** p=params;
  int i;
  for ( i = 0; i<len; ++i){
    free(*p);
    p++;
  }
  free(params);
}
int main(int argc, char *argv[]){
  char line[100]="asdf asdfads";
  printf ("%s\n",line);
  char** params,**p;
  int i;
  int len=parse_args(line,&params);
  /* printf ("%p\n",params); */
  p=params;
  for ( i = 0; i<len; ++i){
    printf ("token%d=%s\n",i,*p);
    p++;
  }
  free_args(params,len);
  return 0;
}
