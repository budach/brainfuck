# Brainfuck Interpreter (C++ & Python)

Reasonably optimized, just for fun.

### C++ Version

Build (requires `g++`):
```sh
make release
```

Run:
```sh
./brainfck_cpp.exe programs/hello.bf
```

### Python Version

Run:
```sh
python main.py programs/hello.bf
```

## Benchmarks

Minimum runtime out of 5 runs each time:

| Program         | CPython 3.13.7 | PyPy 3.11.13 | g++ 15.1.0 |
|-----------------|:--------------:|:------------:|:----------:|
| fibint.bf       |    2.64 s      |   0.10 s     |   0.01 s   |
| golden.bf       |    3.02 s      |   0.19 s     |   0.04 s   |
| towers.bf       |   18.57 s      |   1.28 s     |   0.17 s   |
| mandelbrot.bf   |  173.16 s      |  11.66 s     |   2.32 s   |
