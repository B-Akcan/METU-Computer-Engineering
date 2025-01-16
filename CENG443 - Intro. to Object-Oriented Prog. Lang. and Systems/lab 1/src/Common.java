import java.awt.*;
import java.util.Iterator;
import java.util.Vector;
import java.util.concurrent.ThreadLocalRandom;

public class Common {
    private static final String title = "Economics 101";
    private static final int windowWidth = 1500; // 1650
    private static final int windowHeight = 800; // 1000

    private static final int entityRadius = 20; // radius of drawn entity (customer or store)

    private static final int storeNo = 10; // number of stores in the simulation
    private static final int customerNo = 10; // number of customers

    private static final int stockReplenishmentFrequency = 3000; // number of stepAllEntities calls before replenishing
                                                                 // all stores

    private static final int foodBottomPrice = 20;
    private static final int foodCeilingPrice = 50;
    private static final int electronicsBottomPrice = 200;
    private static final int electronicsCeilingPrice = 2000;
    private static final int LuxuryBottomPrice = 5000;
    private static final int LuxuryCeilingPrice = 10000;

    private static final int minimumShoppingListLength = 5;
    private static final int maximumShoppingListLength = 10;

    private static final int stockStorageMin = 15; // minimum size of storage available for a store
    private static final int stockStorageMax = 25; // maximum number of storage available for a store

    private static final int customerMovementSpeed = 2;
    private static final Font font = new Font("Verdana", Font.BOLD, 20);

    public static String getTitle() {
        return title;
    }

    public static int getWindowWidth() {
        return windowWidth;
    }

    public static int getWindowHeight() {
        return windowHeight;
    }

    public static int getEntityRadius() {
        return entityRadius;
    }

    public static Font getFont() {
        return font;
    }

    public static int getCustomerMovementSpeed() {
        return customerMovementSpeed;
    }

    // TODO
    // put your necessary fields and methods here
    ////
    private static Vector<Store> stores = new Vector<>();
    private static Vector<Customer> customers = new Vector<>();

    public static Vector<Store> getStores() {
        return stores;
    }

    public static Vector<Customer> getCustomers() {
        return customers;
    }

    public static int getStockReplenishmentFrequency() {
        return stockReplenishmentFrequency;
    }

    public static int setShoppingListLength() {
        return randInt(minimumShoppingListLength, maximumShoppingListLength);
    }

    public static int setPrice(ProductType productType) {
        return switch (productType) {
            case ProductType.FOOD -> randInt(foodBottomPrice, foodCeilingPrice);
            case ProductType.ELECTRONICS -> randInt(electronicsBottomPrice, electronicsCeilingPrice);
            case ProductType.LUXURY -> randInt(LuxuryBottomPrice, LuxuryCeilingPrice);
        };
    }

    public static int setMaximumStock() {
        return randInt(stockStorageMin, stockStorageMax);
    }

    public static void createStore(ProductType pt) {
        int positionX = randInt(0, windowWidth - 2*entityRadius);
        int positionY = randInt(0, windowHeight - 2*entityRadius);
        Store store = new Store(positionX, positionY, pt);
        stores.add(store);
    }

    public static void createAllStores() {
        int productTypeCount = ProductType.values().length;
        int minStoreCountPerProductType = storeNo / productTypeCount;
        int i = 0;
        int j = 0;
        for (i = 0; i < productTypeCount; i++) {
            for (j = 0; j < minStoreCountPerProductType; j++) {
                createStore(ProductType.values()[i]);
            }
        }
        Vector<Integer> usedValues = new Vector<>();
        for (int k = i*j; k < storeNo; k++) {
            int randomInt = randInt(0, productTypeCount - 1);
            while (usedValues.contains(randomInt))
                randomInt = randInt(0, productTypeCount - 1);
            usedValues.add(randomInt);

            ProductType pt = ProductType.values()[randomInt];
            createStore(pt);
        }
    }

    public static void createCustomer() {
        int positionX = randInt(0, windowWidth - 2*entityRadius);
        int positionY = randInt(0, windowHeight - 2*entityRadius);
        Customer customer = new Customer(positionX, positionY);
        customers.add(customer);
    }

    public static void createAllCustomers() {
        for (int i = 0; i < customerNo; i++)
            createCustomer();
    }

    public static Store findCheapestStoreWithProductType(ProductType pt) {
        int price = Integer.MAX_VALUE;
        Store cheapestStore = null;
        for (Store s : stores) {
            if (s.getProductType() == pt && s.getSellingPrice() < price) {
                price = s.getSellingPrice();
                cheapestStore = s;
            }
        }
        return cheapestStore;
    }

    public static Store findClosestStoreWithProductType(Position positionOfCustomer, ProductType pt) {
        double distance = Double.MAX_VALUE;
        Store closestStore = null;
        for (Store s : stores) {
            if (s.getProductType() == pt && positionOfCustomer.distanceTo(s.position) < distance) {
                distance = positionOfCustomer.distanceTo(s.position);
                closestStore = s;
            }
        }
        return closestStore;
    }

    public static Store findClosestStoreWithProductTypeExceptVisitedStore(Position positionOfCustomer, ProductType pt, Store storeToExclude) {
        double distance = Double.MAX_VALUE;
        Store closestStore = null;
        for (Store s : stores) {
            if (s != storeToExclude && s.getProductType() == pt && positionOfCustomer.distanceTo(s.position) < distance) {
                distance = positionOfCustomer.distanceTo(s.position);
                closestStore = s;
            }
        }
        return closestStore;
    }

    public static Store findClosestNotVisitedStore(Position positionOfCustomer, Vector<Store> visitedStores) {
        double distance = Double.MAX_VALUE;
        Store closestStore = null;
        for (Store s : stores) {
            if (!visitedStores.contains(s) && positionOfCustomer.distanceTo(s.position) < distance) {
                distance = positionOfCustomer.distanceTo(s.position);
                closestStore = s;
            }
        }
        return closestStore;
    }

    public static Position findClosestExit(Position positionOfCustomer) {
        Position exit = new Position(0, 0);
        double exitRight = windowWidth - positionOfCustomer.getX();
        double exitLeft = positionOfCustomer.getX();
        double exitTop = positionOfCustomer.getY();
        double exitBottom = windowHeight - positionOfCustomer.getY();

        if (exitLeft < exitRight && exitLeft < exitTop && exitLeft < exitBottom) {
            exit.setX(0);
            exit.setY(positionOfCustomer.getY());
        }
        else if (exitRight <= exitLeft && exitRight <= exitTop && exitRight <= exitBottom) {
            exit.setX(windowWidth);
            exit.setY(positionOfCustomer.getY());
        }
        else if (exitTop < exitBottom && exitTop < exitLeft && exitTop < exitRight) {
            exit.setX(positionOfCustomer.getX());
            exit.setY(0);
        }
        else {
            exit.setX(positionOfCustomer.getX());
            exit.setY(windowHeight);
        }

        return exit;
    }

    public static void stepAllCustomers() {
        Iterator<Customer> it = Common.getCustomers().iterator();
        while (it.hasNext()) {
            Customer c = it.next();
            if (c.getCanBeRemoved()) {
                it.remove();
                createCustomer();
                break;
            }
            else
                c.step();
        }
    }

    public static void stepAllStores() {
        for (Store s : stores)
            s.step();
    }

    // TODO
    // When adding new stores or customers, their position, shopping list,
    // max stock etc. should be random between the ranges defined above.
    // You can use the function below or define your own function to generate
    // a random integer
    public static int randInt(int min, int max) {
        return ThreadLocalRandom.current().nextInt(min, max + 1);
    }
    // E.g.
    /*
    //Product Generation
    switch(randInt(0,2)){
        case 0:
            //Food
            break;
        case 1:
            //Electronics
            break;
        case 2:
            //Luxury
            break;
    }
    //x position of the center of entity generation
    double centerX = randInt(0,windowWidth-2*entityRadius)
    */

    // TODO
    // Create customers and stores
    // Hint: you can also use a static block for this
    // Also note that you should make sure there are about equal number of stores
    // for all products
    // like 4 stores for food, 3 stores for electronics and 4 stores for luxury etc.
    // Otherwise your simulation may deadlock
    static {
        createAllStores();
        createAllCustomers();
    }
    ////
}
