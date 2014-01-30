#ifndef __WHITE_WHITE__
#define __WHITE_WHITE__

class Singleton
{
  private:
    Singleton() {}; // Constructor? (the {} brackets) are needed here.
    // Dont forget to declare these two. You want to make sure they
    // are unaccessable otherwise you may accidently get copies of
    // your singleton appearing.
    Singleton(Singleton const&);        // Don't Implement
    void operator=(Singleton const&);   // Don't implement
  public:
    static Singleton& getInstance()
    {
      static Singleton instance; 	// Guaranteed to be destroyed.
      // Instantiated on first use.
      return instance;
    }
};

#endif
