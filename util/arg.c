//file name : arg.c
/* 主要功能：命令行参数传递时，可能会用半双绰号将某些值引号来，此函数解引 */
//created at: 2012年12月23日 星期日 21时23分11秒
//author:  纪秀峰

#include <malloc.h>
static void * emalloc(size_t size)
{
  void *p = malloc(size);
  if (p == NULL)
	error("Insufficient memory");
  return p;
}

static void * erealloc(void *p, size_t size)
{
  void *res = realloc(p, size);
  if (res == NULL)
	error("Insufficient memory");
  return res;
}


char **build_args_from_string(char *string)
{
  int argc = 0;
  char **argv = NULL;
  int alloced = 0;
  char **cur_s = NULL;	/* Initialized to avoid warning. */
  int s_alloced = 0;
  int s_pos = 0;
  char *p = string;
  enum {Start, Build, Build0, BuildSQuoted, BuildDQuoted, AcceptNext} state;

#define ENSURE()                                    \
  if (s_pos >= s_alloced) {                         \
	if (!*cur_s) {                                  \
      *cur_s = emalloc(s_alloced = 20);             \
	} else {                                        \
      *cur_s = erealloc(*cur_s, s_alloced += 20);	\
	}                                               \
  }


  if (!p)
	return NULL;
  argv = emalloc(sizeof(char *) * (alloced = 10));
  state = Start;
  for(;;) {
	switch (state) {
	case Start:
      if (!*p)
		goto done;
      if (argc >= alloced - 1) { /* Make room for extra NULL */
		argv = erealloc(argv, (alloced += 10) * sizeof(char *));
      }
      cur_s = argc + argv;
      *cur_s = NULL;
      s_pos = 0;
      s_alloced = 0;
      state = Build0;
      break;
	case Build0:
      switch (*p) {
      case ' ':
		++p;
		break;
      case '\0':
		state = Start;
		break;
      default:
		state = Build;
		break;
      }
      break;
	case Build:
      switch (*p) {
      case ' ':
      case '\0':
		ENSURE();
		(*cur_s)[s_pos] = '\0';
		++argc;
		state = Start;
		break;
      case '"':
		++p;
		state = BuildDQuoted;
		break;
      case '\'':
		++p;
		state = BuildSQuoted;
		break;
      case '\\':
		++p;
		state = AcceptNext;
		break;
      default:
		ENSURE();
		(*cur_s)[s_pos++] = *p++;
		break;
      }
      break;
	case BuildDQuoted:
      switch (*p) {
      case '"':
		++p;
		/* fall through */
      case '\0':
		state = Build;
		break;
      default:
		ENSURE();
		(*cur_s)[s_pos++] = *p++;
		break;
      }
      break;
	case BuildSQuoted:
      switch (*p) {
      case '\'':
		++p;
		/* fall through */
      case '\0':
		state = Build;
		break;
      default:
		ENSURE();
		(*cur_s)[s_pos++] = *p++;
		break;
      }
      break;
	case AcceptNext:
      if (!*p) {
		state = Build;
      } else {
		ENSURE();
		(*cur_s)[s_pos++] = *p++;
      }
      state = Build;
      break;
	}
  }
 done:
  argv[argc] = NULL; /* Sure to be large enough */
  if (!argc) {
	free(argv);
	return NULL;
  }
  return argv;
#undef ENSURE
}
/*
  test free()
  无限循环也不见内存疯长
  ps -ef |grep arg
  top -p pid
 */
void test_malloc_free(){
  char  **str_arr,**ptr;
  char* str="aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfdddddddddddddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacasdfddddddddddddddddddddddddddddddddddddddddd";
  printf ("test free_malloc or this func\n");
  while(1){
    str_arr=build_args_from_string(str);
    ptr=str_arr;
    while(*ptr){
      /* printf ("%s\n",(*ptr)); */
      ptr++;
    }

    ptr=str_arr;
    while(*ptr){
      free(*ptr);
      ptr++;
    }
    free(str_arr);
  }

}

void test_str(char* string){
  char  **str_arr,**ptr;
    str_arr=build_args_from_string(string);
    ptr=str_arr;
    printf ("==========================================\n");
    printf ("origin str:<%s>\n",string);
    while(*ptr){
      printf ("<%s>\n",(*ptr));
      ptr++;
    }
    printf ("==========================================\n");

    ptr=str_arr;
    while(*ptr){
      free(*ptr);
      ptr++;
    }
    free(str_arr);
}

int main(int argc, char *argv[]){
  test_str("abc");
  test_str("abc=\"def\"");
  test_str("abc='def'");
  test_str("abc=a\tb");
  test_str("  abc=a\tb ");
  test_malloc_free();
  /* test(); */
  return 0;
}
