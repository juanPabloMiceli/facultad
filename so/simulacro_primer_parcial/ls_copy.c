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
    printf("Inode number %ld\n", dirInfo->d_ino);
    printf("Not an offset %ld\n", dirInfo->d_off);
    printf("Record length %d\n", dirInfo->d_reclen);
    printf("File type %d\n", dirInfo->d_type);
    printf("dname: %s\n", dirInfo->d_name);
    dirInfo = readdir(dir);
    }

    printf("contador: %d\n", counter+1);
    
    
    return 0;
}