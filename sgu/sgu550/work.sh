#!bin/sh
python gen.py < inform > input
./force
./main
diff output answer
