#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

int main(){
    DIR *dir = opendir("./");
    int counter = 0;

    struct dirent *dirInfo = readdir(dir);
    while(dirInfo != NULL){
    counter++;
    dirInfo = readdir(dir);
    }

    printf("%d\n", counter+1);
    
    
    return 0;
}