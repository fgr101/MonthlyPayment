#include <stdio.h>	//*This is the STANDARD LIBRARY for C.
#include <string.h> //*This is the library to work with strings.
#include <unistd.h> //*Include this for access function. Required for sleep() on Unix-like systems
#include <time.h>

#ifdef _WIN32
#include <windows.h> // Required for Sleep() on Windows 
#endif

//Functions Declaration

void SaveData();
void Load();
void ClearScreen();
void ChangePrices();
void NewEntryFile();
void ArgMarket();
void GoBackMenu();
void GeneratePayment();
void TimeDifferenceSUB();
void ConfigMenu();
void ShowPayments();
void WaitKey();

//USA Market

void USAMarket();
float USPrice = 5;

// Constants

int MAX_STORAGE = 5;

// General Variables

float SingleLessonPrice = 31;
float GroupLessonPrice = 25;
float ArgPrice = 5000;
float DiscountValue = 10;
float TotalValue = 1;

//Switches

int LessonMode = 0;
int Language = 3;
int ApplyDiscount = 0;
int Market = 2;

// Inputs

char UserInput0[10];
char StudentName[15];
int MonthNumber;
char Month[15];
int Options;
int i;
float HoursNumber;
char CurrencyLetters[3];
char input;

//Date and Time

char s[50];

// Results

float Price;
float Discount;
float MonthPayment;
float PaymentWithDiscount;

// New and Old students differences

float NewSinglePriceBR = 34;
float NewGroupPriceBR = 25;

int TimeDifferenceMODE = 0; // Switch to turn ON and OFF this mode.
int NewOrOld; // Switch that differenciates older from newer students. 0 means OLD, 1 means NEW.

FILE *fptr; // Declare the file pointer globally

int main() {
	
	//==================================================================
	// CREATES DATA FILE (IF IT DOESN'T EXIST)

	const char * filename = "data.dat";

	// Check if the file exists

	if (access(filename, F_OK) != -1) {
		
		//fptr = fopen(filename, "r+"); 
		Load();
		
	} else {
			
			// File doesn't exist, create a new file
			
			fptr = fopen(filename, "w+");
			printf("File does not exist. New file created. \n");
			fclose(fptr);
		
		}

	// Check if the file was opened successfully
	if (fptr == NULL) 

	{
		
		printf("Error opening the file.\n");
		return 1; // indicate an error to the operating system

	}

	// Close the file
	//fclose(fptr);

	//==================================================================

	Load();
	
	ProgramIni:
	Options = 0;   //resets the variable OPTIONS to be used again in the menu.
	ClearScreen();
	
	printf("\n\n");
	printf(".===================================.\n");
	printf("|  Monthly Payment Calculator 0.6   |\n");
	printf(".===================================.\n");
	printf("|                                   |\n");
	printf("| [1] Generate Payment              |\n");
	printf("| [2] Show Monthly Payments Log     | \n");
	printf("| [3] Configuration                 | \n");
	printf("| [7] Exit                          |\n");
	printf("|                                   |\n");
	printf(".===================================.\n\n");

	scanf("%d", &Options);

	switch(Options){
		
		case 1:
		
			break;
		
		case 2:
		
			//SHOW MONTHLY PAYMENTS
			ShowPayments();
			return 0;
			break;
			
		case 3:
			
			//CONFIGURATION
			ConfigMenu();
			SaveData();
			goto ProgramIni;
			break;
		
		case 7:
			
			SaveData();
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
	printf(".===================================.\n");
	printf("|            Language?              |\n");
	printf(".===================================.\n");
	printf("|                                   |\n");
	printf("| [1] English                       |\n");
	printf("| [2] Spanish                       | \n");
	printf("| [3] Portuguese                    | \n");
	printf("|                                   |\n");
    printf("|                                   |\n");
	printf(".===================================.\n\n");
	
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
		
			goto AskCountry;
			break;
	
	}
	
	AskCountry:
	ClearScreen();
	
	printf("\n\n");
	printf(".===================================.\n");
	printf("|   Currency and Country Target?    |\n");
	printf(".===================================.\n");
	printf("|                                   |\n");
	printf("| [1] Argentina [ARS]               |\n");
	printf("| [2] Brazil [BRL]                  |\n");
	printf("| [3] United States [USD]           |\n");
	printf("|                                   |\n");
    printf("|                                   |\n");
	printf(".===================================.\n\n");

	scanf("%d", &Options);
	
	switch(Options) {
	
		case 1:
		
			//SETS MARKET TO ARGENTINA'S MODE
			
			Market = 1;
			goto AskInformation;
			break;
		
		case 2:
			
			Market = 2;
			goto AskGroup;
			break;
			
		case 3:
		
			//SETS MARKET TO UNITED STATES'S MODE
			Market = 3;
			goto AskInformation;
			break;
			
		default:
		
			goto AskGroup;
			break;
		
	}

	AskGroup:
	ClearScreen();
	
	printf("\n\n");
	printf(".===================================.\n");
	printf("|          Kind of Lessons?         |\n");
	printf(".===================================.\n");
	printf("|                                   |\n");
	printf("| [1] Individual Lessons            |\n");
	printf("| [2] Group Lessons                 |\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
    printf("|                                   |\n");
	printf(".===================================.\n\n");
		
	scanf("%d", &Options);
	
	switch(Options) { //MEJORAR TODA ESTA PARTE, QUEDA REDUNDANTE
		
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
	
	switch (LessonMode) { //MEJORAR TODA ESTA PARTE, QUEDA REDUNDANTE
		
		case 0:
			
			printf("Individual Lessons... \n");
			Price = SingleLessonPrice;
			break;
		
		case 1:
			
			printf("Group Lessons... \n");
			Price = GroupLessonPrice;
			break;
			
	}
	
	//==================================================================
	// Ask about TIME DIFFERENCE MODE.
	
	if (TimeDifferenceMODE == 1) { TimeDifferenceSUB();}
	
	//==================================================================
		
	AskInformation:
	
	printf("\nStudent Name: ");
	scanf("%14s", &StudentName);
	
	printf("Month of Payment: ");
	scanf("%14s", &Month);
	
	printf("Number of lessons: ");
	scanf("%f", &HoursNumber);
	
	//==================================================================
	
	// Calls subs for different markets and currencies.
	
	if (Market == 1) { 
		
		ArgMarket();
		if (Options == 7) { return 0; } 
		goto ProgramIni; 
		
	}
	
	if (Market == 3) { 
		
		USAMarket();
		if (Options == 7) { return 0; } 
		goto ProgramIni; 
		
	}

	//==================================================================
	
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
		TotalValue = MonthPayment;
		
		if (ApplyDiscount == 1){
			
			printf("Monthly payment with discount: R$%.2f (%.0f percent discount)", PaymentWithDiscount, DiscountValue);
			TotalValue = PaymentWithDiscount;
			
		}
			
		//--------------------------------------------------------------
		
		NewEntryFile();	// Add information to the 'payments.txt' file.
		
		//--------------------------------------------------------------
		
		printf("\n\n==================================================================================================== \n\n");
		
		switch(Language){
			
			case 1:
			
				printf("%s, this month (%s) there are %.0f classes. _%.0f * %.2f = R$%.2f_", StudentName, Month, HoursNumber, HoursNumber, Price, MonthPayment);
								
				if (ApplyDiscount == 1) {
					
					printf(" --> with the %.0f percent discount it would be: %.2f - %.2f = :receipt *R$%.2f*.", DiscountValue, MonthPayment, Discount, PaymentWithDiscount);
				
				}
				
				if (ApplyDiscount == 0) {
					
					printf(" --> No discount applied.");
				
				}
				
				break;		
					
			case 2: 
				
				printf("%s, este mes (%s) son %.0f clases. _%.0f * %.2f = R$%.2f_", StudentName, Month, HoursNumber, HoursNumber, Price, MonthPayment);
				
				if (ApplyDiscount == 1) {
					
					printf("--> con el %.0f porciento de descuento quedaria: %.2f - %.2f = :receipt *R$%.2f*.", DiscountValue, MonthPayment, Discount, PaymentWithDiscount);
				
				}
			
				if (ApplyDiscount == 0) {
					
					printf(" --> Sin descuento aplicado.");
				
				}
				
				break;
			
			case 3:
				
				printf("%s, esse mes (%s) sao %.0f aulas. _%.0f * %.2f = R$%.2f_", StudentName, Month, HoursNumber, HoursNumber, Price, MonthPayment);
				
				if (ApplyDiscount == 1) {
					
					printf("--> com o %.0f porcento de desconto ficaria: %.2f - %.2f = :receipt *R$%.2f*.", DiscountValue, MonthPayment, Discount, PaymentWithDiscount);
				
				}
				
				if (ApplyDiscount == 0) {
					
					printf(" --> Sem desconto.");
				
				}
				
				break;
				
			default:
			
				break;
		}
	
	
	printf("\n\n==================================================================================================== \n");
	
	GeneratePayment(); // Generate payment receipt.
	
	Exit:
	
	GoBackMenu(); // Show GO BACK menu.
	if (Options == 7) { return 0; } 
	goto ProgramIni;
	
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

void NewEntryFile() {
	
	printf("\nAdding new entry to 'payments.txt' file...");
	
	// Save the variable to a file
	fptr = fopen("payments.txt", "a");
	
	if (fptr == NULL) {
		
		printf("Error opening file!\n");
		return;
	}
	
	//==================================================================
	// REQUESTING DATE AND TIME
		
	time_t now = time(NULL); 
    struct tm *local = localtime(&now);

    strftime(s, sizeof(s), "%d-%m-%Y", local);
        
	//==================================================================
    //SHOW THE RIGHT CURRENCY FOR EACH ENTRY: ARS, BRL, USD.
    
    switch (Market) {
		
		case 1:
		
			strcpy(CurrencyLetters, "ARS");
			break;
			
		case 2:
		
			strcpy(CurrencyLetters, "BRL");
			break;
			
		case 3:
		
			strcpy(CurrencyLetters, "USD");
			break;
		
	}
	
	//==================================================================
    // Write variables to the file

    fprintf(fptr, "* %s || Lessons:%2.f || %s [%s] %s $%.2f\n", s, HoursNumber, StudentName, Month, CurrencyLetters, TotalValue);
     
	fclose(fptr);
	
	}


void SaveData() {
	
	printf("Saving...");
	
	// Save the variable to a file
	fptr = fopen("data.dat", "w+");
	
	if (fptr == NULL) {
		
		printf("Error opening file!\n");
		return;
	}

    // Write variables to the file
    //==================================================================
    
    // Config variables
    //=================
    
    fprintf(fptr, "%d\n", TimeDifferenceMODE);
    
    printf("Config: Time Difference MODE [%d]\n", TimeDifferenceMODE);
    
    //Values and Prices
    //=================
    
    fprintf(fptr, "%f\n", SingleLessonPrice);
    fprintf(fptr, "%f\n", GroupLessonPrice);
    fprintf(fptr, "%f\n", NewSinglePriceBR);
    fprintf(fptr, "%f\n", NewGroupPriceBR);
    fprintf(fptr, "%f\n", DiscountValue);
    fprintf(fptr, "%f\n", ArgPrice);
    fprintf(fptr, "%f\n", USPrice);
    
    printf("Single lesson price saved: %.2f\n", SingleLessonPrice);
    printf("Group lesson price saved: %.2f\n", GroupLessonPrice);
	printf("Single lesson price for new students saved: %.2f\n", NewSinglePriceBR);
    printf("Group lesson price for new students saved: %.2f\n", NewGroupPriceBR);
	printf("Discount value saved: %.2f\n", DiscountValue);
	printf("Argentina's price saved: %.2f\n", ArgPrice);
	printf("United States price saved: %.2f\n", USPrice);

	    
	fclose(fptr);
	
	}
	
// LOAD Function
void Load() {
	
	printf("Loading...");
	
	 fptr = fopen("data.dat", "r");
	
    // Load the variable from the file
	
	if (fptr == NULL) {
		
		printf("Error opening file!\n");
    	return;

	}
		
    // Read variables from the file
    //==================================================================
    
    
    // Config variables
    //=================

    fscanf(fptr, "%d", &TimeDifferenceMODE);
    printf("Config: Time Difference MODE loaded [%d]\n", TimeDifferenceMODE);
  
  
    //Values and Prices
    //=================  
    
    fscanf(fptr, "%f", &SingleLessonPrice);
    fscanf(fptr, "%f", &GroupLessonPrice);
    fscanf(fptr, "%f", &NewSinglePriceBR);
    fscanf(fptr, "%f", &NewGroupPriceBR);
    fscanf(fptr, "%f", &DiscountValue);
    fscanf(fptr, "%f", &ArgPrice);
    fscanf(fptr, "%f", &USPrice);

    printf("Single lesson price loaded: %.2f\n", SingleLessonPrice);
    printf("Group lesson price loaded: %.2f\n", GroupLessonPrice);
    printf("Single lesson price for new students loaded: %.2f\n", NewSinglePriceBR);
    printf("Group lesson price for new students loaded: %.2f\n", NewGroupPriceBR);
    printf("Discount value loaded: %.2f\n", DiscountValue);
    printf("Argentina's price loaded: %.2f\n", ArgPrice);
    printf("United States price loaded: %.2f\n", USPrice);


	fclose(fptr);
	ClearScreen();
	    
}

void ChangePrices() {
	
	AskVariablesAgain:
	ClearScreen();

	
	printf("\n\n");
	printf(".===================================.          Argentina's price: $%.2f [ARS]\n", ArgPrice);
	printf("|         Change Variables          |          Brazil single lesson price: R$%.2f [BRL]\n", SingleLessonPrice);
	printf(".===================================.          Brazil group lesson price: R$%.2f [BRL]\n", GroupLessonPrice);
	printf("|                                   |          Brazil single lesson price for new students: R$%.2f [BRL]\n", NewSinglePriceBR);
	printf("| [1] Argentina [ARS]               |          Brazil group lesson price for new students: R$%.2f [BRL]\n", NewGroupPriceBR);
	printf("| [2] Brazil [BRL]                  |          Brazil discount value: %.2f [percentage]\n", DiscountValue);
	printf("| [3] United States [USD]           |          United States price: $%.2f [USD]\n", USPrice);
	printf("| [7] Go Back                       |\n");
	printf("|                                   |\n");
    printf("|                                   |\n");
	printf(".===================================.\n\n");
		
	scanf("%d", &Options);
	
	switch(Options){
		
		case 1:
		
			printf("\nArgentina's price? \n");
			scanf("%f4s", &ArgPrice);
			
			goto AskVariablesAgain;
			break;
		
		case 2:

			printf("\nSingle lesson price? \n");
			scanf("%f4s", &SingleLessonPrice);
				
			printf("\nGroup lesson price? \n");
			scanf("%f4s", &GroupLessonPrice);

			printf("\nNew students SINGLE lesson price? \n");
			scanf("%f4s", &NewSinglePriceBR);

			printf("\nNew students GROUP lesson price? \n");
			scanf("%f4s", &NewGroupPriceBR);
			
			printf("\nDiscount value? \n");
			scanf("%f4s", &DiscountValue);

			goto AskVariablesAgain;
			break;
			
		case 3:
		
			printf("\nUnited States's price? \n");
			scanf("%f4s", &USPrice);
			
			goto AskVariablesAgain;
			break;
		
		case 7:
		
			return;
			break;
			
		default:
		
			goto AskVariablesAgain;
			break;
	
	}
			
}

void ArgMarket() {
			
	Price = ArgPrice;
	MonthPayment = Price * HoursNumber;
	
	ClearScreen();
	
	printf("\n\n"); 
	printf("Full Monthly Payment: ARS $%.2f \n\n", MonthPayment);
	
	TotalValue = MonthPayment;
					
	//--------------------------------------------------------------
		
	NewEntryFile();	// Add information to the 'payments.txt' file.
		
	//--------------------------------------------------------------
	
	printf("\n\n==================================================================================================== \n\n");
		
	switch(Language){
			
		case 1:
			
			printf("%s, this month (%s) there are %.0f classes. _%.0f * %.2f = :receipt *R$%.$%.2f*_", StudentName, Month, HoursNumber, HoursNumber, Price, MonthPayment);
				
			break;		
					
		
		case 2: 
						
			printf("%s, este mes (%s) son %.0f clases. _%.0f * %.2f = :receipt *R$%.$%.2f*_", StudentName, Month, HoursNumber, HoursNumber, Price, MonthPayment);
				
			break;
			
		case 3:
				
			printf("%s, esse mes (%s) sao %.0f aulas. _%.0f * %.2f = :receipt *R$%.$%.2f*_", StudentName, Month, HoursNumber, HoursNumber, Price, MonthPayment);
			
			break;
				
		default:
			
			break;
	
	}
	
	printf("\n\n==================================================================================================== \n");
	
	GeneratePayment(); // Generate payment receipt.
	GoBackMenu(); // Show GO BACK menu.
	
}

void USAMarket() {

	Price = USPrice;
		
	MonthPayment = Price * HoursNumber;
	
	ClearScreen();
	
	printf("\n\n"); 
	printf("Full Monthly Payment: USD $%.2f \n\n", MonthPayment);
	
	TotalValue = MonthPayment;
					
	//--------------------------------------------------------------
		
	NewEntryFile();	// Add information to the 'payments.txt' file.
		
	//--------------------------------------------------------------
	
	printf("\n\n==================================================================================================== \n\n");
		
	switch(Language){
			
		case 1:
			
			printf("%s, this month (%s) we'll have %.0f classes. _%.0f * %.2f = :receipt *USD $%.2f*_", StudentName, Month, HoursNumber, HoursNumber, Price, MonthPayment);
				
			break;		
					
		
		case 2: 
						
			printf("%s, este mes (%s) vamos a tener %.0f clases. _%.0f * %.2f = :receipt *USD $%.2f*_", StudentName, Month, HoursNumber, HoursNumber, Price, MonthPayment);
				
			break;
			
		case 3:
				
			printf("%s, esse mes (%s) teremos %.0f aulas. _%.0f * %.2f = :receipt *USD $%.2f*_", StudentName, Month, HoursNumber, HoursNumber, Price, MonthPayment);
			
			break;
				
		default:
			
			break;
	
	}
	
	printf("\n\n==================================================================================================== \n");
	
	GeneratePayment(); // Generate payment receipt.
	GoBackMenu(); // Show GO BACK menu.
	
}


void GoBackMenu() {
	
	Exit2:
	
	Options = 0;
		
	//printf("\n\n1- Do Another Payment \n");
	printf("\n\n2- Main Menu \n");
	printf("7- Exit... \n");
	scanf("%d2s", &Options);
	
	switch(Options){
		
		//case 1:
		
			//goto AskLanguage;
			//return;
			//break;
		
		case 2:

			Options = 0;
			main();
			return;
			break;
		
		case 7:
		
			ClearScreen();
			return;
			break;
		
		default:
			
			SaveData();
			goto Exit2;
			break;
	
	}
	

}

void GeneratePayment() {
	
	// Generate payment receipt.
	
	printf(" Generate receipt? [Y/N]: \n\n");
	
	printf("*.====================.*\n");
	printf("*| Payment Received   |*\n");
	printf("*.====================.*\n\n");
	
	printf("*Student Name:* %s \n", StudentName);
	printf("*Month Paid:* %s \n", Month);
	
	if (Market == 1) { printf(":receipt *Total Price:* ARS $%.2f \n\n", TotalValue);}
	if (Market == 2) { printf(":receipt *Total Price:* R$%.2f \n\n", TotalValue);}
	if (Market == 3) { printf(":receipt *Total Price:* USD$%.2f \n\n", TotalValue);}
	
	printf("*.====================.*\n");

	return;

}

void TimeDifferenceSUB() {
	
	AskTimeDifferenceAgain:
	ClearScreen();
	
	printf("\n\n");
	printf(".===================================.\n");
	printf("|   Is it a NEW or OLD student?     |\n");
	printf(".===================================.\n");
	printf("|                                   |\n");
	printf("| [1] Old Student                   |\n");
	printf("| [2] New Student                   |\n");
	printf("|                                   |\n");
    printf("|                                   |\n");
	printf(".===================================.\n\n");

	scanf("%d", &Options);
	
	switch(Options) {
	
		case 1:
		
			NewOrOld = 0; //Old student
			return;
			break;
		
		case 2:
			
			NewOrOld = 1; //NewStudent
			
			if (LessonMode == 0) {
				
				Price = NewSinglePriceBR;
			
			} else { Price = NewGroupPriceBR; }

			return;
			break;
			
			
		default:
		
			goto AskTimeDifferenceAgain;
			break;
		
	}
	
}

void ShowPayments() {
	
    FILE * FilePointer = fopen("Payments.txt", "r");
    
    // Reading the file data using fgets() in the
    // form of a block of size 30 bytes
    
    // Muestra archivo de lista de pagos desde el principio.

	char buff[50];
	char ch;
	ClearScreen();

	do {
		
		for (i = 0; i <= 19 && ch != 0; i++) {
		
			fgets(buff, sizeof(buff), fptr);
			printf("%s", buff);
			
			ch = fgetc(FilePointer);
			printf("\n First character in the line: %c\n", ch);
		
		}
		
		printf ("\n Input [1] to continue...");
		WaitKey();
			
	} while ((fgets(buff, sizeof(buff), FilePointer) != NULL));
        
    //--------------------------------
    
    //fseek(FilePointer, 0, SEEK_SET);

	//char ch = fgetc(FilePointer);
	
	//if (ch != EOF) {
       
       //printf("\n First character in the file: %c\n", ch);
   
   //}
        
}
	
	
void ConfigMenu() {
	
	ConfigMenuIni:
	ClearScreen();
	
	printf("\n\n");
	printf(".==========================================.\n");
	printf("|      Monthly Payment Calculator 0.7      |\n");
	printf(".==========================================.\n");
	printf("|                                          |\n");

if (TimeDifferenceMODE == 0) {printf("| [1] Change prices for NEW students [OFF] |\n");}
if (TimeDifferenceMODE == 1) {printf("| [1] Change prices for NEW students [ON]  |\n");}

	printf("| [2] Change Variables                     |\n");
	printf("|                                          |\n");
	printf("| [7] Go Back                              |\n");
	printf("|                                          |\n");
	printf(".==========================================.\n\n");

	scanf("%d", &Options);

	switch(Options) {
		
		case 1:
			
			if (TimeDifferenceMODE == 0) {TimeDifferenceMODE = 1; goto ConfigMenuIni;}
			if (TimeDifferenceMODE == 1) {TimeDifferenceMODE = 0; goto ConfigMenuIni;}
			break;
		
		case 2:
		
			//CHANGE VARIABLES
			
			ChangePrices();
			SaveData();
			goto ConfigMenuIni;
			break;
			
		case 7:
			
			return;
			break;
			
		default:
		
			goto ConfigMenuIni;
			break;
	
	}

}
	
void WaitKey() {
	
	// Loop until a key is pressed
			
	do {
			
		input = getchar();
		
	} while (input == '\n'); // Ignore newline characters

	//printf("\n Key '%c' pressed. Program continues...\n", input);

	return;

}


// ================================= NOTES =======================================	
	
// TO DO
// =====

//* Que se guarde en el archivo TXT si se aplica el descuento o no.

//* Alerts for late or missed payments.

//* Generating monthly or yearly summary reports of total payments, discounts
//  applied, and other key metrics.

//* Providing filters to view payments by student, lesson type, market, 
//  or date range.

//* Options for each students (country, single, group, old or new, etc.) 
//  are saved in memory and automaticly loaded.

//--------------------------------------------------------------------------

//* Show 'payments.txt' entries in the program. Print entries on the screen.
//  USE fgets() and fputs(): These functions are used to read and write 
// strings to and from files, respectively.

//fgets() allows the programmer to read a line of text from a file.
//fputs() allows the programmer to write a string to a file.
//Understanding these functions is useful for working with text-based files.

//--------------------------------------------------------------------------

//* Open 'payments.txt' from the program.

//* Manage 'payments.txt' from the program. Delete/edit entries.

//  Ability to view and manage payment entries stored in payments.txt 
//  file directly from the program. This could include features like viewing the 
//  payment history, editing or deleting entries, and potentially generating 
//  reports.

// DONE
// ====

// 0.7

//* Que se guarde en el archivo TXT el número de clases.

// 0.6

//* Show the right currency for each 'payments.txt' entry.

//* Most GO BACK MENU bugs solved. User can exit right after producing
// a payment message and log without problems.

//* Variables added for US Payments.
//* English currency and USA payments added. Make options for the United 
// States market available. Differenciate prices in US dollars and create 
// new sub that deals with US payments.

//* DATE and TIME added in payment logs.
//* It is now possible to assign a different price for new students compared to long-standing students.
//* The program can differentiate between new students and long-standing students, and charge different rates for each.
//* Additional variables have been added as well. The 'Change Variables' section has been updated.
//* You can activate and deactivate this mode, which includes price differences between long-standing 
//  students and new students, from the Configuration menu.
//* SAVE and LOAD subfunctions UPDATED with new variables used for price 
//  differences between long-standing students and new students.

//  0.5
//* Adapt system to payments in ARS currency, in Argentinean Pesos. Add it as an option.
//* User can modify variables related to payments in ARS currency. 
//* MENU Improved in the CHANGE VARIABLES section.
//* Show receipt for ARG payments as done in Brazilian payments [OK].

//  0.4
//* Lines in 'payments.txt' are ADDED, APPENDED ['a'] instead of REWRITTEN ['w+'].
//* Create txt file with payments entries. Payments registry.

//  0.3
//* Variables such as SINGLE LESSON PRICE, GROUP LESSON PRICE and DISCOUNT
//  VALUE can be modified, saved and stored in memory.
//* General visuals improved.
//* Main Menu improved.

//  0.2
//* Generate receipt.[50%]
//* Add languages feature. Final messages in Spanish, English and Portuguese. [100%]
//* Don't show discount messages and information when there's NO discount applied. [100%]

//  0.1
//* Basic structure of the program created. First options and basic
//  functionalities developed.
