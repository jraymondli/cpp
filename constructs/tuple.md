## header file
```
#include <tuple>
```

## Operations

### Declare

```
tuple<int, double, string> tp;
```

```
auto my_tuple = std::make_tuple(1, 2.5, "Hello");
```


### Create Tuple

1. declare with initiation
2. make_tuple

### Getting pieces

1. get<0>, get<1> ...
2. tie

```
int a;
double b;
std::string c;
std::tie(a, b, c) = my_tuple;  // Using std::tie

// OR using structured bindings in C++17
auto [x, y, z] = my_tuple;  // Unpacking into variables

```

### Modifying tuple 
using get<0> etc.

```
get<0>myTuple = 42;
```

## Examples

https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/submissions/?envType=study-plan-v2&envId=leetcode-75


