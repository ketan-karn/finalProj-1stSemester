//group 6
//Basically this code is of hotel menu where the user provide some information like name,
//address,mobile numeber and order some items from the menu and at last the final bill will be displayed.
#include <stdio.h>
#include <string.h>

// Define a struct to represent menu items
struct MenuItem {
    char name[50];
    int price;
};

// Define a struct to represent customer information
struct CustomerInfo {
    char name[50];
    char address[100];
    char mobileNumber[15];
};

// Function prototypes
void displayMenu(struct MenuItem menu[], int *size);
float calculateBill(struct MenuItem menu[], int *size, int choices[], int quantity[], int numOrders);
void saveOrderToFile(struct MenuItem menu[], struct CustomerInfo customer, int choices[], int quantity[], int numOrders, float totalBill);

title()
{
	printf("\033[0;33m");
	printf("*******************************************************************************************\n");
	printf(" ||   ||  00000  ========  ||????  ||        ||*     *||  ||????  ||*      ||  ||      ||\n");
	printf(" ||   ||  0   0     ||     ||      ||        || *   * ||  ||      || *     ||  ||      ||\n");
	printf(" ||   ||  0   0     ||     ||      ||        ||  * *  ||  ||      ||  *    ||  ||      ||\n");
	printf(" ||===||  0   0     ||     ||????  ||        ||   *   ||  ||????  ||   *   ||  ||      ||\n");
	printf(" ||   ||  0   0     ||     ||      ||        ||       ||  ||      ||    *  ||  ||      ||\n");
	printf(" ||   ||  0   0     ||     ||      ||        ||       ||  ||      ||     * ||  ||      ||\n");
	printf(" ||   ||  00000     ||     ||????  ||????    ||       ||  ||????  ||      *||  ||??????||\n");
	printf("\n");
	printf("*******************************************************************************************\n");
	printf("\033[0m");

}

int main() {
	title();
    // Define menu items (Authentic Nepali Food)
    struct MenuItem menu[5] = {
        {"Dal Bhat", 200},
        {"Momo", 100},
        {"Thukpa", 150},
        {"Gundruk", 80},
        {"Sel Roti", 50}
    };

    int choices[10]; // Array to store user choices
    int quantity[10]; // Array to store quantity of each choice
    int numOrders = 0; // Number of orders
	int size = 5;
    // Define customer information
    struct CustomerInfo customer;
    printf("Enter your name: ");
    fgets(customer.name, 50, stdin);
    printf("Enter your address: ");
    fgets(customer.address, 100, stdin);
    printf("Enter your mobile number: ");
    fgets(customer.mobileNumber, 15, stdin);

    // Display menu
    printf("\nWelcome to Our Hotel Menu!\n");
    printf("Location: Pokhara, Lamachaur\n\n");
    displayMenu(menu, &size);

    // Take orders from the user
    char response;
    do {
        printf("\nEnter item number to order: ");
        scanf("%d", &choices[numOrders]);
        printf("Enter quantity: ");
        scanf("%d", &quantity[numOrders]);
        numOrders++;

        printf("Would you like to order more items? (y/n): ");
        scanf(" %c", &response);
    } while (response == 'y' && numOrders < 10);

    // Calculate and display bill
    int totalBill = calculateBill(menu, &size, choices, quantity, numOrders);
   
    printf("\n\nThank you for your order!\n\n");
    printf("\033[0;32m");
    printf("---------------------------------------------------------------------------\n");
    printf("|                            Bill                                         |\n");
    printf("---------------------------------------------------------------------------\n");
    printf("| %-20s | %-10s | %-10s |\n", "Item", "Quantity", "Price");
    printf("---------------------------------------------------------------------------\n");
    for (int i = 0; i < numOrders; i++) {
        int choiceIndex = choices[i] - 1;
        printf("| %-20s | %-10d | Rs%-9.2d |\n", menu[choiceIndex].name, quantity[i], menu[choiceIndex].price * quantity[i]);
    }
    printf("\033[0;31m");
    printf("---------------------------------------------------------------------------\n");
    printf("| %-20s | %-10s | Rs%-9d |\n", "Total", "", totalBill);
    printf("---------------------------------------------------------------------------\n\n");
	printf("\033[0;32m");
    // Display customer information
    printf("Customer Information:\n");
    printf("Name: %s", customer.name);
    printf("Address: %s", customer.address);
    printf("Mobile Number: %s\n", customer.mobileNumber);
	printf("\033[0m");
    // Save order to file
    saveOrderToFile(menu, customer, choices, quantity, numOrders, totalBill);

    return 0;
}

// Function to display the menu
void displayMenu(struct MenuItem menu[], int *size) {
    printf("Menu:\n");
    for (int i = 0; i < *size; i++) {
        printf("%d. %-20s - Rs %d\n", i+1, menu[i].name, menu[i].price);

    }
}

// Function to calculate the bill
float calculateBill(struct MenuItem menu[], int *size, int choices[], int quantity[], int numOrders) {
    int totalBill = 0;
    printf("\nYour Order:\n");
    for (int i = 0; i < numOrders; i++) {
        int choiceIndex = choices[i] - 1;
        if (choiceIndex >= 0 && choiceIndex < *size) {
            printf("%s - Rs %.2d x %d\n", menu[choiceIndex].name, menu[choiceIndex].price, quantity[i]);
            totalBill += menu[choiceIndex].price * quantity[i];
        }
    }
    return totalBill;
}

// Function to save order details to a file
void saveOrderToFile(struct MenuItem menu[], struct CustomerInfo customer, int choices[], int quantity[], int numOrders, float totalBill) {
    FILE *file = fopen("order.txt", "a+w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "\nCustomer Information:\n");
    fprintf(file, "Name: %s", customer.name);
    fprintf(file, "Address: %s", customer.address);
    fprintf(file, "Mobile Number: %s\n", customer.mobileNumber);

    fprintf(file, "\nOrder Details:\n");
    for (int i = 0; i < numOrders; i++) {
        int choiceIndex = choices[i] - 1;
        fprintf(file, "%s - Rs %.2f x %d\n", menu[choiceIndex].name, menu[choiceIndex].price, quantity[i]);
    }

    fprintf(file, "\nTotal Bill: Rs %.2f\n\n", totalBill);

    fclose(file);
}
