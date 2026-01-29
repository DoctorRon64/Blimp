#pragma once

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>

#include <array>
#include <map>
#include <ostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Blimp/Log.h"

#if defined(BLIMP_PLATFORM_WINDOWS)
#include <Windows.h>
#elif defined(BLIMP_PLATFORM_LINUX)
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#endif