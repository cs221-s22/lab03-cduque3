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
      char *argument = argv[i];
      char name[50] = ""; //value to hold name
      char quantity[50] = ""; //value to hold quantity
      int j = 0;

      //get the name of product
      while(argument[j] != ' ') {
         strncat(name, &argument[j], 1);
         j++;
      }

      //check if name is longer than 15 characters, terminate program if so
      if( strlen( name ) > 15 ) {
         printf( "string overflow: %s\n", name );
         return -1;
      }

      j++; //skip the space

      //get the quantity of product
      while(argument[j] != '\0') {
         strncat(quantity, &argument[j], 1);
         j++;
      }

      //check that quantity does not contain non-numbers, terminate program if so
      for(int n = 0; n < strlen(quantity); n++) {
            if( !( quantity[n] >= '0' && quantity[n] <= '9' )) {
               printf( "not a number: %s", quantity );
               return -1;
            }
      }

      //put acquired values into struct
      object->quantity = quantity;
      object->name = name;

      fprintf( file, "%s,%s\n", object->name, object->quantity ); //finally, populate .csv file with struct values
      }

   fclose(file); //close file

   return 0;
}
