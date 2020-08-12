# bandit 9 to 10

he password for the next level is stored in the file **data.txt** in one of the few human-readable strings, beginning with several ‘=’ characters.

## Commands you may need to solve this level

grep, sort, uniq, strings, base64, tr, tar, gzip, bzip2, xxd

---

Use 'strings' and 'grep' instruction. 

It's possible to find password by just using 'strings', but for making a good looks I use 'grep' also

```bash
bandit9@bandit:~$ strings data.txt | grep -w ===
2========== the
========== password
========== isa
========== truKLdjsbJ5g7yyJ2X2R0o3a5HQJFuLk
```

password is 'truKLdjsbJ5g7yyJ2X2R0o3a5HQJFuLk'.