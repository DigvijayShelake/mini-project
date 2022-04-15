 // PROGRAM : CHECK ME SYSTEM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

enum gen
{
    male = 1,
    female
};
enum state
{
    critical = 1,
    intermediate,
    outOfDanger
};
enum intermediateSymps
{
    fever = 1,
    bodyAche,
    dryCough,
    lossOfTaste
};
enum criticalSymps
{
    highTemp = 1,
    chestPain,
    breathing,
    Appetite
};

struct Personal // STRUCTURE FOR STORING DATE OF EXAMIN OF PATIENT
{
    char name[50];
    int age;
    int gender;
    int bedNo;
};

struct Date // STRUCTURE FOR STORING DATE OF EXAMIN OF PATIENT
{
    int day;
    int month;
    int year;
};

struct Health // STRUCTURE FOR STORING HEALTH CONDTION OF PATIENT
{
    int inter[5];    // here inter[0] is indicator
    int critical[6]; // herer crirtcal[0] is indicator
    char preDisease[100];
    int healthMeter;
};

struct Patient // STRUCTURE FOR STORING PATIENT OVERALL INFORMATION
{
    struct Date dt;
    struct Personal info;
    struct Health ht;
    int state;
};

struct Tree // NODE FOR TREE DATA STRUCTURE FOR STORING AND DISPLAYING INFORMATION OF PATIENTS
{
    struct Tree *lchild;
    struct Patient person;
    struct Tree *rchild;
};

// MACROS
#define ADMIN_PASS 1234
#define EXAMIN_PASS 5678 

// PROTOYTPE DECLARTIONS

int adminPass(int pass);    // FUNCTION FOR CHECKING PASSWORD BEFORE ENTERING ADMIN MODE
int examinePass(int pass);  // FUNCTION FOR CHECKING PASSWORD BEFORE ENTERING EXAMINE MODE

// FUNCTIONS FOR ADMIN MODE
void adminMode();          // FUNCTION FOR DISPALYING ADMIN MODE MENU
struct Tree *insert(struct Tree *root, struct Patient ikey); // FUCTION FOR FETCHING INFORMATION FROM FILE
void inorder(struct Tree *ptr);   // FUNCTION USED IN INRODER FOR DISPLAING
void showFile(int state);         
void printInfo(struct Tree *ptr); // FUNCTION USED IN INORDER TRAVERSAL

// FUNCTIONS FOR EXMAINE MODE
void examineMode();
void examinePatient();
void getDate(struct Date *examinDate); // FUNCTION USED FOR INPUTING DATE IN EXAMINE MODE
void getPatientInfo(struct Personal *personalInfo);// FUNCTION USED FOR INPUTING PERSONAL INFO
void analyze(struct Health *condition); // FUNCTION FOR OVERALL HEALTH OF PATIENT
void intermediateAnalyze(int *array); // FUNCTION FOR INTERMIDATE ANALYSIS OF PATIENT
void criticalAnalyze(int *array); // FUNCTION FOR CRITICAL ANALYSIS OF PATIENT
void delete();

// END OF PROTOTYPE DECLARATION

// MAIN FUCTION
int main()
{   
    int choice;
    int admin_pass;
    int examine_pass;
    system("cls");
    printf("\n\n----------------------------------------------------------------------------------------------------------------------------\n");
    printf("                                                    THE CHECK ME SYSTEM\n");
    printf("----------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("                                An Easy and Efficient Way to Manage and Prioritize Covid Patients\n\n");
    printf("                                                    press any key to proceed");
    getch();

    printf("\n");
    do
    { 
        system("cls");
        printf("\n===========================");
        printf("\nHOME PAGE\n");
        printf("===========================");
        printf("\n1. Admin Mode\n");
        printf("2. Examine Mode\n");
        printf("3. Close Program\n\n");
        printf("Enter your choice : ");
        scanf("%d",&choice);

        switch (choice)
        {

        case 1:
            printf("Enter Password : ");
            scanf("%d",&admin_pass);
            if(adminPass(admin_pass))
            {
                adminMode();
            }
            else
            {
                printf("\nWrong Password !\n");
                getch();
            }
            break;
        

        case 2:
            printf("Enter Password : ");
            scanf("%d",&examine_pass);
            if(examinePass(examine_pass))
            {
                examineMode();
            }
            else
            {
                printf("\nWrong Password !\n");
                getch();
            }
            break;
        

        case 3:
            system("cls");
            printf("\nProgram Closed\n");
            break;

        default:
            printf("\nEnter valid choice\n");
            break;
        }

    }
    while(choice != 3);
    return 0;
}

int adminPass(int pass) // FUNCTION FOR CHECKING PASSWORD BEFORE ENTERING ADMIN MODE
{
    if(pass == ADMIN_PASS)
        return 1;
    else
        return 0;
}

int examinePass(int pass) // FUNCTION FOR CHECKING PASSWORD BEFORE ENTERING EXAMINE MODE
{
    if(pass == EXAMIN_PASS)
        return 1;
    else
        return 0;
}

// FUNCTIONS REQUIRED FOR ADMIN MODE
void adminMode() // ADMIN MODE IN WHICH YOU CAN WATCH LIST DEPENDING UPON TYPE OF HEALTH CONDiTION OF PATIENT
{   
    system("cls");
    int choice;
    do 
    {
        system("cls");
        printf("=================================");
        printf("\nADMIN MODE\n");
        printf("=================================");
        printf("\n1. Critical Patients List\n");
        printf("2. Normal Patients List\n");
        printf("3. Out Of Danger Patient List\n");
        printf("4. Back To Home Page\n\n");
        printf("Enter Choice : ");
        scanf("%d",&choice); // TAKING INPUT FROM USER WHICH FILE TO BE DISPLAYED

        switch(choice) // SWITCH STATEMENT TO DECIDE WHICH FILE SHOULD BE DISPLAYED
        {
            case 1:  // CASE 1 TO SHOW CRITICAL FILES
                system("cls");
                // printf("\n=================================\n");
                // printf("             CRITICAL PATIENTS");
                // printf("\n=================================\n");
                showFile(1);
                printf("\nPress any key to continue\n");
                getch();
                break;

            case 2:  // CASE 2 TO SHOW NORMAL PATIENT FILES
                system("cls");
                printf("\n=================================\n");
                printf("                                NORMAL PATIENTS");
                printf("\n=================================\n");
                showFile(2);
                printf("\nPress any key to continue\n");
                getch();
                break;

            case 3:  // CASE 3 TO SHOW OUT OF DANGER PATIENTS FILES
                system("cls");
                printf("\n=================================\n");
                printf("                              OUT OF DANGER PATIENTS");
                printf("\n=================================\n");
                showFile(3);
                printf("\nPress any key to continue\n");
                getch();
                break;

            case 4:
                break;

            default:
                printf("\nEnter Valid Choice\n");
                getch();
                break;
        }
    }
    while(choice != 4); // LOOP BREAKING CONDITION
    system("cls");
}

void showFile(int state) // FUNCTION TO PRINT CONTENTS OF FILE
{
    struct Tree *root;
    struct Patient pt;
    root = NULL;

    FILE *fp; 
    fp = fopen("File.dat","r"); // OPENING FILE
    
    if(fp == NULL)
    {
        printf("\nError in opening file!\n");
        return;
    }

    while(fread(&pt,sizeof(struct Patient),1,fp)) // FETCHING CONTENTS FROM FILE
    {
        if(pt.state == state) // CHECKING TYPE OF PATIENT HEATLH (CRITICAL NORMAL OR OUT OF DANGER)
            root = insert(root,pt); // STORING THE CONTENTS OF FILE IN TREE
    }

    fclose(fp);

    if(root == NULL) // IF TREE IS EMPTY NO PATIENTS WILL BE DISPLAYED
    {
        printf("\nFile is Empty!\n"); // EMPTY MESSAGE
        return;
    }

    inorder(root); // SHOWING CONTENTS OF FILE IN SORTED ORDER
}

struct Tree *insert(struct Tree *root, struct Patient ikey) // FUNCTION FOR INSERTION IN B.S.T
{
    struct Tree *ptr;
    struct Tree *par;
    struct Tree *temp;
    ptr = root;
    par = NULL;

    while (ptr != NULL)
    {
        par = ptr;
        if (ikey.ht.healthMeter < ptr->person.ht.healthMeter)
        {
            ptr = ptr->lchild;
        }
        else
        {
            ptr = ptr->rchild;
        }
    }

    temp = (struct Tree *)malloc(sizeof(struct Tree));
    temp->person = ikey;
    temp->lchild = NULL;
    temp->rchild = NULL;

    if (par == NULL)
        root = temp;
    else if (par->person.ht.healthMeter > ikey.ht.healthMeter)
        par->lchild = temp;
    else
        par->rchild = temp;

    return root;
}

void printInfo(struct Tree *ptr) // FUNCTION TO SHOW TOTAL INFORMATION OF INDIVIDUAL PATIENT 
{
    int i;
    //printf("\nPATIENT INFORMANTION\n"); // FOR DISPLAYING INFORMATION OF PATIENT
    printf("\nPatient Name   : %s\n", ptr->person.info.name);
    printf("Patient Bed No : %d\n",ptr->person.info.bedNo);
    printf("Examine Date   : %d - %d - %d\n", ptr->person.dt.day, ptr->person.dt.month, ptr->person.dt.year);
    printf("Patient Age    : %d\n", ptr->person.info.age);
    if (ptr->person.info.gender == male)
        printf("Patient Gender : MALE\n");
    else
        printf("Patient Gender : FEMALE\n");

    printf("\nHEALTH CONDITION\n");
    printf("\nTotal Health Meter : %d\n", ptr->person.ht.healthMeter);
    printf("Intermidiate Symptoms    : ");
    if (ptr->person.ht.inter[0])
    {
        for (i = 1; i < 5; i++)
        {
            if (ptr->person.ht.inter[i] != 0)
            {
                if (i == fever)
                    printf(" Fever. ");
                else if (i == dryCough)
                    printf(" Dry Cough. ");
                else if (i == lossOfTaste)
                    printf(" Loss Of Taste And Smell. ");
                else
                    printf(" Body Ache. ");
            }
        }
    }
    printf("\nCritcal Symptoms         : "); // SHOWING LIST OF CRITICAL PATIENTS
    if (ptr->person.ht.critical[0])
    {
        for (i = 1; i < 5; i++)
        {
            if (ptr->person.ht.critical[i] != 0)
            {
                if (i == highTemp)
                    printf(" High Temperature. ");
                else if (i == chestPain)
                    printf(" Chest Pain. ");
                else if (i == breathing)
                    printf(" Breathing Difficulty. ");
                else if (i == Appetite)
                    printf(" Loss of Appetite. ");
            }
        }
    }

    if (ptr->person.ht.critical[5]) // DISPLAYING PRE-EXISTING DISEASE IF EXIT
        printf("\nPre - existing Disaese   :  %s", ptr->person.ht.preDisease);

    printf("\nPatient Condition        :  "); // DISPLAYING THE HEALTH STATE OF PATIENT
    if (ptr->person.state == critical)
        printf("Critical\n"); // IF CRITICAL THEN PRINT CRITICAL
    else if (ptr->person.state == intermediate)
        printf("Intermidiate\n"); // IF INTERMIDIATE THEN PRINT INTERMIDIATE
    else if (ptr->person.state == outOfDanger)
        printf("Out of danger\n"); // IF OUT OF DANGER THEN PRINT OUT OF DANGER
    printf("----------------------------------------------------------------------------------------------------------------");
}

void inorder(struct Tree *ptr) // FUNCTION OT PRINT CONTENTS OF TREE IN SORTED ORDER
{
    if (ptr == NULL)
        return;

    inorder(ptr->rchild);
    printInfo(ptr);
    inorder(ptr->lchild);
}

// FUNCTIONS REQUIRED FOR EXAMINE MODE

void examineMode()
{
    system("cls");
    int choice;
    do 
    {   
        system("cls");
        printf("\n=================================\n");
        printf("                                    EXAMINE MODE");
        printf("\n=================================\n");
        printf("1. Examine Patients\n");
        printf("2. Delete Patient Information\n");
        printf("3. Back To Home Page\n\n");
        printf("Enter choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                examinePatient();
                break;

            case 2:
                delete();
                getch();
                break;

            case 3:
                break;

            default:
                printf("\nEnter valid choice\n");
                getch();
                break;
        }
    }
    while(choice != 3);
}

void examinePatient()
{
    system("cls");
    int choice, state;
    struct Date examinDate;       // storing date of examination
    struct Personal personalInfo; // storing patient personal info
    struct Health condition;      // storing patient health condtion
    struct Patient totalInfo;     // storing patient total info
    FILE *fp;
    int i;

    fp = fopen("File.dat", "ab"); // Opening file

    if (fp == NULL)
    {
        printf("\nError in File Opening\n");
        getch();
        return;
    }

    system("cls");
    getDate(&examinDate);

    do
    {
        system("cls");
        getPatientInfo(&personalInfo);
        system("cls");
        analyze(&condition);
        system("cls");
        // MERGING
        totalInfo.dt = examinDate;
        totalInfo.info = personalInfo;
        totalInfo.ht = condition;

        if (condition.critical[0]) // IF CRITICAL FLAG IS ONE THEN STATE OF PATIENT WILL BE CRITICAL
            totalInfo.state = critical;
        else if (condition.inter[0]) // IF INETERMIDIATE FLAG IS ONE THE STATE OF PATIENT WILL BE INTERMEDIATE
            totalInfo.state = intermediate;
        else // IF BOTH THE ABOVE FLAGS ARE ZERO THEN STATE WILL BE OUT OF DANGER
            totalInfo.state = outOfDanger;

        fwrite(&totalInfo, sizeof(struct Patient), 1, fp);

        printf("\nDo You want to add more file (Type 1 for 'YES' 0 for 'NO') : ");
        scanf("%d", &choice);

    } while (choice == 1);

    fclose(fp);
    system("cls");
    //showFile();
    return;
}

void getDate(struct Date *examinDate) // FUNCTION USED FOR INPUTING DATE IN EXAMINE MODE (NESTED IN EXAMINE MODE)
{   
    system("cls");
    printf("Enter Date (dd/mm/yy) formant : ");
    scanf("%d%*c%d%*c%d", &examinDate->day, &examinDate->month, &examinDate->year);
    while (examinDate->day < 1 || examinDate->day > 31 || examinDate->month < 0 || examinDate->month > 12 || examinDate->year < 2021) // CHECKS WHEATHER ENTERED DATE IS VALID OR NOT,MEANS WITHIN BOUND OR NOT
    {
        printf("\nInvalid day or month Enter again\n"); // IF DATE IS NOT INPUTED CORRECTLY
        printf("Enter Date (dd/mm/yy) formant : ");
        scanf("%d%*c%d%*c%d", &examinDate->day, &examinDate->month, &examinDate->year);
    }
}

void getPatientInfo(struct Personal *personalInfo) // FUNCTION TO GET INFO OF PATIENT (NESTED IN EAMINE MODE)
{   
    system("cls");
    printf("\n=======================\n");
    printf("                                   PATIENT DETAILS");
    printf("\n=======================\n\n");
    printf("Enter Name  : "); // INPUTING NAME OF PATIENT
    fflush(stdin);
    gets(personalInfo->name);

    printf("\nEnter Bed number : ");
    scanf("%d",&personalInfo->bedNo);

    printf("\nEnter Age   : "); // INPUTING AGE OF PATIENT
    scanf("%d", &personalInfo->age);
    while (personalInfo->age < 0) // CHECKING BOUNDS
    {
        printf("Invalid Age Enter again\n");
        printf("Enter Bed No  : ");
        scanf("%d", &personalInfo->age);
    }

    printf("\nEnter gender 1. Male  2. Female : "); // INPUTING GENDER OF PATIENT
    scanf("%d", &personalInfo->gender);
    while (personalInfo->gender != 1 && personalInfo->gender != 2) // CHECKING BOUNDS
    {
        printf("Invalid Input Enter again\n");
        printf("Enter gender 1. Male  2. Female : ");
        scanf("%d", &personalInfo->gender);
    }
}

void analyze(struct Health *condition) // FUNCTION FOR OVERALL HEALTH OF PATIENT(NESTED IN EXAMINE MODE)
{
    int i = 0;
    for (i = 0; i < 5; i++)      // initializing zero to all array in health struct
        condition->inter[i] = 0; // making all array values to zero

    //making all zero is important as this array act as flags for symptoms
    for (i = 0; i < 6; i++)
        condition->critical[i] = 0;

    condition->healthMeter = 0;

    intermediateAnalyze(condition->inter); // INTERMIDIATE FUNCION IS NESTED (PART OF ANALIZE)
    system("cls");
    criticalAnalyze(condition->critical); // FUNCTION FOR COLLECTING CRITICAL SYMPTOMS

    if (condition->critical[5]) // TAKING PRE EXISTING DESEASE FROM USER IF PATIENT HAVE
    {                           // CRITICAL[5] IS USED TO DETERMINE WHETHER PATIENT HAVE PRE-EXISTING DISEASE OR NOT
        printf("\nType the pre-existing disease patient have and hit enter\n");
        fflush(stdin);
        gets(condition->preDisease);
    }
    condition->healthMeter = condition->inter[0] + condition->critical[0];
    system("cls");
}

void intermediateAnalyze(int *array) // FUNCTION FOR INTERMIDATE ANALYSIS OF PATIENT (NESTED IN ANALYZE FUNCTION)
{
    system("cls");
    printf("\n===================================\n");
    printf("                                           INTERMEDIATE SYMPTOMS ANALYSIS");
    printf("\n===================================\n");

    printf("\n(Enter 1 for 'YES' OR 0 for 'NO')\n");
    printf("\n1. DO PATIENT HAVE FEVER ?\n");
    printf("ENTER (1/0) : ");
    scanf("%d", &array[1]);
    while (array[1] != 1 && array[1] != 0)
    {
        printf("\nIvalid Key enter again\n");
        printf("ENTER (1/0) : ");
        scanf("%d", &array[1]);
    }

    printf("\n2. DO PATIENT EXPERIANCE BODY ACHE ?\n");
    printf("ENTER (1/0) : ");
    scanf("%d", &array[2]);
    while (array[2] != 1 && array[2] != 0)
    {
        printf("\nIvalid Key enter again\n");
        printf("ENTER (1/0) : ");
        scanf("%d", &array[2]);
    }

    printf("\n3. DO PATIENT EXPERIANCE DRY COUGH ?\n");
    printf("ENTER (1/0) : ");
    scanf("%d", &array[3]);
    while (array[3] != 1 && array[3] != 0)
    {
        printf("\nIvalid Key enter again\n");
        printf("ENTER (1/0) : ");
        scanf("%d", &array[3]);
    }

    printf("\n4. DO PATIENT EXPERIANCE LOSS OF TASTE OR SMELL ?\n");
    printf("ENTER (1/0) : ");
    scanf("%d", &array[4]);
    while (array[4] != 1 && array[4] != 0)
    {
        printf("\nIvalid Key enter again\n");
        printf("ENTER (1/0) : ");
        scanf("%d", &array[4]);
    }

    for(int i = 1; i < 5; i++)
    {
        if(array[i])
            array[0]++;
    }
}

void criticalAnalyze(int *array) // FUNCTION TO ANALYZE THE CRITICAL SYMPTOMS OF PATIENT(NESTED IN ANALYZE FUNCTION)
{
    system("cls");
    printf("CRITICAL SYMPTOMS ANALYSIS");
    printf("\n(Enter 1 for 'YES' or Enter 0 for 'NO)\n");

    printf("\n1. DO PATIENT HAVE HIGH TEMPERATURE ?\n"); // checking high temp
    printf("ENTER (1/0) : ");
    scanf("%d", &array[1]);
    while (array[1] != 1 && array[1] != 0)
    {
        printf("\nIvalid Key enter again\n");
        printf("ENTER (1/0) : ");
        scanf("%d", &array[1]);
    }

    printf("\n2. DO PATIENT EXPERIANCE PERSISTENT PAIN OR PRESURE IN CHEST ?\n"); // checking chest presure or pain
    printf("ENTER (1/0) : ");
    scanf("%d", &array[2]);
    while (array[2] != 1 && array[2] != 0)
    {
        printf("\nIvalid Key enter again\n");
        printf("ENTER (1/0) : ");
        scanf("%d", &array[2]);
    }

    printf("\n3. DO PATIENT EXPERIANCE SHORTENESS OR DIFFICULTY IN BREATHING ?\n"); // shortness or difficulty in breathing
    printf("ENTER (1/0) : ");
    scanf("%d", &array[3]);
    while (array[3] != 1 && array[3] != 0)
    {
        printf("\nIvalid Key enter again\n");
        printf("ENTER (1/0) : ");
        scanf("%d", &array[3]);
    }

    printf("\n4. DO PATIENT EXPERIANCE LOSS OF APPETITE ?\n"); // loss of apetite
    printf("ENTER (1/0) : ");
    scanf("%d", &array[4]);
    while (array[4] != 1 && array[4] != 0)
    {
        printf("\nIvalid Key enter again\n");
        printf("ENTER (1/0) : ");
        scanf("%d", &array[4]);
    }

    printf("\n5. DO PATIENT HAVE ANY PRE-EXISTING DISEASE ?\n"); // any pre-exixting disease
    printf("\n1. Blood Presure\n");
    printf("\n2. Diabetes\n");
    printf("\n3. Cancer\n");
    printf("\n4. Lungs or Heart Disease\n");
    printf("\nENTER (1/0) : ");
    scanf("%d", &array[5]);
    while (array[5] != 1 && array[5] != 0)
    {
        printf("\nIvalid Key enter again\n");
        printf("ENTER (1/0) : ");
        scanf("%d", &array[5]);
    }

    for(int i = 1; i < 6; i++)
    {
        if(array[i])
            array[0]++;
    }
    system("cls");
}

void delete() // FUNCTION TO DELETE PATIENT INFORMATION FROM THE FILE
{
    int bedNo;
    int found;
    struct Patient pat;
    FILE *fp1;
    FILE *fp2;
    
    system("cls");
    printf("\nEnter Bed No of Patient to be deleted : ");
    scanf("%d",&bedNo);

    fp1 = fopen("File.dat","rb");
    if(fp1 == NULL)
    {
        printf("\nError in opening File !\n");
        getch();
        return;
    }

    fp2 = fopen("Temp.dat","wb");
    if(fp2 == NULL)
    {
        printf("\nError in opening File\n");
        fclose(fp1);
        getch();
        return;
    }

    found = 0;
    while(fread(&pat,sizeof(struct Patient),1,fp1))//reads a record variable from file
    {
        if(pat.info.bedNo != bedNo)
        {
            fwrite(&pat,sizeof(struct Patient),1,fp2);
        }
        else
        {
            found++;
            printf("\nPatient Information Deleted\n");
        }
    }

    if(!found)
        printf("\nNot Found !\n");
    fclose(fp1);
    fclose(fp2);
    remove("File.dat");
    rename("temp.dat","File.dat");
}


                       