libtoolize -i -c -f
aclocal --force
autoheader -f
automake -a -c -f
autoconf -f
./configure
make clean
make
