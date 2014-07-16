#!bin/sh

python gen.py < inform > input
time ./main
time ./sort
diff output answer
