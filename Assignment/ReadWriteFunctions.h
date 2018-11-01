#ifndef READ_WRITE_FUNCTIONS_H
#define READ_WRITE_FUNCIONS_H

double* ReadText(char *fileName, int matrixWidth, int matrixHeight, bool &flag);

void WritePGM(char *fileName, double *data, int matrixWidth, int matrixHeight, int Q, bool &flag);


#endif // !READ_WRITE_FUNCTIONS_H
