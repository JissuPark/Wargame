# bandit 14 to 15

The password for the next level can be retrieved by submitting the password of the current level to **port 30000 on localhost**.

## Commands you may need to solve this level

ssh, telnet, nc, openssl, s_client, nmap

---

Use 'telnet' instruction.

Too simple. No comment.

```bash
bandit14@bandit:~$ telnet localhost 30000
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
4wcYUJFw0k0XLShlDzztnTBHiqxU3b3e
Correct!
BfMYroe26WYalil77FoDi9qh59eK5xNr

Connection closed by foreign host.
```

password is 'BfMYroe26WYalil77FoDi9qh59eK5xNr'.