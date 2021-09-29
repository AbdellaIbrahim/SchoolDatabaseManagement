/* PLEASE DO NOT MODIFY A SINGLE STATEMENT IN THE TEXT BELOW.
READ THE FOLLOWING CAREFULLY AND FILL IN THE GAPS

I hereby declare that all the work that was required to 
solve the following problem including designing the algorithms
and writing the code below, is solely my own and that I received
no help in creating this solution and I have not discussed my solution 
with anybody. I affirm that I have read and understood
the Senate Policy on Academic honesty at 
https://secretariat-policies.info.yorku.ca/policies/academic-honesty-senate-policy-on/
and I am well aware of the seriousness of the matter and the penalties that I will face as a 
result of committing plagiarism in this assignment.

BY FILLING THE GAPS,YOU ARE SIGNING THE ABOVE STATEMENTS.

Full Name: Abdella Ibrahim
Student Number: 217 223 249
Course Section: 2031ON
eecs user id: Abudy72
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 30
#define fieldLength 200


#define diskFile "diskFile.dat"
#define courseFile "course.txt"

struct db_type
{
   char name[fieldLength];
   int age;
   char course1[fieldLength];
   char course2[fieldLength];
   char status[fieldLength];
 };

struct courseInfo
{ 
  char code [20]; // e.g., EECS2030
  char title [fieldLength];
  char  date [20];
  char time_start [20];
  char time_end [20];
  char  location [20]; 
};
 
 
struct courseInfo courseArr[SIZE]; // global variable  array of struc
     

char prompt_menu(void);
void init_list(struct db_type * pArr[]); 
void clearDB(struct db_type * pArr[]);
void init_courseArr(void);

void writeDisk(struct db_type * pArr[]); 
void emptyDisk(void); 
void loadDisk(struct db_type * pArr[]); 

void displayCourses(void);
void enterNew(struct db_type * pArr[]);
void displayDB(struct db_type * pArr[]);
void removeRecord (struct db_type * pArr[]);
void swap(struct db_type * pArr[]);
void sort(struct db_type * pArr[]);

int StudentIndex = 0; // This global variable will be used to manage students db
int main(int argc, char *argv[])
{
    
    struct db_type * db_pArr[SIZE];  // main db storage

    init_list(db_pArr);  // set to NULL
    
    init_courseArr();  // load course from diskfile
    
    char choice;
    for(; ;){
      choice = prompt_menu();
      switch (choice)
      {
         case 'n': enterNew(db_pArr); break;
         case 'd': displayDB(db_pArr); break;
         case 'w': writeDisk(db_pArr);  break;    
         case 'l': loadDisk(db_pArr); break;
         case 's': sort(db_pArr); break;
       
         case 'c': clearDB(db_pArr); break;  
         case 'e': emptyDisk();break;

         case 'v': displayCourses();break;
         case 'p': swap(db_pArr); break;
         case 'r': removeRecord(db_pArr);break;
         
         case 'q': exit(1); // terminate the whole program
       }
    
     }
     return 0;
}

void init_list(struct db_type * pArr[]){
  int t;
  for (t=0; t<SIZE; t++)
  { 
     pArr[t]= NULL;
  }
}

void clearDB(struct db_type * pArr[]){
   char c3[3];
   printf("are you sure to clear db? (y) or (n)? ");
 
   fgets(c3,3,stdin);
   
   if(! strcmp(c3, "y\n"))  
      init_list(pArr);
}


char prompt_menu(void){
  char s[80];
  while(1){
    printf("\n-----------------------------------------------------------------\n");
    printf("|    %-20s","(N)ew record");
    printf("%-20s","(R)emove record");
    printf("Swa(p) records\t|\n");
    printf("|    %-20s","(S)ort database");
    printf("%-20s","(C)lear database");
    printf("(D)isplay db\t|\n");
  
    printf("|    %-20s","(L)oad disk");
    printf("%-20s","(W)rite disk");
    printf("(E)mpty disk\t|\n");
  
    printf("|    %-20s", "(V)iew courses");//|\tSwa(p) record\t(Q)uit\t\t\t\t|\n");
    printf("%-20s","(Q)uit");
    printf("*Case Insensitive*\t|\n");
    printf("-----------------------------------------------------------------\n");
    printf("choose one: ");
  
    fgets(s,50, stdin); // \n added
   
    if (strlen(s) == 2 && strchr("edlsuqrcwnvpr", tolower(*s))) 
       return tolower(*s); // s[0], return the first character of s  
    //else
    printf("not a valid input!\n");
     
 }
}

/* display all or specified course */
void displayCourses(void){  // the provide sample.out uses "%s\t%-40s%-5s %s-%s   %s\n" as formatting string for printing each course info
    char prompt[8];
    int i=0; 
    int flag = 0;
        printf("Enter Course Code: ");
        scanf("%s", prompt);
        while ((getchar()) != '\n'); // This clears buffer so that we go back to main function with empty stream.
        if(strlen(prompt) > 4){ // Then current choice is in the form of EECSXXX
            for(i = 0;i < SIZE;i++){
                if(strcmp(prompt, (courseArr[i]).code) == 0){
                    printf("%s\t%-40s%-5s %s-%s   %s\n",(courseArr[i]).code, (courseArr[i]).title, (courseArr[i]).date, (courseArr[i]).time_start, (courseArr[i]).time_end,
                                                                                                (courseArr[i]).location);
                                                                                                flag = 1;
                                                                                                i = SIZE;                                               
                }
            }
        }
        if(prompt[2] != '\0'){ // Then current choice is the in form of XXXX
            for(i = 0;i < SIZE;i++){
                if(strcmp(prompt, ((courseArr[i].code) + 4)) == 0){
                    printf("%s\t%-40s%-5s %s-%s   %s\n",(courseArr[i]).code, (courseArr[i]).title, (courseArr[i]).date, (courseArr[i]).time_start, (courseArr[i]).time_end,
                                                                                                (courseArr[i]).location);
                                                                                                flag = 1;
                }
            }
        }
        if(strcmp(prompt,"a") == 0){ // Then current choice is a
            for(i = 0;i < SIZE;i++){
                if(strcmp((courseArr[i]).code,"EECS0000") == 0)break;
                printf("%s\t%-40s%-5s %s-%s   %s\n",(courseArr[i]).code, (courseArr[i]).title, (courseArr[i]).date, (courseArr[i]).time_start, (courseArr[i]).time_end,
                                                                                                (courseArr[i]).location);
            }
            flag = 1;
        }
        if(flag == 0) printf("Course Not found, Please try again!\n");
}



/* input items into the list */
void enterNew(struct db_type * pArr[SIZE]){
  pArr[StudentIndex] = malloc(sizeof(struct db_type));
  char courseTemp[10];
  char courseTemp2[10];
  char dateTemp[2][20];
  char timeTempCourse1[2][20];
  char timeTempCourse2[2][20];
  int flag;
  int counter = 0; // This is used to determine time conflicts
  char msg1[40] = "ATTENTION!, TIME CONFLICT";
  char msg2[40] = "SUCCESSFUL!, NO TIME CONFLICT";

  /* ------ GETTING STUDENT NAME ------ */
  printf("Enter Student Name: ");
  fgets(pArr[StudentIndex]->name,fieldLength, stdin);
  int i = strlen((*(pArr)[StudentIndex]).name) - 1;
  pArr[StudentIndex]->name[i] = '\0';

  /* ------ GETTING STUDENT AGE ------ */
  printf("Enter Student Age: ");
  scanf("%d",&flag);
  pArr[StudentIndex]->age = flag;
  while ((getchar()) != '\n');
  /* ------ GETTING STUDENT COURSES ------ */
  while(1){
    printf("Course1 Code: ");
    scanf("%s",courseTemp);
    while ((getchar()) != '\n');
    for(i= 0;i < SIZE;i++){
       if(courseTemp[4] == '\0'){
        if(strcmp(courseTemp, ((courseArr[i].code) + 4)) == 0){
          //strcpy((*pArr)[StudentIndex].course1, courseArr[i].code);
          sprintf(pArr[StudentIndex]->course1, "%s\t%-40s%-5s %s-%s   %s\n",(courseArr[i]).code, (courseArr[i]).title, (courseArr[i]).date, (courseArr[i]).time_start, (courseArr[i]).time_end,
                                                                                                (courseArr[i]).location);
          strcpy(dateTemp[0],courseArr[i].date);
          strcpy(timeTempCourse1[0],courseArr[i].time_start); // NEW
          strcpy(timeTempCourse1[1],courseArr[i].time_end); // NWQ
          i = SIZE;
          flag = 1;
      }
    }
      if(strcmp(courseArr[i].code,courseTemp) == 0){
        //strcpy((*pArr)[StudentIndex].course1, courseArr[i].code);
        sprintf(pArr[StudentIndex]->course1, "%s\t%-40s%-5s %s-%s   %s\n",(courseArr[i]).code, (courseArr[i]).title, (courseArr[i]).date, (courseArr[i]).time_start, (courseArr[i]).time_end,
                                                                                                (courseArr[i]).location);
        strcpy(dateTemp[0],courseArr[i].date);
        strcpy(timeTempCourse1[0],courseArr[i].time_start); // NEW
        strcpy(timeTempCourse1[1],courseArr[i].time_end); // NWQ
        i = SIZE;
        flag = 1;
      }
    } 
    if(flag == 1)break;
    if(flag != 1) printf("Course Not found. Try Again.\n");
  }
  flag = 0;
  while(1){
    printf("Course2 Code: ");
    scanf("%s",courseTemp2);
    while ((getchar()) != '\n');
    for(i= 0;i < SIZE;i++){
       if(courseTemp2[4] == '\0'){
        if(strcmp(courseTemp2, ((courseArr[i].code) + 4)) == 0){
          //strcpy((*pArr)[StudentIndex].course1, courseArr[i].code);
          sprintf(pArr[StudentIndex]->course2, "%s\t%-40s%-5s %s-%s   %s\n",(courseArr[i]).code, (courseArr[i]).title, (courseArr[i]).date, (courseArr[i]).time_start, (courseArr[i]).time_end,
                                                                                                (courseArr[i]).location);
          strcpy(dateTemp[1],courseArr[i].date);
          strcpy(timeTempCourse2[0],courseArr[i].time_start); // NEW
          strcpy(timeTempCourse2[1],courseArr[i].time_end); // NWQ
          i = SIZE;
          flag = 1;
      }
    }
      if(strcmp(courseArr[i].code,courseTemp2) == 0 && flag == 0){
        //strcpy((*pArr)[StudentIndex].course1, courseArr[i].code);
        sprintf(pArr[StudentIndex]->course2, "%s\t%-40s%-5s %s-%s   %s\n",(courseArr[i]).code, (courseArr[i]).title, (courseArr[i]).date, (courseArr[i]).time_start, (courseArr[i]).time_end,
                                                                                                (courseArr[i]).location);
        strcpy(dateTemp[1],courseArr[i].date);
        strcpy(timeTempCourse2[0],courseArr[i].time_start); // NEW
        strcpy(timeTempCourse2[1],courseArr[i].time_end); // NWQ
        i = SIZE;
        flag = 1;
      }
    } 
    if(flag == 1)break;
    if(flag != 1) printf("Course Not found. Try Again.\n");
  }
  
  /* ------ CHECKING COURSE CONFLICT ------ */
  
  flag = 0;
  int j;
  for(i = 0;i < 3;i++){
      for(j = 0;j < 3;j++){
        if(dateTemp[1][j] == dateTemp[0][i] && dateTemp[1][j] != '\0' && dateTemp[0][i] != '\0'){
          //strcpy(pArr[StudentIndex]->status,msg1);
          if(strcmp(timeTempCourse1[0],timeTempCourse2[0]) < 0){
            if(strcmp(timeTempCourse2[0],timeTempCourse1[1]) < 0){
              flag = 1;
              i = 3;
              j = 3;
            }
          }else if(strcmp(timeTempCourse2[0],timeTempCourse1[1]) > 0){
             if(strcmp(timeTempCourse2[0],timeTempCourse1[1]) > 0){
              flag = 1;
              i = 3;
              j = 3;
            }
          }
        }else if(dateTemp[1][i] == dateTemp[0][j] && dateTemp[0][j] != '\0' && dateTemp[1][i] != '\0'){
          //strcpy(pArr[StudentIndex]->status,msg1);
          if(strcmp(timeTempCourse1[0],timeTempCourse2[0]) < 0){
            if(strcmp(timeTempCourse2[0],timeTempCourse1[1]) < 0){
              flag = 1;
              i = 3;
              j = 3;
            }
          }else if(strcmp(timeTempCourse2[0],timeTempCourse1[1]) > 0){
             if(strcmp(timeTempCourse2[0],timeTempCourse1[1]) > 0){
              flag = 1;
              i = 3;
              j = 3;
            }
          }
        }
      }
  }

  if(flag == 0){
   strcpy(pArr[StudentIndex]->status,msg2);
   printf("%s\n",msg2);
  }
  if(flag == 1){
    strcpy(pArr[StudentIndex]->status,msg1);
    printf("%s\n",msg1);
  }

  StudentIndex++;
}

/* display records */
void displayDB(struct db_type * pArr[]){
  int i, j=0;
  printf("===============================\n");
  if(StudentIndex == 0){
    printf("No records found\n");
  }else{
      for(i = 0;(i < StudentIndex); i++){
        if(pArr[i] != NULL){
          printf("Student Name: %s\n",pArr[i]->name);
          printf("Age: %d\n",   (*(pArr)[i]).age);
          printf("Course-1: %s",(pArr[i]->course1));
          printf("Course-2: %s",pArr[i]->course2);
          printf("REMARKS: %s\n",pArr[i]->status);
          printf("\n");
          j++;
          }
      }
  }
  printf("========== %d records ==========\n", j);
}

/* remove an existing item */
void removeRecord (struct db_type * pArr[])	
{
  int j = 1;
  char nameInput[fieldLength];
  printf("Enter Full Name to delete: ");
  fgets(nameInput,fieldLength, stdin); // This gets the name to be removed.
  int i = strlen(nameInput) - 1;
  nameInput[i] = '\0'; // to remove last \n.
  for(i = 0;i < StudentIndex;i++){
    if(pArr[i] != NULL){
    if(strcmp(nameInput,(pArr[i]->name)) == 0){
      printf("record [%s] removed successfully.",(*(pArr)[i]).name);
      pArr[i] = NULL;
      i = StudentIndex;
      j = 0;
    }
  }
  }
  if(j != 0) printf("Record not Found");
}

/* swap records */
void swap(struct db_type * pArr[]){
  struct  db_type * temp = malloc(sizeof(struct db_type)); // This is used to contain strct target to be copied.
  struct  db_type * temp1 = malloc(sizeof(struct db_type)); // This is used to contain strct target to be copied.
  int i = 0;
  for(i = 0;i < StudentIndex;i=i+2){
    
    if((pArr[i+1]) != NULL){
      temp = ((pArr)[i]);
      pArr[i] = pArr[i+1];
      pArr[i+1] = temp;
    }
  }
} 

/* load from course.txt, store into (global) array of courses  */
void init_courseArr(void){ 
 
   FILE *fr; //file pointer
   fr = fopen (courseFile, "r");
   char arr[50];  
   int count = 0;
   while ((fgets(arr,100,fr)) != NULL)
   {  
     strncpy(courseArr[count].code,  arr, strlen(arr)-1); // remove \n  
     courseArr[count].code[strlen(arr)-1] = '\0';  //to be safe
     
     fgets(arr,100,fr);  
     strncpy(courseArr[count].title ,  arr, strlen(arr)-1);
     courseArr[count].title[strlen(arr)-1] = '\0';  //to be safe
     
          
     fgets(arr,100,fr); 
     strncpy(courseArr[count].date,  arr, strlen(arr)-1);
     courseArr[count].date[strlen(arr)-1] = '\0';  //to be safe
       
     // other ways, remove \n before
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].time_start,  arr);
      
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].time_end,  arr);
      
     fgets(arr,100,fr);
     arr[strlen(arr)-1] = '\0';
     strcpy(courseArr[count].location,  arr); 
      
     count++;
     fgets(arr,100,fr); // read the empty line
   }

   strcpy(courseArr[count].code, "EECS0000"); // a terminator token structure

   fclose(fr);
     
 }
    
/************************ DISK IO *****************************************************************/

void writeDisk(struct db_type * pArr[]){
  FILE *fp;
  int i;

  if ( (fp=fopen(diskFile,"ab")) == NULL)
  {
    printf("cannot open file\n");
    return;
  }

  
  for (i=0; i< SIZE ; i++)
  {
     if ( pArr[i] != NULL)
     {  
       if (fwrite( pArr[i], sizeof(struct db_type), 1, fp) != 1)
       { 
          printf("file write error\n");
       }
     } 
   }
   fclose(fp);

}

void emptyDisk(void){

  FILE *fp;
  
  char c3[3];
  printf("are you sure to empty disk? (y) or (n)? ");
  fgets(c3,3,stdin);
  if(strcmp(c3, "y\n"))  
     return;
 
  //else
  if ( (fp = fopen(diskFile,"w")) == NULL)
  {
     printf("no file to open\n");
     return;
  }
  fclose(fp); // open close, will empty the file
}


void loadDisk(struct db_type * pArr[]){
  FILE *fp;
  int i;
  char c3[3];
  printf("will overwrite current records. are you sure to load disk? (y) or (n)? ");
  fgets(c3,3,stdin);
  if(strcmp(c3, "y\n"))  
     return;

  struct db_type * tmp;  
  
  if ( (fp = fopen(diskFile,"r")) == NULL)
  {
    printf("cannot open file\n");
    return;
  }

  init_list(pArr);
  for (i=0; i < SIZE ; i++)
  {    
     
     tmp =  (struct db_type *) malloc (sizeof(struct db_type));   
       
     if (fread( tmp, sizeof(struct db_type), 1, fp) != 1)
     {
       if (feof(fp))
       { fclose(fp); 
         return;
       }
       printf("file read error\n");
     }
     else pArr[i] = tmp;
  }
}

/****bonus*************************************************************************************/

/* sort the records by ages */
void sort(struct db_type * pArr[])
{
 

}