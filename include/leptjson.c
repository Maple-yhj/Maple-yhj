#include "leptjson.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define lept_init(v) do { (v)->type = LEPT_NULL; } while(0)
#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)
#define ISDIGIT(ch)         ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch)     ((ch) >= '1' && (ch) <= '9')
#define STACK_INIT_SIZE 256;

typedef struct
{
    const char* json;
    char *stack;
    size_t top,size;
}lept_context;

/*free function*/
void lept_free(lept_value *v)
{
    assert(v != NULL);
    if(v->type == LEPT_STRING)
        free(v->u.s.str);
    v->type = LEPT_NULL;
}


/*get data function */
double lept_get_number(const lept_value* v)
{
    assert(v != NULL && v->type == LEPT_NUM);
    return v->u.n;
}

lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}

/*set data function*/
void lept_set_string(lept_value *v, const char* s, size_t len){

    assert(v != NULL && (s != NULL || len == 0));
    lept_free(v);
    v->u.s.str = (char*)malloc(len+1);
    memcpy(v->u.s.str , s ,len);
    v->u.s.str[len] = '/0';
    v->type = LEPT_STRING;
}

/*stack function*/
static void* lept_stack_push(lept_context* c, size_t size)
{
    assert(size > 0);
    void* res;
    if(c->top + size >= c->size)
    {
        if(c->size == 0)
            c->size = STACK_INIT_SIZE;
        while (c->top + size > c->size)
        {
            c->size *= 1.5;
        }
        c->stack = (char*)realloc(c->stack,c->size);
    }
    res = c->stack + c->top;
    c->top += size;

    return res; //返回的是栈顶指针
} 

static void* lept_stack_pop(lept_context* c, size_t size)
{
    assert(c->top >= size);
    
    return c->stack + (c->top -= size);
} 

// 去除json字符串前的空格
static void lept_parse_wthinspace(lept_context *c)
{
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

// 
static int lept_parse_literal(lept_context *c , lept_value *v , const char *compare_str , lept_type type)
{
    size_t i = 0;
    EXPECT(c,compare_str[0]);
    for (i = 0;compare_str[i+1] ; i++)
        if(c->json[i] != compare_str[i+1])
            return LEPT_PARSE_INVALID_VALUE;
    

    c->json +=i;
    v->type = type;
    return LEPT_PARSE_OK;

}

static int lept_parse_number(lept_context *c , lept_value *v)
{
    const char* ch = c->json;
    if(*ch == '-')
        ch++;

    if(*ch == '0')
        ch++;
    else
    {
        if(!ISDIGIT1TO9(*ch))
            return LEPT_PARSE_INVALID_VALUE;
        
        for (ch++ ;ISDIGIT(*ch) ; ch++);
        
    }

    if (*ch == '.')
    {
        ch++;
        if(!ISDIGIT(*ch))
            return LEPT_PARSE_INVALID_VALUE;

        for (ch++ ;ISDIGIT(*ch) ; ch++);
    }
    
    if(*ch == 'E' || *ch == 'e')
    {
        ch++;
        if(*ch == '+' || *ch == '-')
            ch++;
        
        if(!ISDIGIT(*ch)) return LEPT_PARSE_INVALID_VALUE;
        for(ch++ ; ISDIGIT(*ch); ch++);
    }
    errno = 0;

    v->u.n = strtod(c->json,NULL);
    if(errno == ERANGE && (v->u.n == HUGE_VAL || v->u.n == -HUGE_VAL))
        return LEPT_PARSE_INVALID_VALUE;
    
    v->type = LEPT_NUM;
    c->json = ch;

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


