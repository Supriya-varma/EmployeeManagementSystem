#define _CRT_SECURE_NO_WARRNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

 struct Employee
  {
     char Employee_Name[40];
     int Employee_Age;
     char Employee_Designation[40];
     float Employee_Salary;
 };

 void Flush()
 {
    int c = 0;

    while ((c == getchar()) != '\n' && c != EOF)
    { }
 }

void main()
{
   FILE *EmployeeFile;
   FILE *EmployeeFileTemp;

   char userChoice;
   char nextChoice;

   struct Employee Emp;
   char EmployeeName[40];

   long int sizeOfEmployeeRecord;
   const char* fileName = "EMPLOYEE.DAT";

   EmployeeFile = fopen("fileName", "rb+");                   //rb+ => read and write binary mode

   if (EmployeeFile == NULL)
   {
      EmployeeFile = fopen("fileName", "wb+");

      if (EmployeeFile == NULL)
      {
         printf("Unable to open %s file!\n", fileName);
         exit(1);
      }
  
   }
   
   sizeOfEmployeeRecord = sizeof(Emp);

   while (1)
   {
      printf("\n----------------------------------------------\n");

      printf("1. Add new employee\n");
      printf("2. Update employee\n");
      printf("3. Delete employee\n");
      printf("4. Print All employee Details\n");
      printf("5. Exit\n");
      fflush(stdin);

      printf("\nEnter an operation of your choice : ");
      scanf("\n%c",&userChoice);

      printf("\n----------------------------------------------\n");

      switch (userChoice)
      {
      
      case '1':
         fseek(EmployeeFile, 0, SEEK_END);
         nextChoice = 'y';
        
         while (nextChoice == 'y')
         {
            //Flush();
            fflush(stdin);
            printf("\n----------------------------------------------\n");

            printf("Add Employee's name : ");
            scanf("%39s", &Emp.Employee_Name);

            printf("Add Employee's age : ");
            scanf("%d", &Emp.Employee_Age);

            printf("Add Employee's designation : "); 
            scanf("%39s", &Emp.Employee_Designation);

            printf("Add Employee's salary : ");
            scanf("%f", &Emp.Employee_Salary);

            fwrite(&Emp, sizeOfEmployeeRecord, 1, EmployeeFile);

             printf("\n%s has been added as a new employee!", Emp.Employee_Name);

            printf("\nWould you like to add a new record (y/n) ?");
            fflush(stdin);
            scanf("\n%c", &nextChoice); 

            printf("\n----------------------------------------------\n");         
         }
         
         break;
      
      case '2':
         nextChoice = 'y';

         while (nextChoice == 'y')
         {
            fflush(stdin);
             printf("\n----------------------------------------------\n");

            printf("Enter the Employee name to modify : ");
            scanf("%39s", &EmployeeName);

            //rewind(EmployeeFile);
            fseek(EmployeeFile, 0L, SEEK_SET);

            while (fread(&Emp, sizeOfEmployeeRecord, 1, EmployeeFile) == 1)
            {
               if (strcmp(Emp.Employee_Name, EmployeeName) == 0)
               {
                  printf("Change %s name : ", EmployeeName);
                  scanf("%39s", &Emp.Employee_Name);

                  printf("Change %s age : ", EmployeeName);
                  scanf("%d", &Emp.Employee_Age);

                  printf("Change %s designation : ", EmployeeName); 
                  scanf("%39s", &Emp.Employee_Designation);

                  printf("Change %s salary : ", EmployeeName);
                  scanf("%f", &Emp.Employee_Salary);
                 
                  fseek(EmployeeFile, -sizeOfEmployeeRecord, SEEK_CUR);
                  fwrite(&Emp, sizeOfEmployeeRecord, 1, EmployeeFile);
                  break;
               }
               
            }
            
             printf("\n%s has been modified!", EmployeeName);
         
            printf("\nWould you like to modify another record (y/n) ?");
            fflush(stdin);
            scanf("\n%c", &nextChoice);

             printf("\n----------------------------------------------\n");  
         }
         
         break;
     
      case '3':
          nextChoice = 'y';

         while (nextChoice == 'y')
         {
            printf("\n----------------------------------------------\n");

            printf("Enter the Employee name to delete : ");
            scanf("%39s", &EmployeeName);

            EmployeeFileTemp = fopen("Temp.DAT", "wb");     
            rewind(EmployeeFile);

            while (fread(&Emp, sizeOfEmployeeRecord, 1, EmployeeFile) == 1)
            {
               if (strcmp(Emp.Employee_Name, EmployeeName) != 0)
               {
                  fwrite(&Emp, sizeOfEmployeeRecord, 1, EmployeeFileTemp);
               }   
            }
            
            fclose(EmployeeFile);
            fclose(EmployeeFileTemp);

            remove("filename");
            rename("Temp.DAT", "filename");

            fopen("EMPLOYEE.DAT", "wb+");

            printf("\n%s has been deleted!", EmployeeName);
         
            printf("\nWould you like to delete another record (y/n) ?");
            fflush(stdin);
            scanf("\n%c", &nextChoice);  

            printf("\n----------------------------------------------\n");
         }

         break;
      
      case'4':
         fseek(EmployeeFile, 0, SEEK_SET);

         while (fread(&Emp, sizeOfEmployeeRecord, 1, EmployeeFile) == 1)
         {
            printf("\n----------------------------------------------\n");
            printf("Employee Name : %s ", Emp.Employee_Name);
            printf("\n");
            printf("Employee Age : %d ", Emp.Employee_Age);
            printf("\n");
            printf("Employee Designation : %s ", Emp.Employee_Designation);
            printf("\n");
            printf("Employee Salary : %f ", Emp.Employee_Salary);
            printf("\n");
            printf("\n----------------------------------------------\n");
         }
         
         break;
      
      case '5':
         exit(0);
     
      default:
         break;
      }
   }
}