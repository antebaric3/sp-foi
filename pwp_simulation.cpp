#include<iostream>
#include<cstdlib>
#include<string.h>
#include<time.h>

using namespace std;

struct data {
	int id;
	int ip[5];
	int port;
	int speed;
	int completed;
	bool finished;
	bool seeding;
	int status;	
};

struct peer {
	data info; 
	bool cons[5];
	peer *next;
};
peer *peerList = new peer;

string status[4] = {
	"Unchooked",
	"Chooked",
};

void resolve_cons(data local) {
	peer *temp = peerList;
	float best = 0;
	while(temp->next) { temp=temp->next;
		for(int i=0;i<5;i++) {
			temp->cons[i] = rand()%2;
			if(temp->cons[i]) temp->info.status = 0;
			else temp->info.status = 1;
		}
	}	
}

float get_best_peer(data local) {
	peer *temp = peerList;
	float best = 0;
	while(temp->next) { temp=temp->next;
		if(best<temp->info.speed && temp->info.status != 1 && temp->info.completed > local.completed) 
			best = temp->info.speed;
	}
	
	return best;
}

void print_ip(data model) {
	bool first = true;
	for(int i=0;i<5;i++) {
		if(!first) cout << ":";
		else first = false;
		cout << model.ip[i];
	}
}

void gen_peers(int num) {
	peerList->next = NULL;
	peer *temp;
	for(int i=0;i<num;i++) {
		temp = peerList;
		while(temp->next) temp=temp->next;
		temp=temp->next = new peer;
		temp->info.id = i+1;
		for(int i=0;i<5;i++) {
			temp->info.ip[i] = rand()%254+1;
		}
		temp->info.port = rand() % 10+1;
		temp->info.status = 0;
		temp->info.finished = false;
		temp->info.seeding = false;
		temp->info.completed = rand() % 100000;
		temp->info.speed = rand() % 1024+1;
		temp->next = NULL;
	}
}

void print_peers() {
	cout << "Peer list: " << endl;
	cout << "---------------------------------------------------------------" << endl;
	peer *temp = peerList;
	while(temp->next) { temp=temp->next;
		if(!temp->info.finished)
			cout << temp->info.id << "  ";
			print_ip(temp->info);
			cout << "  " << temp->info.port << "  " << status[temp->info.status] << "  " << temp->info.speed << "Kb/s" << "  " << temp->info.completed << "/100000" << endl;
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

void update_peers(data local) {
	resolve_cons(local);
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
		update_peers(local);
		sort();
		local.completed+=get_best_peer(local);
		print_peers();	
		if(local.completed<100000) cout << "My completed: " << local.completed << "/100000" << endl;
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
