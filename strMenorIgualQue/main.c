#include "../libs/my_string.h"

int main(int argc, char *argv[]){
  if(argc != 3){ printf("tente de novo\n"); return 0; }

  printf("%s <= %s ? %d \n",
         argv[1], argv[2], strMenorIgualQue(argv[1],argv[2]));
  printf("%s <= %s ? %d \n",
         argv[2], argv[1], strMenorIgualQue(argv[2],argv[1]));

  return 0;
}