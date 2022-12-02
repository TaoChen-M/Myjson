#ifndef LEPTJSON_H__
#define LEPTJSON_H__

/*定义Json文件中所有得数据类型*/
typedef enum { LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT } lept_type;

/*Json是一个树形结构，定义每个节点得类型*/
typedef struct {
    lept_type type;
}lept_value;

enum {
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR
};

/*解析json，确保不能更改输入数据，所以对char字符串使用const来修饰*/
int lept_parse(lept_value* v, const char* json);

/*获取最终得数据*/
lept_type lept_get_type(const lept_value* v);

#endif /* LEPTJSON_H__ */
