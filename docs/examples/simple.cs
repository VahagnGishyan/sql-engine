using System;
using System.Data;
using System.Data.SqlClient;

class Program
{
    static void Main()
    {
        // Database connection parameters
        string connectionString = "Server=localhost;Database=MyDB;Trusted_Connection=True;";
        
        using (SqlConnection connection = new SqlConnection(connectionString))
        {
            connection.Open();

            // Create a table
            using (SqlCommand cmd = new SqlCommand("CREATE TABLE IF NOT EXISTS Users (Id INT PRIMARY KEY, Name NVARCHAR(50))", connection))
            {
                cmd.ExecuteNonQuery();
            }

            // Insert data
            using (SqlCommand cmd = new SqlCommand("INSERT INTO Users (Id, Name) VALUES (@Id, @Name)", connection))
            {
                cmd.Parameters.Add(new SqlParameter("@Id", SqlDbType.Int) { Value = 1 });
                cmd.Parameters.Add(new SqlParameter("@Name", SqlDbType.NVarChar, 50) { Value = "John Doe" });

                cmd.ExecuteNonQuery();
            }

            Console.WriteLine("Data inserted successfully.");
        }
    }
}
