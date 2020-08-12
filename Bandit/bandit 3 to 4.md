# bandit 3 to 4

The password for the next level is stored in a hidden file in the **inhere** directory.

## Commands you may need to solve this level

ls, cd, cat, file, du, find

---

Use same instruction as before. But I add  option of 'ls' instruction. 

```bash
bandit3@bandit:~$ ls
inhere
bandit3@bandit:~$ cd inhere/
bandit3@bandit:~/inhere$ ls
bandit3@bandit:~/inhere$ ls -al
total 12
drwxr-xr-x 2 root    root    4096 Oct 16  2018 .
drwxr-xr-x 3 root    root    4096 Oct 16  2018 ..
-rw-r----- 1 bandit4 bandit3   33 Oct 16  2018 .hidden
bandit3@bandit:~/inhere$ cat .hidden 
pIwrPrtPN36QITSp3EQaw936yaFoFgAB
```

password is 'pIwrPrtPN36QITSp3EQaw936yaFoFgAB'.