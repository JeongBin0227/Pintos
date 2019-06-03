#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"

#include "devices/timer.h"

//팔 세마포어
struct semaphore *ra3_1;
struct semaphore ra3__1;
struct semaphore *ra3_2;
struct semaphore ra3__2;
struct semaphore *ra2_1;
struct semaphore ra2__1;
struct semaphore *ra2_2;
struct semaphore ra2__2;
struct semaphore *ra1_1;
struct semaphore ra1__1;
struct semaphore *ra1_2;
struct semaphore ra1__2;

//벨트 세마포어
struct semaphore *bt2_1;
struct semaphore bt2__1;
struct semaphore *bt2_2;
struct semaphore bt2__2;
struct semaphore *bt1_1;
struct semaphore bt1__1;
struct semaphore *bt1_2;
struct semaphore bt1__2;

//화로 세마포어
struct semaphore *if3;
struct semaphore if3_;
struct semaphore *if2;
struct semaphore if2_;
struct semaphore *if1;
struct semaphore if1_;

int timer = 3;
int coFeIng = 0;
int feIng_in_if3=0;
int coIng_in_if3=0;

int feOre = 0;
int coOre = 0;
int feIng = 0;
int coIng = 0;
int mineral[4]={0};

int bt_Fe[7]={0,0,0,0,0,0,0};
int bt_Co[7]={0,0,0,0,0,0,0};

int time =1;
int if1_num=0;
int if2_num=0;
int make_coefIng_num = 0;


void map_print(){

	for(int position = 0; position< 10;position++ ){
		printf("x ");
	}
	printf("\n");
	for(int position = 0; position< 10;position++ ){
		if(position==3||position==5||position==9){
               printf("@ ");
		}
		else if(position==4){
         if(if1_num==0) printf("- ");
         else if(if1_num==1) printf("o " );
         else if(if1_num==2) printf("i ");
      }
		else if(position<3){
               if(bt_Fe[position]==1) printf("o ");
               else printf("  ");
            }
      else if(position>5 && position<9){
         if(bt_Fe[position-3]==2) printf("i ");
         else printf("  ");
         }
	}
	printf("\n");

	for(int position = 0; position< 10;position++ ){
		if(position==9)
			printf("- ");
		else
			printf("x ");
	}
	printf("\n");
	for(int position = 0; position< 10;position++ ){
		if(position==3||position==5||position==9){
               printf("@ ");
		}
		else if(position==4){
         if(if2_num==0) printf("- ");
         else if(if2_num==1) printf("o ");
         else if(if2_num==2) printf("i ");
         }
      else if(position<3){
         if(bt_Co[position]==1) printf("o ");
            else printf("  ");
         }
      else if (position>5 && position<9){
         if(bt_Co[position-3]==2) printf("i ");
            else printf("  ");
         }
		
	}
	printf("\n");

	for(int position = 0; position< 10;position++ ){
		printf("x ");
	}

	printf("\n");
	printf("T = %d\n", time);
	time++;

	printf("LEFT: FeOre = %d, CoOre = %d, FeIng = %d, CoIng = %d\n",feOre,coOre,feIng,coIng );
	printf("MADE: CoFe = %d", coFeIng);

   printf("\n");
   printf("\n");

   
		
	   }

void if_third(void){
   while(1){
      if(mineral[2]==feIng_in_if3 && mineral[3]==coIng_in_if3){
         timer--;
         bt_Fe[6] = 1;
			bt_Co[6] = 1;
         if(timer ==0){
            coFeIng++;
            timer=3;
            feIng_in_if3=0;
            coIng_in_if3=0;
            bt_Fe[6] = 0;
				bt_Co[6] = 0;

				if(coFeIng == make_coefIng_num){
					map_print();
		  			printf("끝났습니다.\n");
               return 0; //종료조건

	  			}
         }
     }

			
      sema_up(ra3_1);
      sema_down(if3);
      timer_sleep(1);
   }
}
void ra_third_1(void){
   while(1){
      if(ra3_1->value==0){
			sema_up(ra3_1);
		}
      sema_down(ra3_1);
		
		if(bt_Fe[6] == 0){ //화로가 일을 안하면
      	if(bt_Fe[5]==2 && feIng_in_if3 < mineral[2]){
            	 feIng_in_if3++;
					 feIng--;
         	   bt_Fe[5]=0;
      	}
		}

      sema_up(ra3_2);
      sema_down(ra3_1);
   }
}
void ra_third_2(void){
   while(1){
      if(ra3_2->value==0) {
			sema_up(ra3_2);
		}

      sema_down(ra3_2);
		if(bt_Co[6] == 0){ //화로가 일을 안하면
      	if(bt_Co[5]==2 && coIng_in_if3 < mineral[3]){
         	coIng_in_if3++;
				coIng--;
        		bt_Co[5]=0;
      	}
		}
      sema_up(bt2_1);
      sema_down(ra3_2);
   }
}
void bt_third_1(void){
   while(1){
      if(bt2_1->value==0) sema_up(bt2_1);
      sema_down(bt2_1);

			if(bt_Fe[5] != 2){ 

				bt_Fe[5] = bt_Fe[4];
				bt_Fe[4] = bt_Fe[3];
				bt_Fe[3]=0;

			
		}
		
      sema_up(bt2_2);
      sema_down(bt2_1);
   }
}

void bt_third_2(void){
   while(1){
		if(bt2_1->value==0) sema_up(bt2_1);
      sema_down(bt2_1);

		if(bt_Co[5] != 2){ 
				bt_Co[5] = bt_Co[4];
				bt_Co[4] = bt_Co[3];
				bt_Co[3]=0;
			}
		
      
      sema_up(ra2_1);
      sema_down(bt2_2);
   }
}
void ra_second_1(void) {
	while(1) {
		if(ra2_1->value==0) sema_up(ra2_1);
		sema_down(ra2_1);

		if(if1_num == 2 && bt_Fe[3] == 0) {
			if1_num = 0;
			bt_Fe[3] =2;
		}
		sema_up(ra2_2);
		sema_down(ra2_1);
	}
}

void ra_second_2(void) {
	while(1) {
		if(ra2_2 -> value == 0) sema_up(ra2_2);
		sema_down(ra2_2);

		if(if2_num == 2 && bt_Co[3] == 0){
			if2_num = 0;
			bt_Co[3]=2;
		}

		sema_up(if1);
		sema_down(ra2_2);
	}
}

void if_second(void){
	while(1) {
		if(if1->value==0) sema_up(if1);
		sema_down(if1);

		if(if1_num==1) {
			if1_num=2;
			feIng++;
			feOre--;
		}
		sema_up(if2);
		sema_down(if1);
	}
}

void if_first(void){
	while(1){
		if(if2->value==0) sema_up(if2);
		sema_down(if2);

		if(if2_num == 1) {
			if2_num=2;
	
			coIng++;
			coOre--;

		}

		sema_up(ra1_1);
		sema_down(if2);
	}
}

void ra_first_1(void){
	while(1){
		if(ra1_1->value == 0) sema_up(ra1_1);
		sema_down(ra1_1);

		if(bt_Fe[2]==1 && if1_num==0){
			if1_num=1;
			bt_Fe[2]=0;
		}
		sema_up(ra1_2);
		sema_down(ra1_1);
	}
}

void ra_first_2(void){
	while(1){
		if(ra1_2->value == 0) sema_up(ra1_2);
		sema_down(ra1_2);

		if(bt_Co[2]==1 && if2_num==0){
			if2_num=1;
			bt_Co[2]=0;
			
		}
		sema_up(bt1_1);
		sema_down(ra1_2);
	}
}

void bt_first_1(void){
	while(1){
		if(bt1_1->value==0) sema_up(bt1_1);
		sema_down(bt1_1);

		if(bt_Fe[2]==0){
			if(bt_Fe[1]==1){
				bt_Fe[2]=1;
				bt_Fe[1]=0;
			}
		}
		if(bt_Fe[1]==0){
			if(bt_Fe[0]==1){
				bt_Fe[1]=1;
				bt_Fe[0]=0;
			}
		}
		if(bt_Fe[0]==0 && mineral[0]>0){
			bt_Fe[0]=1;
			mineral[0]--;
			feOre++;
		}
		sema_up(bt1_2);
		sema_down(bt1_1);
	}
}

void bt_first_2(void){
	while(1){
		if(bt1_2->value==0) sema_up(bt1_2);
		sema_down(bt1_2);

		if(bt_Co[2]==0){
			if(bt_Co[1]==1){
				bt_Co[2]=1;
				bt_Co[1]=0;
			}
		}
		if(bt_Co[1]==0){
			if(bt_Co[0]==1){
				bt_Co[1]=1;
				bt_Co[0]=0;
			}
		}
		if(bt_Co[0]==0 && mineral[1]>0){
			bt_Co[0]=1;
			mineral[1]--;
			coOre++;
		}
		map_print();
		sema_up(if3);
		sema_down(bt1_2);
	}
}

void run_factorii(char **argv){
	void *aux; //aux를 활용 안할꺼기 때문에 쓰레기 값을 넘겨 줄것이다.
	for(int i=0; i<4; i++){
		mineral[i] = atoi(argv[i+1]);
	}
	
	if(mineral[0]/mineral[2] > mineral[1]/mineral[3])
		make_coefIng_num = mineral[1]/mineral[3];
	else
		make_coefIng_num = mineral[0]/mineral[2];

	ra3_1 = &ra3__1;
	if3 = &if3_;
	ra3_2 = &ra3__2;
	bt2_1 = &bt2__1;
	bt2_2 = &bt2__2;
	bt1_1 = &bt1__1;
	bt1_2 = &bt1__2;
	ra1_1 = &ra1__1;
	ra1_2 = &ra1__2;
	ra2_1 = &ra2__1;
	ra2_2 = &ra2__2;
	if1 = &if1_;
	if2 = &if2_;


	sema_init(bt1_1, 0);
	sema_init(if3, 0);
	sema_init(bt2_1, 0);
	sema_init(bt2_2, 0);
	sema_init(ra1_1, 0);
	sema_init(ra1_2, 0);
	sema_init(ra2_1, 0);
	sema_init(ra2_2, 0);
	sema_init(if1, 0);
	sema_init(ra3_1, 0);
	sema_init(ra3_2, 0);
	sema_init(if2, 0);
	
	sema_init(bt1_2, 0);

	thread_create("if__third", PRI_DEFAULT, if_third, &aux);
	thread_create("ra_third__1", PRI_DEFAULT, ra_third_1, &aux);
	thread_create("ra_third__2", PRI_DEFAULT, ra_third_2, &aux);
	thread_create("bt_third__1", PRI_DEFAULT, bt_third_1, &aux);
	thread_create("bt_third__2", PRI_DEFAULT, bt_third_2, &aux);
	thread_create("ra_second__1", PRI_DEFAULT, ra_second_1, &aux);
	thread_create("ra_second__2", PRI_DEFAULT, ra_second_2, &aux);
	thread_create("if__second", PRI_DEFAULT, if_second, &aux);
	thread_create("if__first", PRI_DEFAULT, if_first, &aux);
	thread_create("ra_first__1", PRI_DEFAULT, ra_first_1, &aux);
	thread_create("bt_first__1", PRI_DEFAULT, bt_first_1, &aux);
	thread_yield();
	thread_create("bt_first__2", PRI_DEFAULT, bt_first_2, &aux);
	thread_create("ra_first__2", PRI_DEFAULT, ra_first_2, &aux);
	
}