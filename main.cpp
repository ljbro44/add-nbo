#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BYTE_SWAP(x) \
  (((x & 0xFF000000) >> 24) | \
   ((x & 0x00FF0000) >> 8 ) | \
   ((x & 0x0000FF00) << 8 ) | \
   ((x & 0x000000FF) << 24))

int main(int argc, char* argv[])
{
  int max_len = sizeof(uint32_t);

  uint8_t buffer1[max_len];
  uint8_t buffer2[max_len];

  FILE* fp1 = fopen(argv[1], "r");
  FILE* fp2 = fopen(argv[2], "r");

  if(fp1 == NULL || fp2 == NULL || argc !=3){
      printf("input error!\n");
      return 1;
    }

  memset(buffer1, 0, sizeof(buffer1));
  memset(buffer2, 0, sizeof(buffer2));

  int cr1 = fread(buffer1, max_len, 1, fp1);
  int cr2 = fread(buffer2, max_len, 1, fp2);

  if(cr1!=1 || cr2!=1){
       printf("read error!\n");
       return 1;
    }

  fclose(fp1);
  fclose(fp2);

  uint32_t* p1 = reinterpret_cast<uint32_t*>(buffer1);
  uint32_t* p2 = reinterpret_cast<uint32_t*>(buffer2);

  *p1 = BYTE_SWAP(*p1);
  *p2 = BYTE_SWAP(*p2);

  printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", *p1, *p1, *p2, *p2, *p1+*p2, *p1+*p2);

  return 0;
}
