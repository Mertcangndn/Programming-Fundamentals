#include <stdio.h>

void smith(int sayi);

int main(void){
	
	smith(121);
	
	return 0;
}

void smith(int sayi){
	
	int asallik, sayac, carpan, sumc=0, sumsayi=0, tempc, temps=sayi;
	
	for(carpan=2;carpan<sayi;carpan++){
		
		asallik=1;		//Asallýk sýfýrlayýcý
		
		if(carpan!=2){	//Çarpan Asal Mý?
			for(sayac=2;sayac<carpan;sayac++){
				if(carpan%sayac==0){
					asallik=0;
					break;
				}
			}
		}
		
		if(carpan==2 || asallik==1){	//Asal deðilse 
				while(temps%carpan==0){		//Çarpanlýk korunduðu sürece tekrarla
					tempc=carpan;
					while(tempc>0){			//Çarpanýn rakamlarýný topla.
						sumc+=tempc%10;
						tempc/=10;
					}
					temps/=carpan;
				}
			
		}
	}
	
	
	while(sayi>0){			//Sayýnýn rakamlarýný topla
		sumsayi+=sayi%10;
		sayi=sayi/10;
	}
	
	if(sumc==sumsayi){		//Eþitliði karþýlaþtýr
		printf("Smith Sayisidir.");
	}
	else{
		printf("Smith Sayisi Degildir.");
	}
}
