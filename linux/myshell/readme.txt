>ls
getline.c  Makefile  memwatch.log  myshell  myshell.c  parse_args.c  parse_args.h
>pwd
/home/jixiuf/c/linux/myshell
>cat /etc/passwd|grep ro
root:x:0:0:root:/root:/bin/zsh
operator:x:11:0:operator:/root:/bin/bash
proftpd:x:104:199:added by portage for proftpd:/dev/null:/sbin/nologin
cron:x:16:16:added by portage for cronbase:/var/spool/cron:/sbin/nologin
>cat /etc/passwd|grep ro >/tmp/out
