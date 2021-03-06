/*
 * Copyright 2019 Scott Vokes
 *
 * See LICENCE for the full copyright terms.
 */

#include <assert.h>
#include <stdlib.h>

#include <fsm/fsm.h>

#include <adt/queue.h>

static int
create_and_free(void)
{
	struct queue *q = queue_new(NULL, 1);
	if (q == NULL) { return 0; }

	queue_free(q);
	return 1;
}

static int
reject_0_capacity(void)
{
	struct queue *q = queue_new(NULL, 0);
	if (q != NULL) { return 0; }
	return 1;
}

static int
push_all_pop_all(size_t limit)
{
	fsm_state_t i;
	struct queue *q = queue_new(NULL, limit);
	if (q == NULL) { return 0; }

	for (i = 0; i < limit; i++) {
		if (!queue_push(q, i)) { return 0; }
	}
	
	for (i = 0; i < limit; i++) {
		fsm_state_t p;
		if (!queue_pop(q, &p)) { return 0; }
		if (p != i) { return 0; }
	}
	
	queue_free(q);
	return 1;
}

static int
push_pop_interleave(size_t limit)
{
	fsm_state_t i;
	struct queue *q = queue_new(NULL, 1);
	if (q == NULL) { return 0; }

	for (i = 0; i < limit; i++) {
		fsm_state_t p;
		if (!queue_push(q, i)) { return 0; }
		if (!queue_pop(q, &p)) { return 0; }
		if (p != i) { return 0; }
	}
	
	queue_free(q);
	return 1;
}

static int
detect_empty(size_t limit)
{
	fsm_state_t i;
	struct queue *q = queue_new(NULL, 1);
	if (q == NULL) { return 0; }

	for (i = 0; i < limit; i++) {
		fsm_state_t p;
		if (!queue_push(q, i)) { return 0; }
		if (!queue_pop(q, &p)) { return 0; }

		/* queue should be empty */
		if (queue_pop(q, &p)) { return 0; }
	}
	
	queue_free(q);
	return 1;
}

static int
detect_full(size_t limit)
{
	fsm_state_t i;
	struct queue *q = queue_new(NULL, 1);
	if (q == NULL) { return 0; }

	for (i = 0; i < limit; i++) {
		fsm_state_t p;
		if (!queue_push(q, i)) { return 0; }

		/* try pushing again, queue should be at capacity */
		if (queue_push(q, i)) { return 0; }

		if (!queue_pop(q, &p)) { return 0; }
	}
	
	queue_free(q);
	return 1;
}

int main(void) {
	size_t i;
	assert(create_and_free());
	assert(reject_0_capacity());

	for (i = 1; i < 100; i++) {
		assert(push_all_pop_all(i));
		assert(push_pop_interleave(i));
		assert(detect_empty(i));
		assert(detect_full(i));
	}

	return 0;
}
