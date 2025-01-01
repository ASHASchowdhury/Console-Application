package labib;

import java.util.*;

class LoginManager {
    private static final String USERNAME = "Labib1";
    private static final String PASSWORD = "welcome2025";

    public static boolean authenticate() {
        Scanner scanner = new Scanner(System.in);
        try {
            System.out.print("Enter Username: ");
            String username = scanner.nextLine();
            System.out.print("Enter Password: ");
            String password = scanner.nextLine();
            return username.equals(USERNAME) && password.equals(PASSWORD);
        } catch (Exception e) {
            System.out.println("Error during login: " + e.getMessage());
            return false;
        }
    }
}

class Customer {
    String id, name, contact, address;

    public Customer(String id, String name, String contact, String address) {
        this.id = id;
        this.name = name;
        this.contact = contact;
        this.address = address;
    }
}

class Product {
    String id, name;
    double buyingPrice, sellingPrice;
    int quantity;

    public Product(String id, String name, double buyingPrice, double sellingPrice, int quantity) {
        this.id = id;
        this.name = name;
        this.buyingPrice = buyingPrice;
        this.sellingPrice = sellingPrice;
        this.quantity = quantity;
    }
}

class CartItem {
    String productId;
    int quantity;

    public CartItem(String productId, int quantity) {
        this.productId = productId;
        this.quantity = quantity;
    }
}

class CustomerManager {
    static Map<String, Customer> customers = new HashMap<>();
    static Scanner scanner = new Scanner(System.in);

    public static void inputCustomerInfo() {
        try {
            System.out.print("Enter Customer ID: ");
            String id = scanner.nextLine();
            System.out.print("Enter Name: ");
            String name = scanner.nextLine();
            System.out.print("Enter Contact: ");
            String contact = scanner.nextLine();
            System.out.print("Enter Address: ");
            String address = scanner.nextLine();

            customers.put(id, new Customer(id, name, contact, address));
            System.out.println("Customer added successfully!");
        } catch (Exception e) {
            System.out.println("Error adding customer: " + e.getMessage());
        }
    }

    public static Customer getCustomer(String id) {
        return customers.get(id);
    }
}

class ProductManager {
    static Map<String, Product> products = new HashMap<>();
    static Scanner scanner = new Scanner(System.in);

    public static void inputProductInfo() {
        try {
            System.out.print("Enter Product ID: ");
            String id = scanner.nextLine();
            System.out.print("Enter Product Name: ");
            String name = scanner.nextLine();
            System.out.print("Enter Buying Price: ");
            double buyingPrice = scanner.nextDouble();
            System.out.print("Enter Selling Price: ");
            double sellingPrice = scanner.nextDouble();
            System.out.print("Enter Quantity: ");
            int quantity = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            products.put(id, new Product(id, name, buyingPrice, sellingPrice, quantity));
            System.out.println("Product added successfully!");
        } catch (InputMismatchException e) {
            System.out.println("Invalid input for product price or quantity. Please enter valid numbers.");
            scanner.nextLine(); // Clear invalid input
        } catch (Exception e) {
            System.out.println("Error adding product: " + e.getMessage());
        }
    }

    public static Product getProduct(String id) {
        return products.get(id);
    }
}

class CartManager {
    static Map<String, List<CartItem>> carts = new HashMap<>();
    static Scanner scanner = new Scanner(System.in);

    public static void addToCart() {
        try {
            System.out.print("Enter Customer ID: ");
            String customerId = scanner.nextLine();

            if (CustomerManager.getCustomer(customerId) == null) {
                System.out.println("Customer not found!");
                return;
            }

            while (true) {
                System.out.print("Enter Product ID: ");
                String productId = scanner.nextLine();
                Product product = ProductManager.getProduct(productId);

                if (product == null) {
                    System.out.println("Product not found!");
                    return;
                }

                System.out.print("Enter Quantity: ");
                int quantity = scanner.nextInt();
                scanner.nextLine(); // Consume newline

                if (product.quantity < quantity) {
                    System.out.println("Insufficient stock!");
                    return;
                }

                carts.computeIfAbsent(customerId, k -> new ArrayList<>())
                        .add(new CartItem(productId, quantity));
                product.quantity -= quantity;
                System.out.println("Item added to cart successfully!");

                System.out.print("Do you want to add more products to the cart? (yes/no): ");
                String choice = scanner.nextLine();
                if (choice.equalsIgnoreCase("no")) {
                    break;
                }
            }
        } catch (InputMismatchException e) {
            System.out.println("Invalid quantity entered. Please enter a valid number.");
            scanner.nextLine(); // Clear invalid input
        } catch (Exception e) {
            System.out.println("Error adding to cart: " + e.getMessage());
        }
    }

    public static List<CartItem> getCart(String customerId) {
        return carts.getOrDefault(customerId, new ArrayList<>());
    }

    public static void clearCart(String customerId) {
        carts.put(customerId, new ArrayList<>());
    }
}

class BillingManager {
    static double revenue = 0;

    public static void billing() {
        try {
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter Customer ID: ");
            String customerId = scanner.nextLine();
            Customer customer = CustomerManager.getCustomer(customerId);

            if (customer == null) {
                System.out.println("Customer not found!");
                return;
            }

            List<CartItem> cart = CartManager.getCart(customerId);
            if (cart.isEmpty()) {
                System.out.println("Cart is empty!");
                return;
            }

            double total = 0;
            System.out.println("\n===== Invoice =====");
            System.out.println("Customer Name: " + customer.name);
            System.out.println("Contact: " + customer.contact);
            System.out.println("Address: " + customer.address);

            for (CartItem item : cart) {
                Product product = ProductManager.getProduct(item.productId);
                double cost = product.sellingPrice * item.quantity;
                total += cost;
                System.out.println(product.name + " x " + item.quantity + " = " + cost);
            }

            System.out.println("Total: " + total);
            revenue += total;
            CartManager.clearCart(customerId);
        } catch (Exception e) {
            System.out.println("Error during billing: " + e.getMessage());
        }
    }

    public static void displayRevenue() {
        System.out.println("Total Revenue: " + revenue);
    }
}

public class ShopApp {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("===== Shop Application Login =====");
        while (!LoginManager.authenticate()) {
            System.out.println("Invalid username or password. Please try again.");
        }
        System.out.println("Login successful!");

        while (true) {
            try {
                System.out.println("\n===== Menu =====");
                System.out.println("1. Input Customer Info");
                System.out.println("2. Input Product Info");
                System.out.println("3. Add to Cart");
                System.out.println("4. Billing");
                System.out.println("5. Revenue");
                System.out.println("6. Logout");
                System.out.print("Choose an option: ");
                int choice = scanner.nextInt();
                scanner.nextLine(); // Consume newline

                switch (choice) {
                    case 1:
                        CustomerManager.inputCustomerInfo();
                        break;
                    case 2:
                        ProductManager.inputProductInfo();
                        break;
                    case 3:
                        CartManager.addToCart();
                        break;
                    case 4:
                        BillingManager.billing();
                        break;
                    case 5:
                        BillingManager.displayRevenue();
                        break;
                    case 6:
                        System.out.println("Logged out successfully.");
                        return;
                    default:
                        System.out.println("Invalid choice! Try again.");
                }
            } catch (InputMismatchException e) {
                System.out.println("Invalid input. Please enter a number.");
                scanner.nextLine(); // Clear invalid input
            } catch (Exception e) {
                System.out.println("An unexpected error occurred: " + e.getMessage());
            }
        }
    }
}
