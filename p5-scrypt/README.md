This project implements a simple substitution-permutation network
encryption algorithm calles scrypt. The algorithm is designed to be
simplistic, so do not use it for anything serious. The purpose of this
project is to get the idea how a substitution-permutation network
works and how modes of operations of block ciphers (like ecb and cbc)
work. For a more complete description, see the assignment sheet #4
linked to the 'Secure and Dependable Systems' course web page:

https://cnds.jacobs-university.de/courses/sads-2020/

The API for the scrypt algorithm is defined in the header file
`src/scrypt.h`. Some test cases can be found in
`test/check-scrypt.c`. To build the project, just do:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ make test

Of course, you have to provide your own `src/scrypt.c` file to compile
the code and to run the test.

/js
