#include <stdio.h>     // Import fundamental functions like printf()
   #include <stdlib.h>     // Import srand() function
   #include <time.h>     // Import time() function 
   #include <math.h>
   
   // The global variables has 0 value in default
   int NODE[4][1001];     
   int tmp, i, j;
   int cnt_success, cnt_arrive;     //성공률값을받는변수와
				    //Count on Frames arriving at slots 

   double avr_success[500];     //성공률의평균값을받는변수선언
   double input_G[50];     //G값
   double A;     //G값에의해계산될A 값을받기위한변수선언

   int q, s;
   int ceilA;

   int main()
   {
	    FILE* fout = fopen("result_policy1.csv", "w");
	   fprintf(fout, "Average of Success Frame No,Suc_Average\n");

	   srand(time(NULL));     //rand 값생성
	   for(i=0; i<50; i++){
		   input_G[i] = 0.1F*(i+1);
	   }

		 for(s=0; s<50; s++){     //Simulation 동작
		
		   tmp=0;
		   A=4.0F*(2.0F/input_G[s]);     //G값을이용하여A값을계산한다
		   ceilA = ceil(A);
		   for(q=0;q<50;q++){     //50번돌려서평균값계산하는구문
			   for(i=0;i<4;i++){     //station을5개생성하는구문
				   while(1){
					   tmp=tmp+rand() % ceilA +1;
					   //NODE[i][0]에서[i][1000]까지돌림
					   if(tmp>1000)
					   //NODE[4][999] 이상이면빠져나오기
						   break;
					   NODE[i][tmp]=1;
					   //NODE[0][0]에서NODE[9][999]까지
					   //Frame이전송되는것을1로표현
				   }
				   tmp = 0;     //tmp를초기화해준다
			   }
			   for(i=0;i<1000;i++){	
				   cnt_arrive=0;
				   //i 시간에전송받은것을센다
				   for(j=0;j<4;j++){     //각station 체크하기
					   if(NODE[j][i]>0)
						   cnt_arrive++;
				   }
				//한slot에Frame이두개이상
				//시도되는것을체크하기위해
				   if(cnt_arrive == 1){	
                                //한slot에Frame이1개만전송된다면
					   cnt_success++;     //Fraem 전송성공
				   }
			   }
			   avr_success[s]+=cnt_success;     //성공률을50번더한다
			   cnt_success = 0;		    //성공률을초기화한다
			   for(i=0; i<4; i++){		    //NODE를초기화해준다
				   for(j=0; j<1000; j++){
					   NODE[i][j] = 0;
				   }
			   }
		   }     //평균값계산을종료한다
		   avr_success[s]/=50.0F;     
                         //50번더해진성공률을50으로나누어평균값을계산
	    
                         //마찬가지로50번반복하므로50으로나누어평균값을계산
		
		   printf("[%.1f] Average of Success Frame No. = %lf\n", ((float)s/10.0+0.1), avr_success[s]);
		   fprintf(fout, "%.1f,%lf\n", ((float)s/10.0+0.1), avr_success[s]);
	 }     //Simulation termination
	   fclose(fout);
	   return 0;
   }