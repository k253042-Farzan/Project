#include <stdio.h>
#include <stdlib.h>


int booking (int room[][6][5]){
     int roomtype = 0;
    int room_size = 0;
    int error=0;


int count=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<6;j++){
            if(room[i][j][1]==1){
                count++;
            }
        }
    }
    if(count==18){
        printf("\n//All Rooms Are Booked!//");
        return 0;
       
    }

    // --- Room Type ---
    do {
        printf("\nSelect Room Type: ");
        printf("\n1. Standard\n2. Deluxe\n3. Executive\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &roomtype);

        if (roomtype < 1 || roomtype > 3)
            printf("\nInvalid input! Please select 1, 2, or 3.\n");

    } while(roomtype < 1 || roomtype > 3);

    // --- Room Size ---
    do {
        printf("\nSelect Room Size: ");
        printf("\n1. Single (1 person)\n2. Double (2 person)\n3. Family (4-8 person) \n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &room_size);

        if (room_size < 1 || room_size > 3)
            printf("\nInvalid input! Please select 1, 2, or 3.\n");

    } while(room_size < 1 || room_size > 3);
    int pos=0;
    if (room_size==1){
        pos=0;
    }else if(room_size==2){
        pos=2;
    }else if(room_size==3){
        pos=4;
    }

int check=0,valid=0;
// checking rooms are valid and position of room.
    for (int i = 0; i < 2; i++,pos++)
    {
        if (room[roomtype-1][pos][1]==0){

           check=room[roomtype-1][pos][0];
           i=2;
           break;
        }else{
            valid++;
        }
       
    }

    if (valid==2){
        printf("\n//Your Selected Category Room's Are Booked!\n//");
          return 0;

    }
    char name[50];
   for(int i=0;i<3;i++){
    for(int j=0;j<6;j++){
     if(room[i][j][0] == check){
        printf("\nEnter your Name: ");
        scanf(" %[^\n]", &name);
        printf("\nEnter your CNIC number: ");
        scanf("%d",&room[i][j][4]);
        printf("\nEnter Number of days: ");
        scanf("%d",&room[i][j][2]);
        room[i][j][1]=1;
        printf("\n=======================\n");
        printf("Room Booked Succesfully.");
        printf("=======================\n");
         j=6;
         i=3;
   
            }
    }
   }
   
return 0;
}


int main() {
    int room[3][6][5] = {
        // Standard
        {
            {1,0,0,5000,0}, {2,0,0,5000,0}, {3,0,0,10000,0}, {4,1,0,10000,0}, {5,0,0,15000,0}, {6,1,0,15000,0}
        },
        // Deluxe
        {
            {7,1,0,7000,0}, {8,1,0,7000,0}, {9,1,0,12000,0}, {10,1,0,12000,0}, {11,1,0,17000,0}, {12,1,0,17000,0}
        },
        // Executive
        {
            {13,0,0,10000,0}, {14,0,0,10000,0}, {15,1,0,17000,0}, {16,1,0,17000,0}, {17,1,0,30000,0}, {18,1,0,30000,0}
        }
    };

    int choice=0;
    int all_book=0;

    printf("====================\n");
    printf("Welcome To ABC Hotel\n");
    printf("====================\n");

    do{
        printf("\n1. Book A Room\n2. Check Out\n3. Check Vacant Room\n4. Login as Manager\n5. Exit\n\nEnter (1-5): ");
        scanf("%d",&choice);

        switch(choice) {

            case 1:
              all_book =  booking(room);
              if(all_book==0){
                system("pause");
                system("cls");
              }
                break;

            case 2:
           
             
                break;

            case 3:
       
                break;

            case 4:
                 
                  break;
            case 5:
            	
            	break;
            default:
                printf("\nInvalid choice! Try again.\n");
                choice = 0;   // repeat
                break;
        }

    }while(choice != 5);

    return 0;
}