#include "Registry.hh"


typedef map<string, Registry::Factory> dict;

bool init = false;
dict* reg = 0;


int Registry::Register (const char* name, Factory factory) {
    if (not init) {
        init = true;
        reg = new map<string, Factory>();
    }
    (*reg)[name] = factory;
    return 999;
}


Player* Registry::new_player (string name) {
    dict::iterator it = reg->find(name);
    if (it == reg->end()) myerrx("player %s not registered.", name.c_str());
    Factory f = it->second;
    return f();
}


void Registry::print_players (ostream& os) {
    for (dict::iterator it = reg->begin(); it != reg->end(); ++it) {
        os << it->first << endl;
}   }
