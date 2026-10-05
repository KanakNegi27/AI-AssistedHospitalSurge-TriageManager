#ifndef LOGIN_H
#define LOGIN_H

#include <vector>
#include "hospital.h"

// returns the position of the hospital if the password is right, else -1
int staffLogin(std::vector<Hospital> &h);

#endif
