#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

struct clash_event{
	char name[31];
	long long min_member;
	long long min_non_member;
	char hashtag_member[6];
	char hashtag_non_member[6];
};
struct clash_event min_contri[6];

struct node{
	char grow_id[31];
	char status[3];
	long long point;
	struct node *next;
};
//main pointers
struct node *head[11] = {NULL, NULL, NULL, NULL, NULL};
struct node *tail[11] = {NULL, NULL, NULL, NULL, NULL};
/*note:
list #1 > partisipan & leaderboard
list #2 > list depo
list #3 > list ge
list #4 > list promote lama
list #5 > list demote lama
list #6 > member yang dikick
list #7 > list promote baru
list #8 > list demote baru
list #9 > member yang deponya diambil
list #10 > member yang dipromote
list #11 > member yang didemote
*/

//global variables
int member_count = 0;
int clash_type;
int total_GM = 0;
int total_GE = 0;

//function lists
void show_menu();
void generate_clash_data();
int clash_select();
struct node *create_new_node(char[], char[], long long);
void insert_list(struct node*, int);
void delete_node(char[], int);
struct node *search(char[], int);
void show_list(int);
int retrieve_clash_data();
void input_list(int);
void process_clash_data();
void look_for_someone(char[]);
int generate_discord_leaderboard(char[], int);
long long exponent(long long, int);
void number_to_string(long long, FILE*);

//codes
int main(){
	int res, inp_guild_rank, fp_check;
	char sel[3];
	char inp_clash_date[14];
	
	//petunjuk penggunaan aplikasi & persiapan awal
	printf("Luckys Guild Clash Apps Version 1.4 created by: Vannes Theo S. aka 'Meowlynna', 22/09/2022\n\n");
	printf("Selamat datang di Luckys Guild Clash Apps. Harap memperhatikan beberapa petunjuk berikut sebelum menggunakan aplikasi:\n");
	printf("> Harap memasukkan input sesuai yang diminta oleh aplikasi dan tekan enter setelah selesai memasukkan input.\n");
	printf("> Aplikasi ini bersifat 'case sensitive' di mana Grow ID dari member-member yang diinput harus sama persis dengan yang diinput di awal saat memasukkan Grow ID member-member secara manual atau pun menyalin dari file contri_data.txt.\n");
	printf("---------------------------------------\n\n");

	generate_clash_data();
	
	do{
		printf("Masukkan tanggal Clash (format: tanggal_mulai-tanggal_selesai/bulan/tahun >> contoh: 01-04/01/2022):\n");
		scanf("%[^\n]", inp_clash_date); getchar();
		printf("\n");
		if(strlen(inp_clash_date) < 13){
			printf("<<Harap memasukkan tanggal sesuai format tanggal yang telah diberikan.>>\n\n");
		}
	} while(strlen(inp_clash_date) < 13);
	
	
	do{
		res = clash_select();
		if(res == 6){
			printf("\n<<Tidak ada Clash wajib dengan nama tersebut.>>\n\n");
		}
	} while(res == 6);

	printf("Poin minimum member   : %s %lld\n", min_contri[clash_type].hashtag_member, min_contri[clash_type].min_member);
	printf("Poin minimum GE/GC/GL : %s %lld\n\n", min_contri[clash_type].hashtag_non_member, min_contri[clash_type].min_non_member);
	
	printf("Masukkan Guild Rank:\n");
	scanf("%d", &inp_guild_rank); getchar();
	printf("\n");
	
	input_list(1); 	//input clash participants
	input_list(2);	//input members who have given depo 30 WL
	input_list(4);	//input members in previous promote list
	input_list(5);	//input members in previous demote list

	//process clash data
	process_clash_data();
	
	//menu utama
	while(1){
		show_menu();
		scanf("%s", sel); getchar();
		printf("\n");
		
		if(strcmp(sel, "1") == 0){
			printf("Clash Leaderboard\n");
			printf("---------------------------------------\n");
			show_list(1);
		}
		
		else if(strcmp(sel, "2") == 0){
			printf("List Depo Member\n");
			printf("---------------------------------------\n");
			show_list(2);
		}
		
		else if(strcmp(sel, "3") == 0){
			printf("List GE Promote di Clash Sebelumnya\n");
			printf("---------------------------------------\n");
			show_list(4);
		}
		
		else if(strcmp(sel, "4") == 0){
			printf("List GE Demote di Clash sebelumnya\n");
			printf("---------------------------------------\n");
			show_list(5);
		}
		
		else if(strcmp(sel, "5") == 0){
			printf("Member-Member yang akan Dikick\n");
			printf("---------------------------------------\n");
			show_list(6);
		}
		
		else if(strcmp(sel, "6") == 0){
			printf("Member-Member yang Depo-nya akan Diambil\n");
			printf("---------------------------------------\n");
			show_list(9);
		}
		
		else if(strcmp(sel, "7") == 0){
			printf("List GE Promote Baru\n");
			printf("---------------------------------------\n");
			show_list(7);
		}
		
		else if(strcmp(sel, "8") == 0){
			printf("List GE Demote Baru\n");
			printf("---------------------------------------\n");
			show_list(8);
		}
		
		else if(strcmp(sel, "9") == 0){
			printf("List Member yang akan Di-promote ke GE\n");
			printf("---------------------------------------\n");
			show_list(10);
		}
		
		else if(strcmp(sel, "10") == 0){
			printf("List GE yang akan Di-demote dari GE\n");
			printf("---------------------------------------\n");
			show_list(11);
		}
		
		else if(strcmp(sel, "11") == 0){
			fp_check = generate_discord_leaderboard(inp_clash_date, inp_guild_rank);
			if(fp_check == 1){
				printf("<<Teks Clash Leaderboard untuk discord berhasil dibuat.>>\n\n");
			} else if(fp_check == 0){
				printf("<<Terjadi kesalahan.>>\n\n");
			}
		}
		
		else if(strcmp(sel, "x") == 0){
			printf("Terimakasih dan sampai jumpa ^^ (Masukkan satu karakter lalu tekan enter untuk menutup)\n");
			getchar();
			return 0;
		}
		
		else {
			printf("<<Harap memasukkan hanya angka pilihan yang ada di menu!>>\n\n");
		}
	}
}

void show_menu(){
	printf("1. Lihat Leaderboard\n");
	printf("2. Cek member yang depo 30 WL\n");
	printf("3. Cek GE promote list lama\n");
	printf("4. Cek GE demote list lama\n");
	printf("5. Cek member yang dikick\n");
	printf("6. Cek member yang depo-nya diambil\n");
	printf("7. Cek GE promote list baru\n");
	printf("8. Cek GE demote list baru\n");
	printf("9. Cek member yang di-promote ke GE\n");
	printf("10. Cek GE yang di-demote ke member\n");
	printf("11. Buat Clash Leaderboard untuk Discord\n");
	printf("Masukkan 'x' lalu tekan enter untuk mengakhiri\n");
	printf("---------------------------------------\n");
	printf("Pilihan: ");
}

void generate_clash_data(){
	strcpy(min_contri[0].name, "Block Bashers");
	min_contri[0].min_member = 828000;
	min_contri[0].min_non_member = 1242000;
	strcpy(min_contri[0].hashtag_member, "[#15]");
	strcpy(min_contri[0].hashtag_non_member, "");

	strcpy(min_contri[1].name, "Block Builders");
	min_contri[1].min_member = 304100;
	min_contri[1].min_non_member = 938200;
	strcpy(min_contri[1].hashtag_member, "[#15]");
	strcpy(min_contri[1].hashtag_non_member, "[#20]");

	strcpy(min_contri[2].name, "Harvest Heroes");
	min_contri[2].min_member = 304100;
	min_contri[2].min_non_member = 938200;
	strcpy(min_contri[2].hashtag_member, "[#15]");
	strcpy(min_contri[2].hashtag_non_member, "[#20]");
	
	strcpy(min_contri[3].name, "Speedy Splicers");
	min_contri[3].min_member = 142400;
	min_contri[3].min_non_member = 304100;
	strcpy(min_contri[3].hashtag_member, "[#12]");
	strcpy(min_contri[3].hashtag_non_member, "[#15]");

	strcpy(min_contri[4].name, "Fishing Fanatics");
	min_contri[4].min_member = 1520500;
	min_contri[4].min_non_member = 3235000;
	strcpy(min_contri[4].hashtag_member, "[#15]");
	strcpy(min_contri[4].hashtag_non_member, "[#18]");

	strcpy(min_contri[5].name, "Cooking Conquerors");
	min_contri[5].min_member = 611000;
	min_contri[5].min_non_member = 1300000;
	strcpy(min_contri[5].hashtag_member, "[#15]");
	strcpy(min_contri[5].hashtag_non_member, "[#20]");
}

int clash_select(){
	char inp_clash_name[31];
	
	printf("Masukkan nama Clash Event yang sedang berlangsung:\n");
	scanf("%[^\n]", inp_clash_name); getchar();
	
	if(strcmp(inp_clash_name, "Block Bashers") == 0){
		clash_type = 0;
	} else if(strcmp(inp_clash_name, "Block Builders") == 0){
		clash_type = 1;
	} else if(strcmp(inp_clash_name, "Harvest Heroes") == 0){
		clash_type = 2;
	} else if(strcmp(inp_clash_name, "Speedy Splicers") == 0){
		clash_type = 3;
	} else if(strcmp(inp_clash_name, "Fishing Fanatics") == 0){
		clash_type = 4;
	} else if(strcmp(inp_clash_name, "Cooking Conquerors") == 0){
		clash_type = 5;
	} else {
		clash_type = 6;
	}
	
	return clash_type;
}

struct node *create_new_node(char inp_grow_id[31], char inp_status[3], long long inp_point){
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	strcpy(new_node->grow_id, inp_grow_id);
	strcpy(new_node->status, inp_status);
	new_node->point = inp_point;
	new_node->next = NULL;
	
	return new_node;
}

void insert_list(struct node *new_node, int code){
	struct node *curr = NULL;
	struct node *curr2 = NULL;
	
	code--;
	
	if(code + 1 == 1){
		if(head[code] == NULL && tail[code] == NULL){
			head[code] = tail[code] = new_node;
		} else if(head[code] == tail[code]){
			if(new_node->point > head[code]->point){
				new_node->next = head[code];
				head[code] = new_node;
			} else {
				tail[code]->next = new_node;
				tail[code] = new_node;
			}
		} else if(head[code]->next == tail[code]){
			if(new_node->point >= head[code]->point){
				new_node->next = head[code];
				head[code] = new_node;
			} else if(new_node->point <= tail[code]->point){
				tail[code]->next = new_node;
				tail[code] = new_node;
			} else {
				head[code]->next = new_node;
				new_node->next = tail[code];
			}
		} else {
			if(new_node->point >= head[code]->point){
				new_node->next = head[code];
				head[code] = new_node;
			} else if(new_node->point <= tail[code]->point){
				tail[code]->next = new_node;
				tail[code] = new_node;
			} else {
				curr = head[code];
				curr2 = head[code]->next;
				while(new_node->point <= curr2->point){
					curr = curr->next;
					curr2 = curr2->next;
				}
				curr->next = new_node;
				new_node->next = curr2;
			}
		}
	}
	
	else {
		if(head[code] == NULL && tail[code] == NULL){
			head[code] = tail[code] = new_node;
		} else {
			tail[code]->next = new_node;
			tail[code] = new_node;
		}
	}
}

void delete_node(char inp_name[31], int code){
	struct node *del = NULL;
	struct node *curr = NULL;
	struct node *curr2 = NULL;
	code--;
	
	if(head[code] == NULL && tail[code] == NULL){
		return;
	} else if(head[code] == tail[code]){
		free(head[code]);
		head[code] = tail[code] = NULL;
	} else if(head[code]->next == tail[code]){
		if(strcmp(inp_name, head[code]->grow_id) == 0){
			del = head[code];
			head[code] = tail[code];
			free(del);
		} else {
			del = tail[code];
			tail[code] = head[code];
			free(del);
		}
	} else {
		if(strcmp(inp_name, head[code]->grow_id) == 0){
			del = head[code];
			head[code] = head[code]->next;
			free(del);
		} else if(strcmp(inp_name, tail[code]->grow_id) == 0){
			curr = head[code];
			while(curr != tail[code]){
				curr = curr->next;
			}
			del = tail[code];
			tail[code] = curr;
			free(del);
		} else {
			curr = head[code];
			curr2 = head[code]->next->next;
			while(strcmp(inp_name, curr2->grow_id) != 0){
				curr = curr->next;
				curr2 = curr2->next;
			}
			curr->next = curr2->next;
			free(curr2);
		}
	}
}

struct node *search(char inp_name[31], int code){
	struct node *curr = NULL;
	
	code--;
	curr = head[code];
	
	while(curr != NULL){
		if(strcmp(curr->grow_id, inp_name) == 0){
			return curr;
		}
		curr = curr->next;
	}
	
	return NULL;
}

void show_list(int code){
	int i;
	struct node *curr = NULL;
	
	i = 1;
	code--;
	curr = head[code];
	
	if(curr == NULL){
		printf("<<Tidak ada data.>>\n\n");
		return;
	}
	
	while(curr != NULL){
		if(code + 1 == 1){
			printf("#%d %s(%s): %lld\n", i, curr->grow_id, curr->status, curr->point);
			i++;
		} else {
			printf("~ %s(%s)\n", curr->grow_id, curr->status);
		}
		curr = curr->next;
	}
	printf("\n");
}

int retrieve_clash_data(){
	FILE *fp;
	char sel;
	char inp_grow_id[31];
	char inp_status[3];
	long long inp_point;
	
	struct node *new_member = NULL;
	struct node *new_ge = NULL;
	
	fp = fopen("contri_data.txt", "r");
	if(fp == NULL){
		printf("<<Terjadi kesalahan saat membuka file. Harap letakkan file dan aplikasi di lokasi yang sama.>>\n\n");
		return -1;
	}
	
	printf("Pastikan semua data di dalam file contri_data.txt sudah memenuhi format:\n");
	printf("Grow_ID/Status/Poin >> Contoh: Meowlynna/GL/6900\n");
	printf("Note: Status yang dituliskan haruslah antara GM, GE, GC, atau GL!\n\n");
	
	do{
		printf("Apakah anda sudah yakin penulisan di dalam file tersebut sudah memenuhi ketentuan? Masukkan y jika ya dan x jika tidak:\n");
		printf("Jawaban: "); scanf("%c", &sel); getchar();
		printf("\n");
		
		if(sel == 'y'){
			break;
		} else if(sel == 'x'){
			printf("<<Silahkan perbaiki penulisan dan buka kembali aplikasi ini jika sudah selesai.>>\n\n");
			exit(1);
		} else {
			printf("<<Harap masukkan jawaban sesuai yang diminta.>>\n\n");
		}
	} while(sel != 'y');
	
	while(!feof(fp)){
		fscanf(fp, "%[^/]/%[^/]/%lld\n", inp_grow_id, inp_status, &inp_point);
		new_member = create_new_node(inp_grow_id, inp_status, inp_point);
		insert_list(new_member, 1);
				
		if(strcmp(inp_status, "GE") == 0){
			new_ge = create_new_node(inp_grow_id, inp_status, inp_point);
			insert_list(new_ge, 3);
			total_GE++;
		}
				
		if(strcmp(inp_status, "GM") == 0){
			total_GM++;
		}
		
		member_count++;
	}
	
	printf("<<Data berhasil disalin.>>\n\n");
	fclose(fp);
	
	return 1;
}

void input_list(int code){
	int i;
	int n, mistake, file_check;
	char sel;
	char inp_grow_id[31];
	char inp_status[3];
	long long inp_point;
	
	struct node *new_member = NULL;
	struct node *new_ge = NULL;
	struct node *search_res = NULL;
	
	if(code == 1){
		do{
			mistake = 0;
			
			printf("Apakah anda ingin memasukkan data secara manual atau dari file contri_data.txt?\n");
			printf("Masukkan 1 jika ingin secara manual dan masukkan 2 jika tidak.\n");
			printf("Pilihan: "); scanf("%c", &sel); getchar();
			printf("\n");
			
			if(sel == '1'){
				break;
			} else if(sel == '2'){
				file_check = retrieve_clash_data();
				if(file_check == 1){
					return;
				}
				mistake = 1;
			} else {
				printf("<<Harap memasukkan pilihan sesuai yang diminta.>>\n\n");
				mistake = 1;
			}
		} while(mistake == 1);
	}
	
	switch(code){
		case 1: printf("Ada berapa member yang berpartisipasi dalam Clash?\n"); break;
		case 2: printf("Ada berapa member yang memberikan depo 30 WL?\n"); break;
		case 4: printf("Ada berapa member yang masuk GE promote list di Clash sebelumnya?\n"); break;
		case 5: printf("Ada berapa member yang masuk GE demote list di Clash sebelumnya?\n"); break;
	}
	
	do{
		mistake = 0;
		
		printf("Input: "); scanf("%d", &n); getchar();
		printf("\n");
		
		if(code != 1){
			if(n > member_count){
				printf("<<Jumlah yang dimasukkan lebih banyak dari jumlah partisipan.>>\n\n");
				mistake = 1;
			} else {
				if(n < 0){
					printf("<<Jumlah yang dimasukkan tidak boleh negatif.>>\n\n");
					mistake = 1;
				} else if(n == 0){
					printf("\n");
					return;
				} else if(code == 4 && n > total_GM){
					printf("<<Jumlah yang dimasukkan lebih banyak dari jumlah GM yang ada.>>\n\n");
					mistake = 1;
				} else if(code == 5 && n > total_GE){
					printf("<<Jumlah yang dimasukkan lebih banyak dari jumlah GE yang ada.>>\n\n");
					mistake = 1;
				}
			}
		}	
	} while(code != 1 && mistake == 1);
	
	switch(code){
		case 1:
			printf("Masukkan Grow ID, status, dan poin dengan format sebagai berikut:\n");
			printf("GrowID/Status/Poin >> Contoh: Meowlynna/GL/1000\n");
			printf("Note: Status yang diinput haruslah GM, GE, GC, atau GL!\n");
			break;
		case 2: printf("Masukkan Grow ID dari member-member yang depo:\n"); break;
		case 4: printf("Masukkan Grow ID member-member yang masuk ke promote list di Clash sebelumnya:\n"); break;
		case 5: printf("Masukkan Grow ID member-member yang masuk ke demote list di Clash sebelumnya:\n"); break;
	}
	printf("---------------------------------------\n");
	
	for(i = 0; i < n; i++){
		if(code == 1){
			printf("%d. ", i + 1);
			scanf("%[^/]/%[^/]/%lld", inp_grow_id, inp_status, &inp_point); getchar();
			
			if(code == 1 && strcmp(inp_status, "GE") == 0){
				new_ge = create_new_node(inp_grow_id, inp_status, inp_point);
				insert_list(new_ge, 3);
				total_GE++;
			}
			
			if(code == 1 && strcmp(inp_status, "GM") == 0){
				total_GM++;
			}
			
			member_count++;
			new_member = create_new_node(inp_grow_id, inp_status, inp_point);
		}
		
		else {
			do{
				mistake = 0;
				
				printf("%d. ", i + 1);
				scanf("%[^\n]", inp_grow_id); getchar();
				
				search_res = search(inp_grow_id, 1);
				if(search_res == NULL){
					printf("\n<<Tidak ada partisipan dengan Grow ID tersebut.>>\n\n");
					mistake = 1;
				} else if(code == 4 && strcmp(search_res->status, "GM") != 0){
					printf("\n<<Hanya member yang bisa dimasukkan ke list promote GE.>>\n\n");
					mistake = 1;
				} else if(code == 5 && strcmp(search_res->status, "GE") != 0){
					printf("\n<<Hanya GE yang bisa dimasukkan ke list demote GE.>>\n\n");
					mistake = 1;
				}
			} while(mistake == 1);
			
			new_member = create_new_node(search_res->grow_id, search_res->status, search_res->point);
		}
		
		insert_list(new_member, code);
	}
	printf("\n");
}

void process_clash_data(){
	struct node *curr = head[0];
	struct node *check_depo = NULL;
	struct node *check_promote = NULL;
	struct node *check_demote = NULL;
	struct node *new_member = NULL;
	struct node *new_ge = NULL;
	struct node *new_depotake = NULL;
	
	while(curr != NULL){
		check_depo = search(curr->grow_id, 2);
		check_promote = search(curr->grow_id, 4);
		check_demote = search(curr->grow_id, 5);
		
		if(check_depo == NULL && curr->point < min_contri[clash_type].min_member){
			new_member = create_new_node(curr->grow_id, curr->status, curr->point);
			insert_list(new_member, 6);
		}
		
		else if(strcmp(curr->status, "GM") == 0){
			if(check_promote != NULL && curr->point >= min_contri[clash_type].min_non_member){
				new_member = create_new_node(curr->grow_id, curr->status, curr->point);
				new_ge = create_new_node(curr->grow_id, curr->status, curr->point);
				insert_list(new_member, 10);
				insert_list(new_ge, 3);
			}
			
			else if(check_promote == NULL && curr->point >= min_contri[clash_type].min_non_member){
				new_member = create_new_node(curr->grow_id, curr->status, curr->point);
				insert_list(new_member, 7);
			}
		}
		
		else if(strcmp(curr->status, "GE") == 0){
			if(check_demote != NULL && curr->point < min_contri[clash_type].min_non_member){
				if(check_depo == NULL && curr->point > min_contri[clash_type].min_member){
					new_member = create_new_node(curr->grow_id, curr->status, curr->point);
					insert_list(new_member, 11);
					delete_node(curr->grow_id, 3);
				}
			}
			
			else if(check_demote == NULL && curr->point < min_contri[clash_type].min_non_member){
				if(curr->point >= min_contri[clash_type].min_member){
					new_member = create_new_node(curr->grow_id, curr->status, curr->point);
					insert_list(new_member, 8);
				}
			}
		}
		
		if(check_depo != NULL && curr->point < min_contri[clash_type].min_member){
			new_depotake = create_new_node(curr->grow_id, curr->status, curr->point);
			insert_list(new_depotake, 9);
		}
	
		curr = curr->next;
	}
}

int generate_discord_leaderboard(char clash_date[14], int guild_rank){
	FILE *fp;
	struct node *curr = NULL;

	char inp_year[5];
	char inp_month[3];
	char clash_season[7];
	int n, clash_series, current_month, clash_month, clash_year;
	long long guild_contribution;
	int i, j;
	
	char emoji_title_begin[51];
	char emoji_title_end[51];
	char emoji_subtitle[51];
	
	n = strlen(clash_date);
	
	for(i = n - 4, j = 0; i < n; i++, j++){
		inp_year[j] = clash_date[i];
	}
	
	for(i = n - 7, j = 0; i < n - 5; i++, j++){
		inp_month[j] = clash_date[i];
	}
	
	current_month = atoi(inp_month);
	clash_year = atoi(inp_year);
	
	if(current_month >= 3 && current_month <= 6){
		strcpy(clash_season, "Spring");
	} else if(current_month >= 7 && current_month <= 10){
		strcpy(clash_season, "Summer");
	} else {
		strcpy(clash_season, "Winter");
	}
	
	if(current_month < 7){
		clash_series = clash_year - 2018;
	} else {
		clash_series = clash_year - 2017;
	}
	
	if(current_month % 4 == 3){
		clash_month = 1;
	} else if(current_month % 4 == 0){
		clash_month = 2;
	} else if(current_month % 4 == 1){
		clash_month = 3;
	} else {
		clash_month = 4;
	}
	
	if(strcmp(clash_season, "Summer") == 0){
		strcpy(emoji_title_begin, ":sunflower:");
		strcpy(emoji_title_end, ":sunny:");
		strcpy(emoji_subtitle, ":palm_tree:");
	}
	
	else if(strcmp(clash_season, "Winter") == 0){
		strcpy(emoji_title_begin, ":snowflake:");
		strcpy(emoji_title_end, ":snowman2:");
		strcpy(emoji_subtitle, ":cloud_snow:");
	}
	
	else {
		strcpy(emoji_title_begin, ":ear_of_rice:");
		strcpy(emoji_title_end, ":leaves:");
		strcpy(emoji_subtitle, ":potted_plant:");
	}
	
	curr = head[0];
	guild_contribution = 0;
	
	while(curr != NULL){
		guild_contribution += curr->point;
		curr = curr->next;
	}
	
	fp = fopen("clash_leaderboard.txt", "w");
	if(fp == NULL){
		return 0;
	}
	
	fprintf(fp, "%s  **%s Clash %d - Series %d - Month %d**  %s\n", emoji_title_begin, clash_season, clash_year, clash_series, clash_month, emoji_title_end);
	fprintf(fp, "==================================\n");
	fprintf(fp, "%s Clash Details:\n", emoji_subtitle);
	fprintf(fp, "---------------------\n");
	fprintf(fp, ":small_orange_diamond: Clash event : *%s*\n", min_contri[clash_type].name);
	fprintf(fp, ":small_orange_diamond: Clash type : :gtcheck:  *Wajib*\n");
	fprintf(fp, ":small_orange_diamond: Guild rank : *#%d*", guild_rank);
	if(guild_rank > 100){
		fprintf(fp, "\n");
	} else {
		fprintf(fp, " :medal:\n");
	}
	fprintf(fp, ":small_orange_diamond: Guild contribution : *", guild_contribution);
	number_to_string(guild_contribution, fp); fprintf(fp, "* poin\n");
	
	fprintf(fp, ":small_orange_diamond: Poin contribution minimal :\n");
	fprintf(fp, "       :white_check_mark:  Member : *%s :arrow: ", min_contri[clash_type].hashtag_member);
	number_to_string(min_contri[clash_type].min_member, fp); fprintf(fp, " poin*\n");
	fprintf(fp, "       :white_check_mark:  GE/GC/GL : *%s :arrow: ", min_contri[clash_type].hashtag_non_member);
	number_to_string(min_contri[clash_type].min_non_member, fp); fprintf(fp, " poin*\n\n");
	
	fprintf(fp, "%s Top Contributors:\n", emoji_subtitle);
	fprintf(fp, "--------------------------\n");
	
	char member_name[35];
	char gay_of_the_month[31];
	curr = head[0];
	i = 0;
	
	while(curr != NULL){
		if(i > 9){
			break;
		}
		
		if(strcmp(curr->status, "GM") == 0){
			strcpy(member_name, curr->grow_id);
		} else {
			strcpy(member_name, curr->grow_id);
			strcat(member_name, " (");
			strcat(member_name, curr->status);
			strcat(member_name, ")");
		}
		
		if(i == 0){
			fprintf(fp, ":first_place:  **");
		} else if(i == 1){
			fprintf(fp, ":second_place:  **");
		} else if(i == 2){
			fprintf(fp, ":third_place:  **");
		} else if(i == 3){
			fprintf(fp, ":four:  ");
		} else if(i == 4){
			fprintf(fp, ":five:  ");
		} else if(i == 5){
			fprintf(fp, ":six:  ");
		} else if(i == 6){
			fprintf(fp, ":seven:  ");
		} else if(i == 7){
			fprintf(fp, ":eight:  ");
		} else if(i == 8){
			fprintf(fp, ":nine:  ");
		} else if(i == 9){
			fprintf(fp, ":keycap_ten:  ");
		}
		
		fprintf(fp, "%s *~", member_name); number_to_string(curr->point, fp); fprintf(fp, " poin");
		
		if(i < 2){
			fprintf(fp, "***\n");
		} else if(i == 2){
			fprintf(fp, "***\n\n");
		} else {
			fprintf(fp, "*\n");
		}
		
		i++;
		curr = curr->next;
	}
	fprintf(fp, "\n");
	
	fprintf(fp, ":shamrock: Special thanks and appreciation for your great contribution for guild ^^\n\n");
	
	curr = head[0];
	while(curr->next != NULL && curr->next->point != 0){
		if(curr->next == tail[0]){
			curr = tail[0];
			break;
		}
		curr = curr->next;
	}
	fprintf(fp, ":rainbow:  @Gay of the Month : %s\n\n", curr->grow_id);
	
	fprintf(fp, "@everyone");
	
	fclose(fp);
	
	return 1;
}

long long exponent(long long num, int n){
	if(n == 1){
		return num;
	} else if(n == 0){
		return 1;
	} else {
		return num * exponent(num, n - 1);
	}
}

void number_to_string(long long number, FILE *fp){
	int i, j, k;
	int num, digit, comas, type, pos, n;
	char temp_string[MAX + 1];
	
	for(i = 0; i < MAX; i++){
		if(number % exponent(10, i) == number){
			break;
		}
	}
	
	digit = i;
	j = 0;
	
	for(i = digit; i > 0; i--){
		num = (number % exponent(10, i) - number % exponent(10, i - 1)) / exponent(10, i - 1);
		temp_string[j] = num + 48;
		j++;
	}
	
	for(i = j; i < MAX + 1; i++){
		temp_string[i] = '\0';
	}
	
	if(digit > 3){
		comas = (digit - 1) / 3;
		type = digit % 3;
		n = digit + comas;
	
		switch(type){
			case 1: pos = 1; break;
			case 2: pos = 2; break;
			case 0: pos = 3; break;
		}
		
	} else {
		n = digit;
	}
	
	char string_number[MAX + comas + 1];
	
	j = 0;
	for(i = 0; i < n; i++){
		if(digit > 3 && i == pos){
			string_number[i] = ',';
			pos += 4;
		} else {
			string_number[i] = temp_string[j];
			j++;
		}
	}
	
	for(i = n; i < 27; i++){
		string_number[i] = '\0';
	}
	
	fprintf(fp, "%s", string_number);
}
