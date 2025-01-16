import java.awt.*;

public class Store extends Entity {
    private final ProductType productType;
    private final int sellingPrice;
    private final int maximumStock;
    private int currentStock;

    public Store(double x, double y, ProductType pt) {
        super(x, y);
        productType = pt;
        sellingPrice = Common.setPrice(productType);
        maximumStock = Common.setMaximumStock();
        currentStock = maximumStock;
    }

    @Override
    public void draw(Graphics2D g2d) {
        String text = String.format("%c,%d,%d", productType.name().charAt(0), currentStock, sellingPrice);
        drawHelper(g2d, text, Color.orange);
    }

    @Override
    public void step() {
        currentStock = maximumStock;
    }

    public ProductType getProductType() {
        return productType;
    }

    public int getSellingPrice() {
        return sellingPrice;
    }

    public void sell() {
        if (currentStock > 0)
            currentStock--;
        else
            throw new OutOfStockException("The store is out of stock.");
    }
}
