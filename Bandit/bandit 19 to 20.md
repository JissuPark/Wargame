# bandit 19 to 20

To gain access to the next level, you should use the setuid binary in the homedirectory. Execute it without arguments to find out how to use it. The password for this level can be found in the usual place (/etc/bandit_pass), after you have used the setuid binary.

---

There is one executabled file. 

The file may have a 'setuid' function. If it is right, I can do some jobs having next level permission by the file.

Check how to use this file.

```bash
bandit19@bandit:~$ ./bandit20-do 
Run a command as another user.
  Example: ./bandit20-do id
```

Just run the file. I got a usage about this file. 

I think this program has a command instruction as a parameter.

Then try some command instruction.

```bash
bandit19@bandit:~$ ./bandit20-do id
uid=11019(bandit19) gid=11019(bandit19) euid=11020(bandit20) groups=11019(bandit19)
bandit19@bandit:~$ ./bandit20-do ls
bandit20-do
```

Yeah. My guess is right. Now, I can find a password of next level.

```bash
bandit19@bandit:~$ ./bandit20-do cat /etc/bandit_pass/bandit20
GbKksEFF4yrVs6il55v6gwY5aVje5f0j
```

password is 'GbKksEFF4yrVs6il55v6gwY5aVje5f0j'.