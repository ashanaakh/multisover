# Solver

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

### TODO
* Tests
* Stops

## Status
Working in progress

## License
[MIT](LICENSE)
