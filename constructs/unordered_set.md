## header file
```
#include <unordered_set>
```

## operations

1. size()
2. insert()
3. find

## Examples

https://leetcode.com/problems/keys-and-rooms/submissions/1408673283/?envType=study-plan-v2&envId=leetcode-75

## Working with set of pairs

In order to do that, we need to provide a hash function, and use it in the set defintion.

```
// Custom hash function for std::pair
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);  // A way to combine two hash values
    }
};

...

unordered_set<pair<int, int>, pair_hash> original_conns;
```

