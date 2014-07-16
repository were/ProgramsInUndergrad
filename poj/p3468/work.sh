python gen.py < inform > input
time ./main < input > output
time ./force < input > answer
diff output answer
