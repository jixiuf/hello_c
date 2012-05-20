//file name : socket1.c
//created at: 2012年05月20日 星期日 12时10分23秒
//author:  纪秀峰

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <arpa/inet.h>

/*stringIP to in_addr类型  */
/* int inet_aton(const char *strptr, struct in_addr *addrptr); */
/* in_addr_t inet_addr(const char *strptr); */
/* int inet_pton(int family, const char *strptr, void *addrptr); */


int main(int argc, char *argv[]){
  char *ip="192.168.0.1";       /* 196   2#11000000 */
  struct in_addr addr;
  in_addr_t *addrptr;
  inet_aton(ip, &addr);
  printf ("%d\n",addr.s_addr);  /*16820416 2#1000000001010100011000000 */

  /* AF_INET表示ipv4 */
  inet_pton(AF_INET,ip,&addr.s_addr);
  printf ("%d\n",addr.s_addr);  /*16820416 2#1000000001010100011000000 */

  return 0;
}
