#include<iostream>

using namespace std;

class P {
public:
    P(int id) { m_id = id; }

    virtual ~P() = default;

    bool operator==(P p) const {
        return p.getId() == m_id;
    }

    bool operator!=(P p) const {
        return p.getId() != m_id;
    }

    int getId() { return m_id; }

private:
    int m_id;

};

typedef void (P::*p_function)();

int main() {
    P p1(1), p2(1), p3(2);

    cout << (p1 == p2) << endl;
    cout << (p1 != p3) << endl;
    cout << (p1 == p3) << endl;

    return 0;
}
