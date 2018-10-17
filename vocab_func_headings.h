#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//------------------------struct------------------------------

struct Point
{
    int number;
    char* word;
    char* definition;
};

//---------------------functions'-names-------------------------------

int TopicAndRules();

int CountStr(FILE* file);

int DefineOnePoint(FILE* file, struct Point* name, int number);

int DefinePoints(FILE* file, struct Point* buf, int buf_len);

int IWantToPlayAGame(struct Point* buf, int buf_len, char* correct_answer);

int GameEnvironment(struct Point* buf, int buf_len, char* correct_answer);
