import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Stream;

public class Main {

    private static Purchase parsePurchase(String[] purchaseString) {
        double priceOfBread = purchaseString[3].isEmpty() ? 0 : Double.parseDouble(purchaseString[3]);
        int quantityOfBread = purchaseString[4].isEmpty() ? 0 : Integer.parseInt(purchaseString[4]);
        double priceOfMilk = purchaseString[5].isEmpty() ? 0 : Double.parseDouble(purchaseString[5]);
        int quantityOfMilk = purchaseString[6].isEmpty() ? 0 : Integer.parseInt(purchaseString[6]);
        double priceOfEgg = purchaseString[7].isEmpty() ? 0 : Double.parseDouble(purchaseString[7]);
        int quantityOfEgg = purchaseString[8].isEmpty() ? 0 : Integer.parseInt(purchaseString[8]);
        double priceOfPotatoes = purchaseString[9].isEmpty() ? 0 : Double.parseDouble(purchaseString[9]);
        int quantityOfPotatoes = purchaseString[10].isEmpty() ? 0 : Integer.parseInt(purchaseString[10]);
        double priceOfTomatoes = purchaseString[11].isEmpty() ? 0 : Double.parseDouble(purchaseString[11]);
        int quantityOfTomatoes = purchaseString[12].isEmpty() ? 0 : Integer.parseInt(purchaseString[12]);

        return new Purchase(purchaseString[0], Integer.parseInt(purchaseString[1]), purchaseString[2],
                priceOfBread, quantityOfBread, priceOfMilk, quantityOfMilk, priceOfEgg, quantityOfEgg, priceOfPotatoes, quantityOfPotatoes, priceOfTomatoes, quantityOfTomatoes);
    }

    public static void main(String[] args) {
        Path path = Path.of(args[0]);
        String questionNo = args[1];
        List<Purchase> purchaseList = new ArrayList<>();

        try {
            List<String[]> purchaseStringList = Files.lines(path)
                    .skip(1)
                    .map(line -> line.split(",", -1))
                    .toList();
            for (String[] purchaseString : purchaseStringList) {
                Purchase p = parsePurchase(purchaseString);
                purchaseList.add(p);
            }
        } catch (IOException e) {
            System.out.println(e.toString());
        }

        switch (questionNo) {
            case "1": {
                Integer result = purchaseList.stream()
                        .filter(p -> p.name.startsWith("A"))
                        .map(p -> p.quantityOfBread + p.quantityOfMilk + p.quantityOfEgg + p.quantityOfPotatoes + p.quantityOfTomatoes)
                        .mapToInt(i -> i)
                        .sum();
                System.out.println(result);

                break;
            }

            case "2": {
                Double result = purchaseList.stream()
                        .map(p -> p.findMaxPrice())
                        .mapToDouble(d -> d)
                        .max()
                        .orElse(-1);
                System.out.println(result);

                break;
            }

            case "3": {
                Double highestPaid = purchaseList.stream()
                        .map(p -> p.findPaidAmount())
                        .mapToDouble(d -> d)
                        .max()
                        .orElse(-1);
                String date = purchaseList.stream()
                        .filter(p -> p.findPaidAmount() == highestPaid)
                        .map(p -> p.date)
                        .findFirst()
                        .orElse(null);
                System.out.println(date);

                break;
            }

            case "4": {
                Integer breadPurchaseAmountBefore2000 = purchaseList.stream()
                        .filter(p -> Integer.parseInt(p.date.substring(0, 4)) < 2000)
                        .map(p -> p.quantityOfBread)
                        .mapToInt(i -> i)
                        .sum();
                Integer milkPurchaseAmountBefore2000 = purchaseList.stream()
                        .filter(p -> Integer.parseInt(p.date.substring(0, 4)) < 2000)
                        .map(p -> p.quantityOfMilk)
                        .mapToInt(i -> i)
                        .sum();
                Integer eggPurchaseAmountBefore2000 = purchaseList.stream()
                        .filter(p -> Integer.parseInt(p.date.substring(0, 4)) < 2000)
                        .map(p -> p.quantityOfEgg)
                        .mapToInt(i -> i)
                        .sum();
                Integer potatoesPurchaseAmountBefore2000 = purchaseList.stream()
                        .filter(p -> Integer.parseInt(p.date.substring(0, 4)) < 2000)
                        .map(p -> p.quantityOfPotatoes)
                        .mapToInt(i -> i)
                        .sum();
                Integer tomatoesPurchaseAmountBefore2000 = purchaseList.stream()
                        .filter(p -> Integer.parseInt(p.date.substring(0, 4)) < 2000)
                        .map(p -> p.quantityOfTomatoes)
                        .mapToInt(i -> i)
                        .sum();

                Integer mostPurchase = Stream.of(breadPurchaseAmountBefore2000, milkPurchaseAmountBefore2000, eggPurchaseAmountBefore2000, potatoesPurchaseAmountBefore2000, tomatoesPurchaseAmountBefore2000)
                        .mapToInt(i -> i)
                        .max()
                        .orElse(-1);

                if (mostPurchase.equals(breadPurchaseAmountBefore2000))
                    System.out.println("bread");
                else if (mostPurchase.equals(milkPurchaseAmountBefore2000))
                    System.out.println("milk");
                else if (mostPurchase.equals(eggPurchaseAmountBefore2000))
                    System.out.println("egg");
                else if (mostPurchase.equals(potatoesPurchaseAmountBefore2000))
                    System.out.println("potatoes");
                else if (mostPurchase.equals(tomatoesPurchaseAmountBefore2000))
                    System.out.println("tomatoes");

                break;
            }

            case "5": {
                Integer breadPurchaseAmountAfter2000 = purchaseList.stream()
                        .filter(p -> Integer.parseInt(p.date.substring(0,4)) >= 2000)
                        .map(p -> p.quantityOfBread)
                        .mapToInt(i -> i)
                        .sum();
                Integer milkPurchaseAmountAfter2000 = purchaseList.stream()
                        .filter(p -> Integer.parseInt(p.date.substring(0,4)) >= 2000)
                        .map(p -> p.quantityOfMilk)
                        .mapToInt(i -> i)
                        .sum();
                Integer eggPurchaseAmountAfter2000 = purchaseList.stream()
                        .filter(p -> Integer.parseInt(p.date.substring(0,4)) >= 2000)
                        .map(p -> p.quantityOfEgg)
                        .mapToInt(i -> i)
                        .sum();
                Integer potatoesPurchaseAmountAfter2000 = purchaseList.stream()
                        .filter(p -> Integer.parseInt(p.date.substring(0,4)) >= 2000)
                        .map(p -> p.quantityOfPotatoes)
                        .mapToInt(i -> i)
                        .sum();
                Integer tomatoesPurchaseAmountAfter2000 = purchaseList.stream()
                        .filter(p -> Integer.parseInt(p.date.substring(0,4)) >= 2000)
                        .map(p -> p.quantityOfTomatoes)
                        .mapToInt(i -> i)
                        .sum();

                Integer leastPopular = Stream.of(breadPurchaseAmountAfter2000, milkPurchaseAmountAfter2000, eggPurchaseAmountAfter2000, potatoesPurchaseAmountAfter2000, tomatoesPurchaseAmountAfter2000)
                        .mapToInt(i -> i)
                        .min()
                        .orElse(-1);

                if (leastPopular.equals(breadPurchaseAmountAfter2000))
                    System.out.println("bread");
                else if (leastPopular.equals(milkPurchaseAmountAfter2000))
                    System.out.println("milk");
                else if (leastPopular.equals(eggPurchaseAmountAfter2000))
                    System.out.println("egg");
                else if (leastPopular.equals(potatoesPurchaseAmountAfter2000))
                    System.out.println("potatoes");
                else if (leastPopular.equals(tomatoesPurchaseAmountAfter2000))
                    System.out.println("tomatoes");

                break;
            }

            case "6": {
                Double avgAgeOfBreadBuyers = purchaseList.stream()
                        .filter(p -> p.quantityOfBread != 0)
                        .map(p -> p.age)
                        .mapToInt(i -> i)
                        .average()
                        .orElse(-1);
                Double avgAgeOfMilkBuyers = purchaseList.stream()
                        .filter(p -> p.quantityOfMilk != 0)
                        .map(p -> p.age)
                        .mapToInt(i -> i)
                        .average()
                        .orElse(-1);
                Double avgAgeOfEggBuyers = purchaseList.stream()
                        .filter(p -> p.quantityOfEgg != 0)
                        .map(p -> p.age)
                        .mapToInt(i -> i)
                        .average()
                        .orElse(-1);
                Double avgAgeOfPotatoesBuyers = purchaseList.stream()
                        .filter(p -> p.quantityOfPotatoes != 0)
                        .map(p -> p.age)
                        .mapToInt(i -> i)
                        .average()
                        .orElse(-1);
                Double avgAgeOfTomatoesBuyers = purchaseList.stream()
                        .filter(p -> p.quantityOfTomatoes != 0)
                        .map(p -> p.age)
                        .mapToInt(i -> i)
                        .average()
                        .orElse(-1);

                Double minimumAvgAge = Stream.of(avgAgeOfBreadBuyers, avgAgeOfMilkBuyers, avgAgeOfEggBuyers, avgAgeOfPotatoesBuyers, avgAgeOfTomatoesBuyers)
                        .mapToDouble(d -> d)
                        .min()
                        .orElse(-1);

                if (minimumAvgAge.equals(avgAgeOfBreadBuyers))
                    System.out.println("bread");
                else if (minimumAvgAge.equals(avgAgeOfMilkBuyers))
                    System.out.println("milk");
                else if (minimumAvgAge.equals(avgAgeOfEggBuyers))
                    System.out.println("egg");
                else if (minimumAvgAge.equals(avgAgeOfPotatoesBuyers))
                    System.out.println("potatoes");
                else if (minimumAvgAge.equals(avgAgeOfTomatoesBuyers))
                    System.out.println("tomatoes");

                break;
            }

            case "7": {
                String breadMinDate = purchaseList.stream()
                        .filter(p -> p.quantityOfBread != 0)
                        .map(p -> p.date)
                        .min((s1, s2) -> s1.compareTo(s2))
                        .orElse(null);
                String breadMaxDate = purchaseList.stream()
                        .filter(p -> p.quantityOfBread != 0)
                        .map(p -> p.date)
                        .max((s1, s2) -> s1.compareTo(s2))
                        .orElse(null);
                String milkMinDate = purchaseList.stream()
                        .filter(p -> p.quantityOfMilk != 0)
                        .map(p -> p.date)
                        .min((s1, s2) -> s1.compareTo(s2))
                        .orElse(null);
                String milkMaxDate = purchaseList.stream()
                        .filter(p -> p.quantityOfMilk != 0)
                        .map(p -> p.date)
                        .max((s1, s2) -> s1.compareTo(s2))
                        .orElse(null);
                String eggMinDate = purchaseList.stream()
                        .filter(p -> p.quantityOfEgg != 0)
                        .map(p -> p.date)
                        .min((s1, s2) -> s1.compareTo(s2))
                        .orElse(null);
                String eggMaxDate = purchaseList.stream()
                        .filter(p -> p.quantityOfEgg != 0)
                        .map(p -> p.date)
                        .max((s1, s2) -> s1.compareTo(s2))
                        .orElse(null);
                String potatoesMinDate = purchaseList.stream()
                        .filter(p -> p.quantityOfPotatoes != 0)
                        .map(p -> p.date)
                        .min((s1, s2) -> s1.compareTo(s2))
                        .orElse(null);
                String potatoesMaxDate = purchaseList.stream()
                        .filter(p -> p.quantityOfPotatoes != 0)
                        .map(p -> p.date)
                        .max((s1, s2) -> s1.compareTo(s2))
                        .orElse(null);
                String tomatoesMinDate = purchaseList.stream()
                        .filter(p -> p.quantityOfTomatoes != 0)
                        .map(p -> p.date)
                        .min((s1, s2) -> s1.compareTo(s2))
                        .orElse(null);
                String tomatoesMaxDate = purchaseList.stream()
                        .filter(p -> p.quantityOfTomatoes != 0)
                        .map(p -> p.date)
                        .max((s1, s2) -> s1.compareTo(s2))
                        .orElse(null);

                Double breadPriceAtMinDate = purchaseList.stream()
                        .filter(p -> p.date.equals(breadMinDate))
                        .map(p -> p.priceOfBread)
                        .findFirst()
                        .orElse(-1.0);
                Double breadPriceAtMaxDate = purchaseList.stream()
                        .filter(p -> p.date.equals(breadMaxDate))
                        .map(p -> p.priceOfBread)
                        .findFirst()
                        .orElse(-1.0);
                Double milkPriceAtMinDate = purchaseList.stream()
                        .filter(p -> p.date.equals(milkMinDate))
                        .map(p -> p.priceOfMilk)
                        .findFirst()
                        .orElse(-1.0);
                Double milkPriceAtMaxDate = purchaseList.stream()
                        .filter(p -> p.date.equals(milkMaxDate))
                        .map(p -> p.priceOfMilk)
                        .findFirst()
                        .orElse(-1.0);
                Double eggPriceAtMinDate = purchaseList.stream()
                        .filter(p -> p.date.equals(eggMinDate))
                        .map(p -> p.priceOfEgg)
                        .findFirst()
                        .orElse(-1.0);
                Double eggPriceAtMaxDate = purchaseList.stream()
                        .filter(p -> p.date.equals(eggMaxDate))
                        .map(p -> p.priceOfEgg)
                        .findFirst()
                        .orElse(-1.0);
                Double potatoesPriceAtMinDate = purchaseList.stream()
                        .filter(p -> p.date.equals(potatoesMinDate))
                        .map(p -> p.priceOfPotatoes)
                        .findFirst()
                        .orElse(-1.0);
                Double potatoesPriceAtMaxDate = purchaseList.stream()
                        .filter(p -> p.date.equals(potatoesMaxDate))
                        .map(p -> p.priceOfPotatoes)
                        .findFirst()
                        .orElse(-1.0);
                Double tomatoesPriceAtMinDate = purchaseList.stream()
                        .filter(p -> p.date.equals(tomatoesMinDate))
                        .map(p -> p.priceOfTomatoes)
                        .findFirst()
                        .orElse(-1.0);
                Double tomatoesPriceAtMaxDate = purchaseList.stream()
                        .filter(p -> p.date.equals(tomatoesMaxDate))
                        .map(p -> p.priceOfTomatoes)
                        .findFirst()
                        .orElse(-1.0);

                double breadInflation = breadPriceAtMaxDate / breadPriceAtMinDate;
                double milkInflation = milkPriceAtMaxDate / milkPriceAtMinDate;
                double eggInflation = eggPriceAtMaxDate / eggPriceAtMinDate;
                double potatoesInflation = potatoesPriceAtMaxDate / potatoesPriceAtMinDate;
                double tomatoesInflation = tomatoesPriceAtMaxDate / tomatoesPriceAtMinDate;

                double mostInflated = Stream.of(breadInflation, milkInflation, eggInflation, potatoesInflation, tomatoesInflation)
                        .mapToDouble(d -> d)
                        .max()
                        .orElse(-1.0);

                if (mostInflated == breadInflation)
                    System.out.println("bread");
                else if (mostInflated == milkInflation)
                    System.out.println("milk");
                else if (mostInflated == eggInflation)
                    System.out.println("egg");
                else if (mostInflated == potatoesInflation)
                    System.out.println("potatoes");
                else if (mostInflated == tomatoesInflation)
                    System.out.println("tomatoes");

                break;
            }

            default: break;
        }
    }
}
