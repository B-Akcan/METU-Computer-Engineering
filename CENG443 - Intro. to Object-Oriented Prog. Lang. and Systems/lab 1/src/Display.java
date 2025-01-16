import javax.swing.*;
import java.awt.*;

public class Display extends JPanel {
    public Display() {
        this.setBackground(new Color(220, 220, 220));
    }

    @Override
    public Dimension getPreferredSize() {
        return super.getPreferredSize();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        // TODO
        // Draw all stores and customers
        for (Store store : Common.getStores()) {
            store.draw((Graphics2D) g);
        }
        for (Customer customer : Common.getCustomers()) {
            customer.draw((Graphics2D) g);
        }
        ////
    }
}
