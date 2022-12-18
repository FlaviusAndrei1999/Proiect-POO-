#define _CRT_SECURE_NO_WARNINGS 
//BIBLIOTECI
#include<iostream> //contine functiile cin-citim de la tastatura si cout-afisam pe ecran
#include<string> //putem sa folosim cu ajutorul acestei biblioteci string
#include<fstream> //putem sa ne folosim de clasele ofstream si ifstream, pt lucrul cu fisiere
using namespace std; //dupa biblioteci


class Ticket
{
	const int id;
	string user;
	char* event;
	bool paymentViaCreditCard;
	float price;
public:
	static int contor;

	//Constructorul fara parametrii
	Ticket() :id(contor++)
	{
		this->user = "unknown";
		this->event = new char[strlen("unknown") + 1];
		strcpy(this->event, "unknown");
		this->paymentViaCreditCard = 0;
		this->price = 0;
	}

	//Constructorul cu toti parametrii
	Ticket(string user, const char* event, bool paymentViaCard, float price) :id(contor++)
	{
		this->user = user;
		this->event = new char[strlen(event) + 1];
		strcpy(this->event, event);
		this->paymentViaCreditCard = paymentViaCreditCard;
		this->price = price;
	}
	//Destructorul
	~Ticket()
	{
		if (this->event != NULL)
		{
			delete[]this->event;
		}
	}
	//Getteri si setteri
	const int getId()
	{
		return this->id;
	}
	string getUser()
	{
		return this->user;
	}
	const char* getEvent()
	{
		return this->event;
	}

	bool getPaymentViaCard()
	{
		return this->paymentViaCreditCard;
	}
	float getPrice()
	{
		return this->price;
	}

	void setUser(string newUser)
	{
		this->user = newUser;
	}
	void setEvent(const char* newEvent)
	{
		if (this->event != NULL)
		{
			delete[]this->event;
		}
		this->event = new char[strlen(newEvent) + 1];
		strcpy(this->event, newEvent);

	}
	void setPaymentViaCard(bool newPayment)
	{
		this->paymentViaCreditCard = newPayment;
	}
	void setPrice(float newPrice)
	{
		this->price = newPrice;
	}

	//Operatorul<<
	friend ostream& operator<<(ostream& out, Ticket& t)
	{
		out << "Id: " << t.id << endl;
		out << "User: " << t.user << endl;
		out << "Event: " << t.event << endl;
		out << "Payment via card: 1-yes; 0-no: " << t.paymentViaCreditCard << endl;
		out << "Price: " << t.price << endl;
		return out;
	}
	//Constructorul de copiere
	Ticket(const Ticket& t) :id(t.id)
	{
		this->user = t.user;
		this->event = new char[strlen(t.event) + 1];
		strcpy(this->event, t.event);
		this->paymentViaCreditCard = t.paymentViaCreditCard;
		this->price = t.price;
	}

	//Operatorul=
	Ticket& operator=(const Ticket& t)
	{
		if (this->event != NULL)
		{
			delete[]this->event;
		}

		this->user = t.user;
		this->event = new char[strlen(t.event) + 1];
		strcpy(this->event, t.event);
		this->paymentViaCreditCard = t.paymentViaCreditCard;
		this->price = t.price;
		return *this;
	}

	//Operator>>
	friend istream& operator>>(istream& in, Ticket& t)
	{
		if (t.event != NULL)
		{
			delete[]t.event;
		}

		cout << "Enter from the keyboard the user: " << endl;
		in >> t.user;
		cout << "Enter from the keyboard the event: " << endl;
		char aux[50];
		in >> aux;
		t.event = new char[strlen(t.event) + 1];
		strcpy(t.event, aux);
		cout << "Enter from the keyboard if the payment for the ticket was made via credit card: " << endl;
		in >> t.paymentViaCreditCard;
		cout << "Enter from the keyboard the price: " << endl;
		in >> t.price;
		return in;

	}

	//Operatorul++ si -- pre si postincrementare/decrementare  pe price
	Ticket& operator++()
	{
		this->price++;
		return *this;
	}

	Ticket& operator--()
	{
		this->price--;
		return *this;
	}

	Ticket& operator++(int)
	{

		Ticket copie = *this;
		this->price++;
		return *this;
	}

	Ticket& operator--(int)
	{
		Ticket copie = *this;
		this->price--;
		return *this;
	}
	//Operatorul negatie!
	friend void operator!(Ticket& t)
	{
		if (t.paymentViaCreditCard == 1)
		{
			t.paymentViaCreditCard = 0;
		}
		else
		{
			t.paymentViaCreditCard = 1;
		}
	}

	//metoda care compara preturile
	bool comparePrices(Ticket& t)
	{
		if (this->price < t.price)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	//metoda de comparare a atributelor de tip char*-metoda care compara 2 tichete si determina daca evenimentele sunt aceleasi
	bool compareEvents(Ticket& t)
	{
		if (strcmp(this->event, t.event) == 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
};

class Event
{
	const int id;
	string name;
	char* data;
	int numberOfAvailableTickets;
	float* price;
	int numberOfSoldTickets;
	Ticket* tickets;
public:
	static int contor;
	Event() :id(contor++)
	{
		this->name = "unknown";
		this->data = new char[strlen("unknown") + 1];
		strcpy(this->data, "unknown");
		this->numberOfAvailableTickets = 0;
		this->price = NULL;
		this->numberOfSoldTickets = 0;
		this->tickets = NULL;
	}
	Event(string name, const char* data, int numberOfAvailableTickets, float* price, int numberOfSoldTickets, Ticket* tickets) :id(contor++)
	{
		this->name = name;
		this->data = new char[strlen(data) + 1];
		strcpy(this->data, data);
		this->numberOfAvailableTickets = numberOfAvailableTickets;
		this->price = new float[this->numberOfAvailableTickets];
		for (int i = 0; i < this->numberOfAvailableTickets; i++)
		{
			this->price[i] = price[i];
		}
		this->numberOfSoldTickets = numberOfSoldTickets;
		this->tickets = new Ticket[this->numberOfSoldTickets];
		for (int i = 0; i < this->numberOfSoldTickets; i++)
		{
			this->tickets[i] = tickets[i];
		}
	}
	~Event()
	{
		if (this->data != NULL)
		{
			delete[]this->data;
		}
		if (this->price != NULL)
		{
			delete[]this->price;
		}
		if (this->tickets != NULL)
		{
			delete[]this->tickets;
		}
	}

	//Getters and setters
	const int getId()
	{
		return this->id;
	}
	string getName()
	{
		return this->name;
	}
	const char* getData()
	{
		return this->data;
	}
	int getNumberOfAvailableTickets()
	{
		return this->numberOfAvailableTickets;
	}
	float* getPrice()
	{
		return this->price;
	}
	int getNumberOfSoldTickets()
	{
		return this->numberOfSoldTickets;
	}
	Ticket* getTickets()
	{
		return this->tickets;
	}

	void setName(string newName)
	{
		this->name = newName;
	}
	void setData(const char* newData)
	{
		if (this->data != NULL)
		{
			delete[]this->data;
		}
		this->data = new char[strlen(newData) + 1];
		strcpy(this->data, newData);
	}

	void setAvailableTickets(int newNumberOfAvailableTickets, float* newPrice)
	{
		if (this->price != NULL)
		{
			delete[]this->price;
		}
		this->numberOfAvailableTickets = newNumberOfAvailableTickets;
		this->price = new float[this->numberOfAvailableTickets];
		for (int i = 0; i < this->numberOfAvailableTickets; i++)
		{
			this->price[i] = newPrice[i];
		}
	}
	void setSoldTickets(int newNumberOfSoldTickets, Ticket* newTickets)
	{
		if (this->tickets != NULL)
		{
			delete[]this->tickets;
		}
		this->numberOfSoldTickets = newNumberOfSoldTickets;
		this->tickets = new Ticket[this->numberOfSoldTickets];
		for (int i = 0; i < this->numberOfSoldTickets; i++)
		{
			this->tickets[i] = newTickets[i];
		}
	}

	//Constructorul de copiere
	Event(const Event& e) :id(e.id)
	{
		this->name = e.name;
		this->data = new char[strlen(e.data) + 1];
		strcpy(this->data, e.data);
		this->numberOfAvailableTickets = e.numberOfAvailableTickets;
		this->price = new float[this->numberOfAvailableTickets];
		for (int i = 0; i < this->numberOfAvailableTickets; i++)
		{
			this->price[i] = e.price[i];
		}
		this->numberOfSoldTickets = e.numberOfSoldTickets;
		this->tickets = new Ticket[this->numberOfSoldTickets];
		for (int i = 0; i < this->numberOfSoldTickets; i++)
		{
			this->tickets[i] = e.tickets[i];
		}
	}

	//Operatorul=
	Event& operator=(const Event& e)
	{
		if (this->data != NULL)
		{
			delete[]this->data;
		}
		if (this->price != NULL)
		{
			delete[]this->price;
		}
		if (this->tickets != NULL)
		{
			delete[]this->tickets;
		}
		this->name = e.name;
		this->data = new char[strlen(e.data) + 1];
		strcpy(this->data, e.data);
		this->numberOfAvailableTickets = e.numberOfAvailableTickets;
		this->price = new float[this->numberOfAvailableTickets];
		for (int i = 0; i < this->numberOfAvailableTickets; i++)
		{
			this->price[i] = e.price[i];
		}
		this->numberOfSoldTickets = e.numberOfSoldTickets;
		this->tickets = new Ticket[this->numberOfSoldTickets];
		for (int i = 0; i < this->numberOfSoldTickets; i++)
		{
			this->tickets[i] = e.tickets[i];
		}
		return *this;
	}

	//Operatorul<<
	friend ostream& operator<<(ostream& out, Event& e)
	{
		out << "Id: " << e.id << endl;
		out << "Name: " << e.name << endl;
		out << "Data: " << e.data << endl;
		out << "Number of available tickets: " << e.numberOfAvailableTickets << endl;
		out << "Prices of available tickets: " << endl;
		for (int i = 0; i < e.numberOfAvailableTickets; i++)
		{
			out << e.price[i] << " " << endl;
		}
		out << "Number of sold tickets: " << e.numberOfSoldTickets << endl;
		out << "Tickets: " << endl;
		for (int i = 0; i < e.numberOfSoldTickets; i++)
		{
			out << e.tickets[i] << " " << endl;
		}
		return out;
	}

	//Operatorul>>
	friend istream& operator>>(istream& in, Event& e)
	{

		if (e.data != NULL)
		{
			delete[]e.data;
		}
		if (e.price != NULL)
		{
			delete[]e.price;
		}
		if (e.tickets != NULL)
		{
			delete[]e.tickets;
		}
		cout << "Enter from the keyboard the name: " << endl;
		in >> e.name;
		cout << "Enter from the keyboard the data: " << endl;
		char aux[50];
		in >> aux;
		e.data = new char[strlen(e.data) + 1];
		strcpy(e.data, aux);
		cout << "Enter from the keyboard the number of available tickets: " << endl;
		in >> e.numberOfAvailableTickets;
		cout << "Enter from the keyboard the prices of the available tickets: " << endl;
		e.price = new float[e.numberOfAvailableTickets];
		for (int i = 0; i < e.numberOfAvailableTickets; i++)
		{
			in >> e.price[i];
		}
		cout << "Enter from the keyboard the number of sold tickets: " << endl;
		in >> e.numberOfSoldTickets;
		cout << "Enter from the keyboard the sold tickets: " << endl;
		e.tickets = new Ticket[e.numberOfSoldTickets];
		for (int i = 0; i < e.numberOfSoldTickets; i++)
		{
			in >> e.tickets[i];
		}
		return in;
	}

	//Metoda prin care vom adauga in vectorul de tickete vandute inca un ticket pe ultima pozitie din vector
	void addTicket(Ticket t)
	{
		Event copy = *this;
		if (this->tickets != NULL)
		{
			delete[]this->tickets;
		}
		this->numberOfSoldTickets = numberOfSoldTickets++;
		this->tickets = new Ticket[this->numberOfSoldTickets];
		for (int i = 0; i < this->numberOfSoldTickets - 1; i++)
		{
			this->tickets[i] = copy.tickets[i];
		}
		this->tickets[this->numberOfSoldTickets - 1] = t;
	}
	//Operatorul de indexare []
	float operator[](int position)
	{
		if (position >= 0 && position < this->numberOfAvailableTickets)
		{
			return this->price[position];
		}
		else
		{
			return -1;
		}
	}
	//Operatorul de cast la int
	operator int()
	{
		int nr = 0;
		for (int i = 0; i < this->numberOfAvailableTickets; i++)
		{
			if (this->price[i] > 100)
			{
				nr++;
			}
		}
		return nr;
	}

	//Operator<=
	bool operator<=(Event& e)
	{
		if (this->numberOfAvailableTickets <= e.numberOfAvailableTickets)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	//metoda care ofera un discount unui anumit ticket disponibil
	float ticketDiscount(int pos, float discount)
	{
		float discountResult;
		discountResult = this->price[pos] - discount * price[pos];
		return discountResult;

	}

};

class Location
{
	string name;
	int numberOfZones;
	int* capacity;
	bool** map;
public:
	//Constructorul fara parametrii
	Location()
	{
		this->name = "unknown";
		this->numberOfZones = 0;
		this->capacity = NULL;
		this->map = NULL;
	}

	Location(string name, int numberOfZones, int* capacity) :name(name), numberOfZones(numberOfZones)
	{
		this->capacity = new int[this->numberOfZones];
		this->map = new bool* [this->numberOfZones];
		for (int i = 0; i < this->numberOfZones; ++i) {
			this->capacity[i] = capacity[i];
			this->map[i] = new bool[capacity[i]];
			for (int j = 0; j < capacity[i]; ++j) {
				this->map[i][j] = 0;
			}
		}
	}

	~Location() {
		for (int i = 0; i < this->numberOfZones; ++i) {
			delete[] map[i];
		}
		delete[] map;
		delete[] capacity;
	}

	string getName()
	{
		return this->name;
	}

	int getNumberOfZones()
	{
		return this->numberOfZones;
	}
	int* getCapacity()
	{
		return this->capacity;
	}
	bool** getMap()
	{
		return this->map;
	}

	void setName(string newName)
	{
		this->name = newName;
	}

	Location(const Location& l) :name(l.name), numberOfZones(l.numberOfZones)
	{
		this->capacity = new int[this->numberOfZones];
		this->map = new bool* [this->numberOfZones];
		for (int i = 0; i < this->numberOfZones; ++i) {
			this->capacity[i] = l.capacity[i];
			this->map[i] = new bool[capacity[i]];
			for (int j = 0; j < capacity[i]; ++j) {
				this->map[i][j] = l.map[i][j];
			}
		}
	}
	Location& operator=(Location& l)
	{
		for (int i = 0; i < this->numberOfZones; ++i) {
			delete[] map[i];
		}
		delete[] map;
		delete[] capacity;
		this->name = l.name;
		this->numberOfZones = l.numberOfZones;
		this->capacity = new int[numberOfZones];
		this->map = new bool* [numberOfZones];
		for (int i = 0; i < this->numberOfZones; ++i) {
			this->capacity[i] = l.capacity[i];
			this->map[i] = new bool[capacity[i]];
			for (int j = 0; j < capacity[i]; ++j) {
				this->map[i][j] = l.map[i][j];
			}
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, Location& l)
	{
		out << "Name: " << l.name << endl;
		out << "Number of zones: " << l.numberOfZones << endl;
		out << "Capacity: " << endl;
		for (int i = 0; i < l.numberOfZones; i++)
		{
			out << l.capacity[i] << endl;
			for (int j = 0; j < l.capacity[i]; ++j) {
				out << l.map[i][j] << ' ';
			}
			out << endl;
		}
		return out;
	}

	friend istream& operator>>(istream& in, Location& l)
	{
		for (int i = 0; i < l.numberOfZones; ++i) {
			delete[] l.map[i];
		}
		delete[] l.map;
		delete[] l.capacity;
		cout << "Enter name: " << endl;
		in >> l.name;
		cout << "Enter number of zones: " << endl;
		in >> l.numberOfZones;
		l.capacity = new int[l.numberOfZones];
		l.map = new bool* [l.numberOfZones];
		for (int i = 0; i < l.numberOfZones; ++i) {
			cout << "Enter capacity for zone " << i << ": " << endl;
			in >> l.capacity[i];
			l.map[i] = new bool[l.capacity[i]];
			cout << "Enter map for zone " << i << ": " << endl;
			for (int j = 0; j < l.capacity[i]; ++j) {
				in >> l.map[i][j];
			}
		}
		return in;

	}

	bool operator<=(Location& l)
	{
		if (this->numberOfZones <= l.numberOfZones)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	bool operator==(Location& l)
	{
		if (this->numberOfZones == l.numberOfZones)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	operator string()
	{
		string sentence = "The name of the location is: " + this->name;
		return sentence;
	}
	float sumOfCapacity()
	{
		float result = 0;
		for (int i = 0; i < this->numberOfZones; i++)
		{
			result = result + this->capacity[i];
		}
		return result;
	}

	float maxCapacity()
	{
		float max = this->capacity[0];
		for (int i = 0; i < this->numberOfZones; i++)
		{
			if (max < this->capacity[i])
			{
				max = this->capacity[i];
			}
		}
		return max;
	}
};

int Ticket::contor = 1;
int Event::contor = 89373738;
void main()
{
	cout << "----------------------TICKET-------------------------------" << endl << endl;
	Ticket t;
	Ticket t1("Peter", "Concert", 1, 540.89);
	Ticket t2("Merry", "Masterclass", 0, 321.99);
	Ticket t3("Bogdan", "Meci fotbal", 1, 678.23);

	cout << "------------------Getters and setters-----------------------" << endl;
	cout << t.getId() << endl;
	cout << t.getUser() << endl;
	cout << t.getEvent() << endl;
	cout << t.getPaymentViaCard() << endl;
	cout << t.getPrice() << endl;
	cout << endl << endl;
	cout << t1.getId() << endl;
	cout << t1.getUser() << endl;
	cout << t1.getEvent() << endl;
	cout << t1.getPaymentViaCard() << endl;
	cout << t1.getPrice() << endl;
	cout << endl << endl;
	cout << t2.getId() << endl;
	cout << t2.getUser() << endl;
	cout << t2.getEvent() << endl;
	cout << t2.getPaymentViaCard() << endl;
	cout << t2.getPrice() << endl;
	cout << endl << endl;
	cout << t3.getId() << endl;
	cout << t3.getUser() << endl;
	cout << t3.getEvent() << endl;
	cout << t3.getPaymentViaCard() << endl;
	cout << t3.getPrice() << endl;

	cout << endl << endl;
	cout << endl << endl;

	t1.setUser("Andrei");
	t1.setEvent("Programming Class");
	t1.setPaymentViaCard(0);
	t1.setPrice(899.99);
	cout << t1.getId() << endl;
	cout << t1.getUser() << endl;
	cout << t1.getEvent() << endl;
	cout << t1.getPaymentViaCard() << endl;
	cout << t1.getPrice() << endl;
	cout << endl << endl;
	cout << "-------------Operatorul<<---------------------" << endl;
	cout << t << endl << endl;
	cout << t1 << endl << endl;
	cout << t2 << endl << endl;
	cout << t3 << endl << endl;
	cout << endl << endl << endl;
	//cout << "-------------Operatorul>>---------------------" << endl;
	//cout << t1 << endl;
	//cin >> t1;
	//cout << t1 << endl;
	cout << "------------Constructorul de copiere---------------------" << endl;
	cout << t3 << endl << endl;
	Ticket t4 = t3;
	cout << t4 << endl << endl;

	cout << "-------------Operatorul=---------------------" << endl;
	cout << t1 << endl << endl;
	t2 = t1;
	cout << t2 << endl << endl;

	cout << "-------------Operatorul!---------------------" << endl;

	cout << t1 << endl << endl;
	!t1;
	cout << t1 << endl << endl;

	cout << "-------------Operatorul++ si -- ---------------------" << endl;

	cout << t1 << endl << endl;
	++t1;
	cout << t1 << endl << endl;

	cout << t2 << endl << endl;
	t2++;
	cout << t2 << endl << endl;

	cout << t3 << endl << endl;
	--t3;
	cout << t3 << endl << endl;

	cout << t4 << endl << endl;
	t4--;
	cout << t4 << endl << endl;

	cout << "---------------------Metodele de comparatie------------------------" << endl;
	cout << t1.compareEvents(t3) << endl;
	cout << t4.compareEvents(t3) << endl;
	cout << t1.comparePrices(t3) << endl;
	cout << t4.comparePrices(t3) << endl;

	cout << endl << endl << endl;
	cout << "----------------------EVENT-------------------------------" << endl << endl;

	float vectorPrices1[] = { 120,99.9,876,234.5 };
	Ticket vectorTickets1[] = { t1,t2,t3 };

	Event e;
	Event e1("Masterclass C++", "23.12.2022", 4, vectorPrices1, 3, vectorTickets1);

	float vectorPrices2[] = { 120,9.9,876,234.5,99,765.5,234,10,99.7 };
	Ticket vectorTickets2[] = { t1,t2,t3,t4 };

	Event e2("Rihanna Concert", "12.07.2023", 9, vectorPrices2, 4, vectorTickets2);


	float vectorPrices3[] = { 567.7,342.8,789.6,89.7 };
	Ticket vectorTickets3[] = { t1,t3 };

	Event e3("Programming Course", "19.01.2023", 4, vectorPrices3, 2, vectorTickets3);
	cout << "---------------------Getters------------------" << endl;
	cout << e.getId() << endl << endl;
	cout << e.getName() << endl << endl;
	cout << e.getData() << endl << endl;
	cout << e.getNumberOfAvailableTickets() << endl << endl;
	for (int i = 0; i < e.getNumberOfAvailableTickets(); i++)
	{
		cout << e.getPrice()[i] << " " << endl << endl;
	}
	cout << e.getNumberOfSoldTickets() << endl << endl;
	for (int i = 0; i < e.getNumberOfSoldTickets(); i++)
	{
		cout << e.getTickets()[i] << " " << endl << endl;
	}
	cout << endl << endl << endl;
	cout << e1.getId() << endl << endl;
	cout << e1.getName() << endl << endl;
	cout << e1.getData() << endl << endl;
	cout << e1.getNumberOfAvailableTickets() << endl << endl;
	for (int i = 0; i < e1.getNumberOfAvailableTickets(); i++)
	{
		cout << e1.getPrice()[i] << endl << endl;
	}
	cout << e1.getNumberOfSoldTickets() << endl << endl;
	for (int i = 0; i < e1.getNumberOfSoldTickets(); i++)
	{
		cout << e1.getTickets()[i] << " " << endl << endl;
	}
	cout << endl << endl << endl;
	cout << endl << endl << endl;
	cout << e2.getId() << endl << endl;
	cout << e2.getName() << endl << endl;
	cout << e2.getData() << endl << endl;
	cout << e2.getNumberOfAvailableTickets() << endl << endl;
	for (int i = 0; i < e2.getNumberOfAvailableTickets(); i++)
	{
		cout << e2.getPrice()[i] << " " << endl << endl;
	}
	cout << e2.getNumberOfSoldTickets() << endl << endl;
	for (int i = 0; i < e2.getNumberOfSoldTickets(); i++)
	{
		cout << e2.getTickets()[i] << " " << endl << endl;
	}
	cout << endl << endl << endl;
	cout << endl << endl << endl;
	cout << e3.getId() << endl << endl;
	cout << e3.getName() << endl << endl;
	cout << e3.getData() << endl << endl;
	cout << e3.getNumberOfAvailableTickets() << endl << endl;
	for (int i = 0; i < e3.getNumberOfAvailableTickets(); i++)
	{
		cout << e3.getPrice()[i] << " " << endl << endl;
	}
	cout << e3.getNumberOfSoldTickets() << endl << endl;
	for (int i = 0; i < e3.getNumberOfSoldTickets(); i++)
	{
		cout << e3.getTickets()[i] << " " << endl << endl;
	}
	cout << endl << endl << endl;
	cout << "---------------------Setters------------------" << endl;

	e1.setName("Concert Bucharest");
	e1.setData("05.03.2023");
	e1.setAvailableTickets(9, vectorPrices2);
	e1.setSoldTickets(4, vectorTickets2);
	cout << e1.getId() << endl << endl;
	cout << e1.getName() << endl << endl;
	cout << e1.getData() << endl << endl;
	cout << e1.getNumberOfAvailableTickets() << endl << endl;
	for (int i = 0; i < e1.getNumberOfAvailableTickets(); i++)
	{
		cout << e1.getPrice()[i] << " " << endl << endl;
	}
	cout << e1.getNumberOfSoldTickets() << endl << endl;
	for (int i = 0; i < e1.getNumberOfSoldTickets(); i++)
	{
		cout << e1.getTickets()[i] << " " << endl << endl;
	}
	cout << endl << endl << endl;


	cout << "---------------Operatorul<<--------------------" << endl;
	cout << e << endl << endl;
	cout << e1 << endl << endl;
	cout << e2 << endl << endl;
	cout << e3 << endl << endl;

	cout << "---------------------Constructorul de copiere-----------------" << endl;
	cout << e2 << endl << endl;
	Event e4 = e2;
	cout << e4 << endl << endl;

	cout << "---------------Operatorul=--------------------" << endl;
	cout << e1 << endl << endl;
	e2 = e1;
	cout << e2 << endl << endl;

	/*cout << "---------------Operatorul>>--------------------" << endl;
	cout << e1 << endl << endl;
	cin >> e1;
	cout << e1 << endl << endl;*/

	cout << "---------------Operatorul index[] --------------------" << endl;
	cout << e1[1] << endl << endl;
	cout << "---------------Operatorul de cast la int --------------------" << endl;
	cout << (int)e3 << endl << endl;

	cout << "-------------Metoda prin care adaugam un ticket in event--------------" << endl;
	cout << "Before: " << endl;
	cout << e1 << endl << endl;
	e1.addTicket(t2);
	cout << "After: " << endl;
	cout << e1 << endl << endl;

	cout << "-------------Metoda prin care oferim un discount unui anumit ticket disponibil de pe o anumita pozitie--------------" << endl;
	cout << e3.ticketDiscount(1, 0.4) << endl << endl;
	cout << e3 << endl << endl;
	cout << endl << endl << endl << endl << "-------------------------LOCATION------------------------------" << endl;
	int capacity1[] = { 2,3,4 };
	Location l1("Bucharest", 3, capacity1);
	cout << "---------------Operatorul<<------------------" << endl;
	cout << l1 << endl;

	int capacity2[] = { 3,3,3 };
	Location l2("Constanta", 3, capacity2);

	int capacity3[] = { 10,10,10,10,10 };
	Location l3("Ghencea", 5, capacity3);

	cout << l2 << endl << endl;
	cout << l3 << endl << endl;

	cout << "---------------Operatorul>>------------------" << endl;
	/*cout << l1 << endl;
	cin >> l1;
	cout << l1 << endl;*/
	cout << "---------------Operatorul<=---------------" << endl;
	cout << (l1 <= l3) << endl << endl;

	cout << "---------------Operatorul==------------------" << endl;
	cout << (l1 == l3) << endl << endl;

	cout << "-------------Metoda sumOfCapacity-------------------" << endl;
	cout << l1.sumOfCapacity() << endl;

	cout << "-------------Metoda maxCapacity-------------------" << endl;
	cout << l3.maxCapacity() << endl;

	cout << "---------------Constructorul de copiere------------------" << endl;
	cout << l3 << endl << endl;
	Location l4 = l3;
	cout << l4 << endl << endl;

	cout << "---------------Operatorul=------------------" << endl;
	cout << l2 << endl << endl;
	l1 = l2;
	cout << l1 << endl << endl;

}