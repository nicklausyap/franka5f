// Date created: 30 March 2023
// franka5f_dec.cpp
// This source file is part of the franka5f open source project
// Copyright (c) 2023 nicklaus yap ken yik
// franka5f decryption process

#include <cstdio>
#include <cstdlib>

int main()
{
    // w would be the ciphertext needed to be decrypted to be
    unsigned char enc[19];
    FILE* fp_read;
    fp_read = fopen("encrypted_file.txt", "r");
    for (int a = 0; a <= 15; a++) {
        enc[a] = fgetc(fp_read);
    }
    // close the file after reading into enc array
    fclose(fp_read);
    for (int j = 0; j <= 15; j++) {
        printf("%d\n", enc[j]);
    }
    // example only
    unsigned char w[17] = "ABCDABCD12345678";
    unsigned char key[17] = "happyhappyhappy0";
    unsigned char inp[81];
    inp[80] = '\0';
    FILE *fp;

    fp = fopen("f0_f4.f5f", "rb");
    
    for(int i=0;i<=79;i++){
       inp[i] = fgetc(fp);
        printf("inp[%d]:%d\n", i, inp[i]);
    }

    // first step is to unshift using the key
    for(int c=0; c <16; c++){
    enc[c] = enc[c] - key[c];
    }

    int b=0;
    // minus all first
    for(int c=64; c <=79; c++){
    enc[b] = enc[b] - inp[c];
    b++;
    }
    int d=8;
    // minus second half. start from 56 cause second half
    for(int c=56; c <=63; c++){
    enc[d] = enc[d] - inp[c];
    d++;
    }
    b=0; // no need initialize variable b again. Just set value to 0
    // minus first half
    for(int c=32; c <=39; c++){
    enc[b] = enc[b] - inp[c];
    b++;
    }
    d=8; // no need initialize variable d again. Just set value to 8
    // minus second half again
    for(int c=24; c <=31; c++){
    enc[d] = enc[d] - inp[c];
    d++;
    }
    b=0; // no need initialize variable b again. Just set value to 0
    // minus first half again
    for(int c=0; c <=7; c++){
    enc[b] = enc[b] - inp[c];
    b++;
    }

    // final step
    for(int i = 15; i >= 0; i--) {
    enc[i] = (enc[i] ^ key[i]);
    }
    // put null terminator for string printing
    enc[16]='\0';
    printf("decryted text: %s\n",enc);
    FILE* decrypt_fp;

    decrypt_fp = fopen("decrypted.txt", "w");
    fprintf(decrypt_fp, "%s", enc);
    fclose(decrypt_fp);
}