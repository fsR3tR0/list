#include "include.h"

typedef struct lista{
	u8 data_8;
	//u16 data_16
	//float data_f
	struct lista *next;
}lista;

typedef struct lista_komplex{
//	u8 data_Re;
//	u8 data_Im;
	float data_Re;
	float data_Im;
	float degre;
	float absvalue;
	struct lista_komplex *next;
}lista_komplex;

lista *beszur_elore(lista *l, u8 data);
lista_komplex *beszur_komplex_elore(lista_komplex *l_k, float data_1, float data_2, float d, float ab);
lista_komplex *fk_beolvas(FILE *fp, lista_komplex *head);
void kiir(lista *l);
void kiir_komplex(lista_komplex *l_k);
void lista_free(lista *l);
void lista_k_free(lista_komplex *lk);
void hossz_sima(lista *l, u16 *lenght);
void hossz_komplex(lista_komplex *lk);

int main(int argc, uch *argv[])
{
	lista *l0 = NULL;
	lista_komplex *lk = NULL;
	lista_komplex *p_file;
	float in_Re = -1.0, in_Im = -1.0;
	float dgr = 0.0, absv = 0.0;
	u8 flag_im = 0, flag_re = 0;
	float sqr = 0.0, tmp = 0.0;
	float qwe[2] = {};
	u16 mennyi = 0;
	FILE *f1;

	f1 = fopen("numbers.txt","r");
	if(f1 == NULL){
		printf("Sikertelen nyitas");
		return 1;
	}else{
		printf("Na mehet\n");
	}

	while(fscanf(f1,"%f %f", &qwe[0], &qwe[1]) == 2){
		printf("{%.2f:%.2f}", qwe[0], qwe[1]);
	}
	printf("\n");

	p_file = fk_beolvas(f1, p_file);
//	kiir_komplex(p_file);

	for(u8 i = 1; i < 11; i++){
		l0 = beszur_elore(l0,i);
	}
	printf("Feltoltes kesz\n");

	hossz_sima(l0, &mennyi);
	printf("%d\n", mennyi);
/*
	printf("Irja be miket kivan bevinni\n");
	while(in_Re != 0 && in_Im != 0){
		scanf("%d\n",&in_Re);
		scanf("%d\n",&in_Im);
		lk = beszur_komplex_elore(lk,in_Re,in_Im);
		printf("%d %d\n",in_Re,in_Im);
	}*/
	for(float i = 100.0; i > -100.0; i = i-9.6){
		float k = i+2.3;
		tmp = i/k;
		dgr = atan(tmp)*180/PI;
	//	printf("%f %f ",tmp,dgr);
		sqr = pow((double)i,2)+pow((double)k,2);
	//	printf("%f\n", tmp);
		absv = sqrt((double)sqr);
		lk = beszur_komplex_elore(lk,i,i+2.3,dgr,absv);
	}

	kiir(l0);
	kiir_komplex(lk);
/*
	while(in_Re != 0.0 || in_Im != 0.0){
		flag_re = scanf("%f", &in_Re);
		flag_im = scanf("%f", &in_Im);
		if(flag_im != 1 || flag_re != 1){
			printf("Hibas bevitel!\n");
			in_Re = 0.0;
			in_Im = 0.0;
		}else{
			if(in_Re == 0.0 || in_Im == 0.0){
				printf("Bevitel vege.\n");
			}else{
				printf("%.3f %.3f\n", in_Re, in_Im);
			}
		}
	}
*/
	lista_k_free(lk);
	lista_free(l0);
	fclose(f1);

	return 0;
}

void hossz_sima(lista *l, u16 *lenght){
	lista *p = l;
	u16 db = 0;
	while(p != NULL){
		db++;
		p = p->next;
	}
	*lenght = db;
	printf("Lista(sima) hossza: %d\n", db);
}

lista_komplex *fk_beolvas(FILE *fp, lista_komplex *head){
	lista_komplex vissza;

	while(fscanf(fp,"%f %f\n", &vissza.data_Re, &vissza.data_Im) == 2){
		lista_komplex *a = (lista_komplex*)malloc(sizeof(lista_komplex));
		a->data_Re = vissza.data_Re;
		a->data_Im = vissza.data_Im;
		lista_komplex *p = head;
		head = a;
		a->next = p;
	}
	return head;
}

lista *beszur_elore(lista *l, u8 data){
	lista *uj = (lista*)malloc(sizeof(lista));
	uj -> data_8 = data;
	uj -> next = l;
	return uj;
}

lista_komplex *beszur_komplex_elore(lista_komplex *l_k, float data_1, float data_2, float d, float ab){
	lista_komplex *uj = (lista_komplex*)malloc(sizeof(lista_komplex));
	uj -> data_Re = data_1;
	uj -> data_Im = data_2;
	uj -> degre = d;
	uj -> absvalue = ab;
	uj -> next = l_k;
	return uj;
}

void kiir(lista *l){
	lista *p = NULL;
	u8  db = 0;
	/*for(p = l; p != NULL; p = p->next){
		printf("%d, ",p->data);
	}*/
	p = l;
	while( p != NULL){
		if( p->next == NULL){
			printf("%d\n",p->data_8);
			p = p->next;
		}else{
			printf("%d, ",p->data_8);
			p = p->next;
			db++;
			if(db % 5 == 0)
				printf("\n");
		}
	}
	printf("Kiiras befejezodott(egesz).\n");
	printf("===========================\n");
}

void kiir_komplex(lista_komplex *l_k){
	lista_komplex *p = NULL;
	u8 db = 0;

	p = l_k;
	while( p != NULL){
		if( p-> next == NULL){
			if(p->data_Im < 0.0){
				printf("%.2f-j%.2f: %.2f*e^%.2f°\n",p->data_Re,(p->data_Im)*-1.0,p->absvalue, p->degre);
			//	printf("%.2f-j%.2f\n",p->data_Re,abs(p->data_Im));
				p = p->next;
			}else{
				printf("%.2f+j%.2f: %.2f*e^%.2f°\n",p->data_Re,(p->data_Im),p->absvalue, p->degre);
			//	printf("%.2f+j%.2f\n",p->data_Re,p->data_Im);
				p = p->next;
			}
		}else{
			if(p->data_Im < 0.0){
				printf("%.2f-j%.2f: %.2f*e^%.2f°|",p->data_Re,(p->data_Im)*-1.0,p->absvalue, p->degre);
				p = p->next;
				db++;
				if(db%2 == 0)
					printf("\n");
			}else{
				printf("%.2f+j%.2f: %.2f*e^%.2f°|",p->data_Re,(p->data_Im),p->absvalue, p->degre);
				p = p->next;
				db++;
				if(db%2 == 0)
					printf("\n");
			}
		}
	}
	printf("Kiiras befejezodott(komplex).\n");
	printf("=============================\n");
}

void lista_free(lista *l){
	lista *p = l;
	while( p != NULL){
		//kell mert ha csak siman free lenne elveszne a kovetkezo elem
		lista *tmp = p->next;
		free(p);
		p = tmp;
	}
	printf("Felszabaditva(sima).\n");
}


void lista_k_free(lista_komplex *lk){
	lista_komplex *p = lk;
	while( p != NULL){
		//kell mert ha csak siman free lenne elveszne a kovetkezo elem
		lista_komplex *tmp = p->next;
		free(p);
		p = tmp;
	}
	printf("Felszabaditva(komplex).\n");
}








