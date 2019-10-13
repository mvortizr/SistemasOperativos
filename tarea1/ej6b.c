#include <unistd.h>

int main(){
 for(int i = 0; i<100000; i++)
  getpid();
 return 1;
}
