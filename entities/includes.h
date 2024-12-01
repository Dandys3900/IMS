#ifndef INCLUDEFILE_H
#define INCLUDEFILE_H

/***** CONSTS *****/

/***** LIBS *****/
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <atomic>
#include <simlib.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <exception>
#include <map>
#include <cmath>
#include <iomanip>

using namespace std;

/***** OTHERS *****/
#include "time.h"

// Key is coin (unique) name and value is owned amount
using CoinsStats = map<string, double>;
// Key is coin (unique) name and value is (sell_threshold, buy_threshold)
using CoinsThresholds = map<string, pair<double, double>>;

#endif // INCLUDEFILE_H