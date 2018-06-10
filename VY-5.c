/*
	Arithmetic Calculation using Stack

										*/
										
#define SIZE 127
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  Stract of stack for CHAR values  */
typedef struct STACKCH
{
	char operations[SIZE];
	int top; 
}STACKCH;

/*  Initializes the CHAR stack  */
void initializeCH( STACKCH* stack )
{
	stack->top=0;
}

/* Checks whether the CHAR stack is empty  */
int isEmptyCH( STACKCH* stack )
{
	if( stack->top==0 )
		return 1;
	else{
		return 0;		
	}
}

/*  Checks whether the CHAR stack is full  */
int isFullCH( STACKCH *stack )
{
	if( stack->top==SIZE )
		return 1;
	else
		return 0;
}

/* Pushs a CHAR to Stack  */
void pushCH( STACKCH* stack , char ch )
{
	if( isFullCH(stack) )
		printf("Stack is full!");
	else{
		stack->operations[stack->top]=ch ;
		stack->top++ ;
	}		
}

/* Pops a CHAR from Stack  */
char popCH( STACKCH* stack )
{
	if( isEmptyCH(stack) )
		printf("Stack is empty! \n");
	else{
		stack->top-- ;
		return stack->operations[stack->top] ;
	}	
}

/*  Prints the Stack that contains CHAR values */
void printStackCH(STACKCH* stack){
	int i ;
	printf("Stack:");
	if(!isEmptyCH(stack)){
		for(i=0;i<stack->top;i++)
		printf("%c",stack->operations[i]) ;
	printf("\n");	
	}else
		printf("(NULL)\n");

}

/*  Stract of stack for DOUBLE values  */
typedef struct STACKD
{
	double numbers[SIZE];
	int top; 
}STACKD;

/*  Initializes the DOUBLE stack  */
void initializeD( STACKD* stack )
{
	stack->top=0;
}

/* Checks whether the CHAR stack is empty  */
int isEmptyD( STACKD* stack )
{
	if( stack->top==0 )
		return 1;
	else{
		return 0;		
	}
}

/*  Checks whether the DOUBLE stack is full  */
int isFullD( STACKD *stack )
{
	if( stack->top==SIZE )
		return 1;
	else
		return 0;
}

/* Pushs a DOUBLE to Stack  */
void pushD( STACKD* stack , double num )
{
	if( isFullD(stack) )
		printf("Stack is full!");
	else{
		stack->numbers[stack->top]=num ;
		stack->top++ ;
	}		
}

/* Pops a DOUBLE to Stack  */
double popD( STACKD* stack )
{
	if( isEmptyD(stack) )
		printf("Stack is empty! \n");
	else{
		stack->top-- ;
		return stack->numbers[stack->top] ;
	}	
}

/*  Prints the Stack that contains DOUBLE values */
void printStackD(STACKD* stack){
	int i ;
	printf("Stack:");
	if(!isEmptyD(stack)){
		for(i=0;i<stack->top;i++)
		printf("%.2lf ",stack->numbers[i]) ;
	printf("\n");	
	}else
		printf("(NULL)\n");

}

/*  Gives the priority for operations: '+' , '-' , '*' , '/'     */
int findPriority(char operation){
	if( operation =='+'  || operation =='-' )
		return 1 ;
	if( operation =='*'  || operation =='/' )
		return 0 ;		//   '*' and '/'  operations  are prior 
}



/* Converts the Infix string to Postfix string  */ 
char* infixToPostfix(char* infix,int N,STACKCH *stack){
	char *postfix;
	int i,j=0 ;
	char tmp;
	postfix=(char*) calloc( SIZE , sizeof(char) ) ;

	while(i<N){
		
		if(infix[i]==' ');
		
		else if( isdigit( infix[i] ) || isalpha( infix[i] ) ) { // if it is a value or variable
			postfix[j++]=infix[i++]; // add it to postfix 
			while( isdigit(infix[i]) || infix[i]=='.') // For values which contain more than one character  like '111.52'
				postfix[j++]=infix[i++];
			
			postfix[j++]=' ' ;
			printf("Postfix:%s",postfix); // print postfix	
			printStackCH(stack) ; // print stack 
			
		}else 	//  if it is an operation ( + - * / )
		{
			if( isEmptyCH(stack) || ( stack->operations[stack->top - 1] =='(' ) ){ // If stack is empty
				pushCH(stack,infix[i]); 											// push it to the stack
				printf("Postfix:%s",postfix);
				printStackCH(stack) ;					
			}
			else if (infix[i] == '+' || infix[i] == '-' ){  // if it is '+' or '-'
				postfix[j++]= popCH(stack); 				// add it to postfix 
				postfix[j++]=' ' ;
				while(findPriority(stack->operations[stack->top - 1] ) < 1)	{ //  '*' and '/' are popped from stack	 as they have priority over '+' and '-'
					postfix[j++]=popCH(stack);									// and added to postfix
					postfix[j++]=' ' ;
					}
				pushCH(stack,infix[i]);	        // '+' or '-' pushed to stack
				printf("Postfix:%s",postfix);
				printStackCH(stack) ;	
			}
			else if (infix[i] == '*' || infix[i] == '/'){  // if it is '*' or '/'

					while( isEmptyCH(stack)==0 && findPriority(stack->operations[stack->top - 1] ) == 0){ // if are there any '*' or '/' at stack			
					postfix[j++]=popCH(stack);																// pop and add them to postfix 
					postfix[j++]=' ' ;
					printf("Postfix:%s",postfix);
					printStackCH(stack) ;
					}
					pushCH(stack,infix[i]);	// push '*' or '/' to stack
					printf("Postfix:%s",postfix);
					printStackCH(stack) ;							
				}	

			else if(infix[i] == '('){ 	// if it is '('
				pushCH(stack,infix[i]); // just push it to stack
				printf("Postfix:%s",postfix);
				printStackCH(stack) ;
			}
			else if (infix[i] == ')'){ // if it is ')'	
				tmp=popCH(stack) ;		
				while( tmp!= '(' ){		// pop operations from stack until ')' popped
					postfix[j++]=tmp;	// add them to postfix
					postfix[j++]=' ' ;
					tmp=popCH(stack) ;	
				}
			}
			else{
				printf("Invalid input\n" );	
				exit(1) ;
			}
		
		}
	i++ ;
	}
	
	while(isEmptyCH(stack) == 0){  // The rest of the stack values are added to postfix
		postfix[j++]=popCH(stack);
		postfix[j++]=' ' ;
	}
	printf("Postfix:%s",postfix);
	printStackCH(stack) ;
	postfix[j]='\0' ;
	
	return postfix;
} 
/* This function takes a postfix string , a stack of doubles and
	 variables'(alphabets) current values then solves postfix string 
	 and returns the result by using several stack functions
	 															*/
double solvePostfix(char* postfix , int size , STACKD* stack , double* variables){
	int i,j=0 ;
	char temp[SIZE];
	double number1,number2;
	
	while(i<size){
		if(postfix[i] ==' '); // if its space then do nothing.
		else if( isdigit(postfix[i]) ){  // if it is a digit or '.' (for double values)
			while( isdigit(postfix[i]) || postfix[i] == '.' ){ // For more than one character values like '111.52'
				temp[j++]=postfix[i] ; // save them to temp array.
				i++ ;
			}	
			sscanf( temp, "%lf" , &number1 );	// takes double value from "temp" string 
			pushD(stack , number1 ); // push it to stack
			printStackD(stack) ; // print stack.
			j=0;
		}
		else if ( isalpha(postfix[i]) ){ // if it is a variable
			if(variables[postfix[i] - 'a']=='0.0'){ // if user gives unused value then  
				printf("Invalid Input! %c must be declared first!\n",postfix[i]); // gives an error as wrong input.
				exit(1) ;
			}				
			pushD(stack , variables[postfix[i] - 'a'] ) ; // push variables value to stack
			printStackD(stack) ; // print stack.
		}
		else{
				if( postfix[i]== '+' || postfix[i]== '-' || postfix[i]== '*' || postfix[i]== '/' ){ // if it is an operation
				number2=popD(stack) ; // As last in first out in a stack  pops second value from stack first then
				number1=popD(stack) ; // pops first value from stack
				
				switch(postfix[i]){ // Process operations
					
					case '+' : 
						number1 = number1 + number2 ;
						break;
					case '-' :
						number1 = number1 - number2 ;
						break;
					case '*' :
						number1 = number1 * number2 ;
						break;
					case '/' :
						number1 = number1 / number2 ;
						break;			
			    }
			    
			    pushD(stack , number1 ); // push the current result to stack
			    printStackD(stack) ; // print stack.
			}
		}
		i++ ;
	}
	return popD(stack) ; // return final result
}
/*
	Main function takes inputs from "input.txt" file. It
	converts infix inputs to postfixs by using several stack functions then
	solves postfixs before store them in a double array which called variables. 
													*/
int main() {
	STACKCH charStack;
	STACKD doubleStack;
	FILE *fi;
	char equation[SIZE] ;
	char rightsideOfEquation[SIZE] ;
	char *postfix ;
	int infixSize ,i ;
	double variables[26] ;
	
	initializeCH(&charStack) ; // Initializing stacks
	initializeD(&doubleStack) ;
	
	for(i=0;i<26;i++)
		variables[i] = '0.0' ;   // Assign variables null so that determine if they used .
		
	printf("File opening: input.txt\n\n");
	fi=fopen( "input.txt" , "r" ); // Takes input from "input.txt" file.
	if(!fi){
		printf("File could not open!\n");
		exit(1);
	}
	
	postfix=(char*) calloc( SIZE , sizeof(char) ) ;
	while(fgets(equation,SIZE,fi)){ // progress until inputs finished.
		
		infixSize= sprintf( rightsideOfEquation ,"%s", &equation[4] );  // takes string after "=" symbol 
		fflush(stdout);
		printf("Infix: %s\t  ",equation); // prints input
		printf("\n") ;
		postfix = infixToPostfix( rightsideOfEquation , infixSize-2 , &charStack ) ; // converts to postfix
		printf("Final Postfix: %s\n\nThe above Postfix is being solving ... \n",postfix);  // prints postfix
		variables[equation[0] - 'a'] = solvePostfix( postfix , infixSize-1 , &doubleStack , variables ) ; // solves postfix and stores the answers 
		printf("\n--->%c = %.2lf \n\n",equation[0],variables[equation[0] - 'a'] ); // prints  current result
		
	}
	puts("--TOTAL RESULTS--");
		for(i=0;i<26;i++){
			if(variables[i]!='0.0')								// if an alphabet variable used 
				printf(" %c = %.2lf \t \n",i+'a' ,variables[i] );		 // prints them
		}

	fclose(fi);
	free(postfix);
	
	return 0;
}
