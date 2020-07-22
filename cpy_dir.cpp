#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char*argv[]){
	int i = argc;
	printf("ARGC : %d\n", argc);
	//인자의 갯수로, 이동해야할 디렉터리값 : argv[i-1]

	if( argc<5 ){
		printf("Input more than 3files and directory name\nUsage : %s <filename1> <filename2> <filename3> ... <directory name>\n", argv[0]);
		return 0;
	}

	FILE *fd, *dest;
	char buf[257];
	int len;

	for( int j=1; j<i-1; j++ ){
		fd = fopen(argv[j], "r");
		if(chdir(argv[i-1]) == -1){
			perror("chdir failed");
			exit(1);
		}	
		dest = fopen(argv[j], "w");

		while( len = fread(buf, 1, 256, fd) ){
			buf[len] = '\0';
			fwrite(buf, 1, len, dest);
			printf("Length : %d\n", len);
			printf("%s\n", buf);
		}
		chdir("..");
		fflush(dest);
		fflush(fd);
	}
	fclose(dest);
	fclose(fd);

	return 0;
}
