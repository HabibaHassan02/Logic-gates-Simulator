#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<string>
using namespace std;

class Node {
    bool logic;
    string name;

public:
    Node() {
        logic = 0;
        name = "-";
    }
    Node(string n, bool value) {
        name = n;
        logic = value;
    }
    void setNodeVal(bool val) {
        logic = val;
    }
    bool getNodeVal() {
        return logic;
    }
    void setNodeName(string n) {
        name = n;
    }
    string getNodeName() {
        return name;
    }
    friend ostream& operator <<(ostream& output, const Node& n) {
        output << n.name << ": " << n.logic << "\n";
        return output;
    }
    friend istream& operator >>(istream& input, Node& n) {
        input >> n.name;
        return input;
    }
    bool AND(Node& A, Node& B) {
        if (A.logic == 1 && B.logic == 1)
            return 1;
        else return 0;
    }
    bool OR(Node& A, Node& B) {
        if (A.logic == 0 && B.logic == 0)
            return 0;
        else return 1;
    }
    bool XOR(Node& A, Node& B) {
        if (A.logic == B.logic)
            return 0;
        else return 1;
    }
};

class Gate {
protected:
    Node* input1 = new Node();
    Node* input2 = new Node();
    Node* output = new Node();
    string name;
public:
    Gate() {
        input1->setNodeVal(0);
        input1->setNodeName("A");
        input2->setNodeVal(0);
        input2->setNodeName("B");
        output->setNodeVal(0);
        output->setNodeName("O");
    }
    Gate(Node* A, Node* B, Node* O) {
        input1 = A;
        input2 = B;
        output = O;
    }
    Gate(Gate& sample) {
        input1 = sample.input1;
        input2 = sample.input2;
        output = sample.output;
        name = sample.name;
    }
    friend istream& operator >>(istream& input, Gate& g) {
        input >> g.name;
        return input;
    }
    void setInput1(Node* dummy) {
        input1 = dummy;
    }
    Node* getInput1() {
        return input1;
    }
    void setInput2(Node* dummy) {
        input2 = dummy;
    }
    Node* getInput2() {
        return input2;
    }
    void setOutput(Node* dummy) {
        output = dummy;
    }
    Node* getOutput() {
        return output;
    }
    void setGateName(string s) {
        name = s;
    }
    string getGateName() {
        return name;
    }
    virtual bool simulateGate() = 0;
};

class AND :public Gate {
public:
    bool simulateGate() {
        bool x = input1->AND(*input1, *input2);
        output->setNodeVal(x);
        return x;
    }
};

class OR :public Gate {
public:
    bool simulateGate() {
        bool x = input1->OR(*input1, *input2);
        output->setNodeVal(x);
        return x;
    }
};

class NAND :public Gate {
public:
    bool simulateGate() {
        bool x = input1->AND(*input1, *input2);
        output->setNodeVal(!x);
        return !x;
    }
};

class NOR :public Gate {
public:
    bool simulateGate() {
        bool x = input1->OR(*input1, *input2);
        output->setNodeVal(!x);
        return !x;
    }
};

class XOR :public Gate {
public:
    bool simulateGate() {
        bool x = input1->XOR(*input1, *input2);
        output->setNodeVal(x);
        return x;
    }
};

class XNOR :public Gate {
public:
    bool simulateGate() {
        bool x = input1->XOR(*input1, *input2);
        output->setNodeVal(!x);
        return !x;
    }
};

class NOT :public Gate {
public:
    bool simulateGate() {
        output=input2;
        bool x;
        if (input1->getNodeVal() == 1)
            x = 0;
        else x = 1;
        output->setNodeVal(x);
        return x;
    }
};

class Simulator {
protected:
    vector<Gate*> gates;
    vector<Node*> nodes;
public:
    void postGate(Gate* g) {
        gates.push_back(g);
    }
    void postNode(Node* n) {
        nodes.push_back(n);
    }
    int FindNode(string s) {
        for (vector<Node> ::size_type i = 0;i != nodes.size();i++) {
            if (nodes.at(i)->getNodeName() == s)
                return i;
        }
        return -1;
    }
    void startSimulate() {
        for (vector<Gate> ::size_type i = 0;i != gates.size();i++) {
            gates.at(i)->simulateGate();
        }
    }
};

class GateGenerator : public Simulator {
public:
    void parseInput() {
        string s;
        int i = -1;
        int y = i; //to track the adress of the gate 
        int c = 0; //to track number of nodes
        int n = 1; //number of gates of same type for labeling (tried to add it but not neccecary)
        int r = 0; //to track repeated nodes
        int final = 0; //to close
        while (cin >> s) {
            if (s == "AND" || s == "OR" || s == "NAND" || s == "NOR" || s == "XOR" || s == "XNOR" || s == "NOT") {
                r = 0;
                if (s == "AND")
                {
                    AND* A1 = new AND();
                    i = createGate(A1);
                    A1->setGateName(s + to_string(n));
                    n++;
                }
                else if (s == "OR")
                {
                    OR* A1 = new OR();
                    i = createGate(A1);
                    A1->setGateName(s);
                }
                else if (s == "NAND")
                {
                    NAND* A1 = new NAND();
                    i = createGate(A1);
                    A1->setGateName(s);
                }
                else if (s == "NOR")
                {
                    NOR* A1 = new NOR();
                    i = createGate(A1);
                    A1->setGateName(s);
                }
                else if (s == "XOR")
                {
                    XOR* A1 = new XOR();
                    i = createGate(A1);
                    A1->setGateName(s);
                }
                else if (s == "XNOR")
                {
                    XNOR* A1 = new XNOR();
                    i = createGate(A1);
                    A1->setGateName(s);
                }
                else if (s == "NOT")
                {
                    NOT* A1 = new NOT();
                    i = createGate(A1);
                    A1->setGateName(s);
                }
            }
            else if (s == "SIM")
            {
                SIM();
            }
            else if (s == "SET")
            {
                SET();
            }
            else if (s == "OUT")
            {
                cin >> s;
                if (s == "ALL")
                {
                    OUTALL(s);
                    final = 1;
                }
                else
                {
                    OUT(s);
                }
            }
            else {
                if (nodes.size() == 0) { //if it is the first node to be entered for the first gate
                    Node* N = new Node();
                    createNode(N);
                    N->setNodeName(s);
                    gates.at(i)->setInput1(N);
                    y = i; //to track the address of the gate and check on it
                    c = 1; //c=1 after setInput1, c=0 after setInput2
                    //if c==0 && y!=i then enter the first input
                    //if c==1 and y==i then enter the second input
                    //if c==0 and y==i then enter the output
                }
                else {
                    for (vector<Node> ::size_type t = 0;t != nodes.size();t++) {
                        if (s == nodes.at(t)->getNodeName()) { // to check if the node has entered before
                            r++; // if yes change this flag
                            if (y == i && c == 1) {
                                gates.at(i)->setInput2(nodes.at(t));
                                c = 0;
                            }
                            else if (c == 0 && y == i)
                            {
                                gates.at(i)->setOutput(nodes.at(t));
                            }
                            else {
                                gates.at(i)->setInput1(nodes.at(t)); //first input of new gate but not the first gate
                                y = i;
                                c = 1;
                            }
                            break;
                        }
                    }
                    if (r == 0) //if node is new, enter here
                    {
                        Node* N = new Node();
                        createNode(N);
                        N->setNodeName(s);
                        if (y == i && c == 1) {
                            gates.at(i)->setInput2(N);
                            c = 0;
                        }
                        else if (c == 0 && y == i)
                        {
                            gates.at(i)->setOutput(N);
                        }
                        else {
                            gates.at(i)->setInput1(N);
                            y = i;
                            c = 1;
                        }
                    }
                    r = 0; //if node was repeated and r changed to 1 return it to 0 here to be able to check on it again
                }
            }
            if (final == 1) { //end of inputs
                break;
            }
        }
    }
    int createNode(Node* n) {
        postNode(n);
        return nodes.size() - 1;
    }
    int createGate(Gate* g) {
        postGate(g);
        return gates.size() - 1;
    }
    void SIM() {
        startSimulate();
    }
    void SET() {
        string s;
        int x;
        cin >> s >> x;
        for (vector<Node> ::size_type i = 0;i != nodes.size();i++) {
            if (s == nodes.at(i)->getNodeName())
            {
                nodes.at(i)->setNodeVal(x);
                break;
            }
        }
    }
    void OUT(string s) {
        for (vector<Node> ::size_type i = 0;i != nodes.size();i++) {
            if (s == nodes.at(i)->getNodeName()) {
                cout << *nodes.at(i);
                break;
            }
        }
    }
    void OUTALL(string s) {
        for (vector<Node> ::size_type i = 0;i != nodes.size();i++) {
            cout << *nodes.at(i);
        }
    }
};


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    GateGenerator G;
    G.parseInput();
    return 0;
}
