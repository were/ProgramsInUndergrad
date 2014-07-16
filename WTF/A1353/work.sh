#!bin/sh

python gen.py < inform > input
./main
./force
diff output answer
