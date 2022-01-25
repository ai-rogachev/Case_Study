# Simple hello world in linux via C (not C++)

Command for build exe file - call from source folder

`$ make 

If we try to run hello we got aan error! 
We need registate the library.

./hello: error while loading shared libraries: libHello.so: cannot open shared object file: No such file or directory

Registrate lib by LD_LIBRARY_PATH

` export LD_LIBRARY_PATH=.