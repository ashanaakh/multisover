# Solver

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/1fe9046f03124dcc8b97a5e9f86be9cf)](https://www.codacy.com/app/ashanaakh/multisover)

## About
[Lab work 1](https://drive.google.com/drive/u/0/folders/0B-BUpwNPP_9JNURqcm53R1dXam8)

### Task `V16`
Use C++, threads, condvars and global vars or attributes to pass the result
of function computation.

### Conjunction
| A  | B  | A ∧ B |
|:--:|:--:|:-----:|
| 0  | 0  |   0   |
| 0  | 1  |   0   |
| 1  | 0  |   0   |
| 1  | 1  |   1   |

### Build
```shell
make
```

### Clean binaries
```shell
make clean
```

### Usage
```shell
./build/solver --test <boolean> <boolean>
```

| boolean | value |
|:-------:|:-----:|
| true    |   0   |
| false   |   1   |

### Example
```shell
./build/solver --test 0 1 # result: 0
./build/solver --test 1 1 # result: 1
```

### Tasks list
- [x] Tests
- [x] Stops

# Tests
| x | f.time | f.val | g.time | g.val | res.time | res.val |
|:-:|:------:|:-----:|:------:|:-----:|:--------:|:-------:|
| 1 |   1s   | true  |   3s   | true  |    3s    |  true   |
| 2 |   3s   | true  |   1s   | true  |    3s    |  true   |
| 3 |   3s   | false |   4s   | true  |    3s    |  false  |
| 4 |   5s   | true  |   3s   | false |    3s    |  false  |
| 5 |   10s  | true  |   8s   | false |  cancel  |canceled |
| 6 |   6s   | false |   7s   | true  |  cancel  |canceled |

## Status
Ready

## License
[MIT](LICENSE)
