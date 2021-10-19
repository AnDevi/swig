#define SWIG_DEFINE_WRAPPER_ALIASES
#include "cpp_basic/cpp_basic_wrap.h"
#include <assert.h>
#include <stdio.h>

int main(int argc, const char *argv[]) {
	Foo *f = Foo_new(5);

	// test global static variables
	// TODO: Implement or document as not available
	/*
	assert(init_ref != 0);

	global_fptr_set(f);
	assert(Foo_num_get(global_fptr_get()) == 5);

	assert(Foo_num_get(global_fref_get()) == -4);
	Foo_num_set(f, 6);
	global_fref_set(f);
	assert(Foo_num_get(global_fref_get()) == 6);

	Foo_num_set(f, 7);
	global_fval_set(f);
	assert(Foo_num_get(global_fval_get()) == 7);
	*/

	Foo_num_set(f, 5);
	assert(Foo_num_get(f) == 5);
	assert(Foo_func1(f, 2) == 20);
	assert(Foo_func2(f, 2) == -10);

	// function pointer set/get tests are missing
	// because of unclear implementation details
	//foo_func_ptr_set(f, &Foo_func1);

	// test of global static variable is missing
	// because of unclear implementation details
	//assert(c_init_ref != 0);

	Bar *b = Bar_new();

	// check default value set by constructor
	assert(Bar_cint_get(b) == 3);

	// check default value set by Bar initializer
	assert(Foo_num_get(Bar_fval_get(b)) == 15);
	// change, recheck
	Foo_num_set(Bar_fval_get(b), 2);
	assert(Foo_num_get(Bar_fval_get(b)) == 2);

	// check references
	assert(Bar_fref_get(b) != 0);

	// check global static value and references
	assert(Foo_num_get(Bar_fref_get(b)) == -4);
	Foo_num_set(Bar_fref_get(b), 1);
	assert(Foo_num_get(Bar_fref_get(b)) == 1);
	// create new Bar instance and check static member value
	Bar *b2 = Bar_new();
	assert(Foo_num_get(Bar_fref_get(b2)) == 1);
	Bar_delete(b2);
	b2 = 0;

	// Try to set a pointer
	Bar_fptr_set(b, f);

	assert(Bar_test(b, 2, f) == 9);
	assert(Bar_test(b, 2, 0) == 4);

	Foo *f2 = Bar_testFoo(b, 2, f);
	assert(Foo_num_get(f2) == 11);
	Foo_delete(f2);
	f2 = 0;

	// test static variables
	Bar_global_fptr_set(f);
	assert(Foo_num_get(Bar_global_fptr_get()) == 5);

	Foo_num_set(f, 6);
	Bar_global_fref_set(f);
	assert(Foo_num_get(Bar_global_fref_get()) == 6);

	Foo_num_set(f, 7);
	Bar_global_fval_set(f);
	assert(Foo_num_get(Bar_global_fval_get()) == 7);

	// getting, setting and calling function pointers isn't supported yet
#if 0
	SomeTypeForMemFnPtr func1 = get_func1_ptr();
	Foo_func_ptr_set(f, func1);
	assert(test_func_ptr(f, 2) == 28);
	SomeTypeForMemFnPtr func2 = get_func2_ptr();
	Foo_func_ptr_set(f, func2);
	assert(test_func_ptr(f, 2) == -14);
#endif

	Bar_delete(b);
	Foo_delete(f);

	Fl_Window *w = Fl_Window_new();
	// Test whether macro worked for code extension
	// and test optional function parameters
	Fl_Window_show(w);
	Fl_Window_show_pv(w, 0);
	Fl_Window_show_pv_pv(w, 0, 0);
	Fl_Window_delete(w);
	w = 0;

	return 0;
}
