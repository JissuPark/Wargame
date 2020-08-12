# bandit 29 to 30

There is a git repository at `ssh://bandit29-git@localhost/home/bandit29-git/repo`. The password for the user `bandit29-git` is the same as for the user `bandit29`.

Clone the repository and find the password for the next level.

## Commands you may need to solve this level

git

---

### solve

> This time, commit log is not useful. 
>
> So I did check whole directories.
>
> ```bash
> bandit29@bandit:/tmp/mmmnnnbb/repo$ cat README.md 
> # Bandit Notes
> Some notes for bandit30 of bandit.
> 
> ## credentials
> 
> - username: bandit30
> - password: <no passwords in production!>
> ```
>
> If writers gave me a hint, maybe it is "no passwords in production!".
>
> As they say, there is a part of production of password.
>
> During checking whole directories, I found remote references.
>
> ```bash
> bandit29@bandit:/tmp/mmmnnnbb/repo/.git$ cat packed-refs 
> # pack-refs with: peeled fully-peeled 
> 33ce2e95d9c5d6fb0a40e5ee9a2926903646b4e3 refs/remotes/origin/dev
> 84abedc104bbc0c65cb9eb74eb1d3057753e70f8 refs/remotes/origin/master
> 2af54c57b2cb29a72e8f3e84a9e60c019c252b75 refs/remotes/origin/sploits-dev
> ```
>
> but I don't know what refs are doing , I search such a long time. 
>
> As a result , the 'refs' works like 'logs'. 
>
> Check log more details. Totally, there are 4 commit refs repeatedly.
>
> So I checked all refs and found the password.
>
> ```bash
> bandit29@bandit:/tmp/mmmnnnbb/repo$ git checkout 33ce2e95d9c5d6fb0a40e5ee9a2926903646b4e3
> Previous HEAD position was 2af54c5... add some silly exploit, just for shit and giggles
> HEAD is now at 33ce2e9... add data needed for development
> bandit29@bandit:/tmp/mmmnnnbb/repo$ ls
> code  README.md 
> bandit29@bandit:/tmp/mmmnnnbb/repo$ cat README.md 
> # Bandit Notes
> Some notes for bandit30 of bandit.
> 
> ## credentials
> 
> - username: bandit30
> - password: 5b90576bedb2cc04c86a9e924ce42faf
> ```
>
> password is '5b90576bedb2cc04c86a9e924ce42faf'.
>
> 