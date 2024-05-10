#include <stdio.h>	 //*This is the STANDARD LIBRARY for C.
#include <string.h> //*This is the library to work with strings.

#ifdef _WIN32
#include <windows.h> // Required for Sleep() on Windows 
#endif

//Functions Declaration

void PaymentsDetails();
void SaveData();
void StoreInArrays();
void ClearScreen();


// Constants

const float SingleLessonPrice = 31;
const float GroupLessonPrice = 25;
const float DiscountValue = 10;
const int MAX_STORAGE = 5;

// General Variables

//Switches

int LessonMode = 0;
int Language = 3;
int ApplyDiscount = 0;

// Inputs

char UserInput0[10];
char StudentName[15];
int MonthNumber;
char Month[15];
int Options;
int i;
float HoursNumber;

// Results

float Price;
float Discount;
float MonthPayment;
float PaymentWithDiscount;

//Arrays

//char StoreName[50]; 
//char StoreMonth[50];
//float StorePayValue[10];

FILE *fptr; // Declare the file pointer globally

int main() {
	
	ProgramIni:
	
	ClearScreen();
	
	printf("\n");
	printf("1- Generate Payment \n");
	printf("2- Show Monthly Payments Log \n");
	printf("10- SaveData \n");
	printf("7- Exit \n\n");

	scanf("%d", &Options);

	switch(Options){
		
		case 1:
		
			break;
		
		case 2:
		
			//SHOW MONTHLY PAYMENTS
			break;
		
		case 10:
		
			SaveData();
			break;
		
		
		case 7:
		
			ClearScreen();
			return 0;
			break;
			
		default:
		
			goto ProgramIni;
			break;
	
	}

	AskLanguage:
	ClearScreen();
	
	printf("\n\n");
	printf("1- English \n");
	printf("2- Spanish \n");
	printf("3- Portuguese \n");
	
	scanf("%d", &Options);
	
		switch(Options){
		
		case 1:
		
			Language = 1; // English
			break;
		
		case 2:
		
			Language = 2; // Spanish
			break;
		
		case 3:
		
			Language = 3; // Portuguese
			break;
			
		default:
		
			goto AskLanguage;
			break;
	
	}

	AskGroup:
	
	printf("\n\n");
	printf("1- Individual Lessons \n");
	printf("2- Group Lessons \n");
	
	scanf("%d", &Options);
	
	
	switch(Options){
		
		case 1:
		
			LessonMode = 0;
			break;
		
		case 2:
		
			LessonMode = 1;
			break;
		
		default:
		
			goto AskGroup;
			break;
	
	}
	
	printf("\nStudent Name: ");
	scanf("%14s", &StudentName);
	
	printf("\nMonth of Payment: ");
	scanf("%14s", &Month);
	
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
	
	ClearScreen();
	
	printf("\n\n"); 
	printf("Full Monthly Payment: R$ %.2f (No Discount) \n\n", MonthPayment);
	
	ApplyDiscount = 0;
	printf("Apply discount? Y/N \n");
	scanf("%2s", &UserInput0);
	
	if (strcasecmp(UserInput0, "Y") == 0) {
		
		ApplyDiscount = 1; 
		
	}
		ClearScreen();	
		
		if (ApplyDiscount == 1) {
		
			printf("\nAplying discount...\n");
			Discount = (MonthPayment * DiscountValue) / 100;
			PaymentWithDiscount = MonthPayment - Discount;
		}
		
		printf("Full monthly payment: R$ %.2f (No Discount) \n", MonthPayment);
		
		if (ApplyDiscount == 1){
			
			printf("Monthly payment with discount: R$%.2f (%.0f percent discount)", PaymentWithDiscount, DiscountValue);
		
		}
			
		printf("\n\n==================================================================================================== \n\n");
		
		switch(Language){
			
			case 1:
			
				printf("%s, this month there are %.0f classes. _%.0f * %.2f = R$%.2f_", StudentName, HoursNumber, HoursNumber, Price, MonthPayment);
				
				if (ApplyDiscount == 1) {
					
					printf(" --> with the %.0f percent discount it would be: %.2f - %.2f = *R$%.2f*.", DiscountValue, MonthPayment, Discount, PaymentWithDiscount);
				
				}
				
				if (ApplyDiscount == 0) {
					
					printf(" --> No discount applied.");
				
				}
				
				break;		
					
			case 2: 
				
				printf("%s, este mes son %.0f clases. _%.0f * %.2f = R$%.2f_", StudentName, HoursNumber, HoursNumber, Price, MonthPayment);
				
				if (ApplyDiscount == 1) {
					
					printf("--> con el %.0f porciento de descuento quedaria: %.2f - %.2f = *R$%.2f*.", DiscountValue, MonthPayment, Discount, PaymentWithDiscount);
				
				}
			
				if (ApplyDiscount == 0) {
					
					printf(" --> Sin descuento aplicado.");
				
				}
				
				break;
			
			case 3:
				
				printf("%s, esse mes sao %.0f aulas. _%.0f * %.2f = R$%.2f_", StudentName, HoursNumber, HoursNumber, Price, MonthPayment);
				
				if (ApplyDiscount == 1) {
					
					printf("--> com o %.0f porcento de desconto ficaria: %.2f - %.2f = *R$%.2f*.", DiscountValue, MonthPayment, Discount, PaymentWithDiscount);
				
				}
				
				if (ApplyDiscount == 0) {
					
					printf(" --> Sem desconto.");
				
				}
				
				break;
				
			default:
			
				break;
		}
	
	//} else {
		
	//	printf("No discount... \n");
	
	//	printf("\n");
	//	printf("%s, esse mes sao %.0f aulas. %.0f * %.2f = *R$%.2f*.", StudentName, HoursNumber, HoursNumber, Price, MonthPayment);

	//}
	
	printf("\n\n==================================================================================================== \n");
	
	// STORING IN ARRAYS AND SAVING DATA
	StoreInArrays();
	
	// Generate payment receipt.
	
	printf(" Generate receipt? [Y/N]: ");
	
	Exit:
	
	printf("\n\n1- Do Another Payment \n");
	printf("2- Main Menu \n");
	printf("7- Exit... \n");
	scanf("%d2s", &Options);
	
	switch(Options){
		
		case 1:
		
			goto AskLanguage;
			break;
		
		case 2:
		
			goto ProgramIni;
			break;
		
		case 7:
		
			ClearScreen();
			return 0;
			break;
		
		default:
			
			goto Exit;
			break;
	
	}
	
	return 0;
	
}

void StoreInArrays() {
	
	for (i=0; i<MAX_STORAGE; i++) {
		
		//if (strcmp(StoreName[i], "") == 0 && StorePayValue[i] == 0) {
			
			// StoreMonth[i] =
			//StoreName[i] = StudentName; //??????
			//StorePayValue[i] = MonthPayment;
			//printf("Stored in Arrays"); 
			//printf("%d", i);
			//break;
			
		//}
			
	}

}

//CLS Function
void ClearScreen() {

#ifdef _WIN32
    
    // Windows
    system("cls");

#else
    
    // Unix-like systems
    system("clear");

#endif

}

void SaveData() {
	
	
	for (i=0; i<5; i++) {
		
		printf("%d", i);
		
		
		
	}
	
	printf("Saving...");
	
	// Save the variable to a file
	fptr = fopen("data.dat", "w+");
	
	if (fptr == NULL) {
		
		printf("Error opening file!\n");
		return;
	}

    // Write variables to the file
    
    //fprintf(fptr, "%29s", MasterKey);
    
    for (i = 0; i < MAX_STORAGE; i++) { // FOR..I loop to save passwords and IDs.
        
        //fprintf(fptr, "%49s", WebService[i]);
        //fprintf(fptr, "%49s", ID[i]);
        //fprintf(fptr, "%49s", passwords[i]);
    }


	fclose(fptr);
	
	//ClearScreen();
		
	
	
	}

void PaymentsDetails() {
	
	
	
	}

// ================================= NOTES =======================================	
	
// TO DO
// =====

//* Generate receipt.

// DONE
// ====

//* Add languages feature. Final messages in Spanish, English and Portuguese. [100%]
//* Don't show discount messages and information when there's NO discount applied. [100%]






