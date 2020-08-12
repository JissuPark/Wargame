# bandit 27 to 28

There is a git repository at `ssh://bandit27-git@localhost/home/bandit27-git/repo`. The password for the user `bandit27-git` is the same as for the user `bandit27`.

Clone the repository and find the password for the next level.

## Commands you may need to solve this level

git

---

### solve

> Just enter some commands of git.
>
> ```bash
> bandit27@bandit:~$ mkdir /tmp/vvvvdddd
> bandit27@bandit:~$ cd /tmp//vvvvdddd
> bandit27@bandit:/tmp/vvvvdddd$ ls
> bandit27@bandit:/tmp/vvvvdddd$ git clone ssh://bandit27-git@localhost/home/bandit27-git/repo
> Cloning into 'repo'...
> Could not create directory '/home/bandit27/.ssh'.
> The authenticity of host 'localhost (127.0.0.1)' can't be established.
> ECDSA key fingerprint is SHA256:98UL0ZWr85496EtCRkKlo20X3OPnyPSB5tB5RPbhczc.
> Are you sure you want to continue connecting (yes/no)? yes
> Failed to add the host to the list of known hosts (/home/bandit27/.ssh/known_hosts).
> This is a OverTheWire game server. More information on http://www.overthewire.org/wargames
> 
> bandit27-git@localhost's password: 
> remote: Counting objects: 3, done.
> remote: Compressing objects: 100% (2/2), done.
> remote: Total 3 (delta 0), reused 0 (delta 0)
> Receiving objects: 100% (3/3), done.
> bandit27@bandit:/tmp/vvvvdddd$ ls
> repo
> bandit27@bandit:/tmp/vvvvdddd$ cd repo/
> bandit27@bandit:/tmp/vvvvdddd/repo$ ls
> README
> bandit27@bandit:/tmp/vvvvdddd/repo$ cat README 
> The password to the next level is: 0ef186ac70e04ea33b4c1853d2526fa2
> ```
>
> password is '0ef186ac70e04ea33b4c1853d2526fa2'.
>
>  