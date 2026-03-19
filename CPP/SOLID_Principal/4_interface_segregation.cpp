Suppose we have to design a system for Printers in which we have to implement different types 
of Printers like LaserPrinter, InkJetPrinter, LEDPrinter, 3DPrinter.

We can have a abstract class for Printer which will implement the methods like Print,
Scan and Fax.

class Printer {
public:
  virtual void print() = 0;
  virtual void scan() = 0;
  virtual void fax() = 0;
};        
Now let’s implement some of types of Printer

InkJetPrinter
class InkJetPrinter : public Printer {
  public:
    void print() override {
      cout << "InkJet Printer Printing" << endl;
      // Implementation of print for InkJet printer
    }

    void scan() override {
      cout << "InkJet Printer Scanning" << endl;
      // Implementation of scan for InkJet printer
    }

    void fax() override {
      cout << "InkJet Printer Faxing" << endl;
      // Implementation of fax for InkJet printer
    }
};        
LaserPrinter
class LaserPrinter : public Printer {
  public:
    void print() override {
      cout << "Laser Printer Printing" << endl;
      // Implementation of print for laser printer
    }
    
    void scan() override {
      cout << "Laser Printer Scanning" << endl;
      // Implementation of scan for laser printer
    }

    void fax() override {
        throw runtime_error("Laser Printer Can't Fax");
    }
};        
Problem in above approach
The LaserPrinter class does not need the fax() method, but it is forced to implement it because 
it has to adhere to the Printer interface(abstract class).

This violates the Interface Segregation Principle as LaserPrinter class is forced to implement
the fax even it does not support the functionality of Faxing.
