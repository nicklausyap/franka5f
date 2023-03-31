// Date created: 29 March 2023
// franka5f_enc.cpp
// This source file is part of the franka5f open source project
// Copyright (c) 2023 nicklaus yap ken yik

#include <cstdio>
#include <cstdlib>

int main()
{

FILE *fp;

fp = fopen("f0_f4.f5f", "ab");
// temporary buffer to hold f0-f4 to be used later on
unsigned char *f5 = (unsigned char*) malloc(81);
if (f5 == NULL) {
    exit(EXIT_FAILURE);
}

// 00000000 is the padded value
// f0 value is 67452301
unsigned char f0[17] = "6745230100000000";
// f1 value is EFCDAB89
unsigned char f1[17] = "EFCDAB8900000000";
// f2 value is 98BADCFE
unsigned char f2[17] = "98BADCFE00000000";
// f3 value is 10325476
unsigned char f3[17] = "1032547600000000";
// f4 value is C3D2E1F0
unsigned char f4[17] = "C3D2E1F000000000";

// the example input
unsigned char w[17] = "ABCDABCD12345678";
// example key. if key value too short will be padded with value 0. TO BE DONE later
//unsigned char key[17] = "ppppppppppppPPPL";
// test another different key
unsigned char key[17] = "happyhappyhappy0";

for (int i = 0; i <= 15; i++) {
    w[i] = w[i] ^ key[i];
}

// get the last value of w[15];
// put w[15] into a variable;
int B = w[15];
int f;

// another section 
if (0 <= B <= 19)
f = (w[2] & w[3]) ^ ((!w[2]) & w[4]);
else if (20 <= B <= 39)
f = w[2] ^ w[3] ^ w[4];
else if (40 <= B <= 59)
f = (w[2] & w[3]) ^ (w[2] & w[4]) ^ (w[3] & w[4]);
else if (60 <= B <= 79)
f = w[4] ^ w[5] ^ w[6];
else
f = w[3] ^ w[7] ^ w[8];

// temporary buffer
unsigned char temp[17] = "0000000000000000";

for(int n = 0; n <= 16; n++){
// start with temp[0]
if(n == 0){
temp[n] = f + 'C';
}else if (n == 1){
temp[n] = f + 'A';
}else if (n == 2){
temp[n] = f + '6';
}else if (n == 3){
temp[n] = f + '2';
}else if(n == 4){
temp[n] = f + 'C';
}else if(n == 5){
temp[n] = f + '1';
}else if(n == 6){
temp[n] = f + 'D';
}else if(n == 7){
temp[n] = f + '6';
}else if(n == 8){
temp[n] = f + '8';
}else if(n == 9){
temp[9] = f + 'F';
}else if(n == 10){
temp[10] = f + '1';
}else if(n == 11){
temp[11] = f + 'B';
}else if(n == 12){
temp[12] = f + 'B';
}else if(n == 13){
temp[13] = f + 'C';
}else if(n == 14){
temp[14] = f + 'D';
}else if(n == 15){
temp[15] = f + 'C';
}
} // for loop end here

// new value for f0 to f4
int j;
for (j = 0; j <= 15; j++) {
    f0[j] = (f0[j] ^ temp[j]);
    f1[j] = (f1[j] ^ temp[j]);
    f2[j] = (f2[j] ^ temp[j]);
    f3[j] = (f3[j] ^ temp[j]);
    f4[j] = (f4[j] ^ temp[j]);
    printf("f3[j]:%d\n", f3[j]);
}

// write value in array f0-f4 into f5 array
for(int p = 0; p<=15; p++){
    f5[p] = f0[p];
    f5[16+p] = f1[p];
    f5[32+p] = f2[p];
    f5[48+p] = f3[p];
    f5[64+p] = f4[p];
}

// have to use loop to read all character in array cause might contain null character which %s stop
for (int x = 0; x <= 79; x++) {
    fprintf(fp, "%c", f5[x]);
}
fclose(fp);

// starting from f0 add together with the input. Last one is f4
// add the first half from 0-8
int c;
for(c=0; c <=7; c++){
w[c] = w[c] + f0[c];
}
// add the second half from 8-15
for(c=8; c <=15; c++){
w[c] = w[c] + f1[c];
}
// Repeat the step again by adding the first half again
for(c=0; c <=7; c++){
w[c] = w[c] + f2[c];
}
// Repeat the step again by adding the second half again
for(c=8; c <=15; c++){
w[c] = w[c] + f3[c];
}
// Last step add all
for(c=0; c <=15; c++){
w[c] = w[c] + f4[c];
}

// final round
// w shift follow by key each value
for(c=0; c <=15; c++){
w[c] = w[c] + key[c];
}

// print final encrypted output
printf("Output: %s\n", w);
// print final encrypted output in decimal value
int u = 0;
for (c = 0; c <= 15; c++) {
    printf("Output%d: %d\n", u, w[c]);
    u++;
}
// print encrypted text to a file
FILE* encrypted_file;

encrypted_file = fopen("encrypted_file.txt", "a");
for (int x = 0; x <= 15; x++) {
    fprintf(fp, "%c", w[x]);
}
fclose(fp);
}