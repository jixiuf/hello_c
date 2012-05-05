#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
/* 返回token 的长度，解析后的token放在params_out中,如完需要调用 free_args() */
/* 释放相应的内存 */
/* 如果参数line的格式不对，返回-1,会自动释放已分配的内存,不需手动调用free_args */
int parse_args(char* line,char*** params_out){
  int str_len=strlen(line);
  /* 对与一个命令行 cmd，最多有 length(cmd)/2个token ,因为分隔符也要占一份  */
  char* ptrs[strlen(line)/2];
  char *p=line;
  char **params ,**p2;
  int i,index,ptr_index=0,index_total=0;
  while(*p!=0){
    index=get_next_token(p,&ptrs[ptr_index++]);
    if(index==-1){
      /* 如果在解析过程中出错，释放已经审请的内存 */
      for ( i = 0; i < ptr_index-1; ++i){
        free(ptrs[i]);
      }
      fprintf(stderr,"parse command error");
      return -1;
    }else if (index==-2){        /* 解析到空串,说明解析到末尾了 */
      ptr_index--;
      break;
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
 or -2 if whole line is tab or space
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
  /* printf ("cur=%s\n",line); */
  for ( i = 0; i < len; ++i){
    c= *p;
    p++;
    /* if (c!=' '&&c!='\t'){ */
    /*   head=0; */
    /* } */
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
    }else if (c=='|' ||c=='<'){
      if (head==1){
        token[index++]=c;
        token[index++]=0;
        head=0;
        parse_done=1;
        break;
      }else{
        head=0;
        if (quote==1){
          token[index++]=c;
        }else{
          if(translate==1){
            token[index++]='\\';
          }
          i--;
          token[index++]=0;
          /* printf ("%c,%d\n",c,index); */
          parse_done=1;
          break;
        }
      }
    }else if (c=='>'){
      if (head==1){
        head=0;
        token[index++]=c;
        if(i<len-1){          /* 如果有后继字符，判断下一个字符是不是> 以组成>> */
          /* printf ("%c,%d\n",*p,index); */
          if (*p=='>'){
            p++;
            i++;
            token[index++]=c;
          }
        }
        token[index++]=0;
        parse_done=1;
        break;
      }else{
        head=0;
        if (quote==1){
          token[index++]=c;
        }else{
          if(translate==1){
            token[index++]='\\';
          }
          i--;
          token[index++]=0;
          parse_done=1;
          break;
        }
      }
    } else if (c=='\\'){
      head=0;
      if (translate==0){
        translate=1;
      }else{
        translate=0;
        token[index++]='\\';
      }
    }else if (c=='\"'){
      head=0;
      if(translate==1){
        token[index++]='\"';
      }else{
        if (quote==1){
          token[index++]=0;
          i++;
          parse_done=1;
          break;
        }else{
          quote=1;
        }
      }
    }else {
      head=0;
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
  if(head==1){                  /* 如果解析到是是一个空串，返回0,此时并未动态分配内存 */
    return -2;
  }
  p = (char*) malloc(index*sizeof(char));
  strcpy(p,token);
  *got_token = p;
  /* printf ("%d,%d\n",i,index); */
  return i+1;
}
/* 释放在解析参数时审请的内存 */
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
  /* char line[100]="ls -l"; */
  /* char line[100]="ls -l>a.out"; */
  /* char line[100]="ls -l>>a.out"; */
  /* char line[100]="ls -l>> a.out"; */
  /* char line[100]="ls -l >> a.out"; */
  /* char line[100]="ls -l <a.out"; */
  /* char line[100]="ls -l |more"; */
  /* char line[100]="ls -l | more"; */
  /* char line[100]="ls -l| more"; */
  /* char line[100]="ls<a.in >b.out"; */
  /* char line[100]="ls -l|more >b.out"; */
  /* char line[100]="ls -l|more > b.out"; */
  /* char line[100]="ls -l|more >> b.out"; */
  /* char line[100]="ls -l|more >>b.out"; */
  /* char line[100]="ls -l|more>>b.out"; */
  /* char line[100]="ls -l|more>>\"b.out name\""; */
  /* char line[100]="ls -l|more>>\"b.out name\""; */
  /* char line[100]="ls -l|more>>\"|b.out name\""; */
  /* char line[100]="ls -l|more>>\"|<>>b.out name\""; */
  /* char line[100]=" ls -l|more>>\"|<>>b.out name\""; */
  /* char line[100]=" ls -l|more>>\"|<>>b.out name\"  "; */
  /* char line[100]=" dd </dev/zero >/tmp/s "; */
  printf ("%s\n",line);
  char** params,**p;
  int i;
  int len=parse_args(line,&params);
  if(len>0){
    /* printf ("%p\n",params); */
    p=params;
    for ( i = 0; i<len; ++i){
      printf ("token%d=%s\n",i,*p);
      p++;
    }
    /* 释放在解析参数时审请的内存 */
    free_args(params,len);
  }
  return 0;
}
