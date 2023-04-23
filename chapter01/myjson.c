#include "myjson.h"
#include <assert.h>
#include <stdlib.h>

#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)

typedef struct
{
    const char* json
}lept_context;

/*去除json字符串前的空格*/
static void lept_parse_wthinspace(lept_context *c)
{
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}


static int lept_parse_null(lept_context *c , lept_value *v)
{
    EXPECT(c, 'n');
    if(c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;
    c += 3;
    v->type = LEPT_NULL;
    return LEPT_PARSE_OK;
}
static int lept_parse_true(lept_context *c , lept_value *v)
{
    EXPECT(c, 't');
    if(c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c += 3;
    v->type = LEPT_TRUE;
    return LEPT_PARSE_OK;
}
static int lept_parse_false(lept_context *c , lept_value *v)
{
    EXPECT(c, 'f');
    if(c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c += 4;
    v->type = LEPT_FALSE;
    return LEPT_PARSE_OK;
}



/*判断json的值是否有效*/
static int lept_parse_value(lept_context *c ,lept_value *v)
{
    switch (*c->json)
    {
        case 'n': return lept_parse_null(c,v);
        case 't': return lept_parse_true(c,v);
        case 'f': return lept_parse_false(c,v);
        case '\0': return LEPT_PARSE_EXPECT_VALUE;
        default: return LEPT_PARSE_INVALID_VALUE;
        
    }
}


int lept_parse(lept_value* v, const char* json)
{
    lept_context c;
    if(v!=NULL)
    {
        c.json=json;
        v->type=LEPT_NULL;
        lept_parse_wthinspace(&c);
        return lept_parse_value(&c , v);
    }
}