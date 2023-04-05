/*
Author - Shantanu Wable

Consider telephone book database of N clients. Make use of a hash table
implementation to quickly look up client‘s telephone number. Make use of two collision
handling techniques and compare them using number of comparisons required to find a
set of telephone numbers
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Client {

    char name[20];
    ll phone;

public:

    Client() { 
        strcpy( name , "----" ) ;
        phone = 0 ;
    }

    void printDetails() {
		cout.width( 20 ) ;
		cout << name << " " ;
		cout.width( 20 ) ;
		cout << phone << "\n" ;
	}

    Client( char n[] , ll telephone ) {
        strcpy( name , n ) ;
        phone = telephone ;
    }

    bool isEmpty(){
        return phone == 0;
    }

    friend class Hashtable;
};

class Hashtable
{
    int tableSize;
    Client* clients;

    int hashfunction( char clientName[] )
    {   
        int n = sizeof(clientName)/sizeof(clientName[0]);
        int sum=0;
        for(int i=0;i<n;i++)
            sum+=i;
        return sum%n;
    }

    bool isOriginal( int index ) {
        return hashfunction( clients[index].name ) == index;
    }

public:

    Hashtable(int tableSize) {
        this->tableSize = tableSize;
        clients = new Client[ tableSize ];
    }

    void createTable() {
        for(int i=0; i<tableSize; i++) 
            clients[i] = Client();
    }

    void insertClient_woReplacement( Client newClient ) {
        int index = hashfunction( newClient.name );
        if( clients[index].isEmpty() ) {
            clients[index] = newClient;
        }

        else {
            int currentIndex = index;
            while( !clients[currentIndex].isEmpty() ) {
                currentIndex = (currentIndex + 1) % tableSize;
            }
            clients[currentIndex] = newClient;
        }
    }

    void insertClient_wReplacement( Client newClient ) {
        int index = hashfunction( newClient.name );
        if( clients[index].isEmpty() ) {
            clients[index] = newClient;
        }

        else {
            if( isOriginal(index) ) {
                int currentIndex = index;
                while( !clients[currentIndex].isEmpty() ) {
                    currentIndex = (currentIndex + 1) % tableSize;
                }
                clients[currentIndex] = newClient;
            }

            else {
                Client existingClient = clients[index];
                clients[index] = newClient;
                int currentIndex = index;
                while( !clients[currentIndex].isEmpty() ) {
                    currentIndex = (currentIndex + 1) % tableSize;
                }
                clients[currentIndex] = existingClient;
            }
        }
    }

    void search( char clientName[] ) {
        int index = hashfunction( clientName );
        if( strcmp( clientName, clients[index].name ) == 0) {
            cout<<"Client exists"<<endl;
        }

        else {

            int currentIndex = index;
            int passes = 0;
            while( strcmp( clients[currentIndex].name, clientName ) != 0 and passes != tableSize ) {
                currentIndex = (currentIndex + 1) % tableSize;
                passes++;
            }

            if( passes != tableSize ) {
                // clients[index].printDetails();
                cout<<"Client exists"<<endl;
            }

            else {
                cout<<"No such client found"<<endl;
            }
        }
    }

    void displayHT() {
        cout.width( 10 ) ;
		cout << "Client Name  " ;
		cout.width( 10 ) ;
		cout << "Telephone  \n";
		for( int i = 0 ; i < (this->tableSize) ; i++ ) {
			clients[ i ].printDetails() ;
		}
    }
};


int main()
{
    // int n;
    // cout << "Enter number of clients: ";
    // cin >> n;
    Hashtable table(10);
    table.createTable();
    // for(int i = 0; i<n; i++) {
    //     cout << "Enter client name: ";
    //     char name[20];
    //     cin >> name;
    //     cout << "Enter client phone: ";
    //     ll phone;
    //     cin >> phone;
    //     Client newClient( name, phone );
    //     table.insertClient_woReplacement(newClient);
    // }

    // table.insertClient_woReplacement(Client("Damiano", 8979926863));
    // table.insertClient_woReplacement(Client("Muirne", 8637920981));
    // table.insertClient_woReplacement(Client("Kristen", 5822301507));
    // table.insertClient_woReplacement(Client("Leto", 8427943825));
    // table.insertClient_woReplacement(Client("Anita", 5189486425));
    // table.insertClient_woReplacement(Client("Pacífica", 9223409937));
    // table.insertClient_woReplacement(Client("Emma", 5869973957));
    // table.insertClient_woReplacement(Client("Bellamy", 7911222765));
    // table.insertClient_woReplacement(Client("Ríoghnach", 9576492062));
    // table.insertClient_woReplacement(Client("Mathis", 7892997404));

    // table.displayHT();

	// table.search( "Damiano" ) ;
	// table.search( "zdfg" ) ;
	// table.search( "asdf" ) ;
	// table.search( "Muirne" ) ;
	// table.search( "qwer" ) ;
	// table.search( "Emma" ) ;
	// table.search( "ergh" ) ;
	// table.search( "Mathis" ) ;
	// table.search( "zasd" ) ;
	// table.search( "Anita" ) ;

    table.insertClient_woReplacement( Client( "abcd" , 10002 ) ) ;
	table.insertClient_woReplacement( Client( "zdfg" , 10003 ) ) ;
	table.insertClient_woReplacement( Client( "asdf" , 10004 ) ) ;
	table.insertClient_woReplacement( Client( "dbca" , 10005 ) ) ;
	table.insertClient_woReplacement( Client( "qwer" , 10006 ) ) ;
	table.insertClient_woReplacement( Client( "rtyu" , 10006 ) ) ;
	table.insertClient_woReplacement( Client( "ergh" , 10006 ) ) ;
	table.insertClient_woReplacement( Client( "fghj" , 10006 ) ) ;
	table.insertClient_woReplacement( Client( "zasd" , 10006 ) ) ;
	table.insertClient_woReplacement( Client( "dfgh" , 10006 ) ) ;
	table.displayHT() ;
	table.search( "abcd" ) ;
	table.search( "zdfg" ) ;
	table.search( "asdf" ) ;
	table.search( "dbca" ) ;
	table.search( "qwer" ) ;
	table.search( "rtyu" ) ;
	table.search( "ergh" ) ;
	table.search( "fghj" ) ;
	table.search( "zasd" ) ;
	table.search( "dfgh" ) ;

    Hashtable table1(10);

    table1.insertClient_wReplacement( Client( "abcd" , 10002 ) ) ;
	table1.insertClient_wReplacement( Client( "zdfg" , 10003 ) ) ;
	table1.insertClient_wReplacement( Client( "asdf" , 10004 ) ) ;
	table1.insertClient_wReplacement( Client( "dbca" , 10005 ) ) ;
	table1.insertClient_wReplacement( Client( "qwer" , 10006 ) ) ;
	table1.insertClient_wReplacement( Client( "rtyu" , 10006 ) ) ;
	table1.insertClient_wReplacement( Client( "ergh" , 10006 ) ) ;
	table1.insertClient_wReplacement( Client( "fghj" , 10006 ) ) ;
	table1.insertClient_wReplacement( Client( "zasd" , 10006 ) ) ;
	table1.insertClient_wReplacement( Client( "dfgh" , 10006 ) ) ;
	table1.displayHT() ;
	table1.search( "abcd" ) ;
	table1.search( "zdfg" ) ;
	table1.search( "asdf" ) ;
	table1.search( "dbca" ) ;
	table1.search( "qwer" ) ;
	table1.search( "rtyu" ) ;
	table1.search( "ergh" ) ;
	table1.search( "fghj" ) ;
	table1.search( "zasd" ) ;
	table1.search( "dfgh" ) ;

    return 0;
}
