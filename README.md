<h1>Report: Inventory Management System</h1>

<h2>Purpose</h2>
<p>The purpose of the code is to create a simple inventory management system with user authentication, product management, and sales tracking. It allows users to add, view, update, delete, and search for products in an inventory. Additionally, it tracks sales, updates stock levels, and supports restocking products that are low in quantity. The system ensures secure user authentication and stores data persistently using text files.</p>

<h2>Importance</h2>
<p>This inventory management system is important for businesses or small enterprises to efficiently manage product inventories. It helps track stock levels, monitor sales, and ensure products are always available. The code provides an organized way to handle inventory data and automate tasks like updating stock, restocking, and recording sales, thus improving business operations and decision-making. The use of file handling ensures that data is saved and can be accessed even after program termination, making the system more reliable and practical.</p>

<h2>Features</h2>
<ul>
    <li><strong>User Authentication:</strong>
        <ul>
            <li>Sign Up: Allows new users to register by providing a username and password.</li>
            <li>Sign In: Validates existing users and ensures secure access to inventory data.</li>
        </ul>
    </li>
    <li><strong>Product Management:</strong>
        <ul>
            <li>Add Products: Enables adding new products to the inventory.</li>
            <li>Update Products: Allows modification of product details such as name, price, and quantity.</li>
            <li>Delete Products: Removes products from the inventory.</li>
        </ul>
    </li>
    <li><strong>Inventory Operations:</strong>
        <ul>
            <li>Search Products: Retrieves product details by ID.</li>
            <li>Sort Products: Organizes inventory based on price, quantity, or name.</li>
            <li>Sold Products: Tracks and updates the quantity of sold products.</li>
        </ul>
    </li>
    <li><strong>Data Persistence:</strong>
        <ul>
            <li>Inventory data is stored in text files specific to each user.</li>
            <li>Ensures data is saved across program sessions.</li>
        </ul>
    </li>
    <li><strong>Interactive Console UI:</strong>
        <ul>
            <li>Colored text output for better user experience.</li>
            <li>Clear menu-driven navigation.</li>
        </ul>
    </li>
    <li><strong>File Handling:</strong>
        <ul>
            <li>Ensuring data integrity during simultaneous read and write operations.</li>
            <li>Handling cases where files do not exist or are inaccessible.</li>
        </ul>
    </li>
    <li><strong>Error Handling:</strong>
        <ul>
            <li>Validating user input to prevent crashes caused by invalid data.</li>
            <li>Managing edge cases, such as attempting to delete a product that does not exist.</li>
        </ul>
    </li>
    <li><strong>Sorting Algorithms:</strong>
        <ul>
            <li>Implementing sorting based on multiple criteria while maintaining code simplicity.</li>
        </ul>
    </li>
    <li><strong>User Authentication:</strong>
        <ul>
            <li>Protecting user credentials and ensuring secure login processes.</li>
        </ul>
    </li>
</ul>

<h2>Function Descriptions</h2>
<ol>
    <li><strong>fileExists()</strong>
        <ul>
            <li>Checks if a specified file exists.</li>
            <li>Prototype: <code>int fileExists();</code></li>
            <li>Parameters: filename: File name to check</li>
            <li>Return Value: 1 if file exists, 0 otherwise</li>
        </ul>
    </li>
    <li><strong>createFile()</strong>
        <ul>
            <li>Creates a new file with the specified name.</li>
            <li>Prototype: <code>void createFile(char *name);</code></li>
            <li>Parameters: name: File name to create</li>
            <li>Return Value: None</li>
        </ul>
    </li>
    <li><strong>sign_in()</strong>
        <ul>
            <li>Handles user sign-in by verifying credentials and preparing the user's inventory file.</li>
            <li>Prototype: <code>int sign_in(struct Users user[], int *user_count);</code></li>
            <li>Parameters: user[]: Array of users, user_count: Pointer to user count</li>
            <li>Return Value: 1 if sign-in successful, 0 otherwise</li>
        </ul>
    </li>
    <li><strong>sign_up()</strong>
        <ul>
            <li>Allows a new user to register and sign in.</li>
            <li>Prototype: <code>void sign_up(struct Users user[], int *user_count);</code></li>
            <li>Parameters: user[]: Array of users, user_count: Pointer to user count</li>
            <li>Return Value: None</li>
        </ul>
    </li>
    <li><strong>write_product()</strong>
        <ul>
            <li>Adds a new product to the inventory, ensuring unique IDs.</li>
            <li>Prototype: <code>void write_product();</code></li>
            <li>Parameters: None</li>
            <li>Return Value: None</li>
        </ul>
    </li>
    <li><strong>read_products()</strong>
        <ul>
            <li>Reads and displays products from the user's inventory file.</li>
            <li>Prototype: <code>void read_products();</code></li>
            <li>Parameters: None</li>
            <li>Return Value: None</li>
        </ul>
    </li>
    <li><strong>del_product()</strong>
        <ul>
            <li>Deletes a product from the inventory based on its ID.</li>
            <li>Prototype: <code>void del_product();</code></li>
            <li>Parameters: None</li>
            <li>Return Value: None</li>
        </ul>
    </li>
    <li><strong>update_product()</strong>
        <ul>
            <li>Updates product details based on its ID.</li>
            <li>Prototype: <code>void update_product();</code></li>
            <li>Parameters: None</li>
            <li>Return Value: None</li>
        </ul>
    </li>
    <li><strong>search_product()</strong>
        <ul>
            <li>Searches for a product by its ID and displays details.</li>
            <li>Prototype: <code>void search_product();</code></li>
            <li>Parameters: None</li>
            <li>Return Value: None</li>
        </ul>
    </li>
    <li><strong>sort_products()</strong>
        <ul>
            <li>Sorts products based on price, quantity, or name.</li>
            <li>Prototype: <code>void sort_products();</code></li>
            <li>Parameters: None</li>
            <li>Return Value: None</li>
        </ul>
    </li>
    <li><strong>sold_products()</strong>
        <ul>
            <li>Records product sales and updates stock levels.</li>
            <li>Prototype: <code>void sold_products();</code></li>
            <li>Parameters: None</li>
            <li>Return Value: None</li>
        </ul>
    </li>
    <li><strong>restock_products()</strong>
        <ul>
            <li>Identifies and displays products that need restocking.</li>
            <li>Prototype: <code>void restock_products();</code></li>
            <li>Parameters: None</li>
            <li>Return Value: None</li>
        </ul>
    </li>
    <li><strong>main()</strong>
        <ul>
            <li>The main function that handles user interaction and drives the application flow.</li>
        </ul>
    </li>
</ol>

<h2>Data Structures</h2>
<ul>
    <li><strong>Product Structure:</strong>
        <ul>
            <li>id: Unique product identifier</li>
            <li>name: Product name</li>
            <li>price: Product price</li>
            <li>quantity: Current stock quantity</li>
            <li>items_sold: Total items sold</li>
        </ul>
    </li>
    <li><strong>User Structure:</strong>
        <ul>
            <li>username: User's username</li>
            <li>password: User's password</li>
        </ul>
    </li>
</ul>

<h2>Global Variables</h2>
<ul>
    <li>fileName: Stores the unique inventory file name for the logged-in user</li>
    <li>products: Array to store product information</li>
    <li>product_count: Tracks the number of products in the inventory</li>
</ul>
