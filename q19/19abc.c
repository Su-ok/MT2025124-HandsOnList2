/*
==============================================================================================================================
Name: 19abc.c
Author: Suchir Okram
Description: Create a FIFO file by
                a. mknod command
                b. mkfifo command
                c. use strace command to find out, which command (mknod or mkfifo) is better.
                d. mknod system call
                e. mkfifo library function
Date: 11th Sep, 2025
==============================================================================================================================
*/

/*
==============================================================================================================================
SAMPLE OUTPUT:
    a-c in terminal:
        a. mknod command:
            suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q19$ mknod Myfifo1 p
            suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q19$ ls -l
            total 4
            -rw-rw-r-- 1 suchir-okram suchir-okram 975 Sep 12 10:01 19abc.c
            prw-rw-r-- 1 suchir-okram suchir-okram   0 Sep 12 10:02 Myfifo1
        b. mkfifo command:
            suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q19$ mkfifo Myfifo2
            suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q19$ ls -l
            total 4
            -rw-rw-r-- 1 suchir-okram suchir-okram 975 Sep 12 10:01 19abc.c
            prw-rw-r-- 1 suchir-okram suchir-okram   0 Sep 12 10:02 Myfifo1
            prw-rw-r-- 1 suchir-okram suchir-okram   0 Sep 12 10:03 Myfifo2
        c. comparison between mknod and mkfifo:
            1. mkfifo:
                suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q19$ strace -c mkfifo Fifotest
                % time     seconds  usecs/call     calls    errors syscall
                ------ ----------- ----------- --------- --------- ----------------
                43.47    0.000745         745         1           execve
                22.58    0.000387          21        18           mmap
                7.06    0.000121          20         6           openat
                6.07    0.000104         104         1           mknodat
                5.08    0.000087          10         8           close
                4.14    0.000071          14         5           read
                3.44    0.000059           9         6           fstat
                2.45    0.000042          21         2         2 statfs
                2.04    0.000035          11         3           brk
                1.75    0.000030          15         2         2 access
                1.28    0.000022          11         2           pread64
                0.64    0.000011          11         1           getrandom
                0.00    0.000000           0         5           mprotect
                0.00    0.000000           0         1           munmap
                0.00    0.000000           0         1           arch_prctl
                0.00    0.000000           0         1           set_tid_address
                0.00    0.000000           0         1           set_robust_list
                0.00    0.000000           0         1           prlimit64
                0.00    0.000000           0         1           rseq
                ------ ----------- ----------- --------- --------- ----------------
                100.00    0.001714          25        66         4 total
            2. mknod:
                suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q19$ strace -c mknod Fifotest2 p
                % time     seconds  usecs/call     calls    errors syscall
                ------ ----------- ----------- --------- --------- ----------------
                32.15    0.000677         677         1           execve
                21.46    0.000452          25        18           mmap
                8.83    0.000186          31         6           openat
                5.98    0.000126         126         1           mknodat
                5.94    0.000125          25         5           mprotect
                4.65    0.000098          12         8           close
                4.13    0.000087          17         5           read
                3.47    0.000073          12         6           fstat
                3.04    0.000064          32         2         2 statfs
                2.23    0.000047          47         1           munmap
                2.18    0.000046          15         3           brk
                1.76    0.000037          18         2         2 access
                1.00    0.000021          10         2           pread64
                0.71    0.000015          15         1           prlimit64
                0.71    0.000015          15         1           getrandom
                0.47    0.000010          10         1           arch_prctl
                0.43    0.000009           9         1           set_tid_address
                0.43    0.000009           9         1           set_robust_list
                0.43    0.000009           9         1           rseq
                ------ ----------- ----------- --------- --------- ----------------
                100.00    0.002106          31        66         4 total
            
            Which one is better?
                mkfifo is better because:
                * less error-prone (no requirement to check for p argument or mode flags)
                * more readable (explicitly for FIFOs)
==============================================================================================================================
*/