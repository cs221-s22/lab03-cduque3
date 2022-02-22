#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char *name;
	char *quantity;
} name_qty;

int main(int argc, char *argv[]) {

   //exit program if improper number of arguments provided
   if( argc < 3 ) {
   printf( "usage: lab03 filename 'name qty' ['name qty']" );
      return -1;
   }

   //if improper .csv file opened
   if ( strcmp ( argv[1] , "lab03.csv" ) ) {
      printf( "failed to open: %s\n", argv[1] );
      return -1;
   }

   //create file object and open lab03.csv, first thing to be printed is: name,quantity
   FILE * file;
   file = fopen( "lab03.csv", "w" );
   fprintf( file, "name,quantity\n" );

   //allocate memory for struct
   name_qty *object;
   object = ( name_qty *)malloc( argc * sizeof(name_qty) );

   //for loop to put values in arguments into lab03.csv
   for(int i = 2; i < argc; i++) {

      //making this in case the original value needs to be displayed for string overflow error
      char overflow[50];
      strcpy(overflow, argv[i]);

      //get first value (name of object) inside the argument, print error if more than 15 characters
      argv[i] = strtok( argv[i], " " );
      if( strlen( argv[i] ) > 15 ) {
         printf( "string overflow: %s\n", overflow );
         return -1;
      }

      object->name = argv[i] ; //put value into 'name' data member of struct

      //get second value (quantity of object) inside the argument, print error if not a number
      argv[i] = strtok( NULL, " " );
      for( int j = 0; j < strlen(argv[i]); j++ ) {
         if( !( argv[i][j] >= '0' && argv[i][j] <= '9' )) {
            printf( "not a number: %s", argv[i] );
            return -1;
         }
      }

      object->quantity = argv[i]; //put value into 'quantity' data member of struct

      fprintf( file, "%s,%s\n", object->name, object->quantity ); //finally, populate .csv file with values
   }

   fclose(file); //close file

   return 0;
}
