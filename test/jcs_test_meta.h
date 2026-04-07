#ifndef JCS_TEST_META_H
#define JCS_TEST_META_H


#include <jcs.h>


static jcs_meta_t jcs_test_1_meta[] =
{
	{ NULL, json_type_object,  0,  0 },
	{ "a",  json_type_int,     2,  1 },
	{ "b",  json_type_int,     4,  1 },
	{ "c",  json_type_double,  8,  1 },
	{ "d",  json_type_boolean, 1,  1 },
	{ "e",  json_type_null,    1,  1 },
	{ "f",  json_type_string,  32, 1 },
};

static jcs_meta_t jcs_test_2_meta[] =
{
	{ NULL, json_type_object,  0,  0 },
	{ "a",  json_type_int,     2,  1 },
	{ "b",  json_type_int,     4,  1 },
	{ "c",  json_type_double,  8,  1 },
	{ "d",  json_type_boolean, 1,  1 },
	{ "e",  json_type_null,    1,  1 },
	{ "f",  json_type_string,  32, 1 },
	{ "g",  json_type_object,  0,  1 },
	{ "ga", json_type_int,     8,  2 },
	{ "gb", json_type_int,     8,  2 },
	{ "gc", json_type_double,  8,  2 },
	{ "gd", json_type_boolean, 8,  2 },
	{ "ge", json_type_null,    8,  2 },
	{ "gf", json_type_string,  32, 2 },
	{ "h",  json_type_int,     8,  1 },
};

static jcs_meta_t jcs_test_3_meta[] =
{
	{ NULL, json_type_object,  0,  0 },
	{ "a",  json_type_int,     2,  1 },
	{ "b",  json_type_int,     4,  1 },
	{ "c",  json_type_double,  8,  1 },
	{ "d",  json_type_boolean, 1,  1 },
	{ "e",  json_type_null,    1,  1 },
	{ "f",  json_type_string,  32, 1 },
	{ "g",  json_type_object,  0,  1 },
	{ "ga", json_type_int,     8,  2 },
	{ "gb", json_type_int,     8,  2 },
	{ "gc", json_type_double,  8,  2 },
	{ "gd", json_type_boolean, 8,  2 },
	{ "ge", json_type_null,    8,  2 },
	{ "gf", json_type_string,  32, 2 },
	{ "h",  json_type_array,   4,  1 },
	{ NULL, json_type_int,     8,  2 },
	{ "i",  json_type_int,     8,  1 },
};

static jcs_meta_t jcs_test_4_meta[] =
{
	{ NULL, json_type_object,  0,  0 },
	{ "a",  json_type_int,     2,  1 },
	{ "b",  json_type_int,     4,  1 },
	{ "c",  json_type_double,  8,  1 },
	{ "d",  json_type_boolean, 1,  1 },
	{ "e",  json_type_null,    1,  1 },
	{ "f",  json_type_string,  32, 1 },
	{ "g",  json_type_object,  0,  1 },
	{ "ga", json_type_int,     8,  2 },
	{ "gb", json_type_int,     8,  2 },
	{ "gc", json_type_double,  8,  2 },
	{ "gd", json_type_boolean, 8,  2 },
	{ "ge", json_type_null,    8,  2 },
	{ "gf", json_type_string,  32, 2 },
	{ "h",  json_type_array,   4,  1 },
	{ NULL, json_type_int,     8,  2 },
	{ "i",  json_type_array,   4,  1 },
	{ NULL, json_type_array,   4,  2 },
	{ NULL, json_type_int,     8,  3 },
	{ "j",  json_type_int,     8,  1 },
};

static jcs_meta_t jcs_test_5_meta[] =
{
	{ NULL, json_type_object,  0,  0 },
	{ "a",  json_type_int,     2,  1 },
	{ "b",  json_type_int,     4,  1 },
	{ "c",  json_type_double,  8,  1 },
	{ "d",  json_type_boolean, 1,  1 },
	{ "e",  json_type_null,    1,  1 },
	{ "f",  json_type_string,  32, 1 },
	{ "g",  json_type_object,  0,  1 },
	{ "ga", json_type_int,     8,  2 },
	{ "gb", json_type_int,     8,  2 },
	{ "gc", json_type_double,  8,  2 },
	{ "gd", json_type_boolean, 8,  2 },
	{ "ge", json_type_null,    8,  2 },
	{ "gf", json_type_string,  32, 2 },
	{ "h",  json_type_array,   4,  1 },
	{ NULL, json_type_object,  0,  2 },
	{ "ha", json_type_int,     8,  3 },
	{ "hb", json_type_int,     8,  3 },
	{ "i",  json_type_int,     8,  1 },
};

static jcs_meta_t jcs_test_6_meta[] =
{
	{ NULL, json_type_object,  0,  0 },
	{ "a",  json_type_int,     2,  1 },
	{ "b",  json_type_int,     4,  1 },
	{ "c",  json_type_double,  8,  1 },
	{ "d",  json_type_boolean, 1,  1 },
	{ "e",  json_type_null,    1,  1 },
	{ "f",  json_type_string,  32, 1 },
	{ "g",  json_type_object,  0,  1 },
	{ "ga", json_type_int,     8,  2 },
	{ "gb", json_type_int,     8,  2 },
	{ "gc", json_type_double,  8,  2 },
	{ "gd", json_type_boolean, 8,  2 },
	{ "ge", json_type_null,    8,  2 },
	{ "gf", json_type_string,  32, 2 },
	{ "h",  json_type_array,   4,  1 },
	{ NULL, json_type_object,  0,  2 },
	{ "ha", json_type_int,     8,  3 },
	{ "hb", json_type_array,   4,  3 },
	{ NULL, json_type_int,     8,  4 },
	{ "hc", json_type_int,     8,  3 },
	{ "i",  json_type_int,     8,  1 },
};


#endif // JCS_TEST_META_H