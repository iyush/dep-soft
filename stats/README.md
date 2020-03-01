# Stats Calculator

Authors: Drishti Maharjan
        Aayush Sharma Acharya

## Requirements
1. CMake 3.0.0 
2. PkgConfig
3. Threads
4. Check (for tests)
5. AFL (American Fuzzy Lop)

## Building
```sh
    mkdir build
    cd build  
    CC=afl-gcc cmake .. && make
    cd ..
    afl-fuzz -i testCases/ -o gen_tests ./b/src/ds 
```

## Running Tests
From the project directory:
```sh
cd build
make test
```
