#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h> 

HANDLE hConsole; 

// defining color macros
#define RESET_COLOR SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define SET_COLOR_BLACK SetConsoleTextAttribute(hConsole, 0)
#define SET_COLOR_BLUE SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define SET_COLOR_GREEN SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define SET_COLOR_CYAN SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define SET_COLOR_RED SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY)
#define SET_COLOR_MAGENTA SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define SET_COLOR_YELLOW SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define SET_COLOR_WHITE SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define SET_COLOR_GRAY SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY)
#define SET_COLOR_BRIGHT_WHITE SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

// defining item structure
struct product {
    int id;
    char name[50]; 
    float price;
    int quantity;
    int items_sold;
};

char fileName[100] = "inventory.txt";
struct Users {
    char username[20];
    char password[20];
};
void createFile(char *name);
int sign_in(struct Users user[], int *user_count);
//•	Handles user sign-in by verifying credentials and preparing the user's inventory file.
//•	Parameters: user[]: Array of users, user_count: Pointer to user count
//•	Return Value: 1 if sign-in successful, 0 otherwise
int sign_up(struct Users user[], int *user_count);
//•	Allows a new user to register and sign in.
//•	Parameters: user[]: Array of users, user_count: Pointer to user count
//•	Return Value: 1 if sign-up successful, 0 if user exit

//used to check if file exists
int fileExists() {
//•	Checks if a specified file exists.
//•	Parameters: filename: File name to check
//•	Return Value: 1 if file exists, 0 otherwise
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        return 0;
    } else {
        fclose(file);
        return 1;
    }
}

void createFile(char *name) {
//•	Creates a new file with the specified name.
//•	Parameters: name: File name to create
//•	Return Value: None
    FILE *fptr = fopen(name, "w");
    if (fptr == NULL) {
        perror("Error creating file");
        return;
    }
    SET_COLOR_GREEN;
    printf("File '%s' created successfully.\n", name);
    RESET_COLOR;
    fclose(fptr);
}

int sign_in(struct Users user[], int *user_count) {
	
    char username[20];
    char password[20];
    int attempts =0;
    int max_attempts = 3;
    
    while(attempts<max_attempts){
    SET_COLOR_MAGENTA;
    printf("\n============ SIGN IN ============\n");
    RESET_COLOR;

    // Loop for username input
    while (1) {
        printf("Enter Username: ");
        if (scanf("%19s", username) != 1) {
            SET_COLOR_RED;
            printf("Invalid input for username. Please try again.\n");
            RESET_COLOR;
            while (getchar() != '\n');
        } else {
            break;
        }
    }

    // Loop for password input
    while (1) {
        printf("Enter Password: ");
        SET_COLOR_BLACK;
        if (scanf("%19s", password) != 1) {
            RESET_COLOR;
            SET_COLOR_RED;
            printf("Invalid input for password. Please try again.\n");
            RESET_COLOR;
            while (getchar() != '\n');
        } else {
            RESET_COLOR;
            break;
        }
    }

    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        SET_COLOR_RED;
        printf("No users registered yet. Please sign up first.\n");
        RESET_COLOR;
        return 0;
    }
   
    int username_found = 0;
    int temp_user_count = 0;
    while (fscanf(file, "%s %s", user[temp_user_count].username, user[temp_user_count].password) != EOF) {
        if (strcmp(user[temp_user_count].username, username) == 0) {
            username_found = 1;    
            if (strcmp(user[temp_user_count].username, username) == 0 && strcmp(user[temp_user_count].password, password) == 0) {
                fclose(file);

                snprintf(fileName, sizeof(fileName), "%s_inventory.txt", username);
                system("cls");

                SET_COLOR_GREEN;
                printf("Login successful!\n");
                RESET_COLOR;
                return 1;
        }break;
        }
        temp_user_count++;
    }
    fclose(file);

    attempts++;
    if (username_found) {
            SET_COLOR_RED;
            printf("Incorrect Password!\n");
            RESET_COLOR;
        } else {
            SET_COLOR_RED;
            printf("No users registered yet. Please sign up first.\n");
            RESET_COLOR;
            return 0;
        }

    if (attempts < max_attempts) {
            printf("Would you like to try again or exit to the main menu? (1: Try Again, 2: Exit): ");
            int choice;
            if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
                SET_COLOR_RED;
                printf("Invalid choice. Please enter 1 or 2.\n");
                RESET_COLOR;
                while (getchar() != '\n');
            } else if (choice == 2) {
                return 0; 
            }
        }
    }

    SET_COLOR_RED;
    printf("Maximum attempts reached. Returning to main menu.\n");
    RESET_COLOR;
    return 0;
}

int sign_up(struct Users user[], int *user_count) {
    char new_username[20];
    char password[20];

    SET_COLOR_MAGENTA;
    printf("\n============ REGISTER ============\n");
    RESET_COLOR;
    int username_exist;
    // Loop for username input
    do{
        username_exist = 0;
        printf("Enter a new username (or type 'q' to cancel): ");
        if (scanf("%19s", new_username) != 1) {
            SET_COLOR_RED;
            printf("Invalid input for username. Please try again.\n");
            RESET_COLOR;
            while (getchar() != '\n');
            continue;
        }

        if (strcmp(new_username, "q") == 0||strcmp(new_username, "Q") == 0) {
            printf("Exiting registration. Returning to main menu.\n");
            while (getchar() != '\n');
            return 0;
        }
    
        FILE *file = fopen("users.txt", "r");
        if (file != NULL) {
            while (fscanf(file, "%s %s", user[*user_count].username, user[*user_count].password) != EOF) {
                if (strcmp(user[*user_count].username, new_username) == 0) {
                    SET_COLOR_RED;
                    printf("Username already exists. Please choose a different username.\n");
                    RESET_COLOR;
                    username_exist = 1;
                    break;
            }
        }
        fclose(file);
      }
    }while(username_exist);
    // Loop for password input
    while (1) {
        printf("Enter new password: ");
        SET_COLOR_BLACK;
        if (scanf("%19s", password) != 1) {
            RESET_COLOR;
            SET_COLOR_RED;
            printf("Invalid input for password. Please try again.\n");
            RESET_COLOR;
            while (getchar() != '\n');
        } else {
            RESET_COLOR;
            break;
        }
    }

    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        SET_COLOR_RED;
        printf("Error: Unable to open the file.\n");
        RESET_COLOR;
        return 0;
    }
    fprintf(file, "%s %s\n", strcpy(user[*user_count].username, new_username), strcpy(user[*user_count].password, password));
    fclose(file);
    (*user_count)++;

    SET_COLOR_GREEN;
    printf("Registered successfully!\n");
    RESET_COLOR;
    return 1;
}

void write(struct product prod[], int *count) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        createFile(fileName);
    } else {
        *count = 0; 
        while (fscanf(file, "%d;%[^;];%f;%d;%d\n", &prod[*count].id, prod[*count].name,
                      &prod[*count].price, &prod[*count].quantity,
                      &prod[*count].items_sold) != EOF) {
            (*count)++;
        }
        fclose(file);
    }

    int new_id;
    SET_COLOR_CYAN;
    printf("Enter the item details:\n");
    RESET_COLOR;

    // Loop for item ID input
    while (1) {
        printf("Enter the item ID: ");
        if (scanf("%d", &new_id) != 1) {
            SET_COLOR_RED;
            printf("Invalid input for item ID. Please enter an integer.\n");
            RESET_COLOR;
            while (getchar() != '\n');
        } else {
            break;
        }
    }

    for (int i = 0; i < *count; i++) {
        if (prod[i].id == new_id) {
            SET_COLOR_RED;
            printf("Product ID %d already exists.\n", new_id);
            RESET_COLOR;
            return;
        }
    }

    prod[*count].id = new_id;
    printf("Enter the item name: ");
    getchar(); 
    fgets(prod[*count].name, sizeof(prod[*count].name), stdin);
    size_t len = strlen(prod[*count].name);
    if (len > 0 && prod[*count].name[len - 1] == '\n') {
        prod[*count].name[len - 1] = '\0';
    }

    // Loop for price input
    while (1) {
        printf("Enter the price: ");
        if (scanf("%f", &prod[*count].price) != 1 ) {
            SET_COLOR_RED;
            printf("Invalid input for price. Please enter a number.\n");
            RESET_COLOR;
            while (getchar() != '\n');
        } else {
            break;
        }
    }

    // Loop for quantity input
    while (1) {
        printf("Enter the quantity: ");
        if (scanf("%d", &prod[*count].quantity) != 1 || prod[*count].quantity < 0) {
            SET_COLOR_RED;
            printf("Invalid input for quantity. Please enter an integer.\n");
            RESET_COLOR;
            while (getchar() != '\n');
        } else {
            break;
        }
    }

    prod[*count].items_sold = 0;
    (*count)++;

    struct product temp;
    for (int i = 0; i < *count - 1; i++) {
        for (int j = 0; j < *count - i - 1; j++) {
            if (prod[j].id > prod[j + 1].id) {
                temp = prod[j];
                prod[j] = prod[j + 1];
                prod[j + 1] = temp;
            }
        }
    }

    file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Unable to open file for writing!");
        return;
    }
    for (int i = 0; i < *count; i++) {
        fprintf(file, "%d;%s;%.2f;%d;%d\n", prod[i].id, prod[i].name,
                prod[i].price, prod[i].quantity, prod[i].items_sold);
    }
    fclose(file);

    SET_COLOR_GREEN;
    printf("Product added successfully.\n");
    RESET_COLOR;
}

void read(struct product prod[],int *count) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Unable to open file!");
        return;
    }

    SET_COLOR_YELLOW;
    printf("ID\tProduct Name            \tPrice\tQuantity\tItems Sold\n");
    printf("--------------------------------------------------------------------------------------\n");
    RESET_COLOR;

    *count = 0; 
    while (fscanf(file, "%d;%[^;];%f;%d;%d\n", &prod[*count].id, prod[*count].name,
                  &prod[*count].price, &prod[*count].quantity,
                  &prod[*count].items_sold) != EOF) {
        SET_COLOR_WHITE;
        printf("%d\t%-19s\t\t%.2f\t%d\t\t%d\n", prod[*count].id, prod[*count].name, prod[*count].price, prod[*count].quantity, prod[*count].items_sold);
        (*count)++;
        RESET_COLOR;
    }
    fclose(file);
}

void del(struct product prod[], int *count) {
    int id;
    int found = 0;

    // Loop for product ID input
    while (1) {
        printf("Enter the ID of the product to delete: ");
        if (scanf("%d", &id) != 1) {
            SET_COLOR_RED;
            printf("Invalid input for product ID. Please enter an integer.\n");
            RESET_COLOR;
            while (getchar() != '\n');
        } else {
            break;
        }
    }

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Unable to open file!");
        return;
    }
    *count = 0;
    struct product temp_prod;
    while (fscanf(file, "%d;%[^;];%f;%d;%d\n", &temp_prod.id, temp_prod.name, &temp_prod.price, &temp_prod.quantity, &temp_prod.items_sold) != EOF) {
        if (temp_prod.id == id) {
            found = 1;
            continue; 
        }
        prod[*count] = temp_prod;
        (*count)++;
    }
    fclose(file);

    if (!found) {
        SET_COLOR_RED;
        printf("Product with ID %d not found.\n", id);
        RESET_COLOR;
        return;
    }

    file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Unable to open file!");
        return;
    }

    for (int i = 0; i < *count; i++) {
        fprintf(file, "%d;%s;%.2f;%d;%d\n", prod[i].id, prod[i].name, prod[i].price, prod[i].quantity, prod[i].items_sold);
    }
    fclose(file);
    SET_COLOR_GREEN;
    printf("Product with ID %d has been deleted.\n", id);
    RESET_COLOR;
}

void update(struct product prods[], int *count) {
    int item_id;
    char new_name[50];
    float new_price;
    int new_quantity;
    int found = 0;

    // Loop for item ID input
    while (1) {
        printf("Enter the item ID to update: ");
        if (scanf("%d", &item_id) != 1) {
            SET_COLOR_RED;
            printf("Invalid input for item ID. Please enter an integer.\n");
            RESET_COLOR;
            while (getchar() != '\n');
        } else {
            break;
        }
    }

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Unable to open file!");
        return;
    }

    *count = 0;
    while (fscanf(file, "%d;%[^;];%f;%d;%d\n", &prods[*count].id, prods[*count].name, &prods[*count].price, &prods[*count].quantity, &prods[*count].items_sold) != EOF) {
        if (prods[*count].id == item_id) {
            found = 1;
            SET_COLOR_YELLOW;
            printf("\nProduct found:\n");
            RESET_COLOR;
            printf("ID: %d\nName: %s\nPrice: %.2f\nQuantity: %d\nItems Sold: %d\n",
                   prods[*count].id, prods[*count].name, prods[*count].price, prods[*count].quantity, prods[*count].items_sold);

            int choice;
            // Loop for update choice input
            while (1) {
                printf("What do you want to update?\n");
                SET_COLOR_CYAN;
                printf("1) Name\n2) Price\n3) Quantity\nEnter your choice: ");
                RESET_COLOR;
                if (scanf("%d", &choice) != 1) {
                    SET_COLOR_RED;
                    printf("Invalid input for choice. Please enter an integer.\n");
                    RESET_COLOR;
                    while (getchar() != '\n');
                } else if (choice < 1 || choice > 3) {
                    SET_COLOR_RED;
                    printf("Invalid choice. Please select a valid option.\n");
                    RESET_COLOR;
                } else {
                    break;
                }
            }

            if (choice == 1) {
                printf("Enter new product name: ");
                getchar(); 
                fgets(new_name, sizeof(new_name), stdin);
                size_t len = strlen(new_name);
                if (len > 0 && new_name[len - 1] == '\n') {
                    new_name[len - 1] = '\0';
                }
                strcpy(prods[*count].name, new_name);
            } else if (choice == 2) {
                // Loop for new price input
                while (1) {
                    printf("Enter new price: ");
                    if (scanf("%f", &new_price) != 1) {
                        SET_COLOR_RED;
                        printf("Invalid input for new price. Please enter a number.\n");
                        RESET_COLOR;
                        while (getchar() != '\n');
                    } else {
                        prods[*count].price = new_price;
                        break;
                    }
                }
            } else if (choice == 3) {
                // Loop for new quantity input
                while (1) {
                    printf("Enter new quantity: ");
                    if (scanf("%d", &new_quantity) != 1) {
                        SET_COLOR_RED;
                        printf("Invalid input for new quantity. Please enter an integer.\n");
                        RESET_COLOR;
                        while (getchar() != '\n');
                    } else {
                        prods[*count].quantity = new_quantity;
                        break;
                    }
                }
            }
            SET_COLOR_GREEN;
            printf("Product updated successfully!\n");
            RESET_COLOR;
        }
        (*count)++;
    }
    fclose(file);

    if (!found) {
        SET_COLOR_RED;
        printf("Item with ID %d not found.\n", item_id);
        RESET_COLOR;
        return;
    }

    file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Unable to open file!");
        return;
    }

    for (int i = 0; i < *count; i++) {
        fprintf(file, "%d;%s;%.2f;%d;%d\n", prods[i].id, prods[i].name, prods[i].price, prods[i].quantity, prods[i].items_sold);
    }
    fclose(file);
}

void search(struct product prods[], int *count) {
    int item_id;
    int found = 0;

    // Loop for product ID input
    while (1) {
        printf("Enter the product ID to search: ");
        if (scanf("%d", &item_id) != 1) {
            SET_COLOR_RED;
            printf("Invalid input for product ID. Please enter an integer.\n");
            RESET_COLOR;
            while (getchar() != '\n');
        } else {
            break;
        }
    }

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Unable to open file!");
        return;
    }
    *count = 0;
    while (fscanf(file, "%d;%[^;];%f;%d;%d\n", &prods[*count].id, prods[*count].name, &prods[*count].price, &prods[*count].quantity, &prods[*count].items_sold) != EOF) {
        if (prods[*count].id == item_id) {
            found = 1;
            SET_COLOR_YELLOW;
            printf("\nProduct found:\n");
            RESET_COLOR;
            printf("ID: %d\nName: %s\nPrice: %.2f\nQuantity: %d\nItems Sold: %d\n",
                   prods[*count].id, prods[*count].name, prods[*count].price, prods[*count].quantity, prods[*count].items_sold);
            break;
        }
        (*count)++;
    }
    fclose(file);

    if (!found) {
        SET_COLOR_RED;
        printf("Item not found.\n");
        RESET_COLOR;
    }
}

void sorting(struct product prod[], int *count) {
    int choice;

    while (1) {
        printf("Choose sorting criterion:\n");
        SET_COLOR_CYAN;
        printf("1) Price\n2) Quantity\n3) Product Name\nEnter your choice: ");
        RESET_COLOR;
        if (scanf("%d", &choice) != 1) {
            SET_COLOR_RED;
            printf("Invalid input for choice. Please enter an integer.\n");
            RESET_COLOR;
            while (getchar() != '\n');
        } else if (choice < 1 || choice > 3) {
            SET_COLOR_RED;
            printf("Invalid choice. Please select a valid option.\n");
            RESET_COLOR;
        } else {
            break;
        }
    }

    struct product temp;
    int condition;

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Unable to open file for sorting!");
        return;
    }

    *count = 0;
    while (fscanf(file, "%d;%[^;];%f;%d;%d\n", &prod[*count].id, prod[*count].name, &prod[*count].price,
                  &prod[*count].quantity, &prod[*count].items_sold) != EOF) {
        (*count)++;
    }
    fclose(file);

    for (int i = 0; i < *count - 1; i++) {
        for (int j = 0; j < *count - i - 1; j++) {
            if (choice == 1) {
                condition = (prod[j].price > prod[j + 1].price);
            } else if (choice == 2) {
                condition = (prod[j].quantity > prod[j + 1].quantity);
            } else if (choice == 3) {
                condition = (strcmp(prod[j].name, prod[j + 1].name) > 0);
            }

            if (condition) {
                temp = prod[j];
                prod[j] = prod[j + 1];
                prod[j + 1] = temp;
            }
        }
    }

    SET_COLOR_GREEN;
    printf("Sorting completed.\n");
    RESET_COLOR;

    file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Unable to open file for writing sorted data!");
        return;
    }

    for (int i = 0; i < *count; i++) {
        fprintf(file, "%d;%s;%.2f;%d;%d\n", prod[i].id, prod[i].name, prod[i].price, prod[i].quantity,
                prod[i].items_sold);
    }
    fclose(file);
}

void soldproducts(struct product prod[], int *count) {
    int product_id, sold_quantity;
    int found = 0;

    // Loop for product ID input
    while (1) {
        printf("Enter the product ID which was sold: ");
        if (scanf("%d", &product_id) != 1) {
            SET_COLOR_RED;
            printf("Invalid input for product ID. Please enter an integer.\n");
            RESET_COLOR;
            while (getchar() != '\n');
        } else {
            break;
        }
    }

    // Loop for quantity sold input
    while (1) {
        printf("Enter the quantity sold: ");
        if (scanf("%d", &sold_quantity) != 1 || sold_quantity < 0) {
            SET_COLOR_RED;
            printf("Invalid input for quantity sold. Please enter an integer.\n");
            RESET_COLOR;
            while (getchar() != '\n');
        } else {
            break;
        }
    }

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Unable to open file!");
        return;
    }

    *count = 0;
    while (fscanf(file, "%d;%[^;];%f;%d;%d\n", &prod[*count].id, prod[*count].name, &prod[*count].price,
                  &prod[*count].quantity, &prod[*count].items_sold) != EOF) {
        if (prod[*count].id == product_id) {
            found = 1;
            if (prod[*count].quantity >= sold_quantity) {
                prod[*count].quantity -= sold_quantity;
                prod[*count].items_sold += sold_quantity;
                SET_COLOR_GREEN;
                printf("Sale recorded: %d items sold.\n", sold_quantity);
                RESET_COLOR;
            } else {
                SET_COLOR_RED;
                printf("Not enough stock available. Only %d items in stock.\n", prod[*count].quantity);
                RESET_COLOR;
            }
        }
        (*count)++;
    }
    fclose(file);

    if (!found) {
        SET_COLOR_RED;
        printf("Product with ID %d not found.\n", product_id);
        RESET_COLOR;
        return;
    }

    file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Unable to open file!");
        return;
    }

    for (int i = 0; i < *count; i++) {
        fprintf(file, "%d;%s;%.2f;%d;%d\n", prod[i].id, prod[i].name, prod[i].price, prod[i].quantity,
                prod[i].items_sold);
    }
    fclose(file);

    SET_COLOR_GREEN;
    printf("Product data updated successfully!\n");
    RESET_COLOR;
}

void restock(struct product prods[], int *count) {

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Unable to open file!");
        return;
    }

    int found = 0;
    *count = 0;
    SET_COLOR_YELLOW;
    printf("PRODUCTS TO BE RESTOCKED:\n\n");
    printf("ID\tProduct Name            \tPrice\tQuantity\tItems Sold\n");
    printf("--------------------------------------------------------------------------------------\n");
    RESET_COLOR;

    while (fscanf(file, "%d;%[^;];%f;%d;%d\n", &prods[*count].id, prods[*count].name, &prods[*count].price,
                  &prods[*count].quantity, &prods[*count].items_sold) != EOF) {
        if (prods[*count].quantity < 10) {
            found = 1;
            SET_COLOR_WHITE;
            printf("%d\t%-19s\t\t%.2f\t%d\t\t%d\n", prods[*count].id, prods[*count].name, prods[*count].price,
                   prods[*count].quantity, prods[*count].items_sold);
            RESET_COLOR;
        }
        (*count)++;
    }
    fclose(file);

    if (!found) {
        SET_COLOR_GREEN;
        printf("No products in inventory that need restocking.\n");
        RESET_COLOR;
    }
}

int main() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    struct Users user[100];
    int user_count = 0;
    struct product prods[100];
    int count = 0;
    int choice;
    int account;
    

    SET_COLOR_YELLOW;
     char asciiArt[] =
        "WW      WW  EEEEE  LL      CCC   OOO   MM   MM  EEEEE       TTTTTT   OOO  \n"
        "WW      WW  EE     LL     CC    OO OO  MMM MMM  EE            TT    OO OO \n"
        "WW   W  WW  EEEE   LL     CC    OO  OO MM M MM  EEEE          TT   OO   OO\n"
        " WW WWW WW  EE     LL     CC    OO OO  MM   MM  EE            TT    OO OO \n"
        "  WW   WW   EEEEE  LLLLL   CCC   OOO   MM   MM  EEEEE         TT     OOO  \n"
        "\n"
        " III NN  NN VV   VV EEEEE NN  NN TTTTT  OOO   RRRR  YY   YY\n"
        " III NNN NN VV   VV EE    NNN NN   T   OO OO  RR RR  YY YY \n"
        " III NN NNN  VV VV  EEEE  NN NNN   T   OO  OO RRRR    YYY \n"
        " III NN  NN   VVV   EE    NN  NN   T   OO OO  RR RR   YYY \n"
        " III NN  NN    V    EEEEE NN  NN   T    OOO   RR  RR  YYY \n"
        "\n"
        " MM   MM    AAA    NN  NN   AAA   GGGG   EEEEE MM   MM  EEEEE NN  NN  TTTTT\n"
        " MMM MMM   AA AA   NNN NN  AA AA  GG     EE    MMM MMM  EE    NNN NN    T  \n"
        " MM M MM  AAAAAAA  NN NNN AAAAAAA GG GGG EEEE  MM M MM  EEEE  NN NNN    T  \n"
        " MM   MM  AA   AA  NN  NN AA   AA GG  GG EE    MM   MM  EE    NN  NN    T  \n"
        " MM   MM  AA   AA  NN  NN AA   AA  GGGG  EEEEE MM   MM  EEEEE NN  NN    T  \n"
        "\n"
        " SSSS  YY   YY  SSSS  TTTTT EEEEE MM   MM\n"
        "SS      YY YY  SS       T   EE    MMM MMM\n"
        " SSSS    YYY    SSSS    T   EEEE  MM M MM\n"
        "    SS   YYY       SS   T   EE    MM   MM\n"
        " SSSS    YYY    SSSS    T   EEEEE MM   MM\n";

    printf("%s", asciiArt);
    printf("\n\n");
    RESET_COLOR;
    int login_successful = 0;
    // Loop for account choice input
     do {
        SET_COLOR_CYAN;
        printf("1) SIGN IN \n2) SIGN UP\nChoice: ");
        RESET_COLOR;
 
        if (scanf("%d", &account) != 1) {
        SET_COLOR_RED;
        printf("Invalid input. Please enter 1 or 2.\n");
        RESET_COLOR;
        while (getchar() != '\n'); // Clear the input buffer
        continue; // Restart the loop
    }   
        if (account == 2) {
           login_successful = sign_up(user, &user_count) ;
           if(login_successful == 1){
               account = 1;
           }else{
            continue;
           }
        }if (account == 1) {
            login_successful = sign_in(user, &user_count);
            
        }
        else {
            SET_COLOR_RED;
            printf("%d",account);
            printf("Invalid choice. Please select 1 or 2.\n");
            RESET_COLOR;
            
        }
    } while (!login_successful);
    

    

    do {
        if (fileExists() == 1)
        {
            // Loop for main menu choice input
            while (1) {
                SET_COLOR_MAGENTA;
                printf("\nCHOOSE YOUR OPTION (1-9):\n");
                RESET_COLOR;
                SET_COLOR_CYAN;
                printf("1) Add product\n2) Display products\n3) Delete product\n4) Update product\n");
                printf("5) Search product\n6) Product sold\n7) Sorting\n8) Restock\n9) Exit\n");
                printf("\nYour Choice: ");
                RESET_COLOR;
                if (scanf("%d", &choice) != 1) {
                    SET_COLOR_RED;
                    printf("Invalid input for choice. Please enter a number between 1 and 9.\n");
                    RESET_COLOR;
                    while (getchar() != '\n');
                } else if (choice < 1 || choice > 9) {
                    SET_COLOR_RED;
                    printf("Invalid choice. Please select a number between 1 and 9.\n");
                    RESET_COLOR;
                } else {
                    break;
                }
            }
            getchar(); 
            system("cls");

            switch (choice) {
                case 1:
                    write(prods, &count);
                    break;
                case 2:
                    read(prods,&count);
                    break;
                case 3:
                    del(prods, &count);
                    break;
                case 4:
                    update(prods, &count);
                    break;
                case 5:
                    search(prods, &count);
                    break;
                case 6:
                    soldproducts(prods, &count);
                    break;
                case 7:
                    sorting(prods, &count);
                    break;
                case 8:
                    restock(prods, &count);
                    break;
                case 9:
                    SET_COLOR_GREEN;
                    printf("Exiting the program.\n");
                    RESET_COLOR;
                    break;
                default:
                    SET_COLOR_RED;
                    printf("Invalid choice. Please select again.\n");
                    RESET_COLOR;
                    break;
            }
        }
        else
        {
            while (1) {
                printf("\nCHOOSE YOUR OPTION (1-2): \n1) Add product\n2) Exit\n");
                printf("\nYour Choice: ");
                if (scanf("%d", &choice) != 1) {
                    SET_COLOR_RED;
                    printf("Invalid input for choice. Please enter 1 or 2.\n");
                    RESET_COLOR;
                    while (getchar() != '\n');
                } else if (choice < 1 || choice > 2) {
                    SET_COLOR_RED;
                    printf("Invalid choice. Please select 1 or 2.\n");
                    RESET_COLOR;
                } else {
                    break;
                }
            }

            switch (choice)
            {
            case 1:
                printf("FileName: %s\n\n", fileName);
                write(prods, &count);
                system("cls");
                break;
            case 2:
                printf("FileName: %s\n\n", fileName);
                printf("Exiting the program.\n");
                break;
            default:
                printf("FileName: %s\n\n", fileName);
                printf("Invalid choice. Please select again.\n");
                break;
            }
        }
    } while (choice != 9);

    return 0;
}