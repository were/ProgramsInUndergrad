make bootstrap
./bootstrap < bootstrap.c > bootstrap.s
./spim -st 10000000 -ldata 100000000 -ss 10000000 -f bootstrap.s < bootstrap.c > bootstrap1.s
diff bootstrap1.s bootstrap.s
