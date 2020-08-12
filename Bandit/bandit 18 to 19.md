# bandit 18 to 19

he password for the next level is stored in a file **readme** in the homedirectory. Unfortunately, someone has modified **.bashrc** to log you out when you log in with SSH.

## Commands you may need to solve this level

ssh, ls, cat

---

Use 'cat' instruction. 

When I connect by ssh, I saw they say 'Byebye ! ' and get disconnected.

```bash
jisu@ubuntu:~$ ssh bandit18@bandit.labs.overthewire.org -p2220
This is a OverTheWire game server. More information on http://www.overthewire.org/wargames

bandit18@bandit.labs.overthewire.org's password: 
Linux bandit 4.18.12 x86_64 GNU/Linux
               
      ,----..            ,----,          .---. 
     /   /   \         ,/   .`|         /. ./|
    /   .     :      ,`   .'  :     .--'.  ' ;
   .   /   ;.  \   ;    ;     /    /__./ \ : |
  .   ;   /  ` ; .'___,/    ,' .--'.  '   \' .
  ;   |  ; \ ; | |    :     | /___/ \ |    ' ' 
  |   :  | ; | ' ;    |.';  ; ;   \  \;      : 
  .   |  ' ' ' : `----'  |  |  \   ;  `      |
  '   ;  \; /  |     '   :  ;   .   \    .\  ; 
   \   \  ',  /      |   |  '    \   \   ' \ |
    ;   :    /       '   :  |     :   '  |--"  
     \   \ .'        ;   |.'       \   \ ;     
  www. `---` ver     '---' he       '---" ire.org     
               
              
Welcome to OverTheWire!

...(skip)...

  Enjoy your stay!

Byebye !
Connection to bandit.labs.overthewire.org closed.
```

So I append 'bash' to end of ssh instruction option [ command].

```bash
jisu@ubuntu:~$ ssh bandit18@bandit.labs.overthewire.org -p2220 bash
This is a OverTheWire game server. More information on http://www.overthewire.org/wargames

bandit18@bandit.labs.overthewire.org's password: 
ls
readme
cat read	
cat: read: No such file or directory
cat readme 
IueksS7Ubh8G3DCwVzrTd8rAVOwq3M5x
```

password is 'IueksS7Ubh8G3DCwVzrTd8rAVOwq3M5x'.