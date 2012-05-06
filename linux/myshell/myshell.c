#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "parse_args.h"

#define PROMPT ">"
#define LINE_MAX_LENGTH 1024

struct proc_start_info{
  char* cmd;
  char** params;
  int fdin;
  int fdout;
  char* finname;
  char* foutname;
  int fdout_append;
  int need_pipe;
};
print_proc_start_info(struct proc_start_info *psi){
  char **p=psi->params;
  printf ("proc_start_info:\ncmd=%s,fdout_append=%d,need_pipd=%d foutname=%s,finname=%s\nand params:",
          psi->cmd, psi->fdout_append, psi->need_pipe,psi->foutname,psi->finname);
  while(*p!=NULL){
    printf ("%s,",*p);
    p++;
  }
    printf ("\n");
}

free_parse(struct proc_start_info *psi,int proc_len){
  struct proc_start_info *p=psi;
  int i;
  for ( i = 0; i < proc_len; ++i){
    free(p->params);
    /* 释放指向参数的指针数组，但是，存放实际参数的内存并未释放，这部分内容，须另外调free_args(char** params,int len); */
    p++;
  }
  /* 释放 proc_start_info结构体数组占的内存 */
  free(psi);
}
/* read a line to parameter line
   return length of readed chars
   or -1 if out of bound
 */
int my_getline(char* line){
  char c ,*p=line;
  int i=0;
  while(((c=fgetc(stdin))!='\n')&&i<LINE_MAX_LENGTH){
    *p=c;
    p++;
    i++;
  }
  *p=0;
  if (i==LINE_MAX_LENGTH){
    return -1;
  }
  return i;
}
int parse(char** params ,int args_len,struct proc_start_info **psi_out){
  int i,j,pipe_char_count=0;
  char* param;
  char** ptr=params,**real_params;
  char* tmp_params[args_len+1];
  int tmp_params_index=0;
  int isfdin=0,isfdout=0,iscmd=1;
  struct proc_start_info *psi, *psi_tmp;
  for ( i = 0; i < args_len; ++i){
    if(strcmp("|",*ptr)==0){
      pipe_char_count++;
    }
    ptr++;
  }
  psi= calloc(pipe_char_count+1,sizeof(struct proc_start_info));
  psi_tmp=psi;
  ptr=params;

  psi_tmp->need_pipe=0;
  psi_tmp->fdout_append=0;
  psi_tmp->params=NULL;
  for ( i = 0; i < args_len; ++i){
    if(iscmd==1){
      tmp_params[tmp_params_index++]=*ptr;
      psi_tmp->cmd=*ptr;
      iscmd=0;
    }else if(isfdin==1){
      psi_tmp->finname=*ptr;
      isfdin=0;
    }else if(isfdout==1){
      psi_tmp->foutname=*ptr;
      isfdout=0;
    }else if(strcmp("<",*ptr)==0){
      isfdin=1;
    } else if(strcmp(">",*ptr)==0){
      isfdout=1;
    }else if(strcmp(">>",*ptr)==0){
      isfdout=1;
      psi_tmp->fdout_append=1;
    }else if(strcmp("|",*ptr)==0){
      psi_tmp->need_pipe=1;
      tmp_params[tmp_params_index++]=NULL;
      real_params=malloc( tmp_params_index*sizeof(char*));
      for ( j = 0; j <tmp_params_index ; ++j){
        real_params[j]=tmp_params[j];
      }
      psi_tmp->params=real_params;

      /* print_proc_start_info(psi_tmp); */

      tmp_params_index=0;
      psi_tmp++;
      psi_tmp->need_pipe=0;
      psi_tmp->fdout_append=0;
      iscmd=1;
    }else{
      tmp_params[tmp_params_index++]=*ptr;
    }
    ptr++;
  }
  psi_tmp->need_pipe=1;
  tmp_params[tmp_params_index++]=NULL;
  /* printf ("%d\n",tmp_params_index); */
  real_params=malloc( tmp_params_index*sizeof(char*));
  for ( j = 0; j <tmp_params_index ; ++j){
    real_params[j]=tmp_params[j];
  }
  psi_tmp->params=real_params;
  *psi_out=psi;
  /* print_proc_start_info(psi_tmp); */
  return pipe_char_count+1;
}
void exec(){
  int args_len;
  char** params;


}

int main(int argc, char *argv[]){
  char line[100]="ls -l|grep l|more>/tmp/out";
  char** params;
  int params_len,proc_len,i;
  struct proc_start_info *psi,*p;
  params_len=parse_args(line,&params);
  proc_len=parse(params,params_len,&psi);
  p=psi;
  for ( i = 0; i < proc_len; ++i){
    print_proc_start_info(p);
    p++;
  }
  free_parse(psi,proc_len)  ;
  free_args(params,params_len);
  return 0;
}

/* int main(int argc, char *argv[]){ */
/*   char line[LINE_MAX_LENGTH]; */
/*   pid_t pid; */

/*   printf ("%s",PROMPT); */

/*   while (my_getline(line)!=-1){ */
/*     pid= fork(); */
/*     if (pid==-1){ */
/*       perror("for child"); */
/*       exit(1); */
/*     } */
/*     if (pid==0){                /\* child *\/ */
/*       execlp(line,line,NULL); */
/*       perror("exec error"); */
/*     } */
/*     if (pid>0){                 /\* parent *\/ */
/*       wait(NULL); */
/*       fprintf(stderr,PROMPT); */
/*     } */
/*   } */
/*   fprintf(stderr,"error\n"); */
/*   exit(1); */

/*   return 0; */
/* } */
