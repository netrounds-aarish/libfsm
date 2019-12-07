/*
 * Copyright 2019 Shannon F. Stewman
 *
 * See LICENCE for the full copyright terms.
 */

#include <assert.h>
#include <stdlib.h>
#include <stddef.h>

#include <fsm/fsm.h>
#include <fsm/pred.h>
#include <fsm/capture.h>

#include <adt/alloc.h>
#include <adt/set.h>
#include <adt/stateset.h>
#include <adt/edgeset.h>
#include <adt/xalloc.h>

#include "internal.h"

void
fsm_capture_start(struct fsm *fsm, struct fsm_capture *capture)
{
	assert(fsm != NULL);
	assert(capture != NULL);

	capture->start = fsm_countstates(fsm);
}

void
fsm_capture_stop(struct fsm *fsm, struct fsm_capture *capture)
{
	assert(fsm != NULL);
	assert(capture != NULL);

	capture->end = fsm_countstates(fsm);
}

int
fsm_capture_duplicate(struct fsm *fsm,
	const struct fsm_capture *capture,
	fsm_state_t *x,
	fsm_state_t *q)
{
	fsm_state_t old_start, old_end;
	fsm_state_t new_start, new_end;
	fsm_state_t ind;

	assert(fsm     != NULL);
	assert(capture != NULL);
	assert(q       != NULL);
	assert(x == NULL || (*x >= capture->start && *x < capture->end));

	old_start = capture->start;
	old_end   = capture->end;

	if (old_start >= old_end) {
		return 0;
	}

	/* allocate new states */
	new_start = new_end = 0;
	for (ind = old_start; ind < old_end; ind++) {
		fsm_state_t st;
		if (!fsm_addstate(fsm, &st)) {
			return 0;
		}

		fsm_setend(fsm, st, fsm_isend(fsm, ind));

		if (ind == old_start) {
			new_start = st;
		}

		new_end = st+1;
	}

	if (new_start == new_end) {
		return 0;
	}

	/* allocate edges */
	for (ind = new_start; ind < new_end; ind++) {
		const fsm_state_t old_src = old_start + (ind - new_start);
		struct edge_iter it;
		struct fsm_edge *e;

		{
			struct state_iter jt;
			fsm_state_t old_dst;

			for (state_set_reset(fsm->states[old_src].epsilons, &jt); state_set_next(&jt, &old_dst); ) {
				fsm_state_t new_dst;

				if (old_dst < old_start || old_dst >= old_end) {
					continue;
				}

				new_dst = new_start + (old_dst - old_start);

				if (!fsm_addedge_epsilon(fsm, ind, new_dst)) {
					return 0;
				}
			}
		}

		for (e = edge_set_first(fsm->states[old_src].edges, &it); e != NULL; e = edge_set_next(&it)) {
			struct state_iter jt;
			fsm_state_t old_dst;

			for (state_set_reset(e->sl, &jt); state_set_next(&jt, &old_dst); ) {
				fsm_state_t new_dst;

				if (old_dst < old_start || old_dst >= old_end) {
					continue;
				}

				new_dst = new_start + (old_dst - old_start);

				if (!fsm_addedge_literal(fsm, ind, new_dst, e->symbol)) {
					return 0;
				}
			}
		}
	}

	if (x != NULL && *x >= old_start && *x < old_end) {
		fsm_state_t old_x = *x;
		*x = new_start + (old_x - old_start);
	}

	*q = new_start;

	return 1;
}
