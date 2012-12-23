//file name : arg_quote.c
//created at: 2012年12月24日 星期一 00时02分05秒
//author:  纪秀峰

#include <malloc.h>
#include <string.h>
#define NO 0
#define YES 1

void * emalloc(size_t size)
{
  void *p = malloc(size);
  if (p == NULL)
    error("Insufficient memory");
  return p;
}

/* 如果字符串需要用"引用起来，则引用之，否则直接返回 */
char* possibly_quote(char* arg)
{
  int mustQuote = NO;
  int n = 0;
  char* s;
  char* narg;

  if (arg == NULL) {
	return arg;
  }

  /*
   * Scan the string to find out if it needs quoting and return
   * the original argument if not.
   */

  for (s = arg; *s; s++, n++) {
	switch(*s) {
	case ' ':
      mustQuote = YES;
      continue;
	case '"':
      mustQuote = YES;
      n++;
      continue;
	case '\\':
      if(s[1] == '"')
		n++;
      continue;
	default:
      continue;
	}
  }
  if (!mustQuote) {
	return arg;
  }

  /*
   * Insert the quotes and put a backslash in front of every quote
   * inside the string.
   */

  s = narg = emalloc(n+2+1);
  for (*s++ = '"'; *arg; arg++, s++) {
	if (*arg == '"' || (*arg == '\\' && arg[1] == '"')) {
      *s++ = '\\';
	}
	*s = *arg;
  }
  if (s[-1] == '\\') {
	*s++ ='\\';
  }
  *s++ = '"';
  *s = '\0';
  return narg;
}

void test_str(char* str){
  char* ret;
  printf ("------------------------------\n");
  printf ("origin str:%s\n",str);
  printf ("%s\n",ret=possibly_quote(str));
  printf ("------------------------------\n");
  if(ret!=str)
    free(ret);
}
void test(){
  char *ori;

  ori=malloc(4*sizeof(char));
  memcpy(ori ,"abc" ,4*sizeof(char));
  test_str(ori);
  free(ori);

  ori=malloc(5*sizeof(char));
  memcpy(ori ,"a\"bc" ,5*sizeof(char));
  test_str(ori);
  free(ori);

  ori=malloc(6*sizeof(char));
  memcpy(ori ,"a\\\"bc" ,6*sizeof(char));
  test_str(ori);
  free(ori);

}
int main(int argc, char *argv[]){
    test();
  return 0;
}
