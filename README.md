# Expression Unfold
This program takes a mathematical expression and breaks it down into its step-by-step operations. Each operation is isolated so that every line contains only one operation (addition, multiplication, function call, etc.).


## Example
**Input:**
```
pow(min(a + b * c - d, max((x / 2) + sqrt(y), log(z + 1, 10))) + 3, abs((m * n) - (p / q)))
```

**Output:**
```
result = b * c
result = a + result
result = result - d
temp1 = x / 2
temp2 = sqrt(y)
temp1 = temp1 + temp2
temp2 = z + 1
temp2 = log(temp2, 10)
temp1 = max(temp1, temp2)
result = min(result, temp1)
result = result + 3
temp1 = m * n
temp2 = p / q
temp1 = temp1 - temp2
temp1 = abs(temp1)
result = pow(result, temp1)
```

## Usage
Build the project on Linux with:
```sh
make
```

Run it in one of two ways:
```sh
./unfold             # Enter an expression manually
./unfold <FILENAME>  # Read the expression from a text file
```

## Expressions
An expression may contain:
* Numbers
* Variables
* Functions (any name, with at least one parameter)
* Operators (`+ - * /`)
* Brackets for grouping


Examples:
* `1 + 2`
* `10 / 2 + 6`
* `(y + 2) * 3 + (4 - x)`
* `5 + pow(2 + 3, 4 - 1)`
* `pow(max(2, 5), min(3, 4))`
* `randomFunc(1, thisIsAVar, 3, func(4))`

> Note: Functions are completely arbitrary, they are valid (sub-)expressions as long as they follow the `name(arg1, arg2, ...)` syntax.
