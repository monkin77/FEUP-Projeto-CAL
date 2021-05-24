#include "Interface.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Interface::Interface() {
    bakery = NULL;
    selectedPhase = 1;
}

Interface::~Interface() {
    if (bakery != NULL) delete bakery;
}

void Interface::start() {
    cout << "Welcome to the Bakery's service planner!" << endl;
    cout << "Do you wish to load the information from a file? (Y/N)" << endl;

    char res;
    while (true) {
        cin >> res;
        if (cin.fail() || cin.eof() || (toupper(res) != 'Y' && toupper(res) != 'N' && toupper(res) != 'L')) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "That's not a valid answer. Please answer with 'Y' or 'N'" << endl;
            continue;
        }
        break;
    }

    // Developer Option to generate a bakery input
    if(toupper(res) == 'L') {
        InputGenerator gen;
        gen.generateBakeryInput();
        exit(0);
    }
    else if (toupper(res) == 'N') loadByInput();
    else {
        string file;
        while (true) {
            cout << "Insert the name of the file:" << endl;
            cin >> file;
            if (cin.fail() || cin.eof()) {
                cin.clear();
                cin.ignore(100, '\n');
                continue;
            }
            break;
        }
        bakery = new Bakery("resources/bakeryInput/" + file);
    }
    servicePlanner();
    printResult(cout);
    showResultGraphViewer();
    writeResultInFile();
}

void Interface::servicePlanner() {
    cout << "Select the type of problem you want to solve:" << endl;
    cout << "[1]: Single van visiting all clients without delivery times or capacity" << endl;
    cout << "[2]: Single van visiting all clients with delivery times but no capacity" << endl;
    cout << "[3]: Multiple vans with client allocation, capacity and delivery times" << endl;
    cout << "[4]: Show SCC component of the Bakery" << endl;

    while (true) {
        cin >> selectedPhase;
        if (cin.fail() || cin.eof() || selectedPhase < 1 || selectedPhase > 4) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid choice!" << endl;
            continue;
        }
        break;
    }

    switch (selectedPhase) {
        case 1:
            bakery->solveFirstPhase();
            break;
        case 2:
            bakery->solveSecondPhase();
            break;
        case 3:
            bool useKnapsack, optimize;
            cout << "Do you wish to use knapsack or greedy allocation? (1/2)" << endl;
            cout << "Greedy has generally better but slower results" << endl;

            int choice;
            while (true) {
                cin >> choice;
                if (cin.fail() || cin.eof() || choice < 1 || choice > 2) {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Invalid choice" << endl;
                    continue;
                }
                break;
            }
            useKnapsack = choice == 1;

            cout << "Do you want to optimize the allocation? (Y/N)" << endl;
            cout << "This gives a slightly better but slower result" << endl;

            char res;
            while (true) {
                cin >> res;
                if (cin.fail() || cin.eof() || (toupper(res) != 'Y' && toupper(res) != 'N')) {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Invalid choice" << endl;
                    continue;
                }
                break;
            }
            optimize = toupper(res) == 'Y';

            bakery->solveThirdPhase(useKnapsack, optimize);
            break;
        case 4:
            bakery->filterBakerySCCComponent();

            this->showSCCGraphViewer();
            exit(0);
        default:
            break;
    }
}

void Interface::loadByInput() {
    string graphFile;
    int fetchIsDirected, bakeryX, bakeryY, radius, maxDelay, maxBefore, numVans, numClients;
    bool isDirected;
    vector<Van> vans;
    vector<Client*> clients;

    cout << "Is the Graph directed(1) or Undirected(0)?" << endl;
    cin >> fetchIsDirected;
    while (cin.fail() || cin.eof()) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid input!" << endl;
        cin >> fetchIsDirected;
    }
    isDirected = fetchIsDirected == 1 ? true : false;

    cout << "Type the path of the folder containing the graph (inside resources/maps/)" << endl;
    cin >> graphFile;
    while (cin.fail() || cin.eof()) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid input!" << endl;
        cin >> graphFile;
    }
    graphFile = "resources/maps/" + graphFile;

    cout << "Type the position of the bakery in the form X Y" << endl;
    cin >> bakeryX >> bakeryY;
    while (cin.eof() || cin.fail() || bakeryX < 0 || bakeryY < 0) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid input!" << endl;
        cin >> bakeryX >> bakeryY;
    }

    cout << "How many vans do you want to use?" << endl;
    cin >> numVans;
    while (cin.eof() || cin.fail() || numVans <= 0) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid number!" << endl;
        cin >> numVans;
    }

    for (int i = 0; i < numVans; ++i) {
        int capacity, deliveryTime;
        cout << "Insert the capacity of the van (number of breads): ";
        cin >> capacity;
        while (cin.eof() || cin.fail() || capacity <= 0) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << endl << "Invalid number! ";
            cin >> capacity;
        }

        cout << endl << "Insert the duration of the deliveries (minutes): ";
        cin >> deliveryTime;
        while (cin.eof() || cin.fail() || deliveryTime < 0) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid number! ";
            cin >> capacity;
        }

        vans.push_back(Van(capacity, Time(deliveryTime)));
    }

    bakery = new Bakery(graphFile, vans, Position(bakeryX, bakeryY), radius, maxDelay, maxBefore, isDirected);

    cout << "How many clients do you want to use?" << endl;
    cin >> numClients;
    while (cin.eof() || cin.fail() || numClients <= 0) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid number!" << endl;
        cin >> numClients;
    }

    for (int i = 0; i < numClients; ++i) {
        string name;
        int id = 0, latitute, longitude, hours, mins, breadNum;

        cout << "Insert the name of the client: ";
        cin >> name;
        while (cin.eof() || cin.fail() || name == "") {
            cin.clear();
            cin.ignore(100, '\n');
            cout << endl << "Invalid name! ";
            cin >> name;
        }

        cout << endl << "Insert the client position in the format X Y: ";
        cin >> latitute >> longitude;
        while (cin.eof() || cin.fail() || latitute < 0 || longitude < 0) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << endl << "Invalid position!" << endl;
            cin >> latitute >> longitude;
        }

        cout << endl << "Insert the time of the delivery in the format HH:MM" << endl;
        char c;
        cin >> hours >> c >> mins;
        while (cin.eof() || cin.fail() || hours < 7 || hours > 24 || mins < 0 || mins > 60) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid time! Remember that the bakery only opens at 7:00 AM" << endl;
            cin >> hours >> c >> mins;
        }

        cout << "Insert the number of breads in the delivery: ";
        cin >> breadNum;
        while (cin.eof() || cin.fail() || breadNum <= 0) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << endl << "Invalid number! Must be greater than 0: ";
            cin >> breadNum;
        }
        cout << endl;

        bakery->addClient(id++, name, Position(latitute, longitude), Time(hours, mins), breadNum);
    }
}


void Interface::printResult(ostream& os) {
    vector<Van> vans = bakery->getVans();
    for (int i = 0; i < vans.size(); ++i) {
        Van &van = vans[i];
        vector<Client *> clients = van.getClients();
        vector<Edge> edges = van.getEdges();

        os << "Delivery results for van number " << i + 1 << ":" << endl;
        if (clients.empty()) {
            os << "No deliveries made. The van stayed at the bakery" << endl << endl;
            continue;
        }

        os << "Delivered breads: " << van.getDeliveredBread() << endl;

        if (selectedPhase == 3)
            os << "Breads left: " << van.getLeftovers() << endl;

        os << "Total delivery time: " << van.getTotalTime() << endl;
        if (selectedPhase != 1)
            os << "Total delay time: " << van.getTotalDelay() << endl;

        os << endl << "Client information (by order of delivery):" << endl;

        for (Client *client : clients) {
            os << client->getName() << " " << client->getVertex()->getPosition() << ":" << endl;

            if (selectedPhase != 1) {
                os << "Scheduled time: " << client->getDeliveryTime() << endl;
            }
            os << "Real time: " << client->getRealTime() << endl << endl;
        }

        os << "Van's path (by Edge ID):" << endl;
        for (int i = 0; i < edges.size(); ++i) {
            if (i != 0) os << "-";
            os << edges[i].getId();
        }
        os << endl << endl;
    }
}

void Interface::showResultGraphViewer() {
    cout << "Loading GraphViewer..." << endl;

    double nodeScale = 0.1;

    // Set coordinates of window center
    Vertex* startingVertex = this->bakery->getStartingVertex();
    sf::Vector2f centerPos(nodeScale * startingVertex->getPosition().getLatitude(),nodeScale *  startingVertex->getPosition().getLongitude());
    gv.setCenter(centerPos);
    gv.setScale(5 * nodeScale);   // Sets the window scale (works like a zoom)

    vector<Van> vans = bakery->getVans();

    for (int i = 0; i < vans.size(); ++i) {
        Van &van = vans[i];
        vector<Client *> clients = van.getClients();
        vector<Edge> edges = van.getEdges();

        if (clients.empty()) {
            continue;
        }

        Vertex* currV;
        for (int i = 0; i < edges.size(); ++i) {
            Edge& e = edges[i];
            this->addNodeToGV(e.getOrig(), nodeScale);
            this->addNodeToGV(e.getDest(), nodeScale);
            this->addEdgeToGV(e, gvEdge::DIRECTED, nodeScale);
        }
    }

    // Make the “background.png” image the background
    graphCities city = this->bakery->getGraph().getCity();
    if (city == graphCities::Penafiel)
        gv.setBackground("resources/maps/PenafielMap/penafielReal.png", sf::Vector2f(-400, -400), sf::Vector2f(1, 1));
    else if (city == graphCities::Espinho)
        gv.setBackground("resources/maps/EspinhoMap/espinhoReal.png", sf::Vector2f(-875, -155), sf::Vector2f(0.8, 0.8));
    else if (city == graphCities::Porto)
        gv.setBackground("resources/maps/PortoMap/portoReal.png", sf::Vector2f(-235, -310), sf::Vector2f(0.7, 0.6));

    // gv.setEnabledNodes(false); // Disable node drawing
    // gv.setEnabledEdgesText(false); // Disable edge text drawing
    gv.setZipEdges(true);

    // Create window
    gv.createWindow(600, 600);

    // Join viewer thread (blocks till window closed)
    gv.join();
}

void Interface::showSCCGraphViewer() {
    cout << "Loading GraphViewer..." << endl;

    gvEdge::EdgeType edgeType = this->bakery->getGraph().getIsDirected() == true ? gvEdge::DIRECTED : gvEdge::UNDIRECTED;

    double nodeScale = 0.1;

    // Set coordinates of window center
    Vertex* startingVertex = this->bakery->getStartingVertex();
    sf::Vector2f centerPos(nodeScale * startingVertex->getPosition().getLatitude(),nodeScale *  startingVertex->getPosition().getLongitude());
    gv.setCenter(centerPos);
    gv.setScale(5 * nodeScale);   // Sets the window scale (works like a zoom)

    vector<Van> vans = bakery->getVans();
    for(int i = 0; i < this->bakery->getGraph().getNumVertex(); i++) {
        Vertex* currVertex = this->bakery->getGraph().getVertexSet()[i];
        sf::Vector2f pos(nodeScale * currVertex->getPosition().getLatitude(), nodeScale *  currVertex->getPosition().getLongitude());
        gvNode &currNode = gv.addNode(currVertex->getId(), pos); // Create node
        // currNode.setLabel(to_string(currVertex->getId()));
        currNode.setSize(10 * nodeScale);
        currNode.setOutlineThickness(1 * nodeScale);
        if(currVertex == startingVertex) {
            currNode.setColor(GraphViewer::ORANGE);
            currNode.setSize(50 * nodeScale);
        }
    }
    for(Vertex* vert : this->bakery->getGraph().getVertexSet()) {
        for(const Edge& edge : vert->getAdj()) {
            gvNode& srcNode = gv.getNode(edge.getOrig()->getId());
            gvNode& destNode =  gv.getNode(edge.getDest()->getId());
            gvEdge &currEdge = gv.addEdge(edge.getId(), srcNode, destNode, edgeType);
            currEdge.setColor(GraphViewer::RED);   // Set color according to the component
            currEdge.setThickness(5 * nodeScale);
        }
    }

    // Make the “background.png” image the background
    graphCities city = this->bakery->getGraph().getCity();
    if (city == graphCities::Penafiel)
        gv.setBackground("resources/maps/PenafielMap/penafielReal.png", sf::Vector2f(-400, -400), sf::Vector2f(1, 1));
    else if (city == graphCities::Espinho)
        gv.setBackground("resources/maps/EspinhoMap/espinhoReal.png", sf::Vector2f(-875, -155), sf::Vector2f(0.8, 0.8));
    else if (city == graphCities::Porto)
        gv.setBackground("resources/maps/PortoMap/portoReal.png", sf::Vector2f(-235, -310), sf::Vector2f(0.7, 0.6));

    gv.setEnabledNodes(false); // Disable node drawing
    gv.setEnabledEdgesText(false); // Disable edge text drawing
    gv.setZipEdges(true);

    // Create window
    gv.createWindow(600, 600);

    // Join viewer thread (blocks till window closed)
    gv.join();
}

void Interface::addNodeToGV(Vertex* v, double nodeScale = 1) {
    try {
        gv.getNode(v->getId());
    } catch (out_of_range err) {
        sf::Vector2f pos(nodeScale * v->getPosition().getLatitude(),nodeScale *  v->getPosition().getLongitude());
        gvNode &currNode = gv.addNode(v->getId(), pos); // Create node
        // currNode.setLabel(to_string(v->getId()));
        currNode.setSize(10 * nodeScale);
        currNode.setOutlineThickness(1 * nodeScale);
        currNode.setColor(GraphViewer::RED);
        if(v == this->bakery->getStartingVertex()) {
            currNode.setColor(GraphViewer::ORANGE);
            currNode.setSize(nodeScale * 50);
        }
        else if(v->getClient() != NULL) {
            currNode.setColor(GraphViewer::GREEN);
            // currNode.setIcon()
            currNode.setSize(nodeScale * 50);
        }
    }
}

void Interface::addEdgeToGV(Edge &e, gvEdge::EdgeType edgeType, double nodeScale = 1) {
    try {
        gv.getEdge(e.getId());
    }
    catch (out_of_range err) {
        gvNode& srcNode = gv.getNode(e.getOrig()->getId());
        gvNode& destNode =  gv.getNode(e.getDest()->getId());
        gvEdge &currEdge = gv.addEdge(e.getId(), srcNode, destNode, edgeType);
        currEdge.setThickness(nodeScale * 5);
        currEdge.setColor(GraphViewer::WHITE);
        // currEdge.setLabel(to_string(e.getId()));
        // currEdge.setLabelColor(GraphViewer::RED);
        // currEdge.setLabelSize(20);
    }
}

void Interface::writeResultInFile() {
    cout << "Do you wish do write the result in a text file? (Y/N)" << endl;

    char res;
    while (true) {
        cin >> res;
        if (cin.fail() || cin.eof() || (toupper(res) != 'Y' && toupper(res) != 'N' && toupper(res) != 'L')) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "That's not a valid answer. Please answer with 'Y' or 'N'" << endl;
            continue;
        }
        break;
    }
    if (toupper(res) == 'N') return;

    string fileName;
    cout << "Insert the name of the file: ";
    cin >> fileName;
    ofstream fout;
    fout.open("resources/results/" + fileName);

    while (cin.fail() || cin.eof() || !fout.is_open()) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid file name!";
        cin >> fileName;
        fout.open("resources/results/" + fileName);
    }
    printResult(fout);
    cout << "Your result is stored at resources/results" << endl;
}
