# bandit 8 to 9

The password for the next level is stored in the file **data.txt** and is the only line of text that occurs only once

## Commands you may need to solve this level

grep, sort, uniq, strings, base64, tr, tar, gzip, bzip2, xxd

---

Use 'sort', 'uniq' instruction. 

Because I didn't know both, I have been around for a while about instructions.

After then, I knew what I need. There is one count data in file. 

So, I sort the data file by 'sort' and find unique data by 'uniq'.

```bash
bandit8@bandit:~$ sort data.txt | uniq -u
UsvVyFSfZZWbi6wgC7dAFyFuR6jQQUhR
```

password is 'UsvVyFSfZZWbi6wgC7dAFyFuR6jQQUhR'.