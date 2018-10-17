#include "vocab_func_headings.h"

int main()
{
    FILE* dictionary = NULL;
    char* dict_adress = "dictionary.txt";

    dictionary = fopen(dict_adress, "r");

    if (dictionary == NULL)
    {
        fclose(dictionary);

        return -1;
    }

    int amount_of_points = CountStr(dictionary);

    if (amount_of_points == 0)
    {
        printf("Dictionary file is empty. Please put there words you want to learn.\nPut them in format: 1. word\tdefinition\n\n");

        fclose(dictionary);

        return -1;
    }

    struct Point* buf = NULL;
    buf = (struct Point*) calloc(amount_of_points, sizeof(struct Point));

    if (buf == NULL)
    {
        printf("There is no enough memory for your dictionary in computer.");

        free(buf);
        fclose(dictionary);

        return -1;
    }

    if (DefinePoints(dictionary, buf, amount_of_points) == -1)
    {
        free(buf);
        fclose(dictionary);

        return -1;
    }

    TopicAndRules();

    char correct_answer[40] = {};

    srand(time(NULL));

    if (GameEnvironment(buf, amount_of_points, correct_answer) == -1)
    {
        free(buf);
        fclose(dictionary);

        return -1;
    }

    /*for (int i = 0; i < amount_of_points; i++)
    {
        free(buf[i].word);
        free(buf[i].definition);
    }*/

    free(buf);
    fclose(dictionary);

    return 0;
}

//--------------------------functions------------------------------

int TopicAndRules()
{
    printf("This program helps you in learning English vocabulary.\n\n");
    printf("RULES:\n");
    printf("You are given the definition of the word and your aim is to guess this word.");
    printf("You should write answers only with lowercase letters.\n\n");
    printf("//\\\\//\\\\//\\\\//\\\\//\\\\//\\\\//\\\\//\\\\//\\\\//\\\\//\\\\//\\\\\n\n");
    printf("So lets start:\n\n");

    return 0;
}

//-----------------------------------------------------------

int CountStr(FILE* file)
{
    fseek(file, 0, SEEK_SET);

    int count_str = 0;

    while (getc(file) != EOF)
    {
        fscanf(file, "%*[^\nEOF]");
        count_str++;
    }

    fseek(file, 0, SEEK_SET);

	return count_str;
}

//-------------------------------------------------------------------

int DefineOnePoint(FILE* file, struct Point* name, int number)
{
    if (file  == NULL)
        return -1;

    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < number - 1; i++)
    {
        fscanf(file, "%*[^\nEOF]");
        if (getc(file) == EOF)
            return -1;
    }

    fscanf(file, "%*[^A-Za-z]");
    int begining_pos = ftell(file);
    fscanf(file, "%*[^ \t]");
    int ending_pos = ftell(file);
    name->word = (char*) calloc((ending_pos - begining_pos) / sizeof(char), sizeof(char));
    begining_pos = ending_pos;
    fscanf(file, "%*[^\n]");
    ending_pos = ftell(file);
    name->definition = (char*) calloc((ending_pos - begining_pos) / sizeof(char), sizeof(char));

    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < number - 1; i++)
    {
        fscanf(file, "%*[^\nEOF]");
        if (getc(file) == EOF)
            return -1;
    }

    fscanf(file, "%d", &name->number);
    getc(file);
    getc(file);
    fscanf(file, "%[^ \t]", name->word);
    getc(file);
    fscanf(file ,"%[^\n]", name->definition);

    fseek(file, 0, SEEK_SET);

    return 0;
}

//-----------------------------------------------------------

int DefinePoints(FILE* file, struct Point* buf, int buf_len)
{
    if (file  == NULL)
        return -1;
    if (buf  == NULL)
        return -1;

    for (int i = 0; i < buf_len; i++)
        DefineOnePoint(file, &buf[i], i + 1);

    return 0;
}

//------------------------------------------------------------

int IWantToPlayAGame(struct Point* buf, int buf_len, char* correct_answer)
{
    if (buf  == NULL)
        return -1;

    if (correct_answer == NULL)
        return -1;

   int current_number = rand() % buf_len + 1;
   char buf_answer[40] = {};

   printf("%s\n", buf[current_number -1].definition);
   scanf("%s", buf_answer);
   printf("\n");

   for(int i = 0; buf[current_number -1].word[i] != '\0'; i++)
        correct_answer[i] = buf[current_number -1].word[i];

   for(int i = 0; buf_answer[i] != '\0'; i++)
   {
       if (buf_answer[i] != buf[current_number -1].word[i])
        return 0;
   }

   return 1;
}

//---------------------------------------------------------

int GameEnvironment(struct Point* buf, int buf_len, char* correct_answer)
{
  while (1)
    {
        switch (IWantToPlayAGame(buf, buf_len, correct_answer))
        {
            case 0:
            {
                printf("You lose\nThe correct answer was: %s\n\n", correct_answer);
                return 0;
            }
            case 1:
            {
                printf("Correct\n\n");
                printf("----------------------------------------------------\n\n");
                break;
            }
            default:
                return -1;
        }
    }
}
