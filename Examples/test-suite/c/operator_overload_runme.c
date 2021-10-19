#include <stdio.h>
#include <stdlib.h>

#define SWIG_DEFINE_WRAPPER_ALIASES
#include "operator_overload/operator_overload_wrap.h"

#define assert(x,msg) if (!x) { printf("%d: %s\n", x, msg); exit(1); }

int main() {
  Op_sanity_check();
  
  Op *op1 = Op_new_i(1), *op2 = Op_new_i(2), *op3 = Op_copy(op1);

  assert(Op_NotEqual(op1, op2), "neq failed");
  Op_PlusPlusPrefix(op3);  
  assert(Op_EqualEqual(op2, op3), "eqeq failed");
  assert(Op_GreaterThanEqual(op2, op1), "geq failed");
  Op_PlusEqual(op3, op1);
  assert(Op_LessThan(op1, op2) && Op_LessThan(op2, op3), "lt failed");
  assert(3 == *Op_IndexInto(op3, Op_IndexIntoConst(op2, Op_Functor(op1))), "[] or () failed");
  assert(5 == Op_Functor_i(op3, 2), "f(x) failed");
  
  Op_delete(op1);
  Op_delete(op2);
  Op_delete(op3);
  exit(0);
}
