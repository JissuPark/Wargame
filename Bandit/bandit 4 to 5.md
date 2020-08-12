# bandit 4 to 5

The password for the next level is stored in the only human-readable file in the **inhere **directory. Tip: if your terminal is messed up, try the “reset” command.

## Commands you may need to solve this level

ls, cd, cat, file, du, find

---



```bash
bandit4@bandit:~$ ls
inhere
bandit4@bandit:~$ ls -al inhere/
total 48
drwxr-xr-x 2 root    root    4096 Oct 16  2018 .
drwxr-xr-x 3 root    root    4096 Oct 16  2018 ..
-rw-r----- 1 bandit5 bandit4   33 Oct 16  2018 -file00
-rw-r----- 1 bandit5 bandit4   33 Oct 16  2018 -file01
-rw-r----- 1 bandit5 bandit4   33 Oct 16  2018 -file02
-rw-r----- 1 bandit5 bandit4   33 Oct 16  2018 -file03
-rw-r----- 1 bandit5 bandit4   33 Oct 16  2018 -file04
-rw-r----- 1 bandit5 bandit4   33 Oct 16  2018 -file05
-rw-r----- 1 bandit5 bandit4   33 Oct 16  2018 -file06
-rw-r----- 1 bandit5 bandit4   33 Oct 16  2018 -file07
-rw-r----- 1 bandit5 bandit4   33 Oct 16  2018 -file08
-rw-r----- 1 bandit5 bandit4   33 Oct 16  2018 -file09
```

There are 10 files and they have same size. So I opened all files.(ignorantly)

```bash
bandit4@bandit:~$ cd inhere/
bandit4@bandit:~/inhere$ ls
-file00  -file01  -file02  -file03  -file04  -file05  -file06  -file07  -file08  -file09
bandit4@bandit:~/inhere$ cat ./-file00
����������~%	C[�걱>��| �
bandit4@bandit:~/inhere$ cat ./-file01
���U"7�w���H��ê�Q����(���#���
bandit4@bandit:~/inhere$ cat ./-file02
�T�v��(�ִ�����A*�
2J�Ş؇_�y7
bandit4@bandit:~/inhere$ cat ./-file03
��.A��u��#���w$N?c�-��Db3��=��
bandit4@bandit:~/inhere$ cat ./-file04
�=<�W�����ht�Z��!��{�U
                          �
bandit4@bandit:~/inhere$ cat ./-file05
+��pm���;��:D��^��@�gl�Q�
bandit4@bandit:~/inhere$ cat ./-file06
��@�%@���ZP*E��1�V���̫*����
bandit4@bandit:~/inhere$ cat ./-file07
koReBOKuIDDepwhWk7jZC0RTdopnAYKh
bandit4@bandit:~/inhere$ cat ./-file08
FPn�
      '�U���M��/u
                 XS
�mu�z���х
bandit4@bandit:~/inhere$ cat ./-file09
N�{���Y�d4����]3�����9(�
```

I recognize what is password. But writer may expect  for us to use 'du' instruction.

So I add one more way to get password.

```bash
bandit4@bandit:~/inhere$ du -h | file ./*
./-file00: data
./-file01: data
./-file02: data
./-file03: data
./-file04: data
./-file05: data
./-file06: data
./-file07: ASCII text
./-file08: data
./-file09: data
```

if using 'du' instruction, don't need to open all files:)

anyway,

password is "koReBOKuIDDepwhWk7jZC0RTdopnAYKh".