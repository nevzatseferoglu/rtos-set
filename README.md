#### Nevzat Seferoglu - 171044024

## Features
- Keeps an array with `std::unique::ptr` as an underlying buffer.
- It keeps the set always in-order according to comparision operator of given generic type.
- (insert, search and remove) are working according to binary search.
- `CustomType` was implemented for demonstrading purposes.
- Modern cpp features were tried to be exploited.
- One writer, one reader problem was solved.

## Running
- `test/driver.cpp` contains the driver code.
- `make test` compile and run the driver at once.
    - Node: It deletes the executable after running.
- If the executable is needed after running; `make ctest` can be used.

## Driver output
```bash
~/Desktop/rsa/github.com/rtos-set main !4 ?2 > make test                                                                                                                                                   07:09:10
--Begin Test_WriteAndRemove--
[ 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 ]
--End Test_WriteAndRemove, PASS--

--Begin Test_CustomType--
size: 8
time: 2 info: 2_info is in the set!
time: 0 info: 0_info
time: 1 info: 1_info
time: 2 info: 2_info
time: 3 info: 3_info
time: 4 info: 4_info
time: 5 info: 5_info
time: 6 info: 6_info
time: 7 info: 7_info
Cleared!
--End Test_CustomType PASS--
```