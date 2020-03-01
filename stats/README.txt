# Stats
Enable coverage definitions in the top-level CMakeLists.txt and build
normally. In the build directory, you can now produce a nice report:

$ lcov --zerocounters --directory .
$ lcov --capture --initial --directory . --output-file app
$ make test
$ lcov --no-checksum --directory . --capture --output-file app.info
$ genhtml app.info

Look at the report by loading index.html into your browser.
