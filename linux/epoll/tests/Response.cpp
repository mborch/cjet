#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE state

#include <boost/test/unit_test.hpp>

#include "response.h"

BOOST_AUTO_TEST_CASE(boolean_success_false)
{
	cJSON *id = cJSON_CreateString("request1");
	cJSON *response = create_boolean_success_response(id, 0);

	cJSON *result = cJSON_GetObjectItem(response, "result");
	BOOST_CHECK(result->type == cJSON_False);

	cJSON_Delete(id);
	cJSON_Delete(response);
}

BOOST_AUTO_TEST_CASE(boolean_success_true)
{
	cJSON *id = cJSON_CreateString("request1");
	cJSON *response = create_boolean_success_response(id, 1);

	cJSON *result = cJSON_GetObjectItem(response, "result");
	BOOST_CHECK(result->type == cJSON_True);

	cJSON_Delete(id);
	cJSON_Delete(response);
}

BOOST_AUTO_TEST_CASE(boolean_success_true_wrong_id_type)
{
	cJSON *id = cJSON_CreateBool(0);
	cJSON *response = create_boolean_success_response(id, 1);

	BOOST_CHECK(response == NULL);

	cJSON_Delete(id);
}

BOOST_AUTO_TEST_CASE(internal_error_response)
{
	const char *tag = "reason";
	const char *reason = "not enough memory";
	cJSON *id = cJSON_CreateString("request1");
	cJSON *error = create_internal_error(tag, reason);
	cJSON *response = create_error_response(id, error);

	cJSON *err = cJSON_GetObjectItem(response, "error");
	BOOST_CHECK(err->type == cJSON_Object);

	cJSON *code = cJSON_GetObjectItem(err, "code");
	BOOST_CHECK(code->type == cJSON_Number && code->valueint == -32603);

	cJSON *message = cJSON_GetObjectItem(err, "message");
	BOOST_CHECK(message->type == cJSON_String && strcmp(message->valuestring, "Internal error") == 0);
	cJSON *data = cJSON_GetObjectItem(err, "data");
	BOOST_CHECK(data != NULL && data->type == cJSON_Object);

	cJSON *r = cJSON_GetObjectItem(data, tag);
	BOOST_CHECK(r->type == cJSON_String && strcmp(r->valuestring, reason) == 0);


	cJSON_Delete(id);
	cJSON_Delete(response);
}