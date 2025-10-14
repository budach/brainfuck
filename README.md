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

| Program         |  Python 3.13.7 | PyPy 3.11.13 | g++ 15.2.1 |
|-----------------|:--------------:|:------------:|:----------:|
| fibint.bf       |    1.35 s      |   0.09 s     |   0.01 s   |
| golden.bf       |    2.21 s      |   0.16 s     |   0.03 s   |
| towers.bf       |   13.93 s      |   1.06 s     |   0.16 s   |
| mandelbrot.bf   |  128.03 s      |  10.11 s     |   2.07 s   |
