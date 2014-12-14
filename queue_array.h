#include<iostream>
#include<string.h>
using namespace std;

typedef int element;

struct data {
	int ai;
	int bi;
	int ci;
	int di;
};

struct customer {
	int id;
	string name;
	int day;
	int month;
	int year;
	data info;
	bool gender;
};

struct qu {
	customer values[10001];
	element rear,front;
};

int addOne(int n) {
	return((n+1)%10001);
}

void initQ(qu *Q) {
	Q->front = 0;
	Q->rear = 10000;	
}

bool isEmptyQ(qu *Q) {
	if(addOne(Q->rear)==Q->front) return 1;
	else return 0;
}

customer frontQ(qu *Q) {
	if(!isEmptyQ(Q)) return Q->values[Q->front];
}

void enQueueQ(customer v, qu *Q) {
	Q->rear = addOne(Q->rear);
	Q->values[Q->rear] = v;
}

void deQueueQ(qu *Q) {
	Q->front = addOne(Q->front);
}
