#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//structure
struct student{
char fName[30];
char lName[30];
int roll;
float marks;
char address[20];
};

//structure variable declaration
 struct student stds;
 
//functions declaration
int info();
int addStudent();
int displayRec();
int searchStudents();
int deleteRec();

//main function
int main()
{
       int choice;
//Menu      
         while(1){
    
printf("\nStudent Record Management System");
printf("\n_________________________________\n");
printf("\tMenu\n\n");
printf("\t^\n");
printf("<1> Add a new student\n");
printf("<2> Display Student records\n");
printf("<3> Search Students\n");
printf("<4> Delete record\n");
printf("<5> About\n");
printf("<6> Exit\n");
printf("\tv\n");
printf("\nYour key here: ");
scanf("%d",&choice);

//switch case
switch (choice)
{
case 1:
    addStudent();
    break;
case 2:
    displayRec();
    break;
    
case 3:
	searchStudents();
	break;
    	
case 4:
	deleteRec();
	break;
    		
case 5:
    info();
    break;
    
case 6:
    printf("Exiting");
    return 0;

default:
    system("cls");
    printf("Invalid");
}
}
}



//function to add Student
int addStudent()
{
	system("cls");
    char next;
    FILE *fadd;
    printf("\nAdd new records");
    printf("\n_______________\n");
    printf("\nEnter student details:\n");
    
	do{
		//opening file in append mode
   	fadd=fopen("studentrecs.txt","a");
        printf("\nFirst Name: ");
        scanf("%s",stds.fName);
      

        printf("Last Name: ");
        scanf("%s",stds.lName);
        

        printf("Roll No: ");
        scanf("%d",&stds.roll);
        

        printf("Marks: ");
        scanf("%f",&stds.marks);
         
		printf("Address: ");
        scanf("%s",stds.address);
        
    if(fadd==NULL)
    {
        printf("An error occured!");
        return 0;
    }
    else
    {
    	    printf("\nRecord added succesful.\n");
	}
        printf("\n______________\n");
        
        //write in file
        fwrite(&stds,sizeof(struct student),1,fadd);
        fclose(fadd);
        
		printf("\nDo you want to add another record?(y/n): ");
        scanf("%s",&next);

 
   }while(next=='y'||next=='Y');
system("cls");
}

//function to display records
int displayRec()
{
    system("cls");
    FILE *fdisplay;

    fdisplay=fopen("studentrecs.txt","r");

    printf("\nStudent Records\n");

    if(fdisplay==NULL)
    {
        printf("\nAn error occured\n");
        return 0;
    }
    else
    {
        printf("____________________\n");
        printf("\nStudent Details\n");
    }
    //reading and printing contents in console 
    while (fread(&stds,sizeof(struct student),1,fdisplay))
    {
        printf("\nName: %s %s",stds.fName,stds.lName);
        printf("\nRoll No: %d",stds.roll);
        printf("\nMarks: %f",stds.marks);
        printf("\nAddress: %s",stds.address);
        printf("\n_______________________\n");
    }
    fclose(fdisplay);
    getch();
    system("cls");
}


//function to search the records
int searchStudents()
{
	system("cls");
	int rn,found=0;
	FILE *fp;
	fp=fopen("studentrecs.txt","r");
	
	printf("\nSearch a student record");
	printf("\n_______________________\n");
	printf("\n\nEnter the roll no of student: ");
	scanf("%d",&rn);
	
	while (fread(&stds,sizeof(struct student),1,fp)>0)
	{
		//printing
	if(stds.roll==rn)
	{
		found=1;
		 printf("\nName: %s %s",stds.fName,stds.lName);
        printf("\nRoll No: %d",stds.roll);
        printf("\nMarks: %f",stds.marks);
        printf("\nAddress: %s",stds.address);
        printf("\n_______________________\n");

	   }
    }
	if(!found)
	{
		printf("\nCouldn't find!");
		
	}
	fclose(fp);
	getch();
}

//function to open About text
int info()
{
    system("cls");
    FILE *finfo;
    finfo=fopen("info.txt","r");
    if(finfo==NULL)
    {
        printf("Unable to open the file.");
        return 0;
    }
       char buffer[100];

    while (fscanf(finfo, "%s", buffer) != EOF) {
        printf("%s ", buffer);
    }
    printf("\n\n\n");
}

//function to delete the record
int deleteRec()
{
	system("cls");
	FILE *fp,*temp;
	int roll,found=0;
	char del,sure1,sure2;
	printf("\n\tDelete record");
	printf("\n\t_______________\n");
	printf("\n\npress 'D' to delete all the records\n");
	printf("press 's' to delete a particular record\n");
	printf("\n\tPress here: ");
	scanf("%s",&del);
	
	//delete whole record by opening file in write mod 
	if(del=='d'||del=='D')
	{
		printf("\nDelete all records?(y/n): ");
		scanf("%s",&sure1);
		   if(sure1=='y'||sure1=='Y')
		     {
		        fp=fopen("studentrecs.txt","w");
		        if(fp==NULL)
		            {
		 	         printf("\nCouldn't Delete records!");
		 	         return 0;
			        }
			    else{
			 	     printf("\nAll items deleted\n");
			        }	
			    fclose(fp);
		    }
		    
		    //cancel delete
		  else if(sure1=='n'||sure1=='N')
		    {
			 return 0;
		    }
		  else 
		     printf("\nInvalid!\n");
		
	}
	
	//delete a particular record
	else if(del=='s'||del=='S')
	 {
	   printf("\nenter the roll no of student: ");	
	   scanf("%d",&roll);
       
       	printf("\nDelete this record permanently?(y/n): ");
       	scanf("%s",&sure2);
       	//permanently delete
       	  if(sure2=='y'||sure2=='Y')
       	    {
       	      
       	  	fp=fopen("studentrecs.txt","r");
       	  	
       	  	  if(fp==NULL)
       	  	  {printf("\nAn error occured!\n");
       	  	  return 0;
				   }
				   
       	  	temp=fopen("temp.txt","w");
       	  	
       	  	  if(temp==NULL)
       	  	  {printf("\nError occured creating a temp file!\n");
       	  	  return 0;
				   }

                    //store the contents in temporary file skipping the contents to be deleted  			
			      while(fread(&stds,sizeof(struct student),1,fp))
				    {
				    	if(stds.roll==roll)
                           {
                           	found=1;
						   }	   
						else 
						{
							fwrite(&stds,sizeof(struct student),1,temp);
						   }   
					}
					fclose(fp);
					fclose(temp);
			 }
			    
			    if(!found)
			    {
			    	printf("\nRecord couldn't be found\n");
			    	
				}
				//delete original file and rename new temporary file containing rest of data
				if(found)
				{
					remove("studentrecs.txt");
					rename("temp.txt","studentrecs.txt");
					printf("\n\tRecord deleted successfully\n");
				}
				
		//cancel delete		
		  else if(sure2=='n'||sure2=='N')
		    {
		    	return 0;
				 }	 
			else
			{
				printf("\nInvalid!\n");
				 }	 
	   
  	
	 }
}