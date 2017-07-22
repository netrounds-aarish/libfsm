/* Generated by libfsm */

#include LF_HEADER

#include <stddef.h>

#include <fsm/fsm.h>

struct fsm *
class_xdigit_fsm(const struct fsm_options *opt)
{
	struct fsm *fsm;
	size_t i;

	struct fsm_state *s[2] = { 0 };

	fsm = fsm_new(opt);
	if (fsm == NULL) {
		return NULL;
	}

	for (i = 0; i < 2; i++) {
		s[i] = fsm_addstate(fsm);
		if (s[i] == NULL) {
			goto error;
		}
	}

	if (!fsm_addedge_literal(fsm, s[0], s[1], '0')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], '1')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], '2')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], '3')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], '4')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], '5')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], '6')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], '7')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], '8')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], '9')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], 'A')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], 'B')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], 'C')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], 'D')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], 'E')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], 'F')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], 'a')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], 'b')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], 'c')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], 'd')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], 'e')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[1], 'f')) { goto error; }

	fsm_setstart(fsm, s[0]);
	fsm_setend(fsm, s[1], 1);

	return fsm;

error:

	fsm_free(fsm);

	return NULL;
}
