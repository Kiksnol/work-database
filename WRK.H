/* ND4 */
#include <conio.h>
#include <stdio.h>

typedef struct
{
  int Day, Month, Year;
} DATE;

typedef struct
{
  char Name[30], Surname[47];
  DATE Birthday;
  char Sex;
  int Hours[7];
} WORKER;

void ReadWorker( WORKER *W );
void GetStr( char *Str, int MaxLen );

int SaveDB( char *FileName, WORKER * Base, int N );
int LoadDB( char *FileName, WORKER * Base, int Maxsize );
void RemoveWorker( WORKER *A, int n, int MaxSize );
void Sort( WORKER *A, int N, int (*IsLess)( WORKER A, WORKER B ) );
int IsNameLess( WORKER A, WORKER B );
int IsDateLess( WORKER A, WORKER B );
void Reverse( WORKER *A, int MaxSize );
void EditLine( char *S, int MaxLen );
float GetMoney( WORKER *A, float salary, int Days, int MaxSize );
int Report( WORKER *A, int MaxSize, int Days, float salary, char *fname );