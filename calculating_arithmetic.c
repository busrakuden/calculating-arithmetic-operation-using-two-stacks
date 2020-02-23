#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10

typedef struct{
	int item1[MAX];
	int top1;
	
	char item2[MAX];
	int top2;
	
}STACK;

void initstack(STACK *s){
	s->top1=0;
	s->top2=0;
}


void pushInt (int x,STACK *s){
	s->item1[s->top1]=x;
	++s->top1;
}

void pushChar (char x,STACK *s){
	s->item2[s->top2]=x;
	++s->top2;
}

int popInt (STACK *s){
	--s->top1;		
	return s->item1[s->top1];
}

char popChar (STACK *s){
	--s->top2;		
	return s->item2[s->top2];
}
void printStack(STACK *s){
	int i;
	if (s->top1==0)
		printf("\nSayi yigini:Bos");
	else {
		printf("\nSayi yigini:  ");
		for(i=0;i<s->top1;i++){
			printf("%d  ",s->item1[i]);
		}
	}
	if (s->top2==0)
		printf("\nIsaret yigini:Bos");
	else {
		printf("\nIsaret yigini:  ");
		for(i=0;i<s->top2;i++){
			printf("%c  ",s->item2[i]);
		}
	}
}

char peekChar (STACK *s){
	int adr;
	adr=s->top2-1;
	return s->item2[adr];
}
void islemler2(STACK *s){
	int num1,num2,num3;
	char pk;
	pk=peekChar(s);
	if (pk=='*'){
		num1=popInt(s);
		num2=popInt(s);
		num3=num2*num1;
		popChar(s);
		pushInt(num3,s);
		printStack(s);
	}else if (pk=='/'){
		num1=popInt(s);
		num2=popInt(s);
		num3=num2/num1;
		popChar(s);
		pushInt(num3,s);
		printStack(s);
	}
}
void islemler(STACK *s){
	int num1,num2,num3;
	char pk;
	pk=peekChar(s);
	if (pk=='-' ){
		num1=popInt(s);
		num2=popInt(s);
		num3=num2-num1;
		popChar(s);
		pushInt(num3,s);
		printStack(s);
		
		}else if (pk=='+' ){
			num1=popInt(s);
			num2=popInt(s);
			num3=num2+num1;
			popChar(s);
			pushInt(num3,s);
			printStack(s);
		}else 
			islemler2(s);

}
int stringToInteger(char *str){
	int uzunluk,x=0,i,y=0;
	uzunluk=strlen(str);
	if(uzunluk==1)
		x=*str-'0';
	else{
		for(i=0;i<uzunluk;i++){
			y=str[i]-'0';
			y=pow(10,uzunluk-i-1)*y;
			x+=y;
		}
	}
	return x;
}
	
int main(){
	char str[30],tmp[5],pk;
	int x,i=0,num,sonuc,j,k;
	STACK s;
	initstack(&s);
	printf ("Islemi giriniz:");
	scanf("%[^\n]s ",str);
	int uzunluk=strlen(str);
	while (i<uzunluk){
		j=0;
		if ((str[i]>='0') && (str[i]<='9')) {
		
			while((str[i]>='0') && (str[i]<='9')){
				tmp[j]=str[i];
				i++;
				j++;
			}
			i--;
			tmp[j] = '\0';
			num=stringToInteger(tmp);
			pushInt(num,&s);
			printStack(&s);
			tmp[0] = '\0';
	}
		else if(str[i]=='+'){
			islemler(&s);
			pushChar('+',&s);
			printStack(&s);
		}else if (str[i]=='-'){
			islemler(&s);
			pushChar('-',&s);
			printStack(&s);
		}else if(str[i]=='*'){
			islemler2(&s);
			pushChar('*',&s);
			printStack(&s);
		}else if(str[i]=='/'){
			islemler2(&s);
			pushChar('/',&s);
			printStack(&s);
		}else if(str[i]=='('){
			pushChar('(',&s);
			printStack(&s);
		}else if (str[i]==')'){
			pk=peekChar(&s);
			while(pk!='('){
				islemler(&s);
				pk=peekChar(&s);
			}
			popChar(&s);
		}
		i++;
	} 
	while(peekChar(&s)){
		islemler(&s);
	}
	sonuc=popInt(&s);
	printf("\nSonuc:%d",sonuc);
	return 0;
}
