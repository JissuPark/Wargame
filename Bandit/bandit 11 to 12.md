# bandit 11 to 12

The password for the next level is stored in the file **data.txt**, where all lowercase (a-z) and uppercase (A-Z) letters have been rotated by 13 positions

## Commands you may need to solve this level

grep, sort, uniq, strings, base64, tr, tar, gzip, bzip2, xxd

---

Use 'cat' and 'tr' instructions. 

It's too hard to understand 'tr' operands.

They want to translate letters like ceasor cypher for me. x(

```bash
bandit11@bandit:~$ cat data.txt 
Gur cnffjbeq vf 5Gr8L4qetPEsPk8htqjhRK8XSP6x2RHh
bandit11@bandit:~$ cat data.txt | tr a-zA-Z n-za-mN-ZA-M
The password is 5Te8Y4drgCRfCx8ugdwuEX8KFC6k2EUu
```

password is '5Te8Y4drgCRfCx8ugdwuEX8KFC6k2EUu'.

