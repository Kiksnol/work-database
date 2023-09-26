/* ND4 */

#include "WRK.h"

#define MAX 47

void main( void )
{
  int run = 1, DBSize = 0, i, n, k;
  float salary;
  static WORKER DB[MAX];
  char fname[100], choice, FileName[100], tmp[10];

  while (run)
  {
    printf("___________________________________________\n"
         "\n  Input a nuber to do something: \n"
         "  0 - exit\n"
         "  1 - input a new worker\n"
         "  2 - output every worker\n"
         "  3 - delete worker\n"
         "  4 - sort by names or by date of birth\n    1)By names \n    2)By date of birth\n"
         "  5 - reverse\n"
         "  6 - save data base into file\n"
         "  7 - load data base from file\n"
         "  8 - edit worker\n"
         "  9 - show salary\n"
         "___________________________________________\n");

    switch(_getch())
    {
    case '0':
      run = 0;
      break;
    case '1':
      if (DBSize < MAX)
        ReadWorker(&DB[DBSize++]);
      else
        printf("Not enough room\n");
      break;
    case '2':
      for (i = 0; i < DBSize; i++)
        printf("%d) %s %s.\nBirthday date: %02d/%02d/%d.\nSex: %c. \n"
        "Monday hours: %d\n"
        "Tuesday hours: %d\n"
        "Wednesday hours: %d\n"
        "Thursday hours: %d\n"
        "Friday hours: %d\n"
        "Saturday hours: %d\n"
        "Sunday hours: %d\n", i + 1, DB[i].Surname, DB[i].Name, DB[i].Birthday, DB[i].Sex, DB[i].Hours[0], DB[i].Hours[1], DB[i].Hours[2], DB[i].Hours[3], DB[i].Hours[4], DB[i].Hours[5], DB[i].Hours[6]);
      break;
    case '3':
      printf("Which one you would like to remove? ");
      scanf("%d", &n);
      RemoveWorker(DB, n - 1, MAX);
      DBSize--;
      break;
    case '4':
      if (DBSize > 0)
      {
        printf("Enter 1 or 2: ");
        scanf("%s", &choice);
        if (choice == '1')
        {
          Sort(DB, DBSize, IsNameLess);
          printf("OK\n");
        }
        else if (choice == '2')
        {
          Sort(DB, DBSize, IsDateLess);
          printf("OK\n");
        }
        else
          printf("No one is working here(\n");
      }
      else
        printf("DB is empty\n");
      break;
    case '5':
      if (DBSize > 0)
      {
        printf("Doing reverse for data base. . .\n");
        Reverse(DB, DBSize);
        printf("Done\n");
      }
      else
        printf("DB is empty\n");
      break;
    case '6':
      printf("Save file name: ");
      GetStr(fname, sizeof(fname));
      if (SaveDB(fname, DB, DBSize))
        printf("OK\n");
      else
        printf("ERROR\n");
      break;
    case '7':
      printf("Load file name: ");
      GetStr(fname, sizeof(fname));
      DBSize += LoadDB(fname, DB + DBSize, MAX - DBSize);
      printf("Load %d records\n", DBSize);
      break;
    case '8':
      if (DBSize > 0)
      {
        printf("Enter worker's number: \n");
        scanf("%d", &n);

        if (n <= DBSize && n > 0)
        {
          printf("\nEdit name: \n");
          EditLine(DB[n - 1].Name, sizeof DB[n - 1].Name);

          printf("\nEdit surname: \n");
          EditLine(DB[n - 1].Surname, sizeof DB[n - 1].Surname);

          printf("\nEdit b-day day: \n");
          sprintf(tmp, "%d", DB[n - 1].Birthday.Day);
          EditLine(tmp, 10);        
          sscanf(tmp, "%d", &DB[n - 1].Birthday.Day);

          printf("\nEdit b-day month: \n");
          sprintf(tmp, "%d", DB[n - 1].Birthday.Month);
          EditLine(tmp, 10);        
          sscanf(tmp, "%d", &DB[n - 1].Birthday.Month);

          printf("\nEdit b-day year: \n");
          sprintf(tmp, "%d", DB[n - 1].Birthday.Year);
          EditLine(tmp, 10);        
          sscanf(tmp, "%d", &DB[n - 1].Birthday.Year);

          printf("\nEdit sex: \n");
          tmp[0] = DB[n - 1].Sex;
          EditLine(tmp, 2);
          DB[n - 1].Sex = tmp[0];

          printf("\nEdit day hours: \n");

          for (i = 0; i < 7; i++)
          {
            printf("%d)", i + 1);
            sprintf(tmp, "%d", DB[n - 1].Hours[i]);
            EditLine(tmp, 10);        
            sscanf(tmp, "%d", &DB[n - 1].Hours[i]);
          }
        }
      
        else 
          printf("There is no such worker");
        break;
      }
      else
        printf("DB is empty\n");
      _getch();
      break;
    case '9':
      if (DBSize > 0)
      {
          printf("How many days? ");
          scanf("%d", &k);
          GetStr(NULL, 0);
          
          printf("1 hour salary: ");
          scanf("%f", &salary);
          GetStr(NULL, 0);
          
          printf("In what file do u wanna save report? ");
          GetStr(FileName, sizeof(FileName));
          
          if (Report(DB, DBSize, k, salary, FileName))
            printf("DONE\n");
          else
            printf("Oops! Something went wrong!\n");
      }
      else
        printf("Data base is empty");
      break;
    default:
      printf("Incorrect choice\n");
      break;
    }
  }
}
