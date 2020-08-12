# bandit 28 to 29

There is a git repository at `ssh://bandit28-git@localhost/home/bandit28-git/repo`. The password for the user `bandit28-git` is the same as for the user `bandit28`.

Clone the repository and find the password for the next level.

## Commands you may need to solve this level

git

---

### solve

> This time, the password is missing. 
>
> ```bash
> bandit28@bandit:/tmp/ttteee/repo$ cat README.md 
> # Bandit Notes
> Some notes for level29 of bandit.
> 
> ## credentials
> 
> - username: bandit29
> - password: xxxxxxxxxx
> 
> ```
>
> So I have to find whole directory and logs.
>
> I did, I can't find any hints in .git directory but I found a commit in logs.
>
> ```bash
> bandit28@bandit:/tmp/ttteee/repo$ git log 
> commit 073c27c130e6ee407e12faad1dd3848a110c4f95
> Author: Morla Porla <morla@overthewire.org>
> Date:   Tue Oct 16 14:00:39 2018 +0200
> 
>     fix info leak
> 
> commit 186a1038cc54d1358d42d468cdc8e3cc28a93fcb
> Author: Morla Porla <morla@overthewire.org>
> Date:   Tue Oct 16 14:00:39 2018 +0200
> 
>     add missing data
> 
> commit b67405defc6ef44210c53345fc953e6a21338cc7
> Author: Ben Dover <noone@overthewire.org>
> Date:   Tue Oct 16 14:00:39 2018 +0200
> 
>     initial commit of README.md
> ```
>
> I think 'fix info leak' means "restore the data". So I choose that and draw back.
>
> But it isn't.... I did check every commit.
>
> ```bash
> bandit28@bandit:/tmp/ttteee/repo$ git checkout 186a1038cc54d1358d42d468cdc8e3cc28a93fcb
> Previous HEAD position was b67405d... initial commit of README.md
> HEAD is now at 186a103... add missing data
> bandit28@bandit:/tmp/ttteee/repo$ cat README.md 
> # Bandit Notes
> Some notes for level29 of bandit.
> 
> ## credentials
> 
> - username: bandit29
> - password: bbc96594b4e001778eee9975372716b2
> ```
>
> The middle one has  password.
>
> password is 'bbc96594b4e001778eee9975372716b2'.