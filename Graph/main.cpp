#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <list>
using namespace std;

ifstream df("data.txt");
ofstream out("protokolas.txt");

class Graph
{
private:
    int verticesNumber;
    vector<list<int>> adjacencyList;

    vector<list<int>> spanningTree;
    vector<int> sequence;

    bool validateVertex(int vertex)
    {
        if(vertex <= verticesNumber && vertex >= 1)
            return true;
        else
            return false;
    }

public:

    Graph(int verticesNumber)
    {
        this->verticesNumber = verticesNumber;
        adjacencyList.resize(verticesNumber);
        spanningTree.resize(verticesNumber);
        sequence.resize(100);
    }

    void addEdge(int vertex, int edge)
    {
        if(!validateVertex(vertex) || !validateVertex(edge))
        {
            cout << "Klaida skaitant duomenis" << endl;
            exit(0);
        }

        adjacencyList[vertex-1].push_back(edge);
    }

    void BFS(int source)
    {
        if(!validateVertex(source))
        {
            cout << "Ivestas netinkamas skaicius" << endl;
            exit(0);
        }

        int wave = 0;
        int addWave = 0;
        int leftWave = 0;

        vector<bool> visited;
        visited.resize(verticesNumber,false);

        list<int> queue;
    
        visited[source-1] = true;
        queue.push_back(source);

        while(!queue.empty())
        {
            if(leftWave == 0)
            {
                out << "BANGA " << wave << "." << endl;
                leftWave += addWave;
                if(leftWave > 0)
                    --leftWave;
                addWave = 0;
                if (wave == 0)
                    out << "Pradine padetis " << (char) (source + 64) << "." << endl;
                wave++;
            }
            else
            {
                --leftWave;
            }

            source = queue.front();
            queue.pop_front();

            if(wave > 1)
                out << "Atidaryta virsune " << (char) (source + 64) << "." << endl;

            int count = 0;
            for (auto adjacent: adjacencyList[source-1])
            {
                count++;
                out << "     " << count << ") Tikrinama " << (char) (adjacent + 64);
                if (!visited[adjacent-1])
                {
                    addWave++;
                    out << " - atidaryta. ";
                    visited[adjacent-1] = true;
                    queue.push_back(adjacent);
                    out << "I eile pridedama " << (char) (adjacent + 64) << ". Sudaroma briauna " << (char) (source + 64) << "->" << (char) (adjacent + 64) << ". Uzdaroma " << (char) (adjacent + 64) << "." << endl;
                    spanningTree[source-1].push_back(adjacent);
                }
                else
                {
                    out << " - uzdaryta." << endl;
                }
            }

            out << endl;
        }
    }

    void printSpanningTree(int start)
    {
        int height = 0;

        sequence.push_back(start-1);
        out << "  " << (char) (sequence.back()+ 65) << endl;
        cout << " " << (char) (sequence.back()+ 65) << endl;

        searchTree(height);
    }

    void searchTree(int height)
    {
        height++;
        for(auto value : spanningTree[sequence.back()])
        {
            out << "  ";
            cout << " ";
            for(int i = 1; i <= height; i++)
            {
                out << "-";
                cout << "-";
            }
            out << (char) (value + 64) << endl;
            cout << (char) (value + 64) << endl;

            sequence.push_back(value-1);

            searchTree(height);
            sequence.pop_back();
        }
        height--;
        return;
    }
};

void readVerticesNumber(int &verticesNumber)
{
    string s;

    if(!df)
    {
        cout << "Failo data.txt neimanoma atidaryti." << endl;
        out << endl << "TRECIA DALIS. Rezultatai" << endl;
        out << "  1) Programa sekmingai nebaige darbo." << endl;
        cout << "Uzdaroma programa..." << endl;
        exit(0);
    }

    df >> verticesNumber;
    getline(df, s);

    if(verticesNumber >= 1)
    {
        cout << "1) Grafo virsuniu skaicius N = " << verticesNumber << "." << endl;
        out << "  1) Grafo virsuniu skaicius N = " << verticesNumber << "." << endl;
    }
    else
    {
        cout << "Neteisingas virsuniu skaicius N." << endl;
        out << endl << "TRECIA DALIS. Rezultatai" << endl;
        out << "  1) Programa sekmingai nebaige darbo." <<endl;
        cout << "Uzdaroma programa..." << endl;
        exit(0);
    }
}

void readAdjacent(Graph &graph, int &start, int count)
{
    string s;
    char c;
    char letter;
    int vertex;
    int edge;

    cout << "2) Kaimynystes sarasai: E = {";
    out << "  2) Kaimynystes sarasai: E = {";
    while(true)
    {
        df >> c;
        if(c == '/')
            break;
        df >> letter;
        vertex = (int) letter - 64;
        df >>c >> letter >> c >> ws;
        edge = (int) letter - 64;
        cout << " (" << (char) (vertex + 64) << "," << (char) (edge + 64) << ") ";
        out << " (" << (char) (vertex + 64) << "," << (char) (edge + 64) << ") ";
        graph.addEdge(vertex, edge);
    }
    getline(df, s);
    cout << "}." << endl;
    out << "}." << endl;

    df >> letter;
    start = (int) letter - 64;
    if(start < 1 || start > count)
    {
        cout << "Neteisinga pradzios virsune S." << endl;
        out << endl << "TRECIA DALIS. Rezultatai" << endl;
        out << "  1) Programa sekmingai nebaige darbo." << endl;
        cout << "Uzdaroma programa..." << endl;
        exit(0);
    }

    cout << "3) Pradine padetis " << (char) (start + 64) << "." << endl;
    out << "  3) Pradine padetis " << (char) (start + 64) << "." << endl;
}

int main()
{
    int count;
    int start;

    system("cls");
    cout << "Pijus Zlatkus, 4 grupe 2 pogrupis, 4 uzdavinis 14 variantas." << endl;
    cout << "Uzduotis - Is duoto grafo suformuoti medi. (Grafo realizacija grindziama kaimynystes sarasais; naudoti paieskos i ploti metoda)." << endl << endl;
    cout << "Pradiniai duomenys:" << endl;

    out << "Pijus Zlatkus, 4 grupe 2 pogrupis, 4 uzdavinis 14 variantas." << endl;
    out << "Uzduotis - Is duoto grafo suformuoti medi. (Grafo realizacija grindziama kaimynystes sarasais; naudoti paieskos i ploti metoda)." << endl << endl;
    out << "PIRMA DALIS. Duomenys" << endl;

    readVerticesNumber(count);
    Graph graph(count);
    readAdjacent(graph, start, count);

    out << endl << "ANTRA DALIS. Vykdymas" << endl << endl;
    graph.BFS(start);

    out << endl << "TRECIA DALIS. Rezultatai" << endl;
    out << endl;
    cout << endl << "Rezultatai:" << endl;
    cout << endl;

    graph.printSpanningTree(start);
    return 0;
}