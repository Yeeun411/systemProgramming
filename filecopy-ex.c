#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024 // 버퍼 크기를 1024로 정의

int main() {
    char ubuf[BUFFER_SIZE], fbuf[BUFFER_SIZE]; // 버퍼 크기만큼 ubuf와 fbuf 할당
    int n;
    FILE *fpin, *fpout; // 파일 포인터 선언

    if ((fpin = fopen("file1.dat", "r")) == NULL) {
        // "file1.dat" 파일을 읽기 모드로 열고 파일 스트림 객체 생성
        return 2;
    }
    if ((fpout = fopen("file2.dat", "w")) == NULL) {
        // "file2.dat" 파일을 쓰기 모드로 열고 파일 스트림 객체 생성
        // 해당 파일의 크기를 0으로 만들어 열거나, 파일이 없으면 생성
        return 3;
    }
    if (setvbuf(fpin, ubuf, _IOFBF, BUFFER_SIZE) != 0) {
        // 크기 1024인 full buffering 설정
        perror("setvbuf(fpin)");
        return 4;
    }
    if (setvbuf(fpout, ubuf, _IOFBF, BUFFER_SIZE) != 0) {
        // 크기 1024인 full buffering 설정
        perror("setvbuf(fpout)");
        return 5;
    }
    while ((n = fread(fbuf, sizeof(char), BUFFER_SIZE, fpin)) > 0) {
        // "file1.dat"에 읽을 데이터가 있다면 BUFFER_SIZE만큼 캐릭터를 읽음
        fwrite(fbuf, sizeof(char), n, fpout);
        // 읽은 캐릭터를 "file2.dat" 파일에 씀
    }
    fclose(fpin);  // 파일 닫음
    fclose(fpout); // 파일 닫음

    return 0;
}
