https://www.geeksforgeeks.org/lvalues-references-and-rvalues-references-in-c-with-examples/

## lvalue references

```
int a = 10;

// Declaring lvalue reference
int& lref = a;
```

### Use of lvalue references

1. lvalue references can be used to alias an existing object.
2. They can also be used to implement pass-by-reference semantics.




## rvalue references

```
// Declaring rvalue reference
int&& rref = 20;
```


### two properties

1. rvalue references extend the lifespan of the tempeory object to which they are assigned
2. non-const rvalue references allow you to modify the rvalue

### Use of rvalue references

1. They are used in working with the move constructor and move assignment.
2. cannot bind non-const lvalue reference of type ‘int&‘ to an rvalue of type ‘int’.
3. cannot bind rvalue references of type ‘int&&‘ to lvalue of type ‘int’.



 

