# CMake projects:

- 2.10write creates a new FIFO pipe and writes random numbers to it, syntax:
  - ./2.10write AMOUNT_OF_NUMBERS
- 2.10read reads the numbers written to the pipe by 2.10write, syntax:
  - ./2.10read

Running multiple 2.10write programs will result in only one valid open FIFO pipe,
because a new pipe is created every time the program is run.

This is also the reason for 2.10read to fail if it's started before 2.10write.

Running multiple 2.10read programs will result in only the first program working correctly.
