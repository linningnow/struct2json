/*
 * This file is part of the struct2json Library.
 *
 * Copyright (c) 2015, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: It is an head file for this library. You can see all be called functions.
 * Created on: 2015-10-14
 */

#ifndef __S2J_H__
#define __S2J_H__

#include <cJSON.h>
#include <string.h>
#include "s2jdef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* struct2json software version number */
#define S2J_SW_VERSION                "1.0.5"

/* Create JSON object */
#define s2j_create_json_obj(json_obj) \
    S2J_CREATE_JSON_OBJECT(json_obj)

/* Delete JSON object */
#define s2j_delete_json_obj(json_obj) \
    S2J_DELETE_JSON_OBJECT(json_obj)

/* Set basic type element for JSON object */
#define s2j_json_set_basic_element(to_json, from_struct, type, element) \
    S2J_JSON_SET_BASIC_ELEMENT(to_json, from_struct, type, element)

#define s2j_json_set_basic_element_isused(to_json, from_struct, type, element) \
    { \
		if (from_struct->element ## _isUsed) { \
			S2J_JSON_SET_BASIC_ELEMENT(to_json, from_struct, type, element) \
		} \
	}

#define s2j_json_set_basic_element_withlen(to_json, from_struct, type, element) \
    { \
		if (from_struct->element ## Len > 0) { \
			S2J_JSON_SET_BASIC_ELEMENT(to_json, from_struct, type, element) \
		} \
	}

#define s2j_json_set_array_element_withlen(to_json, from_struct, type, element) \
    { \
		if (from_struct->element ## Len > 0) { \
			S2J_JSON_SET_ARRAY_ELEMENT(to_json, from_struct, type, element, from_struct->element ## Len) \
		} \
	}

/* Set array type element for JSON object */
#define s2j_json_set_array_element(to_json, from_struct, type, element, size) \
    S2J_JSON_SET_ARRAY_ELEMENT(to_json, from_struct, type, element, size)

/* Set child structure type element for JSON object */
#define s2j_json_set_struct_element_start(child_json, to_json, child_struct, from_struct, type, element) \
    S2J_JSON_SET_STRUCT_ELEMENT(child_json, to_json, child_struct, from_struct, type, element)

#define s2j_json_set_struct_element_end(child_json, to_json, child_struct, from_struct, type, element)    

#define s2j_json_set_struct_element_isused_start(child_json, to_json, child_struct, from_struct, type, element) \
    { \
		if (from_struct->element ## _isUsed) { \
    		S2J_JSON_SET_STRUCT_ELEMENT(child_json, to_json, child_struct, from_struct, type, element)

#define s2j_json_set_struct_element_isused_end(child_json, to_json, child_struct, from_struct, type, element) \
		} \
	}

/* Set child structure type element for structure object */
#define s2j_struct_set_struct_element(child_struct, to_struct, child_json, from_json, type, element) \
    S2J_STRUCT_SET_STRUCT_ELEMENT(child_struct, to_struct, child_json, from_json, type, element)

/* Set enum type element for struct object */
#define s2j_json_set_enum_element(to_json, from_struct, element, enum_string) \
    S2J_JSON_SET_ENUM_ELEMENT(to_json, from_struct, element, enum_string)

#define s2j_json_set_enum_element_isused(to_json, from_struct, element, enum_string) \
    { \
		if (from_struct->element ## _isUsed) {\
    		S2J_JSON_SET_ENUM_ELEMENT(to_json, from_struct, element, enum_string) \
		}\
	}

/* Set child struct array element from struct array object*/
#define s2j_json_set_structArray_element_start(array_json, to_json, item_json, from_struct, array_struct, type, _element, _level) \
    S2J_JSON_SET_STRUCTARRAY_ELEMENT_START(array_json, to_json, item_json, from_struct, array_struct, type, _element, _level)

#define s2j_json_set_structArray_element_end(array_json, to_json, array_struct, item_json, element, _level) \
    S2J_JSON_SET_STRUCTARRAY_ELEMENT_END(array_json, to_json, array_struct, item_json, element, _level)

/* Create structure object */
#define s2j_create_struct_obj(struct_obj, type) \
    S2J_CREATE_STRUCT_OBJECT(struct_obj, type)

/* Delete structure object */
#define s2j_delete_struct_obj(struct_obj) \
    S2J_DELETE_STRUCT_OBJECT(struct_obj)

/* Get basic type element for structure object */
#define s2j_struct_get_basic_element(to_struct, from_json, type, element) \
    S2J_STRUCT_GET_BASIC_ELEMENT(to_struct, from_json, type, element)

#define s2j_struct_get_basic_element_isused(to_struct, from_json, type, element) \
    S2J_STRUCT_GET_BASIC_ELEMENT_ISUSED(to_struct, from_json, type, element)

/* Get array type element for structure object */
#define s2j_struct_get_array_element(to_struct, from_json, type, element, len) \
    S2J_STRUCT_GET_ARRAY_ELEMENT(to_struct, from_json, type, element, len)

/* Get child structure type element for structure object */
#define s2j_struct_get_struct_element(child_struct, to_struct, child_json, from_json, type, element) \
    S2J_STRUCT_GET_STRUCT_ELEMENT(child_struct, to_struct, child_json, from_json, type, element)

#define s2j_struct_get_struct_element_start(child_struct, to_struct, child_json, from_json, type, element) \
    S2J_STRUCT_GET_STRUCT_ELEMENT(child_struct, to_struct, child_json, from_json, type, element)

#define s2j_struct_get_struct_element_end(child_struct, to_struct, child_json, from_json, type, element)   

#define s2j_struct_get_struct_element_isused_start(child_struct, to_struct, child_json, from_json, type, element) \
    S2J_STRUCT_GET_STRUCT_ELEMENT_ISUSED_START(child_struct, to_struct, child_json, from_json, type, element)

#define s2j_struct_get_struct_element_isused_end(child_struct, to_struct, child_json, from_json, type, element) \
    S2J_STRUCT_GET_STRUCT_ELEMENT_ISUSED_END(child_struct, to_struct, child_json, from_json, type, element)

/* Get enum type element for struct object */
#define s2j_struct_get_enum_element(to_struct, from_json, element, enum_string) \
    S2J_STRUCT_GET_ENUM_ELEMENT(to_struct, from_json, element, enum_string)
	
#define s2j_struct_get_enum_element_isused(to_struct, from_json, element, enum_string) \
    S2J_STRUCT_GET_ENUM_ELEMENT_ISUSED(to_struct, from_json, element, enum_string)

/* Get child struct array element from struct array object*/
#define s2j_struct_get_structArray_element_start(child_struct, to_struct, from_json, array_json, item_json, type, element, level) \
    S2J_STRUCT_GET_STRUCTARRAY_ELEMENT_START(child_struct, to_struct, from_json, array_json, item_json,  type, element, level)

#define s2j_struct_get_structArray_element_end(child_struct, to_struct, type, element) \
    S2J_STRUCT_GET_STRUCTARRAY_ELEMENT_END(child_struct, to_struct, type, element)

/* s2j.c */
extern S2jHook s2jHook;
void s2j_init(S2jHook *hook);

#ifdef __cplusplus
}
#endif

#endif /* __S2J_H__ */
