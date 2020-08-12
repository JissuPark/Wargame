# bandit 12 to 13

The password for the next level is stored in the file **data.txt**, which is a hexdump of a file that has been repeatedly compressed. For this level it may be useful to create a directory under /tmp in which you can work using mkdir. For example: mkdir /tmp/myname123. Then copy the datafile using cp, and rename it using mv (read the manpages!)

## Commands you may need to solve this level

grep, sort, uniq, strings, base64, tr, tar, gzip, bzip2, xxd, mkdir, cp, mv, file

---

Damn it compressed.

This problem has 3 steps.

1. check file type by 'file'
2. rename file by 'mv'
3. decompress by 'gizp','bzip2','tar'

I have repeated this steps 8times....

before decompress, I had to move a data file and translate hexdump file to binary file by 'xxd -r'.

```bash
bandit12@bandit:~$ ls
data.txt
bandit12@bandit:~$ mkdir /tmp/jisuu
bandit12@bandit:~$ cp data.txt  /tmp/jisuu
bandit12@bandit:~$ cd /tmp/jisuu
bandit12@bandit:/tmp/jisuu$ ls
data.txt
bandit12@bandit:/tmp/jisuu$ xxd -r data.txt > data
```

Then, time to decompress!(888888times!!!!)

```bash
bandit12@bandit:/tmp/jisuu$ file data
data: gzip compressed data, was "data2.bin", last modified: Tue Oct 16 12:00:23 2018, max compression, from Unixd
bandit12@bandit:/tmp/jisuu$ mv data data.gz
bandit12@bandit:/tmp/jisuu$ gzip -d data.gz 
bandit12@bandit:/tmp/jisuu$ ls
data  data.txt
bandit12@bandit:/tmp/jisuu$ file data
data: bzip2 compressed data, block size = 900k
bandit12@bandit:/tmp/jisuu$ mv data data.bzip2
bandit12@bandit:/tmp/jisuu$ file data.bz2 
data.bz2: gzip compressed data, was "data4.bin", last modified: Tue Oct 16 12:00:23 2018, max compression, from Unix
bandit12@bandit:/tmp/jisuu$ mv data.bz2 data.gz
bandit12@bandit:/tmp/jisuu$ gzip -d data.gz 
bandit12@bandit:/tmp/jisuu$ ls
data  data.txt
bandit12@bandit:/tmp/jisuu$ file data
data: POSIX tar archive (GNU)
bandit12@bandit:/tmp/jisuu$ mv data data.tar
bandit12@bandit:/tmp/jisuu$ tar -xf data.tar 
bandit12@bandit:/tmp/jisuu$ ls
data5.bin  data.tar  data.txt
bandit12@bandit:/tmp/jisuu$ file data5.bin 
data5.bin: POSIX tar archive (GNU)
bandit12@bandit:/tmp/jisuu$ tar -xf data5.tar 
bandit12@bandit:/tmp/jisuu$ ls
data5.tar  data6.bin  data.tar  data.txt
bandit12@bandit:/tmp/jisuu$ file data6.bin 
data6.bin: bzip2 compressed data, block size = 900k
bandit12@bandit:/tmp/jisuu$ mv data6.bin data6.bz2
bandit12@bandit:/tmp/jisuu$ bzip2 -d data6.bz2    
bandit12@bandit:/tmp/jisuu$ file data6
data6: POSIX tar archive (GNU)
bandit12@bandit:/tmp/jisuu$ tar -xf data6 
bandit12@bandit:/tmp/jisuu$ file data8.bin 
data8.bin: gzip compressed data, was "data9.bin", last modified: Tue Oct 16 12:00:23 2018, max compression, from Unix
bandit12@bandit:/tmp/jisuu$ mv data8.bin data8.gz
bandit12@bandit:/tmp/jisuu$ gzip -d data8.gz 
bandit12@bandit:/tmp/jisuu$ file data8
data8: ASCII text
bandit12@bandit:/tmp/jisuu$ cat data8
The password is 8ZjyCRiBWFYkneahHwxCv3wb2a1ORpYL
```

Finally, I got a password. 

password is '8ZjyCRiBWFYkneahHwxCv3wb2a1ORpYL'.

