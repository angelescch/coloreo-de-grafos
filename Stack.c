#include <stdlib.h>
#include <assert.h>
#include "Stack.h"

struct _s_stack{
	stack_elem elem;
	struct _s_stack *next;
};

bool invrep(stack s){
	s = s;
	return true;
}
 
stack stack_empty(void){
	stack s = NULL;
	assert(invrep(s));
	return s;
}

stack stack_push(stack s, stack_elem e){
	assert(invrep(s));
	stack p = malloc(sizeof(struct _s_stack));
	p->elem = e;
	p->next = s;
	s = p;
	p = NULL;
	assert(invrep(s));
	return s;
}

stack stack_pop(stack s){
	assert(s != NULL && invrep(s));
	stack p;
	p = s;
	s = s->next;
	free(p);
	p = NULL;
	assert(invrep(s));
	return s;
}

unsigned int stack_size(stack s){
	assert(invrep(s));
	unsigned int n;
	stack p;
	n = 0u;
	p = s;
	while(p != NULL){
		n = n + 1;
		p = p->next;
	}
	assert(invrep(s));
	return n;
}

stack_elem stack_top(stack s){
	assert(s != NULL && invrep(s));
	return (s->elem);
}

bool stack_is_empty(stack s){
	assert(invrep(s));
	return (s == NULL);
}

stack_elem *stack_to_array(stack s){
	assert(invrep(s));
	stack p;
	stack_elem *array;
	if(stack_is_empty(s)){
		array = NULL;
	}
	else{
		array = calloc(stack_size(s), sizeof(stack_elem));
		p = s;
		for(unsigned int i = stack_size(s); i > 0u; --i){
			array[i - 1u] = p->elem;
			p = p->next;
		}
	}
	p = NULL;
	assert(invrep(s));
	return array;
}

stack stack_destroy(stack s){
	assert(invrep(s));
	stack p;
	while(s != NULL){
		p = s;
		s = p->next;
		free(p);
	}
	p = NULL;
	return s;
}

