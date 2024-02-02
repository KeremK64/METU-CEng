package ceng.ceng351.cengfactorydb;

import java.net.NetworkInterface;
import java.sql.*;
import java.util.ArrayList;

import com.mysql.cj.protocol.Resultset;

public class CENGFACTORYDB implements ICENGFACTORYDB {
    private static String user = "e2644417";
    private static String password = "IC0UWTikP^Ka";
    private static String host = "144.122.71.128";
    private static String database = "db2644417";
    private static int port = 8080;

    private static Connection connection = null;

    public void initialize() {
        String url = "jdbc:mysql://" + host + ":" + port + "/" + database + "?useSSL=false";

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(url, user, password);
        } catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        }

    }

    /**
     * Should create the necessary tables when called.
     *
     * @return the number of tables that are created successfully.
     */
    public int createTables() {
        int count = 0;

        String createFactory = "CREATE TABLE IF NOT EXISTS Factory ("
                + "factoryId INT NOT NULL,"
                + "factoryName VARCHAR(45),"
                + "factoryType VARCHAR(30),"
                + "country VARCHAR(20),"
                + "PRIMARY KEY (factoryId))";

        String createEmployee = "CREATE TABLE IF NOT EXISTS Employee ("
                + "employeeId INT NOT NULL,"
                + "employeeName VARCHAR(30),"
                + "department VARCHAR(20),"
                + "salary INT,"
                + "PRIMARY KEY (employeeId))";

        String createWorksIn = "CREATE TABLE IF NOT EXISTS WorksIn ("
                + "factoryId INT NOT NULL,"
                + "employeeId INT NOT NULL,"
                + "startDate VARCHAR(20),"
                + "PRIMARY KEY (factoryId, employeeId),"
                + "FOREIGN KEY (factoryId) REFERENCES Factory(factoryId),"
                + "FOREIGN KEY (employeeId) REFERENCES Employee(employeeId) ON DELETE CASCADE)";

        String createProduct = "CREATE TABLE IF NOT EXISTS Product ("
                + "productId INT NOT NULL,"
                + "productName VARCHAR(50),"
                + "productType VARCHAR(50),"
                + "PRIMARY KEY (productId))";

        String createProduce = "CREATE TABLE IF NOT EXISTS Produce ("
                + "factoryId INT NOT NULL,"
                + "productId INT NOT NULL,"
                + "amount INT,"
                + "productionCost INT,"
                + "PRIMARY KEY (factoryId, productId),"
                + "FOREIGN KEY (factoryId) REFERENCES Factory(factoryId),"
                + "FOREIGN KEY (productId) REFERENCES Product(productId))";

        String createShipment = "CREATE TABLE IF NOT EXISTS Shipment ("
                + "factoryId INT NOT NULL,"
                + "productId INT NOT NULL,"
                + "amount INT,"
                + "pricePerUnit INT,"
                + "PRIMARY KEY (factoryId, productId),"
                + "FOREIGN KEY (factoryId) REFERENCES Factory(factoryId),"
                + "FOREIGN KEY (productId) REFERENCES Product(productId))";

        try {
            Statement statement = connection.createStatement();

            statement.executeUpdate(createFactory);
            count++;

            statement.executeUpdate(createEmployee);
            count++;

            statement.executeUpdate(createWorksIn);
            count++;

            statement.executeUpdate(createProduct);
            count++;

            statement.executeUpdate(createProduce);
            count++;

            statement.executeUpdate(createShipment);
            count++;

            statement.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return count;
    }

    /**
     * Should drop the tables if exists when called.
     *
     * @return the number of tables are dropped successfully.
     */

    public int dropTables() {
        int count = 0;

        String dropFactory = "DROP TABLE IF EXISTS Factory";
        String dropEmployee = "DROP TABLE IF EXISTS Employee";
        String dropWorksIn = "DROP TABLE IF EXISTS WorksIn";
        String dropProduct = "DROP TABLE IF EXISTS Product";
        String dropProduce = "DROP TABLE IF EXISTS Produce";
        String dropShipment = "DROP TABLE IF EXISTS Shipment";

        try {
            Statement statement = connection.createStatement();

            statement.executeUpdate(dropShipment);
            count++;

            statement.executeUpdate(dropProduce);
            count++;

            statement.executeUpdate(dropProduct);
            count++;

            statement.executeUpdate(dropWorksIn);
            count++;

            statement.executeUpdate(dropEmployee);
            count++;

            statement.executeUpdate(dropFactory);
            count++;

            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return count;
    }

    /**
     * Should insert an array of Factory into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertFactory(Factory[] factories) {
        int num = 0;

        for (int i = 0; i < factories.length; i++) {
            try {
                Factory fact = factories[i];

                PreparedStatement statement = connection.prepareStatement(
                        "INSERT INTO Factory (factoryId, factoryName, factoryType, country) VALUES(?,?,?,?)");
                statement.setInt(1, fact.getFactoryId());
                statement.setString(2, fact.getFactoryName());
                statement.setString(3, fact.getFactoryType());
                statement.setString(4, fact.getCountry());
                statement.executeUpdate();

                num++;
                statement.close();

            } catch (SQLException e) {
                e.printStackTrace();
            }

        }
        return num;
    }

    /**
     * Should insert an array of Employee into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertEmployee(Employee[] employees) {

        int empInsertion = 0;

        for (int i = 0; i < employees.length; i++) {
            try {
                Employee emp = employees[i];

                PreparedStatement statement = connection.prepareStatement(
                        "INSERT INTO Employee(employeeId, employeeName, department, salary) VALUES(?,?,?,?)");
                statement.setInt(1, emp.getEmployeeId());
                statement.setString(2, emp.getEmployeeName());
                statement.setString(3, emp.getDepartment());
                statement.setInt(4, emp.getSalary());

                statement.executeUpdate();

                empInsertion++;
                statement.close();

            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return empInsertion;

    }

    /**
     * Should insert an array of WorksIn into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertWorksIn(WorksIn[] worksIns) {
        int workInsertion = 0;

        for (int i = 0; i < worksIns.length; i++) {
            try {
                WorksIn work = worksIns[i];

                PreparedStatement statement = connection.prepareStatement("INSERT INTO WorksIn VALUES(?,?,?)");
                statement.setInt(1, work.getFactoryId());
                statement.setInt(2, work.getEmployeeId());
                statement.setString(3, work.getStartDate());

                statement.executeUpdate();

                workInsertion++;
                statement.close();

            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return workInsertion;
    }

    /**
     * Should insert an array of Product into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertProduct(Product[] products) {
        int prodInsertion = 0;

        for (int i = 0; i < products.length; i++) {
            try {
                Product prod = products[i];

                PreparedStatement statement = connection.prepareStatement("INSERT INTO Product VALUES(?,?,?)");
                statement.setInt(1, prod.getProductId());
                statement.setString(2, prod.getProductName());
                statement.setString(3, prod.getProductType());

                statement.executeUpdate();

                prodInsertion++;
                statement.close();

            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return prodInsertion;
    }

    /**
     * Should insert an array of Produce into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertProduce(Produce[] produces) {
        int produceInsertion = 0;
        for (int i = 0; i < produces.length; i++) {
            try {
                Produce produce = produces[i];

                PreparedStatement statement = connection.prepareStatement("INSERT INTO Produce VALUES(?,?,?,?)");
                statement.setInt(1, produce.getFactoryId());
                statement.setInt(2, produce.getProductId());
                statement.setInt(3, produce.getAmount());
                statement.setInt(4, produce.getProductionCost());

                statement.executeUpdate();

                produceInsertion++;
                statement.close();

            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return produceInsertion;
    }

    /**
     * Should insert an array of Shipment into the database.
     *
     * @return Number of rows inserted successfully.
     */
    public int insertShipment(Shipment[] shipments) {
        int shipInsertion = 0;
        for (int i = 0; i < shipments.length; i++) {
            try {
                Shipment shipment = shipments[i];

                PreparedStatement statement = connection.prepareStatement("INSERT INTO Shipment VALUES(?,?,?,?)");
                statement.setInt(1, shipment.getFactoryId());
                statement.setInt(2, shipment.getProductId());
                statement.setInt(3, shipment.getAmount());
                statement.setInt(4, shipment.getPricePerUnit());
                statement.executeUpdate();

                shipInsertion++;
                statement.close();

            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        return shipInsertion;
    }

    /**
     * Should return all factories that are located in a particular country.
     *
     * @return Factory[]
     */
    public Factory[] getFactoriesForGivenCountry(String country) {
        String actualQuery = "SELECT * FROM Factory WHERE country = ? ORDER BY factoryId;";
        String queryForSize = "SELECT COUNT(*) FROM Factory WHERE country = ?;";

        ResultSet actualSet;
        ResultSet sizeSet;

        try {
            PreparedStatement actual = connection.prepareStatement(actualQuery);
            actual.setString(1, country);

            PreparedStatement size = connection.prepareStatement(queryForSize);
            size.setString(1, country);

            sizeSet = size.executeQuery();
            sizeSet.next();

            int sizeOf = sizeSet.getInt(1);

            Factory[] result = new Factory[sizeOf];

            actualSet = actual.executeQuery();

            int i = 0;
            while (actualSet.next()) {
                result[i] = new Factory(actualSet.getInt(1), actualSet.getString(2), actualSet.getString(3),
                        actualSet.getString(4));
                i++;
            }

            return result;

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return new Factory[0];
    }

    /**
     * Should return all factories without any working employees.
     *
     * @return Factory[]
     */
    public Factory[] getFactoriesWithoutAnyEmployee() {
        String actualQuery = "SELECT * FROM Factory F WHERE F.factoryId NOT IN(SELECT W.factoryId FROM WorksIn W) ORDER BY F.factoryId;";
        String queryForSize = "SELECT COUNT(*) FROM Factory F WHERE F.factoryId NOT IN(SELECT W.factoryId FROM WorksIn W);";

        ResultSet actualSet;
        ResultSet sizeSet;

        try {
            PreparedStatement actual = connection.prepareStatement(actualQuery);
            actualSet = actual.executeQuery();

            PreparedStatement size = connection.prepareStatement(queryForSize);
            sizeSet = size.executeQuery();

            sizeSet.next();

            int sizeOf = sizeSet.getInt(1);

            Factory[] result = new Factory[sizeOf];

            int i = 0;
            while (actualSet.next()) {
                result[i] = new Factory(actualSet.getInt(1), actualSet.getString(2), actualSet.getString(3),
                        actualSet.getString(4));
                i++;
            }

            actual.close();
            size.close();

            return result;

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return new Factory[0];
    }

    /**
     * Should return all factories that produce all products for a particular
     * productType
     *
     * @return Factory[]
     */
    public Factory[] getFactoriesProducingAllForGivenType(String productType) {
        String query = "SELECT * FROM Factory F WHERE NOT EXISTS (SELECT P1.productId FROM Product P1 WHERE P1.productType = ? AND NOT EXISTS (SELECT P2.productId FROM Produce P2 WHERE F.factoryId = P2.factoryId AND P1.productId = P2.productId)) ORDER BY factoryId ASC;";

        ResultSet set;
        ArrayList<Factory> arr = new ArrayList<>();
        try {
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setString(1, productType);
            set = statement.executeQuery();

            while (set.next()) {
                arr.add(new Factory(set.getInt(1), set.getString(2), set.getString(3), set.getString(4)));
            }
            statement.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }

        Factory[] resultArr = new Factory[arr.size()];

        return arr.toArray(resultArr);
    }

    /**
     * Should return the products that are produced in a particular factory but
     * don’t have any shipment from that factory.
     *
     * @return Product[]
     */
    public Product[] getProductsProducedNotShipped() {
        String query = "SELECT DISTINCT P.productId, P.productName, P.productType FROM Product P, Produce P1 " +
                "WHERE P.productId = P1.productId AND (P1.factoryId, P1.productId) NOT IN(SELECT factoryId, productId FROM Shipment) ORDER BY productId ASC;";

        ResultSet set;
        ArrayList<Product> result = new ArrayList<>();

        try {
            PreparedStatement statement = connection.prepareStatement(query);
            set = statement.executeQuery();
            while (set.next()) {
                result.add(new Product(set.getInt(1), set.getString(2), set.getString(3)));
            }

            statement.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }
        Product[] resultArray = new Product[result.size()];
        return result.toArray(resultArray);
    }

    /**
     * For a given factoryId and department, should return the average salary of
     * the employees working in that factory and that specific department.
     *
     * @return double
     */
    public double getAverageSalaryForFactoryDepartment(int factoryId, String department) {
        String query = "SELECT AVG(E.salary) FROM WorksIn W, Employee E WHERE E.employeeId = W.employeeId AND E.department = ? AND W.factoryId = ?;";

        ResultSet querySet;

        try {
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setString(1, department);
            statement.setInt(2, factoryId);

            querySet = statement.executeQuery();

            querySet.next();

            int result = querySet.getInt(1);

            return result;

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return 0.0;
    }

    /**
     * Should return the most profitable products for each factory
     *
     * @return QueryResult.MostValueableProduct[]
     */
    public QueryResult.MostValueableProduct[] getMostValueableProducts() {
        ResultSet set;
        ArrayList<QueryResult.MostValueableProduct> arr = new ArrayList<>();

        String query = "SELECT temp.factoryId, temp.productId, temp.productName, temp.productType, MAX(temp.profit) "
                +
                "FROM (SELECT p.factoryId, p.productId, p1.productName, p1.productType, (s.amount * s.pricePerUnit) - (p.amount * p.productionCost) AS profit "
                +
                "FROM Product p1, Produce p, Shipment s, Factory f " +
                "WHERE s.factoryId = p.factoryId AND s.productId = p.productId AND p1.productId = p.productId AND f.factoryId = p.factoryId AND "
                +
                "(s.amount * s.pricePerUnit) - (p.amount * p.productionCost) >= (SELECT MAX(s1.amount * s1.pricePerUnit - p1.amount * p1.productionCost) FROM Produce p1, Shipment s1 WHERE s1.factoryId = p1.factoryId AND s1.productId = p1.productId AND f.factoryId = p1.factoryId) "
                +
                "UNION " +
                "SELECT p.factoryId, p.productId, p1.productName, p1.productType,  (-1) * (p.amount * p.productionCost) AS profit "
                +
                "FROM Produce p, Product p1 " +
                "WHERE p.productId NOT IN (SELECT s.productId FROM Shipment s WHERE s.factoryId = p.factoryId AND s.productId = p.productId) AND p1.productId = p.productId "
                +
                "AND ((-1) * (p.amount * p.productionCost)) >= (SELECT MAX((-1) * p5.amount * " +
                "p5.productionCost) FROM Produce p5 WHERE p5.productId NOT IN (SELECT " +
                "s.productId FROM Shipment s WHERE s.factoryId = p5.factoryId AND s.productId = p5.productId) AND p5.factoryId = p.factoryId ) "
                +
                "ORDER BY profit DESC, factoryId ASC "
                +
                ") AS temp "
                +
                "GROUP BY temp.factoryId "
                +
                "ORDER BY temp.profit DESC, temp.factoryId ASC;";

        try {
            PreparedStatement statement = connection.prepareStatement(query);
            set = statement.executeQuery();

            while (set.next()) {
                arr.add(new QueryResult.MostValueableProduct(set.getInt(1), set.getInt(2), set.getString(3),
                        set.getString(4), set.getInt(5)));

            }

            statement.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }
        QueryResult.MostValueableProduct[] res = new QueryResult.MostValueableProduct[arr.size()];

        return arr.toArray(res);
    }

    /**
     * For each product, return the factories that gather the highest profit
     * for that product
     *
     * @return QueryResult.MostValueableProduct[]
     */
    public QueryResult.MostValueableProduct[] getMostValueableProductsOnFactory() {
        ResultSet set;
        ArrayList<QueryResult.MostValueableProduct> arr = new ArrayList<>();

        String query = "SELECT p.factoryId, p.productId, p1.productName, p1.productType, (s.amount * s.pricePerUnit) - (p.amount * p.productionCost) AS profit "
                +
                "FROM Product p1, Produce p, Shipment s " +
                "WHERE s.factoryId = p.factoryId AND s.productId = p.productId AND p1.productId = p.productId AND " +
                "(s.amount * s.pricePerUnit) - (p.amount * p.productionCost) >= (SELECT MAX(s1.amount * s1.pricePerUnit - p1.amount * p1.productionCost) FROM Produce p1, Shipment s1 WHERE s1.factoryId = p1.factoryId AND s1.productId = p1.productId AND p1.productId = p.productId) "
                +
                "UNION " +
                "SELECT p.factoryId, p.productId, p1.productName, p1.productType,  (-1) * (p.amount * p.productionCost) AS profit "
                +
                "FROM Produce p, Product p1 " +
                "WHERE p.productId NOT IN (SELECT s.productId FROM Shipment s) AND p.productId = p1.productId "
                +
                "AND ((-1) * (p.amount * p.productionCost)) >= (SELECT MAX((-1) * p.amount * " +
                "p.productionCost) FROM Produce p WHERE p.productId NOT IN (SELECT " +
                "s.productId FROM Shipment s) AND p.productId = p1.productId) "
                +
                "ORDER BY profit DESC, productId ASC;";

        try {
            PreparedStatement statement = connection.prepareStatement(query);
            set = statement.executeQuery();

            while (set.next()) {
                arr.add(new QueryResult.MostValueableProduct(set.getInt(1), set.getInt(2), set.getString(3),
                        set.getString(4), set.getInt(5)));

            }

            statement.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }
        QueryResult.MostValueableProduct[] res = new QueryResult.MostValueableProduct[arr.size()];

        return arr.toArray(res);
    }

    /**
     * For each department, should return all employees that are paid under the
     * average salary for that department. You consider the employees
     * that do not work earning ”0”.
     *
     * @return QueryResult.LowSalaryEmployees[]
     */
    public QueryResult.LowSalaryEmployees[] getLowSalaryEmployeesForDepartments() {
        String query = "SELECT * FROM Employee E WHERE E.salary < (SELECT AVG(E1.salary) FROM Employee E1 WHERE E.department = E1.department) \n"
                +
                "UNION \n" +
                "SELECT E2.employeeId, E2.employeeName, E2.department, 0 AS salary FROM Employee E2 WHERE E2.employeeId NOT IN (SELECT W.employeeId FROM WorksIn W) ORDER BY employeeId ASC";

        ResultSet set;
        ArrayList<QueryResult.LowSalaryEmployees> arr = new ArrayList<>();

        try {
            PreparedStatement statement = connection.prepareStatement(query);
            set = statement.executeQuery();

            while (set.next()) {
                arr.add(new QueryResult.LowSalaryEmployees(set.getInt(1), set.getString(2), set.getString(3),
                        set.getInt(4)));

            }

            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        QueryResult.LowSalaryEmployees[] res = new QueryResult.LowSalaryEmployees[arr.size()];

        return arr.toArray(res);
    }

    /**
     * For the products of given productType, increase the productionCost of every
     * unit by a given percentage.
     *
     * @return number of rows affected
     */
    public int increaseCost(String productType, double percentage) {
        String updateQuery = "UPDATE Produce P1, Product P2 SET P1.productionCost = (1 + ?) * P1.productionCost " +
                "WHERE P1.productId = P2.productId AND P2.productType = ?;";
        int res = 0;

        try {
            PreparedStatement statement = connection.prepareStatement(updateQuery);
            statement.setString(2, productType);
            statement.setDouble(1, percentage);
            res = statement.executeUpdate();

            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return res;
    }

    /**
     * Deleting all employees that have not worked since the given date.
     *
     * @return number of rows affected
     */
    public int deleteNotWorkingEmployees(String givenDate) {
        String deleteQuery = "DELETE FROM Employee WHERE employeeId NOT IN (SELECT W.employeeId FROM WorksIn W WHERE W.startDate > ?)";
        String deleteQuery2 = "DELETE FROM Employee WHERE employeeId NOT IN (SELECT W.employeeId FROM WorksIn W);";

        int willReturn = 0;
        int second = 0;

        try {
            PreparedStatement statement = connection.prepareStatement(deleteQuery);
            statement.setString(1, givenDate);

            PreparedStatement statement2 = connection.prepareStatement(deleteQuery2);

            willReturn = statement.executeUpdate();

            second = statement2.executeUpdate();

            statement.close();
            statement2.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return willReturn + second;
    }

    /**
     * *****************************************************
     * *****************************************************
     * *****************************************************
     * *****************************************************
     * THE METHODS AFTER THIS LINE WILL NOT BE GRADED.
     * YOU DON'T HAVE TO SOLVE THEM, LEAVE THEM AS IS IF YOU WANT.
     * IF YOU HAVE ANY QUESTIONS, REACH ME VIA EMAIL.
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
        return new QueryResult.FactoryProfit(0, 0, 0);
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
