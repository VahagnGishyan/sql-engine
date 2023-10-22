import sqlite3

# Create or connect to a SQLite database (a file named "mydb.db")
conn = sqlite3.connect("mydb.db")
cursor = conn.cursor()

# Create a table if it doesn't exist
cursor.execute('''
    CREATE TABLE IF NOT EXISTS users (
        id INTEGER PRIMARY KEY,
        name TEXT,
        age INTEGER
    )
''')

# Insert data into the table
cursor.execute("INSERT INTO users (name, age) VALUES (?, ?)", ("John Doe", 30))
cursor.execute("INSERT INTO users (name, age) VALUES (?, ?)",
               ("Jane Smith", 25))
conn.commit()  # Save the changes

# Retrieve data from the table
cursor.execute("SELECT * FROM users")
rows = cursor.fetchall()

# Display the retrieved data
for row in rows:
    print(f"ID: {row[0]}, Name: {row[1]}, Age: {row[2]}")

# Close the connection
conn.close()
