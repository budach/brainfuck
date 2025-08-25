# Brainfuck Interpreter (C++ & Python)

Reasonably optimized, just for fun.

### C++ Version

Build (requires `g++`):
```sh
make release
```

Run:
```sh
./brainfuck_cpp programs/hello.bf
```

### Python Version

Run:
```sh
python main.py programs/hello.bf
```

## Benchmarks

Minimum runtime out of 5 runs each time:

| Program         | CPython 3.13.7 | PyPy 3.11.11 | g++ 15.2.1 |
|-----------------|:--------------:|:------------:|:----------:|
| fibint.bf       |    1.55 s      |   0.11 s     |   0.01 s   |
| golden.bf       |    2.61 s      |   0.20 s     |   0.04 s   |
| towers.bf       |   16.87 s      |   1.38 s     |   0.17 s   |
| mandelbrot.bf   |  159.25 s      |  12.77 s     |   3.01 s   |
