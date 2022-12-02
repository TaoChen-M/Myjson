#include "leptjson.h"
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */

#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)

typedef struct {
    const char* json;
}lept_context;

/*跳过空白*/
static void lept_parse_whitespace(lept_context* c) {
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

static int lept_parse_null(lept_context* c, lept_value* v) {
    EXPECT(c, 'n');
    /*若值不是那三种字面值，传回 LEPT_PARSE_INVALID_VALUE，没懂*/
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_NULL;
    /* 增加如果一个值之后空白后还有其他字符，返回LEPT_PARSE_ROOT_NOT_SINGULAR
    while (*c->json==' ' || *c->json == '\t' || *c->json == '\n' || *c->json == '\r')
        c->json++;
    if(*c->json!='\0')return LEPT_PARSE_ROOT_NOT_SINGULAR;
     */
    return LEPT_PARSE_OK;
}
static int lept_parse_true(lept_context* c, lept_value* v) {
    EXPECT(c, 't');
    /*若值不是那三种字面值，传回 LEPT_PARSE_INVALID_VALUE，没懂*/
    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_TRUE;
    /* 增加如果一个值之后空白后还有其他字符，返回LEPT_PARSE_ROOT_NOT_SINGULAR
    while (*c->json==' ' || *c->json == '\t' || *c->json == '\n' || *c->json == '\r')
        c->json++;
    if(*c->json!='\0')return LEPT_PARSE_ROOT_NOT_SINGULAR;
     */
    return LEPT_PARSE_OK;
}
static int lept_parse_false(lept_context* c, lept_value* v) {
    EXPECT(c, 'f');
    /*若值不是那三种字面值，传回 LEPT_PARSE_INVALID_VALUE，没懂*/
    if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's',c->json[3] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 4;
    v->type = LEPT_FALSE;
    /* 增加如果一个值之后空白后还有其他字符，返回LEPT_PARSE_ROOT_NOT_SINGULAR
    while (*c->json==' ' || *c->json == '\t' || *c->json == '\n' || *c->json == '\r')
        c->json++;
    if(*c->json!='\0')return LEPT_PARSE_ROOT_NOT_SINGULAR;
     */
    return LEPT_PARSE_OK;
}
static int lept_parse_value(lept_context* c, lept_value* v) {
    switch (*c->json) {
        case 'n':  return lept_parse_null(c, v);
        case 't':  return lept_parse_true(c,v);
        case 'f':  return lept_parse_false(c,v);
        /*一个 JSON 只含有空白*/
        case '\0': return LEPT_PARSE_EXPECT_VALUE;
        default:   return LEPT_PARSE_INVALID_VALUE;
    }
}

/*跳过空白后，只需检测当前字符*/
/*减少解析函数之间传递多个参数，我们把这些数据都放进一个结构体，这里也没懂*/
int lept_parse(lept_value* v, const char* json) {
    lept_context c;
    assert(v != NULL);
    c.json = json;
    v->type = LEPT_NULL;
    lept_parse_whitespace(&c);
    int ret=lept_parse_value(&c, v);
    if(ret==LEPT_PARSE_OK){
        lept_parse_whitespace(&c);
        if(*c.json!='\0')
            return LEPT_PARSE_ROOT_NOT_SINGULAR;
    }
    return ret;
}

lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}
