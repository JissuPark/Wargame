# bandit 7 to 8

The password for the next level is stored in the file **data.txt** next to the word **millionth**

## Commands you may need to solve this level

grep, sort, uniq, strings, base64, tr, tar, gzip, bzip2, xxd

---

Use 'dat', '|(pipe)', 'grep -w'. There is nothing to explain.

```bash
bandit7@bandit:~$ cat data.txt | grep -w millionth
millionth	cvX2JJa4CFALtqS87jk27qwqGhBM9plV
```

password is 'cvX2JJa4CFALtqS87jk27qwqGhBM9plV'.

