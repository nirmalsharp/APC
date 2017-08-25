#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "skel.h"

/*flags*/
int add_flag = 0;
int sub_flag = 0;
int mul_flag = 0;
int dec_flag = 0;
int str_len = 0;
int str_lenA = 0;
int minus_flag = 0;
int set_flag = 0;

void seperate(char *buffer, d_list **expA, d_list **evaB, d_list **result)
{
    /*initials*/
    int i = 0;
    int lenA = 0;
    int lenB = 0;
    char buff_B[10000]; // to store values
    char buff_A[10000];
    char zero[10000]; // to append zeros
    char zeros_m[10000];
    char string[7];
    int value = 0; // convert string to value
    char temp_buff[100000];


    /*this will setting the tails to three linked lists*/
    d_list *tailA = NULL;
    d_list *tailB = NULL;
    d_list *tailC = NULL;

    /*Iam taking files to store the inputs*/
    FILE *fp , *fp1;
    fp = fopen("operandA.txt", "w+"); // w+ mode for writing and reading
    fp1 = fopen("operandB.txt", "w+"); // w+ mode for writing and reading

    /*to tokenize operands*/
    char *varA;
    char *varB;

    //to check which operation to perform
    for (i = 0 ; buffer[i] != '\0'; i++)
    {
	if (buffer[i] == '+')
	    add_flag++;

	if (buffer[i] == '-')
	    sub_flag++;

	if (buffer[i] == '*')
	    mul_flag++;
	
	if (buffer[i] == '.')
	    dec_flag++;


    }

       /**if the flag sets then slice it*/

    if (add_flag == 1)
    {
	varB = strchr(buffer, '+');
	strcpy(buff_B , varB + 1);
	lenB = strlen(buff_B);
	printf("length of B is %d\n",lenB);

	varA = strtok(buffer, "+");
	lenA = strlen(varA);
	printf("length of A is %d\n",lenA);

	/**according to length we will append zeros**/
	if (lenA > lenB)
	{
	    //so need to apppend zeros in B
	    for (i = 0; i < (lenA - lenB); i++)
	    {
		zero[i] = '0';

	    }
	    strcat(zero, buff_B);
	    /***to clear the buffer and store it***/
	    memset(buff_B, '0', sizeof(buff_B));
	    strcpy(buff_B, zero);
	    puts(buff_B);

	}

	else if (lenB > lenA)
	{
	    for (i = 0; i < (lenB - lenA); i++)
	    {
		zero[i] = '0';

	    }
	    strcat(zero, varA);
	    /***to clear the buffer and store it***/
	    strcpy(varA, zero);
	    puts(varA);
	}


	/***write it to file**/
	//this is for convineince

	fwrite(varA, 1, strlen(varA), fp); 
	fwrite(buff_B, 1, strlen(buff_B), fp1);

	/*****put it in list for 6 digits per node*****/

	/*set cursor to first position*/
	fseek(fp, 0L, SEEK_SET);
	/*delete list items*/
	//delete_list(expA);
	//delete_list(&expB);

	while ((fgets(string , 7, fp)) != NULL)
	{
	    //puts(string);

	    /*we need to put inside list1*/
	    str_len = strlen(string);
	    if(str_len < 6)
	    {
		str_len = strlen(string);
	    }

	    value  = atoi(string);
	    //printf("%d\n", value);
	    insert_last(expA, &tailA, value);

	    /*clear the string*/
	    memset(string, '0', sizeof(string));


	}
	/*to check */
	printf("linked list 1:\n");
	print_list(expA, &tailA);


	/*set cursor to first position*/
	fseek(fp1, 0L, SEEK_SET);
	/*delete list items*/
	//delete_list(evaB);

	while ((fgets(string , 7, fp1)) != NULL)
	{
	    //puts(string);

	    /*we need to put inside list1*/

	    value  = atoi(string);
	    //printf("%d\n", value);
	    insert_last(evaB, &tailB, value);

	    /*clear the string*/
	    memset(string, '0', sizeof(string));


	}
	/*to check */
	printf("linked list 2:\n");
	print_list(evaB, &tailB);

	/*evaluate sum*/
	sum(expA, evaB, result, &tailA, &tailB, &tailC);



    }

    if (sub_flag == 1)   
    {
	varB = strchr(buffer, '-');
	strcpy(buff_B , varB + 1);
	lenB = strlen(buff_B);
	printf("length of B is %d\n",lenB);

	varA = strtok(buffer, "-");
	lenA = strlen(varA);
	printf("length of A is %d\n",lenA);

	/******check the size******/
	if (lenB > lenA)
	{
	    minus_flag = 1;
	    strcpy(temp_buff, buff_B);
	    strcpy(buff_B, varA);
	    strcpy(varA, temp_buff);
	    lenB = strlen(buff_B);
	    lenA = strlen(varA);
	}

	/******check for same size****/
	if (lenA == lenB)
	{
	    if (varA[0] < buff_B[0])
	    {
		minus_flag = 1;
		strcpy(temp_buff, buff_B);
		strcpy(buff_B, varA);
		strcpy(varA, temp_buff);
		lenB = strlen(buff_B);
		lenA = strlen(varA);
	    }
	}



	/**according to length we will append zeros**/
	if (lenA > lenB)
	{
	    //so need to apppend zeros in B
	    for (i = 0; i < (lenA - lenB); i++)
	    {
		zero[i] = '0';

	    }
	    strcat(zero, buff_B);
	    /***to clear the buffer and store it***/
	    memset(buff_B, '0', sizeof(buff_B));
	    strcpy(buff_B, zero);
	    puts(buff_B);

	}

	else if (lenB > lenA)
	{

	    for (i = 0; i < (lenB - lenA); i++)
	    {
		zero[i] = '0';

	    }
	    strcat(zero, varA);
	    /***to clear the buffer and store it***/
	    strcpy(varA, zero);
	    puts(varA);
	}


	/***write it to file**/
	//this is for convineince

	fwrite(varA, 1, strlen(varA), fp); 
	fwrite(buff_B, 1, strlen(buff_B), fp1);

	/*****put it in list for 6 digits per node*****/

	/*set cursor to first position*/
	fseek(fp, 0L, SEEK_SET);
	/*delete list items*/
	//delete_list(expA);
	//delete_list(&expB);

	while ((fgets(string , 7, fp)) != NULL)
	{
	    //puts(string);

	    /*we need to put inside list1*/
	    str_len = strlen(string);
	    if(str_len < 6)
	    {
		str_len = strlen(string);
	    }

	    value  = atoi(string);
	    //printf("%d\n", value);
	    insert_last(expA, &tailA, value);

	    /*clear the string*/
	    memset(string, '0', sizeof(string));


	}
	/*to check */
	printf("linked list 1:\n");
	print_list(expA, &tailA);


	/*set cursor to first position*/
	fseek(fp1, 0L, SEEK_SET);
	/*delete list items*/
	//delete_list(evaB);

	while ((fgets(string , 7, fp1)) != NULL)
	{
	    //puts(string);

	    /*we need to put inside list1*/

	    value  = atoi(string);
	    //printf("%d\n", value);
	    insert_last(evaB, &tailB, value);

	    /*clear the string*/
	    memset(string, '0', sizeof(string));


	}
	/*to check */
	printf("linked list 2:\n");
	print_list(evaB, &tailB);

	/*function for difference*/

	subtract(expA, evaB, result, &tailA, &tailB, &tailC);




    }

    /*****multiplication**/

    if (mul_flag == 1)
    {


	varB = strchr(buffer, '*');
	strcpy(buff_B , varB + 1);
	lenB = strlen(buff_B);
	printf("length of B is %d\n",lenB);

	varA = strtok(buffer, "*");
	lenA = strlen(varA);
	printf("length of A is %d\n",lenA);

	/**according to length we will append zeros**/
	if ((lenB % 5) != 0)
	{
	    //so need to apppend zeros in B
	    for (i = 0; i < (5 - (lenB % 5)); i++)
	    {
		zero[i] = '0';

	    }
	    strcat(zero, buff_B);
	    /***to clear the buffer and store it***/
	    memset(buff_B, '0', sizeof(buff_B));
	    strcpy(buff_B, zero);
	    puts(buff_B);

	}

	if ((lenA % 5) != 0)
	{
	    for (i = 0; i < (5 -(lenA % 5)); i++)
	    {
		zeros_m[i] = '0';

	    }
	    strcat(zeros_m, varA);
	    /***to clear the buffer and store it***/
	    strcpy(varA, zeros_m);
	    puts(varA);
	}







	/***write it to file**/
	//this is for convineince

	fwrite(varA, 1, strlen(varA), fp); 
	fwrite(buff_B, 1, strlen(buff_B), fp1);

	/*****put it in list for 6 digits per node*****/

	/*set cursor to first position*/
	fseek(fp, 0L, SEEK_SET);
	/*delete list items*/
	//delete_list(expA);
	//delete_list(&expB);

	while ((fgets(string , 6, fp)) != NULL)
	{
	    //puts(string);

	    /*we need to put inside list1*/
	    str_lenA = strlen(string);
	    if(str_lenA < 5)
	    {
		str_lenA = strlen(string);
	    }


	    value  = atoi(string);
	    //printf("%d\n", value);
	    insert_last(expA, &tailA, value);

	    /*clear the string*/
	    memset(string, '0', sizeof(string));


	}
	/*to check */
	printf("linked list 1:\n");
	print_list(expA, &tailA);


	/*set cursor to first position*/
	fseek(fp1, 0L, SEEK_SET);
	/*delete list items*/
	//delete_list(evaB);

	while ((fgets(string , 6, fp1)) != NULL)
	{
	    //puts(string);

	    /*we need to put inside list1*/
	    str_len = strlen(string);
	    if(str_len < 5)
	    {
		str_len = strlen(string);
	    }


	    value  = atoi(string);
	    //printf("%d\n", value);
	    insert_last(evaB, &tailB, value);

	    /*clear the string*/
	    memset(string, '0', sizeof(string));


	}
	/*to check */
	printf("linked list 2:\n");
	print_list(evaB, &tailB);

	/***to do multiplication operation***/
	multiply(expA, evaB, result, &tailA, &tailB, &tailC);


    }



    fclose(fp);
    fclose(fp1);


}

/*function for multiplication*/
void multiply(d_list **expA, d_list **evaB, d_list **result, d_list **tailA, d_list **tailB, d_list **tailC)
{

    d_list *new = NULL;
    d_list *tailD = NULL;
    d_list *ptrA = *tailA;
    d_list *ptrB = *tailB;
    d_list *new1  = NULL;
    d_list *tailE = NULL;




    unsigned long long val = 0;
    unsigned int carry = 0;
    int c_flag = 0;
    int count = 0;
    int i = 0;



    /***this will do multiplication***/
    while (ptrB != NULL)
    {
	ptrA = *tailA;
	carry = 0;
	i = 0;

	while(ptrA != NULL)
	{

	    val = ((ptrA -> data) * (ptrB -> data)) + carry;
	    if (numl(val) > 5)
	    {
		carry = val / 100000;
		val = val % 100000;


	    }
	    else
	    {
		carry = 0;
	    }



	    insert_first(&new, &tailD, val);

	    if (ptrA -> prev == NULL)
	    {
		if (carry != 0)
		{
		    insert_first(&new,&tailD, carry);
		}
	    }
	    //printf("---%d----\n", tailD -> data);


	    //print_list(&new, &tailD);



	    //ptrC = ptrC -> prev; 
	    ptrA = ptrA -> prev;




	}
	new1 = new_sum(&new, &new1, &tailD, &tailE);
	new = NULL;
	ptrB = ptrB -> prev;



    }

    printf("***********\n");
    printf("multiply result :\n");
    system("clear");




    print_list(&new1, &tailD);
    printf("****************\n");





}

d_list *new_sum(d_list **expA, d_list **evaB, d_list **tailB, d_list **tailD)
{
    d_list *res = 0;
    d_list *l_tail = 0;
    int get = 0;
    int get1 = 0;
    int carry_flag = 0;
    int val = 0;
    int power = 0;
    int zero = 0;
    int i = 0;
    static int t_flag = 0;

    d_list *tempA = *expA;
    d_list *ptrA;
    d_list *ptrB;

    d_list *tempB = *evaB;




    if (*evaB == NULL)
    {
	//print_list(expA, tailD);
	return *expA;
    }

    else
    {
	t_flag++;
	printf("list1 :");
	print_list(expA, tailB);

	printf("list2 :");
	print_list(evaB, tailD);

	for (i = 0; i < t_flag; i++)
	{	    
	    insert_l(expA, 0);
	}
	get1 = get_count(*evaB);
	get = get_count(*expA);


	printf("get is %d\n", get);
	printf("getA is %d\n", get1);

	zero = get - get1;
	//printf("%d\n", zero);

	for (i = 0; i < zero; i++)
	{
	    insert_f(evaB, 0);
	}

	if (zero < 0)
	{
	    zero = zero * (-1);


	    for (i = 0; i < zero; i++)
	    {
		insert_f(expA, 0);
	    }

	}









	printf("***********\n");
	print_list(evaB, tailB);
	printf("***********\n");

	printf("***********\n");
	print_list(expA, tailB);
	printf("***********\n");


	tempA = *expA;
	tempB = *evaB;



	/***go to the last node****/
	while (tempA != NULL )
	{
	    ptrA = tempA;
	    //printf("data is %d\n", ptrA -> data);

	    tempA = tempA -> next;
	}

	/******go to the last**/ 
	while (tempB != NULL )
	{
	    ptrB = tempB;
	    //printf("data is %d\n", ptrB -> data);
	    tempB = tempB -> next;
	}



	//printf("last data is %d\n", ptrB -> data);
	while (ptrA != NULL && ptrB != NULL)
	{

	    if (carry_flag == 0)
	    {
		val = (ptrA -> data) + (ptrB -> data);
	    }
	    else
	    {
		val = (ptrA -> data) + (ptrB -> data);
		val = val + 1;
	    }




	    /*adding*/

	    /*this have to done in first time only*/

	    if (numl(val) > 5)
	    {
		carry_flag = 1;
		power = pow(10, 5);
		//printf("power part2 is %d\n", power);
		val = val % power;
		insert_f(&res, val);



	    }
	    else
	    {
		carry_flag = 0;
		insert_f(&res, val);

	    }



	    ptrA = ptrA -> prev;
	    ptrB = ptrB -> prev;

	    /***check the last node also***/
	    if (ptrA  == NULL)
	    {
		if (carry_flag == 1)
		    insert_f(&res , 1);
	    }



	    //return res;




	}
	printf("res: \n");
	print_list(&res, tailD);
	return res;









    }





}

/*function for sum*/
d_list *sum(d_list **expA, d_list **evaB, d_list **result, d_list **tailA, d_list **tailB, d_list **tailC)
{
    /*first case if only one node is present*/

    d_list *ptrA = *tailA;
    d_list *ptrB = *tailB;
    int length = 0;
    int i;
    int val = 0;
    int power;
    int carry_flag = 0;

    if (ptrA -> prev == NULL)
    {
	//printf("only one node is present\n");

	val = (ptrA -> data) + (ptrB -> data);
	if ((ptrA -> data) > (ptrB -> data))
	{
	    length = numl(ptrA -> data);
	    //printf("length : %d\n", length);
	}
	else
	{
	    length = numl(ptrB -> data);
	    //printf("length : %d\n", length);

	}
	insert_first(result, tailC, val);
	
	


	//printf("linked list 3:\n");
	print_res(result, tailC, length);



    }

    else
    {
	/*if there is more nodes*/
	//printf("last node length is %d\n", str_len);

	i = 0;

	while (ptrA != NULL && ptrB != NULL)
	{

	    if (carry_flag == 0)
	    {
		val = (ptrA -> data) + (ptrB -> data);
	    }
	    else
	    {
		val = (ptrA -> data) + (ptrB -> data);
		val = val + 1;
	    }




	    /*adding*/

	    /*this have to done in first time only*/
	    if (i == 0)
	    {

		if (numl(val) > str_len)
		{
		    carry_flag = 1;
		    power = pow(10, str_len);
		    //printf("power part1 is %d\n", power);
		    val = (val % power);
		    insert_first(result, tailC, val);

		}
		else
		{
		    carry_flag = 0;
		    insert_first(result, tailC, val);


		}

	    }

	    if (i != 0)
	    {
		if (numl(val) > 6)
		{
		    carry_flag = 1;
		    power = pow(10, 6);
		    //printf("power part2 is %d\n", power);
		    val = val % power;
		    insert_first(result, tailC, val);



		}
		else
		{
		    carry_flag = 0;
		    insert_first(result, tailC, val);

		}
	    }


	    ptrA = ptrA -> prev;
	    ptrB = ptrB -> prev;

	    /***check the last node also***/
	    if (ptrA  == NULL)
	    {
		if (carry_flag == 1)
		    insert_first(result, tailC, 1);

		}

	    i++;

	}





	//printf("linked list 3:\n");
	print_res(result, tailC, length);


    }

    return *result;




}


void subtract(d_list **expA, d_list **evaB, d_list **result, d_list **tailA, d_list **tailB, d_list **tailC)
{
    /*first case if only one node is present*/

    int val = 0;
    int length = 0;
    int borrow_flag = 0;
    int orginal_val = 0;
    int first_d = 0;
    int i = 0;

    d_list *ptrA = *tailA;
    d_list *ptrB = *tailB;

    if (ptrA -> prev == NULL)
    {

	printf("only one node is present\n");
	val = (ptrA -> data) - (ptrB -> data);
	if ((ptrA -> data) > (ptrB -> data))
	{
	    length = numl(ptrA -> data);
	    printf("length : %d\n", length);
	}
	else
	{
	    length = numl(ptrB -> data);
	    printf("length : %d\n", length);

	}
	insert_first(result, tailC, val);

	printf("linked list 3:\n");
	print_res(result, tailC, length);



    }
    else

    {
	printf("last node length is %d\n", str_len);

	while(ptrA != NULL && ptrB != NULL)
	{

	    /*****last node modification****/
	    if (i == 0)
	    {
		val = (ptrA -> data) - (ptrB -> data);
		if (val < 0)
		{
		    borrow_flag = 1;
		    orginal_val = pow(10, str_len) +  val;
		    //printf("---%d----\n", orginal_val);
		    insert_first(result, tailC, orginal_val);


		}
		else
		{
		    borrow_flag = 0;
		    orginal_val = val;
		    //printf("---%d----\n", orginal_val);

		    insert_first(result, tailC, orginal_val);

		}

	    }

	    if (i != 0)
	    {
		val = (ptrA -> data) - (ptrB -> data);

		/*********borrow flag exists means****/
		if (borrow_flag == 1)
		{
		    if (val < 0)
		    {
			val = val + 1;
		    }
		    else
		    {
			val = val - 1;
		    }
		}

		else
		{
		    val = val;
		}

		if (val < 0)
		{
		    borrow_flag = 1;
		    orginal_val = pow(10, 6) +  val;
		    //printf("---%d----\n", orginal_val);
		    insert_first(result, tailC, orginal_val);

		}
		else
		{
		    borrow_flag = 0;
		    orginal_val = val;
		    //printf("---%d----\n", orginal_val);
		    insert_first(result, tailC, orginal_val);


		}
	    }






	    i++;
	    ptrA = ptrA -> prev;
	    ptrB = ptrB -> prev;



	}


	print_res(result, tailC, length);



	//print_list(result, tailC);




    }


}



void print_res(d_list **head, d_list **tail, int length)
{
    int i = 0;
    //system("clear");
    /***this will print according to flags*****/
    if (add_flag == 1)
    {
	printf("result of addition is \n");
    }
    if (sub_flag == 1)
    {
	printf("result of subtract is \n");
    }
    if (minus_flag == 1)
    {
	printf("-");
    }

    /*************************/

    if (length == 0)
    {

	if (*head != NULL)
	{
	    d_list *ptr = *head;

	    while (ptr  != NULL)
	    {
		/**tricky process here**/

		if (i == 0)
		{
		    printf("%d", ptr -> data);
		}

		if (i != 0)
		{
		    if (ptr -> next == NULL)
		    {
			if (numl(ptr -> data) < str_len)
			{
			    print_zeros(str_len - numl(ptr -> data));
			    printf("%d", ptr -> data);
			}
			else
			{
			    printf("%d", ptr -> data);
			}
			//ptr = ptr -> next;
		    }	


		    else
		    {

			if (numl(ptr -> data)  < 6)
			{
			    print_zeros(6 - numl(ptr -> data));
			    printf("%d", ptr -> data);

			}
			else
			{
			    printf("%d", ptr -> data);
			}
		    }

		}


		/*if (ptr -> next == NULL)
		  {
		  if (numl(ptr -> data) < str_len)
		  {
		  print_zeros(str_len - numl(ptr -> data));
		  printf("%d\n", ptr -> data);
		  }
		  else
		  {
		  printf("%d\n", ptr -> data);
		  }
		//ptr = ptr -> next;
		}*/



		ptr = ptr -> next;


		i++;



	    }

	}
    }
    else if( length != 0)
    { if (*head != NULL)
	{
	    d_list *ptr = *head;

	    while (ptr  != NULL)
	    {
		printf("%d", ptr -> data);
		ptr = ptr -> next;
	    }

	}
    }



    /*function check no items*/
    else
    {
	printf("NO items in the list\n");
    }
    printf("\n");

}






/*find length of number*/


int numl(int n)
{
    if (n == 0)
	return 1;
    return floor(log10 (abs(n))) + 1;
}

/*function to print zeros*/
int print_zeros(int count)
{
    int i = 0;
    for (i = 0; i < count; i++)
    {
	printf("0");
    }
}

int get_first(int val)
{
    if (val < 10)
    {
	return val;
    }
    while (val >= 10)
    {
	val = val/ 10;
    }
    return val;

}


