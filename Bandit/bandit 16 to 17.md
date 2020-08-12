# bandit 16 to 17

The credentials for the next level can be retrieved by submitting the password of the current level to **a port on localhost in the range 31000 to 32000**. First find out which of these ports have a server listening on them. Then find out which of those speak SSL and which don’t. There is only 1 server that will give the next credentials, the others will simply send back to you whatever you send to it.

## Commands you may need to solve this level

ssh, telnet, nc, openssl, s_client, nmap

---

Use 'nmap' , 'openssl' and 's_client' instructions.

'nmap' scans open ports. So I can scan port from 31000 to 32000.

```bash
bandit16@bandit:~$ nmap localhost -p 31000-32000

Starting Nmap 7.40 ( https://nmap.org ) at 2019-07-25 17:08 CEST
Nmap scan report for localhost (127.0.0.1)
Host is up (0.00023s latency).
Not shown: 999 closed ports
PORT      STATE SERVICE
31518/tcp open  unknown
31790/tcp open  unknown

Nmap done: 1 IP address (1 host up) scanned in 0.08 seconds
```

There are 2 ports opened. 31518 and 31790

Connect each port one by one.

```bash
bandit16@bandit:~$ openssl s_client -connect localhost:31518
CONNECTED(00000003)
depth=0 CN = localhost
verify error:num=18:self signed certificate
verify return:1
depth=0 CN = localhost
verify return:1
---
Certificate chain
 0 s:/CN=localhost
   i:/CN=localhost
---
Server certificate
-----BEGIN CERTIFICATE-----
MIICBjCCAW+gAwIBAgIEZ098+jANBgkqhkiG9w0BAQUFADAUMRIwEAYDVQQDDAls
b2NhbGhvc3QwHhcNMTkwNzE5MTc1MTEzWhcNMjAwNzE4MTc1MTEzWjAUMRIwEAYD
VQQDDAlsb2NhbGhvc3QwgZ8wDQYJKoZIhvcNAQEBBQADgY0AMIGJAoGBAL0X4vYJ
ptgMUdSOSxpeNkk3IO3yBCv6SLis0WTaJJIXDBFZXX7W++GgVSbOi8IPTZfsvjvL
gBDymSRpmD2+MqB+RnQx/XijCb85fjER3oi7chu+iUaJZTtLU+uf/B2hG/mSDiV2
PMn2rgNUch2UtV0nzW5re878OYMvUQ6IqpLBAgMBAAGjZTBjMBQGA1UdEQQNMAuC
CWxvY2FsaG9zdDBLBglghkgBhvhCAQ0EPhY8QXV0b21hdGljYWxseSBnZW5lcmF0
ZWQgYnkgTmNhdC4gU2VlIGh0dHBzOi8vbm1hcC5vcmcvbmNhdC8uMA0GCSqGSIb3
DQEBBQUAA4GBAEtjOA4xrY9tls4YCD0sPgVGAkzt5W9b1+xVfXPerIjT6tibmWxy
fFwSlaNOF5cf8CSnHyTj4eoYpVA+sjuZLf0JefI94GQN/coUfnlePM0t+mxMn+3+
dZgzbUtJ+QwOPQuunZievWcVhi5wXx9IrBJeQKYAgWtlgnbPolhCzCGX
-----END CERTIFICATE-----
subject=/CN=localhost
issuer=/CN=localhost
---
No client certificate CA names sent
Peer signing digest: SHA512
Server Temp Key: X25519, 253 bits
---
SSL handshake has read 1019 bytes and written 269 bytes
Verification error: self signed certificate
---
New, TLSv1.2, Cipher is ECDHE-RSA-AES256-GCM-SHA384
Server public key is 1024 bit
Secure Renegotiation IS supported
Compression: NONE
Expansion: NONE
No ALPN negotiated
SSL-Session:
    Protocol  : TLSv1.2
    Cipher    : ECDHE-RSA-AES256-GCM-SHA384
    Session-ID: 86946C615397CC606C221A59BAD3A6BF6641046E8E5F4525EB9B9B9334334A4D
    Session-ID-ctx: 
    Master-Key: 720C2F660ED1E4D4A6E366B4C961BB99AC159E04329FBD691CAC0942F2B4BC09B419A4CC20834291A2D523A86F5366F9
    PSK identity: None
    PSK identity hint: None
    SRP username: None
    TLS session ticket lifetime hint: 7200 (seconds)
    TLS session ticket:
    0000 - 5a 81 99 c5 c7 21 a0 3c-b5 6d a7 39 c6 37 5e 9c   Z....!.<.m.9.7^.
    0010 - d3 1b c2 51 ac 91 6b a4-b7 dd 17 8d f5 93 f0 d0   ...Q..k.........
    0020 - 67 df 8d a8 df 55 8b e3-84 7a b2 66 cf 1a 7c 0d   g....U...z.f..|.
    0030 - 3b d2 be e8 ba b6 45 ec-da 58 00 7d 01 7f 90 53   ;.....E..X.}...S
    0040 - 7d 5a c3 d1 be fb ac 16-51 4e 58 26 40 bb 6d c6   }Z......QNX&@.m.
    0050 - 69 41 5f 9f 61 9e 7d d2-90 c6 9d 72 6b 60 97 bc   iA_.a.}....rk`..
    0060 - 05 35 ba c5 1a 32 a8 4d-b4 15 74 10 fb 95 20 f7   .5...2.M..t... .
    0070 - 04 ec 79 b6 a7 2a 86 04-cd 92 43 da a6 57 be dd   ..y..*....C..W..
    0080 - c7 a1 1a 75 f5 49 8f da-21 5f 3b e3 26 07 a6 83   ...u.I..!_;.&...
    0090 - 28 a8 06 6a ef 0b 6e 0c-7d 19 2d d8 03 a7 70 ac   (..j..n.}.-...p.

    Start Time: 1564067385
    Timeout   : 7200 (sec)
    Verify return code: 18 (self signed certificate)
    Extended master secret: yes
---
cluFn7wTiGryunymYOu4RcffSxQluehd
cluFn7wTiGryunymYOu4RcffSxQluehd
q
q
^C
```

Port number 31518 is not using ssl. So they give me back what I send.

Then try to connect another port.

```bash
bandit16@bandit:~$ openssl s_client -connect localhost:31790
CONNECTED(00000003)
depth=0 CN = localhost
verify error:num=18:self signed certificate
verify return:1
depth=0 CN = localhost
verify return:1
---
Certificate chain
 0 s:/CN=localhost
   i:/CN=localhost
---
Server certificate
-----BEGIN CERTIFICATE-----
MIICBjCCAW+gAwIBAgIEX+MLqjANBgkqhkiG9w0BAQUFADAUMRIwEAYDVQQDDAls
b2NhbGhvc3QwHhcNMTkwNzE5MTc1MTEzWhcNMjAwNzE4MTc1MTEzWjAUMRIwEAYD
VQQDDAlsb2NhbGhvc3QwgZ8wDQYJKoZIhvcNAQEBBQADgY0AMIGJAoGBAJ/VRb96
pcbLAuDkS1AhM5BPmcHTX5Ln97sAtcjN3rtlZxfd0UGkGM/rw8mtWm1KTLaIxHGS
7Mf9VlbORRAYKtUKlrs/Vi0++TCfLXKQh38E4xLCgOavDA/XM8kxqNTRAUegHPQr
ztIEjcAdPZnD5cg1x/G7FLGCPnZve5AfjlDfAgMBAAGjZTBjMBQGA1UdEQQNMAuC
CWxvY2FsaG9zdDBLBglghkgBhvhCAQ0EPhY8QXV0b21hdGljYWxseSBnZW5lcmF0
ZWQgYnkgTmNhdC4gU2VlIGh0dHBzOi8vbm1hcC5vcmcvbmNhdC8uMA0GCSqGSIb3
DQEBBQUAA4GBAGclZ6Q3EOfSZ0m8XuV787/JhnrfVDbToqt6AKlmg2MhieUHBTb5
oqX8fb3/+LeXydOVAOGrI9IlSUSiHgnKQHx1S/rrJqHowJ+GuOpeuH6tsdP241Sz
eufAJT6Qmvyp3MwtqvoXQr/YhzkI70Oa8lRlj4dyJVUCb/zu9DXV+pWm
-----END CERTIFICATE-----
subject=/CN=localhost
issuer=/CN=localhost
---
No client certificate CA names sent
Peer signing digest: SHA512
Server Temp Key: X25519, 253 bits
---
SSL handshake has read 1019 bytes and written 269 bytes
Verification error: self signed certificate
---
New, TLSv1.2, Cipher is ECDHE-RSA-AES256-GCM-SHA384
Server public key is 1024 bit
Secure Renegotiation IS supported
Compression: NONE
Expansion: NONE
No ALPN negotiated
SSL-Session:
    Protocol  : TLSv1.2
    Cipher    : ECDHE-RSA-AES256-GCM-SHA384
    Session-ID: CB30A4D8A659B8864A4302AC56BF219B2DE73C17E23D045A69BC04A059A4CF4E
    Session-ID-ctx: 
    Master-Key: C6851F935C400B5A90F053F8BD23CE5D83E38A6DDBB58489B87B80D6E73969D98E9D2E1EAD2BFF1D00727F64E64B21DD
    PSK identity: None
    PSK identity hint: None
    SRP username: None
    TLS session ticket lifetime hint: 7200 (seconds)
    TLS session ticket:
    0000 - 08 d1 26 0d 0f 63 d6 0b-b1 5a d8 4a 6f de ec b3   ..&..c...Z.Jo...
    0010 - 6f e0 e9 12 1d 9c c9 0a-b6 60 bf 9d 89 d4 c0 0a   o........`......
    0020 - e3 c9 1f cd 32 b1 7d 88-a7 5f 6a 4e 0d 30 db 5e   ....2.}.._jN.0.^
    0030 - b7 10 8d 49 7a 26 ad 7e-0e f0 08 de 95 92 9f f7   ...Iz&.~........
    0040 - 6b d0 1a 1c f8 90 43 58-47 ad 3a b4 6b 6c eb a5   k.....CXG.:.kl..
    0050 - 21 48 f9 0f 13 b1 9d 2c-39 2d 49 cd b1 cc b7 93   !H.....,9-I.....
    0060 - a0 8d 42 67 d4 11 59 c7-aa 96 c4 f2 4f cb 9d 9f   ..Bg..Y.....O...
    0070 - 8f 74 e2 46 f8 ed 8b 3a-58 f7 ad f6 8e 55 7b 4e   .t.F...:X....U{N
    0080 - 3b 29 64 9d b5 fe 8a a5-c2 d4 3a 7a eb 7d 3e 6f   ;)d.......:z.}>o
    0090 - 4a 02 af c8 ca ad 14 86-1d 69 b7 ab b5 4d e6 03   J........i...M..

    Start Time: 1564067399
    Timeout   : 7200 (sec)
    Verify return code: 18 (self signed certificate)
    Extended master secret: yes
---
cluFn7wTiGryunymYOu4RcffSxQluehd
Correct!
-----BEGIN RSA PRIVATE KEY-----
MIIEogIBAAKCAQEAvmOkuifmMg6HL2YPIOjon6iWfbp7c3jx34YkYWqUH57SUdyJ
imZzeyGC0gtZPGujUSxiJSWI/oTqexh+cAMTSMlOJf7+BrJObArnxd9Y7YT2bRPQ
Ja6Lzb558YW3FZl87ORiO+rW4LCDCNd2lUvLE/GL2GWyuKN0K5iCd5TbtJzEkQTu
DSt2mcNn4rhAL+JFr56o4T6z8WWAW18BR6yGrMq7Q/kALHYW3OekePQAzL0VUYbW
JGTi65CxbCnzc/w4+mqQyvmzpWtMAzJTzAzQxNbkR2MBGySxDLrjg0LWN6sK7wNX
x0YVztz/zbIkPjfkU1jHS+9EbVNj+D1XFOJuaQIDAQABAoIBABagpxpM1aoLWfvD
KHcj10nqcoBc4oE11aFYQwik7xfW+24pRNuDE6SFthOar69jp5RlLwD1NhPx3iBl
J9nOM8OJ0VToum43UOS8YxF8WwhXriYGnc1sskbwpXOUDc9uX4+UESzH22P29ovd
d8WErY0gPxun8pbJLmxkAtWNhpMvfe0050vk9TL5wqbu9AlbssgTcCXkMQnPw9nC
YNN6DDP2lbcBrvgT9YCNL6C+ZKufD52yOQ9qOkwFTEQpjtF4uNtJom+asvlpmS8A
vLY9r60wYSvmZhNqBUrj7lyCtXMIu1kkd4w7F77k+DjHoAXyxcUp1DGL51sOmama
+TOWWgECgYEA8JtPxP0GRJ+IQkX262jM3dEIkza8ky5moIwUqYdsx0NxHgRRhORT
8c8hAuRBb2G82so8vUHk/fur85OEfc9TncnCY2crpoqsghifKLxrLgtT+qDpfZnx
SatLdt8GfQ85yA7hnWWJ2MxF3NaeSDm75Lsm+tBbAiyc9P2jGRNtMSkCgYEAypHd
HCctNi/FwjulhttFx/rHYKhLidZDFYeiE/v45bN4yFm8x7R/b0iE7KaszX+Exdvt
SghaTdcG0Knyw1bpJVyusavPzpaJMjdJ6tcFhVAbAjm7enCIvGCSx+X3l5SiWg0A
R57hJglezIiVjv3aGwHwvlZvtszK6zV6oXFAu0ECgYAbjo46T4hyP5tJi93V5HDi
Ttiek7xRVxUl+iU7rWkGAXFpMLFteQEsRr7PJ/lemmEY5eTDAFMLy9FL2m9oQWCg
R8VdwSk8r9FGLS+9aKcV5PI/WEKlwgXinB3OhYimtiG2Cg5JCqIZFHxD6MjEGOiu
L8ktHMPvodBwNsSBULpG0QKBgBAplTfC1HOnWiMGOU3KPwYWt0O6CdTkmJOmL8Ni
blh9elyZ9FsGxsgtRBXRsqXuz7wtsQAgLHxbdLq/ZJQ7YfzOKU4ZxEnabvXnvWkU
YOdjHdSOoKvDQNWu6ucyLRAWFuISeXw9a/9p7ftpxm0TSgyvmfLF2MIAEwyzRqaM
77pBAoGAMmjmIJdjp+Ez8duyn3ieo36yrttF5NSsJLAbxFpdlc1gvtGCWW+9Cq0b
dxviW8+TFVEBl1O4f7HVm6EpTscdDxU+bCXWkfjuRb7Dy9GOtt9JPsX8MBTakzh3
vBgsyi/sN3RqRBcGU40fOoZyfAMT8s1m/uYv52O6IgeuZ/ujbjY=
-----END RSA PRIVATE KEY-----

closed
```

The port numbered 31790 send me a credential.

At this point, I copy write-up.

Make a .key file and connect by ssh using that key file to next level.

```bash
bandit16@bandit:~$ cat >  /tmp/k.key
-----BEGIN RSA PRIVATE KEY-----
MIIEogIBAAKCAQEAvmOkuifmMg6HL2YPIOjon6iWfbp7c3jx34YkYWqUH57SUdyJ
imZzeyGC0gtZPGujUSxiJSWI/oTqexh+cAMTSMlOJf7+BrJObArnxd9Y7YT2bRPQ
Ja6Lzb558YW3FZl87ORiO+rW4LCDCNd2lUvLE/GL2GWyuKN0K5iCd5TbtJzEkQTu
DSt2mcNn4rhAL+JFr56o4T6z8WWAW18BR6yGrMq7Q/kALHYW3OekePQAzL0VUYbW
JGTi65CxbCnzc/w4+mqQyvmzpWtMAzJTzAzQxNbkR2MBGySxDLrjg0LWN6sK7wNX
x0YVztz/zbIkPjfkU1jHS+9EbVNj+D1XFOJuaQIDAQABAoIBABagpxpM1aoLWfvD
KHcj10nqcoBc4oE11aFYQwik7xfW+24pRNuDE6SFthOar69jp5RlLwD1NhPx3iBl
J9nOM8OJ0VToum43UOS8YxF8WwhXriYGnc1sskbwpXOUDc9uX4+UESzH22P29ovd
d8WErY0gPxun8pbJLmxkAtWNhpMvfe0050vk9TL5wqbu9AlbssgTcCXkMQnPw9nC
YNN6DDP2lbcBrvgT9YCNL6C+ZKufD52yOQ9qOkwFTEQpjtF4uNtJom+asvlpmS8A
vLY9r60wYSvmZhNqBUrj7lyCtXMIu1kkd4w7F77k+DjHoAXyxcUp1DGL51sOmama
+TOWWgECgYEA8JtPxP0GRJ+IQkX262jM3dEIkza8ky5moIwUqYdsx0NxHgRRhORT
8c8hAuRBb2G82so8vUHk/fur85OEfc9TncnCY2crpoqsghifKLxrLgtT+qDpfZnx
SatLdt8GfQ85yA7hnWWJ2MxF3NaeSDm75Lsm+tBbAiyc9P2jGRNtMSkCgYEAypHd
HCctNi/FwjulhttFx/rHYKhLidZDFYeiE/v45bN4yFm8x7R/b0iE7KaszX+Exdvt
SghaTdcG0Knyw1bpJVyusavPzpaJMjdJ6tcFhVAbAjm7enCIvGCSx+X3l5SiWg0A
R57hJglezIiVjv3aGwHwvlZvtszK6zV6oXFAu0ECgYAbjo46T4hyP5tJi93V5HDi
Ttiek7xRVxUl+iU7rWkGAXFpMLFteQEsRr7PJ/lemmEY5eTDAFMLy9FL2m9oQWCg
R8VdwSk8r9FGLS+9aKcV5PI/WEKlwgXinB3OhYimtiG2Cg5JCqIZFHxD6MjEGOiu
L8ktHMPvodBwNsSBULpG0QKBgBAplTfC1HOnWiMGOU3KPwYWt0O6CdTkmJOmL8Ni
blh9elyZ9FsGxsgtRBXRsqXuz7wtsQAgLHxbdLq/ZJQ7YfzOKU4ZxEnabvXnvWkU
YOdjHdSOoKvDQNWu6ucyLRAWFuISeXw9a/9p7ftpxm0TSgyvmfLF2MIAEwyzRqaM
77pBAoGAMmjmIJdjp+Ez8duyn3ieo36yrttF5NSsJLAbxFpdlc1gvtGCWW+9Cq0b
dxviW8+TFVEBl1O4f7HVm6EpTscdDxU+bCXWkfjuRb7Dy9GOtt9JPsX8MBTakzh3
vBgsyi/sN3RqRBcGU40fOoZyfAMT8s1m/uYv52O6IgeuZ/ujbjY=
-----END RSA PRIVATE KEY-----bandit16@bandit:~$ ssh -i /tmp/k.key bandit17@localhost 
Could not create directory '/home/bandit16/.ssh'.
The authenticity of host 'localhost (127.0.0.1)' can't be established.
ECDSA key fingerprint is SHA256:98UL0ZWr85496EtCRkKlo20X3OPnyPSB5tB5RPbhczc.
Are you sure you want to continue connecting (yes/no)? yes
Failed to add the host to the list of known hosts (/home/bandit16/.ssh/known_hosts).
This is a OverTheWire game server. More information on http://www.overthewire.org/wargames

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@         WARNING: UNPROTECTED PRIVATE KEY FILE!          @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
Permissions 0644 for '/tmp/k.key' are too open.
It is required that your private key files are NOT accessible by others.
This private key will be ignored.
Load key "/tmp/k.key": bad permissions
bandit17@localhost's password: 
Permission denied, please try again.
bandit17@localhost's password: 
```

But, I got a warning message that said about private key file's permission.

So I changed permission of key file and retry.

```bash
bandit16@bandit:~$ chmod 600 /tmp/k.key
bandit16@bandit:~$ ssh -i /tmp/k.key bandit17@localhost 
Could not create directory '/home/bandit16/.ssh'.
The authenticity of host 'localhost (127.0.0.1)' can't be established.
ECDSA key fingerprint is SHA256:98UL0ZWr85496EtCRkKlo20X3OPnyPSB5tB5RPbhczc.
Are you sure you want to continue connecting (yes/no)? yes
Failed to add the host to the list of known hosts (/home/bandit16/.ssh/known_hosts).
This is a OverTheWire game server. More information on http://www.overthewire.org/wargames

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

If you find any problems, please report them to Steven or morla on
irc.overthewire.org.

--[ Playing the games ]--

  This machine might hold several wargames. 
  If you are playing "somegame", then:

    * USERNAMES are somegame0, somegame1, ...
    * Most LEVELS are stored in /somegame/.
    * PASSWORDS for each level are stored in /etc/somegame_pass/.

  Write-access to homedirectories is disabled. It is advised to create a
  working directory with a hard-to-guess name in /tmp/.  You can use the
  command "mktemp -d" in order to generate a random and hard to guess
  directory in /tmp/.  Read-access to both /tmp/ and /proc/ is disabled
  so that users can not snoop on eachother. Files and directories with 
  easily guessable or short names will be periodically deleted!
	
  Please play nice:
      
    * don't leave orphan processes running
    * don't leave exploit-files laying around
    * don't annoy other players
    * don't post passwords or spoilers
    * again, DONT POST SPOILERS! 
      This includes writeups of your solution on your blog or website!

--[ Tips ]--

  This machine has a 64bit processor and many security-features enabled
  by default, although ASLR has been switched off.  The following
  compiler flags might be interesting:

    -m32                    compile for 32bit
    -fno-stack-protector    disable ProPolice
    -Wl,-z,norelro          disable relro 

  In addition, the execstack tool can be used to flag the stack as
  executable on ELF binaries.

  Finally, network-access is limited for most levels by a local
  firewall.

--[ Tools ]--

 For your convenience we have installed a few usefull tools which you can find
 in the following locations:

    * pwndbg (https://github.com/pwndbg/pwndbg) in /usr/local/pwndbg/
    * peda (https://github.com/longld/peda.git) in /usr/local/peda/
    * gdbinit (https://github.com/gdbinit/Gdbinit) in /usr/local/gdbinit/
    * pwntools (https://github.com/Gallopsled/pwntools)
    * radare2 (http://www.radare.org/)
    * checksec.sh (http://www.trapkit.de/tools/checksec.html) in /usr/local/bin/checksec.sh

--[ More information ]--

  For more information regarding individual wargames, visit
  http://www.overthewire.org/wargames/

  For support, questions or comments, contact us through IRC on
  irc.overthewire.org #wargames.

  Enjoy your stay!
```

Yeah. I login to next level. Now, I will find this level's password. And I already know where it is by past level.

```bash
bandit17@bandit:~$ cat /etc/bandit_pass/bandit17
xLYVMN9WE5zQ5vHacb0sZEVqbrp7nBTn
```

password is 'xLYVMN9WE5zQ5vHacb0sZEVqbrp7nBTn'.