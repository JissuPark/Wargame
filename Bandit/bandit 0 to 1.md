# bandit 0 to 1

The password for the next level is stored in a file called **readme** located in the home directory. Use this password to log into bandit1 using SSH. Whenever you find a password for a level, use SSH (on port 2220) to log into that level and continue the game.

## Commands you may need to solve this level

ls, cd, cat, file, du, find

---

I use instruction 'ls' and 'cat'. too easy.

```bash
bandit0@bandit:~$ ls
readme
bandit0@bandit:~$ cat readme 
boJ9jbbUNNfktd78OOpsqOltutMc3MY1
```

password is "boJ9jbbUNNfktd78OOpsqOltutMc3MY1"

