#include <stdio.h>

void armstrong(void);

int main(void){
	
	armstrong();	//Fonksiyon Çaðýrýcý
	
	return 0;
}

void armstrong(void){
	
	int sayi, sayac=0, temps, sum=0,bas,us,tempsayac;		//Variables
	
	printf("Bir sayi giriniz: ");			//Girdi
	scanf("%d",&sayi);
	
	temps=sayi;
	
	while(temps>0){			//Basamak Bulucu
		temps=temps/10;		//Basamak her seferinde 1 azalýr
		sayac++;			//Sayac tersi þekilde artar
	}
	
	temps=sayi;
	
	while(temps>0){	
		bas=temps%10;		//O anki basamak
		tempsayac=sayac;	//Basamak sayýsýný her seferinde baþa döndürür
		us=1;				//Üs deðerini sýfýrlar (Çarpmada 1)
		while(tempsayac>0){		//Basamak Sayýsý Kadar Basamaðý kendiyle çarpma (üs alma)
			us*=bas;
			tempsayac--;
		}
		sum+=us;				//Üssü alýnmýþ ifade toplanýr
		temps=temps/10;			//Sonraki basamaða geçilir.
	}
	
	if(sum==sayi){				//Eþitlik saðlanýrsa olumlu, saðlanmazsa olumsuz geridönüþ saðlanýr.
		printf("%d sayisi bir armstrong sayisidir.",sayi);
	}
	else{
		printf("%d sayisi bir armstrong sayisi degildir.",sayi);
	}
	
}
