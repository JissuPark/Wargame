# bandit 20 to 21

There is a setuid binary in the homedirectory that does the following: it makes a connection to localhost on the port you specify as a commandline argument. It then reads a line of text from the connection and compares it to the password in the previous level (bandit20). If the password is correct, it will transmit the password for the next level (bandit21).

**NOTE:** Try connecting to your own network daemon to see if it works as you think

## Commands you may need to solve this level

ssh, nc, cat, bash, screen, tmux, Unix ‘job control’ (bg, fg, jobs, &, CTRL-Z, …)

---

### solve

> Use 'nc' instuction and '-l' option.
>
> If using 'nc' with '-l' option, it can be listening mode.
>
> For solving this level, 
>
> First, make two windows. One is llike server, the other is like client.
>
> As The problem said us ./suconnect is connect another localhost and receive data, I sent a password in another window.
>
> <receiving part>
>
> ```bash
> bandit20@bandit:~$ ./suconnect 2232
> Read: GbKksEFF4yrVs6il55v6gwY5aVje5f0j
> Password matches, sending next password
> ```
>
> <sending part>
>
> ```bash
> bandit20@bandit:~$ nc localhost -l -p 2232
> GbKksEFF4yrVs6il55v6gwY5aVje5f0j
> gE269g2h3mw3pwgrj0Ha9Uoqen1c9DGr
> ```
>
> password is 'gE269g2h3mw3pwgrj0Ha9Uoqen1c9DGr'.

