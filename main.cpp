#include<iostream>
#include<cstdlib>
#include<time.h>
#include "queue_array.h"
//#include "queue_pointer.h"
using namespace std;

string imena_m[14] = {"Ivo","Marko","Ilija","Joso", "Roko", "Marian", "Teo","Ilija", "Roko", "Lovor","Marian", "Rikard","Rajko","Petar"};
string imena_z[14] = {"Mara","Ivana","Luca","Marta", "Petra", "Matea", "Martina","Lukrecija", "Livija", "Laura","Mara", "Valentina","Izabela","Marica"};
string prezimena[14] = {"Ivic","Maric","Ilic","Ilic", "Ribar", "Markovic", "Babi","Ribic", "Rokic", "Dujic","Ilic", "Ronic","Elic","Rac"};

int index = 0,deleted=0,added=0;
bool empty = true,insert;
customer array[10001];
customer temp[10001];

string services[5] = {"predaja/preuzimanje posiljke", "placanje racuna", "uplata lutrije", "Western Union", "EvoTV"};
string types[5] = {"VIP klijent", "Invalid", "Trudnica", "Umirovljenik", "Ostali"};

void gen(int num) {
	for(int i=0;i<num;i++) {
		customer newe;
		newe.id = index;
		data info;
		info.ai = rand()%491+10;
		info.bi = rand()%721+80;
		info.ci = rand()%5+1;
		info.di = rand()%5+1;
		
		newe.info = info;
		newe.gender = rand()%2;	
		newe.day = rand()%31+1;
		newe.month = rand()%12+1;
		newe.year = rand()%46+1950;
		
		if(newe.gender) {
			newe.name = imena_m[rand()%14]+" ";
			newe.name+=prezimena[rand()%14];
			do newe.info.ci = rand()%5+1;
			while(newe.info.ci == 3); 
		} else {
			newe.name = imena_z[rand()%14]+" ";
			newe.name+=prezimena[rand()%14];
			
			if(50 > 2014-newe.year) {
				do newe.info.ci = rand()%5+1;
				while(newe.info.ci == 4);  
			}
		}
		
	array[index] = newe;
	index++;
	}
}

void print_info(customer model) {
	cout << model.id << " ------------------------------------" << endl;
	cout << "Ime i prezime: " << model.name << endl;
	cout << "Datum rodenja: " << model.day << "." << model.month << "." << model.year << "." << endl;
	cout << "Spol: ";
	if(model.gender) cout << "Musko" << endl;
	else cout << "Zensko" << endl;
	cout << types[model.info.ci-1] << endl;
	cout << services[model.info.di-1] << endl;
	cout << "ai " << model.info.ai << endl;
	cout << "bi " << model.info.bi << endl;
	cout << endl;
}

void flip(qu *Q) {
	if(isEmptyQ(Q)) return;
	customer model = frontQ(Q);
	deQueueQ(Q);
	flip(Q);
	
	enQueueQ(model, Q);			
}

void order(qu *Q, customer newe) {
	if(isEmptyQ(Q)) return;
	customer model = frontQ(Q);
	deQueueQ(Q);
	order(Q, newe);
	
	if(newe.info.ci < model.info.ci && insert) {
		enQueueQ(newe, Q);
		insert = false;
	}
	enQueueQ(model, Q);	
}

void to_queue(qu *Q, customer *array) {
	int elapsed = 0, exit, enter=0; 
	int i = 0;
	customer current;
	bool in_prog = false;
	while(i<index || in_prog) {
		customer model = array[i];
		
		//ulaz
		if(elapsed==enter+model.info.ai) {
			cout << "###### Klijent " << model.name << " ulazi u postu." << endl;
			cout << "Podatci: " << endl;
			print_info(model);	
			enter=elapsed;	
			
			if(!isEmptyQ(Q)) {
				if(model.info.ci < (frontQ(Q)).info.ci) cout << "###### Klijent s prioritetom! Sluzbenik mu govori da je sljedeci na redu." << endl;
					insert = true;					
					order(Q, model);			
					flip(Q);	
				//} else enQueueQ(model,Q);
			} else enQueueQ(model,Q);
			i++;	
		}
		
		if(!isEmptyQ(Q) || in_prog) {
			if(!in_prog) {
				in_prog = true;
				current = frontQ(Q);
				cout << "###### Klijent " << current.name << " je na redu." << endl;
				deQueueQ(Q);	
				exit = elapsed+current.info.bi;		
			}

			//izlaz
			if(elapsed==exit && in_prog) {
				in_prog = false; 
				cout << "###### Klijent " << current.name << " izlazi iz poste." << endl;	
			} 	
		}

		
	elapsed++;
	}
}

void print(qu *Q) {
	if(isEmptyQ(Q)) return;	
	customer model = frontQ(Q);
	print_info(model);
	deQueueQ(Q);
	print(Q);
	
	enQueueQ(model, Q);	
}

void printJarac(qu *Q) {
	if(isEmptyQ(Q)) return;
	customer model = frontQ(Q);
	if((model.month == 12 && model.day > 21) || (model.month == 1 && model.day < 21))
		if(2014-model.year < 40 && model.info.di == 3) {
			empty = false;
			print_info(model);	
		}
	deQueueQ(Q);
	printJarac(Q);
	
	enQueueQ(model, Q);
}

void deleteTrudnice(qu *Q) {
	if(isEmptyQ(Q)) return;
	customer model = frontQ(Q);
	deQueueQ(Q);
	deleteTrudnice(Q);
	
	if(model.info.ci == 3) {
		if(model.info.di != 5) enQueueQ(model, Q);	
		else deleted++;
	} else enQueueQ(model, Q);	
}

bool return_model(customer model) {
	for(int i=0;i<index;i++) 
		if(temp[i].id == model.id) return 0;

	return 1;
}

void fastUmirovljenici(qu *Q, qu *F) {
	if(isEmptyQ(Q)) return;	
	customer model = frontQ(Q);
	deQueueQ(Q);
	fastUmirovljenici(Q,F);	

	if(model.info.ci == 4) {
		enQueueQ(model,F);
	}
	enQueueQ(model,Q);
}

void fastTop(qu *Q, int di, qu *F) {
	if(isEmptyQ(Q)) return;	
	customer model = frontQ(Q);
	deQueueQ(Q);
	fastTop(Q,di,F);	
	
	if(model.info.di == di && added<2 && di != 4) {
		added++;
		enQueueQ(model,F);	
	}
	enQueueQ(model,Q);
}

void createQ(qu *Q, customer *array) {
	for(int i=0;i<index;i++) {
		enQueueQ(array[i], Q);
	}
}

void sort(customer *array) {
	for(int i=0;i<index;i++) {
		for(int j=i;j<index;j++)
			if(array[i].info.ci < array[j].info.ci) {
				customer temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}		
	}	
}

void sort2(customer *array) {
	for(int i=0;i<index;i++) {
		for(int j=i;j<index;j++)
			if(array[i].info.di > array[j].info.di) {
				customer temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}		
	}	
}

customer *fast;
customer *to_array(qu *Q) {
	fast = new customer[10001];
	
	while(!isEmptyQ(Q)) {
		fast[index] = frontQ(Q);
		deQueueQ(Q);
	index++;
	}
	
	sort2(fast);
	initQ(Q);
	
	return fast;
}

int main() {
	//init rand seed
	srand(time(NULL));
	int pick, again,num,quit;
	customer *temp;
	//defaults();
	cout << "Ucitano je 100 testnih klijenata.." << endl;
	cout << "Koliko dodatnih klijenata zelite generirati? "; cin >> num;
	gen(num+100);
	cout << "Generirano!!" << endl;
	system("pause");
	
	qu *Q = new qu;
	qu *F = new qu;
	initQ(Q);
	
	do{
		again = 1;
		system("cls");
		cout << "1. Simulacija ulazaka i izlazaka" << endl;
		cout << "2. Ispisi klijente znaka jarac, mlade od 40" << endl;
		cout << "3. Izbaci trudnice koje cekaju za EvoTV" << endl;
		cout << "4. Stvaranje brze linije i izvodenje simulacije" << endl;
		cout << "5. Ipis pojedinih saltera" << endl;
		cout << "9. Izlaz" << endl;
		cout << "Odaberite opciju: ";
		cin >> pick;
		cout << endl;
		
		switch(pick) {
			case 0:
				print(Q); 
				flip(Q);
			break;
			case 1:
				initQ(Q);
				to_queue(Q, array);
				cout << endl << "Simulacija je odradena.. Iznad se nalazi povijest ulazaka i izlazaka." << endl;
			break;
			case 2:
				temp = array;
				sort(temp);
				initQ(Q);
				createQ(Q, temp);
				cout << "Osobe znaka jarac mlade od 40 godina s uplatama lutrije: " << endl;
				printJarac(Q);
				flip(Q);
				if(empty) cout << "Danas nema takvih klijenata u redu." << endl;
			break;
			case 3:		
				temp = array;
				sort(temp);
				initQ(Q);
				createQ(Q,temp);
				cout << "Sluzbenici u posti su jakoo spori danas..." << endl;
				cout << "Neke trudnice gube strpljenje i odlaze, izgleda da ima bebe ipak nece gledati crtice na EvoTV..." << endl;
				system("pause");
				cout << "Novo stanje reda: " << endl;
				deleted = 0;
				deleteTrudnice(Q);
				flip(Q);
				print(Q);
				flip(Q);
				cout << "Izaslo je " << deleted << " trudnica." << endl;
			break;
			case 4:
				cout << "Penzici i najprioritetniji klijenti sa svih saltera su sada brzom redu" << endl;
				cout << "Sada ce se izvrsiti simulacija obrade brzog reda.." << endl;
				system("pause");
				cout << "Stanje brzog reda: " << endl;
				temp = array;
				initQ(Q);
				initQ(F);
				createQ(Q,temp);
				fastUmirovljenici(Q,F);
				flip(Q);
				for(int i=0;i<5;i++) {
					added = 0;
					fastTop(Q,i+1,F);
					flip(Q);
				}
				
				index = 0;
				to_queue(F, to_array(F));
				//flip(F);
				//print(F);
				
			break;
			case 5:
				do{
					system("cls");
					cout << "Odaberite salter za koji zelite ispisati klijente." << endl;
					cout << "1. Predaja/preuzimanje posiljke" << endl;
					cout << "2. Placanje racuna" << endl;
					cout << "3. Uplata lutrije" << endl;
					cout << "4. Western union" << endl;
					cout << "5. EvoTV" << endl;
					cout << "6. Brzi salter" << endl;
					cout << "9. Povratak u glavni izbornik" << endl;
					cout << "Odaberite opciju: ";
					cin >> pick;
					cout << endl;
					
					switch(pick) {	
						case 6:
							cout << "Penzici i najprioritetniji klijenti sa svih saltera su sada brzom redu" << endl;
							system("pause");
							cout << "Stanje brzog reda: " << endl;
							temp = array;
							initQ(Q);
							initQ(F);
							createQ(Q,temp);
							fastUmirovljenici(Q,F);
							flip(Q);
							for(int i=0;i<5;i++) {
								added = 0;
								fastTop(Q,i+1,F);
								flip(Q);
							}
							
							index = 0;
							createQ(F, to_array(F));
							flip(F);
							print(F); 
						break;
						case 9: quit = 1; break;
						default:
							cout << "Status na salteru za " << services[pick-1] << " je:" << endl;
							temp = array;
							sort(temp);
							
							for(int i=num+50;i>=0+50;i--) {
								customer model = temp[i];
								if(model.info.di == pick) print_info(model);
							}
								
						break;
					}
				if(quit != 1) system("pause");
				} while(quit != 1);
			break;
			case 9: again = 0; break;
			default: cout << "Ne postoji ta opcija" << endl;
		}
		
	cout << endl; 
	if(again != 0) system("pause");
	} while(again!=0);

	return 0;
}
