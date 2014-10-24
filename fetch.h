#ifndef CJET_FETCH_H
#define CJET_FETCH_H

#include "cJSON.h"
#include "list.h"
#include "peer.h"

struct fetch {
	const char *fetch_id;
	struct list_head next_fetch;
	struct list_head matcher_list;
};

cJSON *add_fetch_to_peer(struct peer *p, cJSON *params);

#endif
