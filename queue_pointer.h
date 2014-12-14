#include<iostream>
using namespace std;

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

struct element {
	customer value;
	element *next;
};

struct qu {
	element *front,*rear;
};

void initQ(qu *Q) {
	Q->front = new element;
	Q->rear = Q->front;
}

bool isEmptyQ(qu *Q) {
	if(Q->front == Q->rear) return 1;
	else return 0;
}

customer frontQ(qu *Q) {
	if(!isEmptyQ(Q)) 
		return Q->front->next->value;
}

void enQueueQ(customer v, qu *Q) {
	Q->rear->next =new element;
	Q->rear=Q->rear->next;
	Q->rear->next=NULL;
	Q->rear->value=v;
}

void deQueueQ(qu *Q) {
	element *pom = Q->front;
	Q->front = pom->next;
	delete pom;
}
