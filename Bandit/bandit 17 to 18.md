# bandit 17 to 18

There are 2 files in the homedirectory: **passwords.old and passwords.new**. The password for the next level is in **passwords.new** and is the only line that has been changed between**passwords.old and passwords.new**

**NOTE: if you have solved this level and see ‘Byebye!’ when trying to log into bandit18, this is related to the next level, bandit19**

## Commands you may need to solve this level

cat, grep, ls, diff

---

Use 'diff' instruction.

```bash
bandit17@bandit:~$ diff passwords.old passwords.new 
42c42
< hlbSBPAWJmL6WFDb06gpTx1pPButblOA
---
> kfBf3eYk5BPBRzwjqutbbfE887SVc5Yd
```

password is 'kfBf3eYk5BPBRzwjqutbbfE887SVc5Yd'.