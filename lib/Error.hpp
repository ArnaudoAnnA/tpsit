#ifndef ERROR_HPP_INCLUDED
#define ERROR_HPP_INCLUDED

void error(int n, char* s)
{
    printf("\n  ERRORE %d %s", errno strerror(errno));
    printf("\n  durante %s esco con %d", s, n);
    exit(n);
}


#endif // ERROR_HPP_INCLUDED
