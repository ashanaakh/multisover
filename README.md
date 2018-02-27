[codacy]: https://www.codacy.com/app/ashanaakh/multisover
[wiki]: https://en.wikipedia.org/wiki/Logical_conjunction#Truth_table

# Multisolver

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/1fe9046f03124dcc8b97a5e9f86be9cf)][codacy]

## Overview

Use C++, threads, condvars and global vars or attributes to pass the result of function computation.

**Function**: [conjunction][wiki]

### Truth table

| A  | B  | A ∧ B |
|:--:|:--:|:-----:|
| 0  | 0  |   0   |
| 0  | 1  |   0   |
| 1  | 0  |   0   |
| 1  | 1  |   1   |

## Usage

**Build**

```
make
```

**Clean binaries**

```
make clean
```

**Run binary**

```
./build/solver
```

# Tests

| x | f.time | f.val | g.time | g.val | res.time | res.val |
|:-:|:------:|:-----:|:------:|:-----:|:--------:|:-------:|
| 1 |   1s   | true  |   3s   | true  |    3s    |  true   |
| 2 |   3s   | true  |   1s   | true  |    3s    |  true   |
| 3 |   3s   | false |   4s   | true  |    3s    |  false  |
| 4 |   5s   | true  |   3s   | false |    3s    |  false  |
| 5 |   10s  | true  |   8s   | false |  cancel  |canceled |
| 6 |   6s   | false |   7s   | true  |  cancel  |canceled |

Build and run all tests:

```
make test
```

You can build and run specific test.

*Example*

```
make test
```

## License
This project is under the MIT License. See the LICENSE file for the full license text.
