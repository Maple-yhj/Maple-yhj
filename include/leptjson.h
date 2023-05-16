#ifndef MYJSON_H__
#define  MYJSON_H__

/*json只包含6个类型：null,boolean,number,string,array,object*/
typedef enum{LEPT_NULL ,LEPT_TRUE ,LEPT_FALSE ,LEPT_NUM ,LEPT_STRING ,LEPT_ARRAY ,LEPT_OBJECT} lept_type;

/*树结点*/
typedef struct
{
    union{
        struct 
        {
            char *str;
            size_t len;
        }s;
        double n;
    }u;
    lept_type type;
}lept_value;

/*用于判断json中的值是否有效*/
enum {
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR
};

int lept_parse(lept_value* v, const char* json);

lept_type lept_get_type(const lept_value* v);

double lept_get_number(const lept_value* v);

#endif