https://www.geeksforgeeks.org/stdmove-in-utility-in-c-move-semantics-move-constructors-and-move-assignment-operators/

The need or purpose of a move constructor is to steal or move as many resources as it can from the source (original) object, as fast as possible, because the source does not need to have a meaningful value anymore, and/or because it is going to be destroyed in a moment anyway. So that one can avoid unnecessarily creating copies of an object and make efficient use of the resources



