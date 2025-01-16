import java.awt.*;
import java.util.Iterator;
import java.util.Vector;

public class Customer extends Entity {
    private Vector<ProductType> shoppingList;
    private ShoppingStrategy shoppingStrategy;
    private String shoppingStrategyAbbreviation;
    private boolean canBeRemoved;
    private Store visitedStore;
    private final Vector<Store> visitedStores;

    public Customer(double x, double y) {
        super(x, y);
        initializeShoppingList();
        initializeShoppingStrategy();
        canBeRemoved = false;
        visitedStore = null;
        visitedStores = new Vector<>();
    }

    @Override
    public void draw(Graphics2D g2d) {
        String text = null;
        if (shoppingList.size() >= 3) {
            text = String.format("%s,%c,%c,%c",
                    shoppingStrategyAbbreviation,
                    shoppingList.get(0).name().charAt(0),
                    shoppingList.get(1).name().charAt(0),
                    shoppingList.get(2).name().charAt(0));
        } else if (shoppingList.size() == 2) {
            text = String.format("%s,%c,%c",
                    shoppingStrategyAbbreviation,
                    shoppingList.get(0).name().charAt(0),
                    shoppingList.get(1).name().charAt(0));
        } else if (shoppingList.size() == 1) {
            text = String.format("%s,%c",
                    shoppingStrategyAbbreviation,
                    shoppingList.get(0).name().charAt(0));
        } else {
            text = String.format("%s",
                    shoppingStrategyAbbreviation);
        }

        drawHelper(g2d, text, Color.gray);
    }

    @Override
    public void step() {
        if (!shoppingList.isEmpty()) {
            Store storeToGo;

            switch (shoppingStrategy) {
                case CHEAPEST:
                    storeToGo = Common.findCheapestStoreWithProductType(shoppingList.getFirst());
                    if (isArrivedToPosition(storeToGo.position)) {
                        try {
                            storeToGo.sell();
                            shoppingList.removeFirst();
                        } catch (OutOfStockException _) {}
                    }
                    break;

                case CLOSEST:
                    storeToGo = Common.findClosestStoreWithProductTypeExceptVisitedStore(position, shoppingList.getFirst(), visitedStore);
                    if (isArrivedToPosition(storeToGo.position)) {
                        try {
                            storeToGo.sell();
                            shoppingList.removeFirst();
                        } catch (OutOfStockException _) {
                            visitedStore = storeToGo;
                        }
                    }
                    break;

                case TRAVELLING:
                    storeToGo = Common.findClosestNotVisitedStore(position, visitedStores);
                    if (storeToGo != null) {
                        if (isArrivedToPosition(storeToGo.position)) {
                            Iterator<ProductType> it = shoppingList.iterator();
                            while (it.hasNext()) {
                                ProductType pt = it.next();
                                if (pt == storeToGo.getProductType()) {
                                    try {
                                        storeToGo.sell();
                                        it.remove();
                                    } catch (OutOfStockException _) {
                                        break;
                                    }
                                }
                            }
                            visitedStores.add(storeToGo);
                        }
                    }
                    else {
                        visitedStores.clear();
                    }
            }
        } else {
            Position exitPosition = Common.findClosestExit(position);
            if (isArrivedToPosition(exitPosition)) {
                canBeRemoved = true;
            }
        }
    }

    public boolean getCanBeRemoved() {
        return canBeRemoved;
    }

    private void initializeShoppingList() {
        shoppingList = new Vector<>();
        int shoppingListLength = Common.setShoppingListLength();

        for (int i = 0; i < shoppingListLength; i++) {
            int productId = Common.randInt(0, 2);
            switch (productId) {
                case 0:
                    shoppingList.add(ProductType.FOOD);
                    break;
                case 1:
                    shoppingList.add(ProductType.ELECTRONICS);
                    break;
                case 2:
                    shoppingList.add(ProductType.LUXURY);
                    break;
            }
        }
    }

    private void initializeShoppingStrategy() {
        int shoppingStrategyId = Common.randInt(0, 2);
        switch (shoppingStrategyId) {
            case 0:
                shoppingStrategy = ShoppingStrategy.CHEAPEST;
                shoppingStrategyAbbreviation = "Ch";
                break;
            case 1:
                shoppingStrategy = ShoppingStrategy.CLOSEST;
                shoppingStrategyAbbreviation = "Cl";
                break;
            case 2:
                shoppingStrategy = ShoppingStrategy.TRAVELLING;
                shoppingStrategyAbbreviation = "Tr";
                break;
        }
    }

    private boolean isArrivedToPosition(Position position) {
        Vector<Boolean> isPositionChanged = new Vector<>(2);
        isPositionChanged.add(true);
        isPositionChanged.add(true);

        move(position, isPositionChanged);

        return (!isPositionChanged.get(0) && !isPositionChanged.get(1));
    }

    private void move(Position positionToMove, Vector<Boolean> isPositionChanged) {
        if (positionToMove.getX() - Common.getEntityRadius() > position.getX()) {
            position.setX(position.getX() + Common.getCustomerMovementSpeed());
            isPositionChanged.set(0, true);
        } else if (positionToMove.getX() + Common.getEntityRadius() < position.getX()) {
            position.setX(position.getX() - Common.getCustomerMovementSpeed());
            isPositionChanged.set(0, true);
        } else
            isPositionChanged.set(0, false);

        if (positionToMove.getY() - Common.getEntityRadius() > position.getY()) {
            position.setY(position.getY() + Common.getCustomerMovementSpeed());
            isPositionChanged.set(1, true);
        } else if (positionToMove.getY() + Common.getEntityRadius() < position.getY()) {
            position.setY(position.getY() - Common.getCustomerMovementSpeed());
            isPositionChanged.set(1, true);
        } else
            isPositionChanged.set(1, false);
    }
}

