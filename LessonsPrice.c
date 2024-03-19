#include <stdio.h>	 //*This is the STANDARD LIBRARY for C.
#include <string.h> //*This is the library to work with strings.

// Constants

const float SingleLessonPrice = 31;
const float GroupLessonPrice = 25;
const float DiscountValue = 10;

// General Variables

//Switches

int LessonMode = 0;

// Inputs

char UserInput0[10];
char StudentName[15];
int Options;
float HoursNumber;

// Results

float Price;
float Discount;
float MonthPayment;
float PaymentWithDiscount;

int main() {
	
	ProgramIni:
	
	printf("\n");
	printf("1- Individual Lessons \n");
	printf("2- Group Lessons \n\n");

	scanf("%d", &Options);
	
	
	switch(Options){
		
		case 1:
		
			LessonMode = 0;
			break;
		
		case 2:
		
			LessonMode = 1;
			break;
		
		default:
		
			goto ProgramIni;
			break;
	
	}
	
	printf("Student Name: ");
	scanf("%14s", &StudentName);
	
	printf("Number of lessons: ");
	scanf("%f", &HoursNumber);
	
	if (LessonMode == 0) {
		
		printf("Individual Lessons... \n");
		Price = SingleLessonPrice;
		
	} else {
		
		printf("Group Lessons... \n");
		Price = GroupLessonPrice;
		
	}
		
	MonthPayment = Price * HoursNumber;    
	
	printf("\n"); 
	printf("Full Monthly Payment: R$ %.2f (No Discount) \n\n", MonthPayment);
	
	printf("Apply discount? Y/N \n");
	scanf("%2s", &UserInput0);
	
	if (strcasecmp(UserInput0, "Y") == 0) {
			
		printf("Applying discount...\n");
		
		Discount = (MonthPayment * DiscountValue) / 100;
		PaymentWithDiscount = MonthPayment - Discount;
		
		printf("Full Monthly Payment: R$%.2f (with %.0f percent discount) \n\n", PaymentWithDiscount, DiscountValue);
			
		printf("\n");
		printf("%s, esse mes sao %.0f aulas. _%.0f * %.2f = R$%.2f_ --> com o %.0f porcento de desconto ficaria: %.2f - %.2f = *R$%.2f*.", StudentName, HoursNumber, 
		HoursNumber, Price, MonthPayment, DiscountValue, MonthPayment, Discount, PaymentWithDiscount);
	
	} else {
		
		printf("No discount... \n");
	
		printf("\n");
		printf("%s, esse mes sao %.0f aulas. %.0f * %.2f = *R$%.2f*.", StudentName, HoursNumber, HoursNumber, Price, MonthPayment);

	}
	
	Exit:
	
	printf("\n Input 7 to exit...\n");
	scanf("%d2s", &Options);
	
	switch(Options){
		
		case 7:
		
			return 0;
			break;
		
		default:
		
			goto Exit;
			break;
	
	}
	
	return 0;
	
}





