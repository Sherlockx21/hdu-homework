//
// Created by hang on 2022/10/20.
//

#ifndef EXP2_LANGUAGE_PARSE_H
#define EXP2_LANGUAGE_PARSE_H

#include "queue.h"

#define MAXSIZE 100000



Queue* Parse(char *s); //去括号
Queue* Translate(Queue* q); //翻译大写字母
#endif //EXP2_LANGUAGE_PARSE_H
