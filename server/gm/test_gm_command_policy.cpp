#include "gm_command_policy.h"
#include <cassert>
#include <iostream>
using namespace nistor2;
int main() {
    assert(!authorize(Role::Player,"/item 19 1").allowed);
    assert(!authorize(Role::Player,"/gmhelp").allowed);
    assert(authorize(Role::Helper,"/where").allowed);
    assert(!authorize(Role::Helper,"/kick Test reason").allowed);
    assert(authorize(Role::GM,"/goto Test").allowed);
    assert(!authorize(Role::GM,"/setyang Test 100").allowed);
    assert(authorize(Role::Admin,"/spawn 101 1").allowed);
    assert(!authorize(Role::Owner,"/shutdown prepare").allowed);
    assert(!authorize(Role::Owner,"/notarealcommand").allowed);
    assert(!authorize(Role::Owner,"/notice hello\nworld").allowed);
    assert(!authorize(Role::Owner,"/notice "+std::string(300,'x')).allowed);
    std::cout<<"GM policy checks passed\n";
}
