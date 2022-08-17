# Multi-platform Development 

## About

https://ocw.cs.pub.ro/courses/so/teme/tema-1

Implement a mini preprocessor to deal with directives that can both run on Linux and
Windows with the same source code

## How to run the tests

- run local bash script

## Structure & Flow

### For solving the tasks I used the following:

- hashtable.c
    - Here I have all the necessary fields and API calls to use a hashtable. In "hashtable.h" I have used as defines
    several random numbers of my choice to make the hash compute function unique and abstract.
    - Functions for this hashtable include:
        - create
        - destroy
        - put
        - get
        - delete an entry
        - compute hash

- main.c
    - The whole computation is done here in the following way:
        - for #define and #undef directive: As the line buffer gets filled line by line, I split every token
        using strtok and search for the #define or #undef keywords. On #define, I parse the line and check if
        there is a multiline define or an imbricated define, then put and update the value in the hashtable.
        On #undef, I delete the entry from the hashtable.
        - after the line is processed, the hashtable replacements take place in the content buffer that gets
        appended from the line buffer and then written to stdout or output
        - to differentiate between stdin or file I have used several variables so if a file is located in the
        CLI command then we open it and also if a second one is there we are writting the output to it. If not,
        input is taken from stdin and output is put to stdout. If more than 2 files exists at CLI parameters,
        there will be an error as the third file is not permitted.

- GNUmakefile - Linux Makefile

- Makefile - Windows Makefile

## Observations

Some lines of code may seem truncated and that is because the coding style checker had problems with their length
although they do not have over 80 characters. This is why I had to truncate them.

## Project structure including tests
```bash
.
├── GNUmakefile
├── hashtable.c
├── hashtable.h
├── hooks.dll
├── hooks.lib
├── libso.so
├── _log
├── main.c
├── Makefile
├── Makefile.checker
├── README.md
├── run_all.sh
├── run.exe
├── so-cpp
├── so-cpp.exe
└── _test
    ├── inputs
    │   ├── test10.in
    │   ├── test11.in
    │   ├── test12.in
    │   ├── test13.in
    │   ├── test14.in
    │   ├── test15.in
    │   ├── test16.in
    │   ├── test17.in
    │   ├── test18.in
    │   ├── test19.in
    │   ├── test1.in
    │   ├── test1.param
    │   ├── test20.in
    │   ├── test20.param
    │   ├── test21.in
    │   ├── test22.in
    │   ├── test23.in
    │   ├── test24.in
    │   ├── test25.in
    │   ├── test26.in
    │   ├── test27.in
    │   ├── test27.param
    │   ├── test28.in
    │   ├── test29.in
    │   ├── test29.param
    │   ├── test2.param
    │   ├── test30.in
    │   ├── test30.param
    │   ├── test31.in
    │   ├── test31.param
    │   ├── test32.h
    │   ├── test32.in
    │   ├── test33.dir
    │   │   └── test33.h
    │   ├── test33.in
    │   ├── test34.dir
    │   │   └── test34.h
    │   ├── test34.in
    │   ├── test34.param
    │   ├── test35.dir
    │   │   ├── test35.h
    │   │   └── test35.subdir
    │   │       └── test35.h
    │   ├── test35.h
    │   ├── test35.in
    │   ├── test35.param
    │   ├── test36.dir
    │   │   ├── test36.h
    │   │   └── test36.subdir
    │   │       └── test36.h
    │   ├── test36.in
    │   ├── test36.param
    │   ├── test37.h
    │   ├── test37.in
    │   ├── test38.dir
    │   │   └── debug.h
    │   ├── test38.h
    │   ├── test38.in
    │   ├── test38.param
    │   ├── test3.in
    │   ├── test3.param
    │   ├── test4.in
    │   ├── test5.in
    │   ├── test6.in
    │   ├── test7.in
    │   ├── test8.in
    │   ├── test8.param
    │   └── test9.in
    ├── run_test.sh
    └── test_lib.sh

```
