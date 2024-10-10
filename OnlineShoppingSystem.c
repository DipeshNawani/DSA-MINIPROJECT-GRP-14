#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_USERS 100
#define MAX_PRODUCTS 100
#define MAX_CART_ITEMS 100
#define MAX_ORDERS 100
#define MAX_NAME_LENGTH 100

// User Structure
typedef struct {
    char username[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];
} User;

// Product Structure
typedef struct {
    char name[MAX_NAME_LENGTH];
    float price;
    int quantity;
} Product;

// Cart Item Structure
typedef struct {
    char name[MAX_NAME_LENGTH];
    float price;
    int quantity;
} CartItem;

// Order Management
typedef struct {
    char productName[MAX_NAME_LENGTH];
    float productPrice;
    int productQuantity;
} OrderItem;

// Wish List Structure
typedef struct {
    char name[MAX_NAME_LENGTH];
    float price;
} WishListItem;

// Payment Method Structure
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
} PaymentMethod;

// Functions Prototypes
void registerUser();
int loginUser();
void addProducts();
void displayProducts();
void addToCart(char name[], float price, int quantity);
void viewCart();
void removeProductFromCart();
void updateProductQuantityInCart();
void placeOrder();
void viewOrders();
void searchProduct();
void updateInventory(int productId, int quantity);
float applyDiscount(float price, float discountPercentage);
void recommendProducts();
void generateReceipt();
void addToWishList(char name[], float price);
void viewWishList();
void removeFromWishList();
void toLowerCase(char *str);
void clearInputBuffer();
void initializePaymentMethods();
void displayPaymentMethods();
int selectPaymentMethod();
void processPayment(float total, int paymentMethodId);

// Global Variables
User users[MAX_USERS];
int userCount = 0;
Product products[MAX_PRODUCTS];
int productCount = 0;
CartItem cart[MAX_CART_ITEMS];
int cartCount = 0;
OrderItem orders[MAX_ORDERS];
int orderCount = 0;
WishListItem wishList[MAX_PRODUCTS];
int wishListCount = 0;
PaymentMethod paymentMethods[5];
int paymentMethodCount = 0;

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached.\n");
        return;
    }

    printf("Enter username: ");
    scanf("%s", users[userCount].username);
    printf("Enter password: ");
    scanf("%s", users[userCount].password);
    userCount++;
    printf("User registered successfully.\n");
    clearInputBuffer();
}

int loginUser() {
    char username[MAX_NAME_LENGTH], password[MAX_NAME_LENGTH];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful.\n");
            return 1;
        }
    }
    printf("Invalid username or password.\n");
    return 0;
}

void addProducts() {
    strcpy(products[0].name, "Apple iPhone 13");
    products[0].price = 999.99;
    products[0].quantity = 10;

    strcpy(products[1].name, "Samsung Galaxy S22");
    products[1].price = 899.99;
    products[1].quantity = 15;

    strcpy(products[2].name, "OnePlus 9 Pro");
    products[2].price = 799.99;
    products[2].quantity = 20;

    strcpy(products[3].name, "Google Pixel 6");
    products[3].price = 699.99;
    products[3].quantity = 25;

    strcpy(products[4].name, "Apple MacBook Air");
    products[4].price = 1299.99;
    products[4].quantity = 10;

    strcpy(products[5].name, "Dell XPS 13");
    products[5].price = 1099.99;
    products[5].quantity = 15;

    strcpy(products[6].name, "HP Envy x360");
    products[6].price = 999.99;
    products[6].quantity = 20;

    strcpy(products[7].name, "Canon EOS Rebel T8i");
    products[7].price = 749.99;
    products[7].quantity = 25;

    strcpy(products[8].name, "Nikon D5600");
    products[8].price = 699.99;
    products[8].quantity = 30;

    productCount = 9;
}

void displayProducts() {
    printf("Available Products:\n");
    for (int i = 0; i < productCount; i++) {
        printf("%d. %s - $%.2f - Quantity: %d\n", i + 1, products[i].name, products[i].price, products[i].quantity);
    }
}

void addToCart(char name[], float price, int quantity) {
    if (cartCount >= MAX_CART_ITEMS) {
        printf("Cart limit reached.\n");
        return;
    }

    strcpy(cart[cartCount].name, name);
    cart[cartCount].price = price;
    cart[cartCount].quantity = quantity;
    cartCount++;
    printf("Product added to cart.\n");
}

void viewCart() {
    if (cartCount == 0) {
        printf("Your cart is empty.\n");
        return;
    }
    
    printf("Your Cart:\n");
    for (int i = 0; i < cartCount; i++) {
        printf("%d. %s, Price: $%.2f, Quantity: %d\n", i + 1, cart[i].name, cart[i].price, cart[i].quantity);
    }
}

void removeProductFromCart() {
    if (cartCount == 0) {
        printf("Your cart is empty. Nothing to remove.\n");
        return;
    }

    int choice;
    printf("Enter the product number to remove from cart: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }
    choice--;
    if (choice >= 0 && choice < cartCount) {
        for (int i = choice; i < cartCount - 1; i++) {
            strcpy(cart[i].name, cart[i + 1].name);
            cart[i].price = cart[i + 1].price;
            cart[i].quantity = cart[i + 1].quantity;
        }
        cartCount--;
        printf("Product removed from cart.\n");
    } else {
        printf("Invalid choice.\n");
    }
    clearInputBuffer();
}

void updateProductQuantityInCart() {
    if (cartCount == 0) {
        printf("Your cart is empty. Nothing to update.\n");
        return;
    }

    int choice;
    printf("Enter the product number to update quantity: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }
    choice--;
    if (choice >= 0 && choice < cartCount) {
        int quantity;
        printf("Enter the new quantity: ");
        if (scanf("%d", &quantity) != 1 || quantity < 0) {
            printf("Invalid input. Quantity must be a non-negative number.\n");
            clearInputBuffer();
            return;
        }
        cart[choice].quantity = quantity;
        printf("Product quantity updated in cart.\n");
    } else {
        printf("Invalid choice.\n");
    }
    clearInputBuffer();
}

void placeOrder() {
    if (cartCount == 0) {
        printf("Your cart is empty. Nothing to order.\n");
        return;
    }

    if (orderCount >= MAX_ORDERS) {
        printf("Order limit reached.\n");
        return;
    }

    float total = 0;
    for (int i = 0; i < cartCount; i++) {
        total += cart[i].price * cart[i].quantity;
    }

    printf("Order Summary:\n");
    generateReceipt();

    int paymentMethodId = selectPaymentMethod();
    processPayment(total, paymentMethodId);

    for (int i = 0; i < cartCount; i++) {
        strcpy(orders[orderCount].productName, cart[i].name);
        orders[orderCount].productPrice = cart[i].price;
        orders[orderCount].productQuantity = cart[i].quantity;
        orderCount++;
    }
    cartCount = 0; // Clear the cart after placing the order
    printf("Order placed successfully.\n");
}

void viewOrders() {
    if (orderCount == 0) {
        printf("No orders placed yet.\n");
        return;
    }

    printf("Your Orders:\n");
    for (int i = 0; i < orderCount; i++) {
        printf("%d. %s, Price: $%.2f, Quantity: %d\n", i + 1, orders[i].productName, orders[i].productPrice, orders[i].productQuantity);
    }
}

void searchProduct() {
    char name[MAX_NAME_LENGTH];
    printf("Enter the product name to search: ");
    clearInputBuffer();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline
    toLowerCase(name);

    int found = 0;
    for (int i = 0; i < productCount; i++) {
        char lowercaseProductName[MAX_NAME_LENGTH];
        strcpy(lowercaseProductName, products[i].name);
        toLowerCase(lowercaseProductName);

        if (strstr(lowercaseProductName, name) != NULL) {
            printf("Product found: %s, Price: %.2f, Quantity: %d\n", products[i].name, products[i].price, products[i].quantity);
            found = 1;
        }
    }

    if (!found) {
        printf("No matching products found.\n");
    }
}

void updateInventory(int productId, int quantity) {
    if (productId >= 0 && productId < productCount) {
        products[productId].quantity += quantity;
        printf("Inventory updated. New quantity for %s: %d\n", products[productId].name, products[productId].quantity);
    } else {
        printf("Invalid product ID.\n");
    }
}

float applyDiscount(float price, float discountPercentage) {
    return price * (1 - discountPercentage / 100);
}

void recommendProducts() {
    printf("You might also like:\n");
    for (int i = 0; i < 3 && i < productCount; i++) {
        int randomIndex = rand() % productCount;
        printf("- %s (%.2f)\n", products[randomIndex].name, products[randomIndex].price);
    }
}

void generateReceipt() {
    float total = 0;
    printf("\n====== Receipt ======\n");
    for (int i = 0; i < cartCount; i++) {
        printf("%s x%d: $%.2f\n", cart[i].name, cart[i].quantity, cart[i].price * cart[i].quantity);
        total += cart[i].price * cart[i].quantity;
    }
    printf("--------------------\n");
    printf("Total: $%.2f\n", total);
    printf("====================\n");
}

void addToWishList(char name[], float price) {
    if (wishListCount >= MAX_PRODUCTS) {
        printf("Wish list limit reached.\n");
        return;
    }

    strcpy(wishList[wishListCount].name, name);
    wishList[wishListCount].price = price;
    wishListCount++;
    printf("Product added to wish list.\n");
}

void viewWishList() {
    if (wishListCount == 0) {
        printf("Your wish list is empty.\n");
        return;
    }

    printf("Your Wish List:\n");
    for (int i = 0; i < wishListCount; i++) {
        printf("%d. %s - $%.2f\n", i + 1, wishList[i].name, wishList[i].price);
    }
}

void removeFromWishList() {
    if (wishListCount == 0) {
        printf("Your wish list is empty. Nothing to remove.\n");
        return;
    }

    int choice;
    printf("Enter the product number to remove from the wish list: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }
    choice--;
    if (choice >= 0 && choice < wishListCount) {
        for (int i = choice; i < wishListCount - 1; i++) {
            strcpy(wishList[i].name, wishList[i + 1].name);
            wishList[i].price = wishList[i + 1].price;
        }
        wishListCount--;
        printf("Product removed from wish list.\n");
    } else {
        printf("Invalid choice.\n");
    }
    clearInputBuffer();
}

void initializePaymentMethods() {
    strcpy(paymentMethods[0].name, "Cash");
    paymentMethods[0].id = 1;

    strcpy(paymentMethods[1].name, "Credit/Debit Card");
    paymentMethods[1].id = 2;

    strcpy(paymentMethods[2].name, "UPI");
    paymentMethods[2].id = 3;

    strcpy(paymentMethods[3].name, "Net Banking");
    paymentMethods[3].id = 4;

    strcpy(paymentMethods[4].name, "Digital Wallet");
    paymentMethods[4].id = 5;

    paymentMethodCount = 5;
}

void displayPaymentMethods() {
    printf("Available Payment Methods:\n");
    for (int i = 0; i < paymentMethodCount; i++) {
        printf("%d. %s\n", paymentMethods[i].id, paymentMethods[i].name);
    }
}

int selectPaymentMethod() {
    int choice;
    do {
        displayPaymentMethods();
        printf("Select a payment method (1-%d): ", paymentMethodCount);
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > paymentMethodCount) {
            printf("Invalid input. Please try again.\n");
            clearInputBuffer();
        } else {
            return choice;
        }
    } while (1);
}
void processPayment(float total, int paymentMethodId) {
    printf("Processing payment of $%.2f using %s...\n", total, paymentMethods[paymentMethodId - 1].name);
    // Simulate payment processing
    printf("Payment successful!\n");
}

int main() {
    int choice, login = 0;
    addProducts();
    initializePaymentMethods();

    while (1) {
        printf("\n===== E-Commerce System =====\n");
        printf("1. Register\n2. Login\n3. View Products\n4. Add to Cart\n");
        printf("5. View Cart\n6. Remove Product from Cart\n7. Update Product Quantity in Cart\n");
        printf("8. Place Order\n9. View Orders\n10. Search Product\n");
        printf("11. Update Inventory\n12. Apply Discount\n13. Get Recommendations\n");
        printf("14. Add to Wish List\n15. View Wish List\n16. Remove from Wish List\n17. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                login = loginUser();
                break;
            case 3:
                displayProducts();
                break;
            case 4:
                if (login) {
                    int productId;
                    printf("Enter the product ID: ");
                    if (scanf("%d", &productId) == 1) {
                        productId--;
                        if (productId >= 0 && productId < productCount) {
                            int quantity;
                            printf("Enter quantity: ");
                            if (scanf("%d", &quantity) == 1 && quantity > 0) {
                                if (quantity <= products[productId].quantity) {
                                    addToCart(products[productId].name, products[productId].price, quantity);
                                    updateInventory(productId, -quantity);
                                } else {
                                    printf("Not enough stock available.\n");
                                }
                            } else {
                                printf("Invalid quantity.\n");
                            }
                        } else {
                            printf("Invalid product ID.\n");
                        }
                    } else {
                        printf("Invalid input.\n");
                    }
                } else {
                    printf("Please login first.\n");
                }
                clearInputBuffer();
                break;
            case 5:
                viewCart();
                break;
            case 6:
                if (login) removeProductFromCart();
                else printf("Please login first.\n");
                break;
            case 7:
                if (login) updateProductQuantityInCart();
                else printf("Please login first.\n");
                break;
            case 8:
                if (login) {
                    placeOrder();
                } else printf("Please login first.\n");
                break;
            case 9:
                viewOrders();
                break;
            case 10:
                searchProduct();
                break;
            case 11:
                if (login) {
                    int productId, quantity;
                    printf("Enter product ID and quantity to update: ");
                    if (scanf("%d %d", &productId, &quantity) == 2) {
                        updateInventory(productId - 1, quantity);
                    } else {
                        printf("Invalid input.\n");
                    }
                } else {
                    printf("Please login first.\n");
                }
                clearInputBuffer();
                break;
            case 12:
                if (login) {
                    int productId;
                    float discount;
                    printf("Enter product ID and discount percentage: ");
                    if (scanf("%d %f", &productId, &discount) == 2) {
                        productId--;
                        if (productId >= 0 && productId < productCount) {
                            products[productId].price = applyDiscount(products[productId].price, discount);
                            printf("Discount applied. New price for %s: %.2f\n", products[productId].name, products[productId].price);
                        } else {
                            printf("Invalid product ID.\n");
                        }
                    } else {
                        printf("Invalid input.\n");
                    }
                } else {
                    printf("Please login first.\n");
                }
                clearInputBuffer();
                break;
            case 13:
                recommendProducts();
                break;
            case 14:
                if (login) {
                    int productId;
                    printf("Enter the product ID to add to wish list: ");
                    if (scanf("%d", &productId) == 1) {
                        productId--;
                        if (productId >= 0 && productId < productCount) {
                            addToWishList(products[productId].name, products[productId].price);
                        } else {
                            printf("Invalid product ID.\n");
                        }
                    } else {
                        printf("Invalid input.\n");
                    }
                } else {
                    printf("Please login first.\n");
                }
                clearInputBuffer();
                break;
            case 15:
                if (login) viewWishList();
                else printf("Please login first.\n");
                break;
            case 16:
                if (login) removeFromWishList();
                else printf("Please login first.\n");
                break;
            case 17:
                printf("Thank you for using our E-Commerce System. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
