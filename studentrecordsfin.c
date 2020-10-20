#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//MCA macro
#define NUM_SEM 6
#define NUM_COURSE 8
#define NUM_REGIONAL_CENTRE 10
#define NUM_STUDY_CENTRE 20
//Used macro
#define MAX_YR  9999
#define MIN_YR  1900
#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD  20
#define FILE_NAME  "stud1125.bin"
// Macro related to the students info
#define MAX_NAME 50
#define FILE_HEADER_SIZE  sizeof(sAdmin)
#define FILE_HEADER_SIZE1  sizeof(sUser)
// Global variables
char courseInMCA[NUM_SEM][NUM_COURSE][10] ={
												{"MCS11","MCS12","MCS13","MCS14","MCS15","MCS16","MCSL11","MCSL12"},
												{"MCS21","MCS22","MCS23","MCS24","MCS25","MCS26","MCSL21","MCSL22"},
												{"MCS31","MCS32","MCS33","MCS34","MCS35","MCS36","MCSL31","MCSL32"},
												{"MCS41","MCS42","MCS43","MCS44","MCS45","MCS46","MCSL41","MCSL42"},
												{"MCS51","MCS52","MCS53","MCS54","MCS55","MCS56","MCSL51","MCSL52"},
												{"MCS61","MCS62","MCS63","MCS64","MCS65","MCS66","MCSL61","MCSL62"},
										   };
char assignmentDates[NUM_SEM][NUM_COURSE][10] ={
												{"11/2/2020","12/2/2020","15/2/2020","12/2/2020","13/2/2020","10/2/2020","1/2/2020","9/2/2020"},
												{"1/2/2020","12/2/2020","5/2/2020","2/2/2020","3/2/2020","6/2/2020","1/2/2020","9/2/2020"},
												{"14/2/2020","1/2/2020","1/2/2020","1/2/2020","13/2/2020","12/2/2020","21/2/2020","19/2/2020"},
												{"13/2/2020","12/2/2020","1/2/2020","12/2/2020","3/2/2020","4/2/2020","16/2/2020","7/2/2020"},
												{"19/2/2020","1/2/2020","1/2/2020","1/2/2020","13/2/2020","18/2/2020","14/2/2020","2/2/2020"},
												{"17/2/2020","12/2/2020","15/2/2020","2/2/2020","3/2/2020","15/2/2020","13/2/2020","5/2/2020"},
										   };
//structure to store date
typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;
typedef struct
{
    char username1[MAX_SIZE_USER_NAME];
    char password1[MAX_SIZE_PASSWORD];
} sUser;
typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
} sAdmin;
//Elements of structure
typedef struct// to call in program
{
    unsigned int enrolment_no; // declare the integer data type
	unsigned int current_sem; // declare the integer data type
	char studentName[MAX_NAME];
    char studyCentre[MAX_NAME];// declare the charecter data type
    char regionalCentre[MAX_NAME];// declare the character data type
	unsigned int TEmarks[NUM_SEM][NUM_COURSE];//declare the integer data type
	unsigned int Amarks[NUM_SEM][NUM_COURSE];//declare the integer data type
	unsigned int feePaid[NUM_SEM];// declare the integer data type
	Date studentJoiningDate;// declare the integer data type
} sRegister;
//Validate name
int isNameValid(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for(index =0; index <len ; ++index)
    {
        if(!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}
// Function to check leap year.
//Function returns 1 if leap year
int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}
// returns 1 if given date is valid.
int isValidDate(Date *validDate)
{
    //check range of year,month and day
    if (validDate->yyyy > MAX_YR ||
            validDate->yyyy < MIN_YR)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    //Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}
int isSemValid(unsigned int *validSem)
{
	if (validSem>=1 && validSem<=6)
		return 1;
	else
		return 0;
}
int isFeeValid(unsigned int *validFee)
{
	if (validFee>0 && validFee<10000)
		return 1;
	else
		return 0;
}
int isMarksValid(unsigned int *validMarks)
{
	if (validMarks>0 && validMarks<100)
		return 1;
	else
		return 0;
}
//Align the message
void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;
    //calculate how many space need to print
    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);
}
//Head message
void headMessage(const char *message)
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############   Student Record Management System Project in C   ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t----------------------------------------------------------------------------");
}
//Display message
void welcomeMessage()
{
    headMessage("www.aticleworld.com");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                  WELCOME                  =");
    printf("\n\t\t\t        =                    TO                     =");
    printf("\n\t\t\t        =               Student Record              =");
    printf("\n\t\t\t        =                 MANAGEMENT                =");
    printf("\n\t\t\t        =                   SYSTEM                  =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
}
//Assignment submission schedules
void addAssignmentMarks()
{
    sAdmin fileHeaderInfo = {0};
    sUser fileHeaderInfo1 = {0};
//	int totalFeePaid = 0;
//    int found = 0;
//    int enrolment_no =0;
//    int status = 0;
//    sRegister addStudentInfoInDataBase = {0};
//    FILE *fp = NULL;
//    fp = fopen(FILE_NAME,"rb+");
//    if(fp == NULL)
//    {
//        printf("\n\t\t\tFile is not opened\n");
//        exit(1);
//    }
//    headMessage("ADD ASSIGNMENT MARKS");
//    //put the control on student detail
//    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
//    {
//        fclose(fp);
//        printf("\n\t\t\tFacing issue while reading file\n");
//        exit(1);
//    }
//    printf("\n\n\t\t\tEnter Enrolment Number to search:");
//    fflush(stdin);
//    scanf("%u",&enrolment_no);
//    while (fread (&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp))
//    {
//        if(addStudentInfoInDataBase.enrolment_no == enrolment_no)
//        {
//            found = 1;
//            break;
//        }
//    }
//	if(found)
//    {
////        char studentName[MAX_NAME] = addStudentInfoInDataBase.studentName;
////        char studyCentre[MAX_NAME] = addStudentInfoInDataBase.studyCentre;
////        char regionalCentre[MAX_NAME] = addStudentInfoInDataBase.regionalCentre;
////        unsigned int currentSem = addStudentInfoInDataBase.current_sem;
////        unsigned int feePaid[NUM_SEM];
////        for(int i=0; i<NUM_SEM; i++)
////        {
////            feePaid[i] = addStudentInDataBase.feePaid[i];
////        }
////    }
//		for (int i=0; i<addStudentInfoInDataBase.current_sem; i++)
//		{
//			for (int j=0; j<NUM_COURSE; j++)
//			{
//				do
//				{
//					printf("\n\t\t\tPlease Enter Assignment Marks Obtained in Semster %u for Course %s = ", i, courseInMCA[i][j]);
//					fflush(stdin);
//					addStudentInfoInDataBase.Amarks[i][j]=2;
//
////					scanf("%u",&addStudentInfoInDataBase.Amarks[i][j]);
////					printf("%u",addStudentInfoInDataBase.Amarks[i][j]);
//					status = isMarksValid(addStudentInfoInDataBase.Amarks[i][j]);
////					if (!status)
////					{
////						printf("\n\t\t\tYou Entered Invalid Marks. Please enter again.");
////					}
//				}
//				while(!status);
//			}
////		}
//	}
//	fwrite(&addStudentInfoInDataBase,sizeof(addStudentInfoInDataBase), 1, fp);
//	fclose(fp);
    char studentName[MAX_NAME];
    char studyCentre[MAX_NAME];
    char regionalCentre[MAX_NAME];
    unsigned int feePaid[NUM_SEM];
    unsigned int currentSem;
    unsigned int enrolmentNo;
    int status = 0;
    int found = 0;
    unsigned int studentDelete = 0;
    sRegister addStudentInfoInDataBase = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
//    FILE *tmpp = NULL;
    headMessage("Delete Student Details");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File fp is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","ab+");
    if(tmpFp == NULL)
    {
        fclose(tmpFp);
        printf("File tmpFp is not opened\n");
        exit(1);
    }
//    if (fseek(tmpFp,FILE_HEADER_SIZE,SEEK_SET) != 0)
//    {
//        fclose(tmpFp);
//        printf("\n\t\t\tFacing issue while reading file\n");
//        exit(1);
//    }
//    tmpp = fopen("tmpp.bin","wb");
//    if(tmpp == NULL)
//    {
//        fclose(tmpp);
//        printf("File tmpp is not opened\n");
//        exit(1);
//    }
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    fread (&fileHeaderInfo1,FILE_HEADER_SIZE1, 1, fp);
    fwrite(&fileHeaderInfo1,FILE_HEADER_SIZE1, 1, tmpFp);
    printf("\n\t\t\tEnter Student ID NO. for delete:");
    fflush(stdin);
    scanf("%d",&studentDelete);
    printf("%d dfsdfsdf/n",currentSem);
    if (fseek(fp,FILE_HEADER_SIZE+FILE_HEADER_SIZE1,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    while (fread (&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp))
    {
        printf("%u and %u",addStudentInfoInDataBase.enrolment_no, studentDelete);
        if(addStudentInfoInDataBase.enrolment_no != studentDelete)
        {
            fwrite(&addStudentInfoInDataBase,sizeof(addStudentInfoInDataBase), 1, tmpFp);
        }
        else
        {
            printf("gfdsgfdgssfgfd");
            enrolmentNo = addStudentInfoInDataBase.enrolment_no;
            strncpy(studentName,addStudentInfoInDataBase.studentName,sizeof(addStudentInfoInDataBase.studentName));
            strncpy(studyCentre, addStudentInfoInDataBase.studyCentre,sizeof(addStudentInfoInDataBase.studyCentre));
            strncpy(regionalCentre, addStudentInfoInDataBase.regionalCentre,sizeof(addStudentInfoInDataBase.regionalCentre));

            printf("%s%s%s",studentName,studyCentre,regionalCentre);
                currentSem = addStudentInfoInDataBase.current_sem;
                for(int i=0; i<NUM_SEM; i++)
                {
                    feePaid[i] = addStudentInfoInDataBase.feePaid[i];
                }
        }
    }
    fclose(fp);
    fclose(tmpFp);
//    fclose(tmpp);
    remove(FILE_NAME);
    tmpFp = fopen("tmp.bin","ab+");
    if(tmpFp == NULL)
    {
        fclose(tmpFp);
        printf("File tmpFp is not opened\n");
        exit(1);
    }
//    if (fseek(tmpFp,FILE_HEADER_SIZE,SEEK_SET) != 0)
//    {
//        fclose(tmpFp);
//        printf("\n\t\t\tFacing issue while reading file\n");
//        exit(1);
//    }
//    tmpp = fopen("tmpe.bin","rb");
//    if(tmpp == NULL)
//    {
//        fclose(tmpp);
//        printf("File is not opened\n");
//        exit(1);
//    }
//    fread(&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, tmpp);
//    char studentName[MAX_NAME];
//    strncpy(addStudentInfoInDataBase.studentName,studentName,sizeof(studentName));
//    char studyCentre[MAX_NAME];
//    strncpy(addStudentInfoInDataBase.studyCentre,studyCentre,sizeof(studyCentre));
//    char regionalCentre[MAX_NAME];
//    strncpy(addStudentInfoInDataBase.regionalCentre,regionalCentre,sizeof(regionalCentre));
//    unsigned int currentSem = addStudentInfoInDataBase.current_sem;
//    unsigned int feePaid[NUM_SEM];
//    for(int i=0; i<NUM_SEM; i++)
//    {
//        feePaid[i] = addStudentInfoInDataBase.feePaid[i];
//    }
//    fclose(tmpp);
    printf("%d",currentSem);
    for (int i=0; i<currentSem; i++)
    {
        for (int j=0; j<NUM_COURSE; j++)
        {
            do
            {
                printf("\n\t\t\tPlease Enter Assignment Marks Obtained in Semster %u for Course %s = ", i, courseInMCA[i][j]);
                fflush(stdin);
                addStudentInfoInDataBase.Amarks[i][j]=2;
//                scanf("%u",&addStudentInfoInDataBase.Amarks[i][j]);
//                printf("%u",addStudentInfoInDataBase.Amarks[i][j]);
                status = isMarksValid(addStudentInfoInDataBase.Amarks[i][j]);
                if (!status)
                {
                    printf("\n\t\t\tYou Entered Invalid Marks. Please enter again.");
                }
            }
            while(!status);
        }
	}
	addStudentInfoInDataBase.enrolment_no = enrolmentNo;
	strncpy(addStudentInfoInDataBase.studentName,studentName,sizeof(studentName));
    strncpy(addStudentInfoInDataBase.studyCentre,studyCentre,sizeof(studyCentre));
    strncpy(addStudentInfoInDataBase.regionalCentre,regionalCentre,sizeof(regionalCentre));
    addStudentInfoInDataBase.current_sem = currentSem;
    for(int i=0; i<NUM_SEM; i++)
    {
        addStudentInfoInDataBase.feePaid[i] = feePaid[i];
    }
    fwrite(&addStudentInfoInDataBase,sizeof(addStudentInfoInDataBase), 1, tmpFp);
    fclose(tmpFp);
    rename("tmp.bin",FILE_NAME);
    printf("%s",FILE_NAME);
    fflush(stdin);
    getchar();
}
void addTermEndMarks()
{
    sAdmin fileHeaderInfo = {0};
    sUser fileHeaderInfo1 = {0};
    char studentName[MAX_NAME];
    char studyCentre[MAX_NAME];
    char regionalCentre[MAX_NAME];
    unsigned int feePaid[NUM_SEM];
    unsigned int currentSem;
    unsigned int enrolementNo;
    int status = 0;
    int found = 0;
    unsigned int studentDelete = 0;
    sRegister addStudentInfoInDataBase = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    headMessage("Delete Student Details");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File fp is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","ab+");
    if(tmpFp == NULL)
    {
        fclose(tmpFp);
        printf("File tmpFp is not opened\n");
        exit(1);
    }
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    printf("%s dsfsdagf\n", fileHeaderInfo.username);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    fread (&fileHeaderInfo1,FILE_HEADER_SIZE1, 1, fp);
    printf("%s dsfsdagf\n", fileHeaderInfo1.username1);
    fwrite(&fileHeaderInfo1,FILE_HEADER_SIZE1, 1, tmpFp);
    printf("\n\t\t\tEnter Student ID NO. for delete:");
    fflush(stdin);
    scanf("%d",&studentDelete);
    printf("%d dfsdfsdf/n",currentSem);
    if (fseek(fp,FILE_HEADER_SIZE+FILE_HEADER_SIZE1,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    while (fread (&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp))
    {
        printf("%u and %u",addStudentInfoInDataBase.enrolment_no, studentDelete);
        if(addStudentInfoInDataBase.enrolment_no != studentDelete)
        {
            fwrite(&addStudentInfoInDataBase,sizeof(addStudentInfoInDataBase), 1, tmpFp);
        }
        else
        {
            printf("gfdsgfdgssfgfd");
            enrolementNo = addStudentInfoInDataBase.enrolment_no;
            strncpy(studentName,addStudentInfoInDataBase.studentName,sizeof(studentName));
            strncpy(studyCentre, addStudentInfoInDataBase.studyCentre,sizeof(studyCentre));
            strncpy(regionalCentre, addStudentInfoInDataBase.regionalCentre,sizeof(regionalCentre));

            printf("%s%s%s",studentName,studyCentre,regionalCentre);
                currentSem = addStudentInfoInDataBase.current_sem;
                for(int i=0; i<NUM_SEM; i++)
                {
                    feePaid[i] = addStudentInfoInDataBase.feePaid[i];
                }
        }
    }
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    tmpFp = fopen("tmp.bin","ab+");
    if(tmpFp == NULL)
    {
        fclose(tmpFp);
        printf("File tmpFp is not opened\n");
        exit(1);
    }
    printf("%d",currentSem);
    for (int i=0; i<currentSem; i++)
    {
        for (int j=0; j<NUM_COURSE; j++)
        {
            do
            {
                printf("\n\t\t\tPlease Enter Assignment Marks Obtained in Semster %u for Course %s = ", i, courseInMCA[i][j]);
                fflush(stdin);
                addStudentInfoInDataBase.TEmarks[i][j]=2;
//                scanf("%u",&addStudentInfoInDataBase.Amarks[i][j]);
//                printf("%u",addStudentInfoInDataBase.Amarks[i][j]);
                status = isMarksValid(addStudentInfoInDataBase.TEmarks[i][j]);
                if (!status)
                {
                    printf("\n\t\t\tYou Entered Invalid Marks. Please enter again.");
                }
            }
            while(!status);
        }
	}
	addStudentInfoInDataBase.enrolment_no = enrolementNo;
	strncpy(addStudentInfoInDataBase.studentName,studentName,sizeof(studentName));
    strncpy(addStudentInfoInDataBase.studyCentre,studyCentre,sizeof(studyCentre));
    strncpy(addStudentInfoInDataBase.regionalCentre,regionalCentre,sizeof(regionalCentre));
    addStudentInfoInDataBase.current_sem = currentSem;
    for(int i=0; i<NUM_SEM; i++)
    {
        addStudentInfoInDataBase.feePaid[i] = feePaid[i];
    }
    fwrite(&addStudentInfoInDataBase,sizeof(addStudentInfoInDataBase), 1, tmpFp);
    fclose(tmpFp);
    rename("tmp.bin",FILE_NAME);
    printf("%s",FILE_NAME);
    fflush(stdin);
    getchar();
//	int found = 0;
//    int enrolment_no =0;
//    int status = 0;
//    sRegister addStudentInfoInDataBase = {0};
//    FILE *fp = NULL;
//    fp = fopen(FILE_NAME,"rb+");
//    if(fp == NULL)
//    {
//        printf("\n\t\t\tFile is not opened\n");
//        exit(1);
//    }
//    headMessage("ADD TERM END MARKS");
//    //put the control on student detail
//    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
//    {
//        fclose(fp);
//        printf("\n\t\t\tFacing issue while reading file\n");
//        exit(1);
//    }
//    printf("\n\n\t\t\tEnter Enrolment Number to search:");
//    fflush(stdin);
//    scanf("%u",&enrolment_no);
//    while (fread (&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp))
//    {
//        if(addStudentInfoInDataBase.enrolment_no == enrolment_no)
//        {
//            found = 1;
//            break;
//        }
//    }
//    if(found)
//    {
//		for (int i=0; i<addStudentInfoInDataBase.current_sem; i++)
//		{
//			for (int j=0; j<NUM_COURSE; j++)
//			{
//				do
//				{
//					printf("\n\t\t\tPlease enter Term End Marks Obtained in Semster %u for Course %s = ", i, courseInMCA[i][j]);
//					fflush(stdin);
//					scanf("%u",&addStudentInfoInDataBase.TEmarks[i][j]);
//					status = isMarksValid(addStudentInfoInDataBase.TEmarks[i][j]);
//					if (!status)
//					{
//						printf("\n\t\t\tYou entered invalid Marks. Please enter again.");
//					}
//				}
//				while(!status);
//			}
//		}
//	}
//	fclose(fp);
}
void assignmentDate()
{
	int status = 0;
	int current_sem = 0;
	do
    {
        printf("\n\t\t\tCurrent Semester  = ");
        fflush(stdin);
		scanf("%u",&current_sem);
        status = isSemValid(current_sem);
        if (!status)
        {
            printf("\n\t\t\tYou entered invalid semester. Please enter again.");
        }
    }
    while(!status);
	printf("\n\t\t\tAssignment submission schedules for the semeter %d  are : \n",current_sem);
	for (int i=0; i<NUM_COURSE; i++)
	{
		printf("\n\t\t\t%s = On or before %s ",courseInMCA[current_sem][i],assignmentDates[current_sem][i]);
	}
	getch();
}
//Courses in Semester
void courses()
{
	int status = 0;
	int current_sem = 0;
	do
    {
        printf("\n\t\t\tCurrent Semester  = ");
        fflush(stdin);
		scanf("%u",&current_sem);
        status = isSemValid(current_sem);
        if (!status)
        {
            printf("\n\t\t\tYou entered invalid semester. Please enter again.");
        }
    }
	while(!status);
	printf("\n\t\t\tCourses in the semeter %d  are : ");
	for (int i=0; i<NUM_COURSE; i++)
	{
		printf("%s, ",courseInMCA[current_sem][i]);
	}
	getch();
}
//Term end marks
void termEndMarks()
{
    int found = 0;
    int enrolment_no =0;
    sRegister addStudentInfoInDataBase = {0};
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }
    headMessage("TERM END EXAM MARKS");
    //put the control on student detail
    if (fseek(fp,FILE_HEADER_SIZE+FILE_HEADER_SIZE1,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    printf("\n\n\t\t\tEnter Enrolment Number to search:");
    fflush(stdin);
    scanf("%u",&enrolment_no);
    while (fread (&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp))
    {
        if(addStudentInfoInDataBase.enrolment_no == enrolment_no)
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("\n\t\t\tStudent id = %d\n",addStudentInfoInDataBase.enrolment_no);
        printf("\n\t\t\tStudent name = %s",addStudentInfoInDataBase.studentName);
		printf("\n\t\t\tCurren Semester = %d\n",addStudentInfoInDataBase.current_sem);
		for (int i=0; i<addStudentInfoInDataBase.current_sem; i++)
		{
			printf("\n\t\t\tTerm End Exam Marks for Semester %u :\n",i);
			for (int j=0; j<NUM_COURSE; j++)
			{
				printf("\n\t\t\t %s = %u",courseInMCA[i][j],addStudentInfoInDataBase.TEmarks[i][j]);
			}
		}
	}
    else
    {
        printf("\n\t\t\tNo Record");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}
//Assignment marks
void assignmentMarks()
{
    int found = 0;
    int enrolment_no =0;
    sRegister addStudentInfoInDataBase = {0};
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }
    headMessage("ASSIGNMENT MARKS");
    //put the control on student detail
    if (fseek(fp,FILE_HEADER_SIZE+FILE_HEADER_SIZE1,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    printf("\n\n\t\t\tEnter Enrolment Number to search:");
    fflush(stdin);
    scanf("%u",&enrolment_no);
    while (fread (&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp))
    {
        if(addStudentInfoInDataBase.enrolment_no == enrolment_no)
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("\n\t\t\tStudent id = %d\n",addStudentInfoInDataBase.enrolment_no);
        printf("\n\t\t\tStudent name = %s",addStudentInfoInDataBase.studentName);
		printf("\n\t\t\tCurren Semester = %d\n",addStudentInfoInDataBase.current_sem);
		for (int i=0; i<addStudentInfoInDataBase.current_sem; i++)
		{
			printf("\n\t\t\tAssignment Marks for Semester %u :\n",i);
			for (int j=0; j<NUM_COURSE; j++)
			{
				printf("\n\t\t\t %s = %u",courseInMCA[i][j],addStudentInfoInDataBase.Amarks[i][j]);
			}
		}
	}
    else
    {
        printf("\n\t\t\tNo Record");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}
//Registration status
void registrationStatus()
{
	int totalFeePaid = 0;
    int found = 0;
    int enrolment_no =0;
    sRegister addStudentInfoInDataBase = {0};
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }
    headMessage("REGISTRATION STATUS");
    //put the control on student detail
    if (fseek(fp,FILE_HEADER_SIZE+FILE_HEADER_SIZE1,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    printf("\n\n\t\t\tEnter Enrolment Number to search:");
    fflush(stdin);
    scanf("%u",&enrolment_no);
    while (fread (&addStudentInfoInDataBase, sizeof(addStudentInfoInDataBase), 1, fp))
    {
        if(addStudentInfoInDataBase.enrolment_no == enrolment_no)
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("\n\t\t\tStudent id = %d\n",addStudentInfoInDataBase.enrolment_no);
        printf("\n\t\t\tStudent name = %s",addStudentInfoInDataBase.studentName);
        printf("\t\t\tFather Name = %s",addStudentInfoInDataBase.regionalCentre);
        printf("\n\t\t\tStudent Address = %s",addStudentInfoInDataBase.studyCentre);
        printf("\t\t\tStudent Admission Date(day/month/year) =  (%d/%d/%d)",addStudentInfoInDataBase.studentJoiningDate.dd,
               addStudentInfoInDataBase.studentJoiningDate.mm, addStudentInfoInDataBase.studentJoiningDate.yyyy);
		printf("\n\t\t\tCurren Semester = %d\n",addStudentInfoInDataBase.current_sem);
		for (int i=0; i<addStudentInfoInDataBase.current_sem; i++)
		{
			printf("\n\t\t\tTerm End Exam Marks for Semester %u : %u\n", i, addStudentInfoInDataBase.feePaid[i]);
			totalFeePaid += addStudentInfoInDataBase.feePaid[i];
		}
		printf ("\n\t\t\tTotal fee paid until now = %d", totalFeePaid);
    }
    else
    {
        printf("\n\t\t\tNo Record");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}
// Add student in list
void addStudentInDataBase()
{
    sRegister addStudentInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"ab+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    headMessage("ADD NEW Students");
    printf("\n\n\t\t\tENTER YOUR DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\tStudent ID  = ");
    fflush(stdin);
    scanf("%u",&addStudentInfoInDataBase.enrolment_no);
    do
    {
        printf("\n\t\t\tRegional Centre  = ");
        fflush(stdin);
        fgets(addStudentInfoInDataBase.regionalCentre,MAX_NAME,stdin);
        status = isNameValid(addStudentInfoInDataBase.regionalCentre);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tStudent Name  = ");
        fflush(stdin);
        fgets(addStudentInfoInDataBase.studentName,MAX_NAME,stdin);
        status = isNameValid(addStudentInfoInDataBase.studentName);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        printf("\n\t\t\tStudy Centre  = ");
        fflush(stdin);
        fgets(addStudentInfoInDataBase.studyCentre,MAX_NAME,stdin);
        status = isNameValid(addStudentInfoInDataBase.studyCentre);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    do
    {
        //get date year,month and day from user
        printf("\n\t\t\tEnter date in format (day/month/year): ");
        scanf("%d/%d/%d",&addStudentInfoInDataBase.studentJoiningDate.dd,&addStudentInfoInDataBase.studentJoiningDate.mm,&addStudentInfoInDataBase.studentJoiningDate.yyyy);
        //check date validity
        status = isValidDate(&addStudentInfoInDataBase.studentJoiningDate);
        if (!status)
        {
            printf("\n\t\t\tPlease enter a valid date.\n");
        }
    }
    while(!status);
	do
    {
        printf("\n\t\t\tCurrent Semester  = ");
        fflush(stdin);
		scanf("%u",&addStudentInfoInDataBase.current_sem);
        status = isSemValid(addStudentInfoInDataBase.current_sem);
        if (!status)
        {
            printf("\n\t\t\tYou entered invalid semester. Please enter again.");
        }
    }
    while(!status);
	for (int j=0; j<addStudentInfoInDataBase.current_sem; j++)
	{
		do
		{
			printf("\n\t\t\tPlease Enter Fee Paid in Semster %d= ", j+1);
			fflush(stdin);
			scanf("%u",&addStudentInfoInDataBase.feePaid[j]);
			status = isFeeValid(addStudentInfoInDataBase.feePaid[j]);
			if (!status)
			{
				printf("\n\t\t\tYou entered invalid Fee Amount. Please enter again.");
			}
		}
		while(!status);
	}
	for (int i=0; i<NUM_SEM; i++)
    {
        for (int j=0; j<NUM_COURSE; j++)
        {
            addStudentInfoInDataBase.Amarks[i][j]=1;
        }
    }
    for (int i=0; i<NUM_SEM; i++)
    {
        for (int j=0; j<NUM_COURSE; j++)
        {
            addStudentInfoInDataBase.TEmarks[i][j]=1;
        }
    }
    fwrite(&addStudentInfoInDataBase,sizeof(addStudentInfoInDataBase), 1, fp);
    fclose(fp);
}
//Display menu
void adminmenu()
{
    int choice = 0;
    do
    {
        headMessage("ADMIN MENU");
		printf("\n\n\n\t\t\t1.Add Student in database");
        printf("\n\t\t\t2.Add Assignment Marks");
        printf("\n\t\t\t3.Add Term End Marks");
        printf("\n\n\n\t\t\t4.Registration status");
        printf("\n\t\t\t5.Courses in current semester");
        printf("\n\t\t\t6.Assignment submission schedules");
        printf("\n\t\t\t7.Assignment marks");
        printf("\n\t\t\t8.Term end exam marks");
        printf("\n\t\t\t0. Quit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
			case 1:
				addStudentInDataBase();
				break;
			case 2:
				addAssignmentMarks();
				break;
			case 3:
				addTermEndMarks();
				break;
			case 4:
				registrationStatus();
				break;
			case 5:
				courses();
				break;
			case 6:
				assignmentDate();
				break;
			case 7:
				assignmentMarks();
				break;
			case 8:
				termEndMarks();
				break;
			case 0:
				printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
				exit(1);
				break;
			default:
				printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended
}
void usermenu()
{
    int choice = 0;
    do
    {
        headMessage("USER MENU");
        printf("\n\n\n\t\t\t1.Registration status");
        printf("\n\t\t\t2.Courses in current semester");
        printf("\n\t\t\t3.Assignment submission schedules");
        printf("\n\t\t\t4.Assignment marks");
        printf("\n\t\t\t5.Term end exam marks");
        printf("\n\t\t\t0. Quit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
			case 1:
				registrationStatus();
				break;
			case 2:
				courses();
				break;
			case 3:
				assignmentDate();
				break;
			case 4:
				assignmentMarks();
				break;
			case 5:
				termEndMarks();
				break;
			case 0:
				printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
				exit(1);
				break;
			default:
				printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended
}
void adminLogin()
{
	unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int L=0;
    sAdmin fileHeaderInfo = {0};
    FILE *fp = NULL;
    headMessage("ADMIN LOGIN");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
//    int found = 0;
//    printf("\n\n\n\t\t\t\tUsername:");
//    fflush(stdin);
//    fgets(userName,MAX_SIZE_USER_NAME,stdin);
//    printf("\n\t\t\t\tPassword:");
//    fgets(password,MAX_SIZE_PASSWORD,stdin);
//    while (fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp))
//    {
//        if(fileHeaderInfo.username == userName)
//        {
//            found = 1;
//            break;
//        }
//    }
//    if(found)
//    {
//        if((!strcmp(userName,fileHeaderInfo.username)) && (!strcmp(password,fileHeaderInfo.password)))
//        {
//            adminmenu();
//        }
//        else
//        {
//            printf("\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
//            L++;
//        }
//    }
//    else
//    {
//        printf("\n\t\t\tNo Record");
//    }
//    fclose(fp);
//    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
//    fflush(stdin);
//    getchar();
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    printf("%s gfsdgfsdsdds",fileHeaderInfo.username);
    do
    {
        printf("\n\n\n\t\t\t\tUsername:");
        fflush(stdin);
        fgets(userName,MAX_SIZE_USER_NAME,stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(password,MAX_SIZE_PASSWORD,stdin);
        if((!strcmp(userName,fileHeaderInfo.username)) && (!strcmp(password,fileHeaderInfo.password)))
        {
            adminmenu();
        }
        else
        {
            printf("\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        headMessage("Login Failed");
        printf("\t\t\t\tSorry,Unknown User.");
        getch();
        system("cls");
    }
}
void userLogin()
{
	unsigned char username[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int L=0;
    sUser fileHeaderInfo1 = {0};
    FILE *fp = NULL;
    headMessage("USER LOGIN");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    fread (&fileHeaderInfo1,FILE_HEADER_SIZE1, 1, fp);
    printf("%s fdgfdgsdfg",fileHeaderInfo1.username1);
    fclose(fp);
    do
    {
        printf("\n\n\n\t\t\t\tUsername:");
        fflush(stdin);
        fgets(username,MAX_SIZE_USER_NAME,stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(password,MAX_SIZE_PASSWORD,stdin);
        if((!strcmp(username,fileHeaderInfo1.username1)) && (!strcmp(password,fileHeaderInfo1.password1)))
        {
            usermenu();
        }
        else
        {
            printf("\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        headMessage("Login Failed");
        printf("\t\t\t\tSorry,Unknown User.");
        getch();
        system("cls");
    }
}
//Check file exist or not
int isFileExists(const char *path)
{
    // Try to open file
    FILE *fp = fopen(path, "rb");
    int status = 0;
    // If file does not exists
    if (fp != NULL)
    {
        status = 1;
        // File exists hence close file
        fclose(fp);
    }
    return status;
}
//User initialization
void userInit()
{
    FILE *fp = NULL;
    int status = 0;
    char Username[] ="user\n";
    char Password[] ="user\n";
    sUser fileHeaderInfo1 = {0};
    if(!status)
    {
        //create the binary file
        fp = fopen(FILE_NAME,"ab+");
        if(fp != NULL)
        {
            //Copy default password
            strncpy(fileHeaderInfo1.password1,Password,sizeof(Password));
            strncpy(fileHeaderInfo1.username1,Username,sizeof(Username));
            printf("%s",fileHeaderInfo1.username1);
            fwrite(&fileHeaderInfo1,FILE_HEADER_SIZE1, 1, fp);
            fclose(fp);
        }
    }
}
//Admin initialization
void adminInit()
{
    FILE *fp = NULL;
    int status = 0;
    char defaultUsername[] ="admin\n";
    char defaultPassword[] ="admin\n";
    sAdmin fileHeaderInfo = {0};
    status = isFileExists(FILE_NAME);
    if(!status)
    {
        //create the binary file
        fp = fopen(FILE_NAME,"wb+");
        if(fp != NULL)
        {
            //Copy default password
            strncpy(fileHeaderInfo.password,defaultPassword,sizeof(defaultPassword));
            strncpy(fileHeaderInfo.username,defaultUsername,sizeof(defaultUsername));
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}
int main()
{
	welcomeMessage();
	int choice = 0;
    do
    {
        headMessage("LOGIN PAGE");
        printf("\n\n\n\t\t\t1.Admin Login");
        printf("\n\t\t\t2.User Login");
        printf("\n\t\t\t0. Quit");
        printf("\n\n\n\t\t\tEnter choice => ");
        adminInit();
        userInit();
        scanf("%d",&choice);
        switch(choice)
        {
			case 1:
				adminLogin();
				break;
			case 2:
				userLogin();
				break;
			case 0:
				printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
				exit(1);
				break;
			default:
				printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    }
    while(choice!=0);
    return 0;
}
