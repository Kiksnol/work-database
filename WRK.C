/* ND4 */
#include <stdlib.h>
#include <string.h>

#include "WRK.h"

void GetStr( char *Str, int MaxLen )
{
  int i = 0;
  char ch;

  while ((ch = getchar()) != '\n')
    if (Str != NULL && i < MaxLen - 1)
      Str[i++] = ch;
  if (Str != NULL && i < MaxLen)
    Str[i] = 0;
}

void ReadWorker( WORKER *W )
{
  int i;

  printf("Name: ");
  GetStr(W->Name, sizeof W->Name);

  printf("Surname: ");
  GetStr(W->Surname, sizeof W->Surname);

  printf("Birthday:\nYear:\n");
  scanf("%d", &W->Birthday.Year);
  GetStr(NULL, 0);

  printf("Month:\n");
  scanf("%d", &W->Birthday.Month);
  GetStr(NULL, 0);

  printf("Day:\n");
  scanf("%d", &W->Birthday.Day);
  GetStr(NULL, 0);

  printf("Sex(f/m): \n");
  scanf("%c", &W->Sex);
  GetStr(NULL, 0);

  printf("Hours:\n");
  for (i = 0; i < 7; i++)
  {
    printf("  %d) ", i + 1);
    scanf("%d", &W->Hours[i]);
  }
}

void RemoveWorker( WORKER *A, int n, int MaxSize )
{
  int i;

  for (i = n; i < MaxSize; i++)
    A[i] = A[i + 1];
}

int SaveDB( char *FileName, WORKER * Base, int N )
{
  FILE *F;

  if ((F = fopen(FileName, "wb")) == NULL)
    return 0;

  fwrite(Base, sizeof(WORKER), N, F);
  fclose(F);

  return 1;
}

int LoadDB( char *FileName, WORKER * Base, int Maxsize )
{
  int N;
  FILE *F;

  if ((F = fopen(FileName, "rb")) == NULL)
    return 0;
  N = fread(Base, sizeof(WORKER), Maxsize, F);
  fclose(F);
  return N;
}

void Swap( WORKER *A, WORKER *B )
{
  WORKER Tmp = *A;

  *A = *B;
  *B = Tmp;
}

void Sort( WORKER *A, int N, int (*IsLess)( WORKER A, WORKER B ) )
{
  int i, j;
  WORKER Tmp;

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)  
      if (IsLess(A[i], A[j]) && i != j)
      {
        Tmp = A[i];
        A[i] = A[j];
        A[j] = Tmp;
      }
}

int IsNameLess( WORKER A, WORKER B )
{
  int n = strcmp(A.Surname, B.Surname);

  if (n == 0)
    return strcmp(A.Name, B.Name) < 0;
  return n < 0;
}

int IsDateLess( WORKER A, WORKER B )
{
  if (A.Birthday.Year == B.Birthday.Year)
    if (A.Birthday.Month == B.Birthday.Month)
      return A.Birthday.Day < B.Birthday.Day;
    else
      return A.Birthday.Month < B.Birthday.Month;
  else
    return A.Birthday.Year < B.Birthday.Year;
}

void Reverse( WORKER *A, int MaxSize )
{
  WORKER Tmp;
  int i;

  for (i = 0; i < MaxSize / 2; i++)
  {
    Tmp = A[i];
    A[i] = A[MaxSize - 1 - i];
    A[MaxSize - 1 - i] = Tmp;
  }
}

void EditLine( char *S, int MaxLen )
{
  int run_flag = 1, len = strlen(S), pos = len, i;
  char ch;

  printf("%s", S);
  while (run_flag)
  {
    switch ((unsigned char)(ch = _getch()))
    {
    case '\r':
      run_flag = 0;
      break;
    case '\b':
      /* back-space */
      if (pos > 0)
      {
        memmove(S + pos - 1, S + pos, len - pos + 1);
        len--;
        pos--;
        printf("\b");
        for (i = pos; i < len; i++)
          printf("%c", S[i]);
        printf(" \b");
        for (i = len - 1; i >= pos; i--)
          printf("\b");
      }
      break;
    case 224:
      switch (_getch())
      {
      case 75:
        /* left */
        if (pos > 0)
          pos--, printf("\b");
        break;
      case 77:
        /* right */
        if (pos < len)
          printf("%c", S[pos++]);
        break;
      case 83:
        /* delete */
        if (pos < len)
        {
          memmove(S + pos, S + pos + 1, len - pos + 1);
          len--;
          for (i = pos; i < len; i++)
            printf("%c", S[i]);
          printf(" \b");
          for (i = len - 1; i >= pos; i--)
            printf("\b");
        }
        break;
      case 71:
        /* home */
        for (i = pos; i > 0; i--)
          printf("\b");
        pos = 0;
        break;
      case 79:
        /* end */
        for (i = pos; i < len; i++)
          printf("%c", S[i]);
        pos = len;
        break;
      }
      break;
    default:
      if ((unsigned char)ch >= ' ' && pos < MaxLen - 1)
      {
        /* insert a new symbol */
        memmove(S + pos + 1, S + pos, len - pos + 1);
        S[pos] = ch;
        len++;
        for (i = pos; i < len; i++)
          printf("%c", S[i]);
        for (i = len - 1; i > pos; i--)
          printf("\b");
        pos++;
      }
    }
  }
  printf("\n");
}

float GetMoneyForOneWorker( WORKER *A, float salary, int n , int Days )
{
  float DailySalary;
  int sum_hrs, i;

  for (i = 0, sum_hrs = 0; i < Days; i++)
    sum_hrs += A[n].Hours[i % 7];

  DailySalary = sum_hrs * salary;

  return DailySalary;
}

float GetMoney( WORKER *A, float salary, int Days, int MaxSize )
{
  float sum;
  int i;

  for (i = 0, sum = 0; i < MaxSize; i++)
    sum += GetMoneyForOneWorker(A, salary, i, Days);

  return sum;
}

int Report( WORKER *A, int MaxSize, int Days, float salary, char *fname )
{
  int i;
  FILE *F;

  if ((F = fopen(fname, "w")) == NULL)
  {
    printf("FILE '%s' HAS BEEN NOT FOUND", fname);
    getchar();
    return 0;
  }
  fprintf(F, "Amount of money for workers\nTotal: %f rubles\nBy each: \n", GetMoney(A, salary, Days, MaxSize));
  for (i = 0; i < MaxSize; i++)
    fprintf(F, "%d) %s %s: %f rubles\n", i + 1, A[i].Surname, A[i].Name, GetMoneyForOneWorker(A, salary, i, Days));
  fclose(F);
  return 1;
}
  /*
   case '8':
      printf("number worker edit: ");
      scanf("%d", &n);
      GetStr(NULL, 0);
      printf(
        "  a - edit name\n"
        "  b - edit surname\n"
        "  c - edit birthday\n"
        "  d - edit sex\n"
        "  e - edit work hours\n"
        "  0 - cancel\n"
        );
      switch (_getch())
      {
      case 'a':
        EditLine(DB[n - 1].Name, 30);
        break;
      case 'b':
        EditLine(DB[n - 1].Surname, 47);
        break;
      case 'c':
        printf(
          "    d - edit day\n"
          "    e - edit month\n"
          "    f - edit year\n"
          "    0 - cancel\n"
          );
         switch (_getch())
         {
         case 'd':
           sprintf(tmp, "%d", DB[n - 1].Birthday.Day);
           EditLine(tmp, 10);        
           sscanf(tmp, "%d", &DB[n - 1].Birthday.Day);        
           break;
         case 'e':
           sprintf(tmp, "%d", DB[n - 1].Birthday.Month);
           EditLine(tmp, 10);        
           sscanf(tmp, "%d", &DB[n - 1].Birthday.Month);                   
           break;
         case 'f':
           sprintf(tmp, "%d", DB[n - 1].Birthday.Year);
           EditLine(tmp, 10);        
           sscanf(tmp, "%d", &DB[n - 1].Birthday.Year);                   
           break;
         case '0': 
           break;
         }
        break;
      case 'd':
        tmp[0] = DB[n - 1].Sex;
        EditLine(tmp, 2);
        DB[n - 1].Sex = tmp[0];
        break;
      case 'e':
        printf("  number of day: ");
        scanf("%d", &k);
        GetStr(NULL, 0);

        sprintf(tmp, "%d", DB[n - 1].Hours[k]);
        EditLine(tmp, 10);        
        sscanf(tmp, "%d", &DB[n - 1].Hours[k]);        
        break;
      case '0':
        break;
      }
      break;
 */