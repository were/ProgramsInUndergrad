#!bin/sh
python gen.py < inform > input
./main < input > output
./force < input > answer
./judge 
