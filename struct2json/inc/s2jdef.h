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
 * Function: It is an head file for this library.
 * Created on: 2015-10-14
 */

#ifndef __S2JDEF_H__
#define __S2JDEF_H__

#include <cJSON.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void *(*malloc_fn)(size_t sz);
    void (*free_fn)(void *ptr);
} S2jHook, *S2jHook_t;

#define S2J_STRUCT_ISUSED_BASIC_ELEMENT(to_struct, from_json, _element) \
    (to_struct)->_element ## _isUsed = 1;

#define S2J_STRUCT_GET_ENUM_ELEMENT(to_struct, from_json, _element, enum_string) \
    if (from_json) { \
        json_temp = cJSON_GetObjectItem(from_json, #_element); \
        if (json_temp) {\
            for(int i=0; i< sizeof(enum_string)/sizeof(enum_string[0]); i++) { \
                if((json_temp->valuestring) && (0 == strcmp(enum_string[i], json_temp->valuestring))) {\
                    (to_struct)->_element = i;\
                }\
            }\
        } \
    }

#define S2J_STRUCT_GET_ENUM_ELEMENT_ISUSED(to_struct, from_json, _element, enum_string) \
    if (from_json) { \
        json_temp = cJSON_GetObjectItem(from_json, #_element); \
        if (json_temp) {\
            for(int i=0; i< sizeof(enum_string)/sizeof(enum_string[0]); i++) { \
                if((json_temp->valuestring) && (0 == strcmp(enum_string[i], json_temp->valuestring))) {\
                    (to_struct)->_element = i;\
                }\
            }\
    		(to_struct)->_element ## _isUsed = 1; \
        } \
    	else (to_struct)->_element ## _isUsed = 0; \
    } else (to_struct)->_element ## _isUsed = 0;

#define S2J_STRUCT_GET_int_ELEMENT(to_struct, from_json, _element) \
    if (from_json) { \
        json_temp = cJSON_GetObjectItem(from_json, #_element); \
        if (json_temp) (to_struct)->_element = json_temp->valueint; \
    }

#define S2J_STRUCT_GET_int_ELEMENT_ISUSED(to_struct, from_json, _element) \
    if (from_json) { \
        json_temp = cJSON_GetObjectItem(from_json, #_element); \
        if (json_temp) { (to_struct)->_element = json_temp->valueint; (to_struct)->_element ## _isUsed = 1;} \
    	else (to_struct)->_element ## _isUsed = 0; \
    } else (to_struct)->_element ## _isUsed = 0;

#define S2J_STRUCT_GET_string_ELEMENT_ISUSED(to_struct, from_json, _element) \
	S2J_STRUCT_GET_string_ELEMENT(to_struct, from_json, _element)

#define S2J_STRUCT_GET_string_ELEMENT(to_struct, from_json, _element) \
    if (from_json) { \
        json_temp = cJSON_GetObjectItem(from_json, #_element); \
        if (json_temp) {\
            if (json_temp->valuestring) \
            { \
                strcpy((to_struct)->_element, json_temp->valuestring); \
                (to_struct)->_element ## Len = strlen(json_temp->valuestring);\
            } \
            else \
            {(to_struct)->_element ## Len = 0; } \
        } \
    	else \
    		(to_struct)->_element ## Len = 0; \
    } else (to_struct)->_element ## Len = 0; 

#define S2J_STRUCT_GET_double_ELEMENT(to_struct, from_json, _element) \
    if (from_json) {\
        json_temp = cJSON_GetObjectItem(from_json, #_element); \
        if (json_temp) (to_struct)->_element = json_temp->valuedouble; \
    }

#define S2J_STRUCT_GET_double_ELEMENT_ISUSED(to_struct, from_json, _element) \
    if (from_json) { \
        json_temp = cJSON_GetObjectItem(from_json, #_element); \
        if (json_temp) { (to_struct)->_element = json_temp->valuedouble; (to_struct)->_element ## _isUsed = 1; }\
    	else	(to_struct)->_element ## _isUsed = 0; \
    } else (to_struct)->_element ## _isUsed = 0;

#define S2J_STRUCT_ARRAY_GET_int_ELEMENT(to_struct, from_json, _element, index) \
    (to_struct)->_element[index] = from_json->valueint;

#define S2J_STRUCT_ARRAY_GET_string_ELEMENT(to_struct, from_json, _element, index) \
    if (from_json && from_json->valuestring) \
    strcpy((to_struct)->_element[index], from_json->valuestring);

#define S2J_STRUCT_ARRAY_GET_double_ELEMENT(to_struct, from_json, _element, index) \
    (to_struct)->_element[index] = from_json->valuedouble;

#define S2J_STRUCT_ARRAY_GET_ELEMENT(to_struct, from_json, type, _element, index) \
    S2J_STRUCT_ARRAY_GET_##type##_ELEMENT(to_struct, from_json, _element, index)

#define S2J_STRUCT_ARRAY_GET_int_STRUCT_ELEMENT(to_struct, from_json, _element, index, _level) \
    if (from_json) (to_struct)->_element[index] = from_json->valueint; \
    else (to_struct)->_element[index] = 0; 

#define S2J_STRUCT_ARRAY_GET_string_STRUCT_ELEMENT(to_struct, from_json, _element, index, _level) \
    if (from_json && from_json->valuestring) \
    strcpy((to_struct)->_element[index], from_json->valuestring); \
    else strcpy((to_struct)->_element[index], ""); 

#define S2J_STRUCT_ARRAY_GET_double_STRUCT_ELEMENT(to_struct, from_json, _element, index, _level) \
    if (from_json) (to_struct)->_element[index] = from_json->valuedouble; \
    else (to_struct)->_element[index] = 0;

#define S2J_STRUCT_ARRAY_GET_STRUCT_ELEMENT(to_struct, from_json, type, _element, index, _level) \
    S2J_STRUCT_ARRAY_GET_##type##_STRUCT_ELEMENT(to_struct, from_json, _element, index, _level)

#define S2J_JSON_SET_int_ELEMENT(to_json, from_struct, _element) \
    cJSON_AddNumberToObject(to_json, #_element, (from_struct)->_element);

#define S2J_JSON_SET_double_ELEMENT(to_json, from_struct, _element) \
    cJSON_AddNumberToObject(to_json, #_element, (from_struct)->_element);

#define S2J_JSON_SET_string_ELEMENT(to_json, from_struct, _element) \
    cJSON_AddStringToObject(to_json, #_element, (from_struct)->_element);

#define S2J_JSON_SET_boolean_ELEMENT(to_json, from_struct, _element) \
    cJSON_AddBoolToObject(to_json, #_element, (from_struct)->_element);

#define S2J_JSON_ARRAY_SET_int_ELEMENT(to_json, from_struct, _element, index) \
    cJSON_AddItemToArray(to_json, cJSON_CreateNumber((from_struct)->_element[index]));

#define S2J_JSON_ARRAY_SET_double_ELEMENT(to_json, from_struct, _element, index) \
    cJSON_AddItemToArray(to_json, cJSON_CreateNumber((from_struct)->_element[index]));

#define S2J_JSON_ARRAY_SET_string_ELEMENT(to_json, from_struct, _element, index) \
    cJSON_AddItemToArray(to_json, cJSON_CreateString((from_struct)->_element[index]));

#define S2J_JSON_ARRAY_SET_ELEMENT(to_json, from_struct, type, _element, index) \
    S2J_JSON_ARRAY_SET_##type##_ELEMENT(to_json, from_struct, _element, index)

//todo
#define S2J_JSON_ARRAY_SET_int_STRUCT_ELEMENT(array_json, array_struct, element ) \
	cJSON_AddNumberToObject(array_json, #element, array_struct->element)

#define S2J_JSON_ARRAY_SET_string_STRUCT_ELEMENT(array_json, array_struct, element ) \
	cJSON_AddStringToObject(array_json, #element, array_struct->element)

#define S2J_JSON_ARRAY_SET_double_STRUCT_ELEMENT(array_json, array_struct, element ) \
	cJSON_AddNumberToObject(array_json, #element, array_struct->element)

#define S2J_JSON_ARRAY_SET_STRUCT_ELEMENT(array_json, array_struct, type, element ) \
    S2J_JSON_ARRAY_SET_##type##_STRUCT_ELEMENT(to_json, from_struct, type, element)
    

#define S2J_CREATE_JSON_OBJECT(json_obj) \
    cJSON *json_obj = cJSON_CreateObject();

#define S2J_DELETE_JSON_OBJECT(json_obj) \
    cJSON_Delete(json_obj);

#define S2J_JSON_SET_BASIC_ELEMENT(to_json, from_struct, type, _element) \
    S2J_JSON_SET_##type##_ELEMENT(to_json, from_struct, _element)

#define S2J_JSON_SET_ENUM_ELEMENT(to_json, from_struct, _element, enum_string) \
    if (from_struct->_element <= sizeof(enum_string)/sizeof(enum_string[0])) {\
        cJSON_AddStringToObject(to_json, #_element, enum_string[from_struct->_element]); \
    }

#define S2J_JSON_SET_ARRAY_ELEMENT(to_json, from_struct, type, _element, size) \
    { \
        cJSON *array; \
        size_t index = 0; \
        array = cJSON_CreateArray(); \
        if (array) { \
            while (index < size) { \
                S2J_JSON_ARRAY_SET_ELEMENT(array, from_struct, type, _element, index++); \
            } \
            cJSON_AddItemToObject(to_json, #_element, array); \
        } \
    }

#define S2J_JSON_SET_STRUCT_ELEMENT(child_json, to_json, child_struct, from_struct, type, _element) \
    type *child_struct = &((from_struct)->_element); \
    cJSON *child_json = cJSON_CreateObject(); \
    if (child_json) cJSON_AddItemToObject(to_json, #_element, child_json);

//add struct array to json convert functions.
#define S2J_JSON_SET_STRUCTARRAY_ELEMENT_START(array_json, to_json, item_json, from_struct, array_struct, type, _element, _level) \
    { \
        cJSON *array_json, *item_json;\
		type *array_struct = from_struct->_element ; \
        size_t index##_level = 0, size##_level = 0; \
		size##_level = from_struct->_element ## Len; \
		if( size##_level > 0) {\
        	array_json = cJSON_CreateArray(); \
        	if (array_json) { \
            	while (index##_level < size##_level) { \
					index##_level++; \
					item_json = cJSON_CreateObject(); \

#define S2J_JSON_STRUCTARRAY_SET_ELEMENT(item_json, item_struct, type, _element) \
					S2J_JSON_ARRAY_SET_STRUCT_ELEMENT( item_json, item_struct, type, _element )

#define S2J_JSON_SET_STRUCTARRAY_ELEMENT_END(array_json, to_json, array_struct, item_json, _element, _level) \
					array_struct++; \
					cJSON_AddItemToArray(array_json, item_json); \
            	} \
				cJSON_AddItemToObject(to_json, #_element, array_json); \
        	} \
		}\
    }


#define S2J_CREATE_STRUCT_OBJECT(struct_obj, type) \
    cJSON *json_temp; \
    type *struct_obj = s2jHook.malloc_fn(sizeof(type)); \
    if (struct_obj) memset(struct_obj, 0, sizeof(type));

#define S2J_DELETE_STRUCT_OBJECT(struct_obj) \
    s2jHook.free_fn(struct_obj);

#define S2J_STRUCT_GET_BASIC_ELEMENT(to_struct, from_json, type, _element) \
    S2J_STRUCT_GET_##type##_ELEMENT(to_struct, from_json, _element)
	
#define S2J_STRUCT_GET_BASIC_ELEMENT_ISUSED(to_struct, from_json, type, _element) \
    S2J_STRUCT_GET_##type##_ELEMENT_ISUSED(to_struct, from_json, _element)

#define S2J_STRUCT_GET_ARRAY_ELEMENT(to_struct, from_json, type, _element, len) \
    { \
        cJSON *array, *array_element; \
        size_t index = 0, size = 0; \
        array = cJSON_GetObjectItem(from_json, #_element); \
        if (array) { \
            size = cJSON_GetArraySize(array); \
            while ((index < size) && (index < len)) { \
                array_element = cJSON_GetArrayItem(array, index); \
                if (array_element) S2J_STRUCT_ARRAY_GET_ELEMENT(to_struct, array_element, type, _element, index++); \
            } \
            to_struct->_element ## Len = size; \
        } \
    }


//add json to struct array convert functions.
#define S2J_STRUCT_GET_STRUCTARRAY_ELEMENT_START(child_struct, to_struct, from_json, array_json, item_json, type, _element, _level) \
    { \
        cJSON *array_json, *item_json; \
        size_t index##_level = 0, size##_level = 0; \
		type *child_struct = to_struct->_element ; \
        array_json = cJSON_GetObjectItem(from_json, #_element); \
        if (array_json) { \
            size##_level = cJSON_GetArraySize(array_json); \
            while (index##_level < size##_level) { \
                item_json = cJSON_GetArrayItem(array_json, index##_level); \
                if (item_json) \
				{ \
					index##_level++; \

#define S2J_STRUCT_STRUCTARRAY_GET_ELEMENT(child_struct, to_struct, item_json, type, _element) \
					S2J_STRUCT_ARRAY_GET_STRUCT_ELEMENT(child_struct, to_struct, item_json, type, _element )

#define S2J_STRUCT_GET_STRUCTARRAY_ELEMENT_END(child_struct, to_struct, _element, _level) \
					child_struct++; \
				}\
            } \
            to_struct->_element ## Len = size##_level; \
        } \
    }

#define S2J_STRUCT_GET_STRUCT_ELEMENT(child_struct, to_struct, child_json, from_json, type, _element) \
    type *child_struct = &((to_struct)->_element); \
    cJSON *child_json = cJSON_GetObjectItem(from_json, #_element);

#define S2J_STRUCT_GET_STRUCT_ELEMENT_ISUSED_START(child_struct, to_struct, child_json, from_json, type, _element) \
    type *child_struct = &((to_struct)->_element); \
    cJSON *child_json = cJSON_GetObjectItem(from_json, #_element); \
	if( child_json ) { (to_struct)->_element ## _isUsed = 1; 

#define S2J_STRUCT_GET_STRUCT_ELEMENT_ISUSED_END(child_struct, to_struct, child_json, from_json, type, _element) \
	} \
	else	(to_struct)->_element ## _isUsed = 0;

#ifdef __cplusplus
}
#endif

#endif /* __S2JDEF_H__ */
