#ifndef CJET_HANDLE_FETCH_H
#define CJET_HANDLE_FETCH_H

#include "json/cJSON.h"
#include "list.h"
#include "peer.h"
#include "state.h"

#ifdef __cplusplus
extern "C" {
#endif

struct path_matcher;
struct state;

typedef int (*match_func)(const struct path_matcher *pm, const char *state_path);

struct path_matcher {
	char *fetch_path;
	match_func match_function;
	uintptr_t cookie;
};

struct fetch {
	cJSON *fetch_id;
	struct peer *peer;
	struct list_head next_fetch;
	struct path_matcher matcher[12];
};

cJSON *add_fetch_to_peer(struct peer *p, const cJSON *params,
	struct fetch **fetch_return);
cJSON *remove_fetch_from_peer(struct peer *p, const cJSON *params);
void remove_all_fetchers_from_peer(struct peer *p);
cJSON *add_fetch_to_states(struct fetch *f);
int find_fetchers_for_state(struct state *s);

int notify_fetchers(struct state *s, const char *event_name);

#ifdef __cplusplus
}
#endif

#endif

