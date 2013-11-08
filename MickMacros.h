#ifndef MICKMACROS_H
#define MICKMACROS_H

#include <iostream>
#include <sstream>
#include <stdio.h>

#ifndef __FUNCTION__
#define __FUNCTION__ __FUNC__
#endif

// ���� ���������� ����� ����, �������� �� ���� � qWarning � �������
#define WARNING_AND_RETURN_ON_NULL(var) if (var == NULL) { \
    std::cerr << __LINE__ << " " << __FUNCTION__ << ": value of \"" << #var << "\" is NULL\"" << std::endl; \
    return;\
    }

#define WARNING_AND_RETURN_ON_0(var) if (var == 0) { \
    std::cerr << __FUNCTION__ << ": value of \"" << #var << "\" is 0\n"; \
    return;\
    }

#define WARNING_AND_RETURN_VALUE_ON_0(var, returnValue) if (var == 0) { \
    std::cerr << __FUNCTION__ << ": value of \"" << #var << "\" is 0\n"; \
    return returnValue;\
    }

#define WARNING(msg) { \
    std::cerr << __LINE__ << " "<< __FUNCTION__ << ": " << msg << std::endl;  \
}

#define RETURN_ON_EQUALS(var1, var2) if (var1 == var2) return;
#define RETURN_VALUE_ON_EQUALS(var1, var2, returnValue) if (var1 == var2) return returnValue;

#define INTSTR(x) dynamic_cast< std::ostringstream & >( \
    (std::ostringstream() << std::dec << x)).str()

#endif // MICKMACROS_H
