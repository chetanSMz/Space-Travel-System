/**
 * @file: sts_v3.cpp
 * @author: Chetan (210281)
 * @brief: implements the space travel system as specified in the assignment
 * @date: 20230321
 * @version: 0.3
 * 
*/

#include<bits/stdc++.h>
#include<iostream>
#include<string>
#include <ctime>

using namespace std;

// returns the present date in the form of YYYYMMDD
int currentDate(void){
    // Get the current time
   std::time_t now = std::time(nullptr);
   // Convert to a local time struct
   std::tm* localTime = std::localtime(&now);
   // Format the date as YYYYMMDD
   char buffer[9];
   std::strftime(buffer, sizeof(buffer), "%Y%m%d", localTime);
   // Output the formatted date
   //std::cout << buffer << std::endl;

   return stoi(buffer);
}


// calculates the number of days between two given dates(which are in the form of YYYYMMDD)
int difference(int date1, int date2){
    // Extract year, month, and day from input dates
    int year1 = date1 / 10000;
    int year2 = date2 / 10000;
    int month1 = (date1 / 100) % 100;
    int month2 = (date2 / 100) % 100;
    int day1 = date1 % 100;
    int day2 = date2 % 100;

    // Calculate difference in days
    int days1 = day1 + 31 * (month1 - 1) + 365 * (year1 - 1) + std::floor(year1 / 4) - std::floor(year1 / 100) + std::floor(year1 / 400);
    int days2 = day2 + 31 * (month2 - 1) + 365 * (year2 - 1) + std::floor(year2 / 4) - std::floor(year2 / 100) + std::floor(year2 / 400);
    int diff_days = abs(days2 - days1);

return diff_days;
}


/******************************************   TRAVELLER CLASS   *****************************************************/


class traveller{
    public:
        string name;
        string ID;

        //these are required to give unique ID to travellers
        static set <string> list_of_travellers;         // stores any new name in the set
        static map <string, int> count;                 // keeps a track of how many travellers with the same name are present

        static set <pair<string, string>> database_of_travellers;     // stores the name and id of all the travllers

        void setID(string name);
        string getName(void);
        string getID(void);

        traveller(string NAME);

};

set <string> traveller::list_of_travellers;
map<string, int> traveller::count;
set<pair<string, string>> traveller::database_of_travellers;


traveller::traveller(string NAME){
    name = NAME;
    setID(name);
}

void traveller::setID(string name){    
    if(traveller::list_of_travellers.count(name) == 1){
        traveller::count[name]++;
    }

    else if(traveller::list_of_travellers.count(name) == 0){
       traveller::count[name] = 1;
       list_of_travellers.insert(name);
    }

    ID = name;
    string s = to_string(traveller::count[name]);
    ID.append(s);

}

string traveller::getID(void){
    return ID;
}

string traveller::getName(void){
    return name;
}

/******************************    ASTRONAUT CLASS (child class of TRAVELLER CLASS)   ********************************/


class astronaut: public traveller{
    private:
        int experience;

    public:
        astronaut(string NAME);
        void setExperience(int EXPERIENCE);
        int getExperience(void);

};

void astronaut::setExperience(int EXPERIENCE){
    experience = EXPERIENCE;
}

int astronaut::getExperience(void){
    return experience;
}

astronaut::astronaut(string NAME):traveller(NAME){
    string A = "A";
    ID.insert(0, A);

    pair<string, string> p = {name, ID};
    traveller::database_of_travellers.insert(p);
}

/******************************    PASSENGER CLASS (child class of TRAVELLER CLASS)   ********************************/

class passenger: public traveller{
    public:
        passenger(string NAME);
};

passenger::passenger(string NAME):traveller(NAME){
    string P = "P";
    ID.insert(0, P);

    pair<string, string> p = {name, ID};
    traveller::database_of_travellers.insert(p);
}

/******************************    COMMANDER CLASS (child class of TRAVELLER CLASS)   ********************************/


class commander: public traveller{
    private:
        string authority;
        int experience;

    public:
        commander(string NAME);
        void setAuthority(void);
        string getAuthority(void);
        void setExperience(int EXPERIENCE);
        int getExperience(void);
        static vector <pair<string, string>> list_of_commanders;
        void list_all_commanders(void);
};

vector<pair<string, string>> commander::list_of_commanders;

void commander::setExperience(int EXPERIENCE){
    experience = EXPERIENCE;
}

int commander::getExperience(void){
    return experience;
}

void commander::setAuthority(void){
    authority = ID;                              
}

string commander::getAuthority(void){
    return authority;
}


commander::commander(string NAME):traveller(NAME){
    string C = "C";
    ID.insert(0, C);

    pair<string, string> p = {name, ID};
    traveller::database_of_travellers.insert(p);

    commander::list_of_commanders.push_back(p);
}

void commander::list_all_commanders(void){
    for(auto iter = commander::list_of_commanders.begin(); iter != commander::list_of_commanders.end(); ++iter){
        cout << "Name: " << iter->first << "  ID: " << iter->second << "\n";
    }
}


//*********************************************************************************************************

//just declared the function; its definition is written later after defining the space_travel class

bool find_space_travel(string source_station, string destination_station, int travel_date);

/********************************************   PLANET CLASS   *****************************************************/

class planet{
    public:
        string name;
        double position_x;
        double position_y;
        double position_z;
        static vector<tuple<string, double, double, double>> database_of_planets;

        tuple<double, double, double> getCoordinates(void);

        planet(string name, double position_x, double position_y, double position_z);

};

vector<tuple<string, double, double, double>> planet::database_of_planets;

planet::planet(string name, double position_x, double position_y, double position_z){
    this-> name = name;
    this-> position_x = position_x;
    this-> position_y = position_y;
    this-> position_z = position_z;

    auto t = make_tuple(name, position_x, position_y, position_z);
    planet::database_of_planets.push_back(t);

}

tuple<double, double, double> planet::getCoordinates(void){
    cout<<"position_x = "<<position_x<<" position_y = "<<position_y<<" position_z = "<<position_z<<"\n";
    auto coordinates = make_tuple(position_x, position_y, position_z);

return coordinates;
}


/******************************** MOON CLASS (CHILD CLASS OF PLANET CLASS)   ************************************/


class moon:public planet{
    public:
        string atmosphere;
        string water;
        string inhabitants;
        moon(string name, double position_x, double position_y, double position_z);

        string waterInfo(void);
        string atmosphereInfo(void);
        string inhabitantsInfo(void);

};


moon::moon(string name, double position_x, double position_y, double position_z):planet(name, position_x, position_y, position_z){

}


string moon::atmosphereInfo(void){
    return atmosphere;
}

string moon::waterInfo(void){
    return water;
}

string moon::inhabitantsInfo(void){
    return inhabitants;
}

/******************************** MARS CLASS (CHILD CLASS OF PLANET CLASS)   ************************************/


class mars:public planet{
    public:
        string atmosphere;
        string water;
        string inhabitants;
        mars(string name, double position_x, double position_y, double position_z);

        string waterInfo(void);
        string atmosphereInfo(void);
        string inhabitantsInfo(void);

};

mars::mars(string name, double position_x, double position_y, double position_z):planet(name, position_x, position_y, position_z){
    
}

string mars::atmosphereInfo(void){
    return atmosphere;
}

string mars::waterInfo(void){
    return water;
}

string mars::inhabitantsInfo(void){
    return inhabitants;
}

long long int find_distance(tuple<double, double, double> t1, tuple<double, double, double> t2){
    double distance = 0.0;
    double x = pow((get<0>(t1) - get<0>(t2)), 2);
    double y = pow((get<1>(t1) - get<1>(t2)), 2);
    double z = pow((get<2>(t1) - get<2>(t2)), 2);

    distance = abs(sqrt(x + y + z));

    return (long long int)distance;
}



/*****************************************    TICKET CLASS   *****************************************************/


class ticket{
    private:
        long long int price;

    public:
        string source_station;
        string destination_station;
        string name;
        string ID;
        int travel_date;
        int validity;
        static int K;                 
        static vector<tuple<string, string, string, int>> database_of_tickets;
        static void printAllTickets(void);
        ticket(string name, string ID);
        ~ticket();

        void bookTicket(string source_station, string destination_station, int travel_date);
        void cancelTicket(void);
        void updateTicket(string destination_station, int travel_date);
        void setPrice(void);
        long long int getPrice(void);
        void printTicket(void);

};

void ticket::printAllTickets(){
    for(const auto &i : ticket::database_of_tickets){
        cout << "ID: " << get<0>(i) << "  Source Station: " << get<1>(i) << "  Destination Station: " << get<2>(i) << "  Travel Date: " << get<3>(i) << "\n";
    }
}

ticket::~ticket(){
    // this is used to call destructor explicitly to delete the object of ticket class when the user opts to cancel in
}



int ticket::K = 231102; // just a number to find out the price for space_travel

vector<tuple<string, string, string, int>> ticket::database_of_tickets;

ticket::ticket(string name, string ID){
    pair<string, string> p = {name, ID};
    
    if(traveller::database_of_travellers.count(p) == 0){
        cout<<"The name and ID are not valid\n";
        return;
    }
    else if(traveller::database_of_travellers.count(p) == 1){
        this->name = name;
        this->ID = ID;
        string source_station;
        string destination_station;
        int travel_date;
        cout << "*************************************************************************************************\n";
        cout << "Hello " << name << "\n";
        cout << "From where would you like to start your journey?\n" << ">";
        cin >> source_station;
        cout << "Where would you like to go?\n" << ">";
        cin >> destination_station;
        cout << "Please enter your travel date(YYYYMMDD)\n" << ">";
        cin >> travel_date;

        ticket::bookTicket(source_station, destination_station, travel_date);
        
        setPrice();
        long long int PRICE = getPrice();
        cout << "The price of the ticket is " << PRICE << "\n";
        cout << "*************************************************************************************************\n";

    }

    this->name = name;
    this-> ID = ID;
} 

void ticket::bookTicket(string source_station, string destination_station, int travel_date){
    pair<string, string> p = {name, ID};
    
    if(traveller::database_of_travellers.count(p) == 0){
        cout<<"The name and ID are not valid\n";
        ticket::~ticket();
        return;
    }

    if(source_station == destination_station){
        cout << "Source and Destination could not be same\n Please try changing them\n";
        return;
    }

    this->source_station = source_station;
    this->destination_station = destination_station;
    this->travel_date = travel_date;
    
    auto t = make_tuple(ID, source_station, destination_station, travel_date);
    ticket::database_of_tickets.push_back(t);

    cout << "Your ticket has been booked successfully\n";

    if(ID[0] == 'P'){
        int booking_date = currentDate();
        int validity_date = booking_date + 100000;

        int days = difference(booking_date, validity_date);
        validity = days;
        cout << "Your ticket is valid till " << validity_date << "(YYYYMMDD)\n";
    }

    else if(ID[0] == 'C' || ID[0] == 'A'){
        int validity_date = currentDate() + 10000000;
        
        int days = difference(currentDate(), validity_date);
        validity = days;                                        

        cout << "Your ticket has infinite validity\n";
    }

    
    bool is_possible = find_space_travel(source_station, destination_station, travel_date);
    if(is_possible){
        cout<<"space_travel from "<<source_station<<" to "<<destination_station<<" is now possible\n";
    }
}

void ticket::cancelTicket(void){      

    auto iter = ticket::database_of_tickets.begin();
    for(const auto &i : ticket::database_of_tickets){

        if(get<0>(i) == ID && get<1>(i) == source_station && get<2>(i) == this->destination_station && get<3>(i) == this->travel_date){
            ticket::database_of_tickets.erase(iter);
        }

        iter++;
    }

    cout<<"Your ticket has been cancelled successfully\n";

    ticket::~ticket();
}

void ticket::updateTicket(string DESTINATION_STATION, int TRAVEL_DATE){

        auto iter = ticket::database_of_tickets.begin();
    for(const auto &i : ticket::database_of_tickets){

        if(get<0>(i) == ID && get<1>(i) == source_station && get<2>(i) == this->destination_station && get<3>(i) == this->travel_date){
            ticket::database_of_tickets.erase(iter);
        }

        iter++;
    }

    
    destination_station = DESTINATION_STATION;
    travel_date = TRAVEL_DATE;

    auto t = make_tuple(ID, source_station, destination_station, travel_date);
    ticket::database_of_tickets.push_back(t);

    cout<<"Your ticket has been updated successfully\n";

    bool is_possible = find_space_travel(source_station, destination_station, travel_date);
    if(is_possible){
        cout<<"space_travel from "<<source_station<<" to "<<destination_station<<" is now possible\n";
    }
}


void ticket::setPrice(void){
    int presentDate = currentDate();
    int diff = difference(presentDate, travel_date);

    tuple<double, double, double> coordinates1;
    tuple<double, double, double> coordinates2;

    for(auto iter = planet::database_of_planets.begin(); iter != planet::database_of_planets.end(); iter++){
        if(get<0>(*iter) == source_station){
            coordinates1 = make_tuple(get<1>(*iter), get<2>(*iter), get<3>(*iter));
        }

        if(get<0>(*iter) == destination_station){
            coordinates2 = make_tuple(get<1>(*iter), get<2>(*iter), get<3>(*iter));
        }
    }

    long long int distance = find_distance(coordinates1, coordinates2);

    long long int PRICE = ((ticket::K * distance) / (1+diff));

    price = PRICE;
}

long long int ticket::getPrice(void){
    return price;
}

void ticket::printTicket(void){
    cout << "*******************************************************************************\n";
    cout<<"Name: "<<name<<"\n";
    cout<<"ID: "<<ID<<"\n";
    cout<<"Source Station: "<<source_station<<"\n";
    cout<<"Destination Station: "<<destination_station<<"\n";
    cout<<"Travel Date: "<<travel_date<<"\n";
    cout << "*******************************************************************************\n";
}



/*******************************************  SPACE TRAVEL CLASS  *********************************************/


class space_travel{
    private:
      
      // all the passengers present in the space travel class will be added in this vector
      vector<passenger> p;               

      astronaut a{"A1"};
      commander c{"C1"};

    public:
        string source_station;
        string destination_station;
        int travel_date;
        void addPassengers(passenger P);
        void addAstronaut(astronaut A);
        void addCommander(commander C);
        void updateAstronaut(astronaut A);
        void updateCommander(commander C);
        void listTravellers(void);

        space_travel(string source_station, string destination_station, int travel_date);

};

space_travel::space_travel(string source_station, string destination_station, int travel_date){
    
    int passenger_count = 0, astronaut_count = 0, commander_count = 0;
    
    for(auto iter = ticket::database_of_tickets.begin(); iter != ticket::database_of_tickets.end(); ++iter){
        if(get<1>(*iter) == source_station && get<2>(*iter) == destination_station && get<3>(*iter) == travel_date){
            if(get<0>(*iter)[0] == 'P'){
                passenger_count++;
            }
            else if(get<0>(*iter)[0] == 'A'){
                astronaut_count++;
            }
            else if(get<0>(*iter)[0] == 'C'){
                commander_count++;
            }
        } 
    }

    if(passenger_count > 2 && astronaut_count >= 1 && commander_count >=1){
        cout<<"space_travel from "<<source_station<<" to "<<destination_station<<" is created\n";
    }
    else{
        cout<<"space_travel from "<<source_station<<" to "<<destination_station<<" can't be created as it does not satisfy the requirements\n";
    }
    
    this->source_station = source_station;
    this->destination_station = destination_station;
    this->travel_date = travel_date;
}


void space_travel::listTravellers(){
    cout << "****************************************************************************************\n";
    cout << "List of Travellers going from " << source_station << " to " << destination_station << " on " << travel_date << "\n";
    cout << "Astronaut:\n";
    cout << "Name: " << a.name << "  ID: " << a.ID << "\n";

    cout << "Commander:\n";
    cout << "Name: " << c.name << "  ID: " << c.ID << "\n";


    cout << "Passengers:\n";
    for( auto iter = p.begin(); iter != p.end(); iter++){
        cout << "Name: " << iter->name << "  ID: " << iter->ID << "\n";
    }
}

void space_travel::addPassengers(passenger P){
    if(p.size() <= 8){
        p.push_back(P);
    }
}

void space_travel::addAstronaut(astronaut A){
    a = A;
}

void space_travel::addCommander(commander C){
    c = C;
}

void space_travel::updateAstronaut(astronaut A){
    a = A;
}

void space_travel::updateCommander(commander C){
    c = C;
}

//**************************************************************************************************************

bool find_space_travel(string source_station, string destination_station, int travel_date){
    
    int passenger_count = 0, astronaut_count = 0, commander_count = 0;
    
    for(auto iter = ticket::database_of_tickets.begin(); iter != ticket::database_of_tickets.end(); ++iter){
        if(get<1>(*iter) == source_station && get<2>(*iter) == destination_station && get<3>(*iter) == travel_date){
            if(get<0>(*iter)[0] == 'P'){
                passenger_count++;
            }
            else if(get<0>(*iter)[0] == 'A'){
                astronaut_count++;
            }
            else if(get<0>(*iter)[0] == 'C'){
                commander_count++;
            }
        }
    }

    if(passenger_count > 2 && astronaut_count >= 1 && commander_count >=1){
        return 1;
    }

return 0;
}


int main()
{   

    // created 3 planets
    planet earth("earth", 1.0, 1.0, 1.0);
    moon moon1("moon1", 2.0, 2.0, 2.0);
    mars mars1("mars1", 3.0, 3.0, 3.0);

    // created 11 passengers, 2 astronauts, 2 commanders
    passenger A("A");
    passenger B("B");
    passenger C("C");
    passenger D("D");
    passenger E("E");
    passenger F("F");
    passenger G("G");
    passenger H("H");
    passenger I("I");
    passenger J("J");
    passenger K("K");
    astronaut A1("A1");
    astronaut A2("A2");
    commander C1("C1");
    commander C2("C2");

    /**
     * here using these objects of ticket class, you can create tickets for passenger 'A', 'B', 'C' 
     * and astronaut 'A2' and commander 'C2'
     * 
     * now here when prompted you can give
     *  source_station = earth
     *  destination_station = mars1
     *  travel_date = 20301201
     * so that you will be able to create a travel class
     * 
     * 
     * you are free to choose any other values too! but in that case you will not be able to create a travel class
     * and you need to create more tickets
     * 
     */         
    ticket t1("A", "PA1");
    ticket t2("B", "PB1");
    ticket t3("C", "PC1");
    ticket t4("A2", "AA21");
    ticket t5("C2", "CC21");

    // now here I had also created ticket for passenger 'F' so that it can be checked whether update ticket
    // and cancel ticket are working correctly or not
    ticket t6("F", "PF1");
    ticket::printAllTickets();
    t6.updateTicket("mars1", 20301201);
    ticket::printAllTickets();
    t6.cancelTicket();
    ticket::printAllTickets();


    string source_station = "earth";
    string destination_station = "mars1";
    int travel_date = 20301201;

    // if all the tickets have the source_station, destination_station and travel_date as specifed then the object
    // will be created else not
    space_travel S(source_station, destination_station, travel_date);
    
    if(find_space_travel(source_station, destination_station, travel_date)){
        S.addPassengers(A);
        S.addPassengers(B);
        S.addPassengers(C);
        S.addAstronaut(A2);
        S.addCommander(C2);
        S.listTravellers();
    }

    // now here are some more tickets, you can experiment with them
    ticket t7("G", "PG1");
    ticket t8("H", "PH1");
    ticket t9("I", "PI1");
    ticket t10("A1", "AA11");
    ticket t11("C1", "CC11");

    source_station = "mars1";
    destination_station = "moon1";
    travel_date = 20921201;

    space_travel T(source_station, destination_station, travel_date);

    if(find_space_travel(source_station, destination_station, travel_date)){
        S.addPassengers(G);
        S.addPassengers(H);
        S.addPassengers(I);
        S.addAstronaut(A1);
        S.addCommander(C1);
        S.listTravellers();
    }

return 0;
}