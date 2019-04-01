1. First, get a copy of str.tgz and unpack:

$ wget https://web.cs.ucla.edu/classes/fall18/cs35L/assign/srt.tgz
$ tar -xvzf srt.tgz

2. I tried what the TA slides suggestedm and ran the following:

$ make clean check // This essentially cleans up all the executables and files from previous executions and runs a check for all threading solutions, including w/o multiple threads (ie one thread)

Output of the above:
//-------
rm -f *.o *.tmp 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm srt srt.tgz
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o main.o main.c
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o raymath.o raymath.c
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o shaders.o shaders.c
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter -o srt main.o raymath.o shaders.o -lm
time ./srt 1-test.ppm >1-test.ppm.tmp

real	0m34.558s
user	0m34.554s
sys	0m0.003s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp
./srt: Multithreading is not supported yet.

real	0m0.002s
user	0m0.000s
sys	0m0.001s
make: *** [Makefile:36: 2-test.ppm] Error 1
//-------

$ emacs 1-test.ppm
(emacs 1-test.ppm):
P3
131 131
255
# Rendering scene with 1556 spheres and 2 lights
88 148 177
89 148 175
89 146 173
72 132 166
56 118 159
140 175 226
247 250 255
255 255 255
255 255 255
...

3. After Parallelizing:

$ make clean check
(Running on server 07, output is in make-log.txt)

$ time ./srt 1-test.ppm > 1-test.ppm.tmp

real	1m0.350s
user	1m0.325s
sys	0m0.009s

$ time ./srt 2-test.ppm > 2-test.ppm.tmp

real	0m32.150s
user	0m57.491s
sys	0m0.006s

$ time ./srt 4-test.ppm > 4-test.ppm.tmp

real	0m18.085s
user	1m4.612s
sys	0m0.003s

$ time ./srt 8-test.ppm > 8-test.ppm.tmp

real	0m11.043s
user	1m18.870s
sys	0m0.005s









