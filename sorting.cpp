// sorting_project.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	NUMOFNUMBERS	50000		// 5만개, 7.5만개, 10만개, 12.5만개, ..., 50만개까지 증가시키며 시간 측정할 것
#define NUMMAX 500000
// selection sort를 위한 함수들
void selectionSort(long A[], long n);
long theLargest(long A[], long last);
void mergeSort(long A[], long q, long r, int t);
void merge(long A[], long p, long q, long r, int t);

int main(int argc, char* argv[])
{
	register long n, i;
	int t, a;
	clock_t before;
	double elapsed_time;
	

	std::cout << "알고리즘입문 2019년 1학기 소팅 프로젝트 시작합니다.\n\n";

	for (t = NUMOFNUMBERS; t <= 500000; t += 25000)
	{
		srand((unsigned)time(NULL));

		long *randNumbers = new long[t];

		before = clock();
		for (i = t - 1; i >= 0; i--) {
			n = rand();
			n += ((i + 1) / RAND_MAX) * RAND_MAX;
			randNumbers[t - 1 - i] = n;
		}
		elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;	// 초 단위의 경과 시간을 측정함.
		fprintf(stdout, "%d 개의 랜덤 넘버 생성에 걸린 시간(초): %10.2f\n\n", t, elapsed_time);
		before = clock();
		mergeSort(randNumbers, 0, t, t);

		elapsed_time = (double)(clock() - before) / CLOCKS_PER_SEC;	// 초 단위의 경과 시간을 측정함.
		fprintf(stdout, "%d 개의 랜덤 넘버를 selection sort 하는 데에 걸린 시간(초): %10.2f\n\n", t, elapsed_time);
	}

	return 0;
}

void selectionSort(long A[], long n)
{
	int last, k, tmp;

	for (last = n - 1; last >= 1; last--) {
		k = theLargest(A, last);	// A[0...last] 중 가장 큰 수 A[k] 찾기
		tmp = A[last];
		A[last] = A[k];
		A[k] = tmp;
	}
}

long theLargest(long A[], long last)
{
	long largest, i;

	largest = 0;
	for (i = 1; i <= last; i++)
		if (A[i] > A[largest])
			largest = i;
	return largest;
}

void mergeSort(long A[], long p, long r, int t) {
	long q;

	if (p < r) {
		q = ceil((p + r) / 2);
		mergeSort(A, p, q, t);
		mergeSort(A, q + 1, r, t);
		merge(A, p, q, r, t);
	}
}

void merge(long A[], long p, long q, long r, int t) {
	long i, j, k, size;
	int a;
	i = p; // 첫번째 배열의 시작 인덱스
	j = q+1; // 두번째 배열의 시작 인덱스
	k = 0; //tmp 배열의 시작 인덱스

	//size = sizeof(A) / sizeof(A[0]);
	long *tmp = new long[t];
	
	while (i <= q && j <= r) { // 두번째 배열 끝에 이를때 까지
		if (A[i] <= A[j]) { // 첫번째 배열의 원소가 두번째 배열 원소보다 작거나 같으면
			tmp[k] = A[i]; //임시배열에 첫번째 배월 원소 추가
			i++;
		}
		else {
			tmp[k++] = A[j++]; //  두번째 배열의 원소가 더 작거나 같으면
			j++;
		}
		k++;
	}
	while (i <= q) { // 왼쪽 부분 배열이 남은 경우
		tmp[k++] = A[i++];
	}
	while (j <= r) {
		tmp[k++] = A[j++];
	}
	i = p;
	k = 1;
	while (i <= r) { //결과 A[p, ..., r]에 저장
		A[i++] = tmp[k++];
	}
	delete[] tmp;
}


