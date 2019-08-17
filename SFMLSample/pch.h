// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

/// biblioteki SFML
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

/// biblioteki C++
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <windows.h>
#include <random>
#include <map>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <queue>
#include <stack>
#include <string>
#include <queue>
#include <set>

/// pliki nagłówkowe
/// najpierw klasy wirtulane

#include "Globals.h"

#include "Log.h"

#include "Object.h"
#include "Function.h"
#include "Generator.h"

#include "Fraction.h"
#include "Player.h"

#include "Types.h"

#include "District.h"

#include "mapOverlay.h"
#include "Button.h"
#include "Unit.h"
#include "Selectable.h"
#include "City.h"
#include "Data.h"


#include "Tile.h"
#include "Map.h"

#include "Army.h"
#include "Engine.h"

// TODO: add headers that you want to pre-compile here

#endif /* PCH_H */
