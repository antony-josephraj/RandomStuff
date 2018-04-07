std::string Trim(std::string const& str)
{
    std::size_t first = str.find_first_not_of(" \t"); 

    // If there is no non-whitespace character, both first and last will be std::string::npos (-1)
    // There is no point in checking both, since if either doesn't work, the
    // other won't work, either.
    if(first == std::string::npos)
        return "";
 
    std::size_t last  = str.find_last_not_of(" \t"); 

    return str.substr(first, last-first+1);
}

std::string GetParentDir()
{
       std::size_t pos = 0;
       char buffer[MAX_PATH];
       GetModuleFileName( NULL, buffer, MAX_PATH );
       pos = std::string( buffer ).find_last_of( "\\/" );
       return (std::string( buffer ).substr( 0, pos));
}