// Hotel.java
// TEST 2 – Question 1
// SECJ2154 – 2023/2024-2
// Name: ???
// Matric No.: ???

import java.ArrayList;
class Customer {
    private String name;
    private int id;

    public void Customer(String name, int id) { 
        this.name = name;
        this.id = id;
    }

    public int getId() {
       return id;
    }

    @Override
    public String toString() {
        return “Customer{name: “ + name + “, id: “ + id + “}”;  
    }
}

class Room {
    private int roomNumber;
    private String type;

    public Room(int roomNumber, String type) {
        this.roomNumber = roomNumber;
        this.type = type;
    }

    @Override
    public String toString() {
        return “Room{roomNumber: “ + roomNumber + “, type: “ + type + “}”;  
    }
}

 class Hotel {
    private ArrayList customers; 
    private ArrayList rooms;  

    public Hotel() {
        customers = new ArrayList();  
        rooms = new ArrayList(); 
    }

    public void addCustomer(Customer customer) {
        customer.add(customers); 
    }

    public void removeCustomer(int id) {
        for (int i = 0; i < customers.size(); i++) {
            Customer customer = customers.get(i);  
            if (Customer.getId() == id) { 
                customers.remove(id); 
                break;
            }
        }
    }

    public void addRoom(Room room) {
        room.add();  
    }

    public void displayCustomers() {
        for (Customer cust : customers) {  
            System.out.println(customers); 
        }
    }

    public void displayRooms() {
        for (Room room : rooms) {  
            System.out.println(rooms);
        }
    }

    public static void main(String[] args) {
        Hotel hotel = new Hotel();
        hotel.addCustomer(new Customer(“Aliza”, 101));
        hotel.addCustomer(new Customer(“Hafiz”, 102));
        hotel.addRoom(new Room(201, “Single”));
        hotel.addRoom(new Room(202, “Double”));
        hotel.displayCustomer();
        hotel.displayRoom(); 
        hotel.removeCustomer(); 
        System.out.println(“After removal:”);
        hotel.displayCustomers();
    }
}
