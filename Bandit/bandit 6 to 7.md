# bandit 6 to 7

he password for the next level is stored **somewhere on the server** and has all of the following properties:

- owned by user bandit7
- owned by group bandit6
- 33 bytes in size

## Commands you may need to solve this level

ls, cd, cat, file, du, find, grep

---

Like before, there are 3 conditions. 

Just using 'find' can give me answer file. but there are a lot of error msg. So I print only what I want to see by '2>/dev/null'

```bash
bandit6@bandit:~$ find / -user  bandit7 -group bandit6 -size 33c
find: ‘/run/lvm’: Permission denied
find: ‘/run/screen/S-bandit20’: Permission denied
find: ‘/run/screen/S-bandit0’: Permission denied
...
find: ‘/var/cache/apt/archives/partial’: Permission denied
/var/lib/dpkg/info/bandit7.password
find: ‘/var/lib/apt/lists/partial’: Permission denied
...
find: ‘/proc/12196/fdinfo/5’: No such file or directory
find: ‘/boot/lost+found’: Permission denied
```

```bash
bandit6@bandit:~$ find / -user  bandit7 -group bandit6 -size 33c 2>/dev/null
/var/lib/dpkg/info/bandit7.password
bandit6@bandit:~$ cat /var/lib/dpkg/info/bandit7.password 
HKBPTKQnIay4Fw76bEy8PVxKEDQRKTzs
```

password is 'HKBPTKQnIay4Fw76bEy8PVxKEDQRKTzs'.

