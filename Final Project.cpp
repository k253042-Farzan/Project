#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BookingInfo {
    char name[50];
    int roomtype;
};

// Global variable to store the current booking's information
struct BookingInfo info;

// Booking function
int booking (int room[][6][5]){
    int roomtype = 0;
    int room_size = 0;
    int error=0;
    int count=0;

    // Count all booked rooms
    for(int i=0;i<3;i++){
        for(int j=0;j<6;j++){
            if(room[i][j][1]==1){
                count++;
            }
        }
    }

    // If all rooms are booked
    if(count==18){
        printf("\n//All Rooms Are Booked!//");
        return 0;
    }

    // --- Room Type Selection ---
    do {
        printf("\nSelect Room Type: ");
        printf("\n1. Standard\n2. Deluxe\n3. Executive\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &roomtype);
        info.roomtype = roomtype;

        if (roomtype < 1 || roomtype > 3)
            printf("\nInvalid input! Please select 1, 2, or 3.\n");

    } while(roomtype < 1 || roomtype > 3);

    // --- Room Size Selection ---
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
        if (room[roomtype-1][pos][1]==0){// pos for finding single/double/family 
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

    // Customer details and booking
    char name[50];
    for(int i=0;i<3;i++){
        for(int j=0;j<6;j++){
            if(room[i][j][0] == check){
                printf("\nEnter your Name: ");
                scanf(" %[^\n]", &name);
                strcpy(info.name, name); // store into global structure

                printf("Enter your CNIC number: ");
                scanf("%d",&room[i][j][4]);

                printf("Enter Number of days: ");
                scanf("%d",&room[i][j][2]);

                room[i][j][1]=1; // mark room as booked

                printf("\n\nYour Room No is: %d\n", room[i][j][0]);
                printf("\033[1;32m"); //colour
                printf("\n=======================\n");
                printf("Room Booked Succesfully.");
                printf("\n=======================\n");
                printf("\033[0m");  

                // --------- FILE HANDLING ---------
                // Create a file named by CNIC to store booking details
                char filename[20];
                sprintf(filename, "%d.txt", room[i][j][4]); // filename = CNIC.txt
                FILE *fp = fopen(filename, "w"); // open file for writing
                if(fp != NULL){
                    int totalroomcost = room[i][j][2] * room[i][j][3]; // days * price per night
                    int Total = totalroomcost + 500 + 2000 + 1000; // room + service + food + tax

                    fprintf(fp, "Room Number: %d\n", room[i][j][0]);
                    fprintf(fp, "Guest Name: %s\n", info.name);
                    fprintf(fp, "CNIC: %d\n", room[i][j][4]);
                    fprintf(fp, "Days of Stay: %d\n", room[i][j][2]);
                    fprintf(fp, "Total Bill: Rs. %d\n", Total);

                    fclose(fp); // close the file
                }else{
                    printf("Error creating file!\n");
                }
                // ---------------------------------

                j=6; // exit inner loop
                i=3; // exit outer loop
            }
        }
    }
    return 0;
}

int main() {
    int room[3][6][5] = { //{roomid, roomstatus (0 for booked and 1 for free), days of stay, rates, cnic}
        // Standard
        {
            {1,0,0,5000,0}, {2,0,0,5000,0}, {3,0,0,10000,0}, {4,0,0,10000,0}, {5,0,0,15000,0}, {6,1,0,15000,0}
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
    int all_book=0,n=0,count=0, vacant=0;
    char pass[10], usern[10];
    char correctusern[6]="admin", correctpass[7]="123456";
    int bookedroom, recheckcnic;
    int serviceCharges = 500, foodCharges=2000, Total=0, taxR= 20, taxA = 1000, dos, pricepernight, totalroomcost;
    
    printf("\033[1;35m");   
    printf("====================\n");
    printf("Welcome To ABC Hotel\n");
    printf("====================\n");
    printf("\033[0m");  
   
    // Login
    do{
        printf("\n1. Login as Manager\n2. Login as Staff\n\nEnter(1-2): ");
        scanf("%d",&n);
    }while(n!=1 && n!=2);

    if(n==1){
        printf("\nEnter Username: ");
        scanf(" %s", &usern);
        printf("Enter Password: ");
        scanf(" %s", &pass);
        if(strcmp(usern, correctusern)==0 && strcmp(pass, correctpass)==0){
            printf("\n//Logged in Successfully.//\n");
            int count=0;
            for(int i=0;i<3;i++){
                for(int j=0;j<6;j++){
                    if(room[i][j][1]==1){
                        count++;
                    }
                }
            }
            printf("\nRooms Booked: %d",count);
            vacant = 18-count;
            printf("\nRooms Vacant: %d", vacant);
        } else {
            printf("\n//Invalid Username or Password.//");
            system("pause");
            return 1;
        }
    }else{
        do{
            printf("\n1. Book A Room\n2. Rates\n3. Check Vacant Room\n4. Checkout\n5. Exit\n\nEnter (1-5): ");
            scanf("%d",&choice);

            switch(choice) {

                case 1:  //Calling Booking  function
                    all_book = booking(room);
                    if(all_book==0){
                        system("pause");
                        system("cls");
                    }
                    break;

                case 2:  //Rates
                    printf("\nStandard:\n 1. Single (1 person) = 5000\n 2. Double (2 person) = 10000\n 3. Family (4-8 person) = 15000\n ");
                    printf("\nDeluxe:\n 1. Single (1 person) = 7000\n 2. Double (2 person) = 12000\n 3. Family (4-8 person) = 17000\n ");
                    printf("\nExecutive:\n 1. Single (1 person) = 10000\n 2. Double (2 person) = 17000\n 3. Family (4-8 person) = 30000\n ");
                    system("pause");
                    system("cls");
                    break;

                case 3:   //Vacant Room
                    for (int i = 0; i < 3; i++){
                        int x=0;
                        for(int j=0;j<6;j++){
                            if (room[i][j][1]==0){
                                x++;
                            }
                        } 
                        if(i==0) printf("\n%d rooms are free in Standard\n",x);
                        if(i==1) printf("%d rooms are free in Deluxe\n",x);
                        if(i==2) printf("%d rooms are free in Executive\n",x);
                    }
                    system("pause");
                    system("cls");
                    break;

                case 4: // Checkout 
                    printf("\n\nEnter the Room No you Booked: ");
                    scanf("%d", &bookedroom);
                    printf("Enter your CNIC number: ");
                    scanf("%d", &recheckcnic);
                    int found = 0;  
                    char roomTypeName[20];

                    for(int i=0;i<3;i++){
                        for(int j=0;j<6;j++){
                            if(room[i][j][0] == bookedroom && room[i][j][4] == recheckcnic){
                                found = 1;
                                if(info.roomtype == 1) strcpy(roomTypeName, "Standard");
                                else if(info.roomtype == 2) strcpy(roomTypeName, "Deluxe");
                                else if(info.roomtype == 3) strcpy(roomTypeName, "Executive");

                                dos = room[i][j][2];             
                                pricepernight = room[i][j][3];    
                                totalroomcost = dos * pricepernight;
                                Total = totalroomcost + serviceCharges + foodCharges + taxA;
                                printf("\033[1;36m");  
                                printf("========================================================\n");
                                printf("                      ABC Hotel\n");
                                printf("              Customer Billing Receipt\n");
                                printf("========================================================\n\n");

                                printf("Guest Name          : %s\n", info.name);
                                printf("CNIC / ID No.       : %d\n", recheckcnic);
                                printf("Room Number         : %d\n", bookedroom);
                                printf("Room Type           : %s\n", roomTypeName);
                                printf("Total Days Of Stay  : %d\n\n", dos);

                                printf("--------------------------------------------------------\n");
                                printf("                   Charges Summary\n");
                                printf("--------------------------------------------------------\n");
                                printf("Room Price per Night  : Rs. %d\n", pricepernight);
                                printf("Total Room Charges    : Rs. %d\n", totalroomcost);
                                printf("Service Charges       : Rs. %d\n", serviceCharges);
                                printf("Food / Extras         : Rs. %d\n", foodCharges);
                                printf("Tax (%d%%)             : Rs. %d\n", taxR, taxA);
                                printf("--------------------------------------------------------\n");
                                printf("Grand Total           : Rs. %d\n", Total);
                                printf("--------------------------------------------------------\n\n");
                                printf("\nThank you for choosing ABC Hotel!\n");
                                printf("We hope to serve you again.\n");
                                printf("========================================================\n");
                                printf("\033[0m");  

                                room[i][j][1] = 0;

                                system("pause");
                                system("cls");
                            }
                        }
                    }

                    if(!found){
                        printf("\nInvalid Room No or CNIC! Checkout Failed.\n");
                        system("pause");
                        system("cls");
                    }
                    break;

                case 5:
                    break;

                default:
                    printf("\nInvalid choice! Try again.\n");
                    choice = 0; // repeat
                    break;
            }

        }while(choice != 5);
    }

    return 0;
}



