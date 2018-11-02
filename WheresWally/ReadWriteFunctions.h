#ifndef READ_WRITE_FUNCTIONS_H
#define READ_WRITE_FUNCIONS_H

/*
Code was provided by the University (the .h file was not)
I modified the paramaters and renamed variables
*/

// Reads the text file and returns a 1D array of the values
double* ReadText(char *fileName, int matrixWidth, int matrixHeight, bool &flag);


// Writes a double array to a .pgm file
void WritePGM(char *fileName, double *data, int matrixWidth, int matrixHeight, int Q, bool &flag);


#endif // !READ_WRITE_FUNCTIONS_H
