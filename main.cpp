#include<iostream>
#include <vector>
#include <algorithm>

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

    bool operator<(P p) const{
        return m_id < p.getId();
    }

    int getId() { return m_id; }

private:
    int m_id;

};

typedef void (P::*p_function)();

int main() {
    P p1(1), p2(2), p3(3);
    std::vector<P> v;
    v.push_back(p2);
    v.push_back(p1);
    v.push_back(p3);

    std::sort(v.begin(),v.end());

    std::vector<P>::iterator last = v.end();
    P p=v.back();
//    p->getId();
    return 0;
}
