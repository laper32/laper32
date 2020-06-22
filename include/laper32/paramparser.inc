#if defined _paramparser_included
#endinput
#endif
#define _paramparser_included

/**
 * @section Parsing error codes.
 **/
#define PARAM_ERROR_NO                  -1  /** No errors. */
#define PARAM_ERROR_EMPTY               0   /** Source string is empty. */
#define PARAM_ERROR_UNEXPECTED_KEY      1   /** Unexpected key name. */
#define PARAM_ERROR_UNEXPECTED_END      2   /** Unexpected end of source string. */
#define PARAM_ERROR_MISSING_SEPARATOR   3   /** Could not find a separator sign after key name. */
#define PARAM_ERROR_MISSING_QUOTES      4   /** Could not find a quotes sign (") after key name. */
#define PARAM_ERROR_UNKNOWN             5   /** Unknown error. The parser got a invalid result from a search function it couldn't handle. */
#define PARAM_ERROR_FULL                6   /** Destination array is full. */
/**
 * @endsection
 **/

/**
 * Errors description for a codes.
 **/
char sParamError[7][PLATFORM_LINE_LENGTH] = {
    /*"No errors",*/
    "Source string is empty",
    "Unexpected key name",
    "Unexpected end of source string",
    "Could not find a separator sign after key name",
    "Could not find a quotes sign (\") after key name",
    "Unknown error. The parser got a invalid result from a search function it couldn't handle",
    "Destination array is full"
};

/**
 * @brief Parses a parameter string in key = "value" format and store the result in a ParamParseResult array.
 *
 * @param arrayBuffer       Handle of the buffer array containing value data.
 * @param sParamString      The source string to parse. Error message output.
 * @param iMaxLen           Maximum number of keys that can be stored (first dimension of buffer).
 * @param cSeparator        The separator character.
 * @return                  Returns error code if parsing error.
 **/
inline int ParamParseString(ArrayList &arrayBuffer, char[] sParamString, int iMaxLen, char cSeparator)
{
    /*
     *  VALIDATION OF INPUT AND BUFFERS
     */

    // Cut out comments at the end of a line
    SplitString(sParamString, "//", sParamString, iMaxLen);
     
    // Trim string
    TrimString(sParamString);

    // Gets string length
    int iLen = strlen(sParamString);
    
    // Check if string is empty
    if (!iLen)
    {
        strcopy(sParamString, iMaxLen, sParamError[PARAM_ERROR_EMPTY]);
        return PARAM_ERROR_EMPTY;
    }

    // Check if there space left in the destination buffer
    if (iMaxLen > PLATFORM_LINE_LENGTH || iLen > PLATFORM_LINE_LENGTH)
    {
        // Exit loop. No more parameters can be parsed
        strcopy(sParamString, iMaxLen, sParamError[PARAM_ERROR_FULL]);
        return PARAM_ERROR_FULL;
    }
    
    /*__________________________________________________________________________*/

    // Initialize char array
    static char sValue[SMALL_LINE_LENGTH][PLATFORM_LINE_LENGTH];

    // Position of separator character
    int iSeparatorPos = FindCharInString(sParamString, cSeparator, false);

    // Parse error
    if (iSeparatorPos == -1)
    {
        strcopy(sParamString, iMaxLen, sParamError[PARAM_ERROR_MISSING_SEPARATOR]);
        return PARAM_ERROR_MISSING_SEPARATOR;
    }

    /*__________________________________________________________________________*/
    
    // Extract key name
    StrExtract(sValue[0], sParamString, 0, iSeparatorPos);

    // Trim string
    TrimString(sValue[0]);
    
    // Strips a quote pair off a string 
    StripQuotes(sValue[0]);
    
    // Check if string is empty, then stop
    if (!hasLength(sValue[0]))
    {
        strcopy(sParamString, iMaxLen, sParamError[PARAM_ERROR_UNEXPECTED_KEY]);
        return PARAM_ERROR_UNEXPECTED_KEY;
    }

    // Push key name into array
    arrayBuffer.PushString(sValue[0]);

    /*__________________________________________________________________________*/

    // Extract value string
    StrExtract(sParamString, sParamString, iSeparatorPos + 1, iLen);

    // Trim string
    TrimString(sParamString);
    
    // Check if string is empty, then stop
    if (!hasLength(sParamString))
    {
        strcopy(sParamString, iMaxLen, sParamError[PARAM_ERROR_UNEXPECTED_END]);
        return PARAM_ERROR_UNEXPECTED_END;
    }

    // Checks if string has incorrect quotes
    int iQuotes = CountCharInString(sParamString, '"');
    if (iQuotes & 1) /// Is odd ?
    {
        strcopy(sParamString, iMaxLen, sParamError[PARAM_ERROR_MISSING_QUOTES]);
        return PARAM_ERROR_MISSING_QUOTES;
    }

    // Only for one "value"
    if (iQuotes == 2)
    {
        // Strips a quote pair off a string 
        StripQuotes(sParamString);

        // Push value string into array
        arrayBuffer.PushString(sParamString);
    }
    else
    {
        // Breaks a string into pieces and stores each piece into an array of buffers
        int iAmount = ExplodeString(sParamString, ",", sValue, sizeof(sValue), sizeof(sValue[]));
        
        // i = value index
        for (int i = 0; i < iAmount; i++)
        {
            // Trim string
            TrimString(sValue[i]);
            
            // Checks if string has incorrect quotes
            iQuotes = CountCharInString(sValue[i], '"');
            if (iQuotes & 1) /// Is odd ?
            {
                strcopy(sParamString, iMaxLen, sParamError[PARAM_ERROR_MISSING_QUOTES]);
                return PARAM_ERROR_MISSING_QUOTES;
            }
            
            // Strips a quote pair off a string 
            StripQuotes(sValue[i]);

            // Push value string into array
            arrayBuffer.PushString(sValue[i]);
        }
    }


    // Return on success
    return PARAM_ERROR_NO;
}

/**
 * @brief Extracts a area in a string between two positions.
 *
 * @param sBuffer           Destination string buffer.
 * @param sSource           Source string to extract from.
 * @param startPos          Start position of string to extract.
 * @param endPos            End position of string to extract.
 * @return                  The number of cells written.
 **/
inline int StrExtract(char[] sBuffer, char[] sSource, int startPos, int endPos)
{
    // Calculate string length. Also add space for null terminator
    int iMaxLen = endPos - startPos + 1;
    
    // Validate length
    if (iMaxLen < 0)
    {
        sBuffer[0] = NULL_STRING[0];
        return 0;
    }
    
    // Extract string and store it in the buffer
    return strcopy(sBuffer, iMaxLen, sSource[startPos]);
}

/**
 * @brief Checks whether a substring is found inside another string.
 * @param sBuffer           The substring to find inside the original string.
 * @param sSource           The string to search in. 
 * @param cSeparator        The separator character.
 * @return                  True or false.
 **/
inline bool StrContain(char[] sBuffer, char[] sSource, char cSeparator)
{
    // i = char index
    int iLen1 = strlen(sSource); int iLen2 = strlen(sBuffer); int x; int y;
    for (int i = 0; i < iLen1; i++) 
    {
        // Validate char
        if (sSource[i] == sBuffer[x])
        {
            if (++x == iLen2) /// Check length 
            {
                // Validate delimitter
                y = i + 1;
                if (y >= iLen1 || (sSource[y] == cSeparator || sSource[y] == ' '))
                {
                    return true;
                }
            }
            else if (x == 1) /// Check first comparator
            {
                // Validate prefix
                y = i - 1;
                if (y != -1 && (sSource[y] != cSeparator && sSource[y] != ' '))
                {
                    x = 0; /// Resets counter
                }
            }
        }
        else 
        {
            x = 0; /// Resets counter
        }
    }
    
    // Return on unsuccess
    return false;
}

/**
 * @brief Finds the amount of all occurrences of a character in a string.
 *
 * @param sBuffer           Input string buffer.
 * @param cSymbol           The character to search for.
 * @return                  The amount of characters in the string, or -1 if the characters were not found.
 */
inline int CountCharInString(char[] sBuffer, char cSymbol)
{
    // Initialize index
    int iCount;
    
    // i = char index
    int iLen = strlen(sBuffer);
    for (int i = 0; i < iLen; i++) 
    {
        // Validate char
        if (sBuffer[i] == cSymbol)
        {
            // Increment amount
            iCount++;
        }
    }

    // Return amount
    return iCount ? iCount : -1;
}

/**
 * @brief Converts uppercase chars in the string to lowercase chars.
 *
 * @param sBuffer           Input string buffer.
 */
inline void StringToLower(char[] sBuffer)
{
    // i = char index
    int iLen = strlen(sBuffer);
    for (int i = 0; i < iLen; i++) 
    {
        // Character to convert
        sBuffer[i] = CharToLower(sBuffer[i]);
    }
}

/**
 * @brief Randomly permutes the specified list using a default source of randomness.
 *
 * @param hArrayList        The array that is being shuffle.
 **/
inline void ArrayShuffle(ArrayList hArrayList)
{
    // i = client index
    int iSize = hArrayList.Length; int iLen = iSize - 1;
    for (int i = 0; i < iSize; i++)
    {
        // Simple swap
        hArrayList.SwapAt(i, GetRandomInt(0, iLen));
    }
}

/**
 * @brief Sort comparison function by string length.
 *
 * @param iIndex1           The first index to compare.
 * @param iIndex2           The second index to compare.
 * @param hArrayList        The array that is being sorted (order is undefined).
 * @param hCustom           Handle optionally passed in while sorting.
 **/
public int Sort_ByLength(int iIndex1, int iIndex2, ArrayList hArrayList, Handle hCustom)
{
    // Gets strings
    static char sBuffer1[PLATFORM_LINE_LENGTH]; 
    hArrayList.GetString(iIndex1, sBuffer1, sizeof(sBuffer1));
    static char sBuffer2[PLATFORM_LINE_LENGTH];
    hArrayList.GetString(iIndex2, sBuffer2, sizeof(sBuffer2));
    
    // Gets string lengths
    int iLen1 = strlen(sBuffer1); int iLen2 = strlen(sBuffer2); 
    
    // Move left
    if (iLen1 < iLen2)
    {
        return -1;
    }
    // Move right
    else if (iLen1 > iLen2)
    {
        return 1;
    }
    
    // Skip it
    return 0;
}