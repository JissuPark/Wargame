# bandit 25 to 26

Logging in to bandit26 from bandit25 should be fairly easy… The shell for user bandit26 is not **/bin/bash**, but something else. Find out what it is, how it works and how to break out of it.

## Commands you may need to solve this level

ssh, cat, more, vi, ls, id, pwd

---

# solve

> This problem has a ssh key. So I can access to next level, but it is not bash shell.
>
> even, the shell turn off direct. 
>
> Luckily, I know passwd file has a lot of data, so I saw it.
>
> ```bash
> bandit25@bandit:~$ ls
> bandit26.sshkey
> bandit25@bandit:~$ cat /etc/
> Display all 174 possibilities? (y or n)
> bandit25@bandit:~$ cat /etc/passwd
> ...
> bandit26:x:11026:11026:bandit level 26:/home/bandit26:/usr/bin/showtext
> ```
>
> The shell of next level is 'showtext' shell. But there isn't a lot of informations.
>
> Even google told me about "bandit 25 to 26 ~~~ ". 
>
> So I Just see the write-up and pass this level quickly as fast as I can.
>
> First, resize window to be small until they show me at once.
>
> ![1564344686691](C:\Users\qkrwl\AppData\Roaming\Typora\typora-user-images\1564344686691.png)
>
> This mode is made by 'more' instruction. It makes me to edit like vi editor by push 'v'.
>
> And enter the command doing what I want. 
>
> ```bash
> :e /etc/bandit_pass/bandit26
> 5czgV9L3Xx8JPOyRbXh6lQbmIOWvPT6Z
> ```
>
> password is '5czgV9L3Xx8JPOyRbXh6lQbmIOWvPT6Z'.