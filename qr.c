#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void encode_char(const char character, bool bits[8]);

char decode_byte(const bool bits[8]);

void encode_string(const char string[], bool bytes[strlen(string)+1][8]);

void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]);

void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols],
                     const int rows, bool bytes[rows][8]);

 void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]);

int main() {

    // bool bits1[8];
    // encode_char('A', bits1);
    // for(int i = 0; i < 8; i++){
    //     printf("%d", bits1[i]);
    // }
    // printf("\n");
    // // prints: 01000001

    // bool bits2[8] = {0,1,0,0,0,0,0,1};
    // printf("%c\n", decode_byte(bits2));
    // // // prints: A


    // char* text = "Hello, how are you?";
    // const int len = strlen(text);
    // bool bytes1[len+1][8];
    // encode_string(text, bytes1);
    // for(int j = 0; j <= len; j++) {
    //     printf("%c: ", text[j]);
    //     for(int i = 0; i < 8; i++){
    //         printf("%d", bytes1[j][i]);
    //     }
    // printf("\n");
    // }


    // bool bytes2[7][8] = {
    // {0,1,0,0,1,0,0,0},
    // {0,1,1,0,0,1,0,1},
    // {0,1,1,0,1,1,0,0},
    // {0,1,1,0,1,1,0,0},
    // {0,1,1,0,1,1,1,1},
    // {0,0,1,0,0,0,0,1},
    // {0,0,0,0,0,0,0,0}
    // };
    // char string[7];
    // decode_bytes(7, bytes2, string);
    // printf("%s\n", string);


    int length = 4+1, cols = 3, offset = 2;
    bool bytes1[4+1][8] = {
        {0,1,0,0,0,0,0,1},
        {0,1,1,0,1,0,0,0},
        {0,1,1,0,1,1,1,1},
        {0,1,1,0,1,0,1,0},
        {0,0,0,0,0,0,0,0}
    };
    bool blocks1[offset*8][cols];
    bytes_to_blocks(cols, offset, blocks1, length, bytes1);
    for(int j = 0; j < offset*8; j++){
        for(int i = 0; i < cols; i++){
            printf("%d ", (blocks1[j][i] == true) ? 1 : 0);
        }
        printf("\n");
        if(j % 8 == 7){
            printf("\n");
        }
    }


    bool blocks2[2*8][3] = {
    {0,0,0},
    {1,1,1},
    {0,1,1},
    {0,0,0},
    {0,1,1},
    {0,0,1},
    {0,0,1},
    {1,0,1},
    {0,0,0},
    {1,0,0},
    {1,0,0},
    {0,0,0},
    {1,0,0},
    {0,0,0},
    {1,0,0},
    {0,0,0}
    };
    bool bytes2[length][8];
    blocks_to_bytes(3, 2, blocks2, length, bytes2);
    for(int j = 0; j < length; j++){
        for(int i = 0; i < 8; i++){
            printf("%d", bytes2[j][i]);
        }
        printf("\n");
    }

    return 0;
}


void encode_char(const char character, bool bits[8]) {
    int charDec = (int)character;
    int bValue[8] = {128, 64, 32, 16, 8, 4, 2, 1};

    for(int i = 0; i < 8; i++) {
        bits[i] = 0;
        if(bValue[i] <= charDec) {
            bits[i] = 1;
            charDec -= bValue[i];
        }
    }
}

char decode_byte(const bool bits[8]) {
    int temp = 0;
    int bValue[8] = {128, 64, 32, 16, 8, 4, 2, 1};

    for(int i = 0; i < 8; i++) {
        if(bits[i]) {
            temp += bValue[i];
        }
    }
    char symbol = (char)temp;

    return symbol;
}

void encode_string(const char string[], bool bytes[strlen(string)+1][8]) {
    int bValue[8] = {128, 64, 32, 16, 8, 4, 2, 1};
    
    for(int i = 0; i < strlen(string) + 1; i++) {
        int charDec = (int)string[i];
        for(int j = 0; j < 8; j++) {
            bytes[i][j] = false;
            if(bValue[j] <= charDec) {
                bytes[i][j] = true;
                charDec -= bValue[j];
            }
        }
    }
}

void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]) {
    int bValue[8] = {128, 64, 32, 16, 8, 4, 2, 1};
    
    for(int i = 0; i < rows; i++) {
        int temp = 0;
        for(int j = 0; j < 8; j++) {
            if(bytes[i][j]) {
                temp += bValue[j];
            }
        }
        string[i] = (char)temp;
    }
}

void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols],const int rows, bool bytes[rows][8]) {
    int iCols = 0, Iblock = 0;
    for(int i = 0; i < cols * offset; i++, iCols++) {
        if(iCols >= cols) {
            Iblock++;
            iCols = 0;
        }
        for(int j = 0; j < 8; j++) {
            if(i < rows) {
                blocks[j + (Iblock * 8)][iCols] = bytes[i][j];
            } else {
                blocks[j + (Iblock * 8)][iCols] = false;
            }
        }
    }
}

void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]) {
    int iCols = 0, iBlock = 0;
    
    for(int i = 0; i < rows; i++, iCols++) {
        if(iCols >= cols) {
            iBlock++;
            iCols = 0;
        }
        for(int j = 0; j < 8; j++) {
            bytes[i][j] = blocks[j + (iBlock * 8)][iCols];
        }
    }
}

// 01000001
// 01101000
// 01101111
// 01101010
// 00000000