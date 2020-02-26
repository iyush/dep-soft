# RPN Calculator

Done in Conjuction with Drishti Maharjan.

## Requirements
1. CMake 3.0.0 
2. PkgConfig
3. Threads
4. Check (for tests)

## Building
```sh
mkdir build
cd build/
cmake ..
make
```

## Running Tests
From the project directory:
```sh
cd build
make test
```

## Checking Code Coverage
From the project directory. Make sure all the steps above are executed
```sh
cd build
lcov --capture --directory . --output-file COV.info
genhtml COV.info -o HTML_REPORT
cd HTML_REPORT
```
And then open the `index.html` file.