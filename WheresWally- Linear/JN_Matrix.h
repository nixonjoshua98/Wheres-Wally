#ifndef JN_MATRIX_H
#define JN_MATRIX_H

class JN_Matrix
{
public:
	JN_Matrix();							// Default constructor
	JN_Matrix(int w, int h, double *data);	// Constructor overload
	~JN_Matrix();							// Deconstructor

	void SetData(double *data);					// Copies data to the internal container
	void SetData(int w, int h, double *data);	// Overload, re-size container
	void SetIndex(int x, int y, double v);		// Set a single index
	double GetIndex(int x, int y);				// Return value at index
	double GetIndex(int i);						// Return value at index
	double* GetContainer();						// Returns the whole matrix

private:
	int width;
	int height;
	double *container = NULL;
};

#endif // !JN_MATRIX_H
