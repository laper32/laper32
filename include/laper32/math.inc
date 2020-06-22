#if defined _math_included
#endinput
#endif
#define _math_included

// Useful macros

/**
 * @brief Returns the smaller of two provided values.
 *  
 * @param i1                The first value.
 * @param i2                The second value.
 *
 * @return                  The smallest value.
 **/
stock any min(any i1, any i2) 
{
    return (i1 < i2 ? i1 : i2); 
} 

/**
 * @brief Returns the bigger of two provided values.
 *  
 * @param i1                The first value.
 * @param i2                The second value.
 *
 * @return                  The biggest value.
 **/
stock any max(any i1, any i2) 
{
    return (i1 > i2 ? i1 : i2); 
}