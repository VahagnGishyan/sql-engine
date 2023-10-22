import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.Statement;

public class FirstDatabaseExample {
    public static void main(String[] args) {
        // Database connection parameters
        String url = "jdbc:mysql://localhost:3306/mydb"; // Replace with your database URL
        String user = "your_username";
        String password = "your_password";

        try {
            // Connect to the database
            Connection connection = DriverManager.getConnection(url, user, password);

            // Create a table
            Statement statement = connection.createStatement();
            String createTableSQL = "CREATE TABLE IF NOT EXISTS users (id INT AUTO_INCREMENT, name VARCHAR(255), PRIMARY KEY (id))";
            statement.execute(createTableSQL);

            // Insert data
            String insertSQL = "INSERT INTO users (name) VALUES (?)";
            PreparedStatement preparedStatement = connection.prepareStatement(insertSQL);
            preparedStatement.setString(1, "John Doe");
            preparedStatement.execute();

            // Close the resources
            preparedStatement.close();
            statement.close();
            connection.close();

            System.out.println("Data inserted successfully.");

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
