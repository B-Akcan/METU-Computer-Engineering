package ceng.ceng351.cengfactorydb;

import javax.swing.plaf.nimbus.State;
import java.sql.*;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Vector;

public class CENGFACTORYDB implements ICENGFACTORYDB{
    private static String user = "e2580181"; // TODO: Your userName
    private static String password = "GHx(pz04Aes+"; //  TODO: Your password
    private static String host = "144.122.71.128"; // host name
    private static String database = "db2580181"; // TODO: Your database name
    private static int port = 8080; // port
    private static Connection connection = null;

    /**
     * Place your initialization code inside if required.
     *
     * <p>
     * This function will be called before all other operations. If your implementation
     * need initialization , necessary operations should be done inside this function. For
     * example, you can set your connection to the database server inside this function.
     */
    public void initialize() {
        String url = "jdbc:mysql://" + host + ":" + port + "/" + database;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection =  DriverManager.getConnection(url, user, password);
        }
        catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    /**
     * Should create the necessary tables when called.
     *
     * @return the number of tables that are created successfully.
     */
    public int createTables() {
        int numberofTablesInserted = 0;

        String queryCreateFactoryTable = "CREATE TABLE IF NOT EXISTS Factory ( " +
                "factoryId int, " +
                "factoryName varchar(30), " +
                "factoryType varchar(20), " +
                "country varchar(20), " +
                "primary key (factoryId));";

        String queryCreateEmployeeTable = "CREATE TABLE IF NOT EXISTS Employee ( " +
                "employeeId int, " +
                "employeeName varchar(30), " +
                "department varchar(20), " +
                "salary int, " +
                "primary key (employeeId));";

        String queryCreateWorksInTable = "CREATE TABLE IF NOT EXISTS Works_In ( " +
                "worksIn_factoryId int, " +
                "worksIn_employeeId int, " +
                "startDate date, " +
                "primary key (worksIn_factoryId, worksIn_employeeId), " +
                "constraint worksIn_factoryId " +
                "foreign key (worksIn_factoryId) references Factory(factoryId) on delete cascade on update cascade, " +
                "constraint worksIn_employeeId " +
                "foreign key (worksIn_employeeId) references Employee(employeeId) on delete cascade on update cascade);";

        String queryCreateProductTable = "CREATE TABLE IF NOT EXISTS Product ( " +
                "productId int, " +
                "productName varchar(30), " +
                "productType varchar(20), " +
                "primary key (productId));";

        String queryCreateProduceTable = "CREATE TABLE IF NOT EXISTS Produce ( " +
                "produce_factoryId int, " +
                "produce_productId int, " +
                "amount int, " +
                "productionCost int, " +
                "primary key (produce_factoryId, produce_productId), " +
                "constraint produce_factoryId " +
                "foreign key (produce_factoryId) references Factory(factoryId) on delete cascade on update cascade, " +
                "constraint produce_productId " +
                "foreign key (produce_productId) references Product(productId) on delete cascade on update cascade);";

        String queryCreateShipmentTable = "CREATE TABLE IF NOT EXISTS Shipment ( " +
                "shipment_factoryId int, " +
                "shipment_productId int, " +
                "amount int, " +
                "pricePerUnit int, " +
                "primary key (shipment_factoryId, shipment_productId), " +
                "constraint shipment_factoryId " +
                "foreign key (shipment_factoryId) references Factory(factoryId) on delete cascade on update cascade, " +
                "constraint shipment_productId " +
                "foreign key (shipment_productId) references Product(productId) on delete cascade on update cascade);";

        try {
            Statement statement = connection.createStatement();

            statement.executeUpdate(queryCreateFactoryTable);
            numberofTablesInserted++;

            statement.executeUpdate(queryCreateEmployeeTable);
            numberofTablesInserted++;

            statement.executeUpdate(queryCreateWorksInTable);
            numberofTablesInserted++;

            statement.executeUpdate(queryCreateProductTable);
            numberofTablesInserted++;

            statement.executeUpdate(queryCreateProduceTable);
            numberofTablesInserted++;

            statement.executeUpdate(queryCreateShipmentTable);
            numberofTablesInserted++;

            statement.close();
        }

        catch (SQLException e) {
            e.printStackTrace();
        }

        return numberofTablesInserted;
    }

    /**
     * Should drop the tables if exists when called.
     *
     * @return the number of tables are dropped successfully.
     */
    public int dropTables() {
        int numberofTablesDropped = 0;

        String queryDropFactoryTable = "DROP TABLE IF EXISTS Factory;";

        String queryDropEmployeeTable = "DROP TABLE IF EXISTS Employee;";

        String queryDropWorksInTable = "DROP TABLE IF EXISTS Works_In;";

        String queryDropProductTable = "DROP TABLE IF EXISTS Product;";

        String queryDropProduceTable = "DROP TABLE IF EXISTS Produce;";

        String queryDropShipmentTable = "DROP TABLE IF EXISTS Shipment;";


        try {
            Statement statement = connection.createStatement();

            statement.executeUpdate(queryDropWorksInTable);
            numberofTablesDropped++;

            statement.executeUpdate(queryDropProduceTable);
            numberofTablesDropped++;

            statement.executeUpdate(queryDropShipmentTable);
            numberofTablesDropped++;

            statement.executeUpdate(queryDropFactoryTable);
            numberofTablesDropped++;

            statement.executeUpdate(queryDropEmployeeTable);
            numberofTablesDropped++;

            statement.executeUpdate(queryDropProductTable);
            numberofTablesDropped++;

            statement.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return numberofTablesDropped;
    }

    /**
     * Should insert an array of Factory into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertFactory(Factory[] factories) {
        int numberofRowsInserted = 0;

        for (int i = 0; i < factories.length; i++)
        {
            try {
                Factory factory = factories[i];

                PreparedStatement stmt = connection.prepareStatement("INSERT INTO Factory VALUES (?,?,?,?);");
                stmt.setInt(1, factory.getFactoryId());
                stmt.setString(2, factory.getFactoryName());
                stmt.setString(3, factory.getFactoryType());
                stmt.setString(4, factory.getCountry());

                stmt.executeUpdate();

                stmt.close();
                numberofRowsInserted++;

            }
            catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return numberofRowsInserted;
    }

    /**
     * Should insert an array of Employee into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertEmployee(Employee[] employees) {
        int numberofRowsInserted = 0;

        for (int i = 0; i < employees.length; i++)
        {
            try {
                Employee employee = employees[i];

                PreparedStatement stmt = connection.prepareStatement("INSERT INTO Employee VALUES (?,?,?,?);");
                stmt.setInt(1, employee.getEmployeeId());
                stmt.setString(2, employee.getEmployeeName());
                stmt.setString(3, employee.getDepartment());
                stmt.setInt(4, employee.getSalary());

                stmt.executeUpdate();

                stmt.close();
                numberofRowsInserted++;

            }
            catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return numberofRowsInserted;
    }

    /**
     * Should insert an array of WorksIn into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertWorksIn(WorksIn[] worksIns) {
        int numberofRowsInserted = 0;

        for (int i = 0; i < worksIns.length; i++)
        {
            try {
                WorksIn worksIn = worksIns[i];

                PreparedStatement stmt = connection.prepareStatement("INSERT INTO Works_In VALUES (?,?,?);");
                stmt.setInt(1, worksIn.getFactoryId());
                stmt.setInt(2, worksIn.getEmployeeId());
                stmt.setString(3, worksIn.getStartDate());

                stmt.executeUpdate();

                stmt.close();
                numberofRowsInserted++;

            }
            catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return numberofRowsInserted;
    }

    /**
     * Should insert an array of Product into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertProduct(Product[] products) {
        int numberofRowsInserted = 0;

        for (int i = 0; i < products.length; i++)
        {
            try {
                Product product = products[i];

                PreparedStatement stmt = connection.prepareStatement("INSERT INTO Product VALUES (?,?,?);");
                stmt.setInt(1, product.getProductId());
                stmt.setString(2, product.getProductName());
                stmt.setString(3, product.getProductType());

                stmt.executeUpdate();

                stmt.close();
                numberofRowsInserted++;

            }
            catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return numberofRowsInserted;
    }


    /**
     * Should insert an array of Produce into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertProduce(Produce[] produces) {
        int numberofRowsInserted = 0;

        for (int i = 0; i < produces.length; i++)
        {
            try {
                Produce produce = produces[i];

                PreparedStatement stmt = connection.prepareStatement("INSERT INTO Produce VALUES (?,?,?,?);");
                stmt.setInt(1, produce.getFactoryId());
                stmt.setInt(2, produce.getProductId());
                stmt.setInt(3, produce.getAmount());
                stmt.setInt(4, produce.getProductionCost());

                stmt.executeUpdate();

                stmt.close();
                numberofRowsInserted++;

            }
            catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return numberofRowsInserted;
    }


    /**
     * Should insert an array of Shipment into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertShipment(Shipment[] shipments) {
        int numberofRowsInserted = 0;

        for (int i = 0; i < shipments.length; i++)
        {
            try {
                Shipment shipment = shipments[i];

                PreparedStatement stmt = connection.prepareStatement("INSERT INTO Shipment VALUES (?,?,?,?);");
                stmt.setInt(1, shipment.getFactoryId());
                stmt.setInt(2, shipment.getProductId());
                stmt.setInt(3, shipment.getAmount());
                stmt.setInt(4, shipment.getPricePerUnit());

                stmt.executeUpdate();

                stmt.close();
                numberofRowsInserted++;

            }
            catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return numberofRowsInserted;
    }

    /**
     * Should return all factories that are located in a particular country.
     *
     * @return Factory[]
     */
    public Factory[] getFactoriesForGivenCountry(String country) {
        ResultSet rs;
        ArrayList<Factory> reslist = new ArrayList<>();

        try {
            PreparedStatement stmt = connection.prepareStatement("SELECT DISTINCT F.factoryId, F.factoryName, F.factoryType " +
                                                                     "FROM Factory F " +
                                                                     "WHERE F.country = ? " +
                                                                     "ORDER BY F.factoryId ASC;");
            stmt.setString(1, country);

            rs = stmt.executeQuery();

            while (rs.next()) {

                int factoryId = rs.getInt("factoryId");
                String factoryName = rs.getString("factoryName");
                String factoryType = rs.getString("factoryType");

                Factory obj = new Factory(factoryId, factoryName, factoryType, country);
                reslist.add(obj);
            }

            stmt.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        Factory[] resarray = new Factory[reslist.size()];

        return reslist.toArray(resarray);
    }



    /**
     * Should return all factories without any working employees.
     *
     * @return Factory[]
     */
    public Factory[] getFactoriesWithoutAnyEmployee() {
        ResultSet rs;
        ArrayList<Factory> reslist = new ArrayList<>();

        String query = "SELECT DISTINCT F.factoryId, F.factoryName, F.factoryType, F.country " +
                       "FROM Factory F " +
                       "WHERE F.factoryId IN " +
                            "(SELECT F1.factoryId " +
                            "FROM Factory F1 " +
                            "EXCEPT " +
                            "SELECT W.worksIn_factoryId " +
                            "FROM Works_In W) " +
                       "ORDER BY F.factoryId ASC;";
        try {
            Statement st = connection.createStatement();
            rs = st.executeQuery(query);

            while (rs.next()) {

                int factoryId = rs.getInt("factoryId");
                String factoryName = rs.getString("factoryName");
                String factoryType = rs.getString("factoryType");
                String country = rs.getString("country");

                Factory obj = new Factory(factoryId, factoryName, factoryType, country);
                reslist.add(obj);
            }

            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        Factory[] resarray = new Factory[reslist.size()];

        return reslist.toArray(resarray);
    }

    /**
     * Should return all factories that produce all products for a particular productType
     *
     * @return Factory[]
     */
    public Factory[] getFactoriesProducingAllForGivenType(String productType) {
        ResultSet rs;
        ArrayList<Factory> reslist = new ArrayList<Factory>();

        try {
            PreparedStatement stmt = connection.prepareStatement("SELECT DISTINCT F.factoryId, F.factoryName, F.factoryType, F.country " +
                                                                     "FROM Factory F " +
                                                                     "WHERE NOT EXISTS (SELECT Pt1.productId " +
                                                                                       "FROM Product Pt1 " +
                                                                                       "WHERE Pt1.productType = ? " +
                                                                                       "EXCEPT " +
                                                                                       "SELECT P.produce_productId " +
                                                                                       "FROM Produce P, Product Pt2 " +
                                                                                       "WHERE P.produce_factoryId = F.factoryId AND P.produce_productId = Pt2.productId AND Pt2.productType = ?) " +
                                                                     "ORDER BY F.factoryId ASC;");
            stmt.setString(1, productType);
            stmt.setString(2, productType);

            rs = stmt.executeQuery();

            while (rs.next())
            {
                int factoryId = rs.getInt("factoryId");
                String factoryName = rs.getString("factoryName");
                String factoryType = rs.getString("factoryType");
                String country = rs.getString("country");

                Factory obj = new Factory(factoryId, factoryName, factoryType, country);
                reslist.add(obj);
            }

            stmt.close();
        }
        catch (SQLException e){
            e.printStackTrace();
        }

        Factory[] resarray = new Factory[reslist.size()];
        return reslist.toArray(resarray);
    }


    /**
     * Should return the products that are produced in a particular factory but
     * don’t have any shipment from that factory.
     *
     * @return Product[]
     */
    public Product[] getProductsProducedNotShipped() {
        ResultSet rs;
        ArrayList<Product> reslist = new ArrayList<Product>();

        String query = "SELECT DISTINCT P.productId, P.productName, P.productType " +
                       "FROM Product P " +
                       "WHERE P.productId IN ( " +
                                            "SELECT Pr.produce_productId " +
                                            "FROM Produce Pr " +
                                            "WHERE Pr.produce_productId NOT IN ( " +
                                                                            "SELECT S.shipment_productId " +
                                                                            "FROM Shipment S " +
                                                                            "WHERE Pr.produce_factoryId = S.shipment_factoryId)) " +
                       "ORDER BY P.productId ASC;";

        try {
            Statement st = connection.createStatement();
            rs = st.executeQuery(query);

            while (rs.next()) {

                int productId = rs.getInt("productId");
                String productName = rs.getString("productName");
                String productType = rs.getString("productType");

                Product obj = new Product(productId, productName, productType);
                reslist.add(obj);
            }

            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        Product[] resarray = new Product[reslist.size()];

        return reslist.toArray(resarray);
    }


    /**
     * For a given factoryId and department, should return the average salary of
     *     the employees working in that factory and that specific department.
     *
     * @return double
     */
    public double getAverageSalaryForFactoryDepartment(int factoryId, String department) {
        ResultSet rs;
        double avg = 0.0;

        try {
            PreparedStatement stmt = connection.prepareStatement("SELECT AVG(E.salary) AS avgSalary " +
                                                                     "FROM Works_In W, Employee E " +
                                                                     "WHERE W.worksIn_employeeId = E.employeeId AND W.worksIn_factoryId = ? AND E.department = ?;");
            stmt.setInt(1, factoryId);
            stmt.setString(2, department);

            rs = stmt.executeQuery();
            rs.next();

            avg = rs.getDouble("avgSalary");
            stmt.close();
        }
        catch (SQLException e){
            e.printStackTrace();
        }

        return avg;
    }


    /**
     * Should return the most profitable products for each factory
     *
     * @return QueryResult.MostValueableProduct[]
     */
    public QueryResult.MostValueableProduct[] getMostValueableProducts() {
        ResultSet rs;
        ArrayList<QueryResult.MostValueableProduct> reslist = new ArrayList<QueryResult.MostValueableProduct>();

        String query =  "SELECT DISTINCT T.produce_factoryId, P.productId, P.productName, P.productType, T.profit " +
                        "FROM " +
                            "(SELECT DISTINCT Pr.produce_factoryId, Pr.produce_productId, S.amount*S.pricePerUnit-Pr.amount*Pr.productionCost AS profit " +
                            "FROM Produce Pr, Shipment S " +
                            "WHERE Pr.produce_factoryId = S.shipment_factoryId AND Pr.produce_productId = S.shipment_productId " +
                            "UNION " +
                            "SELECT DISTINCT Pr.produce_factoryId, Pr.produce_productId, -Pr.amount*Pr.productionCost AS profit " +
                            "FROM Produce Pr " +
                            "WHERE Pr.produce_productId NOT IN (SELECT S.shipment_productId FROM Shipment S) " +
                            "UNION " +
                            "SELECT DISTINCT Pr.produce_factoryId, Pr.produce_productId, -Pr.amount*Pr.productionCost AS profit " +
                            "FROM Produce Pr, Shipment S " +
                            "WHERE Pr.produce_productId = S.shipment_productId AND Pr.produce_factoryId != S.shipment_factoryId) T, Product P " +
                        "WHERE T.produce_productId = P.productId AND (T.produce_factoryId, T.profit) IN " +
                            "(SELECT DISTINCT T2.produce_factoryId, MAX(profit) AS profit " +
                            "FROM " +
                                "(SELECT DISTINCT Pr.produce_factoryId, MAX(S.amount*S.pricePerUnit-Pr.amount*Pr.productionCost) AS profit " +
                                "FROM Produce Pr, Shipment S " +
                                "WHERE Pr.produce_factoryId = S.shipment_factoryId AND Pr.produce_productId = S.shipment_productId " +
                                "GROUP BY Pr.produce_factoryId " +
                                "UNION " +
                                "SELECT DISTINCT Pr.produce_factoryId, MAX(-Pr.amount*Pr.productionCost) AS profit " +
                                "FROM Produce Pr " +
                                "WHERE Pr.produce_productId NOT IN (SELECT S.shipment_productId FROM Shipment S) " +
                                "GROUP BY Pr.produce_factoryId " +
                                "UNION " +
                                "SELECT DISTINCT Pr.produce_factoryId, MAX(-Pr.amount*Pr.productionCost) AS profit " +
                                "FROM Produce Pr, Shipment S " +
                                "WHERE Pr.produce_productId = S.shipment_productId AND Pr.produce_factoryId != S.shipment_factoryId " +
                                "GROUP BY Pr.produce_factoryId) T2 " +
                            "GROUP BY T2.produce_factoryId) " +
                        "ORDER BY T.profit DESC, T.produce_factoryId ASC;";

        try {
            Statement st = connection.createStatement();
            rs = st.executeQuery(query);

            while (rs.next()) {

                int factoryId = rs.getInt("produce_factoryId");
                int productId = rs.getInt("productId");
                String productName = rs.getString("productName");
                String productType = rs.getString("productType");
                double profit = rs.getDouble("profit");

                QueryResult.MostValueableProduct obj = new QueryResult.MostValueableProduct(factoryId, productId, productName, productType, profit);
                reslist.add(obj);
            }

            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        QueryResult.MostValueableProduct[] resarray = new QueryResult.MostValueableProduct[reslist.size()];

        return reslist.toArray(resarray);
    }

    /**
     * For each product, return the factories that gather the highest profit
     * for that product
     *
     * @return QueryResult.MostValueableProduct[]
     */
    public QueryResult.MostValueableProduct[] getMostValueableProductsOnFactory() {
        ResultSet rs;
        ArrayList<QueryResult.MostValueableProduct> reslist = new ArrayList<QueryResult.MostValueableProduct>();

        String query = "SELECT DISTINCT T.produce_factoryId, T.produce_productId, P.productName, P.productType, T.profit " +
                       "FROM " +
                            "(SELECT DISTINCT Pr.produce_factoryId, Pr.produce_productId, S.amount*S.pricePerUnit-Pr.amount*Pr.productionCost AS profit " +
                            "FROM Produce Pr, Shipment S " +
                            "WHERE Pr.produce_factoryId = S.shipment_factoryId AND Pr.produce_productId = S.shipment_productId " +
                            "UNION " +
                            "SELECT DISTINCT Pr.produce_factoryId, Pr.produce_productId, -Pr.amount*Pr.productionCost AS profit " +
                            "FROM Produce Pr " +
                            "WHERE Pr.produce_productId NOT IN (SELECT S.shipment_productId FROM Shipment S) " +
                            "UNION " +
                            "SELECT DISTINCT Pr.produce_factoryId, Pr.produce_productId, -Pr.amount*Pr.productionCost AS profit " +
                            "FROM Produce Pr, Shipment S " +
                            "WHERE Pr.produce_productId = S.shipment_productId AND Pr.produce_factoryId != S.shipment_factoryId) T, Product P " +
                       "WHERE T.produce_productId = P.productId AND (T.produce_productId, T.profit) IN " +
                            "(SELECT DISTINCT T2.produce_productId, MAX(profit) AS profit " +
                            "FROM " +
                                "(SELECT DISTINCT Pr.produce_productId, MAX(S.amount*S.pricePerUnit-Pr.amount*Pr.productionCost) AS profit " +
                                "FROM Produce Pr, Shipment S " +
                                "WHERE Pr.produce_factoryId = S.shipment_factoryId AND Pr.produce_productId = S.shipment_productId " +
                                "GROUP BY Pr.produce_productId " +
                                "UNION " +
                                "SELECT DISTINCT Pr.produce_productId, MAX(-Pr.amount*Pr.productionCost) AS profit " +
                                "FROM Produce Pr " +
                                "WHERE Pr.produce_productId NOT IN (SELECT S.shipment_productId FROM Shipment S) " +
                                "GROUP BY Pr.produce_productId " +
                                "UNION " +
                                "SELECT DISTINCT Pr.produce_productId, MAX(-Pr.amount*Pr.productionCost) AS profit " +
                                "FROM Produce Pr, Shipment S " +
                                "WHERE Pr.produce_productId = S.shipment_productId AND Pr.produce_factoryId != S.shipment_factoryId " +
                                "GROUP BY Pr.produce_productId) T2 " +
                            "GROUP BY T2.produce_productId) " +
                       "ORDER BY T.profit DESC, T.produce_factoryId ASC;";

        try {
            Statement st = connection.createStatement();
            rs = st.executeQuery(query);

            while (rs.next()) {

                int factoryId = rs.getInt("produce_factoryId");
                int productId = rs.getInt("produce_productId");
                String productName = rs.getString("productName");
                String productType = rs.getString("productType");
                double profit = rs.getDouble("profit");

                QueryResult.MostValueableProduct obj = new QueryResult.MostValueableProduct(factoryId, productId, productName, productType, profit);
                reslist.add(obj);
            }

            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        QueryResult.MostValueableProduct[] resarray = new QueryResult.MostValueableProduct[reslist.size()];

        return reslist.toArray(resarray);
    }


    /**
     * For each department, should return all employees that are paid under the
     *     average salary for that department. You consider the employees
     *     that do not work earning ”0”.
     *
     * @return QueryResult.LowSalaryEmployees[]
     */
    public QueryResult.LowSalaryEmployees[] getLowSalaryEmployeesForDepartments() {
        ResultSet rs;
        ArrayList<QueryResult.LowSalaryEmployees> reslist = new ArrayList<QueryResult.LowSalaryEmployees>();

        String query = "SELECT DISTINCT E2.employeeId, E2.employeeName, E2.department, E2.salary " +
                       "FROM Employee E2 " +
                       "WHERE E2.salary < " +
                                        "(SELECT DISTINCT AVG(E.salary) " +
                                        "FROM Employee E " +
                                        "WHERE E.department = E2.department " +
                                        "GROUP BY E.department) " +
                       "UNION " +
                       "SELECT DISTINCT E2.employeeId, E2.employeeName, E2.department, 0 " +
                       "FROM Employee E2 " +
                       "WHERE E2.employeeId NOT IN (SELECT DISTINCT W.worksIn_employeeId FROM Works_In W) " +
                       "ORDER BY employeeId ASC;";

        try {
            Statement st = connection.createStatement();
            rs = st.executeQuery(query);

            while (rs.next()) {

                int employeeId = rs.getInt("employeeId");
                String employeeName = rs.getString("employeeName");
                String department = rs.getString("department");
                int salary = rs.getInt("salary");

                QueryResult.LowSalaryEmployees obj = new QueryResult.LowSalaryEmployees(employeeId, employeeName, department, salary);
                reslist.add(obj);
            }

            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        QueryResult.LowSalaryEmployees[] resarray = new QueryResult.LowSalaryEmployees[reslist.size()];

        return reslist.toArray(resarray);
    }


    /**
     * For the products of given productType, increase the productionCost of every unit by a given percentage.
     *
     * @return number of rows affected
     */
    public int increaseCost(String productType, double percentage) {
        try {
            PreparedStatement stmt = connection.prepareStatement("UPDATE Produce Pr " +
                                                                     "SET Pr.productionCost = Pr.productionCost * (?+100) / 100 " +
                                                                     "WHERE Pr.produce_productId IN ( " +
                                                                                                    "SELECT P.productId " +
                                                                                                    "FROM Product P " +
                                                                                                    "WHERE P.productType = ?);");
            stmt.setDouble(1, percentage);
            stmt.setString(2, productType);

            return stmt.executeUpdate();
        }
        catch (SQLException e){
            e.printStackTrace();
        }

        return 0;
    }


    /**
     * Deleting all employees that have not worked since the given date.
     *
     * @return number of rows affected
     */
    public int deleteNotWorkingEmployees(String givenDate) {
        try {
            Statement st = connection.createStatement();
            int deletedEW = st.executeUpdate("DELETE FROM Employee " +
                                                  "WHERE employeeId NOT IN ( " +
                                                                            "SELECT DISTINCT W.worksIn_employeeId " +
                                                                            "FROM Works_In W);");

            PreparedStatement stmt = connection.prepareStatement("DELETE FROM Employee " +
                                                                     "WHERE employeeId NOT IN ( " +
                                                                                          "SELECT DISTINCT W.worksIn_employeeId " +
                                                                                          "FROM Works_In W " +
                                                                                          "WHERE W.startDate > ?);");
            stmt.setString(1, givenDate);
            int deletedEW2 = stmt.executeUpdate();

            return deletedEW + deletedEW2;
        }
        catch (SQLException e){
            e.printStackTrace();
        }

        return 0;
    }


    /**
     * *****************************************************
     * *****************************************************
     * *****************************************************
     * *****************************************************
     *  THE METHODS AFTER THIS LINE WILL NOT BE GRADED.
     *  YOU DON'T HAVE TO SOLVE THEM, LEAVE THEM AS IS IF YOU WANT.
     *  IF YOU HAVE ANY QUESTIONS, REACH ME VIA EMAIL.
     * *****************************************************
     * *****************************************************
     * *****************************************************
     * *****************************************************
     */

    /**
     * For each department, find the rank of the employees in terms of
     * salary. Peers are considered tied and receive the same rank. After
     * that, there should be a gap.
     *
     * @return QueryResult.EmployeeRank[]
     */
    public QueryResult.EmployeeRank[] calculateRank() {
        return new QueryResult.EmployeeRank[0];
    }

    /**
     * For each department, find the rank of the employees in terms of
     * salary. Everything is the same but after ties, there should be no
     * gap.
     *
     * @return QueryResult.EmployeeRank[]
     */
    public QueryResult.EmployeeRank[] calculateRank2() {
        return new QueryResult.EmployeeRank[0];
    }

    /**
     * For each factory, calculate the most profitable 4th product.
     *
     * @return QueryResult.FactoryProfit
     */
    public QueryResult.FactoryProfit calculateFourth() {
        return new QueryResult.FactoryProfit(0,0,0);
    }

    /**
     * Determine the salary variance between an employee and another
     * one who began working immediately after the first employee (by
     * startDate), for all employees.
     *
     * @return QueryResult.SalaryVariant[]
     */
    public QueryResult.SalaryVariant[] calculateVariance() {
        return new QueryResult.SalaryVariant[0];
    }

    /**
     * Create a method that is called once and whenever a Product starts
     * losing money, deletes it from Produce table
     *
     * @return void
     */
    public void deleteLosing() {

    }
}
