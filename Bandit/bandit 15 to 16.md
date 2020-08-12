# bandit 15 to 16

The password for the next level can be retrieved by submitting the password of the current level to **port 30001 on localhost** using SSL encryption.

**Helpful note: Getting “HEARTBEATING” and “Read R BLOCK”? Use -ign_eof and read the “CONNECTED COMMANDS” section in the manpage. Next to ‘R’ and ‘Q’, the ‘B’ command also works in this version of that command…**

## Commands you may need to solve this level

ssh, telnet, nc, openssl, s_client, nmap

---

Use 'openssl' and 's_client' instructions. 

I didn't know about all these instruction. So I found how these two instruction co-work together.

's_client' give me a connection with remote server using 'ssl'. 

And 'openssl' receives 's_client' and other options. 

If using them together, they tell me about ssl connection informations.

I connected localhost server with these instructions and gave a current password.

Then they returned next level's password.

```bash
bandit15@bandit:~$ openssl s_client -connect localhost:30001
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
MIICBjCCAW+gAwIBAgIEBadydTANBgkqhkiG9w0BAQUFADAUMRIwEAYDVQQDDAls
b2NhbGhvc3QwHhcNMTkwMjI3MDg1MTQ5WhcNMjAwMjI3MDg1MTQ5WjAUMRIwEAYD
VQQDDAlsb2NhbGhvc3QwgZ8wDQYJKoZIhvcNAQEBBQADgY0AMIGJAoGBAMyEZzRA
+5ll7Ap2bwla+8x39mTviZKqrjnmLuTZj1U3mugt3G2JI5loXyjnFxlXnHUGy/xI
OiACFOEJCce2VIkarMa1Cy13wtGuLoZxjcYSAIMzIOPykCh9+FJ89Tt1TIVXmO0C
TJaxFMhKdX0ALZlxjN1+xoZgeOtN7yfhprjjAgMBAAGjZTBjMBQGA1UdEQQNMAuC
CWxvY2FsaG9zdDBLBglghkgBhvhCAQ0EPhY8QXV0b21hdGljYWxseSBnZW5lcmF0
ZWQgYnkgTmNhdC4gU2VlIGh0dHBzOi8vbm1hcC5vcmcvbmNhdC8uMA0GCSqGSIb3
DQEBBQUAA4GBACNP1/t8pfANluA2MuoxCAkie0bDCUL/ZV7FDaH1YUAEG7wEZVFJ
Pt8+6L8HkLYcuCPtjc2uxA8yEiqS7fiYRU26PmrQXzm09W0ah1pq+7NGMLKz596B
AIpiTkVpA7YCUvGcYvz6yXS202e2GbLOulF2l9kx6hhhBCWubeqh2IjR
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
    Session-ID: 1CC8A21A8A0C6DB27CFE701A92A07C8E52FF96078FFC66B6E3B0AF87597E0CAE
    Session-ID-ctx: 
    Master-Key: 025619DB2E5DD14F1BA3649A5B4D159AA75A19948A6CDB45A6D97F16C8C7380C1FC7326680F4ECB146886633B0EEE4BA
    PSK identity: None
    PSK identity hint: None
    SRP username: None
    TLS session ticket lifetime hint: 7200 (seconds)
    TLS session ticket:
    0000 - df 12 86 44 83 09 d4 62-75 55 25 0c f8 4f 2c 53   ...D...buU%..O,S
    0010 - ef 16 5e e9 7a 74 8e a4-4f 35 ac ab ff 3d 4d 8e   ..^.zt..O5...=M.
    0020 - 32 80 f9 b9 39 28 67 74-4c 8f f5 7c e5 1a 3b 7c   2...9(gtL..|..;|
    0030 - fa 87 64 83 45 28 7d ed-d9 90 37 a9 12 a9 7c b0   ..d.E(}...7...|.
    0040 - ea 26 8f e7 37 31 6e c9-a1 7d f2 24 37 0a 76 dc   .&..71n..}.$7.v.
    0050 - ce b0 e8 5a 8b 93 f0 b3-9c 5e d8 25 89 5c 07 50   ...Z.....^.%.\.P
    0060 - 02 bd 0c ae 64 f0 6d 88-95 5c 35 a6 4e d7 d1 51   ....d.m..\5.N..Q
    0070 - 5a 6c ee 27 2a 6b e1 53-d0 bb b1 dd f6 7d 6a 6f   Zl.'*k.S.....}jo
    0080 - 83 b9 c3 a2 77 a8 17 3f-4d 6f 4e 62 96 6b bc 6b   ....w..?MoNb.k.k
    0090 - 80 f2 94 0c 9e 67 3d 73-5d a9 3e 33 d1 91 9c 21   .....g=s].>3...!

    Start Time: 1564062909
    Timeout   : 7200 (sec)
    Verify return code: 18 (self signed certificate)
    Extended master secret: yes
---
BfMYroe26WYalil77FoDi9qh59eK5xNr
Correct!
cluFn7wTiGryunymYOu4RcffSxQluehd

closed
```

password is 'cluFn7wTiGryunymYOu4RcffSxQluehd'.

