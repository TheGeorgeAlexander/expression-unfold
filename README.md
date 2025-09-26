# Expression Unfold
This program takes a mathematical expression and breaks it down into its step-by-step operations. Each operation is isolated so that every line contains only one operation (addition, multiplication, function call, etc.).


## Example
**Input:**
```
pow(min(a + b * c - d, max((x / 2) + sqrt(y), log(z + 1, 10))) + 3, abs((m * n) - (p / q)))
```

**Output:**
```
temp5 = b * c
temp4 = a + temp5
temp3 = temp4 - d
temp6 = x / 2
temp7 = sqrt(y)
temp5 = temp6 + temp7
temp7 = z + 1
temp6 = log(temp7, 10)
temp4 = max(temp5, temp6)
temp2 = min(temp3, temp4)
temp1 = temp2 + 3
temp4 = m * n
temp5 = p / q
temp3 = temp4 - temp5
temp2 = abs(temp3)
result = pow(temp1, temp2)
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

> Note: Function are completely arbitrary, they are valid (sub-)expressions as long as they follow the `name(arg1, arg2, ...)` pattern.
