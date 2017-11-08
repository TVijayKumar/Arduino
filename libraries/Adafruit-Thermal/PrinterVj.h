#ifndef __Printer_vj__
#define __Printer_vj__

#include "Adafruit_Thermal.h"

class PrinterVj{
public:
	void printerInit();
	void printStr(char *str);
};

#endif