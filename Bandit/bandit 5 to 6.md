# bandit 5 to 6

The password for the next level is stored in a file somewhere under the **inhere** directory and has all of the following properties:

- human-readable
- 1033 bytes in size
- not executable

## Commands you may need to solve this level

ls, cd, cat, file, du, find

---

because 3 conditions are added, I started after studying 'find' instruction.(so many options..)

combining last and this, I can find one file that satisfies all conditions.

First of all, find **human-readable** files by 'du' and find **1033 bytes size** file in them by 'find'.

```bash
bandit5@bandit:~/inhere$ du -h | file * | find . -size 1033c
./maybehere07/.file2
bandit5@bandit:~/inhere$ ls -al ./maybehere07
total 56
drwxr-x---  2 root bandit5 4096 Oct 16  2018 .
drwxr-x--- 22 root bandit5 4096 Oct 16  2018 ..
-rwxr-x---  1 root bandit5 3663 Oct 16  2018 -file1
-rwxr-x---  1 root bandit5 3065 Oct 16  2018 .file1
-rw-r-----  1 root bandit5 2488 Oct 16  2018 -file2
-rw-r-----  1 root bandit5 1033 Oct 16  2018 .file2
-rwxr-x---  1 root bandit5 3362 Oct 16  2018 -file3
-rwxr-x---  1 root bandit5 1997 Oct 16  2018 .file3
-rwxr-x---  1 root bandit5 4130 Oct 16  2018 spaces file1
-rw-r-----  1 root bandit5 9064 Oct 16  2018 spaces file2
-rwxr-x---  1 root bandit5 1022 Oct 16  2018 spaces file3
bandit5@bandit:~/inhere$ cat ./maybehere07/.file2
DXjZPULLxYr17uwoI01bNLQbtFemEgo7
```

password is "DXjZPULLxYr17uwoI01bNLQbtFemEgo7".