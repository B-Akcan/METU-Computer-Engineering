import java.util.stream.Stream;

public class Purchase {
    public String name;
    public int age;
    public String date;
    public double priceOfBread;
    public int quantityOfBread;
    public double priceOfMilk;
    public int quantityOfMilk;
    public double priceOfEgg;
    public int quantityOfEgg;
    public double priceOfPotatoes;
    public int quantityOfPotatoes;
    public double priceOfTomatoes;
    public int quantityOfTomatoes;

    public Purchase(String n, int a, String d, double pB, int qB, double pM, int qM, double pE, int qE, double pP, int qP, double pT, int qT) {
        name = n;
        age = a;
        date = d;
        priceOfBread = pB;
        quantityOfBread = qB;
        priceOfMilk = pM;
        quantityOfMilk = qM;
        priceOfEgg = pE;
        quantityOfEgg = qE;
        priceOfPotatoes = pP;
        quantityOfPotatoes = qP;
        priceOfTomatoes = pT;
        quantityOfTomatoes = qT;
    }

    public double findMaxPrice() {
        return Stream.of(priceOfBread, priceOfMilk, priceOfEgg, priceOfPotatoes, priceOfTomatoes)
                .mapToDouble(d -> d)
                .max()
                .orElse(-1);
    }

    public double findPaidAmount() {
        return priceOfBread * quantityOfBread
                + priceOfMilk * quantityOfMilk
                + priceOfEgg * quantityOfEgg
                + priceOfPotatoes * quantityOfPotatoes
                + priceOfTomatoes * quantityOfTomatoes;
    }
}
