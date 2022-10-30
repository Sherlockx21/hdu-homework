//
// Created by hang on 2022/10/20.
//
#include "define.h"

void Define(char c,char* s){
    int key = c - 'A';
    int i = 0;
    int index = 0;
    while(s[i] != '0'){
        if(s[i] >= 'a' && s[i] <= 'z')
            Map[key][index++] = s[i++];
        else{
            int j = 0;
            while(Map[s[i]][j] != '\0'){
                Map[key][index++] = Map[s[i]][j++];
            }
            i++;
        }
    }
}