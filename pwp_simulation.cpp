#include<iostream>
#include<cstdlib>
#include<string.h>
#include<time.h>

using namespace std;

struct data {
	int id;
	string ip;
	int port;
	int speed;
	int completed;
	bool finished;
	bool seeding;
	int status;	
};

struct peer {
	data info; 
	peer *next;
};
peer *peerList = new peer;

string status[4] = {
	"Unchooked",
	"Chooked",
	"Interested",
	"Uninterested"
};

void gen_peers(int num) {
	peerList->next = NULL;
	peer *temp;
	for(int i=0;i<num;i++) {
		temp = peerList;
		while(temp->next) temp=temp->next;
		temp=temp->next = new peer;
		temp->info.id = i+1;
		temp->info.ip = "11:22:33:44:55";
		temp->info.port = rand() % 10+1;
		temp->info.status = 0;
		temp->info.finished = false;
		temp->info.seeding = false;
		temp->info.completed = 0;
		temp->info.speed = rand() % 4096+1;
		temp->next = NULL;
	}
}

void print_peers() {
	cout << "Peer list: " << endl;
	peer *temp = peerList;
	while(temp->next) { temp=temp->next;
		if(temp->info.status != 1 && !temp->info.finished)
			cout << temp->info.id << "  " << temp->info.ip << "  " << temp->info.port << "  " << status[temp->info.status-1] << "  " << temp->info.speed << "Kb/s" << "  " << temp->info.completed << "/100000" << endl;
		/* 
		cout << "ID: " << temp->id << endl;
		cout << "IP: " << temp->ip << endl;
		cout << "Port " << temp->port << endl;
		cout << "Status: " << status[temp->status-1] << endl; ;*/
	}
}

void sort() {
	peer *temp = peerList;
	peer *temp2 = peerList;
	while(temp->next) { temp=temp->next;
		temp2 = peerList;
		while(temp2->next) { temp2=temp2->next;
			if(temp->info.speed > temp2->info.speed) {
				data pom = temp->info;
				temp->info = temp2->info;
				temp2->info = pom;
			}
		}
	}
}

bool completed(data local) {
	if(local.completed >= 100000) return true;
	else return false;
}

void update_peers() {
	peer *temp = peerList;
	while(temp->next) { temp=temp->next;
		temp->info.completed+=temp->info.speed;	
		if(rand()%2==0) temp->info.speed-=rand()%512+1;
		else temp->info.speed+=rand()%512+1;
		if(temp->info.speed<0) temp->info.speed = 0;
	}
}

void simulate(data local) {
	while(!completed(local)) {
		system("cls");
		update_peers();
		sort();
		local.completed+=peerList->next->info.speed;
		print_peers();	
		cout << "My completed: " << local.completed << "/100000" << endl;
		system("pause");
	}
	cout << "My completed: 100000/100000" << endl;
}

int main() {
	srand(time(NULL));
	int pick, again;
	
	peer *local = new peer;
	local->info.completed = 0;
	
	gen_peers(100);	
	simulate(local->info);

	return 0;
}
