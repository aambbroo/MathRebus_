#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>



typedef struct accord {
    char Char;
    short Num;
    bool Use;
};
struct accord Local_Accord[10];

int Nums[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
char Letters[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
char First_Item[11], Second_Item[11], Third_Item[11], Fourth_Item[11], Fifth_Item[11], Sixth_Item[11], Seventh_Item[11], Amount_Item[11];
short Border = 0;//
short Term_Nums = 2; //слагаемые
short Letter_Max_Nums = 1; //максимальное количество цифр - то есть длина item

//bool Check1 = false, Check2, Check3, Check4, Check5, Check6, Check7, Check8, Check9, Check0, Check_All_Nums;
bool Check[10], Check_All_Nums;

unsigned long long Items[8]; //Items[0] == First_Item etc...

clock_t start, start_bruteforce, end;

void Print_Time() {
    end = clock();
    int msec, msec_bruteforce;
    msec = (end - start) * 1000 / CLOCKS_PER_SEC;
    msec_bruteforce = (end - start_bruteforce) * 1000 / CLOCKS_PER_SEC;
    printf("\n\nAll time is %d seconds %d milliseconds.", msec / 1000, msec % 1000);
    printf("\n\nBruteforce time is %d seconds %d milliseconds.", msec_bruteforce / 1000, msec_bruteforce % 1000);
}


void Print_Result();

/*Проверка на нахождения в слагаемом или сумме*/

inline bool Letter_Check(char check) {
    for (int i = 0; i < 26; i++) {
        if (Letters[i] == check) return true;
    }
    //printf("Use not big latin letter!\n");
    return false;
}

/*Инициализация значений логическх переменных*/

inline void Term_Init(void) {
    for (short i = 0; i < 10; i++)
        Check[i] = false;
    Check_All_Nums = false;
    for (short i = 0; i < 8; i++)
        Items[i] = 0;
}

/*Получаем указатель на соответсвующую переменную: слагаемое 1 - 7 или сумма*/

inline char* Choice(short i) {
    if (i == 1)
        return First_Item;
    else if (i == 2)
        return Second_Item;
    else if (i == 3)
        return Third_Item;
    else if (i == 4)
        return Fourth_Item;
    else if (i == 5)
        return Fifth_Item;
    else if (i == 6)
        return Sixth_Item;
    else if (i == 7)
        return Seventh_Item;
    else if (i == 8)
        return Amount_Item;
}

/*Разделяем входную строку на слагаемые и сумму*/

inline void Make_Items(char String[102]) {
    char b = '\0', bb = '\n';
    char c;
    char* Word = NULL;
    short i;
    short offset = 0;
    short word = 0;
    bool No_Word = false;
    for (i = 0; i < 102; i++) {
        c = String[i];
        if (c == b || c == bb) break;  //должна идти проверка полученного выражения или вызов в другом месте данной проверки

        if (Letter_Check(c)) No_Word = false;
        else No_Word = true;

        if (!No_Word) {
            if (i == 0 && word == 0 && offset == 0) {
                word++;
                Word = Choice(word);
                Word[offset] = c;
                offset++;
            }
            else {
                Word[offset] = c;
                offset++;
            }
        }
        else {
            if (c == ' ' && (String[i + 1] == '+' || String[i + 1] == '=') && String[i + 2] == ' ') {
                i++; i++; Term_Nums = word;  word++;
                if (String[i - 1] == '=') word = 8;
                Word = Choice(word);
                if (offset > Letter_Max_Nums) Letter_Max_Nums = offset;
                offset = 0;
            }
        }
    }
}

/*Проверка на простые ошибки*/

inline void Errors_Check() {
    printf("First item is %s.\n", First_Item);
    printf("Second item is %s.\n", Second_Item);
    printf("Third item is %s.\n", Third_Item);
    printf("Fourth item is %s.\n", Fourth_Item);
    printf("Fifth item is %s.\n", Fifth_Item);
    printf("Sixth item is %s.\n", Sixth_Item);
    printf("Seventh item is %s.\n", Seventh_Item);
    printf("Amount item is %s.\n", Amount_Item);
    if (Term_Nums < 2 || Term_Nums>7) printf("There are some problems with Term_Nums, it is %d.\n", Term_Nums);
    if (Letter_Max_Nums < 1 || Letter_Max_Nums>10) printf("There are some problems with Letter_Max_Nums, it is %d.\n", Letter_Max_Nums);
}


/*Занесение значение в Local_Accord*/

inline short Accord_Check(char c) {
    for (short i = 0; i < 10; i++)
        if (c == Local_Accord[i].Char) return Local_Accord[i].Num;
    return -1;
}

inline void Form_Accord_Struct() {
    char* Item = NULL;
    char letter;
    for (short i = 1; i <= Term_Nums; i++) {
        Item = Choice(i);
        for (short j = 0; j < strlen(Item); j++) {
            letter = Item[j];
            short offset = Accord_Check(letter);
            if (offset == -1) {
                for (offset = 0; offset < 10; offset++) {
                    if (!isalpha(Local_Accord[offset].Char)) {
                        Local_Accord[offset].Char = letter;
                        Local_Accord[offset].Use = true;
                        offset = 10;
                    }
                }
            }
        }
    }
    Item = Choice(8);
    for (short j = 0; j < strlen(Item); j++) {
        letter = Item[j];
        short offset = Accord_Check(letter);
        if (offset == -1) {
            for (offset = 0; offset < 10; offset++) {
                if (!isalpha(Local_Accord[offset].Char)) {
                    Local_Accord[offset].Char = letter;
                    Local_Accord[offset].Use = true;
                    offset = 10;
                }
            }
        }
    }
}

inline short Num_Return(char c) {
    for (short i = 0; i < 10; i++) {
        if (c == Local_Accord[i].Char) return Local_Accord[i].Num;
    }
    return -1;
}

inline void Make_Case() {
    char* Item = NULL;
    char c;
    unsigned long long m = 1;
    for (short i = 1; i <= Term_Nums; i++) {
        Item = Choice(i);
        m = 1;
        for (short j = strlen(Item) - 1; j >= 0; j--) {//
            c = Item[j];
            short k = Num_Return(c);
            if (k == -1) {
                printf("\nThere is some problem\n");
                return;
            }
            if (j == 0 && k == 0 && strlen(Item) > 1) {
                //printf("\n0 in start of item\n");
                Border = -1;
                return;
            }
            Items[i - 1] += m * k;
            m *= 10;
        }
    }
    Item = Choice(8);
    m = 1;
    for (short j = strlen(Item) - 1; j >= 0; j--) {//
        c = Item[j];
        short k = Num_Return(c);
        if (k == -1) {
            printf("\nThere is some problem\n");
            return;
        }
        if (j == 0 && k == 0 && strlen(Item) > 1) {
            //printf("\n0 in start of item\n");
            Border = -1;
            return;
        }
        Items[7] += m * k;
        m *= 10;
    }
    Border = 0;
}

/*Проверка решения*/

inline bool Try() {
    Make_Case();
    if (Border != -1)
        if (Items[0] + Items[1] + Items[2] + Items[3] + Items[4] + Items[5] + Items[6] == Items[7]) return true;
    for (short i = 0; i < 8; i++)
        Items[i] = 0;
    return false;
}

inline bool Check_() {
    char* Item = NULL;
    char c;
    short s = 0;
    for (short i = 1; i <= Term_Nums; i++) {
        Item = Choice(i);
        c = Item[strlen(Item) - 1];
        s += Num_Return(c);
    }
    Item = Choice(8);
    c = Item[strlen(Item) - 1];
    if (s % 10 == Num_Return(c)) return true;
    else return false;
}

/*Подбор*/

void Bruteforce() {
    for (short i = 0; i < 10; i++) {
        short offset = 9;
        Local_Accord[offset].Num = Nums[i];
        for (short j = 0; j < 10; j++) {
            if ((Local_Accord[offset].Use) && (j == i)) continue;
            offset = 8;
            Local_Accord[offset].Num = Nums[j];
            for (short k = 0; k < 10; k++) {
                if ((Local_Accord[offset].Use) && (k == j || k == i)) continue;
                offset = 7;
                Local_Accord[offset].Num = Nums[k];
                for (short l = 0; l < 10; l++) {
                    if ((Local_Accord[offset].Use) && (l == k || l == j || l == i)) continue;
                    offset = 6;
                    Local_Accord[offset].Num = Nums[l];
                    for (short p = 0; p < 10; p++) {
                        if ((Local_Accord[offset].Use) && (p == l || p == k || p == j || p == i)) continue;
                        offset = 5;
                        Local_Accord[offset].Num = Nums[p];
                        for (short o = 0; o < 10; o++) {
                            if ((Local_Accord[offset].Use) && (o == p || o == l || o == k || o == j || o == i)) continue;
                            offset = 4;
                            Local_Accord[offset].Num = Nums[o];
                            for (short u = 0; u < 10; u++) {
                                if ((Local_Accord[offset].Use) && (u == o || u == p || u == l || u == k || u == j || u == i)) continue;
                                offset = 3;
                                Local_Accord[offset].Num = Nums[u];
                                for (short y = 0; y < 10; y++) {
                                    if ((Local_Accord[offset].Use) && (y == u || y == o || y == p || y == l || y == k || y == j || y == i)) continue;
                                    offset = 2;
                                    Local_Accord[offset].Num = Nums[y];
                                    for (short t = 0; t < 10; t++) {
                                        if ((Local_Accord[offset].Use) && (t == y || t == u || t == o || t == p || t == l || t == k || t == j || t == i)) continue;
                                        offset = 1;
                                        Local_Accord[offset].Num = Nums[t];
                                        for (short x = 0; x < 10; x++) {
                                            if ((Local_Accord[offset].Use) && (x == t || x == y || x == u || x == o || x == p || x == l || x == k || x == j || x == i)) continue;
                                            offset = 0;
                                            Local_Accord[offset].Num = Nums[x];
                                            if (!Check_()) continue;
                                            if (Try()) return;
                                            //Print_Result();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


void Print_Result() {
    if (Border == -1) return;
    printf("\n\n");
    for (short i = 0; i < 8; i++) {
        if (1) {
            if (i == 7) printf(" = ");
            else if (i > 0) printf(" + ");
            printf("%lld", Items[i]);
        }
    }
}

int main()
{
    printf("Enter string:\n");
    char S[102]; int i = -1;
    char c = ' ';
    while (c != '\0' && c != '\n')
    {
        scanf("%c", &c);
        S[++i] = c;
    }
    start = clock();
    Make_Items(S);
    Errors_Check();
    Form_Accord_Struct();
    start_bruteforce = clock();
    Bruteforce();
    Print_Time();
    Print_Result();
    return 0;
}
