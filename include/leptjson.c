#include "leptjson.h"
#include <assert.h>
#include <stdlib.h>

#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)
#define ISDIGIT(ch)         ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch)     ((ch) >= '1' && (ch) <= '9')

typedef struct
{
    const char* json
}lept_context;

/*start get_data function */
double lept_get_number(const lept_value* v)
{
    assert(v != NULL && v->type == LEPT_NUM);
    return v->n;
}

lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}

/*end get_data function */


// 去除json字符串前的空格
static void lept_parse_wthinspace(lept_context *c)
{
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

// 
static int lept_parse_literal(lept_context *c , lept_value *v , char *compare_str , lept_type type)
{
    
    while (*c->json != '\0' && *compare_str != '\0')
    {
        if(*c->json != *compare_str)
            return LEPT_PARSE_INVALID_VALUE;
        else
        {
            c->json++;
            compare_str++;
        }
    }

    if(*c->json == '\0' && *c->json != *compare_str)
        return LEPT_PARSE_INVALID_VALUE;

    v->type = type;
    return LEPT_PARSE_OK;

}

static int lept_parse_number(lept_context *c , lept_value *v)
{
    char* ch = c->json;
    if(*ch == '-')
        ch += 1;

    if(!ISDIGIT(ch))
        return LEPT_PARSE_INVALID_VALUE;
    else
        ch += 1;
    
    char* cur_ptr = ch;
    char* after_ptr = ch + 1;
    while (*cur_ptr != '\0')
    {
        if(*cur_ptr == '.' && !ISDIGIT(*after_ptr))
            return LEPT_PARSE_INVALID_VALUE;

        cur_ptr++;
        after_ptr++;
    }
    

    int res = strtod(c->json,NULL);
    

    v->n = res;
    v->type = LEPT_NUM;

    return LEPT_PARSE_OK;
}

// 判断json的值是否有效
static int lept_parse_value(lept_context *c ,lept_value *v)
{
    switch (*c->json)
    {
        case 'n': return lept_parse_literal(c,v,"null",LEPT_NULL);
        case 't': return lept_parse_literal(c,v,"true",LEPT_TRUE);
        case 'f': return lept_parse_literal(c,v,"false",LEPT_FALSE);
        case '\0': return LEPT_PARSE_EXPECT_VALUE;
        default: return lept_parse_number(c, v);
        
    }
}

int lept_parse(lept_value* v, const char* json)
{
    
    lept_context c;
    int ret;
    assert(v!=NULL);
    c.json=json;
    v->type=LEPT_NULL;
    lept_parse_wthinspace(&c);
    if((ret = lept_parse_value(&c , v)) == LEPT_PARSE_OK)
    {
        lept_parse_wthinspace(&c);
        if(*c.json != '\0')
            ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
    }
    
    return ret;
}


