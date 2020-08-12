# bandit 10 to 11

The password for the next level is stored in the file **data.txt**, which contains base64 encoded data

## Commands you may need to solve this level

grep, sort, uniq, strings, base64, tr, tar, gzip, bzip2, xxd

---

They gave me a hint like an answer.

Just use 'base64'.

```bash
bandit10@bandit:~$ base64 -d data.txt 
The password is IFukwKGsFW8MOq3IRFqrxE1hxTNEbUPR
```

 password is 'IFukwKGsFW8MOq3IRFqrxE1hxTNEbUPR'.

