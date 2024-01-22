# hm

Unfinished virtual machine.  
[hasm](./src/hasm.c) prints the tokens of `foo.hasm`. If `foo.hasm` doesn't exist, it just errors out.  
[hm](./src/hm.c) creates a file containing `hm` bytecode, and executes it.

## Quick Start

```console
$ make
$ ./hm
$ ./hasm
```
